/////////////////////////////////////////////////////////////////////////////
// Name:        generic/datectrl.h
// Purpose:     generic wxDatePickerCtrl implementation
// Author:      Andreas Pflug
// Modified by:
// Created:     2005-01-19
// RCS-ID:      $Id$
// Copyright:   (c) 2005 Andreas Pflug <pgadmin@pse-consulting.de>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GENERIC_DATECTRL_H_
#define _WX_GENERIC_DATECTRL_H_

class WXDLLIMPEXP_CORE wxButton;
class WXDLLIMPEXP_ADV wxCalendarDateAttr;
class WXDLLIMPEXP_ADV wxCalendarCtrl;
class WXDLLIMPEXP_ADV wxCalendarEvent;
class WXDLLIMPEXP_CORE wxPopupWindow;
class WXDLLIMPEXP_CORE wxTextCtrl;

class WXDLLIMPEXP_ADV wxDatePickerCtrlGeneric : public wxDatePickerCtrlBase
{
public:
    // creating the control
    wxDatePickerCtrlGeneric() { Init(); }
    wxDatePickerCtrlGeneric(wxWindow *parent,
                            wxWindowID id,
                            const wxDateTime& date = wxDefaultDateTime,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxDP_DEFAULT | wxDP_SHOWCENTURY,
                            const wxString& name = wxDatePickerCtrlNameStr)
    {
        Init();

        (void)Create(parent, id, date, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxDateTime& date = wxDefaultDateTime,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDP_DEFAULT | wxDP_SHOWCENTURY,
                const wxString& name = wxDatePickerCtrlNameStr);

    // wxDatePickerCtrl methods
    void SetValue(const wxDateTime& date);
    wxDateTime GetValue() const;

    bool GetRange(wxDateTime *dt1, wxDateTime *dt2) const;
    void SetRange(const wxDateTime &dt1, const wxDateTime &dt2);

    bool SetDateRange(const wxDateTime& lowerdate = wxDefaultDateTime,
                      const wxDateTime& upperdate = wxDefaultDateTime);

    // extra methods available only in this (generic) implementation
    bool SetFormat(const wxChar *fmt);
    wxCalendarCtrl *GetCalendar() const { return m_cal; }


    // implementation only from now on
    // -------------------------------

    // overridden base class methods
    virtual bool Destroy();

    virtual bool Enable(bool enable = TRUE);
    virtual bool Show(bool show = TRUE);

protected:
    virtual wxSize DoGetBestSize() const;
    virtual void DoMoveWindow(int x, int y, int width, int height);

private:
    void Init();
    void DropDown(bool down = true);

    void OnText(wxCommandEvent &ev);
    void OnEditKey(wxKeyEvent & event);
    void OnCalKey(wxKeyEvent & event);
    void OnClick(wxCommandEvent &ev);
    void OnSelChange(wxCalendarEvent &ev);
    void OnSetFocus(wxFocusEvent &ev);
    void OnKillFocus(wxFocusEvent &ev);
    void OnChildSetFocus(wxChildFocusEvent &ev);


    wxPopupWindow *m_popup;
    wxTextCtrl *m_txt;
    wxCalendarCtrl *m_cal;
    wxButton *m_btn;
    wxString m_format;

    bool m_dropped,
         m_ignoreDrop;


    DECLARE_EVENT_TABLE()
    DECLARE_NO_COPY_CLASS(wxDatePickerCtrlGeneric)
};

#endif // _WX_GENERIC_DATECTRL_H_

