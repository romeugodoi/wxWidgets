/////////////////////////////////////////////////////////////////////////////
// Name:        wx/cocoa/checklst.h
// Purpose:     wxCheckListBox class
// Author:      David Elliott
// Modified by:
// Created:     2003/03/16
// RCS-ID:      $Id:
// Copyright:   (c) 2003 David Elliott
// Licence:   	wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __WX_COCOA_CHECKLST_H__
#define __WX_COCOA_CHECKLST_H__

//#include "wx/cocoa/NSTableView.h"

// ========================================================================
// wxCheckListBox
// ========================================================================
class WXDLLEXPORT wxCheckListBox: public wxCheckListBoxBase //, protected wxCocoaNSTableView
{
    DECLARE_DYNAMIC_CLASS(wxCheckListBox)
    DECLARE_EVENT_TABLE()
    WX_DECLARE_COCOA_OWNER(NSTableView,NSControl,NSView)
// ------------------------------------------------------------------------
// initialization
// ------------------------------------------------------------------------
public:
    wxCheckListBox() { }
    wxCheckListBox(wxWindow *parent, wxWindowID winid,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int n = 0, const wxString choices[] = NULL,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxListBoxNameStr)
    {
        Create(parent, winid,  pos, size, n, choices, style, validator, name);
    }

    bool Create(wxWindow *parent, wxWindowID winid,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int n = 0, const wxString choices[] = NULL,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxListBoxNameStr);
    virtual ~wxCheckListBox();

// ------------------------------------------------------------------------
// Cocoa callbacks
// ------------------------------------------------------------------------
protected:
// ------------------------------------------------------------------------
// Implementation
// ------------------------------------------------------------------------
public:
    // check list box specific methods
    virtual bool IsChecked(size_t item) const;
    virtual void Check(size_t item, bool check = TRUE);
};

#endif // __WX_COCOA_CHECKLST_H__
