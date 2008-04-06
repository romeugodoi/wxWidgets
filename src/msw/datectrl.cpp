/////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/datectrl.cpp
// Purpose:     wxDatePickerCtrl implementation
// Author:      Vadim Zeitlin
// Modified by:
// Created:     2005-01-09
// RCS-ID:      $Id$
// Copyright:   (c) 2005 Vadim Zeitlin <vadim@wxwindows.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_DATEPICKCTRL

#ifndef WX_PRECOMP
    #include "wx/msw/wrapwin.h"
    #include "wx/msw/wrapcctl.h" // include <commctrl.h> "properly"
    #include "wx/app.h"
    #include "wx/intl.h"
    #include "wx/dcclient.h"
    #include "wx/msw/private.h"
#endif

#include "wx/datectrl.h"

#include "wx/msw/private/datecontrols.h"

#include "wx/dateevt.h"

// apparently some versions of mingw define these macros erroneously
#ifndef DateTime_GetSystemtime
    #define DateTime_GetSystemtime DateTime_GetSystemTime
#endif

#ifndef DateTime_SetSystemtime
    #define DateTime_SetSystemtime DateTime_SetSystemTime
#endif

IMPLEMENT_DYNAMIC_CLASS(wxDatePickerCtrl, wxControl)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxDatePickerCtrl creation
// ----------------------------------------------------------------------------

bool
wxDatePickerCtrl::Create(wxWindow *parent,
                         wxWindowID id,
                         const wxDateTime& dt,
                         const wxPoint& pos,
                         const wxSize& size,
                         long style,
                         const wxValidator& validator,
                         const wxString& name)
{
    if ( !wxMSWDateControls::CheckInitialization() )
        return false;

    // use wxDP_SPIN if wxDP_DEFAULT (0) was given as style
    if ( !(style & wxDP_DROPDOWN) )
        style |= wxDP_SPIN;

    // initialize the base class
    if ( !CreateControl(parent, id, pos, size, style, validator, name) )
        return false;

    // create the native control
    if ( !MSWCreateControl(DATETIMEPICK_CLASS, wxEmptyString, pos, size) )
        return false;

    if ( dt.IsValid() || (style & wxDP_ALLOWNONE) )
        SetValue(dt);
    else
        SetValue(wxDateTime::Today());

    return true;
}

WXDWORD wxDatePickerCtrl::MSWGetStyle(long style, WXDWORD *exstyle) const
{
    WXDWORD styleMSW = wxDatePickerCtrlBase::MSWGetStyle(style, exstyle);

    // although MSDN doesn't mention it, DTS_UPDOWN doesn't work with
    // comctl32.dll 4.72
    if ( wxApp::GetComCtl32Version() > 472 && (style & wxDP_SPIN) )
        styleMSW |= DTS_UPDOWN;
    //else: drop down by default

#ifdef DTS_SHORTDATECENTURYFORMAT
    if ( style & wxDP_SHOWCENTURY )
        styleMSW |= DTS_SHORTDATECENTURYFORMAT;
    else
#endif // DTS_SHORTDATECENTURYFORMAT
        styleMSW |= DTS_SHORTDATEFORMAT;

    if ( style & wxDP_ALLOWNONE )
        styleMSW |= DTS_SHOWNONE;

    return styleMSW;
}

// TODO: handle WM_WININICHANGE

// ----------------------------------------------------------------------------
// wxDatePickerCtrl geometry
// ----------------------------------------------------------------------------

wxSize wxDatePickerCtrl::DoGetBestSize() const
{
    wxClientDC dc(wx_const_cast(wxDatePickerCtrl *, this));
    dc.SetFont(GetFont());

    // we can't use FormatDate() here as the CRT doesn't always use the same
    // format as the date picker control
    wxString s;
    for ( int len = 100; ; len *= 2 )
    {
        if ( ::GetDateFormat
               (
                    LOCALE_USER_DEFAULT,    // the control should use the same
                    DATE_SHORTDATE,         // the format used by the control
                    NULL,                   // use current date (we don't care)
                    NULL,                   // no custom format
                    wxStringBuffer(s, len), // output buffer
                    len                     // and its length
               ) )
        {
            // success
            break;
        }

        const DWORD rc = ::GetLastError();
        if ( rc != ERROR_INSUFFICIENT_BUFFER )
        {
            wxLogApiError(_T("GetDateFormat"), rc);

            // fall back on wxDateTime, what else to do?
            s = wxDateTime::Today().FormatDate();
            break;
        }
    }

    // the control adds a lot of extra space around separators
    s.Replace(_T(","), _T("    ,    "));

    int x, y;
    dc.GetTextExtent(s, &x, &y);

    wxSize best(x + 40 /* margin + arrows */, EDIT_HEIGHT_FROM_CHAR_HEIGHT(y));
    CacheBestSize(best);
    return best;
}

// ----------------------------------------------------------------------------
// wxDatePickerCtrl operations
// ----------------------------------------------------------------------------

void wxDatePickerCtrl::SetValue(const wxDateTime& dt)
{
    wxCHECK_RET( dt.IsValid() || HasFlag(wxDP_ALLOWNONE),
                    _T("this control requires a valid date") );

    SYSTEMTIME st;
    if ( dt.IsValid() )
        wxMSWDateControls::ToSystemTime(&st, dt);
    if ( !DateTime_SetSystemtime(GetHwnd(),
                                 dt.IsValid() ? GDT_VALID : GDT_NONE,
                                 &st) )
    {
        wxLogDebug(_T("DateTime_SetSystemtime() failed"));
    }

    // we need to keep only the date part, times don't make sense for this
    // control (in particular, comparisons with other dates would fail)
    m_date = dt;
    if ( m_date.IsValid() )
        m_date.ResetTime();
}

wxDateTime wxDatePickerCtrl::GetValue() const
{
#ifdef __WXDEBUG__
    wxDateTime dt;
    SYSTEMTIME st;
    if ( DateTime_GetSystemtime(GetHwnd(), &st) == GDT_VALID )
    {
        wxMSWDateControls::FromSystemTime(&dt, st);
    }

    wxASSERT_MSG( m_date.IsValid() == dt.IsValid() &&
                    (!dt.IsValid() || dt == m_date),
                  _T("bug in wxDatePickerCtrl: m_date not in sync") );
#endif // __WXDEBUG__

    return m_date;
}

void wxDatePickerCtrl::SetRange(const wxDateTime& dt1, const wxDateTime& dt2)
{
    SYSTEMTIME st[2];

    DWORD flags = 0;
    if ( dt1.IsValid() )
    {
        wxMSWDateControls::ToSystemTime(&st[0], dt1);
        flags |= GDTR_MIN;
    }

    if ( dt2.IsValid() )
    {
        wxMSWDateControls::ToSystemTime(&st[1], dt2);
        flags |= GDTR_MAX;
    }

    if ( !DateTime_SetRange(GetHwnd(), flags, st) )
    {
        wxLogDebug(_T("DateTime_SetRange() failed"));
    }
}

bool wxDatePickerCtrl::GetRange(wxDateTime *dt1, wxDateTime *dt2) const
{
    SYSTEMTIME st[2];

    DWORD flags = DateTime_GetRange(GetHwnd(), st);
    if ( dt1 )
    {
        if ( flags & GDTR_MIN )
            wxMSWDateControls::FromSystemTime(dt1, st[0]);
        else
            *dt1 = wxDefaultDateTime;
    }

    if ( dt2 )
    {
        if ( flags & GDTR_MAX )
            wxMSWDateControls::FromSystemTime(dt2, st[1]);
        else
            *dt2 = wxDefaultDateTime;
    }

    return flags != 0;
}

// ----------------------------------------------------------------------------
// wxDatePickerCtrl events
// ----------------------------------------------------------------------------

bool
wxDatePickerCtrl::MSWOnNotify(int idCtrl, WXLPARAM lParam, WXLPARAM *result)
{
    NMHDR* hdr = (NMHDR *)lParam;
    switch ( hdr->code )
    {
        case DTN_DATETIMECHANGE:
        {
            NMDATETIMECHANGE *dtch = (NMDATETIMECHANGE *)hdr;
            wxDateTime dt;
            if ( dtch->dwFlags == GDT_VALID )
                wxMSWDateControls::FromSystemTime(&dt, dtch->st);

            // filter out duplicate DTN_DATETIMECHANGE events which the native
            // control sends us when using wxDP_DROPDOWN style
            if ( (m_date.IsValid() != dt.IsValid()) ||
                    (m_date.IsValid() && dt != m_date) )
            {
                m_date = dt;
                wxDateEvent event(this, dt, wxEVT_DATE_CHANGED);
                if ( HandleWindowEvent(event) )
                {
                    *result = 0;
                    return true;
                }
            }
            //else: both the old and new values are invalid, nothing changed
        }
    }

    return wxDatePickerCtrlBase::MSWOnNotify(idCtrl, lParam, result);
}

#endif // wxUSE_DATEPICKCTRL
