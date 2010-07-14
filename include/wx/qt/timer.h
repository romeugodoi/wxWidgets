/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/timer.h
// Author:      Javier Torres
// Id:          $Id$
// Copyright:   (c) Javier Torres
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_QT_TIMER_H_
#define _WX_QT_TIMER_H_

#if wxUSE_TIMER

#include "wx/private/timer.h"

#include <QtCore/QObject>

//-----------------------------------------------------------------------------
// wxTimer
//-----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxQtTimerImpl : public wxTimerImpl, QObject
{
public:
    wxQtTimerImpl( wxTimer* timer );

    virtual bool Start( int millisecs = -1, bool oneShot = false );
    virtual void Stop();
    virtual bool IsRunning() const;

protected:
    virtual void timerEvent( QTimerEvent * event );
    
private:
    int m_timerId;
};

#endif // wxUSE_TIMER

#endif // _WX_QT_TIMER_H_
