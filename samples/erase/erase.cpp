/////////////////////////////////////////////////////////////////////////////
// Name:        erase.cpp
// Purpose:     Erase wxWindows sample
// Author:      Robert Roebling
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "erase.cpp"
    #pragma interface "erase.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};


class MyCanvas : public wxScrolledWindow
{
public:
    MyCanvas( MyFrame *parent );
    
    void OnPaint( wxPaintEvent &event );
    void OnEraseBackground( wxEraseEvent &event );

private:
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

enum
{
    // menu items
    Minimal_Quit = 1,
    Minimal_About
};


// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Minimal wxWindows App",
                                 wxPoint(50, 50), wxSize(450, 340));

    frame->Show(TRUE);
    
    return TRUE;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
#ifdef __WXMAC__
    wxApp::s_macAboutMenuItemId = Minimal_About;
#endif

    SetIcon(wxICON(mondrian));

    wxMenu *menuFile = new wxMenu("", wxMENU_TEAROFF);

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About...\tCtrl-A", "Show about dialog");

    menuFile->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWindows!");
#endif // wxUSE_STATUSBAR

    (void)new MyCanvas( this );
}


void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the about dialog of tghe Erase sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, "About Erase", wxOK | wxICON_INFORMATION, this);
}


BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT(  MyCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(  MyCanvas::OnEraseBackground)
END_EVENT_TABLE()

MyCanvas::MyCanvas( MyFrame *parent )
 : wxScrolledWindow( parent, -1, wxDefaultPosition, wxDefaultSize, 
                    wxScrolledWindowStyle|wxNO_FULL_REPAINT_ON_RESIZE )
{
    SetScrollbars( 10, 10, 40, 100, 0, 0 );
}

void MyCanvas::OnPaint( wxPaintEvent &event )
{
    wxPaintDC dc(this);
    PrepareDC( dc );
    
    dc.SetBrush( *wxRED_BRUSH );
    dc.DrawRectangle( 100, 100, 300, 500 );
}

void MyCanvas::OnEraseBackground( wxEraseEvent &event )
{
    event.Skip( TRUE );
}

