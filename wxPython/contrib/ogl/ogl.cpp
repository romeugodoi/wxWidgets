/*
 * FILE : contrib/ogl/ogl.cpp
 * 
 * This file was automatically generated by :
 * Simplified Wrapper and Interface Generator (SWIG)
 * Version 1.1 (Build 883)
 * 
 * Portions Copyright (c) 1995-1998
 * The University of Utah and The Regents of the University of California.
 * Permission is granted to distribute this file in any manner provided
 * this notice remains intact.
 * 
 * Do not make changes to this file--changes will be lost!
 *
 */


#define SWIGCODE
/* Implementation : PYTHON */

#define SWIGPYTHON
#include <string.h>
#include <stdlib.h>
/* Definitions for Windows/Unix exporting */
#if defined(__WIN32__)
#   if defined(_MSC_VER)
#	define SWIGEXPORT(a) __declspec(dllexport) a
#   else
#	if defined(__BORLANDC__)
#	    define SWIGEXPORT(a) a _export
#	else
#	    define SWIGEXPORT(a) a
#	endif
#   endif
#else
#   define SWIGEXPORT(a) a
#endif

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void SWIG_MakePtr(char *, void *, char *);
extern void SWIG_RegisterMapping(char *, char *, void *(*)(void *));
extern char *SWIG_GetPtr(char *, void **, char *);
extern char *SWIG_GetPtrObj(PyObject *, void **, char *);
extern void SWIG_addvarlink(PyObject *, char *, PyObject *(*)(void), int (*)(PyObject *));
extern PyObject *SWIG_newvarlink(void);
#ifdef __cplusplus
}
#endif
#define SWIG_init    initoglc

#define SWIG_name    "oglc"

#include "export.h"
#include "oglhelpers.h"

static PyObject* l_output_helper(PyObject* target, PyObject* o) {
    PyObject*   o2;
    if (!target) {
        target = o;
    } else if (target == Py_None) {
        Py_DECREF(Py_None);
        target = o;
    } else {
        if (!PyList_Check(target)) {
            o2 = target;
            target = PyList_New(0);
            PyList_Append(target, o2);
	    Py_XDECREF(o2);
        }
        PyList_Append(target,o);
	Py_XDECREF(o);
    }
    return target;
}

static PyObject* t_output_helper(PyObject* target, PyObject* o) {
    PyObject*   o2;
    PyObject*   o3;

    if (!target) {
        target = o;
    } else if (target == Py_None) {
        Py_DECREF(Py_None);
        target = o;
    } else {
        if (!PyTuple_Check(target)) {
            o2 = target;
            target = PyTuple_New(1);
            PyTuple_SetItem(target, 0, o2);
        }
        o3 = PyTuple_New(1);
        PyTuple_SetItem(o3, 0, o);

        o2 = target;
        target = PySequence_Concat(o2, o3);
        Py_DECREF(o2);
        Py_DECREF(o3);
    }
    return target;
}

#if PYTHON_API_VERSION >= 1009
    static char* wxStringErrorMsg = "String or Unicode type required";
#else
    static char* wxStringErrorMsg = "string type is required for parameter";
#endif

//---------------------------------------------------------------------------
// This one will work for any class for the VERY generic cases, but beyond that
// the helper needs to know more about the type.

wxList* wxPy_wxListHelper(PyObject* pyList, char* className) {
    bool doSave = wxPyRestoreThread();
    if (!PyList_Check(pyList)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        wxPySaveThread(doSave);
        return NULL;
    }
    int count = PyList_Size(pyList);
    wxList* list = new wxList;
    if (! list) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate wxList object");
        wxPySaveThread(doSave);
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* pyo = PyList_GetItem(pyList, x);
        wxObject* wxo = NULL;

        if (SWIG_GetPtrObj(pyo, (void **)&wxo, className)) {
            char errmsg[1024];
            sprintf(errmsg, "Type error, expected list of %s objects", className);
            PyErr_SetString(PyExc_TypeError, errmsg);
            wxPySaveThread(doSave);
            return NULL;
        }
        list->Append(wxo);
    }
    wxPySaveThread(doSave);
    return list;
}

//---------------------------------------------------------------------------

wxList* wxPy_wxRealPoint_ListHelper(PyObject* pyList) {
    bool doSave = wxPyRestoreThread();
    if (!PyList_Check(pyList)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        wxPySaveThread(doSave);
        return NULL;
    }
    int count = PyList_Size(pyList);
    wxList* list = new wxList;
    if (! list) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate wxList object");
        wxPySaveThread(doSave);
        return NULL;
    }
    for (int x=0; x<count; x++) {
        PyObject* pyo = PyList_GetItem(pyList, x);

        if (PyTuple_Check(pyo)) {
            PyObject* o1 = PyNumber_Float(PyTuple_GetItem(pyo, 0));
            PyObject* o2 = PyNumber_Float(PyTuple_GetItem(pyo, 1));

            double val1 = (o1 ? PyFloat_AsDouble(o1) : 0.0);
            double val2 = (o2 ? PyFloat_AsDouble(o2) : 0.0);

            list->Append((wxObject*) new wxRealPoint(val1, val2));

        } else {
            wxRealPoint* wxo = NULL;
            if (SWIG_GetPtrObj(pyo, (void **)&wxo, "_wxRealPoint_p")) {
                PyErr_SetString(PyExc_TypeError, "Type error, expected list of wxRealPoint objects or 2-tuples");
                wxPySaveThread(doSave);
                return NULL;
            }
            list->Append((wxObject*) new wxRealPoint(*wxo));
        }
    }
    wxPySaveThread(doSave);
    return list;
}


//---------------------------------------------------------------------------


extern "C" SWIGEXPORT(void) initoglbasicc();
extern "C" SWIGEXPORT(void) initoglshapesc();
extern "C" SWIGEXPORT(void) initoglshapes2c();
extern "C" SWIGEXPORT(void) initoglcanvasc();
#ifdef __cplusplus
extern "C" {
#endif
static PyObject *_wrap_wxOGLInitialize(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject * _resultobj;
    char *_kwnames[] = {  NULL };

    self = self;
    if(!PyArg_ParseTupleAndKeywords(args,kwargs,":wxOGLInitialize",_kwnames)) 
        return NULL;
{
    wxPy_BEGIN_ALLOW_THREADS;
        wxOGLInitialize();

    wxPy_END_ALLOW_THREADS;
}    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyObject *_wrap_wxOGLCleanUp(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject * _resultobj;
    char *_kwnames[] = {  NULL };

    self = self;
    if(!PyArg_ParseTupleAndKeywords(args,kwargs,":wxOGLCleanUp",_kwnames)) 
        return NULL;
{
    wxPy_BEGIN_ALLOW_THREADS;
        wxOGLCleanUp();

    wxPy_END_ALLOW_THREADS;
}    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyMethodDef oglcMethods[] = {
	 { "wxOGLCleanUp", (PyCFunction) _wrap_wxOGLCleanUp, METH_VARARGS | METH_KEYWORDS },
	 { "wxOGLInitialize", (PyCFunction) _wrap_wxOGLInitialize, METH_VARARGS | METH_KEYWORDS },
	 { NULL, NULL }
};
#ifdef __cplusplus
}
#endif
/*
 * This table is used by the pointer type-checker
 */
static struct { char *n1; char *n2; void *(*pcnv)(void *); } _swig_mapping[] = {
    { "_wxAcceleratorTable","_class_wxAcceleratorTable",0},
    { "_wxEvent","_class_wxEvent",0},
    { "_class_wxActivateEvent","_wxActivateEvent",0},
    { "_signed_long","_long",0},
    { "_wxMenuEvent","_class_wxMenuEvent",0},
    { "_class_wxProcessEvent","_wxProcessEvent",0},
    { "_class_wxJPEGHandler","_wxJPEGHandler",0},
    { "_class_wxFSFile","_wxFSFile",0},
    { "_wxPyBitmapDataObject","_class_wxPyBitmapDataObject",0},
    { "_wxBitmapDataObject","_class_wxBitmapDataObject",0},
    { "_class_wxPyCommandEvent","_wxPyCommandEvent",0},
    { "_wxBMPHandler","_class_wxBMPHandler",0},
    { "_wxImage","_class_wxImage",0},
    { "_wxFlexGridSizer","_class_wxFlexGridSizer",0},
    { "_wxWindowDisabler","_class_wxWindowDisabler",0},
    { "_class_wxDateTime","_wxDateTime",0},
    { "_wxPrintQuality","_wxCoord",0},
    { "_wxPrintQuality","_int",0},
    { "_wxPrintQuality","_signed_int",0},
    { "_wxPrintQuality","_unsigned_int",0},
    { "_wxPrintQuality","_wxWindowID",0},
    { "_wxPrintQuality","_uint",0},
    { "_wxPrintQuality","_EBool",0},
    { "_wxPrintQuality","_size_t",0},
    { "_wxPrintQuality","_time_t",0},
    { "_class_wxCustomDataObject","_wxCustomDataObject",0},
    { "_wxSpinCtrl","_class_wxSpinCtrl",0},
    { "_wxFontData","_class_wxFontData",0},
    { "_class_wxRegionIterator","_wxRegionIterator",0},
    { "_class_wxPyTextDropTarget","_wxPyTextDropTarget",0},
    { "_class_wxMenuBar","_wxMenuBar",0},
    { "_class_wxPyTreeItemData","_wxPyTreeItemData",0},
    { "_class_wxStaticBoxSizer","_wxStaticBoxSizer",0},
    { "_class_wxEvtHandler","_wxEvtHandler",0},
    { "_wxPaintEvent","_class_wxPaintEvent",0},
    { "_wxGIFHandler","_class_wxGIFHandler",0},
    { "_wxPySizer","_class_wxPySizer",0},
    { "_wxInternetFSHandler","_class_wxInternetFSHandler",0},
    { "_wxPyCompositeShape","_class_wxPyCompositeShape",0},
    { "_wxIndividualLayoutConstraint","_class_wxIndividualLayoutConstraint",0},
    { "_wxCursor","_class_wxCursor",0},
    { "_wxNotifyEvent","_class_wxNotifyEvent",0},
    { "_wxPyProcess","_class_wxPyProcess",0},
    { "_wxPyTreeCtrl","_class_wxPyTreeCtrl",0},
    { "_wxImageHandler","_class_wxImageHandler",0},
    { "_class_wxPyRectangleShape","_wxPyRectangleShape",0},
    { "_wxMutexGuiLocker","_class_wxMutexGuiLocker",0},
    { "_wxLog","_class_wxLog",0},
    { "_class_wxToolBarBase","_wxToolBarBase",0},
    { "_wxMask","_class_wxMask",0},
    { "_wxToolTip","_class_wxToolTip",0},
    { "_wxPNGHandler","_class_wxPNGHandler",0},
    { "_class_wxOGLConstraint","_wxOGLConstraint",0},
    { "_class_wxColourData","_wxColourData",0},
    { "_class_wxPageSetupDialogData","_wxPageSetupDialogData",0},
    { "_wxPrinter","_class_wxPrinter",0},
    { "_wxPseudoMetaFile","_class_wxPseudoMetaFile",0},
    { "_class_wxArrowHead","_wxArrowHead",0},
    { "_wxPen","_class_wxPen",0},
    { "_wxUpdateUIEvent","_class_wxUpdateUIEvent",0},
    { "_class_wxNotebookSizer","_wxNotebookSizer",0},
    { "_byte","_unsigned_char",0},
    { "_wxDataObject","_class_wxDataObject",0},
    { "_class_wxPyFontEnumerator","_wxPyFontEnumerator",0},
    { "_wxStaticBox","_class_wxStaticBox",0},
    { "_wxColourDatabase","_class_wxColourDatabase",0},
    { "_wxPyDataObjectSimple","_class_wxPyDataObjectSimple",0},
    { "_wxPyDropSource","_class_wxPyDropSource",0},
    { "_wxChoice","_class_wxChoice",0},
    { "_wxSlider","_class_wxSlider",0},
    { "_wxNotebookEvent","_class_wxNotebookEvent",0},
    { "_wxPyPrintout","_class_wxPyPrintout",0},
    { "_wxShapeRegion","_class_wxShapeRegion",0},
    { "_long","_unsigned_long",0},
    { "_long","_signed_long",0},
    { "_wxImageList","_class_wxImageList",0},
    { "_wxDataObjectSimple","_class_wxDataObjectSimple",0},
    { "_wxDropFilesEvent","_class_wxDropFilesEvent",0},
    { "_wxBitmapButton","_class_wxBitmapButton",0},
    { "_wxSashWindow","_class_wxSashWindow",0},
    { "_class_wxSizer","_wxSizer",0},
    { "_class_wxTIFFHandler","_wxTIFFHandler",0},
    { "_class_wxPrintDialogData","_wxPrintDialogData",0},
    { "_wxGridSizer","_class_wxGridSizer",0},
    { "_class_wxAcceleratorTable","_wxAcceleratorTable",0},
    { "_class_wxClipboard","_wxClipboard",0},
    { "_class_wxGauge","_wxGauge",0},
    { "_class_wxSashEvent","_wxSashEvent",0},
    { "_wxDC","_class_wxDC",0},
    { "_wxSizerItem","_class_wxSizerItem",0},
    { "_class_wxBitmapDataObject","_wxBitmapDataObject",0},
    { "_wxListEvent","_class_wxListEvent",0},
    { "_class_wxSingleChoiceDialog","_wxSingleChoiceDialog",0},
    { "_wxProgressDialog","_class_wxProgressDialog",0},
    { "_class_wxBMPHandler","_wxBMPHandler",0},
    { "_wxPrintPreview","_class_wxPrintPreview",0},
    { "_class_wxFlexGridSizer","_wxFlexGridSizer",0},
    { "_wxSpinEvent","_class_wxSpinEvent",0},
    { "_wxSashLayoutWindow","_class_wxSashLayoutWindow",0},
    { "_wxPyBitmapShape","_class_wxPyBitmapShape",0},
    { "_class_wxPyEllipseShape","_wxPyEllipseShape",0},
    { "_size_t","_wxCoord",0},
    { "_size_t","_wxPrintQuality",0},
    { "_size_t","_time_t",0},
    { "_size_t","_unsigned_int",0},
    { "_size_t","_int",0},
    { "_size_t","_wxWindowID",0},
    { "_size_t","_uint",0},
    { "_class_wxRealPoint","_wxRealPoint",0},
    { "_wxNavigationKeyEvent","_class_wxNavigationKeyEvent",0},
    { "_wxPNMHandler","_class_wxPNMHandler",0},
    { "_wxWindowCreateEvent","_class_wxWindowCreateEvent",0},
    { "_wxLogGui","_class_wxLogGui",0},
    { "_class_wxPyShapeEvtHandler","_wxPyShapeEvtHandler",0},
    { "_class_wxMenuItem","_wxMenuItem",0},
    { "_class_wxPaintEvent","_wxPaintEvent",0},
    { "_wxSysColourChangedEvent","_class_wxSysColourChangedEvent",0},
    { "_class_wxStatusBar","_wxStatusBar",0},
    { "_class_wxGIFHandler","_wxGIFHandler",0},
    { "_class_wxPySizer","_wxPySizer",0},
    { "_class_wxPyCompositeShape","_wxPyCompositeShape",0},
    { "_wxPyPolygonShape","_class_wxPyPolygonShape",0},
    { "_class_wxPostScriptDC","_wxPostScriptDC",0},
    { "_wxPanel","_class_wxPanel",0},
    { "_wxInitDialogEvent","_class_wxInitDialogEvent",0},
    { "_wxCheckBox","_class_wxCheckBox",0},
    { "_class_wxPyTreeCtrl","_wxPyTreeCtrl",0},
    { "_wxPyEvent","_class_wxPyEvent",0},
    { "_wxTextCtrl","_class_wxTextCtrl",0},
    { "_class_wxMask","_wxMask",0},
    { "_wxTextDataObject","_class_wxTextDataObject",0},
    { "_class_wxKeyEvent","_wxKeyEvent",0},
    { "_class_wxToolTip","_wxToolTip",0},
    { "_class_wxPNGHandler","_wxPNGHandler",0},
    { "_wxFileConfig","_class_wxFileConfig",0},
    { "_wxColour","_class_wxColour",0},
    { "_class_wxDialog","_wxDialog",0},
    { "_wxBusyCursor","_class_wxBusyCursor",0},
    { "_wxPageSetupDialog","_class_wxPageSetupDialog",0},
    { "_class_wxPrinter","_wxPrinter",0},
    { "_class_wxFileDataObject","_wxFileDataObject",0},
    { "_wxIdleEvent","_class_wxIdleEvent",0},
    { "_class_wxUpdateUIEvent","_wxUpdateUIEvent",0},
    { "_wxToolBar","_class_wxToolBar",0},
    { "_class_wxDataObject","_wxDataObject",0},
    { "_wxCaret","_class_wxCaret",0},
    { "_wxStaticLine","_class_wxStaticLine",0},
    { "_class_wxLayoutAlgorithm","_wxLayoutAlgorithm",0},
    { "_wxBrush","_class_wxBrush",0},
    { "_wxToggleButton","_class_wxToggleButton",0},
    { "_wxMiniFrame","_class_wxMiniFrame",0},
    { "_class_wxNotebookEvent","_wxNotebookEvent",0},
    { "_class_wxPyPrintout","_wxPyPrintout",0},
    { "_wxDataFormat","_class_wxDataFormat",0},
    { "_class_wxDataObjectSimple","_wxDataObjectSimple",0},
    { "_class_wxSashWindow","_wxSashWindow",0},
    { "_wxShowEvent","_class_wxShowEvent",0},
    { "_class_wxPyDivisionShape","_wxPyDivisionShape",0},
    { "_uint","_wxCoord",0},
    { "_uint","_wxPrintQuality",0},
    { "_uint","_time_t",0},
    { "_uint","_size_t",0},
    { "_uint","_unsigned_int",0},
    { "_uint","_int",0},
    { "_uint","_wxWindowID",0},
    { "_wxChar","_char",0},
    { "_wxPyValidator","_class_wxPyValidator",0},
    { "_class_wxEvent","_wxEvent",0},
    { "_wxCheckListBox","_class_wxCheckListBox",0},
    { "_wxSplitterEvent","_class_wxSplitterEvent",0},
    { "_wxRect","_class_wxRect",0},
    { "_wxCommandEvent","_class_wxCommandEvent",0},
    { "_wxPyShapeCanvas","_class_wxPyShapeCanvas",0},
    { "_wxSizeEvent","_class_wxSizeEvent",0},
    { "_class_wxLogWindow","_wxLogWindow",0},
    { "_class_wxImage","_wxImage",0},
    { "_wxPoint","_class_wxPoint",0},
    { "_class_wxWindowDisabler","_wxWindowDisabler",0},
    { "_class_wxSashLayoutWindow","_wxSashLayoutWindow",0},
    { "_class_wxPyBitmapShape","_wxPyBitmapShape",0},
    { "_class_wxButton","_wxButton",0},
    { "_wxRadioBox","_class_wxRadioBox",0},
    { "_class_wxSpinCtrl","_wxSpinCtrl",0},
    { "_class_wxFontData","_wxFontData",0},
    { "_class_wxPNMHandler","_wxPNMHandler",0},
    { "_wxBoxSizer","_class_wxBoxSizer",0},
    { "_class_wxZipFSHandler","_wxZipFSHandler",0},
    { "_char","_wxChar",0},
    { "_wxBitmap","_class_wxBitmap",0},
    { "_wxPenList","_class_wxPenList",0},
    { "_wxPrintDialog","_class_wxPrintDialog",0},
    { "_wxPyControlPoint","_class_wxPyControlPoint",0},
    { "_wxWindowDC","_class_wxWindowDC",0},
    { "_wxTimerEvent","_class_wxTimerEvent",0},
    { "_wxPyTimer","_class_wxPyTimer",0},
    { "_wxScrollBar","_class_wxScrollBar",0},
    { "_wxSpinButton","_class_wxSpinButton",0},
    { "_wxColourDialog","_class_wxColourDialog",0},
    { "_wxPrintData","_class_wxPrintData",0},
    { "_class_wxInternetFSHandler","_wxInternetFSHandler",0},
    { "_class_wxIndividualLayoutConstraint","_wxIndividualLayoutConstraint",0},
    { "_class_wxNotifyEvent","_wxNotifyEvent",0},
    { "_wxMessageDialog","_class_wxMessageDialog",0},
    { "_class_wxValidator","_wxValidator",0},
    { "_class_wxPyEvent","_wxPyEvent",0},
    { "_class_wxMutexGuiLocker","_wxMutexGuiLocker",0},
    { "_wxTextEntryDialog","_class_wxTextEntryDialog",0},
    { "_wxConfig","_class_wxConfig",0},
    { "_class_wxIconizeEvent","_wxIconizeEvent",0},
    { "_class_wxStaticBitmap","_wxStaticBitmap",0},
    { "_class_wxFileConfig","_wxFileConfig",0},
    { "_class_wxPyDrawnShape","_wxPyDrawnShape",0},
    { "_class_wxBusyCursor","_wxBusyCursor",0},
    { "_wxToolBarSimple","_class_wxToolBarSimple",0},
    { "_wxMDIChildFrame","_class_wxMDIChildFrame",0},
    { "_wxListItem","_class_wxListItem",0},
    { "_class_wxPseudoMetaFile","_wxPseudoMetaFile",0},
    { "_class_wxToolBar","_wxToolBar",0},
    { "_wxDropTarget","_class_wxDropTarget",0},
    { "_class_wxStaticLine","_wxStaticLine",0},
    { "_class_wxColourDatabase","_wxColourDatabase",0},
    { "_wxScrollEvent","_class_wxScrollEvent",0},
    { "_wxToolBarToolBase","_class_wxToolBarToolBase",0},
    { "_wxCalculateLayoutEvent","_class_wxCalculateLayoutEvent",0},
    { "_class_wxMemoryFSHandler","_wxMemoryFSHandler",0},
    { "_class_wxShapeRegion","_wxShapeRegion",0},
    { "_EBool","_wxCoord",0},
    { "_EBool","_wxPrintQuality",0},
    { "_EBool","_signed_int",0},
    { "_EBool","_int",0},
    { "_EBool","_wxWindowID",0},
    { "_class_wxRegion","_wxRegion",0},
    { "_class_wxDataFormat","_wxDataFormat",0},
    { "_class_wxDropFilesEvent","_wxDropFilesEvent",0},
    { "_wxWindowDestroyEvent","_class_wxWindowDestroyEvent",0},
    { "_class_wxPreviewFrame","_wxPreviewFrame",0},
    { "_wxStaticText","_class_wxStaticText",0},
    { "_wxFont","_class_wxFont",0},
    { "_class_wxPyDropTarget","_wxPyDropTarget",0},
    { "_wxCloseEvent","_class_wxCloseEvent",0},
    { "_class_wxSplitterEvent","_wxSplitterEvent",0},
    { "_wxProcessEvent","_class_wxProcessEvent",0},
    { "_wxNotebook","_class_wxNotebook",0},
    { "_wxFSFile","_class_wxFSFile",0},
    { "_unsigned_long","_long",0},
    { "_class_wxRect","_wxRect",0},
    { "_class_wxDC","_wxDC",0},
    { "_wxScrollWinEvent","_class_wxScrollWinEvent",0},
    { "_wxPyCircleShape","_class_wxPyCircleShape",0},
    { "_class_wxPyShapeCanvas","_wxPyShapeCanvas",0},
    { "_wxGenericDragImage","_class_wxGenericDragImage",0},
    { "_class_wxProgressDialog","_wxProgressDialog",0},
    { "_class_wxBrushList","_wxBrushList",0},
    { "_wxQueryNewPaletteEvent","_class_wxQueryNewPaletteEvent",0},
    { "_wxPyInputStream","_class_wxPyInputStream",0},
    { "_wxPyApp","_class_wxPyApp",0},
    { "_class_wxPenList","_wxPenList",0},
    { "_class_wxWindowCreateEvent","_wxWindowCreateEvent",0},
    { "_class_wxOutputStream","_wxOutputStream",0},
    { "_wxLogTextCtrl","_class_wxLogTextCtrl",0},
    { "_wxMDIParentFrame","_class_wxMDIParentFrame",0},
    { "_class_wxTreeEvent","_wxTreeEvent",0},
    { "_class_wxDirDialog","_wxDirDialog",0},
    { "_wxTimeSpan","_class_wxTimeSpan",0},
    { "_wxPyLineShape","_class_wxPyLineShape",0},
    { "_wxFocusEvent","_class_wxFocusEvent",0},
    { "_wxMaximizeEvent","_class_wxMaximizeEvent",0},
    { "_class_wxTimerEvent","_wxTimerEvent",0},
    { "_class_wxPyTimer","_wxPyTimer",0},
    { "_class_wxSpinButton","_wxSpinButton",0},
    { "_class_wxPyPolygonShape","_wxPyPolygonShape",0},
    { "_wxAcceleratorEntry","_class_wxAcceleratorEntry",0},
    { "_class_wxPanel","_wxPanel",0},
    { "_class_wxCheckBox","_wxCheckBox",0},
    { "_wxComboBox","_class_wxComboBox",0},
    { "_wxRadioButton","_class_wxRadioButton",0},
    { "_class_wxMessageDialog","_wxMessageDialog",0},
    { "_signed_int","_wxCoord",0},
    { "_signed_int","_wxPrintQuality",0},
    { "_signed_int","_EBool",0},
    { "_signed_int","_wxWindowID",0},
    { "_signed_int","_int",0},
    { "_class_wxTextCtrl","_wxTextCtrl",0},
    { "_class_wxListItemAttr","_wxListItemAttr",0},
    { "_wxLayoutConstraints","_class_wxLayoutConstraints",0},
    { "_class_wxTextDataObject","_wxTextDataObject",0},
    { "_wxMenu","_class_wxMenu",0},
    { "_class_wxMoveEvent","_wxMoveEvent",0},
    { "_wxListBox","_class_wxListBox",0},
    { "_wxScreenDC","_class_wxScreenDC",0},
    { "_class_wxToolBarSimple","_wxToolBarSimple",0},
    { "_class_wxMDIChildFrame","_wxMDIChildFrame",0},
    { "_wxArrowHead","_class_wxArrowHead",0},
    { "_WXTYPE","_wxDateTime_t",0},
    { "_WXTYPE","_short",0},
    { "_WXTYPE","_signed_short",0},
    { "_WXTYPE","_unsigned_short",0},
    { "_wxFileDialog","_class_wxFileDialog",0},
    { "_class_wxDropTarget","_wxDropTarget",0},
    { "_class_wxCaret","_wxCaret",0},
    { "_class_wxMDIClientWindow","_wxMDIClientWindow",0},
    { "_class_wxBrush","_wxBrush",0},
    { "_wxTipProvider","_class_wxTipProvider",0},
    { "_unsigned_short","_wxDateTime_t",0},
    { "_unsigned_short","_WXTYPE",0},
    { "_unsigned_short","_short",0},
    { "_class_wxWindow","_wxWindow",0},
    { "_class_wxLogStderr","_wxLogStderr",0},
    { "_wxSplitterWindow","_class_wxSplitterWindow",0},
    { "_wxDateSpan","_class_wxDateSpan",0},
    { "_class_wxStaticText","_wxStaticText",0},
    { "_wxPrintDialogData","_class_wxPrintDialogData",0},
    { "_class_wxFont","_wxFont",0},
    { "_wxClipboard","_class_wxClipboard",0},
    { "_class_wxPyValidator","_wxPyValidator",0},
    { "_class_wxCloseEvent","_wxCloseEvent",0},
    { "_wxSashEvent","_class_wxSashEvent",0},
    { "_wxBusyInfo","_class_wxBusyInfo",0},
    { "_wxFontList","_class_wxFontList",0},
    { "_class_wxMenuEvent","_wxMenuEvent",0},
    { "_wxPaletteChangedEvent","_class_wxPaletteChangedEvent",0},
    { "_class_wxPyBitmapDataObject","_wxPyBitmapDataObject",0},
    { "_class_wxPyCircleShape","_wxPyCircleShape",0},
    { "_wxClientDC","_class_wxClientDC",0},
    { "_wxMouseEvent","_class_wxMouseEvent",0},
    { "_class_wxGenericDragImage","_wxGenericDragImage",0},
    { "_wxListCtrl","_class_wxListCtrl",0},
    { "_wxSingleChoiceDialog","_class_wxSingleChoiceDialog",0},
    { "_wxPyDividedShape","_class_wxPyDividedShape",0},
    { "_class_wxPoint","_wxPoint",0},
    { "_class_wxPyInputStream","_wxPyInputStream",0},
    { "_wxRealPoint","_class_wxRealPoint",0},
    { "_class_wxRadioBox","_wxRadioBox",0},
    { "_class_wxBoxSizer","_wxBoxSizer",0},
    { "_signed_short","_WXTYPE",0},
    { "_signed_short","_short",0},
    { "_wxMemoryDC","_class_wxMemoryDC",0},
    { "_wxPyTextDataObject","_class_wxPyTextDataObject",0},
    { "_class_wxPrintDialog","_wxPrintDialog",0},
    { "_wxPyFileSystemHandler","_class_wxPyFileSystemHandler",0},
    { "_class_wxPyControlPoint","_wxPyControlPoint",0},
    { "_wxPaintDC","_class_wxPaintDC",0},
    { "_class_wxWindowDC","_wxWindowDC",0},
    { "_class_wxFocusEvent","_wxFocusEvent",0},
    { "_class_wxMaximizeEvent","_wxMaximizeEvent",0},
    { "_wxStatusBar","_class_wxStatusBar",0},
    { "_class_wxAcceleratorEntry","_wxAcceleratorEntry",0},
    { "_class_wxCursor","_wxCursor",0},
    { "_wxPostScriptDC","_class_wxPostScriptDC",0},
    { "_wxPyFileDropTarget","_class_wxPyFileDropTarget",0},
    { "_class_wxPyProcess","_wxPyProcess",0},
    { "_class_wxImageHandler","_wxImageHandler",0},
    { "_wxPyShape","_class_wxPyShape",0},
    { "_wxScrolledWindow","_class_wxScrolledWindow",0},
    { "_class_wxLog","_wxLog",0},
    { "_wxTreeItemId","_class_wxTreeItemId",0},
    { "_unsigned_char","_byte",0},
    { "_class_wxMenu","_wxMenu",0},
    { "_wxControl","_class_wxControl",0},
    { "_class_wxListBox","_wxListBox",0},
    { "_unsigned_int","_wxCoord",0},
    { "_unsigned_int","_wxPrintQuality",0},
    { "_unsigned_int","_time_t",0},
    { "_unsigned_int","_size_t",0},
    { "_unsigned_int","_uint",0},
    { "_unsigned_int","_wxWindowID",0},
    { "_unsigned_int","_int",0},
    { "_wxIcon","_class_wxIcon",0},
    { "_wxDialog","_class_wxDialog",0},
    { "_class_wxListItem","_wxListItem",0},
    { "_class_wxPen","_wxPen",0},
    { "_class_wxFileDialog","_wxFileDialog",0},
    { "_wxQueryLayoutInfoEvent","_class_wxQueryLayoutInfoEvent",0},
    { "_wxConfigBase","_class_wxConfigBase",0},
    { "_short","_wxDateTime_t",0},
    { "_short","_WXTYPE",0},
    { "_short","_unsigned_short",0},
    { "_short","_signed_short",0},
    { "_class_wxStaticBox","_wxStaticBox",0},
    { "_wxLayoutAlgorithm","_class_wxLayoutAlgorithm",0},
    { "_wxPyTextShape","_class_wxPyTextShape",0},
    { "_class_wxPyDataObjectSimple","_wxPyDataObjectSimple",0},
    { "_class_wxPyDropSource","_wxPyDropSource",0},
    { "_class_wxScrollEvent","_wxScrollEvent",0},
    { "_wxJoystickEvent","_class_wxJoystickEvent",0},
    { "_class_wxChoice","_wxChoice",0},
    { "_class_wxSlider","_wxSlider",0},
    { "_class_wxCalculateLayoutEvent","_wxCalculateLayoutEvent",0},
    { "_class_wxImageList","_wxImageList",0},
    { "_class_wxBitmapButton","_wxBitmapButton",0},
    { "_wxFileSystemHandler","_class_wxFileSystemHandler",0},
    { "_wxPyTipProvider","_class_wxPyTipProvider",0},
    { "_wxFrame","_class_wxFrame",0},
    { "_wxPCXHandler","_class_wxPCXHandler",0},
    { "_class_wxGridSizer","_wxGridSizer",0},
    { "_wxPyDivisionShape","_class_wxPyDivisionShape",0},
    { "_class_wxPaletteChangedEvent","_wxPaletteChangedEvent",0},
    { "_class_wxNotebook","_wxNotebook",0},
    { "_wxJPEGHandler","_class_wxJPEGHandler",0},
    { "_wxWindowID","_wxCoord",0},
    { "_wxWindowID","_wxPrintQuality",0},
    { "_wxWindowID","_time_t",0},
    { "_wxWindowID","_size_t",0},
    { "_wxWindowID","_EBool",0},
    { "_wxWindowID","_uint",0},
    { "_wxWindowID","_int",0},
    { "_wxWindowID","_signed_int",0},
    { "_wxWindowID","_unsigned_int",0},
    { "_class_wxScrollWinEvent","_wxScrollWinEvent",0},
    { "_class_wxSizerItem","_wxSizerItem",0},
    { "_int","_wxCoord",0},
    { "_int","_wxPrintQuality",0},
    { "_int","_time_t",0},
    { "_int","_size_t",0},
    { "_int","_EBool",0},
    { "_int","_uint",0},
    { "_int","_wxWindowID",0},
    { "_int","_unsigned_int",0},
    { "_int","_signed_int",0},
    { "_class_wxMouseEvent","_wxMouseEvent",0},
    { "_wxPyCommandEvent","_class_wxPyCommandEvent",0},
    { "_wxLogWindow","_class_wxLogWindow",0},
    { "_class_wxListEvent","_wxListEvent",0},
    { "_class_wxPrintPreview","_wxPrintPreview",0},
    { "_wxDateTime_t","_unsigned_short",0},
    { "_wxDateTime_t","_short",0},
    { "_wxDateTime_t","_WXTYPE",0},
    { "_class_wxSpinEvent","_wxSpinEvent",0},
    { "_class_wxQueryNewPaletteEvent","_wxQueryNewPaletteEvent",0},
    { "_wxDateTime","_class_wxDateTime",0},
    { "_time_t","_wxCoord",0},
    { "_time_t","_wxPrintQuality",0},
    { "_time_t","_unsigned_int",0},
    { "_time_t","_int",0},
    { "_time_t","_wxWindowID",0},
    { "_time_t","_uint",0},
    { "_time_t","_size_t",0},
    { "_class_wxNavigationKeyEvent","_wxNavigationKeyEvent",0},
    { "_wxLogNull","_class_wxLogNull",0},
    { "_wxButton","_class_wxButton",0},
    { "_wxZipFSHandler","_class_wxZipFSHandler",0},
    { "_class_wxPyApp","_wxPyApp",0},
    { "_wxSize","_class_wxSize",0},
    { "_wxRegionIterator","_class_wxRegionIterator",0},
    { "_class_wxPyTextDataObject","_wxPyTextDataObject",0},
    { "_class_wxLogTextCtrl","_wxLogTextCtrl",0},
    { "_class_wxLogGui","_wxLogGui",0},
    { "_class_wxMDIParentFrame","_wxMDIParentFrame",0},
    { "_wxPyTreeItemData","_class_wxPyTreeItemData",0},
    { "_wxStaticBoxSizer","_class_wxStaticBoxSizer",0},
    { "_class_wxTimeSpan","_wxTimeSpan",0},
    { "_class_wxPyFileSystemHandler","_wxPyFileSystemHandler",0},
    { "_class_wxPyLineShape","_wxPyLineShape",0},
    { "_class_wxPaintDC","_wxPaintDC",0},
    { "_class_wxSysColourChangedEvent","_wxSysColourChangedEvent",0},
    { "_class_wxPyFileDropTarget","_wxPyFileDropTarget",0},
    { "_class_wxInitDialogEvent","_wxInitDialogEvent",0},
    { "_class_wxComboBox","_wxComboBox",0},
    { "_class_wxRadioButton","_wxRadioButton",0},
    { "_class_wxPyShape","_wxPyShape",0},
    { "_wxValidator","_class_wxValidator",0},
    { "_wxToolBarBase","_class_wxToolBarBase",0},
    { "_class_wxTreeItemId","_wxTreeItemId",0},
    { "_class_wxLayoutConstraints","_wxLayoutConstraints",0},
    { "_wxIconizeEvent","_class_wxIconizeEvent",0},
    { "_class_wxControl","_wxControl",0},
    { "_wxStaticBitmap","_class_wxStaticBitmap",0},
    { "_wxPyDrawnShape","_class_wxPyDrawnShape",0},
    { "_class_wxIcon","_wxIcon",0},
    { "_class_wxColour","_wxColour",0},
    { "_class_wxScreenDC","_wxScreenDC",0},
    { "_class_wxPageSetupDialog","_wxPageSetupDialog",0},
    { "_wxPalette","_class_wxPalette",0},
    { "_class_wxIdleEvent","_wxIdleEvent",0},
    { "_class_wxConfigBase","_wxConfigBase",0},
    { "_wxCoord","_int",0},
    { "_wxCoord","_signed_int",0},
    { "_wxCoord","_unsigned_int",0},
    { "_wxCoord","_wxWindowID",0},
    { "_wxCoord","_uint",0},
    { "_wxCoord","_EBool",0},
    { "_wxCoord","_size_t",0},
    { "_wxCoord","_time_t",0},
    { "_wxCoord","_wxPrintQuality",0},
    { "_wxEraseEvent","_class_wxEraseEvent",0},
    { "_wxDataObjectComposite","_class_wxDataObjectComposite",0},
    { "_class_wxJoystickEvent","_wxJoystickEvent",0},
    { "_class_wxTipProvider","_wxTipProvider",0},
    { "_class_wxToggleButton","_wxToggleButton",0},
    { "_class_wxMiniFrame","_wxMiniFrame",0},
    { "_wxFontDialog","_class_wxFontDialog",0},
    { "_wxMemoryFSHandler","_class_wxMemoryFSHandler",0},
    { "_wxRegion","_class_wxRegion",0},
    { "_class_wxSplitterWindow","_wxSplitterWindow",0},
    { "_wxPreviewFrame","_class_wxPreviewFrame",0},
    { "_wxSizer","_class_wxSizer",0},
    { "_class_wxDateSpan","_wxDateSpan",0},
    { "_wxFileSystem","_class_wxFileSystem",0},
    { "_class_wxShowEvent","_wxShowEvent",0},
    { "_class_wxPyTipProvider","_wxPyTipProvider",0},
    { "_class_wxPCXHandler","_wxPCXHandler",0},
    { "_wxTIFFHandler","_class_wxTIFFHandler",0},
    { "_wxDiagram","_class_wxDiagram",0},
    { "_wxPyDropTarget","_class_wxPyDropTarget",0},
    { "_wxActivateEvent","_class_wxActivateEvent",0},
    { "_wxGauge","_class_wxGauge",0},
    { "_class_wxCheckListBox","_wxCheckListBox",0},
    { "_class_wxBusyInfo","_wxBusyInfo",0},
    { "_class_wxFontList","_wxFontList",0},
    { "_class_wxCommandEvent","_wxCommandEvent",0},
    { "_class_wxClientDC","_wxClientDC",0},
    { "_class_wxSizeEvent","_wxSizeEvent",0},
    { "_class_wxListCtrl","_wxListCtrl",0},
    { "_class_wxPyDividedShape","_wxPyDividedShape",0},
    { "_wxBrushList","_class_wxBrushList",0},
    { "_wxPyEllipseShape","_class_wxPyEllipseShape",0},
    { "_wxCustomDataObject","_class_wxCustomDataObject",0},
    { "_class_wxLogNull","_wxLogNull",0},
    { "_class_wxSize","_wxSize",0},
    { "_class_wxBitmap","_wxBitmap",0},
    { "_class_wxMemoryDC","_wxMemoryDC",0},
    { "_wxPyTextDropTarget","_class_wxPyTextDropTarget",0},
    { "_wxMenuBar","_class_wxMenuBar",0},
    { "_wxOutputStream","_class_wxOutputStream",0},
    { "_wxTreeEvent","_class_wxTreeEvent",0},
    { "_wxDirDialog","_class_wxDirDialog",0},
    { "_wxPyShapeEvtHandler","_class_wxPyShapeEvtHandler",0},
    { "_wxEvtHandler","_class_wxEvtHandler",0},
    { "_wxMenuItem","_class_wxMenuItem",0},
    { "_class_wxScrollBar","_wxScrollBar",0},
    { "_class_wxColourDialog","_wxColourDialog",0},
    { "_class_wxPrintData","_wxPrintData",0},
    { "_wxPyRectangleShape","_class_wxPyRectangleShape",0},
    { "_class_wxScrolledWindow","_wxScrolledWindow",0},
    { "_wxListItemAttr","_class_wxListItemAttr",0},
    { "_class_wxTextEntryDialog","_wxTextEntryDialog",0},
    { "_class_wxConfig","_wxConfig",0},
    { "_wxKeyEvent","_class_wxKeyEvent",0},
    { "_wxMoveEvent","_class_wxMoveEvent",0},
    { "_wxOGLConstraint","_class_wxOGLConstraint",0},
    { "_wxColourData","_class_wxColourData",0},
    { "_wxPageSetupDialogData","_class_wxPageSetupDialogData",0},
    { "_class_wxPalette","_wxPalette",0},
    { "_wxFileDataObject","_class_wxFileDataObject",0},
    { "_class_wxQueryLayoutInfoEvent","_wxQueryLayoutInfoEvent",0},
    { "_wxNotebookSizer","_class_wxNotebookSizer",0},
    { "_class_wxEraseEvent","_wxEraseEvent",0},
    { "_wxPyFontEnumerator","_class_wxPyFontEnumerator",0},
    { "_wxMDIClientWindow","_class_wxMDIClientWindow",0},
    { "_class_wxPyTextShape","_wxPyTextShape",0},
    { "_class_wxDataObjectComposite","_wxDataObjectComposite",0},
    { "_class_wxToolBarToolBase","_wxToolBarToolBase",0},
    { "_class_wxFontDialog","_wxFontDialog",0},
    { "_wxWindow","_class_wxWindow",0},
    { "_class_wxWindowDestroyEvent","_wxWindowDestroyEvent",0},
    { "_wxLogStderr","_class_wxLogStderr",0},
    { "_class_wxFileSystemHandler","_wxFileSystemHandler",0},
    { "_class_wxFileSystem","_wxFileSystem",0},
    { "_class_wxFrame","_wxFrame",0},
    { "_class_wxDiagram","_wxDiagram",0},
{0,0,0}};

static PyObject *SWIG_globals;
#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT(void) initoglc() {
	 PyObject *m, *d;
	 SWIG_globals = SWIG_newvarlink();
	 m = Py_InitModule("oglc", oglcMethods);
	 d = PyModule_GetDict(m);
	 PyDict_SetItemString(d,"KEY_SHIFT", PyInt_FromLong((long) KEY_SHIFT));
	 PyDict_SetItemString(d,"KEY_CTRL", PyInt_FromLong((long) KEY_CTRL));
	 PyDict_SetItemString(d,"ARROW_NONE", PyInt_FromLong((long) ARROW_NONE));
	 PyDict_SetItemString(d,"ARROW_END", PyInt_FromLong((long) ARROW_END));
	 PyDict_SetItemString(d,"ARROW_BOTH", PyInt_FromLong((long) ARROW_BOTH));
	 PyDict_SetItemString(d,"ARROW_MIDDLE", PyInt_FromLong((long) ARROW_MIDDLE));
	 PyDict_SetItemString(d,"ARROW_START", PyInt_FromLong((long) ARROW_START));
	 PyDict_SetItemString(d,"ARROW_HOLLOW_CIRCLE", PyInt_FromLong((long) ARROW_HOLLOW_CIRCLE));
	 PyDict_SetItemString(d,"ARROW_FILLED_CIRCLE", PyInt_FromLong((long) ARROW_FILLED_CIRCLE));
	 PyDict_SetItemString(d,"ARROW_ARROW", PyInt_FromLong((long) ARROW_ARROW));
	 PyDict_SetItemString(d,"ARROW_SINGLE_OBLIQUE", PyInt_FromLong((long) ARROW_SINGLE_OBLIQUE));
	 PyDict_SetItemString(d,"ARROW_DOUBLE_OBLIQUE", PyInt_FromLong((long) ARROW_DOUBLE_OBLIQUE));
	 PyDict_SetItemString(d,"ARROW_METAFILE", PyInt_FromLong((long) ARROW_METAFILE));
	 PyDict_SetItemString(d,"ARROW_POSITION_END", PyInt_FromLong((long) ARROW_POSITION_END));
	 PyDict_SetItemString(d,"ARROW_POSITION_START", PyInt_FromLong((long) ARROW_POSITION_START));
	 PyDict_SetItemString(d,"CONTROL_POINT_VERTICAL", PyInt_FromLong((long) CONTROL_POINT_VERTICAL));
	 PyDict_SetItemString(d,"CONTROL_POINT_HORIZONTAL", PyInt_FromLong((long) CONTROL_POINT_HORIZONTAL));
	 PyDict_SetItemString(d,"CONTROL_POINT_DIAGONAL", PyInt_FromLong((long) CONTROL_POINT_DIAGONAL));
	 PyDict_SetItemString(d,"CONTROL_POINT_ENDPOINT_TO", PyInt_FromLong((long) CONTROL_POINT_ENDPOINT_TO));
	 PyDict_SetItemString(d,"CONTROL_POINT_ENDPOINT_FROM", PyInt_FromLong((long) CONTROL_POINT_ENDPOINT_FROM));
	 PyDict_SetItemString(d,"CONTROL_POINT_LINE", PyInt_FromLong((long) CONTROL_POINT_LINE));
	 PyDict_SetItemString(d,"FORMAT_NONE", PyInt_FromLong((long) FORMAT_NONE));
	 PyDict_SetItemString(d,"FORMAT_CENTRE_HORIZ", PyInt_FromLong((long) FORMAT_CENTRE_HORIZ));
	 PyDict_SetItemString(d,"FORMAT_CENTRE_VERT", PyInt_FromLong((long) FORMAT_CENTRE_VERT));
	 PyDict_SetItemString(d,"FORMAT_SIZE_TO_CONTENTS", PyInt_FromLong((long) FORMAT_SIZE_TO_CONTENTS));
	 PyDict_SetItemString(d,"LINE_ALIGNMENT_HORIZ", PyInt_FromLong((long) LINE_ALIGNMENT_HORIZ));
	 PyDict_SetItemString(d,"LINE_ALIGNMENT_VERT", PyInt_FromLong((long) LINE_ALIGNMENT_VERT));
	 PyDict_SetItemString(d,"LINE_ALIGNMENT_TO_NEXT_HANDLE", PyInt_FromLong((long) LINE_ALIGNMENT_TO_NEXT_HANDLE));
	 PyDict_SetItemString(d,"LINE_ALIGNMENT_NONE", PyInt_FromLong((long) LINE_ALIGNMENT_NONE));
	 PyDict_SetItemString(d,"SHADOW_NONE", PyInt_FromLong((long) SHADOW_NONE));
	 PyDict_SetItemString(d,"SHADOW_LEFT", PyInt_FromLong((long) SHADOW_LEFT));
	 PyDict_SetItemString(d,"SHADOW_RIGHT", PyInt_FromLong((long) SHADOW_RIGHT));
	 PyDict_SetItemString(d,"OP_CLICK_LEFT", PyInt_FromLong((long) OP_CLICK_LEFT));
	 PyDict_SetItemString(d,"OP_CLICK_RIGHT", PyInt_FromLong((long) OP_CLICK_RIGHT));
	 PyDict_SetItemString(d,"OP_DRAG_LEFT", PyInt_FromLong((long) OP_DRAG_LEFT));
	 PyDict_SetItemString(d,"OP_DRAG_RIGHT", PyInt_FromLong((long) OP_DRAG_RIGHT));
	 PyDict_SetItemString(d,"OP_ALL", PyInt_FromLong((long) OP_ALL));
	 PyDict_SetItemString(d,"ATTACHMENT_MODE_NONE", PyInt_FromLong((long) ATTACHMENT_MODE_NONE));
	 PyDict_SetItemString(d,"ATTACHMENT_MODE_EDGE", PyInt_FromLong((long) ATTACHMENT_MODE_EDGE));
	 PyDict_SetItemString(d,"ATTACHMENT_MODE_BRANCHING", PyInt_FromLong((long) ATTACHMENT_MODE_BRANCHING));
	 PyDict_SetItemString(d,"BRANCHING_ATTACHMENT_NORMAL", PyInt_FromLong((long) BRANCHING_ATTACHMENT_NORMAL));
	 PyDict_SetItemString(d,"BRANCHING_ATTACHMENT_BLOB", PyInt_FromLong((long) BRANCHING_ATTACHMENT_BLOB));
	 PyDict_SetItemString(d,"gyCONSTRAINT_CENTRED_VERTICALLY", PyInt_FromLong((long) gyCONSTRAINT_CENTRED_VERTICALLY));
	 PyDict_SetItemString(d,"gyCONSTRAINT_CENTRED_HORIZONTALLY", PyInt_FromLong((long) gyCONSTRAINT_CENTRED_HORIZONTALLY));
	 PyDict_SetItemString(d,"gyCONSTRAINT_CENTRED_BOTH", PyInt_FromLong((long) gyCONSTRAINT_CENTRED_BOTH));
	 PyDict_SetItemString(d,"gyCONSTRAINT_LEFT_OF", PyInt_FromLong((long) gyCONSTRAINT_LEFT_OF));
	 PyDict_SetItemString(d,"gyCONSTRAINT_RIGHT_OF", PyInt_FromLong((long) gyCONSTRAINT_RIGHT_OF));
	 PyDict_SetItemString(d,"gyCONSTRAINT_ABOVE", PyInt_FromLong((long) gyCONSTRAINT_ABOVE));
	 PyDict_SetItemString(d,"gyCONSTRAINT_BELOW", PyInt_FromLong((long) gyCONSTRAINT_BELOW));
	 PyDict_SetItemString(d,"gyCONSTRAINT_ALIGNED_TOP", PyInt_FromLong((long) gyCONSTRAINT_ALIGNED_TOP));
	 PyDict_SetItemString(d,"gyCONSTRAINT_ALIGNED_BOTTOM", PyInt_FromLong((long) gyCONSTRAINT_ALIGNED_BOTTOM));
	 PyDict_SetItemString(d,"gyCONSTRAINT_ALIGNED_LEFT", PyInt_FromLong((long) gyCONSTRAINT_ALIGNED_LEFT));
	 PyDict_SetItemString(d,"gyCONSTRAINT_ALIGNED_RIGHT", PyInt_FromLong((long) gyCONSTRAINT_ALIGNED_RIGHT));
	 PyDict_SetItemString(d,"gyCONSTRAINT_MIDALIGNED_TOP", PyInt_FromLong((long) gyCONSTRAINT_MIDALIGNED_TOP));
	 PyDict_SetItemString(d,"gyCONSTRAINT_MIDALIGNED_BOTTOM", PyInt_FromLong((long) gyCONSTRAINT_MIDALIGNED_BOTTOM));
	 PyDict_SetItemString(d,"gyCONSTRAINT_MIDALIGNED_LEFT", PyInt_FromLong((long) gyCONSTRAINT_MIDALIGNED_LEFT));
	 PyDict_SetItemString(d,"gyCONSTRAINT_MIDALIGNED_RIGHT", PyInt_FromLong((long) gyCONSTRAINT_MIDALIGNED_RIGHT));
	 PyDict_SetItemString(d,"DIVISION_SIDE_NONE", PyInt_FromLong((long) DIVISION_SIDE_NONE));
	 PyDict_SetItemString(d,"DIVISION_SIDE_LEFT", PyInt_FromLong((long) DIVISION_SIDE_LEFT));
	 PyDict_SetItemString(d,"DIVISION_SIDE_TOP", PyInt_FromLong((long) DIVISION_SIDE_TOP));
	 PyDict_SetItemString(d,"DIVISION_SIDE_RIGHT", PyInt_FromLong((long) DIVISION_SIDE_RIGHT));
	 PyDict_SetItemString(d,"DIVISION_SIDE_BOTTOM", PyInt_FromLong((long) DIVISION_SIDE_BOTTOM));


    initoglbasicc();
    initoglshapesc();
    initoglshapes2c();
    initoglcanvasc();


    wxClassInfo::CleanUpClasses();
    wxClassInfo::InitializeClasses();

{
   int i;
   for (i = 0; _swig_mapping[i].n1; i++)
        SWIG_RegisterMapping(_swig_mapping[i].n1,_swig_mapping[i].n2,_swig_mapping[i].pcnv);
}
}
