/////////////////////////////////////////////////////////////////////////////
// Name:        valtext.cpp
// Purpose:     wxTextValidator
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "valtext.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#if wxUSE_VALIDATORS && wxUSE_TEXTCTRL

#ifndef WX_PRECOMP
  #include <stdio.h>
  #include "wx/textctrl.h"
  #include "wx/utils.h"
  #include "wx/msgdlg.h"
  #include "wx/intl.h"
#endif

#include "wx/valtext.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#ifdef __SALFORDC__
    #include <clib.h>
#endif

IMPLEMENT_DYNAMIC_CLASS(wxTextValidator, wxValidator)

BEGIN_EVENT_TABLE(wxTextValidator, wxValidator)
    EVT_CHAR(wxTextValidator::OnChar)
END_EVENT_TABLE()

static bool wxIsNumeric(const wxString& val);

wxTextValidator::wxTextValidator(long style, wxString *val)
{
    m_validatorStyle = style;
    m_stringValue = val;
/*
    m_refData = new wxVTextRefData;

    M_VTEXTDATA->m_validatorStyle = style;
    M_VTEXTDATA->m_stringValue = val;
*/
}

wxTextValidator::wxTextValidator(const wxTextValidator& val)
    : wxValidator()
{
    Copy(val);
}

bool wxTextValidator::Copy(const wxTextValidator& val)
{
    wxValidator::Copy(val);

    m_validatorStyle = val.m_validatorStyle;
    m_stringValue = val.m_stringValue;

    m_includeList = val.m_includeList;
    m_excludeList = val.m_excludeList;

    return true;
}

wxTextValidator::~wxTextValidator()
{
}

static bool wxIsAlpha(const wxString& val)
{
    int i;
    for ( i = 0; i < (int)val.Length(); i++)
    {
        if (!wxIsalpha(val[i]))
            return false;
    }
    return true;
}

static bool wxIsAlphaNumeric(const wxString& val)
{
    int i;
    for ( i = 0; i < (int)val.Length(); i++)
    {
        if (!wxIsalnum(val[i]))
            return false;
    }
    return true;
}

// Called when the value in the window must be validated.
// This function can pop up an error message.
bool wxTextValidator::Validate(wxWindow *parent)
{
    if( !CheckValidator() )
        return false;

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;

    // If window is disabled, simply return
    if ( !control->IsEnabled() )
        return true;

    wxString val(control->GetValue());

    bool ok = true;

    // NB: this format string should contian exactly one '%s'
    wxString errormsg;

    bool includeList = (m_validatorStyle & wxFILTER_INCLUDE_LIST) != 0;
    if ( includeList || (m_validatorStyle & wxFILTER_EXCLUDE_LIST) )
    {
        // if includeList, it's only ok to have the members of the list,
        // otherwise it's only ok to have non-members
        ok = includeList == m_includeList.Member(val);
        if ( !ok )
        {
            errormsg = _("'%s' is invalid");
        }
    }
    else if ( (m_validatorStyle & wxFILTER_ASCII) && !val.IsAscii() )
    {
        ok = false;

        errormsg = _("'%s' should only contain ASCII characters.");
    }
    else if ( (m_validatorStyle & wxFILTER_ALPHA) && !wxIsAlpha(val) )
    {
        ok = false;

        errormsg = _("'%s' should only contain alphabetic characters.");
    }
    else if ( (m_validatorStyle & wxFILTER_ALPHANUMERIC) && !wxIsAlphaNumeric(val))
    {
        ok = false;

        errormsg = _("'%s' should only contain alphabetic or numeric characters.");
    }
    else if ( (m_validatorStyle & wxFILTER_NUMERIC) && !wxIsNumeric(val))
    {
        ok = false;

        errormsg = _("'%s' should be numeric.");
    }
    else if ( (m_validatorStyle & wxFILTER_INCLUDE_CHAR_LIST) && !IsInCharIncludeList(val))
    {
        //it's only ok to have the members of the list
        errormsg = _("'%s' is invalid");
        ok = false;
    }
    else if ( (m_validatorStyle & wxFILTER_EXCLUDE_CHAR_LIST) && !IsNotInCharExcludeList(val))
    {
        // it's only ok to have non-members of the list
        errormsg = _("'%s' is invalid");
        ok = false;
    }

    if ( !ok )
    {
        wxASSERT_MSG( !errormsg.empty(), _T("you forgot to set errormsg") );

        m_validatorWindow->SetFocus();

        wxString buf;
        buf.Printf(errormsg, val.c_str());

        wxMessageBox(buf, _("Validation conflict"),
                     wxOK | wxICON_EXCLAMATION, parent);
    }

    return ok;
}

// Called to transfer data to the window
bool wxTextValidator::TransferToWindow(void)
{
    if( !CheckValidator() )
        return false;

    if ( m_stringValue )
    {
        wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
        control->SetValue(* m_stringValue);
    }

    return true;
}

// Called to transfer data to the window
bool wxTextValidator::TransferFromWindow(void)
{
    if( !CheckValidator() )
        return false;

    if ( m_stringValue )
    {
        wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
        *m_stringValue = control->GetValue();
    }

    return true;
}

void wxTextValidator::SetIncludeList(const wxStringList& list)
{
    m_includeList = list;
}

void wxTextValidator::SetExcludeList(const wxStringList& list)
{
    m_excludeList = list;
}

void wxTextValidator::OnChar(wxKeyEvent& event)
{
/*
    if ( !M_VTEXTDATA )
        return;
*/

    if ( m_validatorWindow )
    {
        int keyCode = event.GetKeyCode();

        // we don't filter special keys and Delete
        if (
             !(keyCode < WXK_SPACE || keyCode == WXK_DELETE || keyCode > WXK_START) &&
             (
              ((m_validatorStyle & wxFILTER_INCLUDE_CHAR_LIST) && !IsInCharIncludeList(wxString((wxChar) keyCode, 1))) ||
              ((m_validatorStyle & wxFILTER_EXCLUDE_CHAR_LIST) && !IsNotInCharExcludeList(wxString((wxChar) keyCode, 1))) ||
              ((m_validatorStyle & wxFILTER_ASCII) && !isascii(keyCode)) ||
              ((m_validatorStyle & wxFILTER_ALPHA) && !wxIsalpha(keyCode)) ||
              ((m_validatorStyle & wxFILTER_ALPHANUMERIC) && !wxIsalnum(keyCode)) ||
              ((m_validatorStyle & wxFILTER_NUMERIC) && !wxIsdigit(keyCode)
                                && keyCode != '.' && keyCode != ',' && keyCode != '-')
             )
           )
        {
            if ( !wxValidator::IsSilent() )
                wxBell();

            // eat message
            return;
        }
    }

    event.Skip();
}

static bool wxIsNumeric(const wxString& val)
{
    int i;
    for ( i = 0; i < (int)val.Length(); i++)
    {
        // Allow for "," (French) as well as "." -- in future we should
        // use wxSystemSettings or other to do better localisation
        if ((!wxIsdigit(val[i])) && (val[i] != '.') && (val[i] != ',') && (val[i] != wxT('e')) && (val[i] != wxT('E')) && (val[i] != wxT('+')) && (val[i] != wxT('-')))
            return false;
    }
    return true;
}

bool wxTextValidator::IsInCharIncludeList(const wxString& val)
{
    size_t i;
    for ( i = 0; i < val.Length(); i++)
    {
        if (!m_includeList.Member((wxString) val[i]))
            return false;
    }
    return true;
}

bool wxTextValidator::IsNotInCharExcludeList(const wxString& val)
{
    size_t i;
    for ( i = 0; i < val.Length(); i++)
    {
       if (m_excludeList.Member((wxString) val[i]))
       return false;
    }
    return true;
}

#endif
  // wxUSE_VALIDATORS && wxUSE_TEXTCTRL
