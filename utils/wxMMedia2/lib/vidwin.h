// ----------------------------------------------------------------------------
// Name:       vidwin.h
// Purpose:    wxMMedia
// Author:     Guilhem Lavaux
// Created:    February 1998
// Updated:
// Copyright:  (C) 1998, Guilhem Lavaux
// License:    wxWindows license
// ----------------------------------------------------------------------------

#ifndef __VID_windows_H__
#define __VID_windows_H__

#ifdef __GNUG__
    #pragma interface "vidwin.h"
#endif

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/string.h"
    #include "wx/stream.h"
    #include "wx/window.h"
#endif

// ----------------------------------------------------------------------------
// wxMMedia2 headers

#include "vidbase.h"

// ----------------------------------------------------------------------------
// System headers and private types

#ifdef WXMMEDIA_INTERNAL
#include <windows.h>
#include <mmsystem.h>

typedef struct VIDW_Internal {
    MCIDEVICEID m_dev_id;
} wxVIDWinternal;
#endif

// ----------------------------------------------------------------------------
// Class definition

class WXDLLEXPORT wxVideoWindows : public wxVideoBaseDriver {
    DECLARE_DYNAMIC_CLASS(wxVideoWindows)
protected:
    struct VIDW_Internal *m_internal;
    bool m_paused, m_stopped, m_remove_file;
    wxString m_filename;

    void OpenFile();
public:
    wxVideoWindows(void);
    wxVideoWindows(wxInputStream& str);
    wxVideoWindows(const wxString& fname);
    ~wxVideoWindows(void);

    bool Play();
    bool Stop();
    bool Pause();
    bool Resume();
    
    bool Resize(wxUint16 w, wxUint16 h);
    bool GetSize(wxSize& size) const;
    
    bool IsCapable(wxVideoType v_type);
    
    bool AttachOutput(wxWindow& output);
    void DetachOutput(void);
    
    bool IsPaused();
    bool IsStopped();
};

#endif
