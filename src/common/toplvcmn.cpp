/////////////////////////////////////////////////////////////////////////////
// Name:        common/toplvcmn.cpp
// Purpose:     common (for all platforms) wxTopLevelWindow functions
// Author:      Julian Smart, Vadim Zeitlin
// Created:     01/02/97
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling, Julian Smart and Markus Holzem
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "toplevelbase.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/toplevel.h"
    #include "wx/dcclient.h"
#endif // WX_PRECOMP

// ----------------------------------------------------------------------------
// event table
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(wxTopLevelWindowBase, wxWindow)
    EVT_CLOSE(wxTopLevelWindowBase::OnCloseWindow)
    EVT_SIZE(wxTopLevelWindowBase::OnSize)
END_EVENT_TABLE()

// ============================================================================
// implementation
// ============================================================================

// FIXME: some platforms don't have wxTopLevelWindow yet
#ifdef wxTopLevelWindowNative
    IMPLEMENT_DYNAMIC_CLASS(wxTopLevelWindow, wxWindow)
#endif

// ----------------------------------------------------------------------------
// construction/destruction
// ----------------------------------------------------------------------------

wxTopLevelWindowBase::wxTopLevelWindowBase()
{
}

wxTopLevelWindowBase::~wxTopLevelWindowBase()
{
    // this destructor is required for Darwin
}

bool wxTopLevelWindowBase::Destroy()
{
    // delayed destruction: the frame will be deleted during the next idle
    // loop iteration
    if ( !wxPendingDelete.Member(this) )
        wxPendingDelete.Append(this);

    return TRUE;
}

// ----------------------------------------------------------------------------
// wxTopLevelWindow size management: we exclude the areas taken by
// menu/status/toolbars from the client area, so the client area is what's
// really available for the frame contents
// ----------------------------------------------------------------------------

void wxTopLevelWindowBase::DoScreenToClient(int *x, int *y) const
{
    wxWindow::DoScreenToClient(x, y);

    // translate the wxWindow client coords to our client coords
    wxPoint pt(GetClientAreaOrigin());
    if ( x )
        *x -= pt.x;
    if ( y )
        *y -= pt.y;
}

void wxTopLevelWindowBase::DoClientToScreen(int *x, int *y) const
{
    // our client area origin (0, 0) may be really something like (0, 30) for
    // wxWindow if we have a toolbar, account for it before translating
    wxPoint pt(GetClientAreaOrigin());
    if ( x )
        *x += pt.x;
    if ( y )
        *y += pt.y;

    wxWindow::DoClientToScreen(x, y);
}


// ----------------------------------------------------------------------------
// event handlers
// ----------------------------------------------------------------------------

// default resizing behaviour - if only ONE subwindow, resize to fill the
// whole client area
void wxTopLevelWindowBase::OnSize(wxSizeEvent& WXUNUSED(event))
{
    // if we're using constraints - do use them
#if wxUSE_CONSTRAINTS
    if ( GetAutoLayout() )
    {
        Layout();
    }
    else
#endif // wxUSE_CONSTRAINTS
    {
        // do we have _exactly_ one child?
        wxWindow *child = (wxWindow *)NULL;
        for ( wxWindowList::Node *node = GetChildren().GetFirst();
              node;
              node = node->GetNext() )
        {
            wxWindow *win = node->GetData();

            // exclude top level and managed windows (status bar isn't
            // currently in the children list except under wxMac anyhow, but
            // it makes no harm to test for it)
            if ( !win->IsTopLevel() && !IsOneOfBars(win) )
            {
                if ( child )
                {
                    return;     // it's our second subwindow - nothing to do
                }

                child = win;
            }
        }

        // do we have any children at all?
        if ( child )
        {
            // exactly one child - set it's size to fill the whole frame
            int clientW, clientH;
            DoGetClientSize(&clientW, &clientH);

            // for whatever reasons, wxGTK wants to have a small offset - it
            // probably looks better with it?
#ifdef __WXGTK__
            static const int ofs = 1;
#else
            static const int ofs = 0;
#endif

            child->SetSize(ofs, ofs, clientW - 2*ofs, clientH - 2*ofs);
        }
    }
}

// The default implementation for the close window event.
void wxTopLevelWindowBase::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}

bool wxTopLevelWindowBase::SendIconizeEvent(bool iconized)
{
    wxIconizeEvent event(GetId(), iconized);
    event.SetEventObject(this);

    return GetEventHandler()->ProcessEvent(event);
}
