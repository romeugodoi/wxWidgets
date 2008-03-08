/////////////////////////////////////////////////////////////////////////////
    // Name:        numdlg.h
    // Purpose:     documentation for global functions
    // Author:      wxWidgets team
    // RCS-ID:      $Id$
    // Licence:     wxWindows license
    /////////////////////////////////////////////////////////////////////////////
    
    /**
    Shows a dialog asking the user for numeric input. The dialogs title is set to
    @e caption, it contains a (possibly) multiline @e message above the
    single line @e prompt and the zone for entering the number.
    
    The number entered must be in the range @e min..@e max (both of which
    should be positive) and @e value is the initial value of it. If the user
    enters an invalid value or cancels the dialog, the function will return -1.
    
    Dialog is centered on its @e parent unless an explicit position is given in
    @e pos.
*/
long wxGetNumberFromUser(const wxString& message,
                         const wxString& prompt,
                         const wxString& caption,
                         long value,
                         long min = 0,
                         long max = 100,
                         wxWindow * parent = @NULL,
                         const wxPoint& pos = wxDefaultPosition);


    