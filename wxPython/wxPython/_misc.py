## This file reverse renames symbols in the wx package to give
## them their wx prefix again, for backwards compatibility.
##
## Generated by BuildRenamers in config.py

# This silly stuff here is so the wxPython.wx module doesn't conflict
# with the wx package.  We need to import modules from the wx package
# here, then we'll put the wxPython.wx entry back in sys.modules.
import sys
_wx = None
if sys.modules.has_key('wxPython.wx'):
    _wx = sys.modules['wxPython.wx']
    del sys.modules['wxPython.wx']

import wx._misc

sys.modules['wxPython.wx'] = _wx
del sys, _wx


# Now assign all the reverse-renamed names:
wxSYS_OEM_FIXED_FONT = wx._misc.SYS_OEM_FIXED_FONT
wxSYS_ANSI_FIXED_FONT = wx._misc.SYS_ANSI_FIXED_FONT
wxSYS_ANSI_VAR_FONT = wx._misc.SYS_ANSI_VAR_FONT
wxSYS_SYSTEM_FONT = wx._misc.SYS_SYSTEM_FONT
wxSYS_DEVICE_DEFAULT_FONT = wx._misc.SYS_DEVICE_DEFAULT_FONT
wxSYS_DEFAULT_PALETTE = wx._misc.SYS_DEFAULT_PALETTE
wxSYS_SYSTEM_FIXED_FONT = wx._misc.SYS_SYSTEM_FIXED_FONT
wxSYS_DEFAULT_GUI_FONT = wx._misc.SYS_DEFAULT_GUI_FONT
wxSYS_ICONTITLE_FONT = wx._misc.SYS_ICONTITLE_FONT
wxSYS_COLOUR_SCROLLBAR = wx._misc.SYS_COLOUR_SCROLLBAR
wxSYS_COLOUR_BACKGROUND = wx._misc.SYS_COLOUR_BACKGROUND
wxSYS_COLOUR_DESKTOP = wx._misc.SYS_COLOUR_DESKTOP
wxSYS_COLOUR_ACTIVECAPTION = wx._misc.SYS_COLOUR_ACTIVECAPTION
wxSYS_COLOUR_INACTIVECAPTION = wx._misc.SYS_COLOUR_INACTIVECAPTION
wxSYS_COLOUR_MENU = wx._misc.SYS_COLOUR_MENU
wxSYS_COLOUR_WINDOW = wx._misc.SYS_COLOUR_WINDOW
wxSYS_COLOUR_WINDOWFRAME = wx._misc.SYS_COLOUR_WINDOWFRAME
wxSYS_COLOUR_MENUTEXT = wx._misc.SYS_COLOUR_MENUTEXT
wxSYS_COLOUR_WINDOWTEXT = wx._misc.SYS_COLOUR_WINDOWTEXT
wxSYS_COLOUR_CAPTIONTEXT = wx._misc.SYS_COLOUR_CAPTIONTEXT
wxSYS_COLOUR_ACTIVEBORDER = wx._misc.SYS_COLOUR_ACTIVEBORDER
wxSYS_COLOUR_INACTIVEBORDER = wx._misc.SYS_COLOUR_INACTIVEBORDER
wxSYS_COLOUR_APPWORKSPACE = wx._misc.SYS_COLOUR_APPWORKSPACE
wxSYS_COLOUR_HIGHLIGHT = wx._misc.SYS_COLOUR_HIGHLIGHT
wxSYS_COLOUR_HIGHLIGHTTEXT = wx._misc.SYS_COLOUR_HIGHLIGHTTEXT
wxSYS_COLOUR_BTNFACE = wx._misc.SYS_COLOUR_BTNFACE
wxSYS_COLOUR_3DFACE = wx._misc.SYS_COLOUR_3DFACE
wxSYS_COLOUR_BTNSHADOW = wx._misc.SYS_COLOUR_BTNSHADOW
wxSYS_COLOUR_3DSHADOW = wx._misc.SYS_COLOUR_3DSHADOW
wxSYS_COLOUR_GRAYTEXT = wx._misc.SYS_COLOUR_GRAYTEXT
wxSYS_COLOUR_BTNTEXT = wx._misc.SYS_COLOUR_BTNTEXT
wxSYS_COLOUR_INACTIVECAPTIONTEXT = wx._misc.SYS_COLOUR_INACTIVECAPTIONTEXT
wxSYS_COLOUR_BTNHIGHLIGHT = wx._misc.SYS_COLOUR_BTNHIGHLIGHT
wxSYS_COLOUR_BTNHILIGHT = wx._misc.SYS_COLOUR_BTNHILIGHT
wxSYS_COLOUR_3DHIGHLIGHT = wx._misc.SYS_COLOUR_3DHIGHLIGHT
wxSYS_COLOUR_3DHILIGHT = wx._misc.SYS_COLOUR_3DHILIGHT
wxSYS_COLOUR_3DDKSHADOW = wx._misc.SYS_COLOUR_3DDKSHADOW
wxSYS_COLOUR_3DLIGHT = wx._misc.SYS_COLOUR_3DLIGHT
wxSYS_COLOUR_INFOTEXT = wx._misc.SYS_COLOUR_INFOTEXT
wxSYS_COLOUR_INFOBK = wx._misc.SYS_COLOUR_INFOBK
wxSYS_COLOUR_LISTBOX = wx._misc.SYS_COLOUR_LISTBOX
wxSYS_COLOUR_HOTLIGHT = wx._misc.SYS_COLOUR_HOTLIGHT
wxSYS_COLOUR_GRADIENTACTIVECAPTION = wx._misc.SYS_COLOUR_GRADIENTACTIVECAPTION
wxSYS_COLOUR_GRADIENTINACTIVECAPTION = wx._misc.SYS_COLOUR_GRADIENTINACTIVECAPTION
wxSYS_COLOUR_MENUHILIGHT = wx._misc.SYS_COLOUR_MENUHILIGHT
wxSYS_COLOUR_MENUBAR = wx._misc.SYS_COLOUR_MENUBAR
wxSYS_COLOUR_MAX = wx._misc.SYS_COLOUR_MAX
wxSYS_MOUSE_BUTTONS = wx._misc.SYS_MOUSE_BUTTONS
wxSYS_BORDER_X = wx._misc.SYS_BORDER_X
wxSYS_BORDER_Y = wx._misc.SYS_BORDER_Y
wxSYS_CURSOR_X = wx._misc.SYS_CURSOR_X
wxSYS_CURSOR_Y = wx._misc.SYS_CURSOR_Y
wxSYS_DCLICK_X = wx._misc.SYS_DCLICK_X
wxSYS_DCLICK_Y = wx._misc.SYS_DCLICK_Y
wxSYS_DRAG_X = wx._misc.SYS_DRAG_X
wxSYS_DRAG_Y = wx._misc.SYS_DRAG_Y
wxSYS_EDGE_X = wx._misc.SYS_EDGE_X
wxSYS_EDGE_Y = wx._misc.SYS_EDGE_Y
wxSYS_HSCROLL_ARROW_X = wx._misc.SYS_HSCROLL_ARROW_X
wxSYS_HSCROLL_ARROW_Y = wx._misc.SYS_HSCROLL_ARROW_Y
wxSYS_HTHUMB_X = wx._misc.SYS_HTHUMB_X
wxSYS_ICON_X = wx._misc.SYS_ICON_X
wxSYS_ICON_Y = wx._misc.SYS_ICON_Y
wxSYS_ICONSPACING_X = wx._misc.SYS_ICONSPACING_X
wxSYS_ICONSPACING_Y = wx._misc.SYS_ICONSPACING_Y
wxSYS_WINDOWMIN_X = wx._misc.SYS_WINDOWMIN_X
wxSYS_WINDOWMIN_Y = wx._misc.SYS_WINDOWMIN_Y
wxSYS_SCREEN_X = wx._misc.SYS_SCREEN_X
wxSYS_SCREEN_Y = wx._misc.SYS_SCREEN_Y
wxSYS_FRAMESIZE_X = wx._misc.SYS_FRAMESIZE_X
wxSYS_FRAMESIZE_Y = wx._misc.SYS_FRAMESIZE_Y
wxSYS_SMALLICON_X = wx._misc.SYS_SMALLICON_X
wxSYS_SMALLICON_Y = wx._misc.SYS_SMALLICON_Y
wxSYS_HSCROLL_Y = wx._misc.SYS_HSCROLL_Y
wxSYS_VSCROLL_X = wx._misc.SYS_VSCROLL_X
wxSYS_VSCROLL_ARROW_X = wx._misc.SYS_VSCROLL_ARROW_X
wxSYS_VSCROLL_ARROW_Y = wx._misc.SYS_VSCROLL_ARROW_Y
wxSYS_VTHUMB_Y = wx._misc.SYS_VTHUMB_Y
wxSYS_CAPTION_Y = wx._misc.SYS_CAPTION_Y
wxSYS_MENU_Y = wx._misc.SYS_MENU_Y
wxSYS_NETWORK_PRESENT = wx._misc.SYS_NETWORK_PRESENT
wxSYS_PENWINDOWS_PRESENT = wx._misc.SYS_PENWINDOWS_PRESENT
wxSYS_SHOW_SOUNDS = wx._misc.SYS_SHOW_SOUNDS
wxSYS_SWAP_BUTTONS = wx._misc.SYS_SWAP_BUTTONS
wxSYS_CAN_DRAW_FRAME_DECORATIONS = wx._misc.SYS_CAN_DRAW_FRAME_DECORATIONS
wxSYS_CAN_ICONIZE_FRAME = wx._misc.SYS_CAN_ICONIZE_FRAME
wxSYS_SCREEN_NONE = wx._misc.SYS_SCREEN_NONE
wxSYS_SCREEN_TINY = wx._misc.SYS_SCREEN_TINY
wxSYS_SCREEN_PDA = wx._misc.SYS_SCREEN_PDA
wxSYS_SCREEN_SMALL = wx._misc.SYS_SCREEN_SMALL
wxSYS_SCREEN_DESKTOP = wx._misc.SYS_SCREEN_DESKTOP
wxSystemSettings = wx._misc.SystemSettings
wxSystemSettingsPtr = wx._misc.SystemSettingsPtr
wxSystemSettings_GetColour = wx._misc.SystemSettings_GetColour
wxSystemSettings_GetFont = wx._misc.SystemSettings_GetFont
wxSystemSettings_GetMetric = wx._misc.SystemSettings_GetMetric
wxSystemSettings_HasFeature = wx._misc.SystemSettings_HasFeature
wxSystemSettings_GetScreenType = wx._misc.SystemSettings_GetScreenType
wxSystemSettings_SetScreenType = wx._misc.SystemSettings_SetScreenType
wxSystemOptions = wx._misc.SystemOptions
wxSystemOptionsPtr = wx._misc.SystemOptionsPtr
wxSystemOptions_SetOption = wx._misc.SystemOptions_SetOption
wxSystemOptions_SetOptionInt = wx._misc.SystemOptions_SetOptionInt
wxSystemOptions_GetOption = wx._misc.SystemOptions_GetOption
wxSystemOptions_GetOptionInt = wx._misc.SystemOptions_GetOptionInt
wxSystemOptions_HasOption = wx._misc.SystemOptions_HasOption
wxFileSelectorPromptStr = wx._misc.FileSelectorPromptStr
wxFileSelectorDefaultWildcardStr = wx._misc.FileSelectorDefaultWildcardStr
wxDirSelectorPromptStr = wx._misc.DirSelectorPromptStr
wxNewId = wx._misc.NewId
wxRegisterId = wx._misc.RegisterId
wxGetCurrentId = wx._misc.GetCurrentId
wxBell = wx._misc.Bell
wxEndBusyCursor = wx._misc.EndBusyCursor
wxGetElapsedTime = wx._misc.GetElapsedTime
wxGetMousePosition = wx._misc.GetMousePosition
wxIsBusy = wx._misc.IsBusy
wxNow = wx._misc.Now
wxShell = wx._misc.Shell
wxStartTimer = wx._misc.StartTimer
wxGetOsVersion = wx._misc.GetOsVersion
wxGetOsDescription = wx._misc.GetOsDescription
wxGetFreeMemory = wx._misc.GetFreeMemory
wxSHUTDOWN_POWEROFF = wx._misc.SHUTDOWN_POWEROFF
wxSHUTDOWN_REBOOT = wx._misc.SHUTDOWN_REBOOT
wxShutdown = wx._misc.Shutdown
wxSleep = wx._misc.Sleep
wxMilliSleep = wx._misc.MilliSleep
wxMicroSleep = wx._misc.MicroSleep
wxEnableTopLevelWindows = wx._misc.EnableTopLevelWindows
wxStripMenuCodes = wx._misc.StripMenuCodes
wxGetEmailAddress = wx._misc.GetEmailAddress
wxGetHostName = wx._misc.GetHostName
wxGetFullHostName = wx._misc.GetFullHostName
wxGetUserId = wx._misc.GetUserId
wxGetUserName = wx._misc.GetUserName
wxGetHomeDir = wx._misc.GetHomeDir
wxGetUserHome = wx._misc.GetUserHome
wxGetProcessId = wx._misc.GetProcessId
wxTrap = wx._misc.Trap
wxFileSelector = wx._misc.FileSelector
wxLoadFileSelector = wx._misc.LoadFileSelector
wxSaveFileSelector = wx._misc.SaveFileSelector
wxDirSelector = wx._misc.DirSelector
wxGetTextFromUser = wx._misc.GetTextFromUser
wxGetPasswordFromUser = wx._misc.GetPasswordFromUser
wxGetSingleChoice = wx._misc.GetSingleChoice
wxGetSingleChoiceIndex = wx._misc.GetSingleChoiceIndex
wxMessageBox = wx._misc.MessageBox
wxGetNumberFromUser = wx._misc.GetNumberFromUser
wxColourDisplay = wx._misc.ColourDisplay
wxDisplayDepth = wx._misc.DisplayDepth
wxGetDisplayDepth = wx._misc.GetDisplayDepth
wxDisplaySize = wx._misc.DisplaySize
wxGetDisplaySize = wx._misc.GetDisplaySize
wxDisplaySizeMM = wx._misc.DisplaySizeMM
wxGetDisplaySizeMM = wx._misc.GetDisplaySizeMM
wxClientDisplayRect = wx._misc.ClientDisplayRect
wxGetClientDisplayRect = wx._misc.GetClientDisplayRect
wxSetCursor = wx._misc.SetCursor
wxBeginBusyCursor = wx._misc.BeginBusyCursor
wxGetActiveWindow = wx._misc.GetActiveWindow
wxGenericFindWindowAtPoint = wx._misc.GenericFindWindowAtPoint
wxFindWindowAtPoint = wx._misc.FindWindowAtPoint
wxGetTopLevelParent = wx._misc.GetTopLevelParent
wxGetKeyState = wx._misc.GetKeyState
wxWakeUpMainThread = wx._misc.WakeUpMainThread
wxMutexGuiEnter = wx._misc.MutexGuiEnter
wxMutexGuiLeave = wx._misc.MutexGuiLeave
wxMutexGuiLocker = wx._misc.MutexGuiLocker
wxMutexGuiLockerPtr = wx._misc.MutexGuiLockerPtr
wxThread_IsMain = wx._misc.Thread_IsMain
wxToolTip = wx._misc.ToolTip
wxToolTipPtr = wx._misc.ToolTipPtr
wxToolTip_Enable = wx._misc.ToolTip_Enable
wxToolTip_SetDelay = wx._misc.ToolTip_SetDelay
wxCaret = wx._misc.Caret
wxCaretPtr = wx._misc.CaretPtr
wxCaret_GetBlinkTime = wx._misc.Caret_GetBlinkTime
wxCaret_SetBlinkTime = wx._misc.Caret_SetBlinkTime
wxBusyCursor = wx._misc.BusyCursor
wxBusyCursorPtr = wx._misc.BusyCursorPtr
wxWindowDisabler = wx._misc.WindowDisabler
wxWindowDisablerPtr = wx._misc.WindowDisablerPtr
wxBusyInfo = wx._misc.BusyInfo
wxBusyInfoPtr = wx._misc.BusyInfoPtr
wxStopWatch = wx._misc.StopWatch
wxStopWatchPtr = wx._misc.StopWatchPtr
wxFileHistory = wx._misc.FileHistory
wxFileHistoryPtr = wx._misc.FileHistoryPtr
wxSingleInstanceChecker = wx._misc.SingleInstanceChecker
wxSingleInstanceCheckerPtr = wx._misc.SingleInstanceCheckerPtr
wxPreSingleInstanceChecker = wx._misc.PreSingleInstanceChecker
wxDrawWindowOnDC = wx._misc.DrawWindowOnDC
wxTipProvider = wx._misc.TipProvider
wxTipProviderPtr = wx._misc.TipProviderPtr
wxPyTipProvider = wx._misc.PyTipProvider
wxPyTipProviderPtr = wx._misc.PyTipProviderPtr
wxShowTip = wx._misc.ShowTip
wxCreateFileTipProvider = wx._misc.CreateFileTipProvider
wxTIMER_CONTINUOUS = wx._misc.TIMER_CONTINUOUS
wxTIMER_ONE_SHOT = wx._misc.TIMER_ONE_SHOT
wxEVT_TIMER = wx._misc.wxEVT_TIMER
wxTimer = wx._misc.Timer
wxTimerPtr = wx._misc.TimerPtr
wxTimerEvent = wx._misc.TimerEvent
wxTimerEventPtr = wx._misc.TimerEventPtr
wxTimerRunner = wx._misc.TimerRunner
wxTimerRunnerPtr = wx._misc.TimerRunnerPtr
wxLOG_FatalError = wx._misc.LOG_FatalError
wxLOG_Error = wx._misc.LOG_Error
wxLOG_Warning = wx._misc.LOG_Warning
wxLOG_Message = wx._misc.LOG_Message
wxLOG_Status = wx._misc.LOG_Status
wxLOG_Info = wx._misc.LOG_Info
wxLOG_Debug = wx._misc.LOG_Debug
wxLOG_Trace = wx._misc.LOG_Trace
wxLOG_Progress = wx._misc.LOG_Progress
wxLOG_User = wx._misc.LOG_User
wxLOG_Max = wx._misc.LOG_Max
wxTRACE_MemAlloc = wx._misc.TRACE_MemAlloc
wxTRACE_Messages = wx._misc.TRACE_Messages
wxTRACE_ResAlloc = wx._misc.TRACE_ResAlloc
wxTRACE_RefCount = wx._misc.TRACE_RefCount
wxTRACE_OleCalls = wx._misc.TRACE_OleCalls
wxTraceMemAlloc = wx._misc.TraceMemAlloc
wxTraceMessages = wx._misc.TraceMessages
wxTraceResAlloc = wx._misc.TraceResAlloc
wxTraceRefCount = wx._misc.TraceRefCount
wxTraceOleCalls = wx._misc.TraceOleCalls
wxLog = wx._misc.Log
wxLogPtr = wx._misc.LogPtr
wxLog_IsEnabled = wx._misc.Log_IsEnabled
wxLog_EnableLogging = wx._misc.Log_EnableLogging
wxLog_OnLog = wx._misc.Log_OnLog
wxLog_FlushActive = wx._misc.Log_FlushActive
wxLog_GetActiveTarget = wx._misc.Log_GetActiveTarget
wxLog_SetActiveTarget = wx._misc.Log_SetActiveTarget
wxLog_Suspend = wx._misc.Log_Suspend
wxLog_Resume = wx._misc.Log_Resume
wxLog_SetVerbose = wx._misc.Log_SetVerbose
wxLog_SetLogLevel = wx._misc.Log_SetLogLevel
wxLog_DontCreateOnDemand = wx._misc.Log_DontCreateOnDemand
wxLog_SetTraceMask = wx._misc.Log_SetTraceMask
wxLog_AddTraceMask = wx._misc.Log_AddTraceMask
wxLog_RemoveTraceMask = wx._misc.Log_RemoveTraceMask
wxLog_ClearTraceMasks = wx._misc.Log_ClearTraceMasks
wxLog_GetTraceMasks = wx._misc.Log_GetTraceMasks
wxLog_SetTimestamp = wx._misc.Log_SetTimestamp
wxLog_GetVerbose = wx._misc.Log_GetVerbose
wxLog_GetTraceMask = wx._misc.Log_GetTraceMask
wxLog_IsAllowedTraceMask = wx._misc.Log_IsAllowedTraceMask
wxLog_GetLogLevel = wx._misc.Log_GetLogLevel
wxLog_GetTimestamp = wx._misc.Log_GetTimestamp
wxLog_TimeStamp = wx._misc.Log_TimeStamp
wxLogStderr = wx._misc.LogStderr
wxLogStderrPtr = wx._misc.LogStderrPtr
wxLogTextCtrl = wx._misc.LogTextCtrl
wxLogTextCtrlPtr = wx._misc.LogTextCtrlPtr
wxLogGui = wx._misc.LogGui
wxLogGuiPtr = wx._misc.LogGuiPtr
wxLogWindow = wx._misc.LogWindow
wxLogWindowPtr = wx._misc.LogWindowPtr
wxLogChain = wx._misc.LogChain
wxLogChainPtr = wx._misc.LogChainPtr
wxSysErrorCode = wx._misc.SysErrorCode
wxSysErrorMsg = wx._misc.SysErrorMsg
wxLogFatalError = wx._misc.LogFatalError
wxLogError = wx._misc.LogError
wxLogWarning = wx._misc.LogWarning
wxLogMessage = wx._misc.LogMessage
wxLogInfo = wx._misc.LogInfo
wxLogDebug = wx._misc.LogDebug
wxLogVerbose = wx._misc.LogVerbose
wxLogStatus = wx._misc.LogStatus
wxLogStatusFrame = wx._misc.LogStatusFrame
wxLogSysError = wx._misc.LogSysError
wxLogTrace = wx._misc.LogTrace
wxLogTrace = wx._misc.LogTrace
wxLogGeneric = wx._misc.LogGeneric
wxSafeShowMessage = wx._misc.SafeShowMessage
wxLogNull = wx._misc.LogNull
wxLogNullPtr = wx._misc.LogNullPtr
wxPyLog = wx._misc.PyLog
wxPyLogPtr = wx._misc.PyLogPtr
wxPROCESS_DEFAULT = wx._misc.PROCESS_DEFAULT
wxPROCESS_REDIRECT = wx._misc.PROCESS_REDIRECT
wxKILL_OK = wx._misc.KILL_OK
wxKILL_BAD_SIGNAL = wx._misc.KILL_BAD_SIGNAL
wxKILL_ACCESS_DENIED = wx._misc.KILL_ACCESS_DENIED
wxKILL_NO_PROCESS = wx._misc.KILL_NO_PROCESS
wxKILL_ERROR = wx._misc.KILL_ERROR
wxSIGNONE = wx._misc.SIGNONE
wxSIGHUP = wx._misc.SIGHUP
wxSIGINT = wx._misc.SIGINT
wxSIGQUIT = wx._misc.SIGQUIT
wxSIGILL = wx._misc.SIGILL
wxSIGTRAP = wx._misc.SIGTRAP
wxSIGABRT = wx._misc.SIGABRT
wxSIGIOT = wx._misc.SIGIOT
wxSIGEMT = wx._misc.SIGEMT
wxSIGFPE = wx._misc.SIGFPE
wxSIGKILL = wx._misc.SIGKILL
wxSIGBUS = wx._misc.SIGBUS
wxSIGSEGV = wx._misc.SIGSEGV
wxSIGSYS = wx._misc.SIGSYS
wxSIGPIPE = wx._misc.SIGPIPE
wxSIGALRM = wx._misc.SIGALRM
wxSIGTERM = wx._misc.SIGTERM
wxProcess = wx._misc.Process
wxProcessPtr = wx._misc.ProcessPtr
wxProcess_Kill = wx._misc.Process_Kill
wxProcess_Exists = wx._misc.Process_Exists
wxProcess_Open = wx._misc.Process_Open
wxProcessEvent = wx._misc.ProcessEvent
wxProcessEventPtr = wx._misc.ProcessEventPtr
wxEVT_END_PROCESS = wx._misc.wxEVT_END_PROCESS
wxEXEC_ASYNC = wx._misc.EXEC_ASYNC
wxEXEC_SYNC = wx._misc.EXEC_SYNC
wxEXEC_NOHIDE = wx._misc.EXEC_NOHIDE
wxEXEC_MAKE_GROUP_LEADER = wx._misc.EXEC_MAKE_GROUP_LEADER
wxExecute = wx._misc.Execute
wxJOYSTICK1 = wx._misc.JOYSTICK1
wxJOYSTICK2 = wx._misc.JOYSTICK2
wxJOY_BUTTON_ANY = wx._misc.JOY_BUTTON_ANY
wxJOY_BUTTON1 = wx._misc.JOY_BUTTON1
wxJOY_BUTTON2 = wx._misc.JOY_BUTTON2
wxJOY_BUTTON3 = wx._misc.JOY_BUTTON3
wxJOY_BUTTON4 = wx._misc.JOY_BUTTON4
wxJoystick = wx._misc.Joystick
wxJoystickPtr = wx._misc.JoystickPtr
wxEVT_JOY_BUTTON_DOWN = wx._misc.wxEVT_JOY_BUTTON_DOWN
wxEVT_JOY_BUTTON_UP = wx._misc.wxEVT_JOY_BUTTON_UP
wxEVT_JOY_MOVE = wx._misc.wxEVT_JOY_MOVE
wxEVT_JOY_ZMOVE = wx._misc.wxEVT_JOY_ZMOVE
wxJoystickEvent = wx._misc.JoystickEvent
wxJoystickEventPtr = wx._misc.JoystickEventPtr
wxSOUND_SYNC = wx._misc.SOUND_SYNC
wxSOUND_ASYNC = wx._misc.SOUND_ASYNC
wxSOUND_LOOP = wx._misc.SOUND_LOOP
wxSound = wx._misc.Sound
wxSoundPtr = wx._misc.SoundPtr
wxSoundFromData = wx._misc.SoundFromData
wxSound_PlaySound = wx._misc.Sound_PlaySound
wxSound_Stop = wx._misc.Sound_Stop
wxMAILCAP_STANDARD = wx._misc.MAILCAP_STANDARD
wxMAILCAP_NETSCAPE = wx._misc.MAILCAP_NETSCAPE
wxMAILCAP_KDE = wx._misc.MAILCAP_KDE
wxMAILCAP_GNOME = wx._misc.MAILCAP_GNOME
wxMAILCAP_ALL = wx._misc.MAILCAP_ALL
wxFileTypeInfo = wx._misc.FileTypeInfo
wxFileTypeInfoPtr = wx._misc.FileTypeInfoPtr
wxFileTypeInfoSequence = wx._misc.FileTypeInfoSequence
wxNullFileTypeInfo = wx._misc.NullFileTypeInfo
wxFileType = wx._misc.FileType
wxFileTypePtr = wx._misc.FileTypePtr
wxFileType_ExpandCommand = wx._misc.FileType_ExpandCommand
wxTheMimeTypesManager = wx._misc.TheMimeTypesManager
wxMimeTypesManager = wx._misc.MimeTypesManager
wxMimeTypesManagerPtr = wx._misc.MimeTypesManagerPtr
wxMimeTypesManager_IsOfType = wx._misc.MimeTypesManager_IsOfType
wxART_TOOLBAR = wx._misc.ART_TOOLBAR
wxART_MENU = wx._misc.ART_MENU
wxART_FRAME_ICON = wx._misc.ART_FRAME_ICON
wxART_CMN_DIALOG = wx._misc.ART_CMN_DIALOG
wxART_HELP_BROWSER = wx._misc.ART_HELP_BROWSER
wxART_MESSAGE_BOX = wx._misc.ART_MESSAGE_BOX
wxART_OTHER = wx._misc.ART_OTHER
wxART_ADD_BOOKMARK = wx._misc.ART_ADD_BOOKMARK
wxART_DEL_BOOKMARK = wx._misc.ART_DEL_BOOKMARK
wxART_HELP_SIDE_PANEL = wx._misc.ART_HELP_SIDE_PANEL
wxART_HELP_SETTINGS = wx._misc.ART_HELP_SETTINGS
wxART_HELP_BOOK = wx._misc.ART_HELP_BOOK
wxART_HELP_FOLDER = wx._misc.ART_HELP_FOLDER
wxART_HELP_PAGE = wx._misc.ART_HELP_PAGE
wxART_GO_BACK = wx._misc.ART_GO_BACK
wxART_GO_FORWARD = wx._misc.ART_GO_FORWARD
wxART_GO_UP = wx._misc.ART_GO_UP
wxART_GO_DOWN = wx._misc.ART_GO_DOWN
wxART_GO_TO_PARENT = wx._misc.ART_GO_TO_PARENT
wxART_GO_HOME = wx._misc.ART_GO_HOME
wxART_FILE_OPEN = wx._misc.ART_FILE_OPEN
wxART_PRINT = wx._misc.ART_PRINT
wxART_HELP = wx._misc.ART_HELP
wxART_TIP = wx._misc.ART_TIP
wxART_REPORT_VIEW = wx._misc.ART_REPORT_VIEW
wxART_LIST_VIEW = wx._misc.ART_LIST_VIEW
wxART_NEW_DIR = wx._misc.ART_NEW_DIR
wxART_FOLDER = wx._misc.ART_FOLDER
wxART_GO_DIR_UP = wx._misc.ART_GO_DIR_UP
wxART_EXECUTABLE_FILE = wx._misc.ART_EXECUTABLE_FILE
wxART_NORMAL_FILE = wx._misc.ART_NORMAL_FILE
wxART_TICK_MARK = wx._misc.ART_TICK_MARK
wxART_CROSS_MARK = wx._misc.ART_CROSS_MARK
wxART_ERROR = wx._misc.ART_ERROR
wxART_QUESTION = wx._misc.ART_QUESTION
wxART_WARNING = wx._misc.ART_WARNING
wxART_INFORMATION = wx._misc.ART_INFORMATION
wxART_MISSING_IMAGE = wx._misc.ART_MISSING_IMAGE
wxArtProvider = wx._misc.ArtProvider
wxArtProviderPtr = wx._misc.ArtProviderPtr
wxArtProvider_PushProvider = wx._misc.ArtProvider_PushProvider
wxArtProvider_PopProvider = wx._misc.ArtProvider_PopProvider
wxArtProvider_RemoveProvider = wx._misc.ArtProvider_RemoveProvider
wxArtProvider_GetBitmap = wx._misc.ArtProvider_GetBitmap
wxArtProvider_GetIcon = wx._misc.ArtProvider_GetIcon
wxCONFIG_USE_LOCAL_FILE = wx._misc.CONFIG_USE_LOCAL_FILE
wxCONFIG_USE_GLOBAL_FILE = wx._misc.CONFIG_USE_GLOBAL_FILE
wxCONFIG_USE_RELATIVE_PATH = wx._misc.CONFIG_USE_RELATIVE_PATH
wxCONFIG_USE_NO_ESCAPE_CHARACTERS = wx._misc.CONFIG_USE_NO_ESCAPE_CHARACTERS
wxConfigBase = wx._misc.ConfigBase
wxConfigBasePtr = wx._misc.ConfigBasePtr
wxConfigBase_Set = wx._misc.ConfigBase_Set
wxConfigBase_Get = wx._misc.ConfigBase_Get
wxConfigBase_Create = wx._misc.ConfigBase_Create
wxConfigBase_DontCreateOnDemand = wx._misc.ConfigBase_DontCreateOnDemand
wxConfig = wx._misc.Config
wxConfigPtr = wx._misc.ConfigPtr
wxFileConfig = wx._misc.FileConfig
wxFileConfigPtr = wx._misc.FileConfigPtr
wxConfigPathChanger = wx._misc.ConfigPathChanger
wxConfigPathChangerPtr = wx._misc.ConfigPathChangerPtr
wxExpandEnvVars = wx._misc.ExpandEnvVars
wxDateFormatStr = wx._misc.DateFormatStr
wxTimeSpanFormatStr = wx._misc.TimeSpanFormatStr
wxDateTime = wx._misc.DateTime
wxDateTimePtr = wx._misc.DateTimePtr
wxDateTime_SetCountry = wx._misc.DateTime_SetCountry
wxDateTime_GetCountry = wx._misc.DateTime_GetCountry
wxDateTime_IsWestEuropeanCountry = wx._misc.DateTime_IsWestEuropeanCountry
wxDateTime_GetCurrentYear = wx._misc.DateTime_GetCurrentYear
wxDateTime_ConvertYearToBC = wx._misc.DateTime_ConvertYearToBC
wxDateTime_GetCurrentMonth = wx._misc.DateTime_GetCurrentMonth
wxDateTime_IsLeapYear = wx._misc.DateTime_IsLeapYear
wxDateTime_GetCentury = wx._misc.DateTime_GetCentury
wxDateTime_GetNumberOfDaysinYear = wx._misc.DateTime_GetNumberOfDaysinYear
wxDateTime_GetNumberOfDaysInMonth = wx._misc.DateTime_GetNumberOfDaysInMonth
wxDateTime_GetMonthName = wx._misc.DateTime_GetMonthName
wxDateTime_GetWeekDayName = wx._misc.DateTime_GetWeekDayName
wxDateTime_GetAmPmStrings = wx._misc.DateTime_GetAmPmStrings
wxDateTime_IsDSTApplicable = wx._misc.DateTime_IsDSTApplicable
wxDateTime_GetBeginDST = wx._misc.DateTime_GetBeginDST
wxDateTime_GetEndDST = wx._misc.DateTime_GetEndDST
wxDateTime_Now = wx._misc.DateTime_Now
wxDateTime_UNow = wx._misc.DateTime_UNow
wxDateTime_Today = wx._misc.DateTime_Today
wxDateTimeFromTimeT = wx._misc.DateTimeFromTimeT
wxDateTimeFromJDN = wx._misc.DateTimeFromJDN
wxDateTimeFromHMS = wx._misc.DateTimeFromHMS
wxDateTimeFromDMY = wx._misc.DateTimeFromDMY
wxTimeSpan = wx._misc.TimeSpan
wxTimeSpanPtr = wx._misc.TimeSpanPtr
wxTimeSpan_Seconds = wx._misc.TimeSpan_Seconds
wxTimeSpan_Second = wx._misc.TimeSpan_Second
wxTimeSpan_Minutes = wx._misc.TimeSpan_Minutes
wxTimeSpan_Minute = wx._misc.TimeSpan_Minute
wxTimeSpan_Hours = wx._misc.TimeSpan_Hours
wxTimeSpan_Hour = wx._misc.TimeSpan_Hour
wxTimeSpan_Days = wx._misc.TimeSpan_Days
wxTimeSpan_Day = wx._misc.TimeSpan_Day
wxTimeSpan_Weeks = wx._misc.TimeSpan_Weeks
wxTimeSpan_Week = wx._misc.TimeSpan_Week
wxDateSpan = wx._misc.DateSpan
wxDateSpanPtr = wx._misc.DateSpanPtr
wxDateSpan_Days = wx._misc.DateSpan_Days
wxDateSpan_Day = wx._misc.DateSpan_Day
wxDateSpan_Weeks = wx._misc.DateSpan_Weeks
wxDateSpan_Week = wx._misc.DateSpan_Week
wxDateSpan_Months = wx._misc.DateSpan_Months
wxDateSpan_Month = wx._misc.DateSpan_Month
wxDateSpan_Years = wx._misc.DateSpan_Years
wxDateSpan_Year = wx._misc.DateSpan_Year
wxGetLocalTime = wx._misc.GetLocalTime
wxGetUTCTime = wx._misc.GetUTCTime
wxGetCurrentTime = wx._misc.GetCurrentTime
wxGetLocalTimeMillis = wx._misc.GetLocalTimeMillis
wxDefaultDateTime = wx._misc.DefaultDateTime
wxDF_INVALID = wx._misc.DF_INVALID
wxDF_TEXT = wx._misc.DF_TEXT
wxDF_BITMAP = wx._misc.DF_BITMAP
wxDF_METAFILE = wx._misc.DF_METAFILE
wxDF_SYLK = wx._misc.DF_SYLK
wxDF_DIF = wx._misc.DF_DIF
wxDF_TIFF = wx._misc.DF_TIFF
wxDF_OEMTEXT = wx._misc.DF_OEMTEXT
wxDF_DIB = wx._misc.DF_DIB
wxDF_PALETTE = wx._misc.DF_PALETTE
wxDF_PENDATA = wx._misc.DF_PENDATA
wxDF_RIFF = wx._misc.DF_RIFF
wxDF_WAVE = wx._misc.DF_WAVE
wxDF_UNICODETEXT = wx._misc.DF_UNICODETEXT
wxDF_ENHMETAFILE = wx._misc.DF_ENHMETAFILE
wxDF_FILENAME = wx._misc.DF_FILENAME
wxDF_LOCALE = wx._misc.DF_LOCALE
wxDF_PRIVATE = wx._misc.DF_PRIVATE
wxDF_HTML = wx._misc.DF_HTML
wxDF_MAX = wx._misc.DF_MAX
wxDataFormat = wx._misc.DataFormat
wxDataFormatPtr = wx._misc.DataFormatPtr
wxCustomDataFormat = wx._misc.CustomDataFormat
wxFormatInvalid = wx._misc.FormatInvalid
wxDataObject = wx._misc.DataObject
wxDataObjectPtr = wx._misc.DataObjectPtr
wxDataObjectSimple = wx._misc.DataObjectSimple
wxDataObjectSimplePtr = wx._misc.DataObjectSimplePtr
wxPyDataObjectSimple = wx._misc.PyDataObjectSimple
wxPyDataObjectSimplePtr = wx._misc.PyDataObjectSimplePtr
wxDataObjectComposite = wx._misc.DataObjectComposite
wxDataObjectCompositePtr = wx._misc.DataObjectCompositePtr
wxTextDataObject = wx._misc.TextDataObject
wxTextDataObjectPtr = wx._misc.TextDataObjectPtr
wxPyTextDataObject = wx._misc.PyTextDataObject
wxPyTextDataObjectPtr = wx._misc.PyTextDataObjectPtr
wxBitmapDataObject = wx._misc.BitmapDataObject
wxBitmapDataObjectPtr = wx._misc.BitmapDataObjectPtr
wxPyBitmapDataObject = wx._misc.PyBitmapDataObject
wxPyBitmapDataObjectPtr = wx._misc.PyBitmapDataObjectPtr
wxFileDataObject = wx._misc.FileDataObject
wxFileDataObjectPtr = wx._misc.FileDataObjectPtr
wxCustomDataObject = wx._misc.CustomDataObject
wxCustomDataObjectPtr = wx._misc.CustomDataObjectPtr
wxURLDataObject = wx._misc.URLDataObject
wxURLDataObjectPtr = wx._misc.URLDataObjectPtr
wxMetafileDataObject = wx._misc.MetafileDataObject
wxMetafileDataObjectPtr = wx._misc.MetafileDataObjectPtr
wxDrag_CopyOnly = wx._misc.Drag_CopyOnly
wxDrag_AllowMove = wx._misc.Drag_AllowMove
wxDrag_DefaultMove = wx._misc.Drag_DefaultMove
wxDragError = wx._misc.DragError
wxDragNone = wx._misc.DragNone
wxDragCopy = wx._misc.DragCopy
wxDragMove = wx._misc.DragMove
wxDragLink = wx._misc.DragLink
wxDragCancel = wx._misc.DragCancel
wxIsDragResultOk = wx._misc.IsDragResultOk
wxDropSource = wx._misc.DropSource
wxDropSourcePtr = wx._misc.DropSourcePtr
wxDropTarget = wx._misc.DropTarget
wxDropTargetPtr = wx._misc.DropTargetPtr
wxTextDropTarget = wx._misc.TextDropTarget
wxTextDropTargetPtr = wx._misc.TextDropTargetPtr
wxFileDropTarget = wx._misc.FileDropTarget
wxFileDropTargetPtr = wx._misc.FileDropTargetPtr
wxClipboard = wx._misc.Clipboard
wxClipboardPtr = wx._misc.ClipboardPtr
wxClipboard_Get = wx._misc.Clipboard_Get
wxClipboardLocker = wx._misc.ClipboardLocker
wxClipboardLockerPtr = wx._misc.ClipboardLockerPtr
wxVideoMode = wx._misc.VideoMode
wxVideoModePtr = wx._misc.VideoModePtr
wxDefaultVideoMode = wx._misc.DefaultVideoMode
wxDisplay = wx._misc.Display
wxDisplayPtr = wx._misc.DisplayPtr
wxDisplay_GetCount = wx._misc.Display_GetCount
wxDisplay_GetFromPoint = wx._misc.Display_GetFromPoint
wxDisplay_GetFromWindow = wx._misc.Display_GetFromWindow
wxPyTimer = wx._misc.PyTimer
wxPyDropTarget = wx._misc.PyDropTarget
wxTheClipboard = wx._misc.TheClipboard


