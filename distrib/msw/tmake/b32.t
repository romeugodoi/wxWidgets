#!#############################################################################
#! File:    b32.t
#! Purpose: tmake template file from which makefile.b32 is generated by running
#!          tmake -t b32 wxwin.pro
#! Author:  Vadim Zeitlin
#! Created: 14.07.99
#! Version: $Id$
#!#############################################################################

#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric and %wxMSW hashes.
    IncludeTemplate("filelist.t");

    #! now transform these hashes into $project tags
    foreach $file (sort keys %wxUNIV) {
        next if $wxUNIV{$file} =~ /\T\b/;

        $file =~ s/cp?p?$/obj/;
        $obj = "\$(UNIVDIR)\\" . $file . " ";
        $project{"WXUNIVOBJS"} .= "\$(OBJ_PATH)\\" . $file . " "
    }

    foreach $file (sort keys %wxUNIV) {
        next unless $wxUNIV{$file} =~ /\T\b/;

        $file =~ s/cp?p?$/obj/;
        $obj = "\$(UNIVTHEMEDIR)\\" . $file . " ";
        $project{"WXUNIVTHEMEOBJS"} .= "\$(OBJ_PATH)\\" . $file . " "
    }

    foreach $file (sort keys %wxHTML) {
        next if $wxHTML{$file} =~ /\b16\b/;

        $file =~ s/cp?p?$/obj/;
        $project{"WXHTMLOBJS"} .= "\$(OBJ_PATH)\\" . $file . " "
    }

    foreach $file (sort keys %wxCommon) {
        next if $wxCommon{$file} =~ /\b(16|U)\b/;

        $isCFile = $file =~ /\.c$/;
        $file =~ s/cp?p?$/obj/;
        $obj = "\$(OBJ_PATH)\\" . $file . " ";
        $project{"WXCOMMONOBJS"} .= $obj;
        $project{"WXCOBJS"} .= $obj if $isCFile;
    }

#! MSW dir for native port
    foreach $file (sort keys %wxMSW) {
        next if $wxMSW{$file} =~ /\b16\b/;

        $isCFile = $file =~ /\.c$/;

        my $isOleObj = $wxMSW{$file} =~ /\bO\b/;
        $file =~ s/cp?p?$/obj/;
        my $obj = "\$(OBJ_PATH)\\" . $file . " ";

        $project{"WXMSWOBJS"} .= $obj;
        if ( $isOleObj ) {
            #! remember that this file is in ole subdir
            $project{"WXOLEOBJS"} .= $obj;
        }
        $project{"WXCOBJS"} .= $obj if $isCFile;
    }

#! Now do MSW dir for UNIV
    foreach $file (sort keys %wxMSW) {
        next unless $wxMSW{$file} =~ /\b(L|B)\b/;

        $isCFile = $file =~ /\.c$/;

        my $isOleObj = $wxMSW{$file} =~ /\bO\b/;
        $file =~ s/cp?p?$/obj/;
        my $obj = "\$(OBJ_PATH)\\" . $file . " ";

        $project{"WXMSWUNIVOBJS"} .= $obj;
        if ( $isOleObj ) {
            #! remember that this file is in ole subdir
            $project{"WXOLEUNIVOBJS"} .= $obj;
        }
        $project{"WXCUNIVOBJS"} .= $obj if $isCFile;
    }

#! Generic Dir for Native Port
    foreach $file (sort keys %wxGeneric) {
        my $tag = "";
        next if $wxGeneric{$file} =~ /\b(PS|G|16|U)\b/;

        $file =~ s/cp?p?$/obj/;
        $project{"WXGENERICOBJS"} .= "\$(OBJ_PATH)\\" . $file . " "
    }

#! Generic Dir for UNIV Port
    foreach $file (sort keys %wxGeneric) {
	my $filereal = $file;
	if ( $file =~ /^([^.]+)g.cpp$/ ) {
	    $filereal = "$1.cpp";
	}
        $file =~ s/cp?p?$/obj/;
        $filereal =~ s/cp?p?$/obj/;

	next if $project{"WXMSWUNIVOBJS"} =~ /\b$filereal\b/ ||
		$project{"WXUNIVOBJS"} =~ /\b$filereal\b/;

        
        $project{"WXGENERICUNIVOBJS"} .= "\$(OBJ_PATH)\\" . $file . " "
    }

#$}

# This file was automatically generated by tmake
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE B32.T!

#
# File:     makefile.b32
# Author:   Julian Smart
# Created:  1998
# Updated:
# Copyright:
#
# "%W% %G%"
#
# Makefile : Builds wxWindows library wx.lib for MS Windows,
# and Borland C++ (32-bit).

# BCCDIR now defined in ../makeb32.env

!if "$(WXWIN)" == ""
!error You must define the WXWIN variable in autoexec.bat, e.g. WXWIN=c:\wx
!endif

WXDIR = $(WXWIN)
THISDIR = $(WXDIR)\src\msw


# Set all these to 1 if you want to build a dynamic library
!if "$(DLL)" == "1"
WXMAKINGDLL=1
WXBUILDDLL=1
!endif

!include $(WXDIR)\src\makeb32.env

# Please set these according to the settings in wx_setup.h, so we can include
# the appropriate libraries in wx.lib
USE_CTL3D=0

PERIPH_LIBS=
PERIPH_TARGET=
PERIPH_CLEAN_TARGET=

!if "$(USE_CTL3D)" == "1"
#Use WIN32S/WIN95 32 bit version ctl3d32.dll under win95 (Andre Beltman)
PERIPH_LIBS=$(WXDIR)\lib\ctl3d32.lib $(PERIPH_LIBS)
PERIPH_TARGET=ctl3d $(PERIPH_TARGET)
PERIPH_CLEAN_TARGET=clean_ctl3d $(PERIPH_CLEAN_TARGET)
!endif

PERIPH_LIBS=
PERIPH_TARGET=zlib png jpeg tiff regex $(PERIPH_TARGET)
PERIPH_CLEAN_TARGET=clean_zlib clean_png clean_jpeg clean_tiff clean_regex $(PERIPH_CLEAN_TARGET)

!if "$(DLL)" == "0"
DUMMY=dummy
!else
DUMMY=dummydll
LIBS= cw32mti import32 ole2w32 odbc32 zlib_bc$(DEBUG_SUFFIX) png_bc$(DEBUG_SUFFIX) jpeg_bc$(DEBUG_SUFFIX) tiff_bc$(DEBUG_SUFFIX) regex_bc$(DEBUG_SUFFIX)
!endif

LIBTARGET=$(WXLIB)

GENDIR=..\generic
COMMDIR=..\common
HTMLDIR=..\html
OLEDIR=.\ole
UNIVDIR=..\univ
UNIVTHEMEDIR=..\univ\themes
MSWDIR=.

DOCDIR = $(WXDIR)\docs

GENERICOBJS= #$ ExpandList("WXGENERICOBJS");

MSWOBJS = #$ ExpandList("WXMSWOBJS");

GENERICUNIVOBJS= #$ ExpandList("WXGENERICUNIVOBJS");

MSWUNIVOBJS = #$ ExpandList("WXMSWUNIVOBJS");

UNIVOBJS = #$ ExpandList("WXUNIVOBJS");

UNIVTHEMEOBJS = #$ ExpandList("WXUNIVTHEMEOBJS");

HTMLOBJS = #$ ExpandList("WXHTMLOBJS");

COMMONOBJS = \
        #$ ExpandList("WXCOMMONOBJS");

!if "$(WXUSINGUNIV)" == "1"
OBJECTS = $(COMMONOBJS) $(GENERICUNIVOBJS) $(MSWUNIVOBJS) $(HTMLOBJS) $(UNIVOBJS) $(UNIVTHEMEOBJS)
!else
OBJECTS = $(COMMONOBJS) $(GENERICOBJS) $(MSWOBJS) $(HTMLOBJS)
!endif

default:    wx

wx:    $(ARCHINCDIR)\wx makeoutdir makesetuph makearchsetuph $(CFG) $(DUMMY).obj $(OBJECTS) $(PERIPH_TARGET) $(LIBTARGET)

all:    wx

# Copy the in-CVS setup0.h to setup.h if necessary
makesetuph:
     cd $(WXDIR)\include\wx\msw
     if not exist setup.h copy setup0.h setup.h
     cd $(WXDIR)\src\msw

# Copy include\wx\msw\setup.h to the architecture-specific location
makearchsetuph:
     copy $(SETUPSRCDIR)\setup.h $(ARCHSETUPH)
     cd $(WXDIR)\src\msw

makeoutdir:
    -mkdir $(OBJ_PATH)

$(ARCHINCDIR)\wx:
    -mkdir $(ARCHINCDIR)
    -mkdir $(ARCHINCDIR)\wx
    -if exist $(CFG) $(RM) $(CFG)

!if "$(DLL)" == "0"

$(LIBTARGET): $(DUMMY).obj $(OBJECTS)
    -if exist $(LIBTARGET) $(RM) $(LIBTARGET)
    tlib "$(LIBTARGET)" /P1024 $(LINKDEBUGFLAGS) @&&!
+$(OBJECTS:.obj =.obj +) +$(PERIPH_LIBS:.lib =.lib +)
!

!else

$(LIBTARGET): $(DUMMY).obj $(OBJECTS)
    -$(RM) $(LIBTARGET)
    -$(RM) $(WXDLL)
        $(LINK) $(LINK_FLAGS) $(LINKDEBUGFLAGS) /L$(WXLIBDIR);$(BCCDIR)\lib;$(BCCDIR)\lib\psdk @&&!
c0d32.obj $(OBJECTS)
$(WXDLL)
nul
$(PERIPH_LIBS) $(LIBS)
wxb32
!
        implib -c -f $(LIBTARGET) $(WXDLL)
!endif

dummy.obj: dummy.$(SRCSUFF) $(LOCALHEADERS) $(BASEHEADERS) $(WXDIR)\include\wx\wx.h
dummydll.obj: dummydll.$(SRCSUFF) $(LOCALHEADERS) $(BASEHEADERS) $(WXDIR)\include\wx\wx.h version.res

version.res:
    brc32 -r -i$(WXDIR)\include\ $(MSWDIR)\version.rc

# $(OBJECTS):   $(WXDIR)\include\wx\setup.h

!if "$(WXUSINGUNIV)" == "1"
########################################################
# MSW objects (compile Native or UNIV) - UNIV

#${
    $_ = $project{"WXMSWUNIVOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";        
        if ( $project{"WXOLEOBJS"} =~ /\Q$_/ ) { s/OBJ_PATH/OLEDIR/; }
        $suffix = $project{"WXCUNIVOBJS"} =~ /\Q$_/ ? "c" : '$(SRCSUFF)';
        s/obj$/$suffix/;
	s/OBJ_PATH/MSWDIR/;
        $text .= $_ . "\n\n";
    }
#$}


!else
########################################################
# MSW objects (compile Native or UNIV) - Native

#${
    $_ = $project{"WXMSWOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";	
        if ( $project{"WXOLEOBJS"} =~ /\Q$_/ ) { s/OBJ_PATH/OLEDIR/; }
        $suffix = $project{"WXCOBJS"} =~ /\Q$_/ ? "c" : '$(SRCSUFF)';
        s/obj$/$suffix/;
 	s/OBJ_PATH/MSWDIR/;
        $text .= $_ . "\n\n";
    }
#$}
!endif

!if "$(WXUSINGUNIV)" == "1"
########################################################
# UNIV objects 
#${
    $_ = $project{"WXUNIVOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/OBJ_PATH/UNIVDIR/;
        s/obj$/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}


########################################################
# UNIV THEME objects 

#${
    $_ = $project{"WXUNIVTHEMEOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/OBJ_PATH/UNIVTHEMEDIR/;
        s/obj$/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}

!endif

########################################################
# Common objects (always compiled)

#${
    $_ = $project{"WXCOMMONOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        $suffix = $project{"WXCOBJS"} =~ /\Q$_/ ? "c" : '$(SRCSUFF)';
        s/OBJ_PATH/COMMDIR/;
        s/obj$/$suffix/;
        $text .= $_ . "\n\n";
    }
#$}

!if "$(WXUSINGUNIV)" == "1"
########################################################
# Generic objects (not always compiled, depending on
# whether platforms have native implementations)
# Native


#${
    $_ = $project{"WXGENERICUNIVOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/OBJ_PATH/GENDIR/;
        s/obj$/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}

!else
########################################################
# Generic objects (not always compiled, depending on
# whether platforms have native implementations)
# Native

#${
    $_ = $project{"WXGENERICOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/OBJ_PATH/GENDIR/;
        s/obj$/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}
!endif

########################################################
# HTML objects (always compiled)

#${
    $_ = $project{"WXHTMLOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/OBJ_PATH/HTMLDIR/;
        s/obj$/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}


all_utils:
    cd $(WXDIR)\utils
    ${MAKE} -f makefile.b32
    cd $(WXDIR)\src\msw

all_samples:
    cd $(WXDIR)\samples
    ${MAKE} -f makefile.b32
    cd $(WXDIR)\src\msw

all_execs:
    cd $(WXDIR)\utils
    ${MAKE} -f makefile.b32 all_execs
    cd $(WXDIR)\src\msw

png:    $(CFG)
        cd $(WXDIR)\src\png
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) lib
        cd $(WXDIR)\src\msw

clean_png:
        cd $(WXDIR)\src\png
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) clean
        cd $(WXDIR)\src\msw

zlib:   $(CFG)
        cd $(WXDIR)\src\zlib
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) lib
        cd $(WXDIR)\src\msw

clean_zlib:
        cd $(WXDIR)\src\zlib
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) clean
        cd $(WXDIR)\src\msw

jpeg:    $(CFG)
        cd $(WXDIR)\src\jpeg
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) lib
        cd $(WXDIR)\src\msw

clean_jpeg:
        cd $(WXDIR)\src\jpeg
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) clean
        cd $(WXDIR)\src\msw

regex:   $(CFG)
        cd $(WXDIR)\src\regex
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) lib
        cd $(WXDIR)\src\msw

clean_regex:
        cd $(WXDIR)\src\regex
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) clean
        cd $(WXDIR)\src\msw

tiff:   $(CFG)
        cd $(WXDIR)\src\tiff
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) lib
        cd $(WXDIR)\src\msw

clean_tiff:
        cd $(WXDIR)\src\tiff
        ${MAKE} -f makefile.b32 $(MAKEFLAGS) clean
        cd $(WXDIR)\src\msw

$(CFG): makefile.b32
    copy &&!
-Hc
-H=$(OBJ_PATH)\wx32.csm
-3
-d
-a1 # byte alignment
-R-
-X
-w-par
-w-aus
-w-hid # virtual function A hides virtual function B
-tWM

-I$(ARCHINCDIR);$(WXINC);$(BCCDIR)\include;$(WXDIR)/src/generic;$(WXDIR)/src/png;$(WXDIR)/src/jpeg;$(WXDIR)/src/zlib;$(WXDIR)/src/tiff
-I$(WXDIR)\include\wx\msw\gnuwin32

-L$(BCCDIR)\lib;$(BCCDIR)\lib\psdk
-D__WXWIN__
-D$(PORT)
-D__WINDOWS__
-DWIN32
$(OPT)
$(DEBUG_FLAGS)
$(WIN95FLAG)
! $(CFG)

cleancfg:
    -if exist $(OBJ_PATH)\*.cfg $(RM) $(OBJ_PATH)\*.cfg    

clean: $(PERIPH_CLEAN_TARGET)
    -if exist $(WXLIBDIR)\wx.il? $(RM) $(WXLIBDIR)\wx.tds
    -if exist $(WXLIBDIR)\wx.il? $(RM) $(WXLIBDIR)\wx.il?
    -if exist $(OBJ_PATH)\*.obj $(RM) $(OBJ_PATH)\*.obj    
    -if exist $(OBJ_PATH)\*.csm $(RM) $(OBJ_PATH)\*.csm    
    -if exist "$(OBJ_PATH)\wx32.#??" $(RM) "$(OBJ_PATH)\wx32.#??"
    -if exist *.pch $(RM) *.pch
    -if exist *.csm $(RM) *.csm
    -if exist *.obj $(RM) *.obj
    -if exist "wx32.#??" $(RM) "wx32.#??"

cleanall: clean cleancfg


# Making documents
docs:   allhlp allhtml allpdfrtf
alldocs: docs
hlp:    wxhlp portinghlp
wxhlp:  $(DOCDIR)/winhelp/wx.hlp
refhlp: $(DOCDIR)/winhelp/techref.hlp
rtf:    $(DOCDIR)/winhelp/wx.rtf
pdfrtf:    $(DOCDIR)/pdf/wx.rtf
refpdfrtf: $(DOCDIR)/pdf/techref.rtf
html:   wxhtml portinghtml
wxhtml: $(DOCDIR)\html\wx\wx.htm
htmlhelp: $(DOCDIR)\html\wx\wx.chm
ps:     wxps referencps
wxps:   $(WXDIR)\docs\ps\wx.ps
referencps: $(WXDIR)\docs\ps\referenc.ps

portinghtml: $(DOCDIR)\html\porting\port.htm
portingrtf: $(DOCDIR)/winhelp/porting.rtf
portinghlp: $(DOCDIR)/winhelp/porting.hlp
portingpdfrtf: $(DOCDIR)/pdf/porting.rtf
portingps:  $(WXDIR)\docs\ps\porting.ps

allhlp: wxhlp portinghlp
        cd $(WXDIR)\utils\dialoged\src
        ${MAKE} -f makefile.b32 hlp
        cd $(THISDIR)

#        cd $(WXDIR)\utils\wxhelp\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\tex2rtf\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\wxgraph\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\wxchart\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\wxtree\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\wxbuild\src
#        ${MAKE} -f makefile.b32 hlp
#        cd $(WXDIR)\utils\wxgrid\src
#        ${MAKE} -f makefile.b32 hlp

allhtml: wxhtml portinghtml
        cd $(WXDIR)\utils\dialoged\src
        ${MAKE} -f makefile.b32 html
        cd $(THISDIR)

#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\dialoged\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\hytext\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\wxhelp\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\tex2rtf\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\wxgraph\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\wxchart\src
#        ${MAKE} -f makefile.b32 html
#        cd $(WXDIR)\utils\wxtree\src
#        ${MAKE} -f makefile.b32 html

allps: wxps referencps portingps
        cd $(WXDIR)\utils\dialoged\src
        ${MAKE} -f makefile.b32 ps
        cd $(THISDIR)

allpdfrtf: pdfrtf portingpdfrtf
        cd $(WXDIR)\utils\dialoged\src
        ${MAKE} -f makefile.b32 pdfrtf
        cd $(THISDIR)

#        cd $(WXDIR)\utils\wxhelp\src
#        ${MAKE} -f makefile.b32 ps
#        cd $(WXDIR)\utils\tex2rtf\src
#        ${MAKE} -f makefile.b32 ps
#        cd $(WXDIR)\utils\wxgraph\src
#        ${MAKE} -f makefile.b32 ps
#        cd $(WXDIR)\utils\wxchart\src
#        ${MAKE} -f makefile.b32 ps
#        cd $(WXDIR)\utils\wxtree\src
#        ${MAKE} -f makefile.b32 ps
#        cd $(THISDIR)

$(DOCDIR)/winhelp/wx.hlp:         $(DOCDIR)/latex/wx/wx.rtf $(DOCDIR)/latex/wx/wx.hpj
        cd $(DOCDIR)/latex/wx
        -if exist wx.ph $(RM)  wx.ph
        hc wx
        move wx.hlp $(DOCDIR)\winhelp\wx.hlp
        move wx.cnt $(DOCDIR)\winhelp\wx.cnt
        cd $(THISDIR)

$(DOCDIR)/winhelp/porting.hlp:         $(DOCDIR)/latex/porting/porting.rtf $(DOCDIR)/latex/porting/porting.hpj
        cd $(DOCDIR)/latex/porting
        -if exist porting.ph $(RM)  porting.ph
        hc porting
        move porting.hlp $(DOCDIR)\winhelp\porting.hlp
        move porting.cnt $(DOCDIR)\winhelp\porting.cnt
        cd $(THISDIR)

$(DOCDIR)/winhelp/techref.hlp:         $(DOCDIR)/latex/techref/techref.rtf $(DOCDIR)/latex/techref/techref.hpj
        cd $(DOCDIR)/latex/techref
        -if exist techref.ph $(RM)  techref.ph
        hc techref
        move techref.hlp $(DOCDIR)\winhelp\techref.hlp
        move techref.cnt $(DOCDIR)\winhelp\techref.cnt
        cd $(THISDIR)

$(DOCDIR)/latex/wx/wx.rtf:         $(DOCDIR)/latex/wx/classes.tex $(DOCDIR)/latex/wx/body.tex $(DOCDIR)/latex/wx/topics.tex $(DOCDIR)/latex/wx/manual.tex
        cd $(DOCDIR)\latex\wx
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/wx/manual.tex $(DOCDIR)/latex/wx/wx.rtf -twice -winhelp
        cd $(THISDIR)

$(DOCDIR)/latex/porting/porting.rtf:         $(DOCDIR)/latex/porting/porting.tex
        cd $(DOCDIR)\latex\porting
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/porting/porting.tex $(DOCDIR)/latex/porting/porting.rtf -twice -winhelp
        cd $(THISDIR)

$(DOCDIR)/latex/techref/techref.rtf:         $(DOCDIR)/latex/techref/techref.tex
        cd $(DOCDIR)\latex\techref
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/techref/techref.tex $(DOCDIR)/latex/techref/techref.rtf -twice -winhelp
        cd $(THISDIR)

$(DOCDIR)/pdf/wx.rtf:         $(DOCDIR)/latex/wx/classes.tex $(DOCDIR)/latex/wx/body.tex $(DOCDIR)/latex/wx/topics.tex $(DOCDIR)/latex/wx/manual.tex
        cd $(DOCDIR)\latex\wx
        -copy *.wmf $(DOCDIR)\pdf
        -copy *.bmp $(DOCDIR)\pdf
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/wx/manual.tex $(DOCDIR)/pdf/wx.rtf -twice -rtf
        cd $(THISDIR)

$(DOCDIR)/pdf/porting.rtf:         $(DOCDIR)/latex/porting/porting.tex
        cd $(DOCDIR)\latex\porting
        -copy *.wmf $(DOCDIR)\pdf
        -copy *.bmp $(DOCDIR)\pdf
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/porting/porting.tex $(DOCDIR)/pdf/porting.rtf -twice -rtf
        cd $(THISDIR)

$(DOCDIR)/pdf/techref.rtf:         $(DOCDIR)/latex/techref/techref.tex
        cd $(DOCDIR)\latex\techref
        -copy *.wmf $(DOCDIR)\pdf
        -copy *.bmp $(DOCDIR)\pdf
        -start $(WAITFLAG) tex2rtf $(DOCDIR)/latex/techref/techref.tex $(DOCDIR)/pdf/techref.rtf -twice -rtf
        cd $(THISDIR)

$(DOCDIR)\html\wx\wx.htm:         $(DOCDIR)\latex\wx\classes.tex $(DOCDIR)\latex\wx\body.tex $(DOCDIR)/latex/wx/topics.tex $(DOCDIR)\latex\wx\manual.tex
        cd $(DOCDIR)\latex\wx
        -mkdir $(DOCDIR)\html\wx
        -start $(WAITFLAG) tex2rtf $(DOCDIR)\latex\wx\manual.tex $(DOCDIR)\html\wx\wx.htm -twice -html
        -if exist $(DOCDIR)\html\wx\*.con $(RM)  $(DOCDIR)\html\wx\*.con
        -if exist $(DOCDIR)\html\wx\*.ref $(RM)  $(DOCDIR)\html\wx\*.ref
        -if exist $(DOCDIR)\latex\wx\*.con $(RM)  $(DOCDIR)\latex\wx\*.con
        -if exist $(DOCDIR)\latex\wx\*.ref $(RM)  $(DOCDIR)\latex\wx\*.ref
         cd $(THISDIR)

$(DOCDIR)\html\wx\wx.chm : $(DOCDIR)\html\wx\wx.htm $(DOCDIR)\html\wx\wx.hhp
    cd $(DOCDIR)\html\wx
    -hhc wx.hhp
    cd $(THISDIR)


$(DOCDIR)\html\porting\port.htm:         $(DOCDIR)\latex\porting\porting.tex
        cd $(DOCDIR)\latex\porting
        -mkdir $(DOCDIR)\html\porting
        -start $(WAITFLAG) tex2rtf $(DOCDIR)\latex\porting\porting.tex $(DOCDIR)\html\porting\port.htm -twice -html
        -if exist $(DOCDIR)\html\porting\*.con $(RM)  $(DOCDIR)\html\porting\*.con
        -if exist $(DOCDIR)\html\porting\*.ref $(RM)  $(DOCDIR)\html\porting\*.ref
        -if exist $(DOCDIR)\latex\porting\*.con $(RM)  $(DOCDIR)\latex\porting\*.con
        -if exist $(DOCDIR)\latex\porting\*.ref $(RM)  $(DOCDIR)\latex\porting\*.ref
        cd $(THISDIR)

$(WXDIR)\docs\latex\wx\manual.dvi:  $(DOCDIR)/latex/wx/body.tex $(DOCDIR)/latex/wx/manual.tex
    cd $(WXDIR)\docs\latex\wx
        -latex manual
        -latex manual
        -makeindx manual
        -bibtex manual
        -latex manual
        -latex manual
        cd $(THISDIR)

$(WXDIR)\docs\latex\porting\porting.dvi:    $(DOCDIR)/latex/porting/porting.tex
    cd $(WXDIR)\docs\latex\porting
        -latex porting
        -latex porting
        -makeindx porting
        -bibtex porting
        -latex porting
        -latex porting
        cd $(THISDIR)

$(WXDIR)\docs\ps\wx.ps: $(WXDIR)\docs\latex\wx\manual.dvi
    cd $(WXDIR)\docs\latex\wx
        -dvips32 -o wx.ps manual
        move wx.ps $(WXDIR)\docs\ps\wx.ps
        cd $(THISDIR)

$(WXDIR)\docs\ps\porting.ps:    $(WXDIR)\docs\latex\porting\porting.dvi
    cd $(WXDIR)\docs\latex\porting
        -dvips32 -o porting.ps porting
        move porting.ps $(WXDIR)\docs\ps\porting.ps
        cd $(THISDIR)

$(WXDIR)\docs\latex\wx\referenc.dvi:    $(DOCDIR)/latex/wx/classes.tex $(DOCDIR)/latex/wx/topics.tex $(DOCDIR)/latex/wx/referenc.tex
    cd $(WXDIR)\docs\latex\wx
        -latex referenc
        -latex referenc
        -makeindx referenc
        -bibtex referenc
        -latex referenc
        -latex referenc
        cd $(THISDIR)

$(WXDIR)\docs\ps\referenc.ps:   $(WXDIR)\docs\latex\wx\referenc.dvi
    cd $(WXDIR)\docs\latex\wx
        -dvips32 -o referenc.ps referenc
        move referenc.ps $(WXDIR)\docs\ps\referenc.ps
        cd $(THISDIR)

# In order to force document reprocessing
touchmanual:
    -touch $(WXDIR)\docs\latex\wx\manual.tex

updatedocs: touchmanual alldocs

# Start Word, running the GeneratePDF macro. MakeManual.dot should be in the
# Office StartUp folder, and PDFMaker should be installed.
updatepdf:  # touchmanual pdfrtf
    start $(WAITFLAG) "winword d:\wx2\wxWindows\docs\latex\pdf\wx.rtf /mGeneratePDF"


MFTYPE=b32
# Can't use this or we'll have to distribute all tmake files with wxWindows
# makefile.$(MFTYPE) : $(WXWIN)\distrib\msw\tmake\filelist.txt $(WXWIN)\distrib\msw\tmake\$(MFTYPE).t

self:
!if "$(TM)"=="" 
	@echo Error in Environment!
	@echo Please set TM in the environment to the directory containing tmake binaries
	@echo eg set TM=c:\wx\tmake\bin
!else
    cd $(WXWIN)\distrib\msw\tmake
    perl $(TM)\tmake -t $(MFTYPE) wxwin.pro -o makefile.$(MFTYPE)
    copy makefile.$(MFTYPE) $(WXWIN)\src\msw
!endif
