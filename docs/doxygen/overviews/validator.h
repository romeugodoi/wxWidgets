/////////////////////////////////////////////////////////////////////////////
// Name:        validator
// Purpose:     topic overview
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/*!

 @page validator_overview wxValidator overview

 Classes: #wxValidator, #wxTextValidator,
 #wxGenericValidator
 The aim of the validator concept is to make dialogs very much easier to write.
 A validator is an object that can be plugged into a control (such as a wxTextCtrl), and
 mediates between C++ data and the control, transferring the data in either direction
 and validating it. It also is able to intercept events generated
 by the control, providing filtering behaviour without the need to derive a new control class.
 You can use a stock validator, such as #wxTextValidator (which does text
 control data transfer, validation and filtering) and
 #wxGenericValidator (which does data transfer for a range of controls);
 or you can write your own.
 @b Example
 Here is an example of wxTextValidator usage.

 @code
 wxTextCtrl *txt1 = new wxTextCtrl(this, -1, wxT(""),
     wxPoint(10, 10), wxSize(100, 80), 0,
     wxTextValidator(wxFILTER_ALPHA, _data.m_string));
 @endcode

 In this example, the text validator object provides the following functionality:


  It transfers the value of g_data.m_string (a wxString variable) to the wxTextCtrl when
 the dialog is initialised.
  It transfers the wxTextCtrl data back to this variable when the dialog is dismissed.
  It filters input characters so that only alphabetic characters are allowed.


 The validation and filtering of input is accomplished in two ways. When a character is input,
 wxTextValidator checks the character against the allowed filter flag (wxFILTER_ALPHA in this case). If
 the character is inappropriate, it is vetoed (does not appear) and a warning beep sounds.
 The second type of validation is performed when the dialog is about to be dismissed, so if
 the default string contained invalid characters already, a dialog box is shown giving the
 error, and the dialog is not dismissed.
 @b Anatomy of a validator
 A programmer creating a new validator class should provide the following functionality.
 A validator constructor is responsible for allowing the programmer to specify the kind
 of validation required, and perhaps a pointer to a C++ variable that is used for storing the
 data for the control. If such a variable address is not supplied by the user, then
 the validator should store the data internally.
 The wxValidator::Validate member function should return
 @true if the data in the control (not the C++ variable) is valid. It should also show
 an appropriate message if data was not valid.
 The wxValidator::TransferToWindow member function should
 transfer the data from the validator or associated C++ variable to the control.
 The wxValidator::TransferFromWindow member function should
 transfer the data from the control to the validator or associated C++ variable.
 There should be a copy constructor, and a wxValidator::Clone function
 which returns a copy of the validator object. This is important because validators
 are passed by reference to window constructors, and must therefore be cloned internally.
 You can optionally define event handlers for the validator, to implement filtering. These handlers
 will capture events before the control itself does.
 For an example implementation, see the valtext.h and valtext.cpp files in the wxWidgets library.
 @b How validators interact with dialogs
 For validators to work correctly, validator functions must be called at the right times during
 dialog initialisation and dismissal.
 When a wxDialog::Show is called (for a modeless dialog)
 or wxDialog::ShowModal is called (for a modal dialog),
 the function wxWindow::InitDialog is automatically called.
 This in turn sends an initialisation event to the dialog. The default handler for
 the wxEVT_INIT_DIALOG event is defined in the wxWindow class to simply call
 the function wxWindow::TransferDataToWindow. This
 function finds all the validators in the window's children and calls the TransferToWindow
 function for each. Thus, data is transferred from C++ variables to the dialog
 just as the dialog is being shown.

 If you are using a window or panel instead of a dialog, you will need to
 call wxWindow::InitDialog explicitly before showing the
 window.

 When the user clicks on a button, for example the OK button, the application should
 first call wxWindow::Validate, which returns @false if
 any of the child window validators failed to validate the window data. The button handler
 should return immediately if validation failed. Secondly, the application should
 call wxWindow::TransferDataFromWindow and
 return if this failed. It is then safe to end the dialog by calling EndModal (if modal)
 or Show (if modeless).
 In fact, wxDialog contains a default command event handler for the wxID_OK button. It goes like
 this:

 @code
 void wxDialog::OnOK(wxCommandEvent& event)
 {
     if ( Validate() && TransferDataFromWindow() )
     {
         if ( IsModal() )
             EndModal(wxID_OK);
         else
         {
             SetReturnCode(wxID_OK);
             this-Show(@false);
         }
     }
 }
 @endcode

 So if using validators and a normal OK button, you may not even need to write any
 code for handling dialog dismissal.
 If you load your dialog from a resource file, you will need to iterate through the controls
 setting validators, since validators can't be specified in a dialog resource.

 */


