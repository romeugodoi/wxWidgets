/////////////////////////////////////////////////////////////////////////////
// Name:        helpers.cpp
// Purpose:     Helper functions/classes for the wxPython extension module
//
// Author:      Robin Dunn
//
// Created:     7/1/97
// RCS-ID:      $Id$
// Copyright:   (c) 1998 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  // get the correct definition of NULL

#undef DEBUG
#include <Python.h>
#include "helpers.h"

#ifdef __WXMSW__
#include <wx/msw/private.h>
#include <wx/msw/winundef.h>
#include <wx/msw/msvcrt.h>
#endif

#ifdef __WXGTK__
#include <gtk/gtk.h>
#include <gdk/gdkprivate.h>
#include <wx/gtk/win_gtk.h>
#endif


//----------------------------------------------------------------------

#ifdef __WXGTK__
int  WXDLLEXPORT wxEntryStart( int& argc, char** argv );
#else
int  WXDLLEXPORT wxEntryStart( int argc, char** argv );
#endif
int  WXDLLEXPORT wxEntryInitGui();
void WXDLLEXPORT wxEntryCleanup();

wxPyApp* wxPythonApp = NULL;  // Global instance of application object


#ifdef WXP_WITH_THREAD
struct wxPyThreadState {
    unsigned long  tid;
    PyThreadState* tstate;

    wxPyThreadState(unsigned long _tid=0, PyThreadState* _tstate=NULL)
        : tid(_tid), tstate(_tstate) {}
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(wxPyThreadState, wxPyThreadStateArray);
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxPyThreadStateArray);

wxPyThreadStateArray* wxPyTStates = NULL;
wxMutex*              wxPyTMutex = NULL;
#endif


#ifdef __WXMSW__             // If building for win32...
//----------------------------------------------------------------------
// This gets run when the DLL is loaded.  We just need to save a handle.
//----------------------------------------------------------------------

BOOL WINAPI DllMain(
    HINSTANCE   hinstDLL,    // handle to DLL module
    DWORD       fdwReason,   // reason for calling function
    LPVOID      lpvReserved  // reserved
   )
{
    wxSetInstance(hinstDLL);
    return 1;
}
#endif

//----------------------------------------------------------------------
// Classes for implementing the wxp main application shell.
//----------------------------------------------------------------------


wxPyApp::wxPyApp() {
//    printf("**** ctor\n");
}

wxPyApp::~wxPyApp() {
//    printf("**** dtor\n");
}


// This one isn't acutally called...  See __wxStart()
bool wxPyApp::OnInit() {
    return FALSE;
}


int  wxPyApp::MainLoop() {
    int retval = 0;

    DeletePendingObjects();
    bool initialized = wxTopLevelWindows.GetCount() != 0;
#ifdef __WXGTK__
    m_initialized = initialized;
#endif

    if (initialized) {
        retval = wxApp::MainLoop();
        OnExit();
    }
    return retval;
}



//---------------------------------------------------------------------
//----------------------------------------------------------------------


// This is where we pick up the first part of the wxEntry functionality...
// The rest is in __wxStart and  __wxCleanup.  This function is called when
// wxcmodule is imported.  (Before there is a wxApp object.)
void __wxPreStart()
{

#ifdef __WXMSW__
//    wxCrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef WXP_WITH_THREAD
    PyEval_InitThreads();
    wxPyTStates = new wxPyThreadStateArray;
    wxPyTMutex = new wxMutex;
#endif

    // Bail out if there is already windows created.  This means that the
    // toolkit has already been initialized, as in embedding wxPython in
    // a C++ wxWindows app.
    if (wxTopLevelWindows.Number() > 0)
        return;


    int argc = 0;
    char** argv = NULL;
    PyObject* sysargv = PySys_GetObject("argv");
    if (sysargv != NULL) {
        argc = PyList_Size(sysargv);
        argv = new char*[argc+1];
        int x;
        for(x=0; x<argc; x++)
            argv[x] = copystring(PyString_AsString(PyList_GetItem(sysargv, x)));
        argv[argc] = NULL;
    }

    wxEntryStart(argc, argv);
    delete [] argv;
}



// Start the user application, user App's OnInit method is a parameter here
PyObject* __wxStart(PyObject* /* self */, PyObject* args)
{
    PyObject*   onInitFunc = NULL;
    PyObject*   arglist;
    PyObject*   result;
    long        bResult;

    if (!PyArg_ParseTuple(args, "O", &onInitFunc))
        return NULL;

#if 0  // Try it out without this check, see how it does...
    if (wxTopLevelWindows.Number() > 0) {
        PyErr_SetString(PyExc_TypeError, "Only 1 wxApp per process!");
        return NULL;
    }
#endif

    // This is the next part of the wxEntry functionality...
    int argc = 0;
    char** argv = NULL;
    PyObject* sysargv = PySys_GetObject("argv");
    if (sysargv != NULL) {
        argc = PyList_Size(sysargv);
        argv = new char*[argc+1];
        int x;
        for(x=0; x<argc; x++)
            argv[x] = copystring(PyString_AsString(PyList_GetItem(sysargv, x)));
        argv[argc] = NULL;
    }
    wxPythonApp->argc = argc;
    wxPythonApp->argv = argv;

    wxEntryInitGui();

    // Call the Python App's OnInit function
    arglist = PyTuple_New(0);
    result = PyEval_CallObject(onInitFunc, arglist);
    if (!result) {      // an exception was raised.
        return NULL;
    }

    if (! PyInt_Check(result)) {
        PyErr_SetString(PyExc_TypeError, "OnInit should return a boolean value");
        return NULL;
    }
    bResult = PyInt_AS_LONG(result);
    if (! bResult) {
        PyErr_SetString(PyExc_SystemExit, "OnInit returned FALSE, exiting...");
        return NULL;
    }

#ifdef __WXGTK__
    wxTheApp->m_initialized = (wxTopLevelWindows.GetCount() > 0);
#endif

    Py_INCREF(Py_None);
    return Py_None;
}


void __wxCleanup() {
    wxEntryCleanup();
    delete wxPyTMutex;
    wxPyTMutex = NULL;
    wxPyTStates->Empty();
    delete wxPyTStates;
    wxPyTStates = NULL;
}



static PyObject* wxPython_dict = NULL;
static PyObject* wxPyPtrTypeMap = NULL;

PyObject* __wxSetDictionary(PyObject* /* self */, PyObject* args)
{

    if (!PyArg_ParseTuple(args, "O", &wxPython_dict))
        return NULL;

    if (!PyDict_Check(wxPython_dict)) {
        PyErr_SetString(PyExc_TypeError, "_wxSetDictionary must have dictionary object!");
        return NULL;
    }

    if (! wxPyPtrTypeMap)
        wxPyPtrTypeMap = PyDict_New();
    PyDict_SetItemString(wxPython_dict, "__wxPyPtrTypeMap", wxPyPtrTypeMap);


#ifdef __WXMOTIF__
#define wxPlatform "__WXMOTIF__"
#endif
#ifdef __WXQT__
#define wxPlatform "__WXQT__"
#endif
#ifdef __WXGTK__
#define wxPlatform "__WXGTK__"
#endif
#if defined(__WIN32__) || defined(__WXMSW__)
#define wxPlatform "__WXMSW__"
#endif
#ifdef __WXMAC__
#define wxPlatform "__WXMAC__"
#endif

    PyDict_SetItemString(wxPython_dict, "wxPlatform", PyString_FromString(wxPlatform));

    Py_INCREF(Py_None);
    return Py_None;
}


//---------------------------------------------------------------------------
// Stuff used by OOR to find the right wxPython class type to return and to
// build it.


// The pointer type map is used when the "pointer" type name generated by SWIG
// is not the same as the shadow class name, for example wxPyTreeCtrl
// vs. wxTreeCtrl.  It needs to be referenced in Python as well as from C++,
// so we'll just make it a Python dictionary in the wx module's namespace.
void wxPyPtrTypeMap_Add(const char* commonName, const char* ptrName) {
    if (! wxPyPtrTypeMap)
        wxPyPtrTypeMap = PyDict_New();
    PyDict_SetItemString(wxPyPtrTypeMap,
                         (char*)commonName,
                         PyString_FromString((char*)ptrName));
}



PyObject* wxPyClassExists(const char* className) {

    if (!className)
        return NULL;

    char    buff[64];               // should always be big enough...

    sprintf(buff, "%sPtr", className);
    PyObject* classobj = PyDict_GetItemString(wxPython_dict, buff);

    return classobj;  // returns NULL if not found
}


PyObject*  wxPyMake_wxObject(wxObject* source, bool checkEvtHandler) {
    PyObject* target = NULL;
    bool      isEvtHandler = FALSE;

    if (source) {
        // If it's derived from wxEvtHandler then there may
        // already be a pointer to a Python object that we can use
        // in the OOR data.
        if (checkEvtHandler && wxIsKindOf(source, wxEvtHandler)) {
            isEvtHandler = TRUE;
            wxEvtHandler* eh = (wxEvtHandler*)source;
            wxPyClientData* data = (wxPyClientData*)eh->GetClientObject();
            if (data) {
                target = data->m_obj;
                Py_INCREF(target);
            }
        }

        if (! target) {
            // Otherwise make it the old fashioned way by making a
            // new shadow object and putting this pointer in it.
            wxClassInfo* info = source->GetClassInfo();
            wxChar*      name = (wxChar*)info->GetClassName();
            PyObject*    klass = wxPyClassExists(name);
            while (info && !klass) {
                name = (wxChar*)info->GetBaseClassName1();
                info = wxClassInfo::FindClass(name);
                klass = wxPyClassExists(name);
            }
            if (info) {
                target = wxPyConstructObject(source, name, klass, FALSE);
                if (target && isEvtHandler)
                    ((wxEvtHandler*)source)->SetClientObject(new wxPyClientData(target));
            } else {
                wxString msg("wxPython class not found for ");
                msg += source->GetClassInfo()->GetClassName();
                PyErr_SetString(PyExc_NameError, msg.c_str());
                target = NULL;
            }
        }
    } else {  // source was NULL so return None.
        Py_INCREF(Py_None); target = Py_None;
    }
    return target;
}


PyObject*  wxPyMake_wxSizer(wxSizer* source) {
    PyObject* target = NULL;

    if (source && wxIsKindOf(source, wxSizer)) {
        // If it's derived from wxSizer then there may
        // already be a pointer to a Python object that we can use
        // in the OOR data.
        wxSizer* sz = (wxSizer*)source;
        wxPyClientData* data = (wxPyClientData*)sz->GetClientObject();
        if (data) {
            target = data->m_obj;
            Py_INCREF(target);
        }
    }
    if (! target) {
        target = wxPyMake_wxObject(source, FALSE);
        if (target != Py_None)
            ((wxSizer*)source)->SetClientObject(new wxPyClientData(target));
    }
    return target;
}



//---------------------------------------------------------------------------

PyObject* wxPyConstructObject(void* ptr,
                              const char* className,
                              PyObject* klass,
                              int setThisOwn) {

    PyObject* obj;
    PyObject* arg;
    PyObject* item;
    char      swigptr[64];      // should always be big enough...
    char      buff[64];

    if ((item = PyDict_GetItemString(wxPyPtrTypeMap, (char*)className)) != NULL) {
        className = PyString_AsString(item);
    }
    sprintf(buff, "_%s_p", className);
    SWIG_MakePtr(swigptr, ptr, buff);

    arg = Py_BuildValue("(s)", swigptr);
    obj = PyInstance_New(klass, arg, NULL);
    Py_DECREF(arg);

    if (setThisOwn) {
        PyObject* one = PyInt_FromLong(1);
        PyObject_SetAttrString(obj, "thisown", one);
        Py_DECREF(one);
    }

    return obj;
}


PyObject* wxPyConstructObject(void* ptr,
                              const char* className,
                              int setThisOwn) {
    PyObject* obj;

    if (!ptr) {
        Py_INCREF(Py_None);
        return Py_None;
    }

    char    buff[64];               // should always be big enough...
    sprintf(buff, "%sPtr", className);

    wxASSERT_MSG(wxPython_dict, "wxPython_dict is not set yet!!");

    PyObject* classobj = PyDict_GetItemString(wxPython_dict, buff);
    if (! classobj) {
        char temp[128];
        sprintf(temp,
                "*** Unknown class name %s, tell Robin about it please ***",
                buff);
        obj = PyString_FromString(temp);
        return obj;
    }

    return wxPyConstructObject(ptr, className, classobj, setThisOwn);
}

//---------------------------------------------------------------------------

// TODO:  This should really be wxThread::GetCurrentId(), and I will do so
//        after I make a quick 2.3.2.1 release.
#ifdef WXP_WITH_THREAD
#ifdef __WXGTK__  // does wxGTK always use pthreads?
#include <unistd.h>
#include <pthread.h>
#endif
inline
unsigned long wxPyGetCurrentThreadId() {
#ifdef __WXMSW__
    return (unsigned long)::GetCurrentThreadId();
#endif
#ifdef __WXGTK__  // does wxGTK always use pthreads?
    return (unsigned long)pthread_self();
#endif
#ifdef __WXMAC__
    ThreadID current ;
    MacGetCurrentThread( &current ) ;
    return (unsigned long)current;
#endif
}



static
PyThreadState* wxPyGetThreadState() {
    unsigned long ctid = wxPyGetCurrentThreadId();
    PyThreadState* tstate = NULL;

    wxPyTMutex->Lock();
    for(size_t i=0; i < wxPyTStates->GetCount(); i++) {
        wxPyThreadState& info = wxPyTStates->Item(i);
        if (info.tid == ctid) {
            tstate = info.tstate;
            break;
        }
    }
    wxPyTMutex->Unlock();
    wxASSERT_MSG(tstate, "PyThreadState should not be NULL!");
    return tstate;
}

static
void wxPySaveThreadState(PyThreadState* tstate) {
    unsigned long ctid = wxPyGetCurrentThreadId();
    wxPyTMutex->Lock();
    for(size_t i=0; i < wxPyTStates->GetCount(); i++) {
        wxPyThreadState& info = wxPyTStates->Item(i);
        if (info.tid == ctid) {
            info.tstate = tstate;
            wxPyTMutex->Unlock();
            return;
        }
    }
    // not found, so add it...
    wxPyTStates->Add(new wxPyThreadState(ctid, tstate));
    wxPyTMutex->Unlock();
}

#endif


// Calls from Python to wxWindows code are wrapped in calls to these
// functions:

PyThreadState* wxPyBeginAllowThreads() {
#ifdef WXP_WITH_THREAD
    PyThreadState* saved = PyEval_SaveThread();  // Py_BEGIN_ALLOW_THREADS;
    wxPySaveThreadState(saved);
    return saved;
#else
    return NULL;
#endif
}

void wxPyEndAllowThreads(PyThreadState* saved) {
#ifdef WXP_WITH_THREAD
    PyEval_RestoreThread(saved);   // Py_END_ALLOW_THREADS;
#endif
}



// Calls from wxWindows back to Python code, or even any PyObject
// manipulations, PyDECREF's and etc. are wrapped in calls to these functions:

void wxPyBeginBlockThreads() {
#ifdef WXP_WITH_THREAD
    PyThreadState* tstate = wxPyGetThreadState();
    PyEval_RestoreThread(tstate);
#endif
}


void wxPyEndBlockThreads() {
#ifdef WXP_WITH_THREAD
    PyThreadState* tstate = PyEval_SaveThread();
    // Is there any need to save it again?
#endif
}


//---------------------------------------------------------------------------

IMPLEMENT_ABSTRACT_CLASS(wxPyCallback, wxObject);

wxPyCallback::wxPyCallback(PyObject* func) {
    m_func = func;
    Py_INCREF(m_func);
}

wxPyCallback::wxPyCallback(const wxPyCallback& other) {
    m_func = other.m_func;
    Py_INCREF(m_func);
}

wxPyCallback::~wxPyCallback() {
    wxPyBeginBlockThreads();
    Py_DECREF(m_func);
    wxPyEndBlockThreads();
}



// This function is used for all events destined for Python event handlers.
void wxPyCallback::EventThunker(wxEvent& event) {
    wxPyCallback*   cb = (wxPyCallback*)event.m_callbackUserData;
    PyObject*       func = cb->m_func;
    PyObject*       result;
    PyObject*       arg;
    PyObject*       tuple;


    wxPyBeginBlockThreads();
    wxString className = event.GetClassInfo()->GetClassName();

    if (className == "wxPyEvent")
        arg = ((wxPyEvent*)&event)->GetSelf();
    else if (className == "wxPyCommandEvent")
        arg = ((wxPyCommandEvent*)&event)->GetSelf();
    else
        arg = wxPyConstructObject((void*)&event, className);

    tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, arg);
    result = PyEval_CallObject(func, tuple);
    Py_DECREF(tuple);
    if (result) {
        Py_DECREF(result);
        PyErr_Clear();       // Just in case...
    } else {
        PyErr_Print();
    }
    wxPyEndBlockThreads();
}


//----------------------------------------------------------------------

wxPyCallbackHelper::wxPyCallbackHelper(const wxPyCallbackHelper& other) {
      m_lastFound = NULL;
      m_self = other.m_self;
      m_class = other.m_class;
      if (m_self) {
          Py_INCREF(m_self);
          Py_INCREF(m_class);
      }
}


void wxPyCallbackHelper::setSelf(PyObject* self, PyObject* klass, int incref) {
    m_self = self;
    m_class = klass;
    m_incRef = incref;
    if (incref) {
        Py_INCREF(m_self);
        Py_INCREF(m_class);
    }
}


#if PYTHON_API_VERSION >= 1011

// Prior to Python 2.2 PyMethod_GetClass returned the class object
// in which the method was defined.  Starting with 2.2 it returns
// "class that asked for the method" which seems totally bogus to me
// but apprently if fixes some obscure problem waiting to happen in
// Python.  Since the API was not documented Guido and the gang felt
// safe in changing it.  Needless to say that totally screwed up the
// logic below in wxPyCallbackHelper::findCallback, hence this icky
// code to find the class where the method is actuallt defined...

static
PyObject* PyFindClassWithAttr(PyObject *klass, PyObject *name)
{
    int i, n;

    if (PyType_Check(klass)) {      // new style classes
        // This code is borrowed/adapted from _PyType_Lookup in typeobject.c
        // (TODO: This part is not tested yet, so I'm not sure it is correct...)
        PyTypeObject* type = (PyTypeObject*)klass;
        PyObject *mro, *res, *base, *dict;
        /* Look in tp_dict of types in MRO */
        mro = type->tp_mro;
        assert(PyTuple_Check(mro));
        n = PyTuple_GET_SIZE(mro);
        for (i = 0; i < n; i++) {
            base = PyTuple_GET_ITEM(mro, i);
            if (PyClass_Check(base))
                dict = ((PyClassObject *)base)->cl_dict;
            else {
                assert(PyType_Check(base));
                dict = ((PyTypeObject *)base)->tp_dict;
            }
            assert(dict && PyDict_Check(dict));
            res = PyDict_GetItem(dict, name);
            if (res != NULL)
                return base;
        }
        return NULL;
    }

    else if (PyClass_Check(klass)) { // old style classes
        // This code is borrowed/adapted from class_lookup in classobject.c
        PyClassObject* cp = (PyClassObject*)klass;
        PyObject *value = PyDict_GetItem(cp->cl_dict, name);
        if (value != NULL) {
            return (PyObject*)cp;
        }
        n = PyTuple_Size(cp->cl_bases);
        for (i = 0; i < n; i++) {
            PyObject* base = PyTuple_GetItem(cp->cl_bases, i);
            PyObject *v = PyFindClassWithAttr(base, name);
            if (v != NULL)
                return v;
        }
        return NULL;
    }
}
#endif


static
PyObject* PyMethod_GetDefiningClass(PyObject* method, const char* name)
{
    PyObject* mgc = PyMethod_GET_CLASS(method);

#if PYTHON_API_VERSION <= 1010    // prior to Python 2.2, the easy way
    return mgc;
#else                             // 2.2 and after, the hard way...

    PyObject* nameo = PyString_FromString(name);
    PyObject* klass = PyFindClassWithAttr(mgc, nameo);
    Py_DECREF(nameo);
    return klass;
#endif
}



bool wxPyCallbackHelper::findCallback(const char* name) const {
    wxPyCallbackHelper* self = (wxPyCallbackHelper*)this; // cast away const
    self->m_lastFound = NULL;

    // If the object (m_self) has an attibute of the given name...
    if (m_self && PyObject_HasAttrString(m_self, (char*)name)) {
        PyObject *method, *klass;
        method = PyObject_GetAttrString(m_self, (char*)name);

        // ...and if that attribute is a method, and if that method's class is
        // not from a base class...
        if (PyMethod_Check(method) &&
            (klass = PyMethod_GetDefiningClass(method, (char*)name)) != NULL &&
            ((klass == m_class) || PyClass_IsSubclass(klass, m_class))) {

            // ...then we'll save a pointer to the method so callCallback can call it.
            self->m_lastFound = method;
        }
        else {
            Py_DECREF(method);
        }
    }
    return m_lastFound != NULL;
}


int wxPyCallbackHelper::callCallback(PyObject* argTuple) const {
    PyObject*   result;
    int         retval = FALSE;

    result = callCallbackObj(argTuple);
    if (result) {                       // Assumes an integer return type...
        retval = PyInt_AsLong(result);
        Py_DECREF(result);
        PyErr_Clear();                  // forget about it if it's not...
    }
    return retval;
}

// Invoke the Python callable object, returning the raw PyObject return
// value.  Caller should DECREF the return value and also call PyEval_SaveThread.
PyObject* wxPyCallbackHelper::callCallbackObj(PyObject* argTuple) const {
    PyObject* result;

    // Save a copy of the pointer in case the callback generates another
    // callback.  In that case m_lastFound will have a different value when
    // it gets back here...
    PyObject* method = m_lastFound;

    result = PyEval_CallObject(method, argTuple);
    Py_DECREF(argTuple);
    Py_DECREF(method);
    if (!result) {
        PyErr_Print();
    }
    return result;
}


void wxPyCBH_setCallbackInfo(wxPyCallbackHelper& cbh, PyObject* self, PyObject* klass, int incref) {
    cbh.setSelf(self, klass, incref);
}

bool wxPyCBH_findCallback(const wxPyCallbackHelper& cbh, const char* name) {
    return cbh.findCallback(name);
}

int  wxPyCBH_callCallback(const wxPyCallbackHelper& cbh, PyObject* argTuple) {
    return cbh.callCallback(argTuple);
}

PyObject* wxPyCBH_callCallbackObj(const wxPyCallbackHelper& cbh, PyObject* argTuple) {
    return cbh.callCallbackObj(argTuple);
}


void wxPyCBH_delete(wxPyCallbackHelper* cbh) {
    if (cbh->m_incRef) {
        wxPyBeginBlockThreads();
        Py_XDECREF(cbh->m_self);
        Py_XDECREF(cbh->m_class);
        wxPyEndBlockThreads();
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// These event classes can be derived from in Python and passed through the event
// system without losing anything.  They do this by keeping a reference to
// themselves and some special case handling in wxPyCallback::EventThunker.


wxPyEvtSelfRef::wxPyEvtSelfRef() {
    //m_self = Py_None;         // **** We don't do normal ref counting to prevent
    //Py_INCREF(m_self);        //      circular loops...
    m_cloned = FALSE;
}

wxPyEvtSelfRef::~wxPyEvtSelfRef() {
    wxPyBeginBlockThreads();
    if (m_cloned)
        Py_DECREF(m_self);
    wxPyEndBlockThreads();
}

void wxPyEvtSelfRef::SetSelf(PyObject* self, bool clone) {
    wxPyBeginBlockThreads();
    if (m_cloned)
        Py_DECREF(m_self);
    m_self = self;
    if (clone) {
        Py_INCREF(m_self);
        m_cloned = TRUE;
    }
    wxPyEndBlockThreads();
}

PyObject* wxPyEvtSelfRef::GetSelf() const {
    Py_INCREF(m_self);
    return m_self;
}


IMPLEMENT_ABSTRACT_CLASS(wxPyEvent, wxEvent);
IMPLEMENT_ABSTRACT_CLASS(wxPyCommandEvent, wxCommandEvent);


wxPyEvent::wxPyEvent(int id)
    : wxEvent(id) {
}


wxPyEvent::wxPyEvent(const wxPyEvent& evt)
    : wxEvent(evt)
{
    SetSelf(evt.m_self, TRUE);
}


wxPyEvent::~wxPyEvent() {
}


wxPyCommandEvent::wxPyCommandEvent(wxEventType commandType, int id)
    : wxCommandEvent(commandType, id) {
}


wxPyCommandEvent::wxPyCommandEvent(const wxPyCommandEvent& evt)
    : wxCommandEvent(evt)
{
    SetSelf(evt.m_self, TRUE);
}


wxPyCommandEvent::~wxPyCommandEvent() {
}




//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


wxPyTimer::wxPyTimer(PyObject* callback) {
    func = callback;
    Py_INCREF(func);
}

wxPyTimer::~wxPyTimer() {
    wxPyBeginBlockThreads();
    Py_DECREF(func);
    wxPyEndBlockThreads();
}

void wxPyTimer::Notify() {
    if (!func || func == Py_None) {
        wxTimer::Notify();
    }
    else {
        wxPyBeginBlockThreads();

        PyObject*   result;
        PyObject*   args = Py_BuildValue("()");

        result = PyEval_CallObject(func, args);
        Py_DECREF(args);
        if (result) {
            Py_DECREF(result);
            PyErr_Clear();
        } else {
            PyErr_Print();
        }

        wxPyEndBlockThreads();
    }
}



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Convert a wxList to a Python List

PyObject* wxPy_ConvertList(wxListBase* list, const char* className) {
    PyObject*   pyList;
    PyObject*   pyObj;
    wxObject*   wxObj;
    wxNode*     node = list->First();

    wxPyBeginBlockThreads();
    pyList = PyList_New(0);
    while (node) {
        wxObj = node->Data();
        pyObj = wxPyMake_wxObject(wxObj); //wxPyConstructObject(wxObj, className);
        PyList_Append(pyList, pyObj);
        node = node->Next();
    }
    wxPyEndBlockThreads();
    return pyList;
}

//----------------------------------------------------------------------

long wxPyGetWinHandle(wxWindow* win) {
#ifdef __WXMSW__
    return (long)win->GetHandle();
#endif

    // Find and return the actual X-Window.
#ifdef __WXGTK__
    if (win->m_wxwindow) {
        GdkWindowPrivate* bwin = (GdkWindowPrivate*)GTK_PIZZA(win->m_wxwindow)->bin_window;
        if (bwin) {
            return (long)bwin->xwindow;
        }
    }
#endif
    return 0;
}

//----------------------------------------------------------------------
// Some helper functions for typemaps in my_typemaps.i, so they won't be
// included in every file...


byte* byte_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    byte* temp = new byte[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (! PyInt_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of integers.");
            return NULL;
        }
        temp[x] = (byte)PyInt_AsLong(o);
    }
    return temp;
}


int* int_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    int* temp = new int[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (! PyInt_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of integers.");
            return NULL;
        }
        temp[x] = PyInt_AsLong(o);
    }
    return temp;
}


long* long_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    long* temp = new long[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (! PyInt_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of integers.");
            return NULL;
        }
        temp[x] = PyInt_AsLong(o);
    }
    return temp;
}


char** string_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    char** temp = new char*[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (! PyString_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of strings.");
            return NULL;
        }
        temp[x] = PyString_AsString(o);
    }
    return temp;
}

//--------------------------------
// Part of patch from Tim Hochberg
static inline bool wxPointFromObjects(PyObject* o1, PyObject* o2, wxPoint* point) {
    if (PyInt_Check(o1) && PyInt_Check(o2)) {
        point->x = PyInt_AS_LONG(o1);
        point->y = PyInt_AS_LONG(o2);
        return true;
    }
    if (PyFloat_Check(o1) && PyFloat_Check(o2)) {
        point->x = (int)PyFloat_AS_DOUBLE(o1);
        point->y = (int)PyFloat_AS_DOUBLE(o2);
        return true;
    }
    if (PyInstance_Check(o1) || PyInstance_Check(o2)) {
        // Disallow instances because they can cause havok
        return false;
    }
    if (PyNumber_Check(o1) && PyNumber_Check(o2)) {
        // I believe this excludes instances, so this should be safe without INCREFFing o1 and o2
        point->x = PyInt_AsLong(o1);
        point->y = PyInt_AsLong(o2);
        return true;
    }
    return false;
}


wxPoint* wxPoint_LIST_helper(PyObject* source, int *count) {
    // Putting all of the declarations here allows
    // us to put the error handling all in one place.
    int x;
    wxPoint* temp;
    PyObject *o, *o1, *o2;
    bool isFast = PyList_Check(source) || PyTuple_Check(source);

    if (!PySequence_Check(source)) {
        goto error0;
    }

    // The length of the sequence is returned in count.
    *count = PySequence_Length(source);
    if (*count < 0) {
        goto error0;
    }

    temp = new wxPoint[*count];
    if (!temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (x=0; x<*count; x++) {
        // Get an item: try fast way first.
        if (isFast) {
            o = PySequence_Fast_GET_ITEM(source, x);
        }
        else {
            o = PySequence_GetItem(source, x);
            if (o == NULL) {
                goto error1;
            }
        }

        // Convert o to wxPoint.
        if ((PyTuple_Check(o) && PyTuple_GET_SIZE(o) == 2) ||
            (PyList_Check(o) && PyList_GET_SIZE(o) == 2)) {
            o1 = PySequence_Fast_GET_ITEM(o, 0);
            o2 = PySequence_Fast_GET_ITEM(o, 1);
            if (!wxPointFromObjects(o1, o2, &temp[x])) {
                goto error2;
            }
        }
        else if (PyInstance_Check(o)) {
            wxPoint* pt;
            if (SWIG_GetPtrObj(o, (void **)&pt, "_wxPoint_p")) {
                goto error2;
            }
            temp[x] = *pt;
        }
        else if (PySequence_Check(o) && PySequence_Length(o) == 2) {
            o1 = PySequence_GetItem(o, 0);
            o2 = PySequence_GetItem(o, 1);
            if (!wxPointFromObjects(o1, o2, &temp[x])) {
                goto error3;
            }
            Py_DECREF(o1);
            Py_DECREF(o2);
        }
        else {
            goto error2;
        }
        // Clean up.
        if (!isFast)
            Py_DECREF(o);
    }
    return temp;

error3:
    Py_DECREF(o1);
    Py_DECREF(o2);
error2:
    if (!isFast)
        Py_DECREF(o);
error1:
    delete temp;
error0:
    PyErr_SetString(PyExc_TypeError, "Expected a sequence of length-2 sequences or wxPoints.");
    return NULL;
}
// end of patch
//------------------------------


wxBitmap** wxBitmap_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    wxBitmap** temp = new wxBitmap*[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (PyInstance_Check(o)) {
            wxBitmap*    pt;
            if (SWIG_GetPtrObj(o, (void **) &pt,"_wxBitmap_p")) {
                PyErr_SetString(PyExc_TypeError,"Expected _wxBitmap_p.");
                return NULL;
            }
            temp[x] = pt;
        }
        else {
            PyErr_SetString(PyExc_TypeError, "Expected a list of wxBitmaps.");
            return NULL;
        }
    }
    return temp;
}



wxString* wxString_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    wxString* temp = new wxString[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
#if PYTHON_API_VERSION >= 1009
        if (! PyString_Check(o) && ! PyUnicode_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of string or unicode objects.");
            return NULL;
        }

        char* buff;
        int   length;
        if (PyString_AsStringAndSize(o, &buff, &length) == -1)
            return NULL;
        temp[x] = wxString(buff, length);
#else
        if (! PyString_Check(o)) {
            PyErr_SetString(PyExc_TypeError, "Expected a list of strings.");
            return NULL;
        }
        temp[x] = PyString_AsString(o);
#endif
    }
    return temp;
}


wxAcceleratorEntry* wxAcceleratorEntry_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count                = PyList_Size(source);
    wxAcceleratorEntry* temp = new wxAcceleratorEntry[count];
    if (! temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (PyInstance_Check(o)) {
            wxAcceleratorEntry* ae;
            if (SWIG_GetPtrObj(o, (void **) &ae,"_wxAcceleratorEntry_p")) {
                PyErr_SetString(PyExc_TypeError,"Expected _wxAcceleratorEntry_p.");
                return NULL;
            }
            temp[x] = *ae;
        }
        else if (PyTuple_Check(o)) {
            PyObject* o1 = PyTuple_GetItem(o, 0);
            PyObject* o2 = PyTuple_GetItem(o, 1);
            PyObject* o3 = PyTuple_GetItem(o, 2);
            temp[x].Set(PyInt_AsLong(o1), PyInt_AsLong(o2), PyInt_AsLong(o3));
        }
        else {
            PyErr_SetString(PyExc_TypeError, "Expected a list of 3-tuples or wxAcceleratorEntry objects.");
            return NULL;
        }
    }
    return temp;
}


wxPen** wxPen_LIST_helper(PyObject* source) {
    if (!PyList_Check(source)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }
    int count = PyList_Size(source);
    wxPen** temp = new wxPen*[count];
    if (!temp) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate temporary array");
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* o = PyList_GetItem(source, x);
        if (PyInstance_Check(o)) {
            wxPen*  pt;
            if (SWIG_GetPtrObj(o, (void **) &pt,"_wxPen_p")) {
                delete temp;
                PyErr_SetString(PyExc_TypeError,"Expected _wxPen_p.");
                return NULL;
            }
            temp[x] = pt;
        }
        else {
            delete temp;
            PyErr_SetString(PyExc_TypeError, "Expected a list of wxPens.");
            return NULL;
        }
    }
    return temp;
}


bool _2int_seq_helper(PyObject* source, int* i1, int* i2) {
    bool isFast = PyList_Check(source) || PyTuple_Check(source);
    PyObject *o1, *o2;

    if (!PySequence_Check(source) || PySequence_Length(source) != 2)
        return FALSE;

    if (isFast) {
        o1 = PySequence_Fast_GET_ITEM(source, 0);
        o2 = PySequence_Fast_GET_ITEM(source, 1);
    }
    else {
        o1 = PySequence_GetItem(source, 0);
        o2 = PySequence_GetItem(source, 1);
    }

    *i1 = PyInt_AsLong(o1);
    *i2 = PyInt_AsLong(o2);

    if (! isFast) {
        Py_DECREF(o1);
        Py_DECREF(o2);
    }
    return TRUE;
}


bool _4int_seq_helper(PyObject* source, int* i1, int* i2, int* i3, int* i4) {
    bool isFast = PyList_Check(source) || PyTuple_Check(source);
    PyObject *o1, *o2, *o3, *o4;

    if (!PySequence_Check(source) || PySequence_Length(source) != 4)
        return FALSE;

    if (isFast) {
        o1 = PySequence_Fast_GET_ITEM(source, 0);
        o2 = PySequence_Fast_GET_ITEM(source, 1);
        o3 = PySequence_Fast_GET_ITEM(source, 2);
        o4 = PySequence_Fast_GET_ITEM(source, 3);
    }
    else {
        o1 = PySequence_GetItem(source, 0);
        o2 = PySequence_GetItem(source, 1);
        o3 = PySequence_GetItem(source, 2);
        o4 = PySequence_GetItem(source, 3);
    }

    *i1 = PyInt_AsLong(o1);
    *i2 = PyInt_AsLong(o2);
    *i3 = PyInt_AsLong(o3);
    *i4 = PyInt_AsLong(o4);

    if (! isFast) {
        Py_DECREF(o1);
        Py_DECREF(o2);
        Py_DECREF(o3);
        Py_DECREF(o4);
    }
    return TRUE;
}


//----------------------------------------------------------------------

bool wxSize_helper(PyObject* source, wxSize** obj) {

    // If source is an object instance then it may already be the right type
    if (PyInstance_Check(source)) {
        wxSize* ptr;
        if (SWIG_GetPtrObj(source, (void **)&ptr, "_wxSize_p"))
            goto error;
        *obj = ptr;
        return TRUE;
    }
    // otherwise a 2-tuple of integers is expected
    else if (PySequence_Check(source) && PyObject_Length(source) == 2) {
        PyObject* o1 = PySequence_GetItem(source, 0);
        PyObject* o2 = PySequence_GetItem(source, 1);
        **obj = wxSize(PyInt_AsLong(o1), PyInt_AsLong(o2));
        return TRUE;
    }

 error:
    PyErr_SetString(PyExc_TypeError, "Expected a 2-tuple of integers or a wxSize object.");
    return FALSE;
}

bool wxPoint_helper(PyObject* source, wxPoint** obj) {

    // If source is an object instance then it may already be the right type
    if (PyInstance_Check(source)) {
        wxPoint* ptr;
        if (SWIG_GetPtrObj(source, (void **)&ptr, "_wxPoint_p"))
            goto error;
        *obj = ptr;
        return TRUE;
    }
    // otherwise a length-2 sequence of integers is expected
    if (PySequence_Check(source) && PySequence_Length(source) == 2) {
        PyObject* o1 = PySequence_GetItem(source, 0);
        PyObject* o2 = PySequence_GetItem(source, 1);
                // This should really check for integers, not numbers -- but that would break code.
                if (!PyNumber_Check(o1) || !PyNumber_Check(o2)) {
                        Py_DECREF(o1);
                    Py_DECREF(o2);
                        goto error;
                }
                **obj = wxPoint(PyInt_AsLong(o1), PyInt_AsLong(o2));
                Py_DECREF(o1);
                Py_DECREF(o2);
        return TRUE;
    }
 error:
    PyErr_SetString(PyExc_TypeError, "Expected a 2-tuple of integers or a wxPoint object.");
    return FALSE;
}



bool wxRealPoint_helper(PyObject* source, wxRealPoint** obj) {

    // If source is an object instance then it may already be the right type
    if (PyInstance_Check(source)) {
        wxRealPoint* ptr;
        if (SWIG_GetPtrObj(source, (void **)&ptr, "_wxRealPoint_p"))
            goto error;
        *obj = ptr;
        return TRUE;
    }
    // otherwise a 2-tuple of floats is expected
    else if (PySequence_Check(source) && PyObject_Length(source) == 2) {
        PyObject* o1 = PySequence_GetItem(source, 0);
        PyObject* o2 = PySequence_GetItem(source, 1);
        **obj = wxRealPoint(PyFloat_AsDouble(o1), PyFloat_AsDouble(o2));
        return TRUE;
    }

 error:
    PyErr_SetString(PyExc_TypeError, "Expected a 2-tuple of floats or a wxRealPoint object.");
    return FALSE;
}




bool wxRect_helper(PyObject* source, wxRect** obj) {

    // If source is an object instance then it may already be the right type
    if (PyInstance_Check(source)) {
        wxRect* ptr;
        if (SWIG_GetPtrObj(source, (void **)&ptr, "_wxRect_p"))
            goto error;
        *obj = ptr;
        return TRUE;
    }
    // otherwise a 4-tuple of integers is expected
    else if (PySequence_Check(source) && PyObject_Length(source) == 4) {
        PyObject* o1 = PySequence_GetItem(source, 0);
        PyObject* o2 = PySequence_GetItem(source, 1);
        PyObject* o3 = PySequence_GetItem(source, 2);
        PyObject* o4 = PySequence_GetItem(source, 3);
        **obj = wxRect(PyInt_AsLong(o1), PyInt_AsLong(o2),
                     PyInt_AsLong(o3), PyInt_AsLong(o4));
        return TRUE;
    }

 error:
    PyErr_SetString(PyExc_TypeError, "Expected a 4-tuple of integers or a wxRect object.");
    return FALSE;
}



bool wxColour_helper(PyObject* source, wxColour** obj) {

    // If source is an object instance then it may already be the right type
    if (PyInstance_Check(source)) {
        wxColour* ptr;
        if (SWIG_GetPtrObj(source, (void **)&ptr, "_wxColour_p"))
            goto error;
        *obj = ptr;
        return TRUE;
    }
    // otherwise a string is expected
    else if (PyString_Check(source)) {
        wxString spec = PyString_AS_STRING(source);
        if (spec[0U] == '#' && spec.Length() == 7) {  // It's  #RRGGBB
            char* junk;
            int red   = strtol(spec.Mid(1,2), &junk, 16);
            int green = strtol(spec.Mid(3,2), &junk, 16);
            int blue  = strtol(spec.Mid(5,2), &junk, 16);
            **obj = wxColour(red, green, blue);
            return TRUE;
        }
        else {                                       // it's a colour name
            **obj = wxColour(spec);
            return TRUE;
        }
    }

 error:
    PyErr_SetString(PyExc_TypeError, "Expected a wxColour object or a string containing a colour name or '#RRGGBB'.");
    return FALSE;
}


//----------------------------------------------------------------------

PyObject* wxArrayString2PyList_helper(const wxArrayString& arr) {

    PyObject* list = PyList_New(0);
    for (size_t i=0; i < arr.GetCount(); i++) {
        PyObject* str = PyString_FromString(arr[i].c_str());
        PyList_Append(list, str);
        Py_DECREF(str);
    }
    return list;
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------




