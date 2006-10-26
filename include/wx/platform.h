/**
* Name:        wx/platform.h
* Purpose:     define the OS and compiler identification macros
* Author:      Vadim Zeitlin
* Modified by:
* Created:     29.10.01 (extracted from wx/defs.h)
* RCS-ID:      $Id$
* Copyright:   (c) 1997-2001 Vadim Zeitlin
* Licence:     wxWindows licence
*/

/* THIS IS A C FILE, DON'T USE C++ FEATURES (IN PARTICULAR COMMENTS) IN IT */

#ifndef _WX_PLATFORM_H_
#define _WX_PLATFORM_H_


/*
    Codewarrior doesn't define any Windows symbols until some headers
    are included
*/
#ifdef __MWERKS__
#    include <stddef.h>
#endif

/*
    WXMAC variants
    __WXMAC_CLASSIC__ means ppc non-carbon builds, __WXMAC_CARBON__ means
    carbon API available (mach or cfm builds) , __WXMAC_OSX__ means mach-o
    builds, running under 10.2 + only
*/
#ifdef __WXMAC__
#    if defined(__MACH__)
#        define __WXMAC_OSX__
#        define __WXMAC_CARBON__
#        include <AvailabilityMacros.h>
#        ifndef MAC_OS_X_VERSION_10_4
#           define MAC_OS_X_VERSION_10_4 1040
#        endif
#        ifndef MAC_OS_X_VERSION_10_5
#           define MAC_OS_X_VERSION_10_5 1050
#        endif
#        ifdef __WXMAC_XCODE__
#            include <unistd.h>
#            include "wx/mac/carbon/config_xcode.h"
#        endif
#    else
#        if TARGET_CARBON
#            define __WXMAC_CARBON__
#        else
#            define __WXMAC_CLASSIC__
#        endif
#    endif
#endif

/*
    __WXOSX__ is a common define to wxMac (Carbon) and wxCocoa ports under OS X.
 */
#if defined(__WXMAC_OSX__) || defined(__WXCOCOA__)
#   define __WXOSX__
#endif

/*
   first define Windows symbols if they're not defined on the command line: we
   can autodetect everything we need if _WIN32 is defined
 */
#if defined(__CYGWIN__) && defined(__WINDOWS__)
#    ifndef __WXMSW__
#        define __WXMSW__
#    endif

#    ifndef _WIN32
#        define _WIN32
#    endif

#    ifndef WIN32
#        define WIN32
#    endif
#endif

#if defined(__PALMOS__)
#   if __PALMOS__ == 0x06000000
#       define __WXPALMOS6__
#   endif
#   if __PALMOS__ == 0x05000000
#       define __WXPALMOS5__
#   endif
#   ifndef __WXPALMOS__
#       define __WXPALMOS__
#   endif
#   ifdef __WXMSW__
#       undef __WXMSW__
#   endif
#   ifdef __WINDOWS__
#       undef __WINDOWS__
#   endif
#   ifdef __WIN32__
#       undef __WIN32__
#   endif
#   ifdef WIN32
#       undef WIN32
#   endif
#   ifdef _WIN32
#       undef _WIN32
#   endif
#endif

#if defined(_WIN64)
#    ifndef _WIN32
        /*
            a lot of code (mistakenly) uses #ifdef _WIN32 to either test for
            Windows or to test for !__WIN16__, so we must define _WIN32 for
            Win64 as well to ensure that the existing code continues to work.
         */
#       define _WIN32
#   endif /* !_WIN32 */

#   ifndef __WIN64__
#       define __WIN64__
#   endif /* !__WIN64__ */
#endif /* _WIN64 */

#if (defined(_WIN32) || defined(WIN32) || defined(__NT__) || defined(__WXWINCE__)) \
    && !defined(__WXMOTIF__) && !defined(__WXGTK__) && !defined(__WXX11__)
#    ifndef __WXMSW__
#        define __WXMSW__
#    endif

#    ifndef __WIN32__
#        define __WIN32__
#    endif
#endif /* Win32 */

#if defined(__WXMSW__) || defined(__WIN32__)
#   if !defined(__WINDOWS__)
#       define __WINDOWS__
#   endif
#endif

/* detect MS SmartPhone */
#if defined( WIN32_PLATFORM_WFSP )
#   ifndef __SMARTPHONE__
#       define __SMARTPHONE__
#   endif
#   ifndef __WXWINCE__
#       define __WXWINCE__
#   endif
#endif

/* detect PocketPC */
#if defined( WIN32_PLATFORM_PSPC )
#   ifndef __POCKETPC__
#       define __POCKETPC__
#   endif
#   ifndef __WXWINCE__
#       define __WXWINCE__
#   endif
#endif

/* detect Standard WinCE SDK */
#if defined( WCE_PLATFORM_STANDARDSDK )
#   ifndef __WINCE_STANDARDSDK__
#       define __WINCE_STANDARDSDK__
#   endif
#   ifndef __WXWINCE__
#       define __WXWINCE__
#   endif
#endif

#if defined(_WIN32_WCE) && !defined(WIN32_PLATFORM_WFSP) && !defined(WIN32_PLATFORM_PSPC)
#   if (_WIN32_WCE >= 400)
#       ifndef __WINCE_NET__
#           define __WINCE_NET__
#       endif
#   elif (_WIN32_WCE >= 200)
#       ifndef __HANDHELDPC__
#           define __HANDHELDPC__
#       endif
#   endif
#   ifndef __WXWINCE__
#       define __WXWINCE__
#   endif
#endif

#if defined(__POCKETPC__) || defined(__SMARTPHONE__) || defined(__WXGPE__)
#   define __WXHANDHELD__
#endif

/*
   Include wx/setup.h for the Unix platform defines generated by configure and
   the library compilation options

   Note that it must be included before defining hardware symbols below as they
   could be already defined by configure
 */
#include "wx/setup.h"

/*
   Hardware platform detection.

   VC++ defines _M_xxx symbols.
 */
#if defined(_M_IX86) || defined(i386) || defined(__i386) || defined(__i386__)
    #ifndef __INTEL__
        #define __INTEL__
    #endif
#endif /* x86 */

#if defined(_M_IA64)
    #ifndef __IA64__
        #define __IA64__
    #endif
#endif /* ia64 */

#if defined(_M_MPPC) || defined(__PPC__)
    #ifndef __POWERPC__
        #define __POWERPC__
    #endif
#endif /* alpha */

#if defined(_M_ALPHA) || defined(__AXP__)
    #ifndef __ALPHA__
        #define __ALPHA__
    #endif
#endif /* alpha */


/*
   adjust the Unicode setting: wxUSE_UNICODE should be defined as 0 or 1
   and is used by wxWidgets, _UNICODE and/or UNICODE may be defined or used by
   the system headers so bring these settings in sync
 */

/* set wxUSE_UNICODE to 1 if UNICODE or _UNICODE is defined */
#if defined(_UNICODE) || defined(UNICODE)
#   undef wxUSE_UNICODE
#   define wxUSE_UNICODE 1
#else /* !UNICODE */
#   ifndef wxUSE_UNICODE
#       define wxUSE_UNICODE 0
#   endif
#endif /* UNICODE/!UNICODE */

/* and vice versa: define UNICODE and _UNICODE if wxUSE_UNICODE is 1 */
#if wxUSE_UNICODE
#   ifndef _UNICODE
#       define _UNICODE
#   endif
#   ifndef UNICODE
#       define UNICODE
#   endif
#endif /* wxUSE_UNICODE */

#if defined( __MWERKS__ ) && !defined(__INTEL__)
/* otherwise MSL headers bring in WIN32 dependant APIs */
#undef UNICODE
#endif


/*
   This macro can be used to test the Open Watcom version.
*/
#ifndef __WATCOMC__
#   define wxWATCOM_VERSION(major,minor) 0
#   define wxCHECK_WATCOM_VERSION(major,minor) 0
#   define wxONLY_WATCOM_EARLIER_THAN(major,minor) 0
#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
#   error "Only Open Watcom is supported in this release"
#else
#   define wxWATCOM_VERSION(major,minor) ( major * 100 + minor * 10 + 1100 )
#   define wxCHECK_WATCOM_VERSION(major,minor) ( __WATCOMC__ >= wxWATCOM_VERSION(major,minor) )
#   define wxONLY_WATCOM_EARLIER_THAN(major,minor) ( __WATCOMC__ < wxWATCOM_VERSION(major,minor) )
#endif

/*
   check the consistency of the settings in setup.h: note that this must be
   done after setting wxUSE_UNICODE correctly as it is used in wx/chkconf.h
 */
#include "wx/chkconf.h"


/*
   some compilers don't support iostream.h any longer, while some of theme
   are not updated with <iostream> yet, so override the users setting here
   in such case.
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#    undef wxUSE_IOSTREAMH
#    define wxUSE_IOSTREAMH 0
#elif defined(__DMC__) || defined(__WATCOMC__)
#    undef wxUSE_IOSTREAMH
#    define wxUSE_IOSTREAMH 1
#elif defined(__MINGW32__)
#    undef wxUSE_IOSTREAMH
#    define wxUSE_IOSTREAMH 0
#endif /* compilers with/without iostream.h */

/*
   old C++ headers (like <iostream.h>) declare classes in the global namespace
   while the new, standard ones (like <iostream>) do it in std:: namespace,
   unless it's an old gcc version.

   using this macro allows constuctions like "wxSTD iostream" to work in
   either case
 */
#if !wxUSE_IOSTREAMH && (!defined(__GNUC__) || ( __GNUC__ > 2 ) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95))
#    define wxSTD std::
#else
#    define wxSTD
#endif

/*
   OS: first of all, test for MS-DOS platform. We must do this before testing
       for Unix, because DJGPP compiler defines __unix__ under MS-DOS
 */
#if defined(__GO32__) || defined(__DJGPP__) || defined(__DOS__)
#    ifndef __DOS__
#        define __DOS__
#    endif
    /* size_t is the same as unsigned int for Watcom 11 compiler, */
    /* so define it if it hadn't been done by configure yet */
#    if !defined(wxSIZE_T_IS_UINT) && !defined(wxSIZE_T_IS_ULONG)
#        ifdef __WATCOMC__
#            define wxSIZE_T_IS_UINT
#        endif
#        ifdef __DJGPP__
#            define wxSIZE_T_IS_ULONG
#        endif
#    endif

/*
   OS: then test for generic Unix defines, then for particular flavours and
       finally for Unix-like systems
 */
#elif defined(__UNIX__) || defined(__unix) || defined(__unix__) || \
      defined(____SVR4____) || defined(__LINUX__) || defined(__sgi) || \
      defined(__hpux) || defined(sun) || defined(__SUN__) || defined(_AIX) || \
      defined(__EMX__) || defined(__VMS) || defined(__BEOS__)

#    define __UNIX_LIKE__

    /* Helps SGI compilation, apparently */
#    ifdef __SGI__
#        ifdef __GNUG__
#            define __need_wchar_t
#        else /* !gcc */
            /*
               Note I use the term __SGI_CC__ for both cc and CC, its not a good
               idea to mix gcc and cc/CC, the name mangling is different
             */
#            define __SGI_CC__
#        endif /* gcc/!gcc */

        /* system headers use this symbol and not __cplusplus in some places */
#       ifndef _LANGUAGE_C_PLUS_PLUS
#           define _LANGUAGE_C_PLUS_PLUS
#       endif
#    endif  /* SGI */

#    if defined(sun) || defined(__SUN__)
#        ifndef __GNUG__
#            ifndef __SUNCC__
#                define __SUNCC__
#            endif /* Sun CC */
#        endif
#    endif /* Sun */

#    ifdef __EMX__
#        define OS2EMX_PLAIN_CHAR
#    endif

    /* define __HPUX__ for HP-UX where standard macro is __hpux */
#    if defined(__hpux) && !defined(__HPUX__)
#        define __HPUX__
#    endif /* HP-UX */

#    if defined(__CYGWIN__) || defined(__WINE__)
#        if !defined(wxSIZE_T_IS_UINT)
#            define wxSIZE_T_IS_UINT
#        endif
#    endif
#elif defined(applec) || \
      defined(THINK_C) || \
      (defined(__MWERKS__) && !defined(__INTEL__))
      /* MacOS */
#    if !defined(wxSIZE_T_IS_UINT) && !defined(wxSIZE_T_IS_ULONG)
#        define wxSIZE_T_IS_ULONG
#    endif
#elif defined(__WXMAC__) && defined(__APPLE__)
    /* Mac OS X */
#    define __UNIX_LIKE__

    /*
      These defines are needed when compiling using Project Builder
      with a non generated setup0.h
    */
#    ifndef __UNIX__
#        define __UNIX__ 1
#    endif
#    ifndef __BSD__
#        define __BSD__ 1
#    endif
#    ifndef __DARWIN__
#        define __DARWIN__ 1
#    endif
#    ifndef __POWERPC__
#        define __POWERPC__ 1
#    endif
#    ifndef TARGET_CARBON
#        define TARGET_CARBON 1
#    endif

#    if !defined(wxSIZE_T_IS_UINT) && !defined(wxSIZE_T_IS_ULONG)
#        define wxSIZE_T_IS_ULONG
#    endif
    /*
       Some code has been added to workaround defects(?) in the
       bundled gcc compiler. These corrections are identified by
       __DARWIN__ for Darwin related corrections (wxMac, wxMotif)
     */
#elif defined(__OS2__)

    /* wxOS2 vs. non wxOS2 ports on OS2 platform */
#    if !defined(__WXMOTIF__) && !defined(__WXGTK__) && !defined(__WXX11__)
#        ifndef __WXPM__
#            define __WXPM__
#        endif
#    endif

#    if defined(__IBMCPP__)
#        define __VISAGEAVER__ __IBMCPP__
#    endif

    /* Place other OS/2 compiler environment defines here */
#    if defined(__VISAGECPP__)
        /* VisualAge is the only thing that understands _Optlink */
#        define LINKAGEMODE _Optlink
#    endif
#    define wxSIZE_T_IS_UINT

#elif defined(__PALMOS__)
#    ifdef __WIN32__
#        error "__WIN32__ should not be defined for PalmOS"
#    endif
#    ifdef __WINDOWS__
#        error "__WINDOWS__ should not be defined for PalmOS"
#    endif
#    ifdef __WXMSW__
#        error "__WXMSW__ should not be defined for PalmOS"
#    endif

#else   /* Windows */
#    ifndef __WINDOWS__
#        define __WINDOWS__
#    endif  /* Windows */

    /* to be changed for Win64! */
#    ifndef __WIN32__
#        error "__WIN32__ should be defined for Win32 and Win64, Win16 is not supported"
#    endif

    /*
       define another standard symbol for Microsoft Visual C++: the standard
       one (_MSC_VER) is also defined by Metrowerks compiler
     */
#    if defined(_MSC_VER) && !defined(__MWERKS__)
#        define __VISUALC__ _MSC_VER
#    elif defined(__BCPLUSPLUS__) && !defined(__BORLANDC__)
#        define __BORLANDC__
#    elif defined(__WATCOMC__)
#    elif defined(__SC__)
#        define __SYMANTECC__
#    endif  /* compiler */

    /* size_t is the same as unsigned int for all Windows compilers we know, */
    /* so define it if it hadn't been done by configure yet */
#    if !defined(wxSIZE_T_IS_UINT) && !defined(wxSIZE_T_IS_ULONG)
#        define wxSIZE_T_IS_UINT
#    endif
#endif  /* OS */

/*
   if we're on a Unix system but didn't use configure (so that setup.h didn't
   define __UNIX__), do define __UNIX__ now
 */
#if !defined(__UNIX__) && defined(__UNIX_LIKE__)
#    define __UNIX__
#endif /* Unix */

#if defined(__WXMOTIF__) || defined(__WXX11__)
#    define __X__
#endif

#ifdef __SC__
#    ifdef __DMC__
#         define __DIGITALMARS__
#    else
#         define __SYMANTEC__
#    endif
#endif

#ifdef __INTEL_COMPILER
#   define __INTELC__
#endif

/*
   We get "Large Files (ILP32) not supported in strict ANSI mode." #error
   from HP-UX standard headers when compiling with g++ without this:
 */
#if defined(__HPUX__) && !defined(__STDC_EXT__)
#   define __STDC_EXT__ 1
#endif

/* Force linking against required libraries under Windows: */
#ifdef __WXWINCE__
#   include "wx/msw/wince/libraries.h"
#elif defined __WINDOWS__
#   include "wx/msw/libraries.h"
#endif

/*
   This macro can be used to test the gcc version and can be used like this:

#    if wxCHECK_GCC_VERSION(3, 1)
        ... we have gcc 3.1 or later ...
#    else
        ... no gcc at all or gcc < 3.1 ...
#    endif
*/
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
    #define wxCHECK_GCC_VERSION( major, minor ) \
        ( ( __GNUC__ > (major) ) \
            || ( __GNUC__ == (major) && __GNUC_MINOR__ >= (minor) ) )
#else
    #define wxCHECK_GCC_VERSION( major, minor ) 0
#endif

/*
   This macro can be used to check that the version of mingw32 compiler is
   at least maj.min
 */
#if ( defined( __GNUWIN32__ ) || defined( __MINGW32__ ) || \
    ( defined( __CYGWIN__ ) && defined( __WINDOWS__ ) ) || \
      wxCHECK_WATCOM_VERSION(1,0) ) && \
    !defined(__DOS__) && \
    !defined(__WXPM__) && \
    !defined(__WXMOTIF__) && \
    !defined(__WXGTK__) && \
    !defined(__WXX11__) && \
    !defined(__WXPALMOS__)
#    include "wx/msw/gccpriv.h"
#else
#    undef wxCHECK_W32API_VERSION
#    define wxCHECK_W32API_VERSION(maj, min) (0)
#endif

#if defined (__WXMSW__)
#    if !defined(__WATCOMC__)
#        define wxHAVE_RAW_BITMAP
#    endif
#endif

#if defined (__WXMAC__)
#    if ( !defined(__MACH__) || ( defined(__BIG_ENDIAN__) && __BIG_ENDIAN__ ) )
#        define WORDS_BIGENDIAN 1
#    else
#        undef WORDS_BIGENDIAN
#    endif
#endif

/* Choose which method we will use for updating menus
 * - in OnIdle, or when we receive a wxEVT_MENU_OPEN event.
 * Presently, only Windows and GTK+ support wxEVT_MENU_OPEN.
 */
#ifndef wxUSE_IDLEMENUUPDATES
#    if (defined(__WXMSW__) || defined(__WXGTK__)) && !defined(__WXUNIVERSAL__)
#        define wxUSE_IDLEMENUUPDATES 0
#    else
#        define wxUSE_IDLEMENUUPDATES 1
#    endif
#endif

/*
 * Define symbols that are not yet in
 * configure or possibly some setup.h files.
 * They will need to be added.
 */

#ifndef wxUSE_FILECONFIG
#    if wxUSE_CONFIG
#        define wxUSE_FILECONFIG 1
#    else
#        define wxUSE_FILECONFIG 0
#    endif
#endif

#ifndef wxUSE_HOTKEY
#    define wxUSE_HOTKEY 0
#endif

#if !defined(wxUSE_WXDIB) && defined(__WXMSW__)
#    define wxUSE_WXDIB 1
#endif

/*
    We need AvailabilityMacros.h for ifdefing out things that don't exist on
    OSX 10.2 and lower
    FIXME:  We need a better way to detect for 10.3 then including a system header
*/
#ifdef __DARWIN__
    #include <AvailabilityMacros.h>
#endif

#endif /* _WX_PLATFORM_H_ */
