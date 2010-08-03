/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/dcmemory.h
// Author:      Peter Most, Javier Torres
// Id:          $Id$
// Copyright:   (c) Peter Most, Javier Torres
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_QT_DCMEMORY_H_
#define _WX_QT_DCMEMORY_H_

#include "wx/qt/dcclient.h"

class WXDLLIMPEXP_CORE wxMemoryDCImpl : public wxQtDCImpl
{
public:
    wxMemoryDCImpl( wxMemoryDC *owner );
    wxMemoryDCImpl( wxMemoryDC *owner, wxBitmap& bitmap );
    wxMemoryDCImpl( wxMemoryDC *owner, wxDC *dc );
    ~wxMemoryDCImpl();

    virtual void DoSelect(const wxBitmap& bitmap);
protected:

private:
    QPixmap *m_pixmap;
};

#endif // _WX_QT_DCMEMORY_H_
