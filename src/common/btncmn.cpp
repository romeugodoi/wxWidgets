///////////////////////////////////////////////////////////////////////////////
// Name:        src/common/btncmn.cpp
// Purpose:     implementation of wxButtonBase
// Author:      Vadim Zeitlin
// Created:     2007-04-08
// RCS-ID:      $Id$
// Copyright:   (c) 2007 Vadim Zeitlin <vadim@wxwindows.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/button.h"
    #include "wx/toplevel.h"
#endif //WX_PRECOMP


// ----------------------------------------------------------------------------
// XTI
// ----------------------------------------------------------------------------

wxDEFINE_FLAGS( wxButtonStyle )
wxBEGIN_FLAGS( wxButtonStyle )
    // new style border flags, we put them first to
    // use them for streaming out
    wxFLAGS_MEMBER(wxBORDER_SIMPLE)
    wxFLAGS_MEMBER(wxBORDER_SUNKEN)
    wxFLAGS_MEMBER(wxBORDER_DOUBLE)
    wxFLAGS_MEMBER(wxBORDER_RAISED)
    wxFLAGS_MEMBER(wxBORDER_STATIC)
    wxFLAGS_MEMBER(wxBORDER_NONE)

    // old style border flags
    wxFLAGS_MEMBER(wxSIMPLE_BORDER)
    wxFLAGS_MEMBER(wxSUNKEN_BORDER)
    wxFLAGS_MEMBER(wxDOUBLE_BORDER)
    wxFLAGS_MEMBER(wxRAISED_BORDER)
    wxFLAGS_MEMBER(wxSTATIC_BORDER)
    wxFLAGS_MEMBER(wxBORDER)

    // standard window styles
    wxFLAGS_MEMBER(wxTAB_TRAVERSAL)
    wxFLAGS_MEMBER(wxCLIP_CHILDREN)
    wxFLAGS_MEMBER(wxTRANSPARENT_WINDOW)
    wxFLAGS_MEMBER(wxWANTS_CHARS)
    wxFLAGS_MEMBER(wxFULL_REPAINT_ON_RESIZE)
    wxFLAGS_MEMBER(wxALWAYS_SHOW_SB )
    wxFLAGS_MEMBER(wxVSCROLL)
    wxFLAGS_MEMBER(wxHSCROLL)

    wxFLAGS_MEMBER(wxBU_LEFT)
    wxFLAGS_MEMBER(wxBU_RIGHT)
    wxFLAGS_MEMBER(wxBU_TOP)
    wxFLAGS_MEMBER(wxBU_BOTTOM)
    wxFLAGS_MEMBER(wxBU_EXACTFIT)
wxEND_FLAGS( wxButtonStyle )

wxIMPLEMENT_DYNAMIC_CLASS_XTI(wxButton, wxControl, "wx/button.h")

wxBEGIN_PROPERTIES_TABLE(wxButton)
    wxEVENT_PROPERTY( Click, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEvent)

    wxPROPERTY( Font, wxFont, SetFont, GetFont , EMPTY_MACROVALUE, \
                0 /*flags*/, wxT("Helpstring"), wxT("group"))
    wxPROPERTY( Label, wxString, SetLabel, GetLabel, wxString(), \
                0 /*flags*/, wxT("Helpstring"), wxT("group") )

    wxPROPERTY_FLAGS( WindowStyle, wxButtonStyle, long, SetWindowStyleFlag, \
                      GetWindowStyleFlag, EMPTY_MACROVALUE, 0 /*flags*/,     \
                      wxT("Helpstring"), wxT("group")) // style
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(wxButton)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_6( wxButton, wxWindow*, Parent, wxWindowID, Id, wxString, \
                 Label, wxPoint, Position, wxSize, Size, long, WindowStyle )



// ============================================================================
// implementation
// ============================================================================

wxWindow *wxButtonBase::SetDefault()
{
    wxTopLevelWindow * const
        tlw = wxDynamicCast(wxGetTopLevelParent(this), wxTopLevelWindow);

    wxCHECK_MSG( tlw, NULL, _T("button without top level window?") );

    return tlw->SetDefaultItem(this);
}

