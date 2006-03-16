/////////////////////////////////////////////////////////////////////////////
// Name:        _vscroll.i
// Purpose:     SWIG interface defs for wxVScrolledWindow, wxVListBox, and
//              wxHtmlListBox
//
// Author:      Robin Dunn
//
// Created:     14-Aug-2003
// RCS-ID:      $Id$
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

%{
#include <wx/tipwin.h>
%}

//---------------------------------------------------------------------------
%newgroup;


// wxVScrolledWindow

%{
#include <wx/vscroll.h>
%}


// First, the C++ version
%{
class wxPyVScrolledWindow  : public wxVScrolledWindow
{
    DECLARE_ABSTRACT_CLASS(wxPyVScrolledWindow)
public:
    wxPyVScrolledWindow() : wxVScrolledWindow() {}

    wxPyVScrolledWindow(wxWindow *parent,
                        wxWindowID id = wxID_ANY,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = 0,
                        const wxString& name = wxPyPanelNameStr)
        : wxVScrolledWindow(parent, id, pos, size, style, name)
    {}

    // Overridable virtuals

    // this function must be overridden in the derived class and it should
    // return the height of the given line in pixels
    DEC_PYCALLBACK_COORD_SIZET_constpure(OnGetLineHeight);


    // this function doesn't have to be overridden but it may be useful to do
    // it if calculating the lines heights is a relatively expensive operation
    // as it gives the user code a possibility to calculate several of them at
    // once
    //
    // OnGetLinesHint() is normally called just before OnGetLineHeight() but you
    // shouldn't rely on the latter being called for all lines in the interval
    // specified here. It is also possible that OnGetLineHeight() will be
    // called for the lines outside of this interval, so this is really just a
    // hint, not a promise.
    //
    // finally note that lineMin is inclusive, while lineMax is exclusive, as
    // usual
    DEC_PYCALLBACK_VOID_SIZETSIZET_const(OnGetLinesHint);


    // when the number of lines changes, we try to estimate the total height
    // of all lines which is a rather expensive operation in terms of lines
    // access, so if the user code may estimate the average height
    // better/faster than we do, it should override this function to implement
    // its own logic
    //
    // this function should return the best guess for the total height it may
    // make
    DEC_PYCALLBACK_COORD_const(EstimateTotalHeight);


    // Also expose some other interesting protected methods


    // find the index of the line we need to show at the top of the window such
    // that the last (fully or partially) visible line is the given one
    size_t FindFirstFromBottom(size_t lineLast, bool fullyVisible = false)
    { return wxVScrolledWindow::FindFirstFromBottom(lineLast, fullyVisible); }

    // get the total height of the lines between lineMin (inclusive) and
    // lineMax (exclusive)
    wxCoord GetLinesHeight(size_t lineMin, size_t lineMax) const
    { return wxVScrolledWindow::GetLinesHeight(lineMin, lineMax); }


    PYPRIVATE;
};

IMPLEMENT_ABSTRACT_CLASS(wxPyVScrolledWindow, wxVScrolledWindow);

IMP_PYCALLBACK_COORD_SIZET_constpure(wxPyVScrolledWindow, wxVScrolledWindow, OnGetLineHeight);
IMP_PYCALLBACK_VOID_SIZETSIZET_const(wxPyVScrolledWindow, wxVScrolledWindow, OnGetLinesHint);
IMP_PYCALLBACK_COORD_const          (wxPyVScrolledWindow, wxVScrolledWindow, EstimateTotalHeight);
%}



// Now define this class for SWIG

/*
   In the name of this class, "V" may stand for "variable" because it can be
   used for scrolling lines of variable heights; "virtual" because it is not
   necessary to know the heights of all lines in advance -- only those which
   are shown on the screen need to be measured; or, even, "vertical" because
   this class only supports scrolling in one direction currently (this could
   and probably will change in the future however).

   In any case, this is a generalization of the wxScrolledWindow class which
   can be only used when all lines have the same height. It lacks some other
   wxScrolledWindow features however, notably it currently lacks support for
   horizontal scrolling; it can't scroll another window nor only a rectangle
   of the window and not its entire client area.
 */

MustHaveApp(wxPyVScrolledWindow);

%rename(VScrolledWindow) wxPyVScrolledWindow;
class wxPyVScrolledWindow : public wxPanel
{
public:
    %pythonAppend wxPyVScrolledWindow         "self._setOORInfo(self); self._setCallbackInfo(self, VScrolledWindow)"
    %pythonAppend wxPyVScrolledWindow()       ""
    

    wxPyVScrolledWindow(wxWindow *parent,
                        wxWindowID id = wxID_ANY,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = 0,
                        const wxString& name = wxPyPanelNameStr);

    %RenameCtor(PreVScrolledWindow, wxPyVScrolledWindow());

    void _setCallbackInfo(PyObject* self, PyObject* _class);

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxPyPanelNameStr);


    // set the number of lines the window contains: the derived class must
    // provide the heights for all lines with indices up to the one given here
    // in its OnGetLineHeight()
    void SetLineCount(size_t count);

    // scroll to the specified line: it will become the first visible line in
    // the window
    //
    // return True if we scrolled the window, False if nothing was done
    bool ScrollToLine(size_t line);

    // scroll by the specified number of lines/pages
    virtual bool ScrollLines(int lines);
    virtual bool ScrollPages(int pages);

    // redraw the specified line
    void RefreshLine(size_t line);

    // redraw all lines in the specified range (inclusive)
    void RefreshLines(size_t from, size_t to);

    // return the item at the specified (in physical coordinates) position or
    // wxNOT_FOUND if none, i.e. if it is below the last item
    %Rename(HitTestXY, int, HitTest(wxCoord x, wxCoord y) const);
    int HitTest(const wxPoint& pt) const;

    // recalculate all our parameters and redisplay all lines
    virtual void RefreshAll();


    // get the number of lines this window contains (previously set by
    // SetLineCount())
    size_t GetLineCount() const;

    // get the first currently visible line
    size_t GetVisibleBegin() const;

    // get the last currently visible line
    size_t GetVisibleEnd() const;

    // is this line currently visible?
    bool IsVisible(size_t line) const;

    // this is the same as GetVisibleBegin(), exists to match
    // GetLastVisibleLine() and for backwards compatibility only
    size_t GetFirstVisibleLine() const;

    // get the last currently visible line
    //
    // this function is unsafe as it returns (size_t)-1 (i.e. a huge positive
    // number) if the control is empty, use GetVisibleEnd() instead, this one
    // is kept for backwards compatibility
    size_t GetLastVisibleLine() const;

    // find the index of the line we need to show at the top of the window such
    // that the last (fully or partially) visible line is the given one
    size_t FindFirstFromBottom(size_t lineLast, bool fullyVisible = false);

    // get the total height of the lines between lineMin (inclusive) and
    // lineMax (exclusive)
    wxCoord GetLinesHeight(size_t lineMin, size_t lineMax) const;
};



// //----------------------------------------------------------------------------
// %newgroup;

// // wxHVScrolledWindow

// // First, the C++ version
// %{
// class wxPyHVScrolledWindow : public wxHVScrolledWindow
// {
//     DECLARE_ABSTRACT_CLASS(wxPyHVScrolledWindow)
// public:
//     wxPyHVScrolledWindow() : wxHVScrolledWindow() {}
//     wxPyHVScrolledWindow(wxWindow *parent,
//                          wxWindowID id = wxID_ANY,
//                          const wxPoint& pos = wxDefaultPosition,
//                          const wxSize& size = wxDefaultSize,
//                          long style = 0,
//                          const wxString& name = wxPyPanelNameStr)
//         : wxHVScrolledWindow(parent, id, pos, size, style, name) {}

//     // Overridable virtuals

//     // these functions must be overridden in the derived class and they should
//     // return the width or height of the given line in pixels
//     DEC_PYCALLBACK_COORD_SIZET_constpure(OnGetRowHeight);
//     DEC_PYCALLBACK_COORD_SIZET_constpure(OnGetColumnWidth);
    
//     // the following functions don't need to be overridden but it may be useful
//     // to do if calculating the lines widths or heights is a relatively
//     // expensive operation as it gives the user code a possibility to calculate
//     // several of them at once
//     //
//     // OnGetRowsHeightHint() and OnGetColumnsWidthHint() are normally called
//     // just before OnGetRowHeight() and OnGetColumnWidth(), respectively, but
//     // you shouldn't rely on the latter methods being called for all lines in
//     // the interval specified here. It is also possible that OnGetRowHeight()
//     // or OnGetColumnWidth() will be called for the lines outside of this
//     // interval, so this is really just a hint, not a promise.
//     //
//     // finally note that min is inclusive, while max is exclusive, as usual
//     DEC_PYCALLBACK_VOID_SIZETSIZET_const(OnGetRowsHeightHint);
//     DEC_PYCALLBACK_VOID_SIZETSIZET_const(OnGetColumnsWidthHint);
    
//     // when the number of lines changes, we try to estimate the total width or
//     // height of all lines which is a rather expensive operation in terms of
//     // lines access, so if the user code may estimate the average height
//     // better/faster than we do, it should override this function to implement
//     // its own logic
//     //
//     // this function should return the best guess for the total height it may
//     // make
//     DEC_PYCALLBACK_COORD_const(EstimateTotalHeight);
//     DEC_PYCALLBACK_COORD_const(EstimateTotalWidth);


//     // Also expose some other interesting protected methods

//     // find the index of the horizontal line we need to show at the top of the
//     // window such that the last (fully or partially) visible line is the given
//     // one
//     size_t FindFirstFromRight(size_t columnLast, bool fullyVisible = false)
//     { return wxHVScrolledWindow::FindFirstFromRight(columnLast, fullyVisible); }
    
//     // find the index of the vertical line we need to show at the top of the
//     // window such that the last (fully or partially) visible line is the given
//     // one
//     size_t FindFirstFromBottom(size_t lineLast, bool fullyVisible = false)
//     { return wxHVScrolledWindow::FindFirstFromBottom(lineLast, fullyVisible); }

    
//     // get the total width or height of the lines between lineMin (inclusive)
//     // and lineMax (exclusive)
//     wxCoord GetRowsHeight(size_t lineMin, size_t lineMax) const
//     { return wxHVScrolledWindow::GetRowsHeight(lineMin, lineMax); }
//     wxCoord GetColumnsWidth(size_t columnMin, size_t columnMax) const
//     { return wxHVScrolledWindow::GetColumnsWidth(columnMin, columnMax); }

//     PYPRIVATE;
// };

 
// IMPLEMENT_ABSTRACT_CLASS(wxPyHVScrolledWindow, wxHVScrolledWindow);

// IMP_PYCALLBACK_COORD_SIZET_constpure(wxPyHVScrolledWindow, wxHVScrolledWindow, OnGetRowHeight);
// IMP_PYCALLBACK_COORD_SIZET_constpure(wxPyHVScrolledWindow, wxHVScrolledWindow, OnGetColumnWidth); 
// IMP_PYCALLBACK_VOID_SIZETSIZET_const(wxPyHVScrolledWindow, wxHVScrolledWindow, OnGetRowsHeightHint);
// IMP_PYCALLBACK_VOID_SIZETSIZET_const(wxPyHVScrolledWindow, wxHVScrolledWindow, OnGetColumnsWidthHint); 
// IMP_PYCALLBACK_COORD_const          (wxPyHVScrolledWindow, wxHVScrolledWindow, EstimateTotalHeight);
// IMP_PYCALLBACK_COORD_const          (wxPyHVScrolledWindow, wxHVScrolledWindow, EstimateTotalWidth); 
// %}




// // Now define this class for SWIG

// /*
//    This class is strongly influenced by wxVScrolledWindow. In fact, much of
//    code is line for line the same except it EXPLICITLY states which axis is
//    being worked on.  Like wxVScrolledWindow, this class is here to provide
//    an easy way to implement variable line sizes.  The difference is that
//    wxVScrolledWindow only works with vertical scrolling.  This class extends
//    the behavior of wxVScrolledWindow to the horizontal axis in addition to the
//    vertical axis.

//    The scrolling is also "virtual" in the sense that line widths and heights
//    only need to be known for lines that are currently visible.

//    Like wxVScrolledWindow, this is a generalization of the wxScrolledWindow
//    class which can be only used when all horizontal lines have the same width
//    and all of the vertical lines have the same height. Like wxVScrolledWinow
//    it lacks some of wxScrolledWindow features such as scrolling another window
//    or only scrolling a rectangle of the window and not its entire client area.

//    If only vertical scrolling is needed, wxVScrolledWindow is recommended
//    because it is simpler to use (and you get to type less).
   
//    There is no wxHScrolledWindow but horizontal only scrolling is implemented
//    easily enough with this class.  If someone feels the need for such a class,
//    implementing it is trivial.
//  */
// MustHaveApp(wxPyHVScrolledWindow);

// %rename(HVScrolledWindow) wxPyHVScrolledWindow;
// class wxPyHVScrolledWindow : public wxPanel
// {
// public:
//     %pythonAppend wxPyHVScrolledWindow         "self._setOORInfo(self); self._setCallbackInfo(self, VScrolledWindow)"
//     %pythonAppend wxPyHVScrolledWindow()       ""

//     // normal ctor, no need to call Create() after this one
//     //
//     // note that wxVSCROLL and wxHSCROLL are always automatically added to our
//     // style, there is no need to specify them explicitly
//     wxPyHVScrolledWindow(wxWindow *parent,
//                          wxWindowID id = wxID_ANY,
//                          const wxPoint& pos = wxDefaultPosition,
//                          const wxSize& size = wxDefaultSize,
//                          long style = 0,
//                          const wxString& name = wxPyPanelNameStr);

//     %RenameCtor(PreHVScrolledWindow, wxPyHVScrolledWindow());
//     void _setCallbackInfo(PyObject* self, PyObject* _class);

    
//     bool Create(wxWindow *parent,
//                 wxWindowID id = wxID_ANY,
//                 const wxPoint& pos = wxDefaultPosition,
//                 const wxSize& size = wxDefaultSize,
//                 long style = 0,
//                 const wxString& name = wxPyPanelNameStr);


//     // operations
//     // ----------

//     // set the number of lines the window contains for each axis: the derived
//     // class must provide the widths and heights for all lines with indices up
//     // to each of the one given here in its OnGetColumnWidth() and
//     // OnGetRowHeight()
//     void SetRowColumnCounts(size_t rowCount, size_t columnCount);

//     // with physical scrolling on, the device origin is changed properly when
//     // a wxPaintDC is prepared, children are actually moved and layed out
//     // properly, and the contents of the window (pixels) are actually moved
//     void EnablePhysicalScrolling(bool scrolling = true);

//     // scroll to the specified line: it will become the first visible line in
//     // the window
//     //
//     // return true if we scrolled the window, false if nothing was done
//     bool ScrollToRow(size_t row);
//     bool ScrollToColumn(size_t column);
//     bool ScrollToRowColumn(size_t row, size_t column);

//     // scroll by the specified number of lines/pages
//     virtual bool ScrollRows(int rows);
//     virtual bool ScrollColumns(int columns);
//     virtual bool ScrollRowsColumns(int rows, int columns);
//     virtual bool ScrollRowPages(int pages);
//     virtual bool ScrollColumnPages(int pages);
//     virtual bool ScrollPages(int rowPages, int columnPages);

//     // redraw the specified line
//     virtual void RefreshRow(size_t line);
//     virtual void RefreshColumn(size_t line);
//     virtual void RefreshRowColumn(size_t row, size_t column);

//     // redraw all lines in the specified range (inclusive)
//     virtual void RefreshRows(size_t from, size_t to);
//     virtual void RefreshColumns(size_t from, size_t to);
//     virtual void RefreshRowsColumns(size_t fromRow, size_t toRow,
//                                     size_t fromColumn, size_t toColumn);

//     // return the horizontal and vertical line within a wxPoint at the
//     // specified (in physical coordinates) position or.

//     // wxNOT_FOUND in either or both axes if no line is present at the
//     // requested coordinates, i.e. if it is past the last lines
//     %Rename(HitTestXY, wxPoint, HitTest(wxCoord x, wxCoord y) const);
//     wxPoint HitTest(const wxPoint& pt) const;

//     // recalculate all our parameters and redisplay all lines
//     virtual void RefreshAll();


//     // accessors
//     // ---------

//     // get the number of lines this window contains (previously set by
//     // SetLineCount())
//     size_t GetRowCount() const;
//     size_t GetColumnCount() const;
//     wxSize GetRowColumnCounts() const;

//     // get the first currently visible line/lines
//     size_t GetVisibleRowsBegin() const;
//     size_t GetVisibleColumnsBegin() const;
//     wxPoint GetVisibleBegin() const;

//     // get the last currently visible line/lines
//     size_t GetVisibleRowsEnd() const;
//     size_t GetVisibleColumnsEnd() const;
//     wxPoint GetVisibleEnd() const;

//     // is this line currently visible?
//     bool IsRowVisible(size_t row) const;
//     bool IsColumnVisible(size_t column) const;
//     bool IsVisible(size_t row, size_t column) const;


//     // find the index of the horizontal line we need to show at the top of the
//     // window such that the last (fully or partially) visible line is the given
//     // one
//     size_t FindFirstFromRight(size_t columnLast, bool fullyVisible = false);
    
//     // find the index of the vertical line we need to show at the top of the
//     // window such that the last (fully or partially) visible line is the given
//     // one
//     size_t FindFirstFromBottom(size_t lineLast, bool fullyVisible = false);

    
//     // get the total width or height of the lines between lineMin (inclusive)
//     // and lineMax (exclusive)
//     wxCoord GetRowsHeight(size_t lineMin, size_t lineMax) const;
//     wxCoord GetColumnsWidth(size_t columnMin, size_t columnMax) const;
    
// };



//---------------------------------------------------------------------------
// wxVListBox

%{
#include <wx/vlbox.h>
%}

MAKE_CONST_WXSTRING(VListBoxNameStr);


// First, the C++ version
%{
class wxPyVListBox  : public wxVListBox
{
    DECLARE_ABSTRACT_CLASS(wxPyVListBox)
public:
    wxPyVListBox() : wxVListBox() {}

    wxPyVListBox(wxWindow *parent,
                 wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0,
                 const wxString& name = wxPyVListBoxNameStr)
        : wxVListBox(parent, id, pos, size, style, name)
    {}

    // Overridable virtuals

    // the derived class must implement this function to actually draw the item
    // with the given index on the provided DC
    // virtual void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const = 0;
    DEC_PYCALLBACK__DCRECTSIZET_constpure(OnDrawItem);


    // the derived class must implement this method to return the height of the
    // specified item
    // virtual wxCoord OnMeasureItem(size_t n) const = 0;
    DEC_PYCALLBACK_COORD_SIZET_constpure(OnMeasureItem);


    // this method may be used to draw separators between the lines; note that
    // the rectangle may be modified, typically to deflate it a bit before
    // passing to OnDrawItem()
    //
    // the base class version doesn't do anything
    //    virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
    DEC_PYCALLBACK__DCRECTSIZET2_const(OnDrawSeparator);


    // this method is used to draw the items background and, maybe, a border
    // around it
    //
    // the base class version implements a reasonable default behaviour which
    // consists in drawing the selected item with the standard background
    // colour and drawing a border around the item if it is either selected or
    // current
    //     virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const;
    DEC_PYCALLBACK__DCRECTSIZET_const(OnDrawBackground);


    PYPRIVATE;
};

IMPLEMENT_ABSTRACT_CLASS(wxPyVListBox, wxVListBox);

IMP_PYCALLBACK__DCRECTSIZET_constpure(wxPyVListBox, wxVListBox, OnDrawItem);
IMP_PYCALLBACK_COORD_SIZET_constpure (wxPyVListBox, wxVListBox, OnMeasureItem);
IMP_PYCALLBACK__DCRECTSIZET2_const   (wxPyVListBox, wxVListBox, OnDrawSeparator);
IMP_PYCALLBACK__DCRECTSIZET_const    (wxPyVListBox, wxVListBox, OnDrawBackground);

%}



// Now define this class for SWIG

/*
    This class has two main differences from a regular listbox: it can have an
    arbitrarily huge number of items because it doesn't store them itself but
    uses OnDrawItem() callback to draw them and its items can have variable
    height as determined by OnMeasureItem().

    It emits the same events as wxListBox and the same event macros may be used
    with it.
 */
MustHaveApp(wxPyVListBox);

%rename(VListBox) wxPyVListBox;
class wxPyVListBox : public wxPyVScrolledWindow
{
public:
    %pythonAppend wxPyVListBox         "self._setOORInfo(self);self._setCallbackInfo(self, VListBox)"
    %pythonAppend wxPyVListBox()       ""
    

    wxPyVListBox(wxWindow *parent,
                 wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0,
                 const wxString& name = wxPyVListBoxNameStr);

    %RenameCtor(PreVListBox,  wxPyVListBox());

    void _setCallbackInfo(PyObject* self, PyObject* _class);

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxPyVListBoxNameStr);

    // get the number of items in the control
    size_t GetItemCount() const;

    // does this control use multiple selection?
    bool HasMultipleSelection() const;

    // get the currently selected item or wxNOT_FOUND if there is no selection
    //
    // this method is only valid for the single selection listboxes
    int GetSelection() const;

    // is this item the current one?
    bool IsCurrent(size_t item) const;

    // is this item selected?
    bool IsSelected(size_t item) const;

    // get the number of the selected items (maybe 0)
    //
    // this method is valid for both single and multi selection listboxes
    size_t GetSelectedCount() const;

    %extend {
        // get the first selected item, returns wxNOT_FOUND if none
        //
        // cookie is an opaque parameter which should be passed to
        // GetNextSelected() later
        //
        // this method is only valid for the multi selection listboxes
        //int GetFirstSelected(unsigned long& cookie) const;
        PyObject* GetFirstSelected() {
            unsigned long cookie = 0;
            int selected = self->GetFirstSelected(cookie);
            wxPyBlock_t blocked = wxPyBeginBlockThreads();
            PyObject* tup = PyTuple_New(2);
            PyTuple_SET_ITEM(tup, 0, PyInt_FromLong(selected));
            PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(cookie));
            wxPyEndBlockThreads(blocked);
            return tup;           
        }   

        // get next selection item, return wxNOT_FOUND if no more
        //
        // cookie must be the same parameter that was passed to GetFirstSelected()
        // before
        //
        // this method is only valid for the multi selection listboxes
        // int GetNextSelected(unsigned long& cookie) const;
        PyObject* GetNextSelected(unsigned long cookie) {
            int selected = self->GetNextSelected(cookie);
            wxPyBlock_t blocked = wxPyBeginBlockThreads();
            PyObject* tup = PyTuple_New(2);
            PyTuple_SET_ITEM(tup, 0, PyInt_FromLong(selected));
            PyTuple_SET_ITEM(tup, 1, PyInt_FromLong(cookie));
            wxPyEndBlockThreads(blocked);
            return tup;           
        }   
    }

    
    // get the margins around each item
    wxPoint GetMargins() const;

    // get the background colour of selected cells
    const wxColour& GetSelectionBackground() const;


    // set the number of items to be shown in the control
    //
    // this is just a synonym for wxVScrolledWindow::SetLineCount()
    void SetItemCount(size_t count);

    // delete all items from the control
    void Clear();

    // set the selection to the specified item, if it is wxNOT_FOUND the
    // selection is unset
    //
    // this function is only valid for the single selection listboxes
    void SetSelection(int selection);

    // selects or deselects the specified item which must be valid (i.e. not
    // equal to wxNOT_FOUND)
    //
    // return True if the items selection status has changed or False
    // otherwise
    //
    // this function is only valid for the multiple selection listboxes
    bool Select(size_t item, bool select = true);

    // selects the items in the specified range whose end points may be given
    // in any order
    //
    // return True if any items selection status has changed, False otherwise
    //
    // this function is only valid for the single selection listboxes
    bool SelectRange(size_t from, size_t to);

    // toggle the selection of the specified item (must be valid)
    //
    // this function is only valid for the multiple selection listboxes
    void Toggle(size_t item);

    // select all items in the listbox
    //
    // the return code indicates if any items were affected by this operation
    // (True) or if nothing has changed (False)
    bool SelectAll();

    // unselect all items in the listbox
    //
    // the return code has the same meaning as for SelectAll()
    bool DeselectAll();

    // set the margins: horizontal margin is the distance between the window
    // border and the item contents while vertical margin is half of the
    // distance between items
    //
    // by default both margins are 0
    void SetMargins(const wxPoint& pt);
    %Rename(SetMarginsXY, void, SetMargins(wxCoord x, wxCoord y));

    // change the background colour of the selected cells
    void SetSelectionBackground(const wxColour& col);

    virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
    virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const;
};


//---------------------------------------------------------------------------
// wxHtmlListBox

%{
#include <wx/htmllbox.h>
%}

// First, the C++ version
%{
class wxPyHtmlListBox  : public wxHtmlListBox
{
    DECLARE_ABSTRACT_CLASS(wxPyHtmlListBox)
public:
    wxPyHtmlListBox() : wxHtmlListBox() {}

    wxPyHtmlListBox(wxWindow *parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxString& name = wxPyVListBoxNameStr)
        : wxHtmlListBox(parent, id, pos, size, style, name)
    {}

    // Overridable virtuals

    // this method must be implemented in the derived class and should return
    // the body (i.e. without <html>) of the HTML for the given item
    DEC_PYCALLBACK_STRING_SIZET_pure(OnGetItem);

    // this function may be overridden to decorate HTML returned by OnGetItem()
    DEC_PYCALLBACK_STRING_SIZET(OnGetItemMarkup);

    // These are from wxVListBox
    DEC_PYCALLBACK__DCRECTSIZET2_const(OnDrawSeparator);
    DEC_PYCALLBACK__DCRECTSIZET_const(OnDrawBackground);

// TODO:
//     // this method allows to customize the selection appearance: it may be used
//     // to specify the colour of the text which normally has the given colour
//     // colFg when it is inside the selection
//     //
//     // by default, the original colour is not used at all and all text has the
//     // same (default for this system) colour inside selection
//     virtual wxColour GetSelectedTextColour(const wxColour& colFg) const;

//     // this is the same as GetSelectedTextColour() but allows to customize the
//     // background colour -- this is even more rarely used as you can change it
//     // globally using SetSelectionBackground()
//     virtual wxColour GetSelectedTextBgColour(const wxColour& colBg) const;


    PYPRIVATE;
};


IMPLEMENT_ABSTRACT_CLASS(wxPyHtmlListBox, wxHtmlListBox)

IMP_PYCALLBACK_STRING_SIZET_pure(wxPyHtmlListBox, wxHtmlListBox, OnGetItem);
IMP_PYCALLBACK_STRING_SIZET     (wxPyHtmlListBox, wxHtmlListBox, OnGetItemMarkup);
IMP_PYCALLBACK__DCRECTSIZET2_const   (wxPyHtmlListBox, wxHtmlListBox, OnDrawSeparator);
IMP_PYCALLBACK__DCRECTSIZET_const    (wxPyHtmlListBox, wxHtmlListBox, OnDrawBackground);

%}



// Now define this class for SWIG


// wxHtmlListBox is a listbox whose items are wxHtmlCells
MustHaveApp(wxPyHtmlListBox);
%rename(HtmlListBox) wxPyHtmlListBox;
class wxPyHtmlListBox : public wxPyVListBox
{
public:
    %pythonAppend wxPyHtmlListBox         "self._setOORInfo(self);self._setCallbackInfo(self, HtmlListBox)"
    %pythonAppend wxPyHtmlListBox()       ""
    

    // normal constructor which calls Create() internally
    wxPyHtmlListBox(wxWindow *parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxString& name = wxPyVListBoxNameStr);

    %RenameCtor(PreHtmlListBox,  wxPyHtmlListBox());

    void _setCallbackInfo(PyObject* self, PyObject* _class);

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxPyVListBoxNameStr);


    void RefreshAll();
    void SetItemCount(size_t count);

    // retrieve the file system used by the wxHtmlWinParser: if you use
    // relative paths in your HTML, you should use its ChangePathTo() method
    wxFileSystem& GetFileSystem();
};



//---------------------------------------------------------------------------

%init %{
    // Map renamed classes back to their common name for OOR
    wxPyPtrTypeMap_Add("wxHtmlListBox",     "wxPyHtmlListBox");
    wxPyPtrTypeMap_Add("wxVListBox",        "wxPyVListBox");
    wxPyPtrTypeMap_Add("wxVScrolledWindow", "wxPyVScrolledWindow");
%}

//---------------------------------------------------------------------------
