/////////////////////////////////////////////////////////////////////////////
// Name:        src/qt/dcclient.cpp
// Author:      Peter Most
// Id:          $Id$
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/dcclient.h"
#include "wx/qt/dcclient.h"

//##############################################################################

wxWindowDCImpl::wxWindowDCImpl( wxDC *owner )
    : wxQtDCImpl( owner )
{
    m_ok = false;
}

wxWindowDCImpl::wxWindowDCImpl( wxDC *owner, wxWindow *win )
    : wxQtDCImpl( owner )
{
    m_ok = m_qtPainter.begin(win->GetHandle());
    if (m_ok) PrepareQPainter();
}

//##############################################################################


wxClientDCImpl::wxClientDCImpl( wxDC *owner )
    : wxWindowDCImpl( owner )
{
}

wxClientDCImpl::wxClientDCImpl( wxDC *owner, wxWindow *win )
    : wxWindowDCImpl( owner, win )
{
}

//##############################################################################

wxPaintDCImpl::wxPaintDCImpl( wxDC *owner )
    : wxClientDCImpl( owner )
{
}

wxPaintDCImpl::wxPaintDCImpl( wxDC *owner, wxWindow *win )
    : wxClientDCImpl( owner, win )
{
}

