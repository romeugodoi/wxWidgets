/////////////////////////////////////////////////////////////////////////////
// Name:        wx/settings.h
// Purpose:     wxSystemSettings class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_SETTINGS_H_BASE_
#define _WX_SETTINGS_H_BASE_

#include "wx/colour.h"
#include "wx/font.h"

// possible values for wxSystemSettings::GetFont() parameter
//
// NB: wxMSW assumes that they have the same values as the parameters of
//     Windows GetStockObject() API, don't change the values!
enum wxSystemFont
{
    wxSYS_OEM_FIXED_FONT = 10,
    wxSYS_ANSI_FIXED_FONT,
    wxSYS_ANSI_VAR_FONT,
    wxSYS_SYSTEM_FONT,
    wxSYS_DEVICE_DEFAULT_FONT,
    wxSYS_DEFAULT_PALETTE,
    wxSYS_SYSTEM_FIXED_FONT,
    wxSYS_DEFAULT_GUI_FONT
};

// possible values for wxSystemSettings::GetColour() parameter
//
// NB: wxMSW assumes that they have the same values as the parameters of
//     Windows GetSysColor() API, don't change the values!
enum wxSystemColour
{
    wxSYS_COLOUR_SCROLLBAR,
    wxSYS_COLOUR_BACKGROUND,
    wxSYS_COLOUR_ACTIVECAPTION,
    wxSYS_COLOUR_INACTIVECAPTION,
    wxSYS_COLOUR_MENU,
    wxSYS_COLOUR_WINDOW,
    wxSYS_COLOUR_WINDOWFRAME,
    wxSYS_COLOUR_MENUTEXT,
    wxSYS_COLOUR_WINDOWTEXT,
    wxSYS_COLOUR_CAPTIONTEXT,
    wxSYS_COLOUR_ACTIVEBORDER,
    wxSYS_COLOUR_INACTIVEBORDER,
    wxSYS_COLOUR_APPWORKSPACE,
    wxSYS_COLOUR_HIGHLIGHT,
    wxSYS_COLOUR_HIGHLIGHTTEXT,
    wxSYS_COLOUR_BTNFACE,
    wxSYS_COLOUR_BTNSHADOW,
    wxSYS_COLOUR_GRAYTEXT,
    wxSYS_COLOUR_BTNTEXT,
    wxSYS_COLOUR_INACTIVECAPTIONTEXT,
    wxSYS_COLOUR_BTNHIGHLIGHT,
    wxSYS_COLOUR_3DDKSHADOW,
    wxSYS_COLOUR_3DLIGHT,
    wxSYS_COLOUR_INFOTEXT,
    wxSYS_COLOUR_INFOBK,
    wxSYS_COLOUR_LISTBOX,

    wxSYS_COLOUR_DESKTOP = wxSYS_COLOUR_BACKGROUND,
    wxSYS_COLOUR_3DFACE = wxSYS_COLOUR_BTNFACE,
    wxSYS_COLOUR_3DSHADOW = wxSYS_COLOUR_BTNSHADOW,
    wxSYS_COLOUR_3DHIGHLIGHT = wxSYS_COLOUR_BTNHIGHLIGHT,
    wxSYS_COLOUR_3DHILIGHT = wxSYS_COLOUR_BTNHIGHLIGHT,
    wxSYS_COLOUR_BTNHILIGHT = wxSYS_COLOUR_BTNHIGHLIGHT
};

// possible values for wxSystemSettings::GetMetric() parameter
//
// NB: update the conversion table in msw/settings.cpp if you change the values
//     of the elements of this enum
enum wxSystemMetric
{
    wxSYS_MOUSE_BUTTONS = 1,
    wxSYS_BORDER_X,
    wxSYS_BORDER_Y,
    wxSYS_CURSOR_X,
    wxSYS_CURSOR_Y,
    wxSYS_DCLICK_X,
    wxSYS_DCLICK_Y,
    wxSYS_DRAG_X,
    wxSYS_DRAG_Y,
    wxSYS_EDGE_X,
    wxSYS_EDGE_Y,
    wxSYS_HSCROLL_ARROW_X,
    wxSYS_HSCROLL_ARROW_Y,
    wxSYS_HTHUMB_X,
    wxSYS_ICON_X,
    wxSYS_ICON_Y,
    wxSYS_ICONSPACING_X,
    wxSYS_ICONSPACING_Y,
    wxSYS_WINDOWMIN_X,
    wxSYS_WINDOWMIN_Y,
    wxSYS_SCREEN_X,
    wxSYS_SCREEN_Y,
    wxSYS_FRAMESIZE_X,
    wxSYS_FRAMESIZE_Y,
    wxSYS_SMALLICON_X,
    wxSYS_SMALLICON_Y,
    wxSYS_HSCROLL_Y,
    wxSYS_VSCROLL_X,
    wxSYS_VSCROLL_ARROW_X,
    wxSYS_VSCROLL_ARROW_Y,
    wxSYS_VTHUMB_Y,
    wxSYS_CAPTION_Y,
    wxSYS_MENU_Y,
    wxSYS_NETWORK_PRESENT,
    wxSYS_PENWINDOWS_PRESENT,
    wxSYS_SHOW_SOUNDS,
    wxSYS_SWAP_BUTTONS
};

// possible values for wxSystemSettings::HasFeature() parameter
enum wxSystemFeature
{
    wxSYS_CAN_DRAW_FRAME_DECORATIONS = 1,
    wxSYS_CAN_ICONIZE_FRAME
};

// ----------------------------------------------------------------------------
// wxSystemSettingsNative: defines the API for wxSystemSettings class
// ----------------------------------------------------------------------------

// this is a namespace rather than a class: it has only non virtual static
// functions
//
// also note that the methods are implemented in the platform-specific source
// files (i.e. this is not a real base class as we can't override its virtual
// functions because it doesn't have any)

class WXDLLEXPORT wxSystemSettingsNative
{
public:
    // get a standard system colour
    static wxColour GetColour(wxSystemColour index);

    // get a standard system font
    static wxFont GetFont(wxSystemFont index);

    // get a system-dependent metric
    static int GetMetric(wxSystemMetric index);

    // return true if the port has certain feature
    static bool HasFeature(wxSystemFeature index);


    // the backwards compatible versions, don't use these methods in the new
    // code!
    static wxColour GetSystemColour(int index)
        { return GetColour((wxSystemColour)index); }
    static wxFont GetSystemFont(int index)
        { return GetFont((wxSystemFont)index); }
    static int GetSystemMetric(int index)
        { return GetMetric((wxSystemMetric)index); }
};

// ----------------------------------------------------------------------------
// include the declaration of the real platform-dependent class
// ----------------------------------------------------------------------------

// TODO: this should go away once wxOS2 has been updated to use wxSSNative
#if defined(__WXPM__)
    #include "wx/os2/settings.h"
#else

class wxSystemSettings : public wxSystemSettingsNative
{
public:
#ifdef __WXUNIVERSAL__
    // in wxUniversal we want to use the theme standard colours instead of the
    // system ones, otherwuse wxSystemSettings is just the same as
    // wxSystemSettingsNative
    static wxColour GetColour(wxSystemColour index);
#endif // __WXUNIVERSAL__
};

#endif // ! __WXPM__

#endif
    // _WX_SETTINGS_H_BASE_

