#!#############################################################################
#! File:    bcc.t
#! Purpose: tmake template file from which makefile.bcc is generated by running
#!          tmake -t bcc wxwin.pro -o makefile.bcc
#! Author:  Vadim Zeitlin
#! Created: 14.07.99
#! Version: $Id$
#!#############################################################################

#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric and %wxMSW hashes.
    IncludeTemplate("filelist.t");

    #! now transform these hashes into $project tags
    foreach $file (sort keys %wxGeneric) {
        my $tag = "";
        next if $wxGeneric{$file} =~ /\b(PS|G|U)\b/;

        $file =~ s/cp?p?$/obj/;
        $project{"WXGENERICOBJS"} .= "\$(MSWDIR)\\" . $file . " "
    }

    foreach $file (sort keys %wxCommon) {
        #! socket files don't compile under Win16 currently
        next if $wxCommon{$file} =~ /\b(32|S)\b/;

        #! needs extra files (sql*.h) so not compiled by default.
        next if $file =~ /^odbc\./;

        $isCFile = $file =~ /\.c$/;
        $file =~ s/cp?p?$/obj/;
        $obj = "\$(MSWDIR)\\" . $file . " ";
        $project{"WXCOMMONOBJS"} .= $obj;
        $project{"WXCOBJS"} .= $obj if $isCFile;
    }

    #! special hack for Borland in 16 bits needs this file
    $project{"WXCOMMONOBJS"} .= '${MSWDIR}\resourc2.cpp';

    foreach $file (sort keys %wxMSW) {
        #! don't take files not appropriate for 16-bit Windows
        next if $wxMSW{$file} =~ /\b(32|O)\b/;

        $isCFile = $file =~ /\.c$/;
        $file =~ s/cp?p?$/obj/;
        $obj = "\$(MSWDIR)\\" . $file . " ";
        $project{"WXMSWOBJS"} .= $obj;
        $project{"WXCOBJS"} .= $obj if $isCFile;
    }
#$}

# This file was automatically generated by tmake at #$ Now()
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE BCC.T!

#
# File:     makefile.bcc
# Author:   Julian Smart
# Created:  1993
# Updated:
# Copyright:(c) 1993, AIAI, University of Edinburgh
#
# "%W% %G%"
#
# Makefile : Builds wxWindows library wx.lib for Windows 3.1
# and Borland C++ 3.1

!if "$(BCCDIR)" == ""
!error You must define the BCCDIR variable in autoexec.bat, e.g. BCCDIR=d:\bc4
!endif

!if "$(WXWIN)" == ""
!error You must define the WXWIN variable in autoexec.bat, e.g. WXWIN=c:\wx
!endif

!if "$(CFG)" == ""
# !error You must start compiling from wx\src, not wx\src\msw.
!endif

!ifndef DEBUG
DEBUG=0
!endif

WXDIR = $(WXWIN)

!include $(WXDIR)\src\makebcc.env

THISDIR = $(WXDIR)\src\msw

# Please set these according to the settings in wx_setup.h, so we can include
# the appropriate libraries in wx.lib
USE_CTL3D=1
USE_XPM_IN_MSW=0

PERIPH_LIBS=
PERIPH_TARGET=
PERIPH_CLEAN_TARGET=

!if "$(USE_CTL3D)" == "1"
PERIPH_LIBS=$(BCCDIR)\lib\ctl3dv2.lib $(PERIPH_LIBS)
!endif

!if "$(USE_XPM_IN_MSW)" == "1"
PERIPH_LIBS=$(WXDIR)\xpm.lib $(PERIPH_LIBS)
PERIPH_TARGET=xpm $(PERIPH_TARGET)
PERIPH_CLEAN_TARGET=clean_xpm $(PERIPH_CLEAN_TARGET)
!endif

# TODO: add these libraries
# PERIPH_LIBS=$(WXDIR)\lib\zlib.lib $(WXDIR)\lib\winpng.lib $(PERIPH_LIBS)
PERIPH_TARGET=zlib png $(PERIPH_TARGET)
PERIPH_CLEAN_TARGET=clean_zlib clean_png $(PERIPH_CLEAN_TARGET)

CPPFLAGS=$(DEBUG_FLAGS) $(OPT) @$(CFG)

LIBTARGET= $(WXLIBDIR)\wx.lib
DUMMY=dummy

GENDIR=..\generic
COMMDIR=..\common
OLEDIR=.\ole
MSWDIR=.

DOCDIR = $(WXDIR)\docs

GENERICOBJS= #$ ExpandList("WXGENERICOBJS");

COMMONOBJS = \
		$(MSWDIR)\y_tab.obj \
		#$ ExpandList("WXCOMMONOBJS");

MSWOBJS = #$ ExpandList("WXMSWOBJS");

OBJECTS = $(COMMONOBJS) $(GENERICOBJS) $(MSWOBJS)

default:	wx

wx:    $(CFG) $(DUMMY).obj $(OBJECTS) $(PERIPH_TARGET) $(LIBTARGET)

$(LIBTARGET): $(DUMMY).obj $(OBJECTS) $(PERIPH_LIBS)
	erase $(LIBTARGET)
	tlib $(LIBTARGET) /P1024 @&&!
+$(OBJECTS:.obj =.obj +) +$(PERIPH_LIBS:.lib =.lib +)
!

dummy.obj: dummy.$(SRCSUFF) $(LOCALHEADERS) $(BASEHEADERS) $(WXDIR)\include\wx\wx.h
dummydll.obj: dummydll.$(SRCSUFF) $(LOCALHEADERS) $(BASEHEADERS) $(WXDIR)\include\wx\wx.h

$(MSWDIR)\y_tab.obj:     $(COMMDIR)\y_tab.c $(COMMDIR)\lex_yy.c

#        cl @<<
# $(CPPFLAGS2) /c $*.c -DUSE_DEFINE -DYY_USE_PROTOS /Fo$@
# <<

$(COMMDIR)\y_tab.c:     $(COMMDIR)\dosyacc.c
        copy $(COMMDIR)\dosyacc.c $(COMMDIR)\y_tab.c

$(COMMDIR)\lex_yy.c:    $(COMMDIR)\doslex.c
    copy $(COMMDIR)\doslex.c $(COMMDIR)\lex_yy.c

# $(OBJECTS):	$(WXDIR)\include\wx\setup.h

#${
    $_ = $project{"WXMSWOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        $suffix = $project{"WXCOBJS"} =~ /\Q$_/ ? "c" : '$(SRCSUFF)';
        s/obj/$suffix/;
        $text .= $_ . "\n\n";
    }
#$}

########################################################
# Common objects (always compiled)

#${
    $_ = $project{"WXCOMMONOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        $suffix = $project{"WXCOBJS"} =~ /\Q$_/ ? "c" : '$(SRCSUFF)';
        s/MSWDIR/COMMDIR/;
        s/obj/$suffix/;
        $text .= $_ . "\n\n";
    }
#$}

########################################################
# Generic objects (not always compiled, depending on
# whether platforms have native implementations)

#${
    $_ = $project{"WXGENERICOBJS"};
    my @objs = split;
    foreach (@objs) {
        $text .= $_ . ": ";
        s/MSWDIR/GENDIR/;
        s/obj/\$(SRCSUFF)/;
        $text .= $_ . "\n\n";
    }
#$}

all_utils:
    cd $(WXDIR)\utils
    make -f makefile.bcc
    cd $(WXDIR)\src\msw

all_samples:
    cd $(WXDIR)\samples
    make -f makefile.bcc
    cd $(WXDIR)\src\msw

all_execs:
    cd $(WXDIR)\utils
    make -f makefile.bcc all_execs
    cd $(WXDIR)\src\msw

all_libs:
    cd $(WXDIR)\src\msw
    make -f makefile.bcc ctl3d dib fafa gauge hytext itsy prologio rcparser wx wxgraph\
          wxstring wxtree mfutils # wxxpm

all_contribs:
    cd $(WXDIR)\src\msw
    make -f makefile.bcc ctl3d fafa wxstring itsy gauge # wxxpm

# CONTRIB
ctl3d:  $(CFG)
        cd $(WXDIR)\src\msw\ctl3d\borland
        make -f makefile.bcc -DCFG=$(CFG)
        cd $(WXDIR)\src\msw

wxxpm:	$(CFG)
	cd $(WXDIR)\src\xpm
	make -f makefile.bcc -DCFG=$(CFG) -DFINAL=$(FINAL) -DWXWIN=$(WXDIR) -DDEBUG=$(DEBUG)
	cd $(WXDIR)\src\msw

png:    $(CFG)
        cd $(WXDIR)\src\png
        make -f makefile.bcc
        cd $(WXDIR)\src\msw

clean_png:
        cd $(WXDIR)\src\png
        make -f makefile.bcc clean
        cd $(WXDIR)\src\msw

zlib:   $(CFG)
        cd $(WXDIR)\src\zlib
        make -f makefile.bcc
        cd $(WXDIR)\src\msw

clean_zlib:
        cd $(WXDIR)\src\zlib
        make -f makefile.bcc clean
        cd $(WXDIR)\src\msw

$(CFG): makefile.bcc
	copy &&!
-H=$(WXDIR)\src\msw\borland.pch
-2
-P
-d
-w-hid
-w-par
-w-pia
-w-aus
-w-rch
-ml
-Od
-WE
-Fs-
-Vf
-Ff=4
-I$(WXINC);$(BCCDIR)\include;$(WXDIR)/src/png;$(WXDIR)/src/zlib;$(WXDIR)/src/xpm
-I$(WXDIR)\include\wx\msw\gnuwin32
-L$(BCCDIR)\lib
-D__WXWIN__
-D__WXMSW__
-D__WINDOWS__
-D__WIN16__
! $(CFG)
!if "$(BOR_VER)" == "3.1"
	echo -Ff=4 >>$(CFG)
!elif "$(BOR_VER)" == "4"
	echo -Ff=512 >>$(CFG)
	echo -dc >>$(CFG)
!else
	echo -Ff=512 >>$(CFG)
	echo -dc >>$(CFG)
!endif

# -O was: -Oxt

clean: $(PERIPH_CLEAN_TARGET)
    erase $(LIBTARGET)
    erase *.obj
    erase *.pch
    erase *.csm
    erase *.cfg
	erase ..\common\y_tab.c
    erase ..\common\lex_yy.c

cleanall: clean


MFTYPE=bcc
# Can't use this or we'll have to distribute all tmake files with wxWindows
#makefile.$(MFTYPE) : $(WXWIN)\distrib\msw\tmake\filelist.txt $(WXWIN)\distrib\msw\tmake\$(MFTYPE).t

self:
	cd $(WXWIN)\distrib\msw\tmake
	tmake -t $(MFTYPE) wxwin.pro -o makefile.$(MFTYPE)
	copy makefile.$(MFTYPE) $(WXWIN)\src\msw
