///////////////////////////////////////////////////////////////////////////////
// Name:        wx/evtloop.h
// Purpose:     declares wxEventLoop class
// Author:      Vadim Zeitlin
// Modified by:
// Created:     01.06.01
// RCS-ID:      $Id$
// Copyright:   (c) 2001 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_EVTLOOP_H_
#define _WX_EVTLOOP_H_

#include "wx/event.h"
#include "wx/utils.h"

// ----------------------------------------------------------------------------
// wxEventLoopSource: source of i/o for wxEventLoop
// ----------------------------------------------------------------------------

#define wxTRACE_Event_Source "EventSource"

#if defined(__UNIX__) && wxUSE_CONSOLE_EVENTLOOP

// handler used to process events on event loop sources
class WXDLLIMPEXP_BASE wxEventLoopSourceHandler
{
public:
    // called when descriptor is available for non-blocking read
    virtual void OnReadWaiting() = 0;

    // called when descriptor is available  for non-blocking write
    virtual void OnWriteWaiting() = 0;

    // called when there is exception on descriptor
    virtual void OnExceptionWaiting() = 0;

    // virtual dtor for the base class
    virtual ~wxEventLoopSourceHandler() { }
};

// those flags describes what events should be reported
enum
{
    wxEVENT_SOURCE_INPUT = 0x01,
    wxEVENT_SOURCE_OUTPUT = 0x02,
    wxEVENT_SOURCE_EXCEPTION = 0x04,
    wxEVENT_SOURCE_ALL = wxEVENT_SOURCE_INPUT | wxEVENT_SOURCE_OUTPUT |
                        wxEVENT_SOURCE_EXCEPTION,
};

// This class is a simple wrapper for OS specific resources than can be a
// source of I/O. On Unix,for instance these are file descriptors.
//
// Instances of this class doesn't take resposibility of any resource you pass
// to them, I.E. you have to release them yourself.
//
// (CHECK: maybe it is actually better to release resources at the end, because
// otherwise the user has to manually remove all resources from wxEventLoop...
// OTOH sources are more likely to be used by internal code, not by client code)
// Another approach: trying do release resources in event loop destructor, and
// just silently pass if they were already freed.
class WXDLLIMPEXP_BASE wxEventLoopSource
{
public:
    typedef int Resource;
    enum
    {
        INVALID_RESOURCE = -1
    };

    // hashing function
    class Hash
    {
    public:
        unsigned long operator() (const wxEventLoopSource& src) const
        {
            // XXX a little unsafe, define platform dependand way
            return static_cast<long>(src.GetResource());
        }

        Hash& operator=(const Hash&) { return *this; }
    };

    // comparison operator
    class Equal
    {
    public:
        bool operator() (const wxEventLoopSource& a,
                const wxEventLoopSource& b) const
        {
            return a.GetResource() == b.GetResource();
        }

        Equal& operator=(const Equal&) { return *this; }
    };

    // empty ctor, beacuse we often store event sources as values
    wxEventLoopSource() : m_res(INVALID_RESOURCE) { }

    // ctor setting internal value to the os resource res
    wxEventLoopSource(int res) : m_res(res) { }

    // sets internal value to res
    void SetResource(int res)
    {
        m_res = res;
    }

    // returns associated resource
    Resource GetResource() const
    {
        return m_res;
    }

    bool IsOk() const
    {
        return m_res != INVALID_RESOURCE;
    }

protected:
    Resource m_res;
};

#endif


/*
    NOTE ABOUT wxEventLoopBase::YieldFor LOGIC
    ------------------------------------------

    The YieldFor() function helps to avoid re-entrancy problems and problems
    caused by out-of-order event processing
    (see "wxYield-like problems" and "wxProgressDialog+threading BUG" wx-dev threads).

    The logic behind YieldFor() is simple: it analyzes the queue of the native
    events generated by the underlying GUI toolkit and picks out and processes
    only those matching the given mask.

    It's important to note that YieldFor() is used to selectively process the
    events generated by the NATIVE toolkit.
    Events syntethized by wxWidgets code or by user code are instead selectively
    processed thanks to the logic built into wxEvtHandler::ProcessPendingEvents().
    In fact, when wxEvtHandler::ProcessPendingEvents gets called from inside a
    YieldFor() call, wxEventLoopBase::IsEventAllowedInsideYield is used to decide
    if the pending events for that event handler can be processed.
    If all the pending events associated with that event handler result as "not processable",
    the event handler "delays" itself calling wxEventLoopBase::DelayPendingEventHandler
    (so it's moved: m_handlersWithPendingEvents => m_handlersWithPendingDelayedEvents).
    Last, wxEventLoopBase::ProcessPendingEvents() before exiting moves the delayed
    event handlers back into the list of handlers with pending events
    (m_handlersWithPendingDelayedEvents => m_handlersWithPendingEvents) so that
    a later call to ProcessPendingEvents() (possibly outside the YieldFor() call)
    will process all pending events as usual.
*/

// ----------------------------------------------------------------------------
// wxEventLoopBase: interface for wxEventLoop
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_BASE wxEventLoopBase
{
public:
    // trivial, but needed (because of wxEventLoopBase) ctor
    wxEventLoopBase();

    // dtor
    virtual ~wxEventLoopBase() { }

    // use this to check whether the event loop was successfully created before
    // using it
    virtual bool IsOk() const { return true; }

    // returns true if this is the main loop
    bool IsMain() const;


    // dispatch&processing
    // -------------------

    // start the event loop, return the exit code when it is finished
    virtual int Run() = 0;

    // is this event loop running now?
    //
    // notice that even if this event loop hasn't terminated yet but has just
    // spawned a nested (e.g. modal) event loop, this would return false
    bool IsRunning() const;

    // exit from the loop with the given exit code
    virtual void Exit(int rc = 0) = 0;

    // return true if any events are available
    virtual bool Pending() const = 0;

    // dispatch a single event, return false if we should exit from the loop
    virtual bool Dispatch() = 0;

    // same as Dispatch() but doesn't wait for longer than the specified (in
    // ms) timeout, return true if an event was processed, false if we should
    // exit the loop or -1 if timeout expired
    virtual int DispatchTimeout(unsigned long timeout) = 0;

    // implement this to wake up the loop: usually done by posting a dummy event
    // to it (can be called from non main thread)
    virtual void WakeUp() = 0;

#if defined(__UNIX__) && wxUSE_CONSOLE_EVENTLOOP

    // adding/removing sources
    // -----------------------

    // adds source to be monitored for I/O events specified in flags. Upon an
    // event the appropriate method of handler will be called. The handler is
    // owned be the calling client and will not be freed in any case.
    // Returns true if the source was successfully added, false if it failed
    // (this may happen for example when this source is already monitored)
    virtual bool AddSource(const wxEventLoopSource& source,
                            wxEventLoopSourceHandler* handler, int flags)
    {
        wxCHECK_MSG( source.IsOk(), false, "Invalid source" );
        wxCHECK_MSG( handler, false, "Null handler" );

        wxEventLoopSourceHashMap::value_type val(source, handler);
        if (!m_sourceMap.insert(val).second)
        {
            wxFAIL_MSG( "Source already registered");
            return false;
        }

        return DoAddSource(source, handler, flags);
    }

    // removes the source from the list of monitored sources.
    // Returns true if the source was successfully removed, false otherwise
    virtual bool RemoveSource(const wxEventLoopSource& source)
    {
        wxCHECK_MSG( source.IsOk(), false, "Invalid source" );

        if (m_sourceMap.erase(source) != 1)
        {
            wxFAIL_MSG( "Source not registered" );
            return false;
        }

        return DoRemoveSource(source);
    }

#endif

    // idle handling
    // -------------

    // make sure that idle events are sent again
    virtual void WakeUpIdle();

        // this virtual function is called  when the application
        // becomes idle and normally just sends wxIdleEvent to all interested
        // parties
        //
        // it should return true if more idle events are needed, false if not
    virtual bool ProcessIdle();


    // Yield-related hooks
    // -------------------

        // process all currently pending events right now
        //
        // it is an error to call Yield() recursively unless the value of
        // onlyIfNeeded is true
        //
        // WARNING: this function is dangerous as it can lead to unexpected
        //          reentrancies (i.e. when called from an event handler it
        //          may result in calling the same event handler again), use
        //          with _extreme_ care or, better, don't use at all!
    bool Yield(bool onlyIfNeeded = false);
    virtual bool YieldFor(long eventsToProcess) = 0;

        // returns true if the main thread is inside a Yield() call
    virtual bool IsYielding() const
        { return m_isInsideYield; }

        // returns true if events of the given event category should be immediately
        // processed inside a wxApp::Yield() call or rather should be queued for
        // later processing by the main event loop
    virtual bool IsEventAllowedInsideYield(wxEventCategory cat) const
        { return (m_eventsToProcessInsideYield & cat) != 0; }

    // no SafeYield hooks since it uses wxWindow which is not available when wxUSE_GUI=0


    // active loop
    // -----------

    // return currently active (running) event loop, may be NULL
    static wxEventLoopBase *GetActive() { return ms_activeLoop; }

    // set currently active (running) event loop
    static void SetActive(wxEventLoopBase* loop);


protected:
    // this function should be called before the event loop terminates, whether
    // this happens normally (because of Exit() call) or abnormally (because of
    // an exception thrown from inside the loop)
    virtual void OnExit();

    // the pointer to currently active loop
    static wxEventLoopBase *ms_activeLoop;

    // YieldFor() helpers:
    bool m_isInsideYield;
    long m_eventsToProcessInsideYield;

#if defined(__UNIX__) && wxUSE_CONSOLE_EVENTLOOP
    virtual bool DoAddSource(const wxEventLoopSource&,
                             wxEventLoopSourceHandler*, int)
    {
        wxFAIL_MSG("not implemented");
        return false;
    }

    virtual bool DoRemoveSource(const wxEventLoopSource&)
    {
        wxFAIL_MSG("not implemented");
        return false;
    }

    WX_DECLARE_HASH_MAP(wxEventLoopSource, wxEventLoopSourceHandler*,
            wxEventLoopSource::Hash, wxEventLoopSource::Equal,
            wxEventLoopSourceHashMap);

    wxEventLoopSourceHashMap m_sourceMap;
#endif

    wxDECLARE_NO_COPY_CLASS(wxEventLoopBase);
};

#if defined(__WXMSW__) || defined(__WXMAC__) || defined(__WXDFB__) || defined(__UNIX__)

// this class can be used to implement a standard event loop logic using
// Pending() and Dispatch()
//
// it also handles idle processing automatically
class WXDLLIMPEXP_BASE wxEventLoopManual : public wxEventLoopBase
{
public:
    wxEventLoopManual();

    // enters a loop calling OnNextIteration(), Pending() and Dispatch() and
    // terminating when Exit() is called
    virtual int Run();

    // sets the "should exit" flag and wakes up the loop so that it terminates
    // soon
    virtual void Exit(int rc = 0);

protected:
    // may be overridden to perform some action at the start of each new event
    // loop iteration
    virtual void OnNextIteration() { }


    // the loop exit code
    int m_exitcode;

    // should we exit the loop?
    bool m_shouldExit;
};

#endif // platforms using "manual" loop

// we're moving away from old m_impl wxEventLoop model as otherwise the user
// code doesn't have access to platform-specific wxEventLoop methods and this
// can sometimes be very useful (e.g. under MSW this is necessary for
// integration with MFC) but currently this is done for MSW only, other ports
// should follow a.s.a.p.
#if defined(__WXPALMOS__)
    #include "wx/palmos/evtloop.h"
#elif defined(__WXMSW__)
    #include "wx/msw/evtloop.h"
#elif defined(__WXMAC__)
    #include "wx/osx/evtloop.h"
#elif defined(__WXCOCOA__)
    #include "wx/cocoa/evtloop.h"
#elif defined(__WXDFB__)
    #include "wx/dfb/evtloop.h"
#elif defined(__WXGTK20__)
    #include "wx/gtk/evtloop.h"
#else // other platform

#include "wx/stopwatch.h"   // for wxMilliClock_t

class WXDLLIMPEXP_FWD_CORE wxEventLoopImpl;

class WXDLLIMPEXP_CORE wxGUIEventLoop : public wxEventLoopBase
{
public:
    wxGUIEventLoop() { m_impl = NULL; }
    virtual ~wxGUIEventLoop();

    virtual int Run();
    virtual void Exit(int rc = 0);
    virtual bool Pending() const;
    virtual bool Dispatch();
    virtual int DispatchTimeout(unsigned long timeout)
    {
        // TODO: this is, of course, horribly inefficient and a proper wait with
        //       timeout should be implemented for all ports natively...
        const wxMilliClock_t timeEnd = wxGetLocalTimeMillis() + timeout;
        for ( ;; )
        {
            if ( Pending() )
                return Dispatch();

            if ( wxGetLocalTimeMillis() >= timeEnd )
                return -1;
        }
    }
    virtual void WakeUp() { }
    virtual bool YieldFor(long eventsToProcess);

protected:
    // the pointer to the port specific implementation class
    wxEventLoopImpl *m_impl;

    wxDECLARE_NO_COPY_CLASS(wxGUIEventLoop);
};

#endif // platforms

// also include the header defining wxConsoleEventLoop for Unix systems
#if defined(__UNIX__)
    #include "wx/unix/evtloop.h"
#endif

// we use a class rather than a typedef because wxEventLoop is forward-declared
// in many places
#if wxUSE_GUI
    class wxEventLoop : public wxGUIEventLoop { };
#else // !GUI
    // we can't define wxEventLoop differently in GUI and base libraries so use
    // a #define to still allow writing wxEventLoop in the user code
    #if wxUSE_CONSOLE_EVENTLOOP && (defined(__WXMSW__) || defined(__UNIX__))
        #define wxEventLoop wxConsoleEventLoop
    #else // we still must define it somehow for the code below...
        #define wxEventLoop wxEventLoopBase
    #endif
#endif

inline bool wxEventLoopBase::IsRunning() const { return GetActive() == this; }

#if wxUSE_GUI
// ----------------------------------------------------------------------------
// wxModalEventLoop
// ----------------------------------------------------------------------------

// this is a naive generic implementation which uses wxWindowDisabler to
// implement modality, we will surely need platform-specific implementations
// too, this generic implementation is here only temporarily to see how it
// works
class WXDLLIMPEXP_CORE wxModalEventLoop : public wxGUIEventLoop
{
public:
    wxModalEventLoop(wxWindow *winModal)
    {
        m_windowDisabler = new wxWindowDisabler(winModal);
    }

protected:
    virtual void OnExit()
    {
        delete m_windowDisabler;
        m_windowDisabler = NULL;

        wxGUIEventLoop::OnExit();
    }

private:
    wxWindowDisabler *m_windowDisabler;
};

#endif //wxUSE_GUI

// ----------------------------------------------------------------------------
// wxEventLoopActivator: helper class for wxEventLoop implementations
// ----------------------------------------------------------------------------

// this object sets the wxEventLoop given to the ctor as the currently active
// one and unsets it in its dtor, this is especially useful in presence of
// exceptions but is more tidy even when we don't use them
class wxEventLoopActivator
{
public:
    wxEventLoopActivator(wxEventLoopBase *evtLoop)
    {
        m_evtLoopOld = wxEventLoopBase::GetActive();
        wxEventLoopBase::SetActive(evtLoop);
    }

    ~wxEventLoopActivator()
    {
        // restore the previously active event loop
        wxEventLoopBase::SetActive(m_evtLoopOld);
    }

private:
    wxEventLoopBase *m_evtLoopOld;
};

#if wxUSE_CONSOLE_EVENTLOOP

class wxEventLoopGuarantor
{
public:
    wxEventLoopGuarantor()
    {
        m_evtLoopNew = NULL;
        if (!wxEventLoop::GetActive())
        {
            m_evtLoopNew = new wxEventLoop;
            wxEventLoop::SetActive(m_evtLoopNew);
        }
    }

    ~wxEventLoopGuarantor()
    {
        if (m_evtLoopNew)
        {
            wxEventLoop::SetActive(NULL);
            delete m_evtLoopNew;
        }
    }

private:
    wxEventLoop *m_evtLoopNew;
};

#endif // wxUSE_CONSOLE_EVENTLOOP

#endif // _WX_EVTLOOP_H_
