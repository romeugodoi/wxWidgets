/////////////////////////////////////////////////////////////////////////////
// Name:        panelg.cpp
// Purpose:     wxPanel
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:           wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "panelg.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/object.h"
#include "wx/font.h"
#include "wx/colour.h"
#include "wx/settings.h"
#endif

#include "wx/generic/panelg.h"

#if !USE_SHARED_LIBRARY
IMPLEMENT_DYNAMIC_CLASS(wxPanel, wxWindow)

BEGIN_EVENT_TABLE(wxPanel, wxWindow)
  EVT_SYS_COLOUR_CHANGED(wxPanel::OnSysColourChanged)
  EVT_SET_FOCUS(wxPanel::OnFocus)
  EVT_NAVIGATION_KEY(wxPanel::OnNavigationKey)
END_EVENT_TABLE()

#endif

wxPanel::wxPanel()
{
    m_lastFocus = NULL;
}

bool wxPanel::Create(wxWindow *parent, wxWindowID id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name)
{
    m_lastFocus = NULL;

    bool ret = wxWindow::Create(parent, id, pos, size, style, name);

    if ( ret )
    {
#ifndef __WXGTK__
        SetBackgroundColour(wxSystemSettings::GetSystemColour(wxSYS_COLOUR_3DFACE));
        SetFont(wxSystemSettings::GetSystemFont(wxSYS_DEFAULT_GUI_FONT));
#endif
    }

    return ret;
}

void wxPanel::InitDialog(void)
{
    wxInitDialogEvent event(GetId());
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);
}

// Responds to colour changes, and passes event on to children.
void wxPanel::OnSysColourChanged(wxSysColourChangedEvent& event)
{
    SetBackgroundColour(wxSystemSettings::GetSystemColour(wxSYS_COLOUR_3DFACE));
    Refresh();

    // Propagate the event to the non-top-level children
    wxWindow::OnSysColourChanged(event);
}

void wxPanel::OnNavigationKey( wxNavigationKeyEvent& event )
{
    // there is not much to do if we have only one child (or not at all)
    if (GetChildren().GetCount() < 2)
    {
        event.Skip();
        return;
    }

    // don't process these ones here
    if (event.IsWindowChange())
    {
        event.Skip();
        return;
    }

    wxWindow *winFocus = event.GetCurrentFocus();
    if (!winFocus)
        winFocus = wxWindow::FindFocus();

    if (!winFocus)
    {
        event.Skip();
        return;
    }

    wxNode *start_node = GetChildren().Find( winFocus );
    if (!start_node)
        start_node = GetChildren().First();

    wxNode *node = event.GetDirection() ? start_node->Next()
                                        : start_node->Previous();

    while (node != start_node)
    {
        if (!node)
        {
//#if 0 // FIXME seems to enter in an infinite loop - how is this possible?
            // we arrived at the last/first of our children - but may be this
            // panel is inside another panel, so make focus go to the next/prev
            // control in the parent (if we have one)
            if (GetParent() != NULL)
            {
                wxNavigationKeyEvent new_event;
                new_event.SetDirection( event.GetDirection() );
                new_event.SetWindowChange(FALSE);
                new_event.SetCurrentFocus( this );

                if (GetParent()->GetEventHandler()->ProcessEvent(new_event))
                {
                    return;
                }
            }
//#endif // 0

            node = event.GetDirection() ? GetChildren().First()
                                        : GetChildren().Last();

            continue;
        }

        wxWindow *child = (wxWindow *)node->Data();

        if (child->AcceptsFocus())
        {
            // ok, event processed
            child->SetFocus();
            return;
        }

        node = event.GetDirection() ? node->Next() : node->Previous();
    }

    // we cycled through all of our children and none of them wanted to accept
    // focus
    event.Skip();
}

void wxPanel::OnFocus(wxFocusEvent& event)
{
    if ( m_lastFocus )
        m_lastFocus->SetFocus();
    else
        event.Skip();
}
