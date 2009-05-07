/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_listc.h
// Purpose:     XML resource handler for wxListCtrl
// Author:      Brian Gavin
// Created:     2000/09/09
// RCS-ID:      $Id$
// Copyright:   (c) 2000 Brian Gavin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_LISTC_H_
#define _WX_XH_LISTC_H_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC && wxUSE_LISTCTRL

class WXDLLIMPEXP_FWD_CORE wxListCtrl;

class WXDLLIMPEXP_XRC wxListCtrlXmlHandler : public wxXmlResourceHandler
{
public:
    wxListCtrlXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

private:
    long Handle_wxListItem();
    wxObject* Handle_wxListCtrl();

    // gets the items image index in the corresponding image list (normal if
    // which is wxIMAGE_LIST_NORMAL or small if it is wxIMAGE_LIST_SMALL)
    long GetImageIndex(wxListCtrl *listctrl, int which);

    DECLARE_DYNAMIC_CLASS(wxListCtrlXmlHandler)
};

#endif // wxUSE_XRC && wxUSE_LISTCTRL

#endif // _WX_XH_LISTC_H_
