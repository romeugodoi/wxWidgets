/////////////////////////////////////////////////////////////////////////////
// Name:        wx/sound.h
// Purpose:     wxSoundBase class
// Author:      Vaclav Slavik
// Modified by:
// Created:     2004/02/01
// RCS-ID:      $Id$
// Copyright:   (c) 2004, Vaclav Slavik
// Licence:   	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_SOUND_H_BASE_
#define _WX_SOUND_H_BASE_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "soundbase.h"
#endif

#include "wx/defs.h"

#if wxUSE_SOUND

#include "wx/object.h"

// ----------------------------------------------------------------------------
// wxSoundBase: common wxSound code and interface
// ----------------------------------------------------------------------------

// Flags for wxSound::Play
#if WXWIN_COMPATIBILITY_2_4
    // NB: we can't use enum because there would be ambiguity between the
    //     two Play() prototypes when called without explicit parameters
    #define wxSOUND_SYNC  ((unsigned)0)
    #define wxSOUND_ASYNC ((unsigned)1)
    #define wxSOUND_LOOP  ((unsigned)2)
#else
    enum wxSoundFlags
    {
        wxSOUND_SYNC   = 0,
        wxSOUND_ASYNC  = 1,
        wxSOUND_LOOP   = 2
    };
#endif

// Base class for wxSound implementations
class WXDLLIMPEXP_ADV wxSoundBase : public wxObject
{
public:
    // Play the sound:
    bool Play(unsigned flags = wxSOUND_ASYNC) const
    {
        wxASSERT_MSG( (flags & wxSOUND_LOOP) == 0 ||
                      (flags & wxSOUND_ASYNC) != 0,
                     _T("sound can only be looped asynchronously") );
        return DoPlay(flags);
    }
#if WXWIN_COMPATIBILITY_2_4
    wxDEPRECATED( bool Play(bool async, bool looped = false) const );
#endif

    // Plays sound from filename:
    static bool Play(const wxString& filename, unsigned flags = wxSOUND_ASYNC);
    
protected:
    virtual bool DoPlay(unsigned flags) const = 0;
};

// ----------------------------------------------------------------------------
// wxSound class implementation
// ----------------------------------------------------------------------------

#if defined(__WXMSW__)
    #include "wx/msw/sound.h"
#elif defined(__WXMAC__)
    #include "wx/mac/sound.h"
#elif defined(__WXPM__)
    #include "wx/os2/sound.h"
#elif defined(__UNIX__)
    #include "wx/unix/sound.h"
#endif

// ----------------------------------------------------------------------------
// wxSoundBase methods
// ----------------------------------------------------------------------------

inline bool wxSoundBase::Play(const wxString& filename, unsigned flags)
{
    wxSound snd(filename);
    return snd.IsOk() ? snd.Play(flags) : false;
}

#if WXWIN_COMPATIBILITY_2_4
inline bool wxSoundBase::Play(bool async, bool looped) const
{
    unsigned flags = 0;
    if (async) flags |= wxSOUND_ASYNC;
    if (looped) flags |= wxSOUND_LOOP | wxSOUND_ASYNC;
    return DoPlay(flags);
}
#endif

#endif // wxUSE_SOUND

#endif // _WX_SOUND_H_BASE_
