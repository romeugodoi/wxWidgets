///////////////////////////////////////////////////////////////////////////////
// Name:        wx/palmos/popupwin.h
// Purpose:     wxPopupWindow class for wxMSW
// Author:      William Osborne
// Modified by:
// Created:     10/13/04
// RCS-ID:      $Id: 
// Copyright:   (c) William Osborne
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_MSW_POPUPWIN_H_
#define _WX_MSW_POPUPWIN_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "popup.h"
#endif

// ----------------------------------------------------------------------------
// wxPopupWindow
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxPopupWindow : public wxPopupWindowBase
{
public:
    wxPopupWindow() { }

    wxPopupWindow(wxWindow *parent, int flags = wxBORDER_NONE)
        { (void)Create(parent, flags); }

    bool Create(wxWindow *parent, int flags = wxBORDER_NONE);

    virtual bool Show(bool show = TRUE);

protected:
    // popups handle the position like wxTopLevelWindow, not wxWindow
    virtual void DoGetPosition(int *x, int *y) const;

    // return the style to be used for the popup windows
    virtual WXDWORD MSWGetStyle(long flags, WXDWORD *exstyle) const;

    // get the HWND to be used as parent of this window with CreateWindow()
    virtual WXHWND MSWGetParent() const;

    DECLARE_DYNAMIC_CLASS_NO_COPY(wxPopupWindow)
};

#endif // _WX_MSW_POPUPWIN_H_

