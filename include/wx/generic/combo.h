/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/combo.h
// Purpose:     Generic wxComboControl
// Author:      Jaakko Salli
// Modified by:
// Created:     Apr-30-2006
// RCS-ID:      $Id$
// Copyright:   (c) Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GENERIC_COMBOCONTROL_H_
#define _WX_GENERIC_COMBOCONTROL_H_

#if wxUSE_COMBOCONTROL

// Only define generic if native doesn't have all the features
#if !defined(wxCOMBOCONTROL_FULLY_FEATURED)

// ----------------------------------------------------------------------------
// Generic wxComboControl
// ----------------------------------------------------------------------------

#if defined(__WXUNIVERSAL__)

// all actions of single line text controls are supported

// popup/dismiss the choice window
#define wxACTION_COMBOBOX_POPUP     _T("popup")
#define wxACTION_COMBOBOX_DISMISS   _T("dismiss")

#endif


class WXDLLEXPORT wxGenericComboControl : public wxComboControlBase
{
public:
    // ctors and such
    wxGenericComboControl() : wxComboControlBase() { Init(); }

    wxGenericComboControl(wxWindow *parent,
                          wxWindowID id = wxID_ANY,
                          const wxString& value = wxEmptyString,
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxDefaultSize,
                          long style = 0,
                          const wxValidator& validator = wxDefaultValidator,
                          const wxString& name = wxComboBoxNameStr)
        : wxComboControlBase()
    {
        Init();

        (void)Create(parent, id, value, pos, size, style, validator, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxString& value = wxEmptyString,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator = wxDefaultValidator,
                const wxString& name = wxComboBoxNameStr);

    virtual ~wxGenericComboControl();

    static int GetFeatures() { return wxComboControlFeatures::All; }

#if defined(__WXUNIVERSAL__)
    // we have our own input handler and our own actions
    virtual bool PerformAction(const wxControlAction& action,
                               long numArg = 0l,
                               const wxString& strArg = wxEmptyString);
#endif

protected:

    // Mandatory virtuals
    virtual void OnResize();

    // Event handlers
    void OnPaintEvent( wxPaintEvent& event );
    void OnMouseEvent( wxMouseEvent& event );

private:
    void Init();

    DECLARE_EVENT_TABLE()

    DECLARE_DYNAMIC_CLASS(wxGenericComboControl)
};


#ifndef _WX_COMBOCONTROL_H_

// If native wxComboControl was not defined, then prepare a simple
// front-end so that wxRTTI works as expected.

class WXDLLEXPORT wxComboControl : public wxGenericComboControl
{
public:
    wxComboControl() : wxGenericComboControl() {}

    wxComboControl(wxWindow *parent,
                   wxWindowID id = wxID_ANY,
                   const wxString& value = wxEmptyString,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxComboBoxNameStr)
        : wxGenericComboControl()
    {
        (void)Create(parent, id, value, pos, size, style, validator, name);
    }

    virtual ~wxComboControl() {}

protected:

private:
    DECLARE_DYNAMIC_CLASS(wxComboControl)
};

#endif // _WX_COMBOCONTROL_H_

#else

#define wxGenericComboControl   wxComboControl

#endif // !defined(wxCOMBOCONTROL_FULLY_FEATURED)

#endif // wxUSE_COMBOCONTROL
#endif
    // _WX_GENERIC_COMBOCONTROL_H_
