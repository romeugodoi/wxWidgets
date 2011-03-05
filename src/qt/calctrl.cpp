/////////////////////////////////////////////////////////////////////////////
// Name:        src/qt/calctrl.cpp
// Purpose:     wxCalendarCtrl control implementation for wxQt
// Author:      Kolya Kosenko
// Created:     2010-05-12
// RCS-ID:      $Id$
// Copyright:   (C) 2010 Kolya Kosenko
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_CALENDARCTRL

#include "wx/calctrl.h"
#include "wx/qt/utils.h"

#include <QtGui/QTextCharFormat>


void wxCalendarCtrl::Init()
{
    m_qtCalendar = NULL;

    for ( size_t n = 0; n < WXSIZEOF(m_attrs); n++ )
    {
        m_attrs[n] = NULL;
    }
}

wxCalendarCtrl::~wxCalendarCtrl()
{
    for ( size_t n = 0; n < WXSIZEOF(m_attrs); n++ )
    {
        delete m_attrs[n];
    }
}

bool wxCalendarCtrl::Create(wxWindow *parent,
                            wxWindowID id,
                            const wxDateTime& date,
                            const wxPoint& pos,
                            const wxSize& size,
                            long style,
                            const wxString& name)
{
    if ( !CreateControl(parent, id, pos, size, style, wxDefaultValidator, name) )
        return false;

    m_qtCalendar = new wxQtCalendarWidget( parent, this );
    m_qtCalendar->resize(m_qtCalendar->sizeHint());

    {
        // Init holiday colours
        const QTextCharFormat format = m_qtCalendar->weekdayTextFormat(Qt::Sunday);
        m_colHolidayFg = format.foreground().color();

        wxMISSING_IMPLEMENTATION( "Get holiday background color" );

        // Bug in Qt: returned background color is incorrect
        //m_colHolidayBg = format.background().color();
    }

    {
        // synchronize header colours
        QTextCharFormat format = m_qtCalendar->headerTextFormat();

        bool sync = false;

        if ( m_colHeaderFg.IsOk() )
            sync = true;
        else
            m_colHeaderFg = format.foreground().color();

        if ( m_colHeaderBg.IsOk() )
            sync = true;
        else
            m_colHeaderFg = format.background().color();

        if ( sync )
            SetHeaderColours(m_colHeaderFg, m_colHeaderBg);
    }

    UpdateStyle();

    if ( date.IsValid() )
        SetDate(date);

    return true;
}

void wxCalendarCtrl::UpdateStyle()
{
    if ( !m_qtCalendar )
        return;

    if ( m_windowStyle & wxCAL_MONDAY_FIRST )
        m_qtCalendar->setFirstDayOfWeek(Qt::Monday);
    else // wxCAL_SUNDAY_FIRST
        m_qtCalendar->setFirstDayOfWeek(Qt::Sunday);

    if ( m_windowStyle & wxCAL_SHOW_WEEK_NUMBERS )
        m_qtCalendar->setVerticalHeaderFormat(QCalendarWidget::ISOWeekNumbers);
    else
        m_qtCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    RefreshHolidays();
}

void wxCalendarCtrl::SetWindowStyleFlag(long style)
{
    const long styleOld = GetWindowStyleFlag();

    wxCalendarCtrlBase::SetWindowStyleFlag(style);

    if ( styleOld != GetWindowStyleFlag() )
        UpdateStyle();
}

bool wxCalendarCtrl::SetDate(const wxDateTime& date)
{
    wxCHECK_MSG( date.IsValid(), false, "invalid date" );
    if ( !m_qtCalendar )
        return false;

    m_qtCalendar->setSelectedDate(wxQtConvertDate(date));

    return true;
}

wxDateTime wxCalendarCtrl::GetDate() const
{
    if ( !m_qtCalendar )
        return wxDateTime();

    return wxQtConvertDate(m_qtCalendar->selectedDate());
}

bool wxCalendarCtrl::SetDateRange(const wxDateTime& lowerdate,
                                  const wxDateTime& upperdate)
{
    if ( !m_qtCalendar )
        return false;

    m_qtCalendar->setMinimumDate(wxQtConvertDate(lowerdate));
    m_qtCalendar->setMaximumDate(wxQtConvertDate(upperdate));

    return true;
}

bool wxCalendarCtrl::GetDateRange(wxDateTime *lowerdate,
                                  wxDateTime *upperdate) const
{
    if ( !m_qtCalendar )
        return false;

    if (lowerdate)
        *lowerdate = wxQtConvertDate(m_qtCalendar->minimumDate());
    if (upperdate)
        *upperdate = wxQtConvertDate(m_qtCalendar->maximumDate());

    return true;
}

// Copied from wxMSW
bool wxCalendarCtrl::EnableMonthChange(bool enable)
{
    if ( !wxCalendarCtrlBase::EnableMonthChange(enable) )
        return false;

    wxDateTime dtStart, dtEnd;
    if ( !enable )
    {
        dtStart = GetDate();
        dtStart.SetDay(1);

        dtEnd = dtStart.GetLastMonthDay();
    }
    //else: leave them invalid to remove the restriction

    SetDateRange(dtStart, dtEnd);

    return true;
}

void wxCalendarCtrl::Mark(size_t day, bool mark)
{
    wxCHECK_RET( day > 0 && day < 32, "invalid day" );

    if ( !m_qtCalendar )
        return;

    QDate date = m_qtCalendar->selectedDate();
    date.setDate(date.year(), date.month(), day);

    QTextCharFormat format = m_qtCalendar->dateTextFormat(date);
    format.setFontWeight(mark ? QFont::Bold : QFont::Normal);
    m_qtCalendar->setDateTextFormat(date, format);
}

void wxCalendarCtrl::SetHoliday(size_t day)
{
    wxCHECK_RET( day > 0 && day < 32, "invalid day" );

    if ( !(m_windowStyle & wxCAL_SHOW_HOLIDAYS) )
        return;

    if ( !m_qtCalendar )
        return;

    QDate date = m_qtCalendar->selectedDate();
    date.setDate(date.year(), date.month(), day);

    QTextCharFormat format = m_qtCalendar->dateTextFormat(date);
    format.setForeground(m_colHolidayFg.GetHandle());
    m_qtCalendar->setDateTextFormat(date, format);
}

void wxCalendarCtrl::SetHolidayColours(const wxColour& colFg, const wxColour& colBg)
{
    m_colHolidayFg = colFg;
    m_colHolidayBg = colBg;
    RefreshHolidays();
}

void wxCalendarCtrl::RefreshHolidays()
{
    if ( !m_qtCalendar )
        return;

    QTextCharFormat format;
    if ( m_windowStyle & wxCAL_SHOW_HOLIDAYS )
    {
        if ( m_colHolidayFg.IsOk() )
            format.setForeground(m_colHolidayFg.GetHandle());
        if ( m_colHolidayBg.IsOk() )
            format.setBackground(m_colHolidayBg.GetHandle());
    }
    else
    {
        format.setForeground(m_qtCalendar->weekdayTextFormat(Qt::Monday)
            .foreground().color());

        wxMISSING_IMPLEMENTATION( "Set holiday background color" );

        // Bug in Qt: returned background color is incorrect
        //format.setBackground(m_qtCalendar->weekdayTextFormat(Qt::Monday)
        //    .background().color());
    }
    m_qtCalendar->setWeekdayTextFormat(Qt::Saturday, format);
    m_qtCalendar->setWeekdayTextFormat(Qt::Sunday,   format);
}

void wxCalendarCtrl::SetHeaderColours(const wxColour& colFg, const wxColour& colBg)
{
    m_colHeaderFg = colFg;
    m_colHeaderBg = colBg;

    if ( !m_qtCalendar )
        return;

    QTextCharFormat format = m_qtCalendar->headerTextFormat();
    if ( m_colHeaderFg.IsOk() )
        format.setForeground(m_colHeaderFg.GetHandle());
    if ( m_colHeaderBg.IsOk() )
        format.setBackground(m_colHeaderBg.GetHandle());
    m_qtCalendar->setHeaderTextFormat(format);
}

wxCalendarDateAttr *wxCalendarCtrl::GetAttr(size_t day) const
{
    wxCHECK_MSG( day > 0 && day < 32, NULL, wxT("invalid day") );

    return m_attrs[day - 1];
}

void wxCalendarCtrl::SetAttr(size_t day, wxCalendarDateAttr *attr)
{
    wxCHECK_RET( day > 0 && day < 32, wxT("invalid day") );

    delete m_attrs[day - 1];
    m_attrs[day - 1] = attr;

    QDate date = m_qtCalendar->selectedDate();
    date.setDate(date.year(), date.month(), day);

    QTextCharFormat format = m_qtCalendar->dateTextFormat(date);
    if ( attr->HasTextColour() )
        format.setForeground(attr->GetTextColour().GetHandle());
    if ( attr->HasBackgroundColour() )
        format.setBackground(attr->GetBackgroundColour().GetHandle());

    wxMISSING_IMPLEMENTATION( "Setting font" );

    // wxFont is not implemented yet
    //if ( attr->HasFont() )
    //    format.setFont(attr->GetFont().GetQFont());
    
    m_qtCalendar->setDateTextFormat(date, format);
}

QCalendarWidget *wxCalendarCtrl::GetHandle() const
{
    return m_qtCalendar;
}

//=============================================================================

wxQtCalendarWidget::wxQtCalendarWidget( wxWindow *parent, wxCalendarCtrl *handler )
    : wxQtEventSignalHandler< QCalendarWidget, wxCalendarCtrl >( parent, handler )
{
    m_date = selectedDate();
    connect(this, SIGNAL(selectionChanged()), this, SLOT(OnSelectionChanged()));
    connect(this, SIGNAL(activated(QDate)),   this, SLOT(OnActivated(QDate)));
}

void wxQtCalendarWidget::OnSelectionChanged()
{
    GetHandler()->GenerateAllChangeEvents(wxQtConvertDate(m_date));
    m_date = selectedDate();
}

void wxQtCalendarWidget::OnActivated(const QDate &WXUNUSED(date))
{
    GetHandler()->GenerateEvent(wxEVT_CALENDAR_DOUBLECLICKED);
}

#endif // wxUSE_CALENDARCTRL
