/////////////////////////////////////////////////////////////////////////////
// Name:        palmos/spinctrl.cpp
// Purpose:     wxSpinCtrl class implementation for Palm OS
// Author:      William Osborne
// Modified by:
// Created:     10/13/04
// RCS-ID:      $Id: 
// Copyright:   (c) William Osborne
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "spinctrlbase.h"
    #pragma implementation "spinctrl.h"
#endif

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if wxUSE_SPINCTRL

#if defined(__WIN95__)

#include "wx/spinctrl.h"
#include "wx/palmos/private.h"

// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

#if wxUSE_EXTENDED_RTTI
WX_DEFINE_FLAGS( wxSpinCtrlStyle )

wxBEGIN_FLAGS( wxSpinCtrlStyle )
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

    wxFLAGS_MEMBER(wxSP_HORIZONTAL)
    wxFLAGS_MEMBER(wxSP_VERTICAL)
    wxFLAGS_MEMBER(wxSP_ARROW_KEYS)
    wxFLAGS_MEMBER(wxSP_WRAP)

wxEND_FLAGS( wxSpinCtrlStyle )

IMPLEMENT_DYNAMIC_CLASS_XTI(wxSpinCtrl, wxControl,"wx/spinbut.h")

wxBEGIN_PROPERTIES_TABLE(wxSpinCtrl)
    wxEVENT_RANGE_PROPERTY( Spin , wxEVT_SCROLL_TOP , wxEVT_SCROLL_ENDSCROLL , wxSpinEvent )
    wxEVENT_PROPERTY( Updated , wxEVT_COMMAND_SPINCTRL_UPDATED , wxCommandEvent )
    wxEVENT_PROPERTY( TextUpdated , wxEVT_COMMAND_TEXT_UPDATED , wxCommandEvent ) 
    wxEVENT_PROPERTY( TextEnter , wxEVT_COMMAND_TEXT_ENTER , wxCommandEvent )

    wxPROPERTY( ValueString , wxString , SetValue , GetValue , EMPTY_MACROVALUE , 0 /*flags*/ , wxT("Helpstring") , wxT("group")) ;
    wxPROPERTY( Value , int , SetValue, GetValue, 0 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY( Min , int , SetMin, GetMin, 0, 0 /*flags*/ , wxT("Helpstring") , wxT("group") )
    wxPROPERTY( Max , int , SetMax, GetMax, 0 , 0 /*flags*/ , wxT("Helpstring") , wxT("group"))
    wxPROPERTY_FLAGS( WindowStyle , wxSpinCtrlStyle , long , SetWindowStyleFlag , GetWindowStyleFlag , EMPTY_MACROVALUE , 0 /*flags*/ , wxT("Helpstring") , wxT("group")) // style
/*
    TODO PROPERTIES
        style wxSP_ARROW_KEYS
*/
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(wxSpinCtrl)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_6( wxSpinCtrl , wxWindow* , Parent , wxWindowID , Id , wxString , ValueString , wxPoint , Position , wxSize , Size , long , WindowStyle ) 
#else
IMPLEMENT_DYNAMIC_CLASS(wxSpinCtrl, wxControl)
#endif

BEGIN_EVENT_TABLE(wxSpinCtrl, wxSpinButton)
    EVT_CHAR(wxSpinCtrl::OnChar)

    EVT_SET_FOCUS(wxSpinCtrl::OnSetFocus)

    EVT_SPIN(-1, wxSpinCtrl::OnSpinChange)
END_EVENT_TABLE()

#define GetBuddyHwnd()      (HWND)(m_hwndBuddy)

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// the margin between the up-down control and its buddy (can be arbitrary,
// choose what you like - or may be decide during run-time depending on the
// font size?)
static const int MARGIN_BETWEEN = 1;

// ============================================================================
// implementation
// ============================================================================

wxArraySpins wxSpinCtrl::ms_allSpins;

/* static */
wxSpinCtrl *wxSpinCtrl::GetSpinForTextCtrl(WXHWND hwndBuddy)
{
    return NULL;
}

// process a WM_COMMAND generated by the buddy text control
bool wxSpinCtrl::ProcessTextCommand(WXWORD cmd, WXWORD WXUNUSED(id))
{
    return false;
}

void wxSpinCtrl::OnChar(wxKeyEvent& event)
{
}

void wxSpinCtrl::OnSetFocus(wxFocusEvent& event)
{
}

// ----------------------------------------------------------------------------
// construction
// ----------------------------------------------------------------------------

bool wxSpinCtrl::Create(wxWindow *parent,
                        wxWindowID id,
                        const wxString& value,
                        const wxPoint& pos,
                        const wxSize& size,
                        long style,
                        int min, int max, int initial,
                        const wxString& name)
{
    return false;
}

wxSpinCtrl::~wxSpinCtrl()
{
}

// ----------------------------------------------------------------------------
// wxTextCtrl-like methods
// ----------------------------------------------------------------------------

void wxSpinCtrl::SetValue(const wxString& text)
{
}

int wxSpinCtrl::GetValue() const
{
    return 0;
}

void wxSpinCtrl::SetSelection(long from, long to)
{
}

// ----------------------------------------------------------------------------
// forward some methods to subcontrols
// ----------------------------------------------------------------------------

bool wxSpinCtrl::SetFont(const wxFont& font)
{
    return false;
}

bool wxSpinCtrl::Show(bool show)
{
    return false;
}

bool wxSpinCtrl::Enable(bool enable)
{
    return false;
}

void wxSpinCtrl::SetFocus()
{
}

// ----------------------------------------------------------------------------
// event processing
// ----------------------------------------------------------------------------

void wxSpinCtrl::OnSpinChange(wxSpinEvent& eventSpin)
{
}

// ----------------------------------------------------------------------------
// size calculations
// ----------------------------------------------------------------------------

wxSize wxSpinCtrl::DoGetBestSize() const
{
    return wxSize(0,0);
}

void wxSpinCtrl::DoMoveWindow(int x, int y, int width, int height)
{
}

// get total size of the control
void wxSpinCtrl::DoGetSize(int *x, int *y) const
{
}

void wxSpinCtrl::DoGetPosition(int *x, int *y) const
{
}

#endif // __WIN95__

#endif
       // wxUSE_SPINCTRL

