# =========================================================================
#     This makefile was generated by
#     Bakefile 0.1.1 (http://bakefile.sourceforge.net)
#     Do not modify, all changes will be overwritten!
# =========================================================================

!include ../../../build/msw/config.wat

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
PORTNAME = msw
!endif
VENDORTAG =
!ifeq OFFICIAL_BUILD 0
VENDORTAG = _$(VENDOR)
!endif
!ifeq OFFICIAL_BUILD 1
VENDORTAG = 
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
WXDLLFLAG =
!ifeq SHARED 1
WXDLLFLAG = dll
!endif
WXUNICODEFLAG =
!ifeq UNICODE 1
WXUNICODEFLAG = u
!endif
WXUNIVNAME =
!ifeq WXUNIV 1
WXUNIVNAME = univ
!endif
__DEBUGINFO =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO = -d2
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO = -d0
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO = -d0
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO = -d2
!endif
__DEBUGINFO_1 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = debug all
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = 
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_1 = 
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_1 = debug all
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
__LIB_JPEG_p =
!ifeq USE_GUI 1
__LIB_JPEG_p = wxjpeg$(WXDEBUGFLAG).lib
!endif
__LIB_PNG_p =
!ifeq USE_GUI 1
__LIB_PNG_p = wxpng$(WXDEBUGFLAG).lib
!endif
__LIB_TIFF_p =
!ifeq USE_GUI 1
__LIB_TIFF_p = wxtiff$(WXDEBUGFLAG).lib
!endif
__OPTIMIZEFLAG =
!ifeq BUILD debug
__OPTIMIZEFLAG = -od
!endif
!ifeq BUILD release
__OPTIMIZEFLAG = -ot -ox
!endif
__RUNTIME_LIBS =
!ifeq RUNTIME_LIBS dynamic
__RUNTIME_LIBS = -br
!endif
!ifeq RUNTIME_LIBS static
__RUNTIME_LIBS = 
!endif
__UNICODE_DEFINE_p =
!ifeq UNICODE 1
__UNICODE_DEFINE_p = -dwxUSE_UNICODE=1
!endif
__WXLIB_BASE_p =
!ifeq MONOLITHIC 0
__WXLIB_BASE_p = wxbase25$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib
!endif
__WXLIB_CORE_p =
!ifeq MONOLITHIC 0
__WXLIB_CORE_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_core.lib
!endif
__WXLIB_MONO_p =
!ifeq MONOLITHIC 1
__WXLIB_MONO_p = &
	wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib
!endif
__WXUNIV_DEFINE_p =
!ifeq WXUNIV 1
__WXUNIV_DEFINE_p = -d__WXUNIVERSAL__
!endif
__mmediadll___depname =
!ifeq SHARED 1
__mmediadll___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)250$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia_wat$(VENDORTAG).dll
!endif
__mmedialib___depname =
!ifeq SHARED 0
__mmedialib___depname = &
	$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib
!endif

### Variables: ###

LIBDIRNAME = &
	..\..\src\mmedia\..\..\..\lib\wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
MMEDIADLL_CXXFLAGS = $(CPPFLAGS) -bd $(__DEBUGINFO) $(__OPTIMIZEFLAG) -bm &
	$(__RUNTIME_LIBS) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__UNICODE_DEFINE_p) -i=..\..\src\mmedia\..\..\..\include &
	-i=$(LIBDIRNAME) -i=..\..\src\mmedia\..\..\..\src\tiff &
	-i=..\..\src\mmedia\..\..\..\src\jpeg &
	-i=..\..\src\mmedia\..\..\..\src\png &
	-i=..\..\src\mmedia\..\..\..\src\zlib &
	-i=..\..\src\mmedia\..\..\..\src\regex &
	-i=..\..\src\mmedia\..\..\..\src\expat\lib &
	-i=..\..\src\mmedia\..\..\include -dWXUSINGDLL -dWXMAKINGDLL_MMEDIA &
	$(CXXFLAGS) /fh=$(OBJS)\wxprec_mmediadll.pch
MMEDIADLL_OBJECTS =  &
	$(OBJS)\mmediadll_dummy.obj &
	$(OBJS)\mmediadll_cdwin.obj &
	$(OBJS)\mmediadll_sndwin.obj &
	$(OBJS)\mmediadll_vidwin.obj &
	$(OBJS)\mmediadll_cdbase.obj &
	$(OBJS)\mmediadll_g711.obj &
	$(OBJS)\mmediadll_g721.obj &
	$(OBJS)\mmediadll_g723_24.obj &
	$(OBJS)\mmediadll_g723_40.obj &
	$(OBJS)\mmediadll_g72x.obj &
	$(OBJS)\mmediadll_sndaiff.obj &
	$(OBJS)\mmediadll_sndbase.obj &
	$(OBJS)\mmediadll_sndcodec.obj &
	$(OBJS)\mmediadll_sndcpcm.obj &
	$(OBJS)\mmediadll_sndfile.obj &
	$(OBJS)\mmediadll_sndg72x.obj &
	$(OBJS)\mmediadll_sndmsad.obj &
	$(OBJS)\mmediadll_sndpcm.obj &
	$(OBJS)\mmediadll_sndulaw.obj &
	$(OBJS)\mmediadll_sndwav.obj &
	$(OBJS)\mmediadll_vidbase.obj
MMEDIALIB_CXXFLAGS = $(CPPFLAGS) $(__DEBUGINFO) $(__OPTIMIZEFLAG) -bm &
	$(__RUNTIME_LIBS) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__UNICODE_DEFINE_p) -i=..\..\src\mmedia\..\..\..\include &
	-i=$(LIBDIRNAME) -i=..\..\src\mmedia\..\..\..\src\tiff &
	-i=..\..\src\mmedia\..\..\..\src\jpeg &
	-i=..\..\src\mmedia\..\..\..\src\png &
	-i=..\..\src\mmedia\..\..\..\src\zlib &
	-i=..\..\src\mmedia\..\..\..\src\regex &
	-i=..\..\src\mmedia\..\..\..\src\expat\lib &
	-i=..\..\src\mmedia\..\..\include $(CXXFLAGS) &
	/fh=$(OBJS)\wxprec_mmedialib.pch
MMEDIALIB_OBJECTS =  &
	$(OBJS)\mmedialib_dummy.obj &
	$(OBJS)\mmedialib_cdwin.obj &
	$(OBJS)\mmedialib_sndwin.obj &
	$(OBJS)\mmedialib_vidwin.obj &
	$(OBJS)\mmedialib_cdbase.obj &
	$(OBJS)\mmedialib_g711.obj &
	$(OBJS)\mmedialib_g721.obj &
	$(OBJS)\mmedialib_g723_24.obj &
	$(OBJS)\mmedialib_g723_40.obj &
	$(OBJS)\mmedialib_g72x.obj &
	$(OBJS)\mmedialib_sndaiff.obj &
	$(OBJS)\mmedialib_sndbase.obj &
	$(OBJS)\mmedialib_sndcodec.obj &
	$(OBJS)\mmedialib_sndcpcm.obj &
	$(OBJS)\mmedialib_sndfile.obj &
	$(OBJS)\mmedialib_sndg72x.obj &
	$(OBJS)\mmedialib_sndmsad.obj &
	$(OBJS)\mmedialib_sndpcm.obj &
	$(OBJS)\mmedialib_sndulaw.obj &
	$(OBJS)\mmedialib_sndwav.obj &
	$(OBJS)\mmedialib_vidbase.obj
OBJS = &
	wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)

MAKEARGS = BUILD=$(BUILD) CFG=$(CFG) CPPFLAGS=$(CPPFLAGS) CXX=$(CXX) CXXFLAGS=$(CXXFLAGS) DEBUG_FLAG=$(DEBUG_FLAG) DEBUG_INFO=$(DEBUG_INFO) LDFLAGS=$(LDFLAGS) MONOLITHIC=$(MONOLITHIC) OFFICIAL_BUILD=$(OFFICIAL_BUILD) RUNTIME_LIBS=$(RUNTIME_LIBS) SHARED=$(SHARED) UNICODE=$(UNICODE) USE_GUI=$(USE_GUI) VENDOR=$(VENDOR) WXUNIV=$(WXUNIV)


all : $(OBJS)
$(OBJS) :
	-if not exist $(OBJS) mkdir $(OBJS)

### Targets: ###

all : .SYMBOLIC $(__mmediadll___depname) $(__mmedialib___depname)

$(OBJS)\mmediadll_cdbase.obj :  .AUTODEPEND ../../src/mmedia\cdbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_cdwin.obj :  .AUTODEPEND ../../src/mmedia\cdwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_dummy.obj :  .AUTODEPEND ../../src/mmedia\..\..\..\src\msw\dummy.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_g711.obj :  .AUTODEPEND ../../src/mmedia\g711.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_g721.obj :  .AUTODEPEND ../../src/mmedia\g721.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_g723_24.obj :  .AUTODEPEND ../../src/mmedia\g723_24.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_g723_40.obj :  .AUTODEPEND ../../src/mmedia\g723_40.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_g72x.obj :  .AUTODEPEND ../../src/mmedia\g72x.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndaiff.obj :  .AUTODEPEND ../../src/mmedia\sndaiff.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndbase.obj :  .AUTODEPEND ../../src/mmedia\sndbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndcodec.obj :  .AUTODEPEND ../../src/mmedia\sndcodec.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndcpcm.obj :  .AUTODEPEND ../../src/mmedia\sndcpcm.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndfile.obj :  .AUTODEPEND ../../src/mmedia\sndfile.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndg72x.obj :  .AUTODEPEND ../../src/mmedia\sndg72x.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndmsad.obj :  .AUTODEPEND ../../src/mmedia\sndmsad.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndpcm.obj :  .AUTODEPEND ../../src/mmedia\sndpcm.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndulaw.obj :  .AUTODEPEND ../../src/mmedia\sndulaw.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndwav.obj :  .AUTODEPEND ../../src/mmedia\sndwav.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_sndwin.obj :  .AUTODEPEND ../../src/mmedia\sndwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_vidbase.obj :  .AUTODEPEND ../../src/mmedia\vidbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmediadll_vidwin.obj :  .AUTODEPEND ../../src/mmedia\vidwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIADLL_CXXFLAGS) $<

$(OBJS)\mmedialib_cdbase.obj :  .AUTODEPEND ../../src/mmedia\cdbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_cdwin.obj :  .AUTODEPEND ../../src/mmedia\cdwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_dummy.obj :  .AUTODEPEND ../../src/mmedia\..\..\..\src\msw\dummy.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_g711.obj :  .AUTODEPEND ../../src/mmedia\g711.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_g721.obj :  .AUTODEPEND ../../src/mmedia\g721.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_g723_24.obj :  .AUTODEPEND ../../src/mmedia\g723_24.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_g723_40.obj :  .AUTODEPEND ../../src/mmedia\g723_40.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_g72x.obj :  .AUTODEPEND ../../src/mmedia\g72x.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndaiff.obj :  .AUTODEPEND ../../src/mmedia\sndaiff.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndbase.obj :  .AUTODEPEND ../../src/mmedia\sndbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndcodec.obj :  .AUTODEPEND ../../src/mmedia\sndcodec.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndcpcm.obj :  .AUTODEPEND ../../src/mmedia\sndcpcm.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndfile.obj :  .AUTODEPEND ../../src/mmedia\sndfile.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndg72x.obj :  .AUTODEPEND ../../src/mmedia\sndg72x.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndmsad.obj :  .AUTODEPEND ../../src/mmedia\sndmsad.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndpcm.obj :  .AUTODEPEND ../../src/mmedia\sndpcm.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndulaw.obj :  .AUTODEPEND ../../src/mmedia\sndulaw.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndwav.obj :  .AUTODEPEND ../../src/mmedia\sndwav.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_sndwin.obj :  .AUTODEPEND ../../src/mmedia\sndwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_vidbase.obj :  .AUTODEPEND ../../src/mmedia\vidbase.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

$(OBJS)\mmedialib_vidwin.obj :  .AUTODEPEND ../../src/mmedia\vidwin.cpp
	$(CXX) -zq -fo=$^@ $(MMEDIALIB_CXXFLAGS) $<

clean : .SYMBOLIC 
	-if exist $(OBJS)\*.obj del $(OBJS)\*.obj
	-if exist $(OBJS)\*.res del $(OBJS)\*.res
	-if exist $(OBJS)\*.lbc del $(OBJS)\*.lbc
	-if exist $(OBJS)\*.ilk del $(OBJS)\*.ilk
	-if exist $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)250$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia_wat$(VENDORTAG).dll del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)250$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia_wat$(VENDORTAG).dll
	-if exist $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib
	-if exist $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib del $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib

!ifeq SHARED 1
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)250$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia_wat$(VENDORTAG).dll :  $(MMEDIADLL_OBJECTS)
	@%create $(OBJS)\mmediadll.lbc
	@%append $(OBJS)\mmediadll.lbc option quiet
	@%append $(OBJS)\mmediadll.lbc name $^@
	@%append $(OBJS)\mmediadll.lbc option incremental
	@%append $(OBJS)\mmediadll.lbc $(LDFLAGS) $(__DEBUGINFO_1)  libpath $(LIBDIRNAME)
	@for %i in ($(MMEDIADLL_OBJECTS)) do @%append $(OBJS)\mmediadll.lbc file %i
	@for %i in ( $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib  kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib odbc32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib  $(__WXLIB_CORE_p) $(__WXLIB_BASE_p)) do @%append $(OBJS)\mmediadll.lbc library %i
	@%append $(OBJS)\mmediadll.lbc
	@%append $(OBJS)\mmediadll.lbc system nt_dll
	wlink @$(OBJS)\mmediadll.lbc
	wlib -q -n -b $(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib +$^@
!endif

!ifeq SHARED 0
$(LIBDIRNAME)\wx$(PORTNAME)$(WXUNIVNAME)25$(WXUNICODEFLAG)$(WXDEBUGFLAG)_mmedia.lib :  $(MMEDIALIB_OBJECTS)
	@%create $(OBJS)\mmedialib.lbc
	@for %i in ($(MMEDIALIB_OBJECTS)) do @%append $(OBJS)\mmedialib.lbc +%i
	wlib -q -p2048 -n -b $^@ @$(OBJS)\mmedialib.lbc
!endif
