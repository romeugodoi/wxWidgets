/////////////////////////////////////////////////////////////////////////////
// Name:        control.cpp
// Purpose:
// Author:      Robert Roebling
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling, Julian Smart and Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "control.h"
#endif

#include "wx/control.h"

#include "gtk/gtkfeatures.h"

//-----------------------------------------------------------------------------
// wxControl
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxControl,wxWindow)

wxControl::wxControl()
{
    m_needParent = TRUE;
}

wxControl::wxControl( wxWindow *parent,
                      wxWindowID id,
                      const wxPoint &pos,
                      const wxSize &size,
                      long style,
                      const wxString &name )
         : wxWindow( parent, id, pos, size, style, name )
{
}

void wxControl::Command( wxCommandEvent &WXUNUSED(event) )
{
}

void wxControl::SetLabel( const wxString &label )
{
    m_label = _T("");
    for ( const wxChar *pc = label; *pc != _T('\0'); pc++ )
    {
        if ( *pc == _T('&') )
        {
            pc++; // skip it
#if 0 // it would be unused anyhow for now - kbd interface not done yet
            if ( *pc != _T('&') ) m_chAccel = *pc;
#endif
        }
        m_label << *pc;
    }
}

wxString wxControl::GetLabel(void) const
{
    return m_label;
}


