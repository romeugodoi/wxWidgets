///////////////////////////////////////////////////////////////////////////////
// Name:        ribbon/control.h
// Purpose:     interface of wxRibbonControl
// Author:      Peter Cawley
// RCS-ID:      $Id$
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/**
    @class wxRibbonControl

    wxRibbonControl serves as a base class for all controls which share the
    ribbon charactertics of having a ribbon art provider, and (optionally)
    non-continous resizing. Despite what the name may imply, it is not the
    top-level control for creating a ribbon interface - that is wxRibbonBar.

    @library{wxribbon}
    @category{ribbon}
*/
class wxRibbonControl : public wxControl
{
public:
    /**
        Constructor.
    */
    wxRibbonControl();

    /**
        Constructor.
        
        If @a parent is a wxRibbonControl with a non-NULL art provider, then
        the art provider of this control is set to that.
    */
    wxRibbonControl(wxWindow *parent, wxWindowID id,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize, long style = 0,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = wxControlNameStr);

    /**
        Set the art provider to be used. In many cases, setting the art provider
        will also set the art provider on all child windows which extend
        wxRibbonControl.
    */
    virtual void SetArtProvider(wxRibbonArtProvider* art);
    
    /**
        Get the art provider to be used. Note that until an art provider has
        been set in some way, this function may return NULL.
    */
    wxRibbonArtProvider* GetArtProvider() const;

    /**
        @return @true if this window can take any size (greater than its minimum
        size), @false if it can only take certain sizes.
        
        @see GetNextSmallerSize()
        @see GetNextLargerSize()
    */
    virtual bool IsSizingContinuous() const;
    
    /**
        If sizing is not continuous, then return a suitable size for the control
        which is smaller than the current size.
    
        @param direction
            The direction(s) in which the size should reduce.
        @return
            The current size if there is no smaller size, otherwise a suitable
            size which is smaller in the given direction(s), and the same as the
            current size in the other direction (if any).
      
        @see IsSizingContinuous()
    */
    wxSize GetNextSmallerSize(wxOrientation direction) const;
    
    /**
        If sizing is not continuous, then return a suitable size for the control
        which is smaller than the given size.
    
        @param direction
            The direction(s) in which the size should reduce.
        @param relative_to
            The size for which a smaller size should be found.
        @return
            @a relative_to if there is no smaller size, otherwise a suitable
            size which is smaller in the given direction(s), and the same as
            @a relative_to in the other direction (if any).
      
        @see IsSizingContinuous()
        @see DoGetNextSmallerSize()
    */
    wxSize GetNextSmallerSize(wxOrientation direction, wxSize relative_to) const;
    
    /**
        If sizing is not continuous, then return a suitable size for the control
        which is larger then the current size.
    
        @param direction
            The direction(s) in which the size should increase.
        @return
            The current size if there is no larger size, otherwise a suitable
            size which is larger in the given direction(s), and the same as the
            current size in the other direction (if any).
    
        @see IsSizingContinuous()
    */
    wxSize GetNextLargerSize(wxOrientation direction) const;
    
    /**
        If sizing is not continuous, then return a suitable size for the control
        which is larger then the given size.
    
        @param direction
            The direction(s) in which the size should increase.
        @param relative_to
            The size for which a larger size should be found.
        @return
            @a relative_to if there is no larger size, otherwise a suitable
            size which is larger in the given direction(s), and the same as
            @a relative_to in the other direction (if any).
    
        @see IsSizingContinuous()
        @see DoGetNextLargerSize()
    */
    wxSize GetNextLargerSize(wxOrientation direction, wxSize relative_to) const;
    
    /**
        Perform initial size and layout calculations after children have been
        added, and/or realize children.
    */
    virtual bool Realize();
    
    /**
        Alias for Realize().
    */
    bool Realise();
    
protected:
    /**
        Implementation of GetNextSmallerSize().
        Controls which have non-continuous sizing must override this virtual
        function rather than GetNextSmallerSize().
    */
    virtual wxSize DoGetNextSmallerSize(wxOrientation direction,
                                        wxSize relative_to) const;

    /**
        Implementation of GetNextLargerSize().
        Controls which have non-continuous sizing must override this virtual
        function rather than GetNextLargerSize().
    */
    virtual wxSize DoGetNextLargerSize(wxOrientation direction,
                                       wxSize relative_to) const;
};
