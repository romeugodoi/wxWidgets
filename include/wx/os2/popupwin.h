///////////////////////////////////////////////////////////////////////////////
// Name:        wx/os2/popupwin.h
// Purpose:     wxPopupWindow class for wxPM
// Author:      Vadim Zeitlin
// Modified by:
// Created:     06.01.01
// RCS-ID:      $Id$
// Copyright:   (c) 2001 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_PM_POPUPWIN_H_
#define _WX_PM_POPUPWIN_H_

// ----------------------------------------------------------------------------
// wxPopupWindow
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxPopupWindow : public wxPopupWindowBase
{
public:
    wxPopupWindow() { }

    wxPopupWindow(wxWindow* pParent) { (void)Create(pParent); }

    bool Create( wxWindow* pParent
                ,int       nFlags = wxBORDER_NONE
               );
protected:
    virtual void DoGetPosition( int* pnX
                               ,int* pny
                              ) const;

    virtual WXDWORD OS2GetStyle( long     lFlags
                                ,WXDWORD* dwExstyle
                               ) const;
    DECLARE_DYNAMIC_CLASS(wxPopupWindow)
}; // end of CLASS wxPopupWindow

#endif // _WX_PM_POPUPWIN_H_
