/////////////////////////////////////////////////////////////////////////////
// Name:        wx/icon.h
// Purpose:     wxIcon base header
// Author:      Julian Smart
// Modified by:
// Created:
// Copyright:   (c) Julian Smart
// RCS-ID:      $Id$
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_ICON_H_BASE_
#define _WX_ICON_H_BASE_

#include "wx/iconloc.h"


// the wxICON_DEFAULT_TYPE (the wxIcon equivalent of wxBITMAP_DEFAULT_TYPE)
// constant defines the default argument value for wxIcon ctor and wxIcon::LoadFile()
// functions.
#if defined(__WXMSW__)
  #define wxICON_DEFAULT_TYPE   wxBITMAP_TYPE_ICO_RESOURCE
#elif defined(__WXMGL__)
  #define wxICON_DEFAULT_TYPE   wxBITMAP_TYPE_ICO_RESOURCE
#elif defined(__WXMAC__) && wxOSX_USE_COCOA_OR_CARBON
  #define wxICON_DEFAULT_TYPE   wxBITMAP_TYPE_ICON_RESOURCE
#else
  #define wxICON_DEFAULT_TYPE   wxBITMAP_TYPE_XPM
#endif

// a more readable way to tell
#define wxICON_SCREEN_DEPTH     (-1)

#if defined(__WXPALMOS__)
  #include "wx/generic/icon.h"
#elif defined(__WXMSW__)
  #include "wx/msw/icon.h"
#elif defined(__WXMOTIF__)
  #include "wx/motif/icon.h"
#elif defined(__WXGTK20__)
  #include "wx/generic/icon.h"
#elif defined(__WXGTK__)
  #include "wx/generic/icon.h"
#elif defined(__WXX11__)
  #include "wx/generic/icon.h"
#elif defined(__WXMGL__)
  #include "wx/generic/icon.h"
#elif defined(__WXDFB__)
  #include "wx/generic/icon.h"
#elif defined(__WXMAC__)
#if wxOSX_USE_COCOA_OR_CARBON
  #include "wx/osx/icon.h"
#else
  #include "wx/generic/icon.h"
#endif
#elif defined(__WXCOCOA__)
  #include "wx/cocoa/icon.h"
#elif defined(__WXPM__)
  #include "wx/os2/icon.h"
#endif

//-----------------------------------------------------------------------------
// wxVariant support
//-----------------------------------------------------------------------------

#if wxUSE_VARIANT
#include "wx/variant.h"
DECLARE_VARIANT_OBJECT_EXPORTED(wxIcon,WXDLLIMPEXP_CORE)
#endif


#endif
    // _WX_ICON_H_BASE_
