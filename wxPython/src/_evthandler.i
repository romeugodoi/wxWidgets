/////////////////////////////////////////////////////////////////////////////
// Name:        _evthandler.i
// Purpose:     SWIG interface for wxEventHandler
//
// Author:      Robin Dunn
//
// Created:     9-Aug-2003
// RCS-ID:      $Id$
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%newgroup

// wxEvtHandler: the base class for all objects handling wxWindows events
class wxEvtHandler : public wxObject {
public:
    wxEvtHandler();

    wxEvtHandler* GetNextHandler();
    wxEvtHandler* GetPreviousHandler();
    void SetNextHandler(wxEvtHandler* handler);
    void SetPreviousHandler(wxEvtHandler* handler);

    bool GetEvtHandlerEnabled();
    void SetEvtHandlerEnabled(bool enabled);


    // process an event right now
    bool ProcessEvent(wxEvent& event);

    // add an event to be processed later
    void AddPendingEvent(wxEvent& event);

    // process all pending events
    void ProcessPendingEvents();

    %extend {
        // Dynamic association of a member function handler with the event handler
        void Connect( int id, int lastId, int eventType, PyObject* func) {
            if (PyCallable_Check(func)) {
                self->Connect(id, lastId, eventType,
                          (wxObjectEventFunction) &wxPyCallback::EventThunker,
                          new wxPyCallback(func));
            }
            else if (func == Py_None) {
                self->Disconnect(id, lastId, eventType,
                                 (wxObjectEventFunction)
                                 &wxPyCallback::EventThunker);
            }
            else {
                PyErr_SetString(PyExc_TypeError, "Expected callable object or None.");
            }
        }

        bool Disconnect(int id, int lastId = -1,
                        wxEventType eventType = wxEVT_NULL) {
            return self->Disconnect(id, lastId, eventType,
                                   (wxObjectEventFunction)
                                    &wxPyCallback::EventThunker);
        }
    }

    %extend {
        void _setOORInfo(PyObject* _self) {
            if (_self && _self != Py_None) {
                self->SetClientObject(new wxPyOORClientData(_self));
            }
            else {
                wxPyOORClientData* data = (wxPyOORClientData*)self->GetClientObject();
                if (data) {
                    self->SetClientObject(NULL);  // This will delete it too
                }
            }
        }
    }

    %pythoncode {
        def Bind(self, event, handler, source=None, id=wx.ID_ANY, id2=wx.ID_ANY):
            """
            Bind an event to an event handler.

              event     One of the EVT_* objects that specifies the
                        type of event to bind,

              handler   A callable object to be invoked when the event
                        is delivered to self.  Pass None to disconnect an
                        event handler.

              source    Sometimes the event originates from a different window
                        than self, but you still want to catch it in self.  (For
                        example, a button event delivered to a frame.)  By
                        passing the source of the event, the event handling
                        system is able to differentiate between the same event
                        type from different controls.

              id,id2    Used for menu IDs or for event types that require a
                        range of IDs
            """
            if source is not None:
                id  = source.GetId()
            event.Bind(self, id, id2, handler)              

    }

    
};

//---------------------------------------------------------------------------
