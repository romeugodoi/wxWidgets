/////////////////////////////////////////////////////////////////////////////
// Name:        unix/fswatcher_kqueue.cpp
// Purpose:     wxKqueueFileSystemWatcher
// Author:      Bartosz Bekier
// Created:     2009-05-26
// RCS-ID:      $Id$
// Copyright:   (c) 2009 Bartosz Bekier <bartosz.bekier@gmail.com>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_FSWATCHER

#include "wx/fswatcher.h"

#if wxUSE_FSWATCHER_KQUEUE

#include <sys/types.h>
#include <sys/event.h>
#include <wx/dynarray.h>
#include <wx/private/fswatcher.h>

// ============================================================================
// wxFSWatcherImpl implementation & helper wxFSWSourceHandler implementation
// ============================================================================

/**
 * Helper class encapsulating inotify mechanism
 */
class wxFSWatcherImplKqueue : public wxFSWatcherImpl
{
public:
    wxFSWatcherImplKqueue(wxFileSystemWatcherBase* watcher) :
        wxFSWatcherImpl(watcher),
        m_loop(NULL), m_source(wxEventLoopSource::INVALID_RESOURCE)
    {
        m_handler = new wxFSWSourceHandler(this);
    }

    ~wxFSWatcherImplKqueue()
    {
        // we close kqueue only if initialized before
        if (IsOk())
        {
            Close();
        }

        delete m_handler;
    }

    bool Init()
    {
        wxCHECK_MSG( !m_source.IsOk(), false,
                    "Kqueue appears to be already initialized" );

        int fd = kqueue();
        if (fd == -1)
        {
            wxLogSysError(_("Unable to create kqueue instance"));
            m_source.SetResource(wxEventLoopSource::INVALID_RESOURCE);
            return false;
        }

        m_source.SetResource(fd);
        return RegisterSource();
    }

    bool Close()
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );
        wxCHECK_MSG( m_loop, false,
                    "m_loop shouldn't be null if kqueue is initialized" );

        // ignore errors
        (void) UnregisterSource();

        int ret = close(m_source.GetResource());
        if (ret == -1)
        {
            wxLogSysError(_("Unable to close kqueue instance"));
        }
        m_source.SetResource(wxEventLoopSource::INVALID_RESOURCE);

        return ret != -1;
    }

    virtual bool DoAdd(wxSharedPtr<wxFSWatchEntryKq> watch)
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );

        struct kevent event;
        int action = EV_ADD | EV_ENABLE | EV_CLEAR | EV_ERROR;
        int flags = Watcher2NativeFlags(watch->GetFlags());
        EV_SET( &event, watch->GetFileDescriptor(), EVFILT_VNODE, action,
                flags, 0, watch.get() );

        // TODO more error conditions according to man
        // TODO best deal with the error here
        int ret = kevent(m_source.GetResource(), &event, 1, NULL, 0, NULL);
        if (ret == -1)
        {
            wxLogSysError(_("Unable to add kqueue watch"));
            return false;
        }

        return true;
    }

    virtual bool DoRemove(wxSharedPtr<wxFSWatchEntryKq> watch)
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );

        // TODO more error conditions according to man
        // XXX closing file descriptor removes the watch. The logic resides in
        // the watch which is not nice, but effective and simple
        bool ret = watch->Close();
        if (ret == -1)
        {
            wxLogSysError(_("Unable to remove kqueue watch"));
            return false;
        }

        return true;
    }

    virtual bool RemoveAll()
    {
        wxFSWatchEntries::iterator it = m_watches.begin();
        for ( ; it != m_watches.end(); ++it )
        {
            (void) DoRemove(it->second);
        }
        m_watches.clear();
        return true;
    }

    // return true if there was no error, false on error
    bool ReadEvents()
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );

        // read events
        do 
        {
            struct kevent event;
            struct timespec timeout = {0, 0};
            int ret = kevent(m_source.GetResource(), NULL, 0, &event, 1,
                             &timeout);
            if (ret == -1)
            {
                wxLogSysError(_("Unable to get events from kqueue"));
                return false;
            } 
            else if (ret == 0)
            {
                return true;
            }

            // we have event, so process it
            ProcessNativeEvent(event);
        } 
        while (true); 

        // when ret>0 we still have events, when ret<=0 we return
        wxFAIL_MSG( "Never reached" );
        return true;
    }

    bool IsOk()
    {
        return m_source.IsOk();
    }

    wxEventLoopSource GetSource() const
    {
        return m_source;
    }

protected:
    bool RegisterSource()
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );
        wxCHECK_MSG( m_loop == NULL, false, "Event loop should be NULL");

        m_loop = wxEventLoopBase::GetActive();
        wxCHECK_MSG( m_loop, false,
                    "wxFileSystemWatcher requires an active event loop" );

        return m_loop->AddSource(m_source, m_handler, wxEVENT_SOURCE_INPUT);
    }

    bool UnregisterSource()
    {
        wxCHECK_MSG( m_source.IsOk(), false,
                    "Kqueue not initialized or invalid kqueue descriptor" );
        wxCHECK_MSG( m_loop, false,
                    "m_loop shouldn't be null if kqueue is initialized" );

        bool ret = m_loop->RemoveSource(m_source);
        m_loop = NULL;
        return ret;
    }

    // returns all new dirs/files present in the immediate level of the dir
    // pointed by watch.GetPath(). "new" means created between the last time
    // the state of watch was computed and now
    void FindChanges(wxFSWatchEntryKq& watch, wxArrayString& changedFiles,
                      wxArrayInt& changedFlags)
    {
        wxFSWatchEntryKq::wxDirState old = watch.GetLastState();
        watch.RefreshState();
        wxFSWatchEntryKq::wxDirState curr = watch.GetLastState();    

        // iterate over old/curr file lists and compute changes
        wxArrayString::iterator oit = old.files.begin();
        wxArrayString::iterator cit = curr.files.begin();
        for ( ; oit != old.files.end() && cit != curr.files.end(); )
        {
            if ( *cit == *oit )
            {
                ++cit;
                ++oit;
            }
            else if ( *cit <= *oit )
            {
                changedFiles.push_back(*cit);
                changedFlags.push_back(wxFSW_EVENT_CREATE);
                ++cit;
            }
            else // ( *cit > *oit )
            {   
                changedFiles.push_back(*oit);
                changedFlags.push_back(wxFSW_EVENT_DELETE);
                ++oit;
            }
        }

        // border conditions
        if ( oit == old.files.end() )
        {
            for ( ; cit != curr.files.end(); ++cit )
            {
                changedFiles.push_back( *cit );
                changedFlags.push_back(wxFSW_EVENT_CREATE);
            }
        }
        else if ( cit == curr.files.end() )
        {
            for ( ; oit != old.files.end(); ++oit )
            {
                changedFiles.push_back( *oit );
                changedFlags.push_back(wxFSW_EVENT_DELETE);
            }
        }

        wxASSERT( changedFiles.size() == changedFlags.size() );

#if 0
        wxLogTrace(wxTRACE_FSWATCHER, "Changed files:");
        wxArrayString::iterator it = changedFiles.begin();
        wxArrayInt::iterator it2 = changedFlags.begin();
        for ( ; it != changedFiles.end(); ++it, ++it2)
        {
            wxString action = (*it2 == wxFSW_EVENT_CREATE) ? 
                                "created" : "deleted";
            wxLogTrace(wxTRACE_FSWATCHER, wxString::Format("File: '%s' %s",
                        *it, action));
        }
#endif
    }

    void ProcessNativeEvent(const struct kevent& e)
    {
        wxASSERT_MSG(e.udata, "Null user data associated with kevent!");

        wxLogTrace(wxTRACE_FSWATCHER, "Event: ident=%d, filter=%d, flags=%u, "
                   "fflags=%u, data=%d, user_data=%p",
                   e.ident, e.filter, e.flags, e.fflags, e.data, e.udata);

        // for ease of use
        wxFSWatchEntryKq& w = *(static_cast<wxFSWatchEntry*>(e.udata));
        int nflags = e.fflags;

        // clear ignored flags
        nflags &= ~NOTE_REVOKE;

        // TODO ignore events we didn't ask for + refactor this cascade ifs
        // check for events
        while ( nflags )
        {
            // when monitoring dir, this means create/delete
            if ( nflags & NOTE_WRITE && wxDirExists(w.GetPath()) )
            {
                // NOTE_LINK is set when the dir was created, but we 
                // don't care - we look for new names in directory
                // regardless of type. Also, clear all this, because 
                // it cannot mean more by itself
                nflags &= ~(NOTE_WRITE | NOTE_ATTRIB | NOTE_LINK);

                wxArrayString changedFiles;
                wxArrayInt changedFlags;
                FindChanges(w, changedFiles, changedFlags);
                wxArrayString::iterator it = changedFiles.begin();
                wxArrayInt::iterator changeType = changedFlags.begin();
                for ( ; it != changedFiles.end(); ++it, ++changeType )
                {
                    wxFileName path;
                    if ( wxDirExists(*it) ) 
                    {
                        path = wxFileName::DirName(w.GetPath() + *it);
                    }
                    else
                    {
                        path = wxFileName::FileName(w.GetPath() + *it);
                    }
                    
                    wxFileSystemWatcherEvent event(*changeType, path, path);
                    SendEvent(event);
                }
            } 
            else if ( nflags & NOTE_RENAME )
            {
                // CHECK it'd be only possible to detect name if we had
                // parent files listing which we could confront with now and
                // still we couldn't be sure we have the right name...
                nflags &= ~NOTE_RENAME;
                wxFileSystemWatcherEvent event(wxFSW_EVENT_RENAME,
                                        w.GetPath(), wxFileName());
                SendEvent(event);
            }
            else if ( nflags & NOTE_WRITE || nflags & NOTE_EXTEND )
            {
                nflags &= ~(NOTE_WRITE | NOTE_EXTEND);
                wxFileSystemWatcherEvent event(wxFSW_EVENT_MODIFY,
                                        w.GetPath(), w.GetPath());
                SendEvent(event);
            }
            else if ( nflags & NOTE_DELETE )
            {
                nflags &= ~(NOTE_DELETE);
                wxFileSystemWatcherEvent event(wxFSW_EVENT_DELETE,
                                        w.GetPath(), w.GetPath());
                SendEvent(event);
            }
            else if ( nflags & NOTE_ATTRIB )
            {
                nflags &= ~(NOTE_ATTRIB);
                wxFileSystemWatcherEvent event(wxFSW_EVENT_ACCESS,
                                        w.GetPath(), w.GetPath());
                SendEvent(event);
            }

            // clear any flags that won't mean anything by themselves
            nflags &= ~(NOTE_LINK);
        }
    }

    void SendEvent(wxFileSystemWatcherEvent& evt)
    {
        m_watcher->GetOwner()->ProcessEvent(evt);
    }

    static int Watcher2NativeFlags(int flags)
    {
        // FIXME this needs a bit of thinking, quick impl for now
        return NOTE_DELETE | NOTE_WRITE | NOTE_EXTEND |
               NOTE_ATTRIB | NOTE_LINK | NOTE_RENAME |
               NOTE_REVOKE;
    }

    wxFSWSourceHandler* m_handler;        // handler for kqueue event source
    wxEventLoopBase* m_loop;              // event loop we have registered with
    wxEventLoopSource m_source;           // our event loop source
};


// once we get signaled to read, actuall event reading occurs
void wxFSWSourceHandler::OnReadWaiting()
{
    wxLogTrace(wxTRACE_FSWATCHER, "--- OnReadWaiting ---");
    m_service->ReadEvents();
}

void wxFSWSourceHandler::OnWriteWaiting()
{
    wxFAIL_MSG("We never write to kqueue descriptor.");
}

void wxFSWSourceHandler::OnExceptionWaiting()
{
    wxFAIL_MSG("We never receive exceptions on kqueue descriptor.");
}


// ============================================================================
// wxKqueueFileSystemWatcher implementation
// ============================================================================

wxKqueueFileSystemWatcher::wxKqueueFileSystemWatcher() :
    wxFileSystemWatcherBase()
{
    Init();
}

wxKqueueFileSystemWatcher::wxKqueueFileSystemWatcher(const wxFileName& path,
                                                     int events) :
    wxFileSystemWatcherBase()
{
    if (!Init())
    {
        if (m_service) 
        {
            delete m_service;
            m_service = NULL;
        }
        return;
    }

    Add(path, events);
}

wxKqueueFileSystemWatcher::~wxKqueueFileSystemWatcher()
{
}

bool wxKqueueFileSystemWatcher::Init()
{
    m_service = new wxFSWatcherImplKqueue(this);
    return m_service->Init();
}

#endif
#endif // wxUSE_FSWATCHER
