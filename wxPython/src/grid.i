////////////////////////////////////////////////////////////////////////////
// Name:        grid.i
// Purpose:     SWIG definitions for the new wxGrid and related classes
//
// Author:      Robin Dunn
//
// Created:     17-March-2000
// RCS-ID:      $Id$
// Copyright:   (c) 2000 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

%module grid

%{
#include "wx/wxPython/wxPython.h"
#include "wx/wxPython/pyclasses.h"
#include "wx/wxPython/printfw.h"

#include <wx/grid.h>
#include <wx/generic/gridctrl.h>

%}


//---------------------------------------------------------------------------

%import windows.i
%pythoncode { wx = core }
%pythoncode { __docfilter__ = wx.__docfilter__ }


%include _grid_rename.i

MAKE_CONST_WXSTRING_NOSWIG(EmptyString);
MAKE_CONST_WXSTRING_NOSWIG(PanelNameStr);
MAKE_CONST_WXSTRING2(DateTimeFormatStr, wxT("%c"));


//---------------------------------------------------------------------------
// OOR related typemaps and helper functions

%typemap(out) wxGridCellRenderer*     { $result = wxPyMake_wxGridCellRenderer($1); }
%typemap(out) wxGridCellEditor*       { $result = wxPyMake_wxGridCellEditor($1); }
%typemap(out) wxGridCellAttr*         { $result = wxPyMake_wxGridCellAttr($1); }
%typemap(out) wxGridCellAttrProvider* { $result = wxPyMake_wxGridCellAttrProvider($1); }
%typemap(out) wxGridTableBase*        { $result = wxPyMake_wxGridTableBase($1); }


%{

#define wxPyMake_TEMPLATE(TYPE) \
PyObject* wxPyMake_##TYPE(TYPE* source) { \
    PyObject* target = NULL; \
    if (source) { \
        /* Check if there is already a pointer to a Python object in the \
           OOR data that we can use. */ \
        wxPyOORClientData* data = (wxPyOORClientData*)source->GetClientObject(); \
        if (data) { \
            target = data->m_obj; \
            Py_INCREF(target); \
        } \
        /* Otherwise make a new wrapper for it the old fashioned way and \
           give it the OOR treatment */ \
        if (! target) { \
            target = wxPyConstructObject(source, wxT(#TYPE), False); \
            if (target) \
                source->SetClientObject(new wxPyOORClientData(target)); \
        } \
    } else {  /* source was NULL so return None. */ \
        Py_INCREF(Py_None); target = Py_None; \
    } \
    return target; \
} \


wxPyMake_TEMPLATE(wxGridCellRenderer)
wxPyMake_TEMPLATE(wxGridCellEditor)
wxPyMake_TEMPLATE(wxGridCellAttr)
wxPyMake_TEMPLATE(wxGridCellAttrProvider)
wxPyMake_TEMPLATE(wxGridTableBase)

%}

//---------------------------------------------------------------------------
// Macros, similar to what's in helpers.h, to aid in the creation of
// virtual methods that are able to make callbacks to Python.  Many of these
// are specific to wxGrid and so are kept here to reduce the mess in helpers.h
// a bit.


%{
#define PYCALLBACK_GCA_INTINTKIND(PCLASS, CBNAME)                               \
    wxGridCellAttr* CBNAME(int a, int b, wxGridCellAttr::wxAttrKind c) {        \
        wxGridCellAttr* rval = NULL;                                            \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                            \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* ro;                                                       \
            wxGridCellAttr* ptr;                                                \
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(iii)", a, b, c)); \
            if (ro) {                                                           \
                if (wxPyConvertSwigPtr(ro, (void **)&ptr, wxT("wxGridCellAttr")))    \
                    rval = ptr;                                                 \
                Py_DECREF(ro);                                                  \
            }                                                                   \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                             \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a, b, c);                                     \
        return rval;                                                            \
    }                                                                           \
    wxGridCellAttr *base_##CBNAME(int a, int b, wxGridCellAttr::wxAttrKind c) { \
        return PCLASS::CBNAME(a, b, c);                                         \
    }



#define PYCALLBACK__GCAINTINT(PCLASS, CBNAME)                                   \
    void CBNAME(wxGridCellAttr *attr, int a, int b) {                           \
        bool blocked = wxPyBeginBlockThreads();                                                \
        bool found;                                                             \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* obj = wxPyMake_wxGridCellAttr(attr);                      \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(Oii)", obj, a, b));  \
            Py_DECREF(obj);                                                     \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(attr, a, b);                                         \
    }                                                                           \
    void base_##CBNAME(wxGridCellAttr *attr, int a, int b) {                    \
        PCLASS::CBNAME(attr, a, b);                                             \
    }



#define PYCALLBACK__GCAINT(PCLASS, CBNAME)                                      \
    void CBNAME(wxGridCellAttr *attr, int val) {                                \
        bool blocked = wxPyBeginBlockThreads();                                                \
        bool found;                                                             \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* obj = wxPyMake_wxGridCellAttr(attr);                      \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(Oi)", obj, val));    \
            Py_DECREF(obj);                                                     \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                             \
        if (! found)                                                            \
            PCLASS::CBNAME(attr, val);                                          \
    }                                                                           \
    void base_##CBNAME(wxGridCellAttr *attr, int val) {                         \
        PCLASS::CBNAME(attr, val);                                              \
    }



#define PYCALLBACK_INT__pure(CBNAME)                                            \
    int  CBNAME() {                                                             \
        bool blocked = wxPyBeginBlockThreads();                            \
        int rval = 0;                                                           \
        if (wxPyCBH_findCallback(m_myInst, #CBNAME))                            \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("()"));         \
        wxPyEndBlockThreads(blocked);                                             \
        return rval;                                                            \
    }



#define PYCALLBACK_BOOL_INTINT_pure(CBNAME)                                     \
    bool CBNAME(int a, int b) {                                                 \
        bool blocked = wxPyBeginBlockThreads();                            \
        bool rval = 0;                                                          \
        if (wxPyCBH_findCallback(m_myInst, #CBNAME))                            \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(ii)",a,b));   \
        wxPyEndBlockThreads(blocked);                                             \
        return rval;                                                            \
    }


#define PYCALLBACK_STRING_INTINT_pure(CBNAME)                                   \
    wxString CBNAME(int a, int b) {                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        wxString rval;                                                          \
        if (wxPyCBH_findCallback(m_myInst, #CBNAME)) {                          \
            PyObject* ro;                                                       \
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)",a,b));  \
            if (ro) {                                                           \
                rval = Py2wxString(ro);                                         \
                Py_DECREF(ro);                                                  \
            }                                                                   \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        return rval;                                                            \
    }


#define PYCALLBACK__INTINTSTRING_pure(CBNAME)                                   \
    void CBNAME(int a, int b, const wxString& c) {                              \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if (wxPyCBH_findCallback(m_myInst, #CBNAME)) {                          \
            PyObject* s = wx2PyString(c);                                       \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iiO)",a,b,s));\
            Py_DECREF(s);                                                       \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
    }


#define PYCALLBACK_STRING_INTINT(PCLASS, CBNAME)                                \
    wxString CBNAME(int a, int b) {                                             \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        wxString rval;                                                          \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* ro;                                                       \
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)",a,b));  \
            if (ro) {                                                           \
                rval = Py2wxString(ro);                                         \
                Py_DECREF(ro);                                                  \
            }                                                                   \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a, b);                                        \
        return rval;                                                            \
    }                                                                           \
    wxString base_##CBNAME(int a, int b) {                                      \
        return PCLASS::CBNAME(a, b);                                            \
    }


#define PYCALLBACK_BOOL_INTINTSTRING(PCLASS, CBNAME)                            \
    bool CBNAME(int a, int b, const wxString& c)  {                             \
        bool rval = 0;                                                          \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* s = wx2PyString(c);                                       \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iiO)",a,b,s));\
            Py_DECREF(s);                                                       \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a,b,c);                                       \
        return rval;                                                            \
    }                                                                           \
    bool base_##CBNAME(int a, int b, const wxString& c) {                       \
        return PCLASS::CBNAME(a,b,c);                                           \
    }




#define PYCALLBACK_LONG_INTINT(PCLASS, CBNAME)                                  \
    long CBNAME(int a, int b)  {                                                \
        long rval;                                                              \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                            \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(ii)", a,b));  \
        wxPyEndBlockThreads(blocked);                                             \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a,b);                                         \
        return rval;                                                            \
    }                                                                           \
    long base_##CBNAME(int a, int b) {                                          \
        return PCLASS::CBNAME(a,b);                                             \
    }



#define PYCALLBACK_BOOL_INTINT(PCLASS, CBNAME)                                  \
    bool CBNAME(int a, int b)  {                                                \
        bool rval = 0;                                                          \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                            \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(ii)", a,b));  \
        wxPyEndBlockThreads(blocked);                                             \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a,b);                                         \
        return rval;                                                            \
    }                                                                           \
    bool base_##CBNAME(int a, int b) {                                          \
        return PCLASS::CBNAME(a,b);                                             \
    }



#define PYCALLBACK_DOUBLE_INTINT(PCLASS, CBNAME)                                \
    double CBNAME(int a, int b) {                                               \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                            \
        double rval;                                                            \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* ro;                                                       \
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)",a,b));  \
            if (ro) {                                                           \
                PyObject* str = PyObject_Str(ro);                               \
                rval = PyFloat_AsDouble(str);                                   \
                Py_DECREF(ro);   Py_DECREF(str);                                \
            }                                                                   \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a, b);                                        \
        return rval;                                                            \
    }                                                                           \
    double base_##CBNAME(int a, int b) {                                        \
        return PCLASS::CBNAME(a, b);                                            \
    }



#define PYCALLBACK__(PCLASS, CBNAME)                                            \
    void CBNAME()  {                                                            \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("()"));                \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME();                                                   \
    }                                                                           \
    void base_##CBNAME() {                                                      \
        PCLASS::CBNAME();                                                       \
    }




#define PYCALLBACK_BOOL_SIZETSIZET(PCLASS, CBNAME)                              \
    bool CBNAME(size_t a, size_t b)  {                                          \
        bool rval = 0;                                                          \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(ii)", a,b));  \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a,b);                                         \
        return rval;                                                            \
    }                                                                           \
    bool base_##CBNAME(size_t a, size_t b) {                                    \
        return PCLASS::CBNAME(a,b);                                             \
    }



#define PYCALLBACK_BOOL_SIZET(PCLASS, CBNAME)                                   \
    bool CBNAME(size_t a)  {                                                    \
        bool rval = 0;                                                          \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(i)", a));     \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a);                                           \
        return rval;                                                            \
    }                                                                           \
    bool base_##CBNAME(size_t a) {                                              \
        return PCLASS::CBNAME(a);                                               \
    }


#define PYCALLBACK_STRING_INT(PCLASS, CBNAME)                                   \
    wxString CBNAME(int a) {                                                    \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        wxString rval;                                                          \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* ro;                                                       \
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(i)",a));     \
            if (ro) {                                                           \
                rval = Py2wxString(ro);                                         \
                Py_DECREF(ro);                                                  \
            }                                                                   \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME(a);                                           \
        return rval;                                                            \
    }                                                                           \
    wxString base_##CBNAME(int a) {                                             \
        return PCLASS::CBNAME(a);                                               \
    }


#define PYCALLBACK__INTSTRING(PCLASS, CBNAME)                                   \
    void CBNAME(int a, const wxString& c)  {                                    \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME))) {                \
            PyObject* s = wx2PyString(c);                                       \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iO)",a,s));          \
            Py_DECREF(s);                                                       \
        }                                                                       \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(a,c);                                                \
    }                                                                           \
    void base_##CBNAME(int a, const wxString& c) {                              \
        PCLASS::CBNAME(a,c);                                                    \
    }




#define PYCALLBACK_BOOL_(PCLASS, CBNAME)                                        \
    bool CBNAME()  {                                                            \
        bool rval = 0;                                                          \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("()"));         \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            rval = PCLASS::CBNAME();                                            \
        return rval;                                                            \
    }                                                                           \
    bool base_##CBNAME() {                                                      \
        return PCLASS::CBNAME();                                                \
    }



#define PYCALLBACK__SIZETINT(PCLASS, CBNAME)                                    \
    void CBNAME(size_t a, int b)  {                                             \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(ii)", a,b));         \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(a,b);                                                \
    }                                                                           \
    void base_##CBNAME(size_t a, int b) {                                       \
        PCLASS::CBNAME(a,b);                                                    \
    }




#define PYCALLBACK__INTINTLONG(PCLASS, CBNAME)                                  \
    void CBNAME(int a, int b, long c)  {                                        \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iii)", a,b,c));      \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(a,b,c);                                              \
    }                                                                           \
    void base_##CBNAME(int a, int b, long c) {                                  \
        PCLASS::CBNAME(a,b,c);                                                  \
    }




#define PYCALLBACK__INTINTDOUBLE(PCLASS, CBNAME)                                \
    void CBNAME(int a, int b, double c)  {                                      \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iif)", a,b,c));      \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(a,b,c);                                              \
    }                                                                           \
    void base_##CBNAME(int a, int b, double c) {                                \
        PCLASS::CBNAME(a,b,c);                                                  \
    }



#define PYCALLBACK__INTINTBOOL(PCLASS, CBNAME)                                  \
    void CBNAME(int a, int b, bool c)  {                                        \
        bool found;                                                             \
        bool blocked = wxPyBeginBlockThreads();                                                \
        if ((found = wxPyCBH_findCallback(m_myInst, #CBNAME)))                  \
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iii)", a,b,c));      \
        wxPyEndBlockThreads(blocked);                                                  \
        if (! found)                                                            \
            PCLASS::CBNAME(a,b,c);                                              \
    }                                                                           \
    void base_##CBNAME(int a, int b, bool c) {                                  \
        PCLASS::CBNAME(a,b,c);                                                  \
    }




%}

//---------------------------------------------------------------------------

class wxGridCellCoords;
class wxGridCellAttr;

#define wxGRID_VALUE_STRING     "string"
#define wxGRID_VALUE_BOOL       "bool"
#define wxGRID_VALUE_NUMBER     "long"
#define wxGRID_VALUE_FLOAT      "double"
#define wxGRID_VALUE_CHOICE     "choice"
#define wxGRID_VALUE_TEXT       "string"
#define wxGRID_VALUE_LONG       "long"
#define wxGRID_VALUE_CHOICEINT  "choiceint"
#define wxGRID_VALUE_DATETIME   "datetime"


%immutable;
const wxGridCellCoords wxGridNoCellCoords;
const wxRect           wxGridNoCellRect;
%mutable;


//---------------------------------------------------------------------------
// wxGridCellRenderer is an ABC, and several derived classes are available.
// Classes implemented in Python should be derived from wxPyGridCellRenderer.


class wxGridCellRenderer
{
public:
    %extend {
        void _setOORInfo(PyObject* _self) {
            self->SetClientObject(new wxPyOORClientData(_self));
        }
    }

    void SetParameters(const wxString& params);
    void IncRef();
    void DecRef();

    virtual void Draw(wxGrid& grid,
                      wxGridCellAttr& attr,
                      wxDC& dc,
                      const wxRect& rect,
                      int row, int col,
                      bool isSelected);
    virtual wxSize GetBestSize(wxGrid& grid,
                               wxGridCellAttr& attr,
                               wxDC& dc,
                               int row, int col);
    virtual wxGridCellRenderer *Clone() const;
};


// The C++ version of wxPyGridCellRenderer
%{
class wxPyGridCellRenderer : public wxGridCellRenderer
{
public:
    wxPyGridCellRenderer() : wxGridCellRenderer() {};

    // Implement Python callback aware virtual methods
    void Draw(wxGrid& grid, wxGridCellAttr& attr,
              wxDC& dc, const wxRect& rect,
              int row, int col, bool isSelected) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "Draw")) {
            PyObject* go = wxPyMake_wxObject(&grid);
            PyObject* dco = wxPyMake_wxObject(&dc);
            PyObject* ao = wxPyMake_wxGridCellAttr(&attr);
            PyObject* ro = wxPyConstructObject((void*)&rect, wxT("wxRect"), 0);

            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(OOOOiii)", go, ao, dco, ro,
                                                         row, col, isSelected));
            Py_DECREF(go);
            Py_DECREF(ao);
            Py_DECREF(dco);
            Py_DECREF(ro);
        }
        wxPyEndBlockThreads(blocked);
    }

    wxSize GetBestSize(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                       int row, int col) {
        wxSize rval;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "GetBestSize")) {
            PyObject* ro;
            wxSize*   ptr;
            PyObject* go = wxPyMake_wxObject(&grid);
            PyObject* dco = wxPyMake_wxObject(&dc);
            PyObject* ao = wxPyMake_wxGridCellAttr(&attr);

            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(OOOii)",
                                                                 go, ao, dco,
                                                                 row, col));
            Py_DECREF(go);
            Py_DECREF(ao);
            Py_DECREF(dco);

            if (ro) {
                const char* errmsg = "GetBestSize should return a 2-tuple of integers or a wxSize object.";
                if (wxPyConvertSwigPtr(ro, (void **)&ptr, wxT("wxSize"))) {
                    rval = *ptr;
                }
                else if (PySequence_Check(ro) && PyObject_Length(ro) == 2) {
                    PyObject* o1 = PySequence_GetItem(ro, 0);
                    PyObject* o2 = PySequence_GetItem(ro, 1);
                    if (PyNumber_Check(o1) && PyNumber_Check(o2))
                        rval = wxSize(PyInt_AsLong(o1), PyInt_AsLong(o2));
                    else
                        PyErr_SetString(PyExc_TypeError, errmsg);
                    Py_DECREF(o1);
                    Py_DECREF(o2);
                }
                else {
                    PyErr_SetString(PyExc_TypeError, errmsg);
                }
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }


    wxGridCellRenderer *Clone() const {
        wxGridCellRenderer* rval = NULL;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "Clone")) {
            PyObject* ro;
            wxGridCellRenderer* ptr;
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("()"));
            if (ro) {
                if (wxPyConvertSwigPtr(ro, (void **)&ptr, wxT("wxGridCellRenderer")))
                    rval = ptr;
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }

    DEC_PYCALLBACK__STRING(SetParameters);

    PYPRIVATE;
};

IMP_PYCALLBACK__STRING( wxPyGridCellRenderer, wxGridCellRenderer, SetParameters);

%}


// Let SWIG know about it so it can create the Python version
class wxPyGridCellRenderer : public wxGridCellRenderer {
public:
    %pythonAppend wxPyGridCellRenderer  "self._setCallbackInfo(self, PyGridCellRenderer);self._setOORInfo(self)"

    wxPyGridCellRenderer();
    void _setCallbackInfo(PyObject* self, PyObject* _class);

    void base_SetParameters(const wxString& params);
};

//---------------------------------------------------------------------------
//  Predefined Renderers

class wxGridCellStringRenderer : public wxGridCellRenderer
{
public:
    %pythonAppend wxGridCellStringRenderer "self._setOORInfo(self)"
    wxGridCellStringRenderer();
};


class  wxGridCellNumberRenderer : public wxGridCellStringRenderer
{
public:
    %pythonAppend wxGridCellNumberRenderer "self._setOORInfo(self)"
    wxGridCellNumberRenderer();
};


class  wxGridCellFloatRenderer : public wxGridCellStringRenderer
{
public:
    %pythonAppend wxGridCellFloatRenderer "self._setOORInfo(self)"
    wxGridCellFloatRenderer(int width = -1, int precision = -1);

    int GetWidth() const;
    void SetWidth(int width);
    int GetPrecision() const;
    void SetPrecision(int precision);
};


class  wxGridCellBoolRenderer : public wxGridCellRenderer
{
public:
    %pythonAppend wxGridCellBoolRenderer "self._setOORInfo(self)"
    wxGridCellBoolRenderer();
};


class wxGridCellDateTimeRenderer : public wxGridCellStringRenderer
{
public:
    %pythonAppend wxGridCellDateTimeRenderer "self._setOORInfo(self)"
    wxGridCellDateTimeRenderer(wxString outformat = wxPyDateTimeFormatStr,
                               wxString informat =  wxPyDateTimeFormatStr);
};


class wxGridCellEnumRenderer : public wxGridCellStringRenderer
{
public:
    %pythonAppend wxGridCellEnumRenderer "self._setOORInfo(self)"
    wxGridCellEnumRenderer( const wxString& choices = wxPyEmptyString );
};


class wxGridCellAutoWrapStringRenderer : public wxGridCellStringRenderer
{
public:
    %pythonAppend wxGridCellAutoWrapStringRenderer "self._setOORInfo(self)"
    wxGridCellAutoWrapStringRenderer();
};


//---------------------------------------------------------------------------
// wxGridCellEditor is an ABC, and several derived classes are available.
// Classes implemented in Python should be derived from wxPyGridCellEditor.

class  wxGridCellEditor
{
public:
    %extend {
        void _setOORInfo(PyObject* _self) {
            self->SetClientObject(new wxPyOORClientData(_self));
        }
    }

    bool IsCreated();
    wxControl* GetControl();
    void SetControl(wxControl* control);

    wxGridCellAttr* GetCellAttr();
    void SetCellAttr(wxGridCellAttr* attr);

    void SetParameters(const wxString& params);
    void IncRef();
    void DecRef();

    virtual void Create(wxWindow* parent,
                        wxWindowID id,
                        wxEvtHandler* evtHandler);
    virtual void BeginEdit(int row, int col, wxGrid* grid);
    virtual bool EndEdit(int row, int col, wxGrid* grid);
    virtual void Reset();
    virtual wxGridCellEditor *Clone() const;

    virtual void SetSize(const wxRect& rect);
    virtual void Show(bool show, wxGridCellAttr *attr = NULL);
    virtual void PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr);
    virtual bool IsAcceptedKey(wxKeyEvent& event);
    virtual void StartingKey(wxKeyEvent& event);
    virtual void StartingClick();
    virtual void HandleReturn(wxKeyEvent& event);
    virtual void Destroy();

};


// The C++ version of wxPyGridCellEditor
%{
class wxPyGridCellEditor : public wxGridCellEditor
{
public:
    wxPyGridCellEditor() : wxGridCellEditor() {}

    void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "Create")) {
            PyObject* po = wxPyMake_wxObject(parent);
            PyObject* eo = wxPyMake_wxObject(evtHandler);

            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(OiO)", po, id, eo));
            Py_DECREF(po);
            Py_DECREF(eo);
        }
        wxPyEndBlockThreads(blocked);
    }


    void BeginEdit(int row, int col, wxGrid* grid) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "BeginEdit")) {
            PyObject* go = wxPyMake_wxObject(grid);
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iiO)", row, col, go));
            Py_DECREF(go);
        }
        wxPyEndBlockThreads(blocked);
    }


    bool EndEdit(int row, int col, wxGrid* grid) {
        bool rv = False;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "EndEdit")) {
            PyObject* go = wxPyMake_wxObject(grid);
            rv = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iiO)", row, col, go));
            Py_DECREF(go);
        }
        wxPyEndBlockThreads(blocked);
        return rv;
    }


    wxGridCellEditor* Clone() const {
        wxGridCellEditor* rval = NULL;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "Clone")) {
            PyObject* ro;
            wxGridCellEditor* ptr;
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("()"));
            if (ro) {
                if (wxPyConvertSwigPtr(ro, (void **)&ptr, wxT("wxGridCellEditor")))
                    rval = ptr;
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }


    void Show(bool show, wxGridCellAttr *attr) {
        bool found;
        bool blocked = wxPyBeginBlockThreads();
        if ((found = wxPyCBH_findCallback(m_myInst, "Show"))) {
            PyObject* ao = wxPyMake_wxGridCellAttr(attr);
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iO)", show, ao));
            Py_DECREF(ao);
        }
        wxPyEndBlockThreads(blocked);
        if (! found)
            wxGridCellEditor::Show(show, attr);
    }
    void base_Show(bool show, wxGridCellAttr *attr) {
        wxGridCellEditor::Show(show, attr);
    }


    void PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr) {
        bool found;
        bool blocked = wxPyBeginBlockThreads();
        if ((found = wxPyCBH_findCallback(m_myInst, "PaintBackground)"))) {
            PyObject* ao = wxPyMake_wxGridCellAttr(attr);
            PyObject* ro = wxPyConstructObject((void*)&rectCell, wxT("wxRect"), 0);

            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(OO)", ro, ao));

            Py_DECREF(ro);
            Py_DECREF(ao);
        }
        wxPyEndBlockThreads(blocked);
        if (! found)
            wxGridCellEditor::PaintBackground(rectCell, attr);
    }
    void base_PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr) {
        wxGridCellEditor::PaintBackground(rectCell, attr);
    }


    DEC_PYCALLBACK___pure(Reset);
    DEC_PYCALLBACK__constany(SetSize, wxRect);
    DEC_PYCALLBACK_bool_any(IsAcceptedKey, wxKeyEvent);
    DEC_PYCALLBACK__any(StartingKey, wxKeyEvent);
    DEC_PYCALLBACK__any(HandleReturn, wxKeyEvent);
    DEC_PYCALLBACK__(StartingClick);
    DEC_PYCALLBACK__(Destroy);
    DEC_PYCALLBACK__STRING(SetParameters);
    DEC_PYCALLBACK_STRING__constpure(GetValue);

    PYPRIVATE;
};


IMP_PYCALLBACK__STRING( wxPyGridCellEditor, wxGridCellEditor, SetParameters);
IMP_PYCALLBACK___pure(wxPyGridCellEditor, wxGridCellEditor, Reset);
IMP_PYCALLBACK__constany(wxPyGridCellEditor, wxGridCellEditor, SetSize, wxRect);
IMP_PYCALLBACK_bool_any(wxPyGridCellEditor, wxGridCellEditor, IsAcceptedKey, wxKeyEvent);
IMP_PYCALLBACK__any(wxPyGridCellEditor, wxGridCellEditor, StartingKey, wxKeyEvent);
IMP_PYCALLBACK__any(wxPyGridCellEditor, wxGridCellEditor, HandleReturn, wxKeyEvent);
IMP_PYCALLBACK__(wxPyGridCellEditor, wxGridCellEditor, StartingClick);
IMP_PYCALLBACK__(wxPyGridCellEditor, wxGridCellEditor, Destroy);
IMP_PYCALLBACK_STRING__constpure(wxPyGridCellEditor, wxGridCellEditor, GetValue);

%}


// Let SWIG know about it so it can create the Python version
class wxPyGridCellEditor : public wxGridCellEditor {
public:
    %pythonAppend wxPyGridCellEditor  "self._setCallbackInfo(self, PyGridCellEditor);self._setOORInfo(self)"
    
    wxPyGridCellEditor();
    void _setCallbackInfo(PyObject* self, PyObject* _class);

    void base_SetSize(const wxRect& rect);
    void base_Show(bool show, wxGridCellAttr *attr = NULL);
    void base_PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr);
    bool base_IsAcceptedKey(wxKeyEvent& event);
    void base_StartingKey(wxKeyEvent& event);
    void base_StartingClick();
    void base_HandleReturn(wxKeyEvent& event);
    void base_Destroy();
    void base_SetParameters(const wxString& params);
};

//---------------------------------------------------------------------------
//  Predefined Editors

class wxGridCellTextEditor : public wxGridCellEditor
{
public:
    %pythonAppend wxGridCellTextEditor  "self._setOORInfo(self)"
    wxGridCellTextEditor();
    virtual wxString GetValue();
};


class wxGridCellNumberEditor : public wxGridCellTextEditor
{
public:
    %pythonAppend wxGridCellNumberEditor  "self._setOORInfo(self)"
    wxGridCellNumberEditor(int min = -1, int max = -1);
    virtual wxString GetValue();
};


class wxGridCellFloatEditor : public wxGridCellTextEditor
{
public:
    %pythonAppend wxGridCellFloatEditor  "self._setOORInfo(self)"
    wxGridCellFloatEditor(int width = -1, int precision = -1);
    virtual wxString GetValue();
};


class wxGridCellBoolEditor : public wxGridCellEditor
{
public:
    %pythonAppend wxGridCellBoolEditor  "self._setOORInfo(self)"
    wxGridCellBoolEditor();
    virtual wxString GetValue();
};

class wxGridCellChoiceEditor : public wxGridCellEditor
{
public:
    %pythonAppend wxGridCellChoiceEditor  "self._setOORInfo(self)"
    wxGridCellChoiceEditor(int choices = 0,
                           const wxString* choices_array = NULL,
                           bool allowOthers = False);
    virtual wxString GetValue();
};


class wxGridCellEnumEditor : public wxGridCellChoiceEditor
{
public:
    %pythonAppend wxGridCellEnumEditor  "self._setOORInfo(self)"
    wxGridCellEnumEditor( const wxString& choices = wxPyEmptyString );
    virtual wxString GetValue();
};


class wxGridCellAutoWrapStringEditor : public wxGridCellTextEditor
{
public:
    %pythonAppend wxGridCellAutoWrapStringEditor  "self._setOORInfo(self)"
    wxGridCellAutoWrapStringEditor();
    virtual wxString GetValue();
};



//---------------------------------------------------------------------------


class wxGridCellAttr
{
public:
    enum wxAttrKind
    {
        Any,
        Default,
        Cell,
        Row,
        Col,
        Merged
    };

    %extend {
        void _setOORInfo(PyObject* _self) {
            self->SetClientObject(new wxPyOORClientData(_self));
        }
    }
    
    %pythonAppend wxGridCellAttr  "self._setOORInfo(self)"

    wxGridCellAttr(wxGridCellAttr *attrDefault = NULL);

    wxGridCellAttr *Clone() const;
    void MergeWith(wxGridCellAttr *mergefrom);
    void IncRef();
    void DecRef();
    void SetTextColour(const wxColour& colText);
    void SetBackgroundColour(const wxColour& colBack);
    void SetFont(const wxFont& font);
    void SetAlignment(int hAlign, int vAlign);
    void SetSize(int num_rows, int num_cols);
    void SetOverflow( bool allow = True );
    void SetReadOnly(bool isReadOnly = True);

    void SetRenderer(wxGridCellRenderer *renderer);
    void SetEditor(wxGridCellEditor* editor);
    void SetKind(wxAttrKind kind);

    bool HasTextColour() const;
    bool HasBackgroundColour() const;
    bool HasFont() const;
    bool HasAlignment() const;
    bool HasRenderer() const;
    bool HasEditor() const;
    bool HasReadWriteMode() const;
    bool HasOverflowMode() const;

    wxColour GetTextColour() const;
    wxColour GetBackgroundColour() const;
    wxFont GetFont() const;

    DocDeclA(
        void, GetAlignment(int *OUTPUT, int *OUTPUT) const,
        "GetAlignment() -> (hAlign, vAlign)");
    
    DocDeclA(
        void, GetSize(int *OUTPUT, int *OUTPUT) const,
        "GetSize() -> (num_rows, num_cols)");

    bool GetOverflow() const;
    wxGridCellRenderer *GetRenderer(wxGrid* grid, int row, int col) const;
    wxGridCellEditor *GetEditor(wxGrid* grid, int row, int col) const;

    bool IsReadOnly() const;
    void SetDefAttr(wxGridCellAttr* defAttr);
};

//---------------------------------------------------------------------------

class wxGridCellAttrProvider
{
public:
    %pythonAppend wxGridCellAttrProvider "self._setOORInfo(self)"
    wxGridCellAttrProvider();
    // ???? virtual ~wxGridCellAttrProvider();

    %extend {
        void _setOORInfo(PyObject* _self) {
            self->SetClientObject(new wxPyOORClientData(_self));
        }
    }

    wxGridCellAttr *GetAttr(int row, int col,
                            wxGridCellAttr::wxAttrKind  kind) const;
    void SetAttr(wxGridCellAttr *attr, int row, int col);
    void SetRowAttr(wxGridCellAttr *attr, int row);
    void SetColAttr(wxGridCellAttr *attr, int col);

    void UpdateAttrRows( size_t pos, int numRows );
    void UpdateAttrCols( size_t pos, int numCols );

};


// A Python-aware version
%{
class wxPyGridCellAttrProvider : public wxGridCellAttrProvider
{
public:
    wxPyGridCellAttrProvider() : wxGridCellAttrProvider() {};

    PYCALLBACK_GCA_INTINTKIND(wxGridCellAttrProvider, GetAttr);
    PYCALLBACK__GCAINTINT(wxGridCellAttrProvider, SetAttr);
    PYCALLBACK__GCAINT(wxGridCellAttrProvider, SetRowAttr);
    PYCALLBACK__GCAINT(wxGridCellAttrProvider, SetColAttr);

    PYPRIVATE;
};
%}


// The python-aware version get's SWIGified
class wxPyGridCellAttrProvider : public wxGridCellAttrProvider
{
public:
    %pythonAppend wxPyGridCellAttrProvider  "self._setCallbackInfo(self, PyGridCellAttrProvider)"
    wxPyGridCellAttrProvider();
    void _setCallbackInfo(PyObject* self, PyObject* _class);

    wxGridCellAttr *base_GetAttr(int row, int col,
                                 wxGridCellAttr::wxAttrKind kind);
    void base_SetAttr(wxGridCellAttr *attr, int row, int col);
    void base_SetRowAttr(wxGridCellAttr *attr, int row);
    void base_SetColAttr(wxGridCellAttr *attr, int col);
};


//---------------------------------------------------------------------------
// Grid Table Base class and Python aware version


class wxGridTableBase : public wxObject
{
public:
    // wxGridTableBase();   This is an ABC
    //~wxGridTableBase();

    %extend {
        void _setOORInfo(PyObject* _self) {
            self->SetClientObject(new wxPyOORClientData(_self));
        }
    }

    void SetAttrProvider(wxGridCellAttrProvider *attrProvider);
    wxGridCellAttrProvider *GetAttrProvider() const;
    void SetView( wxGrid *grid );
    wxGrid * GetView() const;


    // pure virtuals
    virtual int GetNumberRows();
    virtual int GetNumberCols();
    virtual bool IsEmptyCell( int row, int col );
    virtual wxString GetValue( int row, int col );
    virtual void SetValue( int row, int col, const wxString& value );

    // virtuals overridable in wxPyGridTableBase
    virtual wxString GetTypeName( int row, int col );
    virtual bool CanGetValueAs( int row, int col, const wxString& typeName );
    virtual bool CanSetValueAs( int row, int col, const wxString& typeName );
    virtual long GetValueAsLong( int row, int col );
    virtual double GetValueAsDouble( int row, int col );
    virtual bool GetValueAsBool( int row, int col );
    virtual void SetValueAsLong( int row, int col, long value );
    virtual void SetValueAsDouble( int row, int col, double value );
    virtual void SetValueAsBool( int row, int col, bool value );

    //virtual void* GetValueAsCustom( int row, int col, const wxString& typeName );
    //virtual void  SetValueAsCustom( int row, int col, const wxString& typeName, void* value );


    virtual void Clear();
    virtual bool InsertRows( size_t pos = 0, size_t numRows = 1 );
    virtual bool AppendRows( size_t numRows = 1 );
    virtual bool DeleteRows( size_t pos = 0, size_t numRows = 1 );
    virtual bool InsertCols( size_t pos = 0, size_t numCols = 1 );
    virtual bool AppendCols( size_t numCols = 1 );
    virtual bool DeleteCols( size_t pos = 0, size_t numCols = 1 );

    virtual wxString GetRowLabelValue( int row );
    virtual wxString GetColLabelValue( int col );
    virtual void SetRowLabelValue( int row, const wxString& value );
    virtual void SetColLabelValue( int col, const wxString& value );

    virtual bool CanHaveAttributes();

    virtual wxGridCellAttr *GetAttr( int row, int col,
                                     wxGridCellAttr::wxAttrKind  kind);
    virtual void SetAttr(wxGridCellAttr* attr, int row, int col);
    virtual void SetRowAttr(wxGridCellAttr *attr, int row);
    virtual void SetColAttr(wxGridCellAttr *attr, int col);

};



// Python-aware version
%{
class wxPyGridTableBase : public wxGridTableBase
{
public:
    wxPyGridTableBase() : wxGridTableBase() {}

    PYCALLBACK_INT__pure(GetNumberRows);
    PYCALLBACK_INT__pure(GetNumberCols);
    PYCALLBACK_BOOL_INTINT_pure(IsEmptyCell);
    PYCALLBACK_STRING_INTINT(wxGridTableBase, GetTypeName);
    PYCALLBACK_BOOL_INTINTSTRING(wxGridTableBase, CanGetValueAs);
    PYCALLBACK_BOOL_INTINTSTRING(wxGridTableBase, CanSetValueAs);
    PYCALLBACK__(wxGridTableBase, Clear);
    PYCALLBACK_BOOL_SIZETSIZET(wxGridTableBase, InsertRows);
    PYCALLBACK_BOOL_SIZETSIZET(wxGridTableBase, DeleteRows);
    PYCALLBACK_BOOL_SIZETSIZET(wxGridTableBase, InsertCols);
    PYCALLBACK_BOOL_SIZETSIZET(wxGridTableBase, DeleteCols);
    PYCALLBACK_BOOL_SIZET(wxGridTableBase, AppendRows);
    PYCALLBACK_BOOL_SIZET(wxGridTableBase, AppendCols);
    PYCALLBACK_STRING_INT(wxGridTableBase, GetRowLabelValue);
    PYCALLBACK_STRING_INT(wxGridTableBase, GetColLabelValue);
    PYCALLBACK__INTSTRING(wxGridTableBase, SetRowLabelValue);
    PYCALLBACK__INTSTRING(wxGridTableBase, SetColLabelValue);
    PYCALLBACK_BOOL_(wxGridTableBase, CanHaveAttributes);
    PYCALLBACK_GCA_INTINTKIND(wxGridTableBase, GetAttr);
    PYCALLBACK__GCAINTINT(wxGridTableBase, SetAttr);
    PYCALLBACK__GCAINT(wxGridTableBase, SetRowAttr);
    PYCALLBACK__GCAINT(wxGridTableBase, SetColAttr);


    wxString GetValue(int row, int col) {
        bool blocked = wxPyBeginBlockThreads();
        wxString rval;
        if (wxPyCBH_findCallback(m_myInst, "GetValue")) {
            PyObject* ro;
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)",row,col));
            if (ro) {
                rval = Py2wxString(ro);
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }

    void SetValue(int row, int col, const wxString& val) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "SetValue")) {
            PyObject* s = wx2PyString(val);
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iiO)",row,col,s));
            Py_DECREF(s);
	}
        wxPyEndBlockThreads(blocked);
    }


    // Map the Get/Set methods for the standard non-string types to
    // the GetValue and SetValue python methods.
    long GetValueAsLong( int row, int col ) {
        long rval = 0;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "GetValue")) {
            PyObject* ro;
            PyObject* num;
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)", row, col));
            if (ro && PyNumber_Check(ro)) {
                num = PyNumber_Int(ro);
                if (num) {
                    rval = PyInt_AsLong(num);
                    Py_DECREF(num);
                }
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }

    double GetValueAsDouble( int row, int col ) {
        double rval = 0.0;
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "GetValue")) {
            PyObject* ro;
            PyObject* num;
            ro = wxPyCBH_callCallbackObj(m_myInst, Py_BuildValue("(ii)", row, col));
            if (ro && PyNumber_Check(ro)) {
                num = PyNumber_Float(ro);
                if (num) {
                    rval = PyFloat_AsDouble(num);
                    Py_DECREF(num);
                }
                Py_DECREF(ro);
            }
        }
        wxPyEndBlockThreads(blocked);
        return rval;
    }

    bool GetValueAsBool( int row, int col ) {
        return (bool)GetValueAsLong(row, col);
    }

    void SetValueAsLong( int row, int col, long value ) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "SetValue")) {
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iii)", row, col, value));
        }
        wxPyEndBlockThreads(blocked);
    }

    void SetValueAsDouble( int row, int col, double value ) {
        bool blocked = wxPyBeginBlockThreads();
        if (wxPyCBH_findCallback(m_myInst, "SetValue")) {
            wxPyCBH_callCallback(m_myInst, Py_BuildValue("(iid)", row, col, value));
        }
        wxPyEndBlockThreads(blocked);
    }

    void SetValueAsBool( int row, int col, bool value ) {
        SetValueAsLong( row, col, (long)value );
    }


    PYPRIVATE;
};
%}


// The python-aware version get's SWIGified
class wxPyGridTableBase : public wxGridTableBase
{
public:
    %pythonAppend wxPyGridTableBase "self._setCallbackInfo(self, PyGridTableBase);self._setOORInfo(self)"
    wxPyGridTableBase();
    void _setCallbackInfo(PyObject* self, PyObject* _class);

    %extend { void Destroy() { delete self; } }

    wxString base_GetTypeName( int row, int col );
    bool base_CanGetValueAs( int row, int col, const wxString& typeName );
    bool base_CanSetValueAs( int row, int col, const wxString& typeName );
    void base_Clear();
    bool base_InsertRows( size_t pos = 0, size_t numRows = 1 );
    bool base_AppendRows( size_t numRows = 1 );
    bool base_DeleteRows( size_t pos = 0, size_t numRows = 1 );
    bool base_InsertCols( size_t pos = 0, size_t numCols = 1 );
    bool base_AppendCols( size_t numCols = 1 );
    bool base_DeleteCols( size_t pos = 0, size_t numCols = 1 );
    wxString base_GetRowLabelValue( int row );
    wxString base_GetColLabelValue( int col );
    void base_SetRowLabelValue( int row, const wxString& value );
    void base_SetColLabelValue( int col, const wxString& value );
    bool base_CanHaveAttributes();
    wxGridCellAttr *base_GetAttr( int row, int col,
                                  wxGridCellAttr::wxAttrKind kind );
    void base_SetAttr(wxGridCellAttr* attr, int row, int col);
    void base_SetRowAttr(wxGridCellAttr *attr, int row);
    void base_SetColAttr(wxGridCellAttr *attr, int col);
};


//---------------------------------------------------------------------------
// Predefined Tables

class  wxGridStringTable : public wxGridTableBase
{
public:
    %pythonAppend wxGridStringTable "self._setOORInfo(self)"
    wxGridStringTable( int numRows=0, int numCols=0 );
};

//---------------------------------------------------------------------------
// The Table can pass messages to the grid to tell it to update itself if
// something has changed.

enum wxGridTableRequest
{
    wxGRIDTABLE_REQUEST_VIEW_GET_VALUES = 2000,
    wxGRIDTABLE_REQUEST_VIEW_SEND_VALUES,
    wxGRIDTABLE_NOTIFY_ROWS_INSERTED,
    wxGRIDTABLE_NOTIFY_ROWS_APPENDED,
    wxGRIDTABLE_NOTIFY_ROWS_DELETED,
    wxGRIDTABLE_NOTIFY_COLS_INSERTED,
    wxGRIDTABLE_NOTIFY_COLS_APPENDED,
    wxGRIDTABLE_NOTIFY_COLS_DELETED
};


class wxGridTableMessage
{
public:
    wxGridTableMessage( wxGridTableBase *table, int id,
                        int comInt1 = -1,
                        int comInt2 = -1 );
    ~wxGridTableMessage();

    void SetTableObject( wxGridTableBase *table );
    wxGridTableBase * GetTableObject() const;
    void SetId( int id );
    int  GetId();
    void SetCommandInt( int comInt1 );
    int  GetCommandInt();
    void SetCommandInt2( int comInt2 );
    int  GetCommandInt2();
};


//---------------------------------------------------------------------------


// Typemap to allow conversion of sequence objects to wxGridCellCoords...
%typemap(in) wxGridCellCoords& (wxGridCellCoords temp) {
    $1 = &temp;
    if (! wxGridCellCoords_helper($input, &$1)) SWIG_fail;
}
%typemap(typecheck, precedence=SWIG_TYPECHECK_POINTER) wxGridCellCoords& {
    $1 = wxGridCellCoords_typecheck($input);
}


// ...and here is the associated helper.
%{
bool wxGridCellCoords_helper(PyObject* source, wxGridCellCoords** obj) {

    if (source == Py_None) {
        **obj = wxGridCellCoords(-1,-1);
        return True;
    }

    // If source is an object instance then it may already be the right type
    if (wxPySwigInstance_Check(source)) {
        wxGridCellCoords* ptr;
        if (! wxPyConvertSwigPtr(source, (void **)&ptr, wxT("wxGridCellCoords")))
            goto error;
        *obj = ptr;
        return True;
    }
    // otherwise a 2-tuple of integers is expected
    else if (PySequence_Check(source) && PyObject_Length(source) == 2) {
        PyObject* o1 = PySequence_GetItem(source, 0);
        PyObject* o2 = PySequence_GetItem(source, 1);
        if (!PyNumber_Check(o1) || !PyNumber_Check(o2)) {
            Py_DECREF(o1);
            Py_DECREF(o2);
            goto error;
        }
        **obj = wxGridCellCoords(PyInt_AsLong(o1), PyInt_AsLong(o2));
        Py_DECREF(o1);
        Py_DECREF(o2);
        return True;
    }

 error:
    PyErr_SetString(PyExc_TypeError, "Expected a 2-tuple of integers or a wxGridCellCoords object.");
    return False;
}


bool wxGridCellCoords_typecheck(PyObject* source) {
    void* ptr;
    
    if (wxPySwigInstance_Check(source) &&
        wxPyConvertSwigPtr(source, (void **)&ptr, wxT("wxGridCellCoords")))
        return True;

    PyErr_Clear();
    if (PySequence_Check(source) && PySequence_Length(source) == 2)
        return True;
    
    return False;
}
%}


// Typemap to convert an array of cells coords to a list of tuples...
%typemap(out) wxGridCellCoordsArray {
    $result = wxGridCellCoordsArray_helper($1);
}

// %typemap(ret) wxGridCellCoordsArray {
//     delete $1;
// }


// ...and the helper function for the above typemap.
%{
PyObject* wxGridCellCoordsArray_helper(const wxGridCellCoordsArray& source)
{
    PyObject* list = PyList_New(0);
    size_t idx;
    for (idx = 0; idx < source.GetCount(); idx += 1) {
        wxGridCellCoords& coord = source.Item(idx);
        PyObject* tup = PyTuple_New(2);
        PyTuple_SET_ITEM(tup, 0, PyInt_FromLong(coord.GetRow()));
        PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(coord.GetCol()));
        PyList_Append(list, tup);
        Py_DECREF(tup);
    }
    return list;
}
%}





class wxGridCellCoords
{
public:
    wxGridCellCoords( int r=-1, int c=-1 );
    ~wxGridCellCoords();

    int GetRow() const;
    void SetRow( int n );
    int GetCol() const;
    void SetCol( int n );
    void Set( int row, int col );

    bool operator==( const wxGridCellCoords& other ) const;
    bool operator!=( const wxGridCellCoords& other ) const;

    %extend {
        PyObject* asTuple() {
            PyObject* tup = PyTuple_New(2);
            PyTuple_SET_ITEM(tup, 0, PyInt_FromLong(self->GetRow()));
            PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(self->GetCol()));
            return tup;
        }
    }
    %pythoncode {
    def __str__(self):                   return str(self.asTuple())
    def __repr__(self):                  return 'wxGridCellCoords'+str(self.asTuple())
    def __len__(self):                   return len(self.asTuple())
    def __getitem__(self, index):        return self.asTuple()[index]
    def __setitem__(self, index, val):
        if index == 0: self.SetRow(val)
        elif index == 1: self.SetCol(val)
        else: raise IndexError
    }

};


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// The grid itself


// Fool SWIG into treating this enum as an int
typedef int WXGRIDSELECTIONMODES;

// but let the C++ code know what it really is.
%{
typedef wxGrid::wxGridSelectionModes WXGRIDSELECTIONMODES;
%}



class wxGrid : public wxScrolledWindow
{
public:
    %pythonAppend wxGrid "self._setOORInfo(self)"

    wxGrid( wxWindow *parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxWANTS_CHARS,
            const wxString& name = wxPyPanelNameStr);


    enum wxGridSelectionModes {
        wxGridSelectCells,
        wxGridSelectRows,
        wxGridSelectColumns
    };
    %pythoncode {
        SelectCells =   wxGridSelectCells
        SelectRows =    wxGridSelectRows
        SelectColumns = wxGridSelectColumns
    }

    bool CreateGrid( int numRows, int numCols,
                     WXGRIDSELECTIONMODES selmode = wxGrid::wxGridSelectCells );
    void SetSelectionMode(WXGRIDSELECTIONMODES selmode);
    WXGRIDSELECTIONMODES GetSelectionMode();


    // ------ grid dimensions
    //
    int      GetNumberRows();
    int      GetNumberCols();


    bool ProcessTableMessage( wxGridTableMessage& );


    wxGridTableBase * GetTable() const;
    bool SetTable( wxGridTableBase *table, bool takeOwnership=False,
                   WXGRIDSELECTIONMODES selmode =
                   wxGrid::wxGridSelectCells );

    void ClearGrid();
    bool InsertRows( int pos = 0, int numRows = 1, bool updateLabels=True );
    bool AppendRows( int numRows = 1, bool updateLabels=True );
    bool DeleteRows( int pos = 0, int numRows = 1, bool updateLabels=True );
    bool InsertCols( int pos = 0, int numCols = 1, bool updateLabels=True );
    bool AppendCols( int numCols = 1, bool updateLabels=True );
    bool DeleteCols( int pos = 0, int numCols = 1, bool updateLabels=True );


    // this function is called when the current cell highlight must be redrawn
    // and may be overridden by the user
    virtual void DrawCellHighlight( wxDC& dc, const wxGridCellAttr *attr );


    // ------ Cell text drawing functions
    //
    void DrawTextRectangle( wxDC& dc, const wxString&, const wxRect&,
                            int horizontalAlignment = wxLEFT,
                            int verticalAlignment = wxTOP,
                            int textOrientation = wxHORIZONTAL );

//      // Split a string containing newline chararcters into an array of
//      // strings and return the number of lines
//      //
//      void StringToLines( const wxString& value, wxArrayString& lines );

    DocDeclA(
        void, GetTextBoxSize( wxDC& dc, wxArrayString& lines,
                              long *OUTPUT, long *OUTPUT ),
        "GetTextBoxSize(DC dc, list lines) -> (width, height)");


    // ------
    // Code that does a lot of grid modification can be enclosed
    // between BeginBatch() and EndBatch() calls to avoid screen
    // flicker
    //
    void     BeginBatch();
    void     EndBatch();
    int      GetBatchCount();
    void     ForceRefresh();


    // ------ edit control functions
    //
    bool IsEditable();
    void EnableEditing( bool edit );

    void EnableCellEditControl( bool enable = True );
    void DisableCellEditControl();
    bool CanEnableCellControl() const;
    bool IsCellEditControlEnabled() const;
    bool IsCellEditControlShown() const;

    bool IsCurrentCellReadOnly() const;

    void ShowCellEditControl();
    void HideCellEditControl();
    void SaveEditControlValue();


    // ------ grid location functions
    //  Note that all of these functions work with the logical coordinates of
    //  grid cells and labels so you will need to convert from device
    //  coordinates for mouse events etc.
    //

    //void XYToCell( int x, int y, wxGridCellCoords& );
    %extend {
        wxGridCellCoords XYToCell(int x, int y) {
            wxGridCellCoords rv;
            self->XYToCell(x, y, rv);
            return rv;
        }
    }

    int  YToRow( int y );
    int  XToCol( int x );

    int  YToEdgeOfRow( int y );
    int  XToEdgeOfCol( int x );

    wxRect CellToRect( int row, int col );
    // TODO: ??? wxRect CellToRect( const wxGridCellCoords& coords );


    int  GetGridCursorRow();
    int  GetGridCursorCol();

    // check to see if a cell is either wholly visible (the default arg) or
    // at least partially visible in the grid window
    //
    bool IsVisible( int row, int col, bool wholeCellVisible = True );
    // TODO: ??? bool IsVisible( const wxGridCellCoords& coords, bool wholeCellVisible = True );
    void MakeCellVisible( int row, int col );
    // TODO: ??? void MakeCellVisible( const wxGridCellCoords& coords );


    // ------ grid cursor movement functions
    //
    void SetGridCursor( int row, int col );
    bool MoveCursorUp( bool expandSelection );
    bool MoveCursorDown( bool expandSelection );
    bool MoveCursorLeft( bool expandSelection );
    bool MoveCursorRight( bool expandSelection );
    bool MovePageDown();
    bool MovePageUp();
    bool MoveCursorUpBlock( bool expandSelection );
    bool MoveCursorDownBlock( bool expandSelection );
    bool MoveCursorLeftBlock( bool expandSelection );
    bool MoveCursorRightBlock( bool expandSelection );


    // ------ label and gridline formatting
    //
    int      GetDefaultRowLabelSize();
    int      GetRowLabelSize();
    int      GetDefaultColLabelSize();
    int      GetColLabelSize();
    wxColour GetLabelBackgroundColour();
    wxColour GetLabelTextColour();
    wxFont   GetLabelFont();

    DocDeclA(
        void, GetRowLabelAlignment( int *OUTPUT, int *OUTPUT ),
        "GetRowLabelAlignment() -> (horiz, vert)");
    
    DocDeclA(
        void, GetColLabelAlignment( int *OUTPUT, int *OUTPUT ),
        "GetColLabelAlignment() -> (horiz, vert)");

    int      GetColLabelTextOrientation();
    wxString GetRowLabelValue( int row );
    wxString GetColLabelValue( int col );
    wxColour GetGridLineColour();
    wxColour GetCellHighlightColour();
    int      GetCellHighlightPenWidth();
    int      GetCellHighlightROPenWidth();

    void     SetRowLabelSize( int width );
    void     SetColLabelSize( int height );
    void     SetLabelBackgroundColour( const wxColour& );
    void     SetLabelTextColour( const wxColour& );
    void     SetLabelFont( const wxFont& );
    void     SetRowLabelAlignment( int horiz, int vert );
    void     SetColLabelAlignment( int horiz, int vert );
    void     SetColLabelTextOrientation( int textOrientation );
    void     SetRowLabelValue( int row, const wxString& );
    void     SetColLabelValue( int col, const wxString& );
    void     SetGridLineColour( const wxColour& );
    void     SetCellHighlightColour( const wxColour& );
    void     SetCellHighlightPenWidth(int width);
    void     SetCellHighlightROPenWidth(int width);

    void     EnableDragRowSize( bool enable = True );
    void     DisableDragRowSize();
    bool     CanDragRowSize();
    void     EnableDragColSize( bool enable = True );
    void     DisableDragColSize();
    bool     CanDragColSize();
    void     EnableDragGridSize(bool enable = True);
    void     DisableDragGridSize();
    bool     CanDragGridSize();

    // this sets the specified attribute for all cells in this row/col
    void     SetAttr(int row, int col, wxGridCellAttr *attr);
    void     SetRowAttr(int row, wxGridCellAttr *attr);
    void     SetColAttr(int col, wxGridCellAttr *attr);

    // shortcuts for setting the column parameters

    // set the format for the data in the column: default is string
    void     SetColFormatBool(int col);
    void     SetColFormatNumber(int col);
    void     SetColFormatFloat(int col, int width = -1, int precision = -1);
    void     SetColFormatCustom(int col, const wxString& typeName);

    void     EnableGridLines( bool enable = True );
    bool     GridLinesEnabled();

    // ------ row and col formatting
    //
    int      GetDefaultRowSize();
    int      GetRowSize( int row );
    int      GetDefaultColSize();
    int      GetColSize( int col );
    wxColour GetDefaultCellBackgroundColour();
    wxColour GetCellBackgroundColour( int row, int col );
    wxColour GetDefaultCellTextColour();
    wxColour GetCellTextColour( int row, int col );
    wxFont   GetDefaultCellFont();
    wxFont   GetCellFont( int row, int col );

    DocDeclA(
        void, GetDefaultCellAlignment( int *OUTPUT, int *OUTPUT ),
        "GetDefaultCellAlignment() -> (horiz, vert)");
    
    DocDeclA(
        void, GetCellAlignment( int row, int col, int *OUTPUT, int *OUTPUT ),
        "GetCellAlignment() -> (horiz, vert)");

    bool     GetDefaultCellOverflow();
    bool     GetCellOverflow( int row, int col );

    DocDeclA(
        void, GetCellSize( int row, int col, int *OUTPUT, int *OUTPUT ),
        "GetCellSize(int row, int col) -> (num_rows, num_cols)");

    void     SetDefaultRowSize( int height, bool resizeExistingRows = False );
    void     SetRowSize( int row, int height );
    void     SetDefaultColSize( int width, bool resizeExistingCols = False );

    void     SetColSize( int col, int width );

    // automatically size the column or row to fit to its contents, if
    // setAsMin is True, this optimal width will also be set as minimal width
    // for this column
    void     AutoSizeColumn( int col, bool setAsMin = True );
    void     AutoSizeRow( int row, bool setAsMin = True );


    // auto size all columns (very ineffective for big grids!)
    void     AutoSizeColumns( bool setAsMin = True );
    void     AutoSizeRows( bool setAsMin = True );

    // auto size the grid, that is make the columns/rows of the "right" size
    // and also set the grid size to just fit its contents
    void     AutoSize();

    // autosize row height depending on label text
    void     AutoSizeRowLabelSize( int row );

    // autosize column width depending on label text
    void     AutoSizeColLabelSize( int col );


    // column won't be resized to be lesser width - this must be called during
    // the grid creation because it won't resize the column if it's already
    // narrower than the minimal width
    void     SetColMinimalWidth( int col, int width );
    void     SetRowMinimalHeight( int row, int width );

    void     SetColMinimalAcceptableWidth( int width );
    void     SetRowMinimalAcceptableHeight( int width );
    int      GetColMinimalAcceptableWidth() const;
    int      GetRowMinimalAcceptableHeight() const;

    void     SetDefaultCellBackgroundColour( const wxColour& );
    void     SetCellBackgroundColour( int row, int col, const wxColour& );
    void     SetDefaultCellTextColour( const wxColour& );

    void     SetCellTextColour( int row, int col, const wxColour& );
    void     SetDefaultCellFont( const wxFont& );
    void     SetCellFont( int row, int col, const wxFont& );
    void     SetDefaultCellAlignment( int horiz, int vert );
    void     SetCellAlignment( int row, int col, int horiz, int vert );
    void     SetDefaultCellOverflow( bool allow );
    void     SetCellOverflow( int row, int col, bool allow );
    void     SetCellSize( int row, int col, int num_rows, int num_cols );

    // takes ownership of the pointer
    void SetDefaultRenderer(wxGridCellRenderer *renderer);
    void SetCellRenderer(int row, int col, wxGridCellRenderer *renderer);
    wxGridCellRenderer *GetDefaultRenderer() const;
    wxGridCellRenderer* GetCellRenderer(int row, int col);

    // takes ownership of the pointer
    void SetDefaultEditor(wxGridCellEditor *editor);
    void SetCellEditor(int row, int col, wxGridCellEditor *editor);
    wxGridCellEditor *GetDefaultEditor() const;
    wxGridCellEditor* GetCellEditor(int row, int col);



    // ------ cell value accessors
    //
    wxString GetCellValue( int row, int col );
    // TODO: ??? wxString GetCellValue( const wxGridCellCoords& coords )

    void SetCellValue( int row, int col, const wxString& s );
    // TODO: ??? void SetCellValue( const wxGridCellCoords& coords, const wxString& s )

    // returns True if the cell can't be edited
    bool IsReadOnly(int row, int col) const;

    // make the cell editable/readonly
    void SetReadOnly(int row, int col, bool isReadOnly = True);

    // ------ selections of blocks of cells
    //
    void SelectRow( int row, bool addToSelected = False );
    void SelectCol( int col, bool addToSelected = False );

    void SelectBlock( int topRow, int leftCol, int bottomRow, int rightCol,
                      bool addToSelected = False );
    // TODO: ??? void SelectBlock( const wxGridCellCoords& topLeft,
    // TODO: ???                   const wxGridCellCoords& bottomRight )

    void SelectAll();
    bool IsSelection();
    void ClearSelection();
    bool IsInSelection( int row, int col );
    // TODO: ??? bool IsInSelection( const wxGridCellCoords& coords )

    const wxGridCellCoordsArray GetSelectedCells() const;
    const wxGridCellCoordsArray GetSelectionBlockTopLeft() const;
    const wxGridCellCoordsArray GetSelectionBlockBottomRight() const;
    const wxArrayInt GetSelectedRows() const;
    const wxArrayInt GetSelectedCols() const;

    void DeselectRow( int row );
    void DeselectCol( int col );
    void DeselectCell( int row, int col );


    // This function returns the rectangle that encloses the block of cells
    // limited by TopLeft and BottomRight cell in device coords and clipped
    //  to the client size of the grid window.
    //
    wxRect BlockToDeviceRect( const wxGridCellCoords & topLeft,
                              const wxGridCellCoords & bottomRight );


    // Access or update the selection fore/back colours
    wxColour GetSelectionBackground() const;
    wxColour GetSelectionForeground() const;

    void SetSelectionBackground(const wxColour& c);
    void SetSelectionForeground(const wxColour& c);


    // Methods for a registry for mapping data types to Renderers/Editors
    void RegisterDataType(const wxString& typeName,
                          wxGridCellRenderer* renderer,
                          wxGridCellEditor* editor);
    wxGridCellEditor* GetDefaultEditorForCell(int row, int col) const;
    // TODO: ??? wxGridCellEditor* GetDefaultEditorForCell(const wxGridCellCoords& c) const
    wxGridCellRenderer* GetDefaultRendererForCell(int row, int col) const;
    wxGridCellEditor* GetDefaultEditorForType(const wxString& typeName) const;
    wxGridCellRenderer* GetDefaultRendererForType(const wxString& typeName) const;

    // grid may occupy more space than needed for its rows/columns, this
    // function allows to set how big this extra space is
    void SetMargins(int extraWidth, int extraHeight);


    // Accessors for component windows
    wxWindow* GetGridWindow();
    wxWindow* GetGridRowLabelWindow();
    wxWindow* GetGridColLabelWindow();
    wxWindow* GetGridCornerLabelWindow();


};


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Grid events and stuff



class wxGridEvent : public wxNotifyEvent
{
public:
    wxGridEvent(int id, wxEventType type, wxGrid* obj,
                int row=-1, int col=-1, int x=-1, int y=-1, bool sel = True,
                bool control=False, bool shift=False, bool alt=False, bool meta=False);

    virtual int GetRow();
    virtual int GetCol();
    wxPoint     GetPosition();
    bool        Selecting();
    bool        ControlDown();
    bool        MetaDown();
    bool        ShiftDown();
    bool        AltDown();

};


class  wxGridSizeEvent : public wxNotifyEvent
{
public:
    wxGridSizeEvent(int id, wxEventType type, wxGrid* obj,
                int rowOrCol=-1, int x=-1, int y=-1,
                bool control=False, bool shift=False, bool alt=False, bool meta=False);

    int         GetRowOrCol();
    wxPoint     GetPosition();
    bool        ControlDown();
    bool        MetaDown();
    bool        ShiftDown();
    bool        AltDown();

};


class wxGridRangeSelectEvent : public wxNotifyEvent
{
public:
    wxGridRangeSelectEvent(int id, wxEventType type, wxGrid* obj,
                           const wxGridCellCoords& topLeft,
                           const wxGridCellCoords& bottomRight,
                           bool sel = True,
                           bool control=False, bool shift=False,
                           bool alt=False, bool meta=False);

    wxGridCellCoords GetTopLeftCoords();
    wxGridCellCoords GetBottomRightCoords();
    int         GetTopRow();
    int         GetBottomRow();
    int         GetLeftCol();
    int         GetRightCol();
    bool        Selecting();
    bool        ControlDown();
    bool        MetaDown();
    bool        ShiftDown();
    bool        AltDown();
};


class wxGridEditorCreatedEvent : public wxCommandEvent {
public:
    wxGridEditorCreatedEvent(int id, wxEventType type, wxObject* obj,
                             int row, int col, wxControl* ctrl);

    int GetRow();
    int GetCol();
    wxControl* GetControl();
    void SetRow(int row);
    void SetCol(int col);
    void SetControl(wxControl* ctrl);
};



%constant wxEventType wxEVT_GRID_CELL_LEFT_CLICK;
%constant wxEventType wxEVT_GRID_CELL_RIGHT_CLICK;
%constant wxEventType wxEVT_GRID_CELL_LEFT_DCLICK;
%constant wxEventType wxEVT_GRID_CELL_RIGHT_DCLICK;
%constant wxEventType wxEVT_GRID_LABEL_LEFT_CLICK;
%constant wxEventType wxEVT_GRID_LABEL_RIGHT_CLICK;
%constant wxEventType wxEVT_GRID_LABEL_LEFT_DCLICK;
%constant wxEventType wxEVT_GRID_LABEL_RIGHT_DCLICK;
%constant wxEventType wxEVT_GRID_ROW_SIZE;
%constant wxEventType wxEVT_GRID_COL_SIZE;
%constant wxEventType wxEVT_GRID_RANGE_SELECT;
%constant wxEventType wxEVT_GRID_CELL_CHANGE;
%constant wxEventType wxEVT_GRID_SELECT_CELL;
%constant wxEventType wxEVT_GRID_EDITOR_SHOWN;
%constant wxEventType wxEVT_GRID_EDITOR_HIDDEN;
%constant wxEventType wxEVT_GRID_EDITOR_CREATED;



%pythoncode {
EVT_GRID_CELL_LEFT_CLICK = wx.PyEventBinder( wxEVT_GRID_CELL_LEFT_CLICK )
EVT_GRID_CELL_RIGHT_CLICK = wx.PyEventBinder( wxEVT_GRID_CELL_RIGHT_CLICK )
EVT_GRID_CELL_LEFT_DCLICK = wx.PyEventBinder( wxEVT_GRID_CELL_LEFT_DCLICK )
EVT_GRID_CELL_RIGHT_DCLICK = wx.PyEventBinder( wxEVT_GRID_CELL_RIGHT_DCLICK )
EVT_GRID_LABEL_LEFT_CLICK = wx.PyEventBinder( wxEVT_GRID_LABEL_LEFT_CLICK )
EVT_GRID_LABEL_RIGHT_CLICK = wx.PyEventBinder( wxEVT_GRID_LABEL_RIGHT_CLICK )
EVT_GRID_LABEL_LEFT_DCLICK = wx.PyEventBinder( wxEVT_GRID_LABEL_LEFT_DCLICK )
EVT_GRID_LABEL_RIGHT_DCLICK = wx.PyEventBinder( wxEVT_GRID_LABEL_RIGHT_DCLICK )
EVT_GRID_ROW_SIZE = wx.PyEventBinder( wxEVT_GRID_ROW_SIZE )
EVT_GRID_COL_SIZE = wx.PyEventBinder( wxEVT_GRID_COL_SIZE )
EVT_GRID_RANGE_SELECT = wx.PyEventBinder( wxEVT_GRID_RANGE_SELECT )
EVT_GRID_CELL_CHANGE = wx.PyEventBinder( wxEVT_GRID_CELL_CHANGE )
EVT_GRID_SELECT_CELL = wx.PyEventBinder( wxEVT_GRID_SELECT_CELL )
EVT_GRID_EDITOR_SHOWN = wx.PyEventBinder( wxEVT_GRID_EDITOR_SHOWN )
EVT_GRID_EDITOR_HIDDEN = wx.PyEventBinder( wxEVT_GRID_EDITOR_HIDDEN )
EVT_GRID_EDITOR_CREATED = wx.PyEventBinder( wxEVT_GRID_EDITOR_CREATED )
}

//---------------------------------------------------------------------------

%init %{
%}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

