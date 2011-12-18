///////////////////////////////////////////////////////////////////////////////
// Name:        src/generic/filepickerg.cpp
// Purpose:     wxGenericFileDirButton class implementation
// Author:      Francesco Montorsi
// Modified by:
// Created:     15/04/2006
// RCS-ID:      $Id$
// Copyright:   (c) Francesco Montorsi
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_FILEPICKERCTRL || wxUSE_DIRPICKERCTRL

#include "wx/filepicker.h"

#include "wx/scopedptr.h"


// ============================================================================
// implementation
// ============================================================================

IMPLEMENT_DYNAMIC_CLASS(wxGenericFileButton, wxButton)
IMPLEMENT_DYNAMIC_CLASS(wxGenericDirButton, wxButton)

// ----------------------------------------------------------------------------
// wxGenericFileButton
// ----------------------------------------------------------------------------

bool wxGenericFileDirButton::Create(wxWindow *parent,
                                    wxWindowID id,
                                    const wxString& label,
                                    const wxString& path,
                                    const wxString& message,
                                    const wxString& wildcard,
                                    const wxPoint& pos,
                                    const wxSize& size,
                                    long style,
                                    const wxValidator& validator,
                                    const wxString& name)
{
    m_pickerStyle = style;

    // If the special wxPB_SMALL flag is used, ignore the provided label and
    // use the shortest possible label and the smallest possible button fitting
    // it.
    long styleButton = 0;
    wxString labelButton;
    if ( m_pickerStyle & wxPB_SMALL )
    {
        labelButton = _("...");
        styleButton = wxBU_EXACTFIT;
    }
    else
    {
        labelButton = label;
    }

    // create this button
    if ( !wxButton::Create(parent, id, labelButton,
                           pos, size, styleButton, validator, name) )
    {
        wxFAIL_MSG( wxT("wxGenericFileButton creation failed") );
        return false;
    }

    // and handle user clicks on it
    Connect(GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(wxGenericFileDirButton::OnButtonClick),
            NULL, this);

    // create the dialog associated with this button
    m_path = path;
    m_message = message;
    m_wildcard = wildcard;

    return true;
}

void wxGenericFileDirButton::OnButtonClick(wxCommandEvent& WXUNUSED(ev))
{
    wxScopedPtr<wxDialog> p(CreateDialog());
    if (p->ShowModal() == wxID_OK)
    {
        // save updated path in m_path
        UpdatePathFromDialog(p.get());

        // fire an event
        wxFileDirPickerEvent event(GetEventType(), this, GetId(), m_path);
        GetEventHandler()->ProcessEvent(event);
    }
}

#endif      // wxUSE_FILEPICKERCTRL || wxUSE_DIRPICKERCTRL
