/////////////////////////////////////////////////////////////////////////////
// Name:        wx/features.h
// Purpose:     test macros for the features which might be available in some
//              wxWindows ports but not others
// Author:      Vadim Zeitlin
// Modified by:
// Created:     18.03.02
// RCS-ID:      $Id$
// Copyright:   (c) 2002 Vadim Zeitlin <vadim@wxwindows.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_FEATURES_H_
#define _WX_FEATURES_H_

// radio menu items are currently only implemented in wxGTK
#if defined(__WXGTK__) // || defined(__WXMSW__)
    #define wxHAS_RADIO_MENU_ITEMS
#else
    #undef wxHAS_RADIO_MENU_ITEMS
#endif

#endif // _WX_FEATURES_H_

