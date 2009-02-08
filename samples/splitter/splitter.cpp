/////////////////////////////////////////////////////////////////////////////
// Name:        splitter.cpp
// Purpose:     wxSplitterWindow sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/log.h"

    #include "wx/app.h"
    #include "wx/frame.h"

    #include "wx/scrolwin.h"
    #include "wx/menu.h"

    #include "wx/textdlg.h"       // for wxGetTextFromUser
#endif

#include "wx/splitter.h"
#include "wx/dcmirror.h"

#ifndef __WXMSW__
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// ID for the menu commands
enum
{
    SPLIT_QUIT = 1,
    SPLIT_HORIZONTAL,
    SPLIT_VERTICAL,
    SPLIT_UNSPLIT,
    SPLIT_LIVE,
    SPLIT_BORDER,
    SPLIT_3DSASH,
    SPLIT_SETPOSITION,
    SPLIT_SETMINSIZE,
    SPLIT_SETGRAVITY,
    SPLIT_REPLACE
};

// ----------------------------------------------------------------------------
// our classes
// ----------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    MyApp() { }

    virtual bool OnInit();

    wxDECLARE_NO_COPY_CLASS(MyApp);
};

class MyFrame: public wxFrame
{
public:
    MyFrame();
    virtual ~MyFrame();

    void ToggleFlag(int flag, bool enable);

    // Menu commands
    void OnSplitHorizontal(wxCommandEvent& event);
    void OnSplitVertical(wxCommandEvent& event);
    void OnUnsplit(wxCommandEvent& event);
    void OnToggleLive(wxCommandEvent& event)
                  { ToggleFlag(wxSP_LIVE_UPDATE, event.IsChecked()); }
    void OnToggleBorder(wxCommandEvent& event)
                  { ToggleFlag(wxSP_BORDER, event.IsChecked()); }
    void OnToggle3DSash(wxCommandEvent& event)
                  { ToggleFlag(wxSP_3DSASH, event.IsChecked()); }
    void OnSetPosition(wxCommandEvent& event);
    void OnSetMinSize(wxCommandEvent& event);
    void OnSetGravity(wxCommandEvent& event);
    void OnReplace(wxCommandEvent &event);

    void OnQuit(wxCommandEvent& event);

    // Menu command update functions
    void OnUpdateUIHorizontal(wxUpdateUIEvent& event);
    void OnUpdateUIVertical(wxUpdateUIEvent& event);
    void OnUpdateUIUnsplit(wxUpdateUIEvent& event);

private:
    wxScrolledWindow *m_left, *m_right;

    wxSplitterWindow* m_splitter;
    wxWindow *m_replacewindow;

    DECLARE_EVENT_TABLE()
    wxDECLARE_NO_COPY_CLASS(MyFrame);
};

class MySplitterWindow : public wxSplitterWindow
{
public:
    MySplitterWindow(wxFrame *parent);

    // event handlers
    void OnPositionChanged(wxSplitterEvent& event);
    void OnPositionChanging(wxSplitterEvent& event);
    void OnDClick(wxSplitterEvent& event);
    void OnUnsplitEvent(wxSplitterEvent& event);

private:
    wxFrame *m_frame;

    DECLARE_EVENT_TABLE()
    wxDECLARE_NO_COPY_CLASS(MySplitterWindow);
};

class MyCanvas: public wxScrolledWindow
{
public:
    MyCanvas(wxWindow* parent, bool mirror);
    virtual ~MyCanvas(){};

    virtual void OnDraw(wxDC& dc);

private:
    bool m_mirror;

    wxDECLARE_NO_COPY_CLASS(MyCanvas);
};

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // create and show the main frame
    MyFrame* frame = new MyFrame;

    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(SPLIT_VERTICAL, MyFrame::OnSplitVertical)
    EVT_MENU(SPLIT_HORIZONTAL, MyFrame::OnSplitHorizontal)
    EVT_MENU(SPLIT_UNSPLIT, MyFrame::OnUnsplit)
    EVT_MENU(SPLIT_LIVE, MyFrame::OnToggleLive)
    EVT_MENU(SPLIT_BORDER, MyFrame::OnToggleBorder)
    EVT_MENU(SPLIT_3DSASH, MyFrame::OnToggle3DSash)
    EVT_MENU(SPLIT_SETPOSITION, MyFrame::OnSetPosition)
    EVT_MENU(SPLIT_SETMINSIZE, MyFrame::OnSetMinSize)
    EVT_MENU(SPLIT_SETGRAVITY, MyFrame::OnSetGravity)
    EVT_MENU(SPLIT_REPLACE, MyFrame::OnReplace)

    EVT_MENU(SPLIT_QUIT, MyFrame::OnQuit)

    EVT_UPDATE_UI(SPLIT_VERTICAL, MyFrame::OnUpdateUIVertical)
    EVT_UPDATE_UI(SPLIT_HORIZONTAL, MyFrame::OnUpdateUIHorizontal)
    EVT_UPDATE_UI(SPLIT_UNSPLIT, MyFrame::OnUpdateUIUnsplit)
END_EVENT_TABLE()

// My frame constructor
MyFrame::MyFrame()
       : wxFrame(NULL, wxID_ANY, _T("wxSplitterWindow sample"),
                 wxDefaultPosition, wxSize(420, 300),
                 wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
    SetIcon(wxICON(sample));

#if wxUSE_STATUSBAR
    CreateStatusBar(2);
#endif // wxUSE_STATUSBAR

    // Make a menubar
    wxMenu *splitMenu = new wxMenu;
    splitMenu->Append(SPLIT_VERTICAL,
                      _T("Split &Vertically\tCtrl-V"),
                      _T("Split vertically"));
    splitMenu->Append(SPLIT_HORIZONTAL,
                      _T("Split &Horizontally\tCtrl-H"),
                      _T("Split horizontally"));
    splitMenu->Append(SPLIT_UNSPLIT,
                      _T("&Unsplit\tCtrl-U"),
                      _T("Unsplit"));
    splitMenu->AppendSeparator();

    splitMenu->AppendCheckItem(SPLIT_LIVE,
                               _T("&Live update\tCtrl-L"),
                               _T("Toggle live update mode"));
    splitMenu->AppendCheckItem(SPLIT_BORDER,
                               _T("3D &Border"),
                               _T("Toggle wxSP_BORDER flag"));
    splitMenu->Check(SPLIT_BORDER, true);
    splitMenu->AppendCheckItem(SPLIT_3DSASH,
                               _T("&3D Sash"),
                               _T("Toggle wxSP_3DSASH flag"));
    splitMenu->Check(SPLIT_3DSASH, true);
    splitMenu->Append(SPLIT_SETPOSITION,
                      _T("Set splitter &position\tCtrl-P"),
                      _T("Set the splitter position"));
    splitMenu->Append(SPLIT_SETMINSIZE,
                      _T("Set &min size\tCtrl-M"),
                      _T("Set minimum pane size"));
    splitMenu->Append(SPLIT_SETGRAVITY,
                      _T("Set &gravity\tCtrl-G"),
                      _T("Set gravity of sash"));
    splitMenu->AppendSeparator();

    splitMenu->Append(SPLIT_REPLACE,
                      _T("&Replace right window"),
                      _T("Replace right window"));
    splitMenu->AppendSeparator();

    splitMenu->Append(SPLIT_QUIT, _T("E&xit\tAlt-X"), _T("Exit"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(splitMenu, _T("&Splitter"));

    SetMenuBar(menuBar);

    menuBar->Check(SPLIT_LIVE, true);
    m_splitter = new MySplitterWindow(this);

    m_splitter->SetSashGravity(1.0);

#if 1
    m_left = new MyCanvas(m_splitter, true);
    m_left->SetBackgroundColour(*wxRED);
    m_left->SetScrollbars(20, 20, 5, 5);
    m_left->SetCursor(wxCursor(wxCURSOR_MAGNIFIER));

    m_right = new MyCanvas(m_splitter, false);
    m_right->SetBackgroundColour(*wxCYAN);
    m_right->SetScrollbars(20, 20, 5, 5);
#else // for testing kbd navigation inside the splitter
    m_left = new wxTextCtrl(m_splitter, wxID_ANY, _T("first text"));
    m_right = new wxTextCtrl(m_splitter, wxID_ANY, _T("second text"));
#endif

    // you can also do this to start with a single window
#if 0
    m_right->Show(false);
    m_splitter->Initialize(m_left);
#else
    // you can also try -100
    m_splitter->SplitVertically(m_left, m_right, 100);
#endif

#if wxUSE_STATUSBAR
    SetStatusText(_T("Min pane size = 0"), 1);
#endif // wxUSE_STATUSBAR

    m_replacewindow = (wxWindow *)0;
}

MyFrame::~MyFrame()
{
    if (m_replacewindow) {
        m_replacewindow->Destroy();
        m_replacewindow = (wxWindow *)0;
    }
}

// menu command handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}

void MyFrame::OnSplitHorizontal(wxCommandEvent& WXUNUSED(event) )
{
    if ( m_splitter->IsSplit() )
        m_splitter->Unsplit();
    m_left->Show(true);
    m_right->Show(true);
    m_splitter->SplitHorizontally( m_left, m_right );

#if wxUSE_STATUSBAR
    SetStatusText(_T("Splitter split horizontally"), 1);
#endif // wxUSE_STATUSBAR
}

void MyFrame::OnSplitVertical(wxCommandEvent& WXUNUSED(event) )
{
    if ( m_splitter->IsSplit() )
        m_splitter->Unsplit();
    m_left->Show(true);
    m_right->Show(true);
    m_splitter->SplitVertically( m_left, m_right );

#if wxUSE_STATUSBAR
    SetStatusText(_T("Splitter split vertically"), 1);
#endif // wxUSE_STATUSBAR
}

void MyFrame::OnUnsplit(wxCommandEvent& WXUNUSED(event) )
{
    if ( m_splitter->IsSplit() )
        m_splitter->Unsplit();
#if wxUSE_STATUSBAR
    SetStatusText(_T("No splitter"));
#endif // wxUSE_STATUSBAR
}

void MyFrame::ToggleFlag(int flag, bool enable)
{
    long style = m_splitter->GetWindowStyleFlag();
    if ( enable )
        style |= flag;
    else
        style &= ~flag;

    m_splitter->SetWindowStyleFlag(style);

    // we need to move sash to redraw it
    int pos = m_splitter->GetSashPosition();
    m_splitter->SetSashPosition(pos + 1);
    m_splitter->SetSashPosition(pos);
}

void MyFrame::OnSetPosition(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%d"), m_splitter->GetSashPosition());
#if wxUSE_TEXTDLG
    str = wxGetTextFromUser(_T("Enter splitter position:"), _T(""), str, this);
#endif
    if ( str.empty() )
        return;

    long pos;
    if ( !str.ToLong(&pos) )
    {
        wxLogError(_T("The splitter position should be an integer."));
        return;
    }

    m_splitter->SetSashPosition(pos);

    wxLogStatus(this, _T("Splitter position set to %ld"), pos);
}

void MyFrame::OnSetMinSize(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%d"), m_splitter->GetMinimumPaneSize());
#if wxUSE_TEXTDLG
    str = wxGetTextFromUser(_T("Enter minimal size for panes:"), _T(""), str, this);
#endif
    if ( str.empty() )
        return;

    int minsize = wxStrtol( str, (wxChar**)NULL, 10 );
    m_splitter->SetMinimumPaneSize(minsize);
#if wxUSE_STATUSBAR
    str.Printf( wxT("Min pane size = %d"), minsize);
    SetStatusText(str, 1);
#endif // wxUSE_STATUSBAR
}

void MyFrame::OnSetGravity(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%g"), m_splitter->GetSashGravity());
#if wxUSE_TEXTDLG
    str = wxGetTextFromUser(_T("Enter sash gravity (0,1):"), _T(""), str, this);
#endif
    if ( str.empty() )
        return;

    double gravity = wxStrtod( str, (wxChar**)NULL);
    m_splitter->SetSashGravity(gravity);
#if wxUSE_STATUSBAR
    str.Printf( wxT("Gravity = %g"), gravity);
    SetStatusText(str, 1);
#endif // wxUSE_STATUSBAR
}

void MyFrame::OnReplace(wxCommandEvent& WXUNUSED(event) )
{
    if (m_replacewindow == 0) {
        m_replacewindow = m_splitter->GetWindow2();
        m_splitter->ReplaceWindow(m_replacewindow, new wxPanel(m_splitter, wxID_ANY));
        m_replacewindow->Hide();
    } else {
        wxWindow *empty = m_splitter->GetWindow2();
        m_splitter->ReplaceWindow(empty, m_replacewindow);
        m_replacewindow->Show();
        m_replacewindow = 0;
        empty->Destroy();
    }
}

// Update UI handlers

void MyFrame::OnUpdateUIHorizontal(wxUpdateUIEvent& event)
{
    event.Enable( (!m_splitter->IsSplit()) || (m_splitter->GetSplitMode() != wxSPLIT_HORIZONTAL) );
}

void MyFrame::OnUpdateUIVertical(wxUpdateUIEvent& event)
{
    event.Enable( ( (!m_splitter->IsSplit()) || (m_splitter->GetSplitMode() != wxSPLIT_VERTICAL) ) );
}

void MyFrame::OnUpdateUIUnsplit(wxUpdateUIEvent& event)
{
    event.Enable( m_splitter->IsSplit() );
}

// ----------------------------------------------------------------------------
// MySplitterWindow
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MySplitterWindow, wxSplitterWindow)
    EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, MySplitterWindow::OnPositionChanged)
    EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, MySplitterWindow::OnPositionChanging)

    EVT_SPLITTER_DCLICK(wxID_ANY, MySplitterWindow::OnDClick)

    EVT_SPLITTER_UNSPLIT(wxID_ANY, MySplitterWindow::OnUnsplitEvent)
END_EVENT_TABLE()

MySplitterWindow::MySplitterWindow(wxFrame *parent)
                : wxSplitterWindow(parent, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxSP_LIVE_UPDATE |
                                   wxCLIP_CHILDREN /* | wxSP_NO_XP_THEME */ )
{
    m_frame = parent;
}

void MySplitterWindow::OnPositionChanged(wxSplitterEvent& event)
{
    wxLogStatus(m_frame, _T("Position has changed, now = %d (or %d)"),
                event.GetSashPosition(), GetSashPosition());

    event.Skip();
}

void MySplitterWindow::OnPositionChanging(wxSplitterEvent& event)
{
    wxLogStatus(m_frame, _T("Position is changing, now = %d (or %d)"),
                event.GetSashPosition(), GetSashPosition());

    event.Skip();
}

void MySplitterWindow::OnDClick(wxSplitterEvent& event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText(_T("Splitter double clicked"), 1);
#endif // wxUSE_STATUSBAR

    event.Skip();
}

void MySplitterWindow::OnUnsplitEvent(wxSplitterEvent& event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText(_T("Splitter unsplit"), 1);
#endif // wxUSE_STATUSBAR

    event.Skip();
}

// ----------------------------------------------------------------------------
// MyCanvas
// ----------------------------------------------------------------------------

MyCanvas::MyCanvas(wxWindow* parent, bool mirror)
        : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    m_mirror = mirror;
}

void MyCanvas::OnDraw(wxDC& dcOrig)
{
    wxMirrorDC dc(dcOrig, m_mirror);

    dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(0, 0, 100, 200);

    dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
    dc.DrawText(_T("Testing"), 50, 50);

    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(120, 120, 100, 80);
}

