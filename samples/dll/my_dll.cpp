/////////////////////////////////////////////////////////////////////////////
// Name:        my_dll.cpp
// Purpose:     Sample showing how to use wx from a DLL
// Author:      Vaclav Slavik
// Created:     2009-12-03
// RCS-ID:      $Id$
// Copyright:   (c) 2009 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef __WXMSW__
    #error "This sample is MSW-only"
#endif

#include "wx/app.h"
#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/button.h"
#include "wx/thread.h"
#include "wx/msgdlg.h"
#include "wx/msw/wrapwin.h"

#include <process.h> // for _beginthreadex()

#include "my_dll.h"

// ----------------------------------------------------------------------------
// GUI classes
// ----------------------------------------------------------------------------

class MyDllFrame : public wxFrame
{
public:
    MyDllFrame(wxWindow *parent, const wxString& label);

    void OnAbout(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};


static const int CMD_SHOW_WINDOW = wxNewId();
static const int CMD_TERMINATE = wxNewId();

class MyDllApp : public wxApp
{
public:
    MyDllApp();

private:
    void OnShowWindow(wxThreadEvent& event);
    void OnTerminate(wxThreadEvent& event);
};


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// MyDllFrame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyDllFrame, wxFrame)
    EVT_BUTTON(wxID_ABOUT, MyDllFrame::OnAbout)
END_EVENT_TABLE()

MyDllFrame::MyDllFrame(wxWindow *parent, const wxString& label)
    : wxFrame(parent, wxID_ANY, label)
{
    wxPanel *p = new wxPanel(this, wxID_ANY);
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add
           (
               new wxStaticText
                   (
                       p, wxID_ANY,
                       wxString::Format
                       (
                           "Running using %s\n"
                           "wxApp instance is %p, thread ID %ld",
                           wxVERSION_STRING,
                           wxApp::GetInstance(),
                           wxThread::GetCurrentId()
                       )
                   ),
               wxSizerFlags(1).Expand().Border(wxALL, 10)
           );

    sizer->Add
           (
               new wxButton(p, wxID_ABOUT, "Show info"),
               wxSizerFlags(0).Right().Border(wxALL, 10)
           );

    p->SetSizerAndFit(sizer);

    wxSizer *fsizer = new wxBoxSizer(wxVERTICAL);
    fsizer->Add(p, wxSizerFlags(1).Expand());
    SetSizerAndFit(fsizer);
}

void MyDllFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("This window is running in its own thread,\n"
                 "using private wxWidgets instance compiled into the DLL.",
                 "About",
                 wxOK | wxICON_INFORMATION);
}


// ----------------------------------------------------------------------------
// MyDllApp
// ----------------------------------------------------------------------------

MyDllApp::MyDllApp()
{
    // Keep the wx "main" thread running even without windows. This greatly
    // simplifies threads handling, because we don't have to correctly
    // implement wx-thread restarting.
    //
    // Note that this only works if you don't explicitly call ExitMainLoop(),
    // except in reaction to wx_dll_cleanup()'s message. wx_dll_cleanup()
    // relies on the availability of wxApp instance and if the event loop
    // terminated, wxEntry() would return and wxApp instance would be
    // destroyed.
    //
    // Also note that this is efficient, because if there are no windows, the
    // thread will sleep waiting for a new event. We could safe some memory
    // by shutting the thread down when it's no longer needed, though.
    SetExitOnFrameDelete(false);

    Connect(wxEVT_IDLE, wxIdleEventHandler(MyDllApp::OnIdle));
    Connect(CMD_SHOW_WINDOW,
            wxEVT_COMMAND_THREAD,
            wxThreadEventHandler(MyDllApp::OnShowWindow));
    Connect(CMD_TERMINATE,
            wxEVT_COMMAND_THREAD,
            wxThreadEventHandler(MyDllApp::OnTerminate));
}

void MyDllApp::OnShowWindow(wxThreadEvent& event)
{
    wxFrame *f = new MyDllFrame(NULL, event.GetString());
    f->Show(true);
}

void MyDllApp::OnTerminate(wxThreadEvent& WXUNUSED(event))
{
    ExitMainLoop();
}


// ----------------------------------------------------------------------------
// application startup
// ----------------------------------------------------------------------------

// we can't have WinMain() in a DLL and want to start the app ourselves
IMPLEMENT_APP_NO_MAIN(MyDllApp)

namespace
{

// Critical section that guards everything related to wxWidgets "main" thread
// startup or shutdown.
wxCriticalSection gs_wxStartupCS;
// Handle of wx "main" thread if running, NULL otherwise
HANDLE gs_wxMainThread = NULL;


//  wx application startup code -- runs from its own thread
unsigned wxSTDCALL MyAppLauncher(void* event)
{
    // Note: The thread that called run_wx_gui_from_dll() holds gs_wxStartupCS
    //       at this point and won't release it until we signal it.

    // We need to pass correct HINSTANCE to wxEntry() and the right value is
    // HINSTANCE of this DLL, not of the main .exe.
    //
    // This method of obtaining DLL's instance handle requires at least
    // Windows XP/2003. We could also implement DllMain() and remember it from
    // there, that would work on older systems too.
    HINSTANCE hInstance;
    int ret = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                                (LPCTSTR)&MyAppLauncher,
                                &hInstance);
    if ( ret == 0 )
        return 0; // failed to get DLL's handle

    // IMPLEMENT_WXWIN_MAIN does this as the first thing
    wxDISABLE_DEBUG_SUPPORT();

    // We do this before wxEntry() explicitly, even though wxEntry() would
    // do it too, so that we know when wx is initialized and can signal
    // run_wx_gui_from_dll() about it *before* starting the event loop.
    wxInitializer wxinit;
    if ( !wxinit.IsOk() )
        return 0; // failed to init wx

    // Signal run_wx_gui_from_dll() that it can continue
    HANDLE hEvent = *(static_cast<HANDLE*>(event));
    if ( !SetEvent(hEvent) )
        return 0; // failed setting up the mutex

    // Run the app:
    wxEntry(hInstance);

    return 1;
}

} // anonymous namespace

// ----------------------------------------------------------------------------
// public DLL interface
// ----------------------------------------------------------------------------

extern "C" WXEXPORT
void run_wx_gui_from_dll(const char *title)
{
    // In order to prevent conflicts with hosting app's event loop, we
    // launch wx app from the DLL in its own thread.
    //
    // We can't even use wxInitializer: it initializes wxModules and one of
    // the modules it handles is wxThread's private module that remembers
    // ID of the main thread. But we need to fool wxWidgets into thinking that
    // the thread we are about to create now is the main thread, not the one
    // from which this function is called.
    //
    // Note that we cannot use wxThread here, because the wx library wasn't
    // initialized yet. wxCriticalSection is safe to use, though.

    wxCriticalSectionLocker lock(gs_wxStartupCS);

    if ( !gs_wxMainThread )
    {
        HANDLE hEvent = CreateEvent
                        (
                            NULL,  // default security attributes
                            FALSE, // auto-reset
                            FALSE, // initially non-signaled
                            NULL   // anonymous
                        );
        if ( !hEvent )
            return; // error

        // NB: If your compiler doesn't have _beginthreadex(), use CreateThread()
        gs_wxMainThread = (HANDLE)_beginthreadex
                                  (
                                      NULL,           // default security
                                      0,              // default stack size
                                      &MyAppLauncher,
                                      &hEvent,        // arguments
                                      0,              // create running
                                      NULL
                                  );

        if ( !gs_wxMainThread )
        {
            CloseHandle(hEvent);
            return; // error
        }

        // Wait until MyAppLauncher signals us that wx was initialized. This
        // is because we use wxMessageQueue<> and wxString later and so must
        // be sure that they are in working state.
        WaitForSingleObject(hEvent, INFINITE);
        CloseHandle(hEvent);
    }

    // Send a message to wx thread to show a new frame:
    wxThreadEvent *event =
        new wxThreadEvent(wxEVT_COMMAND_THREAD, CMD_SHOW_WINDOW);
    event->SetString(title);
    wxQueueEvent(wxApp::GetInstance(), event);
}


extern "C" WXEXPORT
void wx_dll_cleanup(void)
{
    wxCriticalSectionLocker lock(gs_wxStartupCS);

    if ( !gs_wxMainThread )
        return;

    // If wx main thread is running, we need to stop it. To accomplish this,
    // send a message telling it to terminate the app.
    wxThreadEvent *event =
        new wxThreadEvent(wxEVT_COMMAND_THREAD, CMD_TERMINATE);
    wxQueueEvent(wxApp::GetInstance(), event);

    // We must then wait for the thread to actually terminate.
    WaitForSingleObject(gs_wxMainThread, INFINITE);
    CloseHandle(gs_wxMainThread);
    gs_wxMainThread = NULL;
}
