# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.2 (http://bakefile.sourceforge.net)
#     Do not modify, all changes will be overwritten!
# =========================================================================

!include ../../../build/os2/config.wat

# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

# Speed up compilation a bit:
!ifdef __LOADDLL__
!  loaddll wcc      wccd
!  loaddll wccaxp   wccdaxp
!  loaddll wcc386   wccd386
!  loaddll wpp      wppdi86
!  loaddll wppaxp   wppdaxp
!  loaddll wpp386   wppd386
!  loaddll wlink    wlink
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

PORTNAME =
!ifeq USE_GUI 0
PORTNAME = base
!endif
!ifeq USE_GUI 1
PORTNAME = pm
!endif
WXDEBUGFLAG =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
WXDEBUGFLAG = d
!endif
!endif
!ifeq DEBUG_FLAG 1
WXDEBUGFLAG = d
!endif
WXUNICODEFLAG =
!ifeq UNICODE 1
WXUNICODEFLAG = u
!endif
WXUNIVNAME =
!ifeq WXUNIV 1
WXUNIVNAME = univ
!endif
WXDLLFLAG =
!ifeq SHARED 1
WXDLLFLAG = dll
!endif
LIBTYPE_SUFFIX =
!ifeq SHARED 0
LIBTYPE_SUFFIX = pm_lib
!endif
!ifeq SHARED 1
LIBTYPE_SUFFIX = pm_dll
!endif
EXTRALIBS_FOR_BASE =
!ifeq MONOLITHIC 0
EXTRALIBS_FOR_BASE = 
!endif
!ifeq MONOLITHIC 1
EXTRALIBS_FOR_BASE =  
!endif
__gizmosdll___depname =
!ifeq SHARED 1
__gizmosdll___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.dll
!endif
__gizmos_xrcdll___depname =
!ifeq SHARED 1
!ifeq USE_XRC 1
__gizmos_xrcdll___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.dll
!endif
!endif
__WXLIB_XRC_p =
!ifeq MONOLITHIC 0
__WXLIB_XRC_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_xrc.lib
!endif
__WXLIB_XML_p =
!ifeq MONOLITHIC 0
__WXLIB_XML_p = &
	wxbase$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_xml.lib
!endif
__gizmoslib___depname =
!ifeq SHARED 0
__gizmoslib___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib
!endif
__gizmos_xrclib___depname =
!ifeq SHARED 0
!ifeq USE_XRC 1
__gizmos_xrclib___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.lib
!endif
!endif
__DEBUGINFO =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO = debug all
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO = 
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO = 
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO = debug all
!endif
__WXLIB_MONO_p =
!ifeq MONOLITHIC 1
__WXLIB_MONO_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif
__LIB_TIFF_p =
!ifeq USE_GUI 1
__LIB_TIFF_p = wxtiff$(WXDEBUGFLAG).lib
!endif
__LIB_JPEG_p =
!ifeq USE_GUI 1
__LIB_JPEG_p = wxjpeg$(WXDEBUGFLAG).lib
!endif
__LIB_PNG_p =
!ifeq USE_GUI 1
__LIB_PNG_p = wxpng$(WXDEBUGFLAG).lib
!endif
__WXLIB_CORE_p =
!ifeq MONOLITHIC 0
__WXLIB_CORE_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core.lib
!endif
__WXLIB_BASE_p =
!ifeq MONOLITHIC 0
__WXLIB_BASE_p = &
	wxbase$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif
__DEBUGINFO_3 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_3 = -d2
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_3 = -d0
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_3 = -d0
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_3 = -d2
!endif
__OPTIMIZEFLAG =
!ifeq BUILD debug
__OPTIMIZEFLAG = -od
!endif
!ifeq BUILD release
__OPTIMIZEFLAG = -ot -ox
!endif
__THREADSFLAG =
!ifeq USE_THREADS 0
__THREADSFLAG = 
!endif
!ifeq USE_THREADS 1
__THREADSFLAG = -bm
!endif
__RUNTIME_LIBS =
!ifeq RUNTIME_LIBS dynamic
__RUNTIME_LIBS = -br
!endif
!ifeq RUNTIME_LIBS static
__RUNTIME_LIBS = 
!endif
__RTTIFLAG =
!ifeq USE_RTTI 0
__RTTIFLAG = 
!endif
!ifeq USE_RTTI 1
__RTTIFLAG = -xr
!endif
__EXCEPTIONSFLAG =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONSFLAG = 
!endif
!ifeq USE_EXCEPTIONS 1
__EXCEPTIONSFLAG = -xs
!endif
__WXUNIV_DEFINE_p =
!ifeq WXUNIV 1
__WXUNIV_DEFINE_p = -d__WXUNIVERSAL__
!endif
__DEBUG_DEFINE_p =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif
!endif
!ifeq DEBUG_FLAG 1
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif
__EXCEPTIONS_DEFINE_p =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONS_DEFINE_p = -dwxNO_EXCEPTIONS
!endif
__RTTI_DEFINE_p =
!ifeq USE_RTTI 0
__RTTI_DEFINE_p = -dwxNO_RTTI
!endif
__THREAD_DEFINE_p =
!ifeq USE_THREADS 0
__THREAD_DEFINE_p = -dwxNO_THREADS
!endif
__UNICODE_DEFINE_p =
!ifeq UNICODE 1
__UNICODE_DEFINE_p = -d_UNICODE
!endif
__GFXCTX_DEFINE_p =
!ifeq USE_GDIPLUS 1
__GFXCTX_DEFINE_p = -dwxUSE_GRAPHICS_CONTEXT=1
!endif

### Variables: ###

WX_RELEASE_NODOT = 28
OBJS = &
	wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
LIBDIRNAME = ..\..\src\gizmos\..\..\..\lib\wat_$(LIBTYPE_SUFFIX)$(CFG)
SETUPHDIR = &
	$(LIBDIRNAME)\$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)
GIZMOSDLL_CXXFLAGS = -bd $(__DEBUGINFO_3) $(__OPTIMIZEFLAG) $(__THREADSFLAG) &
	$(__RUNTIME_LIBS) -d__WXPM__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) &
	$(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) &
	-i=..\..\src\gizmos\..\..\..\include -wx -wcd=549 -wcd=656 -wcd=657 -wcd=667 &
	-i=..\..\src\gizmos\..\..\include -dWXUSINGDLL -dWXMAKINGDLL_GIZMOS &
	/fh=$(OBJS)\wxprec_gizmosdll.pch $(__RTTIFLAG) $(__EXCEPTIONSFLAG) &
	$(CPPFLAGS) $(CXXFLAGS)
GIZMOSDLL_OBJECTS =  &
	$(OBJS)\gizmosdll_dummy.obj &
	$(OBJS)\gizmosdll_dynamicsash.obj &
	$(OBJS)\gizmosdll_editlbox.obj &
	$(OBJS)\gizmosdll_ledctrl.obj &
	$(OBJS)\gizmosdll_multicell.obj &
	$(OBJS)\gizmosdll_splittree.obj &
	$(OBJS)\gizmosdll_statpict.obj
GIZMOS_XRCDLL_CXXFLAGS = -bd $(__DEBUGINFO_3) $(__OPTIMIZEFLAG) &
	$(__THREADSFLAG) $(__RUNTIME_LIBS) -d__WXPM__ $(__WXUNIV_DEFINE_p) &
	$(__DEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) &
	$(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) &
	-i=$(SETUPHDIR) -i=..\..\src\gizmos\..\..\..\include -wx -wcd=549 -wcd=656 &
	-wcd=657 -wcd=667 -i=..\..\src\gizmos\..\..\include -dWXUSINGDLL &
	-dWXMAKINGDLL_GIZMOS_XRC /fh=$(OBJS)\wxprec_gizmos_xrcdll.pch &
	$(__RTTIFLAG) $(__EXCEPTIONSFLAG) $(CPPFLAGS) $(CXXFLAGS)
GIZMOS_XRCDLL_OBJECTS =  &
	$(OBJS)\gizmos_xrcdll_dummy.obj &
	$(OBJS)\gizmos_xrcdll_xh_statpict.obj
GIZMOSLIB_CXXFLAGS = $(__DEBUGINFO_3) $(__OPTIMIZEFLAG) $(__THREADSFLAG) &
	$(__RUNTIME_LIBS) -d__WXPM__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) &
	$(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) &
	-i=..\..\src\gizmos\..\..\..\include -wx -wcd=549 -wcd=656 -wcd=657 -wcd=667 &
	-i=..\..\src\gizmos\..\..\include /fh=$(OBJS)\wxprec_gizmoslib.pch &
	$(__RTTIFLAG) $(__EXCEPTIONSFLAG) $(CPPFLAGS) $(CXXFLAGS)
GIZMOSLIB_OBJECTS =  &
	$(OBJS)\gizmoslib_dummy.obj &
	$(OBJS)\gizmoslib_dynamicsash.obj &
	$(OBJS)\gizmoslib_editlbox.obj &
	$(OBJS)\gizmoslib_ledctrl.obj &
	$(OBJS)\gizmoslib_multicell.obj &
	$(OBJS)\gizmoslib_splittree.obj &
	$(OBJS)\gizmoslib_statpict.obj
GIZMOS_XRCLIB_CXXFLAGS = $(__DEBUGINFO_3) $(__OPTIMIZEFLAG) $(__THREADSFLAG) &
	$(__RUNTIME_LIBS) -d__WXPM__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) &
	$(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) &
	-i=..\..\src\gizmos\..\..\..\include -wx -wcd=549 -wcd=656 -wcd=657 -wcd=667 &
	-i=..\..\src\gizmos\..\..\include /fh=$(OBJS)\wxprec_gizmos_xrclib.pch &
	$(__RTTIFLAG) $(__EXCEPTIONSFLAG) $(CPPFLAGS) $(CXXFLAGS)
GIZMOS_XRCLIB_OBJECTS =  &
	$(OBJS)\gizmos_xrclib_dummy.obj &
	$(OBJS)\gizmos_xrclib_xh_statpict.obj


all : $(OBJS)
$(OBJS) :
	-if not exist $(OBJS) mkdir $(OBJS)

### Targets: ###

all : .SYMBOLIC $(__gizmosdll___depname) $(__gizmos_xrcdll___depname) $(__gizmoslib___depname) $(__gizmos_xrclib___depname)

clean : .SYMBOLIC 
	-if exist $(OBJS)\*.obj del $(OBJS)\*.obj
	-if exist $(OBJS)\*.res del $(OBJS)\*.res
	-if exist $(OBJS)\*.lbc del $(OBJS)\*.lbc
	-if exist $(OBJS)\*.ilk del $(OBJS)\*.ilk
	-if exist $(OBJS)\*.pch del $(OBJS)\*.pch
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.dll
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.dll
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.lib
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib
	-del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.lib

!ifeq SHARED 1
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.dll :  $(GIZMOSDLL_OBJECTS)
	@%create $(OBJS)\gizmosdll.lbc
	@%append $(OBJS)\gizmosdll.lbc option quiet
	@%append $(OBJS)\gizmosdll.lbc name $^@
	@%append $(OBJS)\gizmosdll.lbc option caseexact
	@%append $(OBJS)\gizmosdll.lbc $(LDFLAGS) $(__DEBUGINFO)  libpath $(LIBDIRNAME)
	@for %i in ($(GIZMOSDLL_OBJECTS)) do @%append $(OBJS)\gizmosdll.lbc file %i
	@for %i in ( $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE) upm32.lib $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p) ) do @%append $(OBJS)\gizmosdll.lbc library %i
	@%append $(OBJS)\gizmosdll.lbc
	@%append $(OBJS)\gizmosdll.lbc system os2v2 dll
	wlink @$(OBJS)\gizmosdll.lbc
	wlib -q -n -b $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib +$^@
!endif

!ifeq SHARED 1
!ifeq USE_XRC 1
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.dll :  $(GIZMOS_XRCDLL_OBJECTS) $(__gizmosdll___depname)
	@%create $(OBJS)\gizmos_xrcdll.lbc
	@%append $(OBJS)\gizmos_xrcdll.lbc option quiet
	@%append $(OBJS)\gizmos_xrcdll.lbc name $^@
	@%append $(OBJS)\gizmos_xrcdll.lbc option caseexact
	@%append $(OBJS)\gizmos_xrcdll.lbc $(LDFLAGS) $(__DEBUGINFO)  libpath $(LIBDIRNAME)
	@for %i in ($(GIZMOS_XRCDLL_OBJECTS)) do @%append $(OBJS)\gizmos_xrcdll.lbc file %i
	@for %i in ( $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE) upm32.lib $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib $(__WXLIB_XRC_p)  $(__WXLIB_XML_p)  $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p) ) do @%append $(OBJS)\gizmos_xrcdll.lbc library %i
	@%append $(OBJS)\gizmos_xrcdll.lbc
	@%append $(OBJS)\gizmos_xrcdll.lbc system os2v2 dll
	wlink @$(OBJS)\gizmos_xrcdll.lbc
	wlib -q -n -b $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.lib +$^@
!endif
!endif

!ifeq SHARED 0
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos.lib :  $(GIZMOSLIB_OBJECTS)
	@%create $(OBJS)\gizmoslib.lbc
	@for %i in ($(GIZMOSLIB_OBJECTS)) do @%append $(OBJS)\gizmoslib.lbc +%i
	wlib -q -p4096 -n -b $^@ @$(OBJS)\gizmoslib.lbc
!endif

!ifeq SHARED 0
!ifeq USE_XRC 1
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_gizmos_xrc.lib :  $(GIZMOS_XRCLIB_OBJECTS)
	@%create $(OBJS)\gizmos_xrclib.lbc
	@for %i in ($(GIZMOS_XRCLIB_OBJECTS)) do @%append $(OBJS)\gizmos_xrclib.lbc +%i
	wlib -q -p4096 -n -b $^@ @$(OBJS)\gizmos_xrclib.lbc
!endif
!endif

$(OBJS)\gizmosdll_dummy.obj :  .AUTODEPEND ../../src/gizmos\..\..\..\src\common\dummy.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_dynamicsash.obj :  .AUTODEPEND ../../src/gizmos\dynamicsash.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_editlbox.obj :  .AUTODEPEND ../../src/gizmos\editlbox.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_ledctrl.obj :  .AUTODEPEND ../../src/gizmos\ledctrl.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_multicell.obj :  .AUTODEPEND ../../src/gizmos\multicell.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_splittree.obj :  .AUTODEPEND ../../src/gizmos\splittree.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmosdll_statpict.obj :  .AUTODEPEND ../../src/gizmos\statpict.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSDLL_CXXFLAGS) $<

$(OBJS)\gizmos_xrcdll_dummy.obj :  .AUTODEPEND ../../src/gizmos\..\..\..\src\common\dummy.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOS_XRCDLL_CXXFLAGS) $<

$(OBJS)\gizmos_xrcdll_xh_statpict.obj :  .AUTODEPEND ../../src/gizmos\xh_statpict.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOS_XRCDLL_CXXFLAGS) $<

$(OBJS)\gizmoslib_dummy.obj :  .AUTODEPEND ../../src/gizmos\..\..\..\src\common\dummy.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_dynamicsash.obj :  .AUTODEPEND ../../src/gizmos\dynamicsash.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_editlbox.obj :  .AUTODEPEND ../../src/gizmos\editlbox.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_ledctrl.obj :  .AUTODEPEND ../../src/gizmos\ledctrl.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_multicell.obj :  .AUTODEPEND ../../src/gizmos\multicell.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_splittree.obj :  .AUTODEPEND ../../src/gizmos\splittree.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmoslib_statpict.obj :  .AUTODEPEND ../../src/gizmos\statpict.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOSLIB_CXXFLAGS) $<

$(OBJS)\gizmos_xrclib_dummy.obj :  .AUTODEPEND ../../src/gizmos\..\..\..\src\common\dummy.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOS_XRCLIB_CXXFLAGS) $<

$(OBJS)\gizmos_xrclib_xh_statpict.obj :  .AUTODEPEND ../../src/gizmos\xh_statpict.cpp
	$(CXX) -bt=os2 -zq -fo=$^@ $(GIZMOS_XRCLIB_CXXFLAGS) $<

