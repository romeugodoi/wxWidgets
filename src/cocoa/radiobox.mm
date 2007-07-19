/////////////////////////////////////////////////////////////////////////////
// Name:        src/cocoa/radiobox.mm
// Purpose:     wxRadioBox
// Author:      David Elliott
// Modified by:
// Created:     2003/02/15
// RCS-ID:      $Id$
// Copyright:   (c) 2003 David Elliott
//              (c) 2007 Software 2000 Ltd.
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#if wxUSE_RADIOBOX

#include "wx/radiobox.h"

#ifndef WX_PRECOMP
    #include "wx/app.h"
    #include "wx/arrstr.h"
#endif //WX_PRECOMP

#include "wx/cocoa/string.h"
#include "wx/cocoa/autorelease.h"

#include "wx/cocoa/objc/NSView.h"
#import <AppKit/NSButton.h>
#import <AppKit/NSBox.h>
#import <AppKit/NSMatrix.h>

IMPLEMENT_DYNAMIC_CLASS(wxRadioBox, wxControl)
BEGIN_EVENT_TABLE(wxRadioBox, wxControl)
END_EVENT_TABLE()
// WX_IMPLEMENT_COCOA_OWNER(wxRadioBox,NSTextField,NSControl,NSView)

bool wxRadioBox::Create(wxWindow *parent, wxWindowID winid,
            const wxString& title,
            const wxPoint& pos,
            const wxSize& size,
            const wxArrayString& choices,
            int majorDim,
            long style, const wxValidator& validator,
            const wxString& name)
{
    wxCArrayString chs(choices);

    return Create(parent, winid, title, pos, size, chs.GetCount(),
                  chs.GetStrings(), majorDim, style, validator, name);
}

bool wxRadioBox::Create(wxWindow *parent, wxWindowID winid,
            const wxString& title,
            const wxPoint& pos,
            const wxSize& size,
            int n, const wxString choices[],
            int majorDim,
            long style, const wxValidator& validator,
            const wxString& name)
{
    // We autorelease heavily so we want our own pool
    wxAutoNSAutoreleasePool pool;

    if(!CreateControl(parent,winid,pos,size,style,validator,name))
        return false;

    majorDim = majorDim == 0 ? n : majorDim;
    // TODO: Don't forget to call SetMajorDim
    // We can't yet as we can't implement GetCount() until after
    // we make the NSMatrix.
    int minorDim = (n + majorDim - 1) / majorDim;


    // Create a prototype cell for use with the NSMatrix build
    NSCell *currCell = [[NSButtonCell alloc] initTextCell:@""];
    [(NSButtonCell*)currCell setButtonType:NSRadioButton];

    // Build up an array of all cells plus any extra empty cells
    NSMutableArray *allCells = [NSMutableArray arrayWithCapacity:n];
    for(int i=0; i<n; ++i)
    {
        [currCell setTitle: wxNSStringWithWxString(choices[i])];
        [allCells addObject: currCell];
        [currCell release];
        // NOTE: We can still safely message currCell as the array has retained it.
        currCell = [currCell copy];
    }
    [currCell release];

    // NOTE: Although an image cell with no image is documented to return NSZeroSize from
    // the cellSize method, the documentation is WRONG.  It will actually return a huge size
    // (thousands) which makes every cell in the matrix that big. Not good.
    // Be safe and initialize a text cell with an empty string.  That always works.
    currCell = [[NSCell alloc] initTextCell:@""];
    for(int i=n; i < majorDim * minorDim; ++i)
    {
        [allCells addObject: currCell];
        // NOTE: Use the same instance.. this should work and save some heap allocations.
        // It will, however, make the selection rather indeterminate if the user clicks
        // on the empty space.
#if 0
	[currCell release];
	currCell = [currCell copy];
#endif
    }
    [currCell release];
    currCell = NULL;

    // Although the documentation on addColumnWithCells:/addRowWithCells: explicitly
    // states that it will determine the initial dimension upon the first call if
    // the initial size is 0x0 it LIES.  It will fail an assertion in the code
    // if you use the simpler initWithFrame: initializer.
    // Therefore, we specify the major dimension and leave the minor dimension as 0
    // so that we can add the rows/columns without failing the assertion.
    NSMatrix* radioBox = [[NSMatrix alloc]
		initWithFrame:NSZeroRect
		mode:NSRadioModeMatrix
		cellClass:nil
		numberOfRows:style&wxRA_SPECIFY_COLS?0:majorDim
		numberOfColumns:style&wxRA_SPECIFY_COLS?majorDim:0
	];

    SEL addMajorWithCellsSelector;
    // If column count is the major dimension then we add by row
    if( style & wxRA_SPECIFY_COLS )
        addMajorWithCellsSelector = @selector(addRowWithCells:);
    // If row count is the major dimension then we add by column
    else
        addMajorWithCellsSelector = @selector(addColumnWithCells:);

    for(int i=0; i<minorDim; ++i)
    {
        [radioBox
            performSelector:addMajorWithCellsSelector
            withObject:[allCells subarrayWithRange:NSMakeRange(i*majorDim, majorDim)]];
    }

    //make and set up an NSBox (TODO: Just derive from wxStaticBox)
    SetNSView([[NSBox alloc] initWithFrame:MakeDefaultNSRect(size)]);
    [m_cocoaNSView release];

    // Replace the box's content view with the NSMatrix we just created
    [GetNSBox() setContentView:radioBox];
    [radioBox release]; // The NSBox retains it for us.

    [GetNSBox() setTitle:wxNSStringWithWxString(title)];
//    [GetNSBox() setBorderType:NSLineBorder]; // why??

    SetMajorDim(majorDim, style);

    if(m_parent)
        m_parent->CocoaAddChild(this);

    // Do the sizer dance
    [GetNSBox() sizeToFit];
    SetInitialFrameRect(pos, size);

    return true;
}

wxRadioBox::~wxRadioBox()
{
}

WX_NSMatrix wxRadioBox::GetNSMatrix() const
{
    return (NSMatrix*)[(NSBox*)m_cocoaNSView contentView];
}

    // selection
void wxRadioBox::SetSelection(int n)
{
}

int wxRadioBox::GetSelection() const
{
    return 0;
}

    // string access
unsigned int wxRadioBox::GetCount() const
{
    NSMatrix *radioBox = GetNSMatrix();
    NSInteger rowCount, columnCount;
    [radioBox getNumberOfRows:&rowCount columns:&columnCount];

    // FIXME: This is wrong if padding cells were made
    return rowCount * columnCount;
}

wxString wxRadioBox::GetString(unsigned int n) const
{
    return wxEmptyString;
}

void wxRadioBox::SetString(unsigned int n, const wxString& label)
{
}

    // change the individual radio button state
bool wxRadioBox::Enable(unsigned int n, bool enable)
{
    // TODO
    return false;
}

bool wxRadioBox::Show(unsigned int n, bool show)
{
    // TODO
    return false;
}

wxSize wxRadioBox::DoGetBestSize() const
{
    // The NSBox responds to sizeToFit by sending sizeToFit to its contentView
    // which is the NSMatrix and does the right thing.
    return wxControl::DoGetBestSize();
}

#endif
