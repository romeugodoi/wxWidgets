/////////////////////////////////////////////////////////////////////////////
// Name:        app.cpp
// Purpose:     wxApp
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// RCS-ID:      $Id$
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "app.h"
#endif

#include "wx/defs.h"

#include "wx/window.h"
#include "wx/frame.h"
#include "wx/button.h"
#include "wx/app.h"
#include "wx/utils.h"
#include "wx/gdicmn.h"
#include "wx/pen.h"
#include "wx/brush.h"
#include "wx/cursor.h"
#include "wx/intl.h"
#include "wx/icon.h"
#include "wx/palette.h"
#include "wx/dc.h"
#include "wx/dialog.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wx/module.h"
#include "wx/memory.h"
#include "wx/tooltip.h"
#include "wx/textctrl.h"
#include "wx/menu.h"
#include "wx/docview.h"
#include "wx/filename.h"

#include <string.h>

// mac

#ifndef __DARWIN__
  #if __option(profile)
    #include <profiler.h>
  #endif
#endif

#include "apprsrc.h"

#include "wx/mac/uma.h"
#include "wx/mac/macnotfy.h"

#ifdef __DARWIN__
#  include <CoreServices/CoreServices.h>
#  if defined(WXMAKINGDLL_CORE)
#    include <mach-o/dyld.h>
#  endif
#else
#  include <Sound.h>
#  include <Threads.h>
#  include <ToolUtils.h>
#  include <DiskInit.h>
#  include <Devices.h>
#endif

extern wxList wxPendingDelete;

#if wxUSE_THREADS
extern size_t g_numberOfThreads;
#endif // wxUSE_THREADS

// statics for implementation

static bool s_inYield = FALSE;

static bool s_inReceiveEvent = FALSE ;
static EventTime sleepTime = kEventDurationNoWait ;

#if !USE_SHARED_LIBRARY
IMPLEMENT_DYNAMIC_CLASS(wxApp, wxEvtHandler)
BEGIN_EVENT_TABLE(wxApp, wxEvtHandler)
    EVT_IDLE(wxApp::OnIdle)
    EVT_END_SESSION(wxApp::OnEndSession)
    EVT_QUERY_END_SESSION(wxApp::OnQueryEndSession)
END_EVENT_TABLE()
#endif


const short    kMacMinHeap = (29 * 1024) ;
// platform specific static variables

const short kwxMacMenuBarResource = 1 ;
const short kwxMacAppleMenuId = 1 ;

WXHRGN    wxApp::s_macCursorRgn = NULL;
wxWindow* wxApp::s_captureWindow = NULL ;
int       wxApp::s_lastMouseDown = 0 ;
long      wxApp::sm_lastMessageTime = 0;
long      wxApp::s_lastModifiers = 0 ;


bool      wxApp::s_macSupportPCMenuShortcuts = true ;
long      wxApp::s_macAboutMenuItemId = wxID_ABOUT ;
long      wxApp::s_macPreferencesMenuItemId = wxID_PREFERENCES ;
long      wxApp::s_macExitMenuItemId = wxID_EXIT ;
wxString  wxApp::s_macHelpMenuTitleName = wxT("&Help") ;

// Normally we're not a plugin
bool      wxApp::sm_isEmbedded = false;
//----------------------------------------------------------------------
// Core Apple Event Support
//----------------------------------------------------------------------

pascal OSErr AEHandleODoc( const AppleEvent *event , AppleEvent *reply , long refcon ) ;
pascal OSErr AEHandleOApp( const AppleEvent *event , AppleEvent *reply , long refcon ) ;
pascal OSErr AEHandlePDoc( const AppleEvent *event , AppleEvent *reply , long refcon ) ;
pascal OSErr AEHandleQuit( const AppleEvent *event , AppleEvent *reply , long refcon ) ;
pascal OSErr AEHandleRApp( const AppleEvent *event , AppleEvent *reply , long refcon ) ;

pascal OSErr AEHandleODoc( const AppleEvent *event , AppleEvent *reply , long WXUNUSED(refcon) )
{
    return wxTheApp->MacHandleAEODoc( (AppleEvent*) event , reply) ;
}

pascal OSErr AEHandleOApp( const AppleEvent *event , AppleEvent *reply , long WXUNUSED(refcon) )
{
    return wxTheApp->MacHandleAEOApp( (AppleEvent*) event , reply ) ;
}

pascal OSErr AEHandlePDoc( const AppleEvent *event , AppleEvent *reply , long WXUNUSED(refcon) )
{
    return wxTheApp->MacHandleAEPDoc( (AppleEvent*) event , reply ) ;
}

pascal OSErr AEHandleQuit( const AppleEvent *event , AppleEvent *reply , long WXUNUSED(refcon) )
{
    return wxTheApp->MacHandleAEQuit( (AppleEvent*) event , reply) ;
}

pascal OSErr AEHandleRApp( const AppleEvent *event , AppleEvent *reply , long WXUNUSED(refcon) )
{
    return wxTheApp->MacHandleAERApp( (AppleEvent*) event , reply) ;
}

// AEODoc Calls MacOpenFile on each of the files passed

short wxApp::MacHandleAEODoc(const WXEVENTREF event, WXEVENTREF WXUNUSED(reply))
{
    AEDescList docList;
    AEKeyword keywd;
    DescType returnedType;
    Size actualSize;
    long itemsInList;
    FSSpec theSpec;
    OSErr err;
    short i;
    err = AEGetParamDesc((AppleEvent *)event, keyDirectObject, typeAEList,&docList);
    if (err != noErr)
        return err;

    err = AECountItems(&docList, &itemsInList);
    if (err != noErr)
        return err;

    ProcessSerialNumber PSN ;
    PSN.highLongOfPSN = 0 ;
    PSN.lowLongOfPSN = kCurrentProcess ;
    SetFrontProcess( &PSN ) ;

    for (i = 1; i <= itemsInList; i++) {
        AEGetNthPtr(&docList, i, typeFSS, &keywd, &returnedType,
        (Ptr) & theSpec, sizeof(theSpec), &actualSize);
        wxString fName = wxMacFSSpec2MacFilename(&theSpec);
        MacOpenFile(fName);
    }
    return noErr;
}

// AEPDoc Calls MacPrintFile on each of the files passed

short wxApp::MacHandleAEPDoc(const WXEVENTREF event , WXEVENTREF WXUNUSED(reply))
{
    AEDescList docList;
    AEKeyword keywd;
    DescType returnedType;
    Size actualSize;
    long itemsInList;
    FSSpec theSpec;
    OSErr err;
    short i;
    err = AEGetParamDesc((AppleEvent *)event, keyDirectObject, typeAEList,&docList);
    if (err != noErr)
        return err;

    err = AECountItems(&docList, &itemsInList);
    if (err != noErr)
        return err;

    ProcessSerialNumber PSN ;
    PSN.highLongOfPSN = 0 ;
    PSN.lowLongOfPSN = kCurrentProcess ;
    SetFrontProcess( &PSN ) ;

    for (i = 1; i <= itemsInList; i++) {
        AEGetNthPtr(&docList, i, typeFSS, &keywd, &returnedType,
        (Ptr) & theSpec, sizeof(theSpec), &actualSize);
        wxString fName = wxMacFSSpec2MacFilename(&theSpec);
        MacPrintFile(fName);
    }
    return noErr;
}

// AEOApp calls MacNewFile

short wxApp::MacHandleAEOApp(const WXEVENTREF WXUNUSED(event) , WXEVENTREF WXUNUSED(reply))
{
    MacNewFile() ;
    return noErr ;
}

// AEQuit attempts to quit the application

short wxApp::MacHandleAEQuit(const WXEVENTREF WXUNUSED(event) , WXEVENTREF WXUNUSED(reply))
{
    wxWindow* win = GetTopWindow() ;
    if ( win )
    {
        wxCommandEvent exitEvent(wxEVT_COMMAND_MENU_SELECTED, s_macExitMenuItemId);
        if (!win->ProcessEvent(exitEvent))
            win->Close(TRUE ) ;
    }
    else
    {
        ExitMainLoop() ;
    }
    return noErr ;
}

// AEROApp calls MacReopenApp

short wxApp::MacHandleAERApp(const WXEVENTREF WXUNUSED(event) , WXEVENTREF WXUNUSED(reply))
{
    MacReopenApp() ;
    return noErr ;
}


//----------------------------------------------------------------------
// Support Routines linking the Mac...File Calls to the Document Manager
//----------------------------------------------------------------------

void wxApp::MacOpenFile(const wxString & fileName )
{
    wxDocManager* dm = wxDocManager::GetDocumentManager() ;
    if ( dm )
        dm->CreateDocument(fileName , wxDOC_SILENT ) ;
}

void wxApp::MacPrintFile(const wxString & fileName )
{
    wxDocManager* dm = wxDocManager::GetDocumentManager() ;
    if ( dm )
    {
        wxDocument *doc = dm->CreateDocument(fileName , wxDOC_SILENT ) ;
        if ( doc )
        {
            wxView* view = doc->GetFirstView() ;
            if( view )
            {
                wxPrintout *printout = view->OnCreatePrintout();
                if (printout)
                {
                    wxPrinter printer;
                    printer.Print(view->GetFrame(), printout, TRUE);
                    delete printout;
                }
            }
            if (doc->Close())
            {
                doc->DeleteAllViews();
                dm->RemoveDocument(doc) ;
            }
        }
    }
}

void wxApp::MacNewFile()
{
}

void wxApp::MacReopenApp()
{
    // eventually check for open docs, if none, call MacNewFile
}

//----------------------------------------------------------------------
// Carbon Event Handler
//----------------------------------------------------------------------

static const EventTypeSpec eventList[] =
{
    { kEventClassCommand, kEventProcessCommand } ,
    { kEventClassCommand, kEventCommandUpdateStatus } ,

    { kEventClassMenu, kEventMenuOpening },
    { kEventClassMenu, kEventMenuClosed },
    { kEventClassMenu, kEventMenuTargetItem },

    { kEventClassApplication , kEventAppActivated } ,
    { kEventClassApplication , kEventAppDeactivated } ,
    // handling the quit event is not recommended by apple
    // rather using the quit apple event - which we do

    { kEventClassAppleEvent , kEventAppleEvent } ,

    { kEventClassMouse , kEventMouseDown } ,
    { kEventClassMouse , kEventMouseMoved } ,
    { kEventClassMouse , kEventMouseUp } ,
    { kEventClassMouse , kEventMouseDragged } ,
    { 'WXMC' , 'WXMC' }
} ;

static pascal OSStatus
wxMacAppMenuEventHandler( EventHandlerCallRef handler , EventRef event , void *data )
{
    wxMenuBar* mbar = wxMenuBar::MacGetInstalledMenuBar();
    
    if ( mbar )
    {
        wxFrame* win = mbar->GetFrame();
        if ( win )
        {
            
            // VZ: we could find the menu from its handle here by examining all
            //     the menus in the menu bar recursively but knowing that neither
            //     wxMSW nor wxGTK do it why bother...
 #if 0
            MenuRef menuRef;

            GetEventParameter(event,
                              kEventParamDirectObject,
                              typeMenuRef, NULL,
                              sizeof(menuRef), NULL,
                              &menuRef);
 #endif // 0

            wxEventType type=0;        
            MenuCommand cmd=0;
            switch (GetEventKind(event))
            {
                case kEventMenuOpening:
                    type = wxEVT_MENU_OPEN;
                    break;
                case kEventMenuClosed:
                    type = wxEVT_MENU_CLOSE;
                    break;
                case kEventMenuTargetItem:
                    type = wxEVT_MENU_HIGHLIGHT;
                    GetEventParameter(event, kEventParamMenuCommand,
                                      typeMenuCommand, NULL,
                                      sizeof(cmd), NULL, &cmd);
                    if (cmd == 0) return eventNotHandledErr;
                    break;
                default:
                    wxFAIL_MSG(wxT("Unexpected menu event kind"));
                    break;
            }

            wxMenuEvent wxevent(type, cmd);
            wxevent.SetEventObject(win);

            (void)win->GetEventHandler()->ProcessEvent(wxevent);
        }
    }

    return eventNotHandledErr;
}

static pascal OSStatus wxMacAppCommandEventHandler( EventHandlerCallRef handler , EventRef event , void *data )
{
    OSStatus result = eventNotHandledErr ;

    HICommand command ;

    GetEventParameter( event, kEventParamDirectObject, typeHICommand, NULL,
        sizeof( HICommand ), NULL, &command );

    MenuCommand id = command.commandID ;
    if ( id == kHICommandPreferences )
        id = wxApp::s_macPreferencesMenuItemId ;

    wxMenuBar* mbar = wxMenuBar::MacGetInstalledMenuBar() ;
    wxMenu* menu = NULL ;
    wxMenuItem* item = NULL ;

    if ( mbar )
    {
        item = mbar->FindItem( id , &menu ) ;
        // it is not 100 % sure that an menu of id 0 is really ours, safety check
        if ( id == 0 && menu != NULL && menu->GetHMenu() != command.menu.menuRef )
        {
            item = NULL ;
            menu = NULL ;
        }
    }

    if ( item == NULL || menu == NULL || mbar == NULL )
        return result ;

       switch( GetEventKind( event ) )
       {
           case kEventProcessCommand :
           {
                if (item->IsCheckable())
                {
                    item->Check( !item->IsChecked() ) ;
                }

                menu->SendEvent( id , item->IsCheckable() ? item->IsChecked() : -1 ) ;
                result = noErr ;
            }
               break ;
        case kEventCommandUpdateStatus:
            // eventually trigger an updateui round
            result = noErr ;
            break ;
           default :
               break ;
       }

    return result ;
}

static pascal OSStatus wxMacAppApplicationEventHandler( EventHandlerCallRef handler , EventRef event , void *data )
{
    OSStatus result = eventNotHandledErr ;
    switch ( GetEventKind( event ) )
    {
        case kEventAppActivated :
            {
                if ( wxTheApp )
                    wxTheApp->SetActive( true , NULL ) ;
                result = noErr ;
            }
            break ;
        case kEventAppDeactivated :
            {
                if ( wxTheApp )
                    wxTheApp->SetActive( false , NULL ) ;
                result = noErr ;
            }
            break ;
        default :
            break ;
    }
    return result ;
}

pascal OSStatus wxMacAppEventHandler( EventHandlerCallRef handler , EventRef event , void *data )
{
    OSStatus result = eventNotHandledErr ;
    switch( GetEventClass( event ) )
    {
        case kEventClassCommand :
            result = wxMacAppCommandEventHandler( handler , event , data ) ;
            break ;
        case kEventClassApplication :
            result = wxMacAppApplicationEventHandler( handler , event , data ) ;
            break ;
        case kEventClassMenu :
            result = wxMacAppMenuEventHandler( handler , event , data ) ;
            break ;
        case kEventClassMouse :
            result = wxMacTopLevelMouseEventHandler( handler , event , NULL ) ;
            break ;
        case kEventClassAppleEvent :
            {
                EventRecord rec ;
                wxMacConvertEventToRecord( event , &rec ) ;
                result = AEProcessAppleEvent( &rec ) ;
            }
            break ;
        default :
            break ;
    }

    return result ;
}

DEFINE_ONE_SHOT_HANDLER_GETTER( wxMacAppEventHandler )

#if defined(WXMAKINGDLL_CORE) && !defined(__DARWIN__)
// we know it's there ;-)
WXIMPORT char std::__throws_bad_alloc ;
#endif

pascal static void wxMacAssertOutputHandler(OSType componentSignature, UInt32 options, 
    const char *assertionString, const char *exceptionLabelString, 
    const char *errorString, const char *fileName, long lineNumber, void *value, ConstStr255Param outputMsg)
{
    // flow into assert handling
    wxString fileNameStr ;
    wxString assertionStr ;
    wxString exceptionStr ;
    wxString errorStr ;
#if wxUSE_UNICODE
    fileNameStr = wxString(fileName, wxConvLocal);
    assertionStr = wxString(assertionString, wxConvLocal);
    exceptionStr = wxString((exceptionLabelString!=0) ? exceptionLabelString : "", wxConvLocal) ;
    errorStr = wxString((errorString!=0) ? errorString : "", wxConvLocal) ;
#else
    fileNameStr = fileName;
    assertionStr = assertionString;
    exceptionStr = (exceptionLabelString!=0) ? exceptionLabelString : "" ;
    errorStr = (errorString!=0) ? errorString : "" ;
#endif

#if 1
    // flow into log
    wxLogDebug( wxT("AssertMacros: %s %s %s file: %s, line: %ld (value %p)\n"), 
        assertionStr.c_str() , 
        exceptionStr.c_str() , 
        errorStr.c_str(), 
        fileNameStr.c_str(), lineNumber ,
        value ) ;
#else

    wxOnAssert(fileNameStr, lineNumber , assertionStr ,
        wxString::Format( wxT("%s %s value (%p)") ,exceptionStr, errorStr , value ) ) ;
#endif
}

bool wxApp::Initialize(int& argc, wxChar **argv)
{
    // Mac-specific

#if __WXDEBUG__
    InstallDebugAssertOutputHandler ( NewDebugAssertOutputHandlerUPP( wxMacAssertOutputHandler ) );
#endif
    UMAInitToolbox( 4, sm_isEmbedded ) ;
    SetEventMask( everyEvent ) ;
    UMAShowWatchCursor() ;

#if defined(WXMAKINGDLL_CORE) && defined(__DARWIN__)
    // open shared library resources from here since we don't have
    //   __wxinitialize in Mach-O shared libraries
    wxStAppResource::OpenSharedLibraryResource(NULL);
#endif

#ifndef __DARWIN__
#  if __option(profile)
    ProfilerInit( collectDetailed, bestTimeBase , 40000 , 50 ) ;
#  endif
#endif

#ifndef __DARWIN__
    // now avoid exceptions thrown for new (bad_alloc)
    // FIXME CS for some changes outside wxMac does not compile anymore
#if 0
    std::__throws_bad_alloc = 0 ;
#endif

#endif

    s_macCursorRgn = ::NewRgn() ;

    // Mac OS X passes a process serial number command line argument when
    // the application is launched from the Finder. This argument must be
    // removed from the command line arguments before being handled by the
    // application (otherwise applications would need to handle it)
    if ( argc > 1 )
    {
        static const wxChar *ARG_PSN = _T("-psn_");
        if ( wxStrncmp(argv[1], ARG_PSN, wxStrlen(ARG_PSN)) == 0 )
        {
            // remove this argument
            --argc;
            memmove(argv + 1, argv + 2, argc * sizeof(char *));
        }
    }

    if ( !wxAppBase::Initialize(argc, argv) )
        return false;

#if wxUSE_INTL
    wxFont::SetDefaultEncoding(wxLocale::GetSystemEncoding());
#endif


    wxMacCreateNotifierTable() ;

    UMAShowArrowCursor() ;

    return true;
}

bool wxApp::OnInitGui()
{
    if( !wxAppBase::OnInitGui() )
        return false ;

    InstallStandardEventHandler( GetApplicationEventTarget() ) ;

    if (!sm_isEmbedded)
    {
        InstallApplicationEventHandler(
            GetwxMacAppEventHandlerUPP(),
            GetEventTypeCount(eventList), eventList, wxTheApp, (EventHandlerRef *)&(wxTheApp->m_macEventHandler));
    }

    if (!sm_isEmbedded)
    {
        AEInstallEventHandler( kCoreEventClass , kAEOpenDocuments ,
                               NewAEEventHandlerUPP(AEHandleODoc) ,
                               0 , FALSE ) ;
        AEInstallEventHandler( kCoreEventClass , kAEOpenApplication ,
                               NewAEEventHandlerUPP(AEHandleOApp) ,
                               0 , FALSE ) ;
        AEInstallEventHandler( kCoreEventClass , kAEPrintDocuments ,
                               NewAEEventHandlerUPP(AEHandlePDoc) ,
                               0 , FALSE ) ;
        AEInstallEventHandler( kCoreEventClass , kAEReopenApplication ,
                               NewAEEventHandlerUPP(AEHandleRApp) ,
                               0 , FALSE ) ;
        AEInstallEventHandler( kCoreEventClass , kAEQuitApplication ,
                               NewAEEventHandlerUPP(AEHandleQuit) ,
                               0 , FALSE ) ;
    }

    return TRUE ;
}

void wxApp::CleanUp()
{
    wxToolTip::RemoveToolTips() ;

    // One last chance for pending objects to be cleaned up
    wxTheApp->DeletePendingObjects();

    wxMacDestroyNotifierTable() ;

#ifndef __DARWIN__
#  if __option(profile)
    ProfilerDump( (StringPtr)"\papp.prof" ) ;
    ProfilerTerm() ;
#  endif
#endif

#if defined(WXMAKINGDLL_CORE) && defined(__DARWIN__)
    // close shared library resources from here since we don't have
    //   __wxterminate in Mach-O shared libraries
    wxStAppResource::CloseSharedLibraryResource();
#endif

    UMACleanupToolbox() ;
    if (s_macCursorRgn) {
        ::DisposeRgn((RgnHandle)s_macCursorRgn);
    }

    #if 0
        TerminateAE() ;
    #endif

    wxAppBase::CleanUp();
}

//----------------------------------------------------------------------
// misc initialization stuff
//----------------------------------------------------------------------

// extern variable for shared library resource id
// need to be able to find it with NSLookupAndBindSymbol
short gSharedLibraryResource = kResFileNotOpened ;

#if defined(WXMAKINGDLL_CORE) && defined(__DARWIN__)
CFBundleRef gSharedLibraryBundle = NULL;
#endif /* WXMAKINGDLL_CORE && __DARWIN__ */

wxStAppResource::wxStAppResource()
{
    m_currentRefNum = CurResFile() ;
    if ( gSharedLibraryResource != kResFileNotOpened )
    {
        UseResFile( gSharedLibraryResource ) ;
    }
}

wxStAppResource::~wxStAppResource()
{
    if ( m_currentRefNum != kResFileNotOpened )
    {
        UseResFile( m_currentRefNum ) ;
    }
}

void wxStAppResource::OpenSharedLibraryResource(const void *initBlock)
{
    gSharedLibraryResource = kResFileNotOpened;

#ifdef WXMAKINGDLL_CORE
    if ( initBlock != NULL ) {
        const CFragInitBlock *theInitBlock = (const CFragInitBlock *)initBlock;
        FSSpec *fileSpec = NULL;

        if (theInitBlock->fragLocator.where == kDataForkCFragLocator) {
            fileSpec = theInitBlock->fragLocator.u.onDisk.fileSpec;
        }
        else if (theInitBlock->fragLocator.where == kResourceCFragLocator) {
            fileSpec = theInitBlock->fragLocator.u.inSegs.fileSpec;
        }

        if (fileSpec != NULL) {
            gSharedLibraryResource =  FSpOpenResFile(fileSpec, fsRdPerm);
        }
    }
    else {
#ifdef __DARWIN__
        // Open the shared library resource file if it is not yet open
        NSSymbol    theSymbol;
        NSModule    theModule;
        const char *theLibPath;

        gSharedLibraryBundle = CFBundleGetBundleWithIdentifier(CFSTR("com.wxwindows.wxWindows"));
        if (gSharedLibraryBundle != NULL) {
            // wxWindows has been bundled into a framework
            //   load the framework resources

            gSharedLibraryResource = CFBundleOpenBundleResourceMap(gSharedLibraryBundle);
        }
        else {
            // wxWindows is a simple dynamic shared library
            //   load the resources from the data fork of a separate resource file
            wxString theResPath;
            wxString theName;
            FSRef  theResRef;
            OSErr  theErr = noErr;

            // get the library path
            theSymbol = NSLookupAndBindSymbol("_gSharedLibraryResource");
            theModule = NSModuleForSymbol(theSymbol);
            theLibPath = NSLibraryNameForModule(theModule);

            // if we call wxLogDebug from here then, as wxTheApp hasn't been
            // created yet when we're called from wxApp::Initialize(), wxLog
            // is going to create a default stderr-based log target instead of
            // the expected normal GUI one -- don't do it, if we really want
            // to see this message just use fprintf() here
#if 0
            wxLogDebug( wxT("wxMac library installation name is '%s'"),
                        theLibPath );
#endif

            // allocate copy to replace .dylib.* extension with .rsrc
            if (theLibPath != NULL) {
#if wxUSE_UNICODE
                theResPath = wxString(theLibPath, wxConvLocal);
#else
                theResPath = wxString(theLibPath);
#endif
                // replace '_core' with '' in case of multi-lib build
                theResPath.Replace(wxT("_core"), wxEmptyString);
                // replace ".dylib" shared library extension with ".rsrc"
                theResPath.Replace(wxT(".dylib"), wxT(".rsrc"));
                // Find the begining of the filename
                theName = theResPath.AfterLast('/');

#if 0
                wxLogDebug( wxT("wxMac resources file name is '%s'"),
                            theResPath.mb_str() );
#endif

                theErr = FSPathMakeRef((UInt8 *) theResPath.mb_str(), &theResRef, false);
                if (theErr != noErr) {
                    // try in current directory (using name only)
                    theErr = FSPathMakeRef((UInt8 *) theName.mb_str(), &theResRef, false);
                }

                // open the resource file
                if (theErr == noErr) {
                    theErr = FSOpenResourceFile( &theResRef, 0, NULL, fsRdPerm,
                                                 &gSharedLibraryResource);
                }
                if (theErr != noErr) {
#ifdef __WXDEBUG__
                    wxLogDebug( wxT("unable to open wxMac resource file '%s'\n"),
                                theResPath.mb_str() );
#endif // __WXDEBUG__
                }

            }
        }
#endif /* __DARWIN__ */
    }
#endif /* WXMAKINGDLL_CORE */
}

void wxStAppResource::CloseSharedLibraryResource()
{
#ifdef WXMAKINGDLL_CORE
    // Close the shared library resource file
    if (gSharedLibraryResource != kResFileNotOpened) {
#ifdef __DARWIN__
        if (gSharedLibraryBundle != NULL) {
            CFBundleCloseBundleResourceMap(gSharedLibraryBundle,
                                           gSharedLibraryResource);
            gSharedLibraryBundle = NULL;
        }
        else
#endif /* __DARWIN__ */
        {
            CloseResFile(gSharedLibraryResource);
        }
        gSharedLibraryResource = kResFileNotOpened;
    }
#endif /* WXMAKINGDLL_CORE */
}

#if defined(WXMAKINGDLL_CORE) && !defined(__DARWIN__)

// for shared libraries we have to manually get the correct resource
// ref num upon initializing and releasing when terminating, therefore
// the __wxinitialize and __wxterminate must be used

extern "C" {
    void __sinit(void);    /*    (generated by linker)    */
    pascal OSErr __initialize(const CFragInitBlock *theInitBlock);
    pascal void __terminate(void);
}

pascal OSErr __wxinitialize(const CFragInitBlock *theInitBlock)
{
    wxStAppResource::OpenSharedLibraryResource( theInitBlock ) ;
    return __initialize( theInitBlock ) ;
}

pascal void __wxterminate(void)
{
    wxStAppResource::CloseSharedLibraryResource() ;
    __terminate() ;
}

#endif /* WXMAKINGDLL_CORE && !__DARWIN__ */

bool wxMacConvertEventToRecord( EventRef event , EventRecord *rec)
{
    bool converted = ConvertEventRefToEventRecord( event,rec) ;
    OSStatus err = noErr ;
    if ( !converted )
    {
        switch( GetEventClass( event ) )
        {
            case kEventClassKeyboard :
            {
                converted = true ;
                switch( GetEventKind(event) )
                {
                    case kEventRawKeyDown :
                        rec->what = keyDown ;
                        break ;
                    case kEventRawKeyRepeat :
                        rec->what = autoKey ;
                        break ;
                    case kEventRawKeyUp :
                        rec->what = keyUp ;
                        break ;
                    case kEventRawKeyModifiersChanged :
                        rec->what = nullEvent ;
                        break ;
                    default :
                        converted = false ;
                        break ;
                }
                if ( converted )
                {
                    UInt32 keyCode ;
                    unsigned char charCode ;
                    UInt32 modifiers ;
                    GetMouse( &rec->where) ;

                    err = GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, NULL, 4, NULL, &modifiers);
                    err = GetEventParameter(event, kEventParamKeyCode, typeUInt32, NULL, 4, NULL, &keyCode);
                    err = GetEventParameter(event, kEventParamKeyMacCharCodes, typeChar, NULL, 1, NULL, &charCode);
                    rec->modifiers = modifiers ;
                    rec->message = (keyCode << 8 ) + charCode ;
                }
            }
            break ;
            case kEventClassTextInput :
            {
                switch( GetEventKind( event ) )
                {
                    case kEventTextInputUnicodeForKeyEvent :
                        {
                            EventRef rawEvent ;
                            err = GetEventParameter( event , kEventParamTextInputSendKeyboardEvent ,typeEventRef,NULL,sizeof(rawEvent),NULL,&rawEvent ) ;
                            converted = true ;
                            {
                                UInt32 keyCode ;
                                unsigned char charCode ;
                                UInt32 modifiers ;
                                GetMouse( &rec->where) ;
                                rec->what = keyDown ;
                                err = GetEventParameter(rawEvent, kEventParamKeyModifiers, typeUInt32, NULL, 4, NULL, &modifiers);
                                err = GetEventParameter(rawEvent, kEventParamKeyCode, typeUInt32, NULL, 4, NULL, &keyCode);
                                err = GetEventParameter(rawEvent, kEventParamKeyMacCharCodes, typeChar, NULL, 1, NULL, &charCode);
                                rec->modifiers = modifiers ;
                                rec->message = (keyCode << 8 ) + charCode ;
                            }
                       }
                        break ;
                    default :
                        break ;
                }
            }
            break ;
        }
    }

    return converted ;
}

wxApp::wxApp()
{
  m_printMode = wxPRINT_WINDOWS;

  m_macCurrentEvent = NULL ;
  m_macCurrentEventHandlerCallRef = NULL ;
}

int wxApp::MainLoop()
{
    m_keepGoing = TRUE;

    while (m_keepGoing)
    {
        MacDoOneEvent() ;
    }

    return 0;
}

void wxApp::ExitMainLoop()
{
      m_keepGoing = FALSE;
}

// Is a message/event pending?
bool wxApp::Pending()
{
    // without the receive event (with pull param = false ) nothing is ever reported
    EventRef theEvent;
    ReceiveNextEvent (0, NULL, kEventDurationNoWait, false, &theEvent);
    return GetNumEventsInQueue( GetMainEventQueue() ) > 0 ; 
}

// Dispatch a message.
bool wxApp::Dispatch()
{
    MacDoOneEvent() ;

    return true;
}

void wxApp::OnIdle(wxIdleEvent& event)
{
    wxAppBase::OnIdle(event);

    // If they are pending events, we must process them: pending events are
    // either events to the threads other than main or events posted with
    // wxPostEvent() functions
    wxMacProcessNotifierAndPendingEvents();

  if(!wxMenuBar::MacGetInstalledMenuBar() && wxMenuBar::MacGetCommonMenuBar())
    wxMenuBar::MacGetCommonMenuBar()->MacInstallMenuBar();
}

void wxApp::WakeUpIdle()
{
    wxMacWakeUp() ;
}

void wxApp::Exit()
{
    wxApp::CleanUp();
    ::ExitToShell() ;
}

void wxApp::OnEndSession(wxCloseEvent& WXUNUSED(event))
{
    if (GetTopWindow())
        GetTopWindow()->Close(TRUE);
}

// Default behaviour: close the application with prompts. The
// user can veto the close, and therefore the end session.
void wxApp::OnQueryEndSession(wxCloseEvent& event)
{
    if (GetTopWindow())
    {
        if (!GetTopWindow()->Close(!event.CanVeto()))
            event.Veto(TRUE);
    }
}

extern "C" void wxCYield() ;
void wxCYield()
{
    wxYield() ;
}

// Yield to other processes

bool wxApp::Yield(bool onlyIfNeeded)
{
    if (s_inYield)
    {
        if ( !onlyIfNeeded )
        {
            wxFAIL_MSG( wxT("wxYield called recursively" ) );
        }

        return FALSE;
    }

    s_inYield = TRUE;

#if wxUSE_THREADS
    YieldToAnyThread() ;
#endif
    // by definition yield should handle all non-processed events

    EventRef theEvent;

    OSStatus status = noErr ;
    do
    {
        s_inReceiveEvent = true ;
        status = ReceiveNextEvent(0, NULL,kEventDurationNoWait,true,&theEvent) ;
        s_inReceiveEvent = false ;

        if ( status == eventLoopTimedOutErr )
        {
            // make sure next time the event loop will trigger idle events
            sleepTime = kEventDurationNoWait ;
        }
        else if ( status == eventLoopQuitErr )
        {
            // according to QA1061 this may also occur when a WakeUp Process
            // is executed
        }
        else
        {
            MacHandleOneEvent( theEvent ) ;
            ReleaseEvent(theEvent);
        }
    } while( status == noErr ) ;

    wxMacProcessNotifierAndPendingEvents() ;
    s_inYield = FALSE;

    return TRUE;
}

void wxApp::MacDoOneEvent()
{
    EventRef theEvent;

    s_inReceiveEvent = true ;
    OSStatus status = ReceiveNextEvent(0, NULL,sleepTime,true,&theEvent) ;
    s_inReceiveEvent = false ;
    if ( status == eventLoopTimedOutErr )
    {
        if ( wxTheApp->ProcessIdle() )
            sleepTime = kEventDurationNoWait ;
        else
        {
#if wxUSE_THREADS
            if (g_numberOfThreads)
            {
                sleepTime = kEventDurationNoWait;
            }
            else
#endif // wxUSE_THREADS
            {
                sleepTime = kEventDurationSecond;
            }
        }
    }
    else if ( status == eventLoopQuitErr )
    {
        // according to QA1061 this may also occur when a WakeUp Process
        // is executed
    }
    else
    {
        MacHandleOneEvent( theEvent ) ;
        ReleaseEvent(theEvent);
        sleepTime = kEventDurationNoWait ;
    }
    // repeaters

    DeletePendingObjects() ;
    wxMacProcessNotifierAndPendingEvents() ;
}

/*virtual*/ void wxApp::MacHandleUnhandledEvent( WXEVENTREF evr )
{
    // Override to process unhandled events as you please    
}

void wxApp::MacHandleOneEvent( WXEVENTREF evr )
{
    EventTargetRef theTarget;
    theTarget = GetEventDispatcherTarget();
    m_macCurrentEvent = evr ;
    OSStatus status = SendEventToEventTarget ((EventRef) evr , theTarget);
    if(status == eventNotHandledErr)
    {
        MacHandleUnhandledEvent(evr);
    }
    wxMacProcessNotifierAndPendingEvents() ;
}

long wxMacTranslateKey(unsigned char key, unsigned char code) ;
long wxMacTranslateKey(unsigned char key, unsigned char code)
{
    long retval = key ;
    switch (key)
    {
        case kHomeCharCode :
                 retval = WXK_HOME;
          break;
        case kEnterCharCode :
                 retval = WXK_RETURN;
          break;
        case kEndCharCode :
                 retval = WXK_END;
          break;
        case kHelpCharCode :
                 retval = WXK_HELP;
          break;
        case kBackspaceCharCode :
                 retval = WXK_BACK;
          break;
        case kTabCharCode :
                 retval = WXK_TAB;
          break;
        case kPageUpCharCode :
                 retval = WXK_PAGEUP;
          break;
        case kPageDownCharCode :
                 retval = WXK_PAGEDOWN;
          break;
        case kReturnCharCode :
                 retval = WXK_RETURN;
          break;
            case kFunctionKeyCharCode :
            {
                switch( code )
                {
                    case 0x7a :
                        retval = WXK_F1 ;
                        break;
                    case 0x78 :
                        retval = WXK_F2 ;
                        break;
                    case 0x63 :
                        retval = WXK_F3 ;
                        break;
                    case 0x76 :
                        retval = WXK_F4 ;
                        break;
                    case 0x60 :
                        retval = WXK_F5 ;
                        break;
                    case 0x61 :
                        retval = WXK_F6 ;
                        break;
                    case 0x62:
                        retval = WXK_F7 ;
                        break;
                    case 0x64 :
                        retval = WXK_F8 ;
                        break;
                    case 0x65 :
                        retval = WXK_F9 ;
                        break;
                    case 0x6D :
                        retval = WXK_F10 ;
                        break;
                    case 0x67 :
                        retval = WXK_F11 ;
                        break;
                    case 0x6F :
                        retval = WXK_F12 ;
                        break;
                    case 0x69 :
                        retval = WXK_F13 ;
                        break;
                    case 0x6B :
                        retval = WXK_F14 ;
                        break;
                    case 0x71 :
                        retval = WXK_F15 ;
                        break;
                }
            }
            break ;
            case kEscapeCharCode :
                retval = WXK_ESCAPE ;
            break ;
            case kLeftArrowCharCode :
                retval = WXK_LEFT ;
            break ;
            case kRightArrowCharCode :
                retval = WXK_RIGHT ;
            break ;
            case kUpArrowCharCode :
                retval = WXK_UP ;
            break ;
            case kDownArrowCharCode :
                retval = WXK_DOWN ;
            break ;
            case kDeleteCharCode :
                retval = WXK_DELETE ;
             default:
            break ;
     } // end switch

    return retval;
}

int wxMacKeyCodeToModifier(wxKeyCode key)
{
    switch (key)
    {
    case WXK_START:
    case WXK_MENU:
        return cmdKey;

    case WXK_SHIFT:
        return shiftKey;

    case WXK_CAPITAL:
        return alphaLock;

    case WXK_ALT:
        return optionKey;

    case WXK_CONTROL:
        return controlKey;

    default:
        return 0;
    }
}

bool wxGetKeyState(wxKeyCode key) //virtual key code if < 10.2.x, else see below
{
//#ifdef __DARWIN__
//	wxHIDKeyboard keyboard;
//	return keyboard.IsActive(key);
//#else
// TODO:  Have it use HID Manager on OSX...
//if OS X > 10.2 (i.e. 10.2.x)
//a known apple bug prevents the system from determining led
//states with GetKeys... can only determine caps lock led
   return !!(GetCurrentKeyModifiers() & wxMacKeyCodeToModifier(key)); 
//else
//  KeyMapByteArray keymap; 
//  GetKeys((BigEndianLong*)keymap);
//  return !!(BitTst(keymap, (sizeof(KeyMapByteArray)*8) - iKey));
//#endif
}


bool wxApp::MacSendKeyDownEvent( wxWindow* focus , long keymessage , long modifiers , long when , short wherex , short wherey )
{
    if ( !focus )
        return false ;

    short keycode ;
    short keychar ;
    keychar = short(keymessage & charCodeMask);
    keycode = short(keymessage & keyCodeMask) >> 8 ;

    if ( modifiers & ( controlKey|shiftKey|optionKey ) )
    {
        // control interferes with some built-in keys like pgdown, return etc. therefore we remove the controlKey modifier
        // and look at the character after
        UInt32 state = 0;
        UInt32 keyInfo = KeyTranslate((Ptr)GetScriptManagerVariable(smKCHRCache), ( modifiers & (~(controlKey|shiftKey|optionKey))) | keycode, &state);
        keychar = short(keyInfo & charCodeMask);
        keycode = short(keyInfo & keyCodeMask) >> 8 ;
    }
    long keyval = wxMacTranslateKey(keychar, keycode) ;
    long realkeyval = keyval ;
    if ( keyval == keychar )
    {
        // we are not on a special character combo -> pass the real os event-value to EVT_CHAR, but not to EVT_KEY (make upper first)
        realkeyval = short(keymessage & charCodeMask) ;
        keyval = wxToupper( keyval ) ;
    }

    wxKeyEvent event(wxEVT_KEY_DOWN);
    bool handled = false ;
    event.m_shiftDown = modifiers & shiftKey;
    event.m_controlDown = modifiers & controlKey;
    event.m_altDown = modifiers & optionKey;
    event.m_metaDown = modifiers & cmdKey;
    event.m_keyCode = keyval ;

    event.m_x = wherex;
    event.m_y = wherey;
    event.m_timeStamp = when;
    event.SetEventObject(focus);
    handled = focus->GetEventHandler()->ProcessEvent( event ) ;
    if ( handled && event.GetSkipped() )
        handled = false ;
    if ( !handled )
    {
#if wxUSE_ACCEL
        if (!handled)
        {
            wxWindow *ancestor = focus;
            while (ancestor)
            {
                int command = ancestor->GetAcceleratorTable()->GetCommand( event );
                if (command != -1)
                {
                    wxCommandEvent command_event( wxEVT_COMMAND_MENU_SELECTED, command );
                    handled = ancestor->GetEventHandler()->ProcessEvent( command_event );
                    break;
                }
                if (ancestor->IsTopLevel())
                    break;
                ancestor = ancestor->GetParent();
            }
        }
#endif // wxUSE_ACCEL
    }
    if (!handled)
    {
        event.Skip( FALSE ) ;
        event.SetEventType( wxEVT_CHAR ) ;
        // raw value again
        event.m_keyCode = realkeyval ;

        handled = focus->GetEventHandler()->ProcessEvent( event ) ;
        if ( handled && event.GetSkipped() )
            handled = false ;
    }
    if ( !handled && (keyval == WXK_TAB) )
    {
        wxWindow* iter = focus->GetParent() ;
        while( iter && !handled )
        {
            if ( iter->HasFlag( wxTAB_TRAVERSAL ) )
            {
                wxNavigationKeyEvent new_event;
                new_event.SetEventObject( focus );
                new_event.SetDirection( !event.ShiftDown() );
                /* CTRL-TAB changes the (parent) window, i.e. switch notebook page */
                new_event.SetWindowChange( event.ControlDown() );
                new_event.SetCurrentFocus( focus );
                handled = focus->GetParent()->GetEventHandler()->ProcessEvent( new_event );
                if ( handled && new_event.GetSkipped() )
                    handled = false ;
            }
            iter = iter->GetParent() ;
        }
    }
    // backdoor handler for default return and command escape
    if ( !handled && (!focus->IsKindOf(CLASSINFO(wxControl) ) || !focus->MacCanFocus() ) )
    {
          // if window is not having a focus still testing for default enter or cancel
          // TODO add the UMA version for ActiveNonFloatingWindow
          wxWindow* focus = wxFindWinFromMacWindow( FrontWindow() ) ;
          if ( focus )
          {
            if ( keyval == WXK_RETURN )
            {
                 wxButton *def = wxDynamicCast(focus->GetDefaultItem(),
                                                       wxButton);
                 if ( def && def->IsEnabled() )
                 {
                     wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, def->GetId() );
                     event.SetEventObject(def);
                     def->Command(event);
                     return true ;
                }
            }
            /* generate wxID_CANCEL if command-. or <esc> has been pressed (typically in dialogs) */
            else if (keyval == WXK_ESCAPE || (keyval == '.' && modifiers & cmdKey ) )
            {
                  wxCommandEvent new_event(wxEVT_COMMAND_BUTTON_CLICKED,wxID_CANCEL);
                  new_event.SetEventObject( focus );
                  handled = focus->GetEventHandler()->ProcessEvent( new_event );
            }
          }
    }
    return handled ;
}

bool wxApp::MacSendKeyUpEvent( wxWindow* focus , long keymessage , long modifiers , long when , short wherex , short wherey )
{
    if ( !focus )
        return false ;

    short keycode ;
    short keychar ;
    keychar = short(keymessage & charCodeMask);
    keycode = short(keymessage & keyCodeMask) >> 8 ;
    if ( modifiers & ( controlKey|shiftKey|optionKey ) )
    {
        // control interferes with some built-in keys like pgdown, return etc. therefore we remove the controlKey modifier
        // and look at the character after
        UInt32 state = 0;
        UInt32 keyInfo = KeyTranslate((Ptr)GetScriptManagerVariable(smKCHRCache), ( modifiers & (~(controlKey|shiftKey|optionKey))) | keycode, &state);
        keychar = short(keyInfo & charCodeMask);
        keycode = short(keyInfo & keyCodeMask) >> 8 ;
    }
    long keyval = wxMacTranslateKey(keychar, keycode) ;

    if ( keyval == keychar )
    {
        keyval = wxToupper( keyval ) ;
    }
    bool handled = false ;

    wxKeyEvent event(wxEVT_KEY_UP);
    event.m_shiftDown = modifiers & shiftKey;
    event.m_controlDown = modifiers & controlKey;
    event.m_altDown = modifiers & optionKey;
    event.m_metaDown = modifiers & cmdKey;
    event.m_keyCode = keyval ;

    event.m_x = wherex;
    event.m_y = wherey;
    event.m_timeStamp = when;
    event.SetEventObject(focus);
    handled = focus->GetEventHandler()->ProcessEvent( event ) ;

    return handled ;
}
