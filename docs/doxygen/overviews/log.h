/////////////////////////////////////////////////////////////////////////////
// Name:        log
// Purpose:     topic overview
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/*!
 
 @page log_overview wxLog classes overview
 
 Classes: #wxLog,
 
 #wxLogStderr,
 
 #wxLogStream,
 
 #wxLogTextCtrl,
 
 #wxLogWindow,
 
 #wxLogGui,
 
 #wxLogNull,
 
 #wxLogChain,
 
 #wxLogInterposer,
 
 #wxLogInterposerTemp,
 
 #wxStreamToTextRedirector
 This is a general overview of logging classes provided by wxWidgets. The word
 logging here has a broad sense, including all of the program output, not only
 non-interactive messages. The logging facilities included in wxWidgets provide
 the base @e wxLog class which defines the standard interface for a @e log
 target as well as several standard implementations of it and a family of
 functions to use with them.
 First of all, no knowledge of @e wxLog classes is needed to use them. For
 this, you should only know about @e wxLogXXX() functions. All of them have
 the same syntax as @e printf() or @e vprintf() , i.e. they take the
 format string as the first argument and respectively a variable number of
 arguments or a variable argument list pointer. Here are all of them:
 
 
 @b wxLogFatalError which is like @e wxLogError, but also
 terminates the program with the exit code 3 (using @e abort() standard
 function). Unlike for all the other logging functions, this function can't be
 overridden by a log target.
 @b wxLogError is the function to use for error messages, i.e. the
 messages that must be shown to the user. The default processing is to pop up a
 message box to inform the user about it.
 @b wxLogWarning for warnings - they are also normally shown to the
 user, but don't interrupt the program work.
 @b wxLogMessage is for all normal, informational messages. They also
 appear in a message box by default (but it can be changed, see below).
 @b wxLogVerbose is for verbose output. Normally, it is suppressed, but
 might be activated if the user wishes to know more details about the program
 progress (another, but possibly confusing name for the same function is @b wxLogInfo).
 @b wxLogStatus is for status messages - they will go into the status
 bar of the active or specified (as the first argument) #wxFrame if it has one.
 @b wxLogSysError is mostly used by wxWidgets itself, but might be
 handy for logging errors after system call (API function) failure. It logs the
 specified message text as well as the last system error
 code (@e errno or @e ::GetLastError() depending on the platform) and
 the corresponding error message. The second form of this function takes the
 error code explicitly as the first argument.
 @b wxLogDebug is @b the right function for debug output. It only
 does anything at all in the debug mode (when the preprocessor symbol
 __WXDEBUG__ is defined) and expands to nothing in release mode (otherwise).
 @b Tip: under Windows, you must either run the program under debugger or
 use a 3rd party program such as #DbgView 
 to actually see the debug output.
 @b wxLogTrace as @b wxLogDebug only does something in debug
 build. The reason for making it a separate function from it is that usually
 there are a lot of trace messages, so it might make sense to separate them
 from other debug messages which would be flooded in them. Moreover, the second
 version of this function takes a trace mask as the first argument which allows
 to further restrict the amount of messages generated.
 
 
 The usage of these functions should be fairly straightforward, however it may
 be asked why not use the other logging facilities, such as C standard stdio
 functions or C++ streams. The short answer is that they're all very good
 generic mechanisms, but are not really adapted for wxWidgets, while the log
 classes are. Some of advantages in using wxWidgets log functions are:
 
 
 @b Portability It is a common practice to use @e printf()
 statements or cout/cerr C++ streams for writing out some (debug or otherwise)
 information.
 Although it works just fine under Unix, these messages go strictly nowhere
 under Windows where the stdout of GUI programs is not assigned to anything.
 Thus, you might view @e wxLogMessage() as a simple substitute for @e printf().
 You can also redirect the @e wxLogXXX calls to @e cout by just writing:
 
 
 @code
 wxLog *logger=new wxLogStream();
   wxLog::SetActiveTarget(logger);
 @endcode
 
 
 Finally, there is also a possibility to redirect the output sent to @e cout 
 to a #wxTextCtrl by using the 
 #wxStreamToTextRedirector class.
 @b Flexibility The output of wxLog functions can be redirected or
 suppressed entirely based on their importance, which is either impossible or
 difficult to do with traditional methods. For example, only error messages, or
 only error messages and warnings might be logged, filtering out all
 informational messages.
 @b Completeness Usually, an error message should be presented to the user
 when some operation fails. Let's take a quite simple but common case of a file
 error: suppose that you're writing your data file on disk and there is not
 enough space. The actual error might have been detected inside wxWidgets code
 (say, in @e wxFile::Write), so the calling function doesn't really know the
 exact reason of the failure, it only knows that the data file couldn't be
 written to the disk. However, as wxWidgets uses @e wxLogError() in this
 situation, the exact error code (and the corresponding error message) will be
 given to the user together with "high level" message about data file writing
 error.
 
 
 After having enumerated all the functions which are normally used to log the
 messages, and why would you want to use them we now describe how all this
 works.
 wxWidgets has the notion of a @e log target: it is just a class deriving
 from #wxLog. As such, it implements the virtual functions of
 the base class which are called when a message is logged. Only one log target
 is @e active at any moment, this is the one used by @e wxLogXXX()
 functions. The normal usage of a log object (i.e. object of a class derived
 from wxLog) is to install it as the active target with a call to @e SetActiveTarget() and it will be used automatically by all subsequent calls
 to @e wxLogXXX() functions.
 To create a new log target class you only need to derive it from wxLog and
 implement one (or both) of @e DoLog() and @e DoLogString() in it. The
 second one is enough if you're happy with the standard wxLog message
 formatting (prepending "Error:" or "Warning:", timestamping c) but just want
 to send the messages somewhere else. The first one may be overridden to do
 whatever you want but you have to distinguish between the different message
 types yourself.
 There are some predefined classes deriving from wxLog and which might be
 helpful to see how you can create a new log target class and, of course, may
 also be used without any change. There are:
 
 
 @b wxLogStderr This class logs messages to a @e FILE *, using
 stderr by default as its name suggests.
 @b wxLogStream This class has the same functionality as wxLogStderr,
 but uses @e ostream and cerr instead of @e FILE * and stderr.
 @b wxLogGui This is the standard log target for wxWidgets
 applications (it is used by default if you don't do anything) and provides the
 most reasonable handling of all types of messages for given platform.
 @b wxLogWindow This log target provides a "log console" which
 collects all messages generated by the application and also passes them to the
 previous active log target. The log window frame has a menu allowing user to
 clear the log, close it completely or save all messages to file.
 @b wxLogNull The last log class is quite particular: it doesn't do
 anything. The objects of this class may be instantiated to (temporarily)
 suppress output of @e wxLogXXX() functions. As an example, trying to open a
 non-existing file will usually provoke an error message, but if for some
 reasons it is unwanted, just use this construction:
 
 @code
 wxFile file;
 
   // wxFile.Open() normally complains if file can't be opened, we don't want it
   {
     wxLogNull logNo;
     if ( !file.Open("bar") )
       ... process error ourselves ...
   } // ~wxLogNull called, old log sink restored
   
   wxLogMessage("..."); // ok
 @endcode
 
 
 
 The log targets can also be combined: for example you may wish to redirect the
 messages somewhere else (for example, to a log file) but also process them as
 normally. For this the #wxLogChain, #wxLogInterposer and
 #wxLogInterposerTemp can be used.
 
 */
 
 
