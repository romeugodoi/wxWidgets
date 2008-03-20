/////////////////////////////////////////////////////////////////////////////
// Name:        accel.h
// Purpose:     interface of wxAccelerator* classes
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


/** wxAcceleratorEntry flags */
enum wxAcceleratorEntryFlags
{
    /** no modifiers */
    wxACCEL_NORMAL,

    /** hold Alt key down */
    wxACCEL_ALT,

    /** hold Ctrl key down */
    wxACCEL_CTRL,

    /** hold Shift key down */
    wxACCEL_SHIFT,

    /** Command key on OS X; identic to wxACCEL_CTRL on other platforms. */
    wxACCEL_CMD
};


/**
    @class wxAcceleratorEntry
    @wxheader{accel.h}

    An object used by an application wishing to create an accelerator table
    (see wxAcceleratorTable).

    @library{wxcore}
    @category{misc}

    @see wxAcceleratorTable, wxWindow::SetAcceleratorTable
*/
class wxAcceleratorEntry
{
public:
    /**
        Default ctor.
    */
    wxAcceleratorEntry();

    /**
        Constructor.

        @param flags
            A combination of the wxAcceleratorEntryFlags values, which
            indicates which modifier keys are held down.
        @param keyCode
            The keycode to be detected. See @ref page_keycodes for a full list of keycodes.
        @param cmd
            The menu or control command identifier.
    */
    wxAcceleratorEntry(int flags, int keyCode, int cmd);

    /**
        Returns the command identifier for the accelerator table entry.
    */
    int GetCommand() const;

    /**
        Returns the flags for the accelerator table entry.
    */
    int GetFlags() const;

    /**
        Returns the keycode for the accelerator table entry.
    */
    int GetKeyCode() const;

    /**
        Sets the accelerator entry parameters.
        
        @param flags
            A combination of the wxAcceleratorEntryFlags values, which
            indicates which modifier keys are held down.
        @param keyCode
            The keycode to be detected. See @ref page_keycodes for a full list of keycodes.
        @param cmd
            The menu or control command identifier.

    */
    void Set(int flags, int keyCode, int cmd);
};


/**
    @class wxAcceleratorTable
    @wxheader{accel.h}

    An accelerator table allows the application to specify a table of keyboard
    shortcuts for menu or button commands.

    The object ::wxNullAcceleratorTable is defined to be a table with no data, and
    is the initial accelerator table for a window.

    Example:

    @code
    wxAcceleratorEntry entries[4];
    entries[0].Set(wxACCEL_CTRL, (int) 'N', ID_NEW_WINDOW);
    entries[1].Set(wxACCEL_CTRL, (int) 'X', wxID_EXIT);
    entries[2].Set(wxACCEL_SHIFT, (int) 'A', ID_ABOUT);
    entries[3].Set(wxACCEL_NORMAL, WXK_DELETE, wxID_CUT);

    wxAcceleratorTable accel(4, entries);
    frame->SetAcceleratorTable(accel);
    @endcode

    @remarks
    An accelerator takes precedence over normal processing and can be a convenient
    way to program some event handling. For example, you can use an accelerator table
    to enable a dialog with a multi-line text control to accept CTRL-Enter as meaning
    'OK'.

    @library{wxcore}
    @category{misc}

    @stdobjects
    ::wxNullAcceleratorTable

    @see wxAcceleratorEntry, wxWindow::SetAcceleratorTable
*/
class wxAcceleratorTable : public wxObject
{
public:
    /**
        Default ctor.
    */
    wxAcceleratorTable();

    /**
        Copy ctor.
    */
    wxAcceleratorTable(const wxAcceleratorTable& bitmap);

    /**
        Initializes the accelerator table from an array of wxAcceleratorEntry.
        
        @param n
            Number of accelerator entries.
        @param entries
            The array of entries.
    */
    wxAcceleratorTable(int n, wxAcceleratorEntry entries[]);

    /**
        Loads the accelerator table from a Windows resource (Windows only).
        
        @param resource
            Name of a Windows accelerator.
    */
    wxAcceleratorTable(const wxString& resource);

    /**
        Destroys the wxAcceleratorTable object.
        See @ref overview_refcount_destruct for more info.
    */
    ~wxAcceleratorTable();

    /**
        Returns @true if the accelerator table is valid.
    */
    bool IsOk() const;

    /**
        Assignment operator, using @ref overview_refcount "reference counting".
        
        @param accel
            Accelerator table to assign.
    */
    wxAcceleratorTable operator =(const wxAcceleratorTable& accel);
};


// ============================================================================
// Global functions/macros
// ============================================================================

/**
    An empty accelerator table.
*/
wxAcceleratorTable wxNullAcceleratorTable;
