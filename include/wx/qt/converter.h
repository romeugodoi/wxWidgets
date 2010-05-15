///////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/converter.h
// Purpose:     Converter utility classes and functions
// Author:      Peter Most, Kolya Kosenko
// Created:     02/28/10
// RCS-ID:      $Id$
// Copyright:   (c) Peter Most
//              (c) 2010 Kolya Kosenko
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_QT_CONVERTER_H_
#define _WX_QT_CONVERTER_H_

// Rely on overloading and let the compiler pick the correct version, which makes
// them easier to use then to write wxQtConvertQtRectToWxRect() or wxQtConvertWxRectToQtRect()

class WXDLLIMPEXP_FWD_CORE wxPoint;
class QPoint;
wxPoint wxQtConvertPoint( const QPoint &point );
QPoint wxQtConvertPoint( const wxPoint &point );

class WXDLLIMPEXP_FWD_CORE wxRect;
class QRect;
wxRect wxQtConvertRect( const QRect &rect );
QRect  wxQtConvertRect( const wxRect &rect );

class WXDLLIMPEXP_FWD_BASE wxString;
class QString;
wxString wxQtConvertString( const QString &str );
QString  wxQtConvertString( const wxString &str );

#if wxUSE_DATETIME

class WXDLLIMPEXP_FWD_BASE wxDateTime;
class QDate;

wxDateTime wxQtConvertDate(const QDate& date);
QDate wxQtConvertDate(const wxDateTime& date);

#endif // wxUSE_DATETIME


#endif // _WX_QT_CONVERTER_H_

