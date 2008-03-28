///////////////////////////////////////////////////////////////////////////////
// Name:        common/calctrlcmn.cpp
// Author:      Marcin Wojdyr
// Created:     2008-03-26
// RCS-ID:      $Id$
// Copyright:   (C) Marcin Wojdyr
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
#endif //WX_PRECOMP

#if wxUSE_CALENDARCTRL || wxUSE_DATEPICKCTRL

#include "wx/dateevt.h"
IMPLEMENT_DYNAMIC_CLASS(wxDateEvent, wxCommandEvent)
DEFINE_EVENT_TYPE(wxEVT_DATE_CHANGED)

#endif // wxUSE_CALENDARCTRL || wxUSE_DATEPICKCTRL


#if wxUSE_CALENDARCTRL

#include "wx/calctrl.h"

// ----------------------------------------------------------------------------
// events
// ----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(wxCalendarEvent, wxDateEvent)

DEFINE_EVENT_TYPE(wxEVT_CALENDAR_SEL_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_PAGE_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_DOUBLECLICKED)
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_WEEKDAY_CLICKED)

// deprecated events
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_DAY_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_MONTH_CHANGED)
DEFINE_EVENT_TYPE(wxEVT_CALENDAR_YEAR_CHANGED)


wxCalendarDateAttr wxCalendarDateAttr::m_mark(wxCAL_BORDER_SQUARE);

bool wxCalendarCtrlBase::EnableMonthChange(bool enable)
{
    const long styleOrig = GetWindowStyle();
    long style = enable ? styleOrig & ~wxCAL_NO_MONTH_CHANGE
                        : styleOrig | wxCAL_NO_MONTH_CHANGE;
    if ( style == styleOrig )
        return false;

    SetWindowStyle(style);

    return true;
}

#endif // wxUSE_CALENDARCTRL

