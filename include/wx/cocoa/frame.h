/////////////////////////////////////////////////////////////////////////////
// Name:        wx/cocoa/frame.h
// Purpose:     wxFrame class
// Author:      David Elliott
// Modified by:
// Created:     2003/03/16
// RCS-ID:      $Id:
// Copyright:   (c) 2003 David Elliott
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_COCOA_FRAME_H_
#define _WX_COCOA_FRAME_H_

class WXDLLEXPORT wxMenuBar;
class WXDLLEXPORT wxMenuItem;
class WXDLLEXPORT wxStatusBar;

class WXDLLEXPORT wxFrame: public wxFrameBase 
{
    DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(wxFrame)
// ------------------------------------------------------------------------
// initialization
// ------------------------------------------------------------------------
public:
    wxFrame() { Init(); }
    wxFrame(wxWindow *parent,
            wxWindowID winid,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString& name = wxFrameNameStr)
    {
        Init();
        Create(parent, winid, title, pos, size, style, name);
    }

    virtual ~wxFrame();

    bool Create(wxWindow *parent,
                wxWindowID winid,
                const wxString& title,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE,
                const wxString& name = wxFrameNameStr);
protected:
    void Init();
// ------------------------------------------------------------------------
// Cocoa specifics
// ------------------------------------------------------------------------
protected:
    virtual void Cocoa_wxMenuItemAction(wxMenuItem& item);

    // Helper function to position status/tool bars
    void UpdateFrameNSView();

    virtual void CocoaReplaceView(WX_NSView oldView, WX_NSView newView);
    // frameNSView is used whenever a statusbar/generic toolbar are present
    WX_NSView m_frameNSView;
// ------------------------------------------------------------------------
// Implementation
// ------------------------------------------------------------------------
public:
    void AttachMenuBar(wxMenuBar *mbar);
    void DetachMenuBar();

    // implementation only from now on
    // -------------------------------

    // override some more virtuals
    virtual bool Show( bool show = true );

    // get the origin of the client area (which may be different from (0, 0)
    // if the frame has a toolbar) in client coordinates
    virtual wxPoint GetClientAreaOrigin() const;

    // create the main status bar by calling OnCreateStatusBar()
    virtual wxStatusBar* CreateStatusBar(int number = 1,
                                         long style = wxST_SIZEGRIP,
                                         wxWindowID winid = 0,
                                         const wxString& name =
                                            wxStatusLineNameStr);
    // sets the main status bar
    void SetStatusBar(wxStatusBar *statBar);
    // create main toolbar bycalling OnCreateToolBar()
    virtual wxToolBar* CreateToolBar(long style = -1,
                                     wxWindowID winid = -1,
                                     const wxString& name = wxToolBarNameStr);
    // sets the main tool bar
    virtual void SetToolBar(wxToolBar *toolbar);
protected:
    void PositionStatusBar();
    // override base class virtuals
    virtual void DoGetClientSize(int *width, int *height) const;
    virtual void DoSetClientSize(int width, int height);
};

#endif // _WX_COCOA_FRAME_H_
