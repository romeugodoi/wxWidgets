#!################################################################################
#! File:    unx.t
#! Purpose: tmake template file from which Makefile.in is generated by running
#!          tmake -t unx wxwin.pro -o Makefile.in
#! Author:  Vadim Zeitlin, Robert Roebling, Julian Smart
#! Created: 14.07.99
#! Version: $Id$
#!################################################################################
#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric, %wxHtml, %wxUnix and %wxGTK hashes.
    IncludeTemplate("filelist.t");

    #! Generic
    
    foreach $file (sort keys %wxGeneric) {
        #! native wxDirDlg can't be compiled due to GnuWin32/OLE limitations,
        #! so take the generic version
        if ( $wxGeneric{$file} =~ /\b(PS|G|U|16)\b/ ) {
            next unless $file =~ /^dirdlgg\./;
        }

        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXMSW_GENERICOBJS"} .= $file . " ";
        $project{"WXMSW_GENERICDEPS"} .= $file2 . " "
    }

    foreach $file (sort keys %wxGeneric) {
        #! skip generic files not required for the wxGTK port
        next if $wxGeneric{$file} =~ /\bR\b/;

        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXGTK_GENERICOBJS"} .= $file . " ";
        $project{"WXGTK_GENERICDEPS"} .= $file2 . " "
    }

    foreach $file (sort keys %wxGeneric) {
        next if $wxGeneric{$file} =~ /\bX\b/;

        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXMOTIF_GENERICOBJS"} .= $file . " ";
        $project{"WXMOTIF_GENERICDEPS"} .= $file2 . " "
    }

    #! Common
    
    foreach $file (sort keys %wxCommon) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;
        ($filedep = $file) =~ s/cp?p?$/\d/;

        #! 'B' flag means that the file makes part of wxBase too
        if ( $wxCommon{$file} =~ /\bB\b/ ) {
            $project{"BASE_OBJS"} .= $fileobj . " ";
            $project{"BASE_DEPS"} .= $filedep . " ";
        }

        #! if it's the wxBase-only file, nothing more to do with it
        next if $wxCommon{$file} =~ /\bBO\b/;

        if ( $wxCommon{$file} !~ /\bR\b/ ) {    #! unless not for GTK
            $project{"WXGTK_COMMONOBJS"} .= $fileobj . " ";
            $project{"WXGTK_COMMONDEPS"} .= $filedep . " "
        }
        if ( $wxCommon{$file} !~ /\bX\b/ ) {    #! unless not for Motif
            $project{"WXMOTIF_COMMONOBJS"} .= $fileobj . " ";
            $project{"WXMOTIF_COMMONDEPS"} .= $filedep . " "
        }

        #! ODBC needs extra files (sql*.h) so not compiled by default.
        if ( (file !~ /^odbc\./) && ($wxCommon{$file} !~ /\b(16)\b/) ) {
            $project{"WXMSW_COMMONOBJS"} .= $fileobj . " ";
            $project{"WXMSW_COMMONDEPS"} .= $filedep . " "
        }
    }

    #! GUI
    
    foreach $file (sort keys %wxMSW) {
        #! Mingw32 doesn't have the OLE headers and has some troubles with
        #! socket code
        next if $wxMSW{$file} =~ /\b(O|16)\b/;

        #! native wxDirDlg can't be compiled due to GnuWin32/OLE limitations,
        next if $file =~ /^dirdlg\./;

        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXMSW_GUIOBJS"} .= $file . " ";
        $project{"WXMSW_GUIDEPS"} .= $file2 . " "
    }

    foreach $file (sort keys %wxGTK) {
        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXGTK_GUIOBJS"} .= $file . " ";
        $project{"WXGTK_GUIDEPS"} .= $file2 . " "
    }

    foreach $file (sort keys %wxMOTIF) {
        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXMOTIF_GUIOBJS"} .= $file . " ";
        $project{"WXMOTIF_GUIDEPS"} .= $file2 . " "
    }

    #! others
    
    foreach $file (sort keys %wxHTML) {
        $file2 = $file;
        $file =~ s/cp?p?$/\o/;
        $file2 =~ s/cp?p?$/\d/;
        $project{"WXHTMLOBJS"} .= $file . " ";
        $project{"WXHTMLDEPS"} .= $file2 . " "
    }

    foreach $file (sort keys %wxUNIX) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;
        ($filedep = $file) =~ s/cp?p?$/\d/;

        #! 'B' flag means that the file makes part of wxBase too
        if ( $wxUNIX{$file} =~ /\bB\b/ ) {
            $project{"BASE_OBJS"} .= $fileobj . " ";
            $project{"BASE_DEPS"} .= $filedep . " "
        }

        $project{"WXUNIX_OBJS"} .= $fileobj . " ";
        $project{"WXUNIX_DEPS"} .= $filedep . " "
    }
    
    #! headers
    
    foreach $file (sort keys %wxWXINCLUDE) {
        $project{"WX_HEADERS"} .= $file . " ";
        $project{"BASE_HEADERS"} .= $file . " " if $wxWXINCLUDE{$file} =~ /\bB\b/;
    }
    
    foreach $file (sort keys %wxGENERICINCLUDE) {
        $project{"WXGENERIC_HEADERS"} .= "generic/" . $file . " "
    }
    
    foreach $file (sort keys %wxMOTIFINCLUDE) {
        $project{"WXMOTIF_HEADERS"} .= "motif/" . $file . " "
    }
    
    foreach $file (sort keys %wxGTKINCLUDE) {
        $project{"WXGTK_HEADERS"} .= "gtk/" . $file . " "
    }
    
    foreach $file (sort keys %wxMSWINCLUDE) {
        $project{"WXMSW_HEADERS"} .= "msw/" . $file . " "
    }
    
    foreach $file (sort keys %wxHTMLINCLUDE) {
        $project{"WXHTML_HEADERS"} .= "html/" . $file . " "
    }
    
    foreach $file (sort keys %wxUNIXINCLUDE) {
        $project{"WXUNIX_HEADERS"} .= "unix/" . $file . " "
    }
    
    foreach $file (sort keys %wxPROTOCOLINCLUDE) {
        $project{"WXPROTOCOL_HEADERS"} .= "protocol/" . $file . " "
    }
#$}
#
# This file was automatically generated by tmake at #$ Now()
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE UNX.T!

#
# File:     makefile.unx
# Author:   Julian Smart, Robert Roebling, Vadim Zeitlin
# Created:  1993
# Updated:  1999
# Copyright:(c) 1993, AIAI, University of Edinburgh,
# Copyright:(c) 1999, Vadim Zeitlin
# Copyright:(c) 1999, Robert Roebling
#
# Makefile for libwx_gtk.a, libwx_motif.a and libwx_msw.a

###################################################################

include ./src/make.env

############## override make.env for PIC ##########################

# Clears all default suffixes
.SUFFIXES:	.o .cpp .c .cxx

.c.o :
	$(CCC) -c @DEP_INFO_FLAGS@ $(CFLAGS) $(PICFLAGS) -o $@ $<

.cpp.o :
	$(CC) -c @DEP_INFO_FLAGS@ $(CPPFLAGS) $(PICFLAGS) -o $@ $<

.cxx.o :
	$(CC) -c @DEP_INFO_FLAGS@ $(CPPFLAGS) $(PICFLAGS) -o $@ $<

########################### Paths #################################

srcdir = @srcdir@

VP1 = @top_srcdir@/src/common
VP2 = @top_srcdir@/src/@TOOLKIT_DIR@
VP3 = @top_srcdir@/src/motif/xmcombo
VP4 = @top_srcdir@/src/generic
VP5 = @top_srcdir@/src/unix
VP6 = @top_srcdir@/src/html
VP7 = @top_srcdir@/src/png
VP8 = @top_srcdir@/src/jpeg
VP9 = @top_srcdir@/src/zlib
VP10 = @top_srcdir@/src/iodbc

VPATH = $(VP1):$(VP2):$(VP3):$(VP4):$(VP5):$(VP6):$(VP7):$(VP8):$(VP9):$(VP10)

top_srcdir = @top_srcdir@
prefix = @prefix@
exec_prefix = @exec_prefix@

bindir = @bindir@
sbindir = @sbindir@
libexecdir = @libexecdir@
datadir = @datadir@
sysconfdir = @sysconfdir@
sharedstatedir = @sharedstatedir@
localstatedir = @localstatedir@
libdir = @libdir@
infodir = @infodir@
mandir = @mandir@
includedir = @includedir@
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/@PACKAGE@
pkglibdir = $(libdir)/@PACKAGE@
pkgincludedir = $(includedir)/@PACKAGE@

top_builddir = .

INSTALL = @INSTALL@
INSTALL_PROGRAM = @INSTALL_PROGRAM@
INSTALL_DATA = @INSTALL_DATA@
# my autoconf doesn't set this
#INSTALL_SCRIPT = @INSTALL_SCRIPT@
# maybe do an additional chmod if needed?
INSTALL_SCRIPT = @INSTALL@ 
transform = @program_transform_name@

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_alias = @build_alias@
build_triplet = @build@
host_alias = @host_alias@
host_triplet = @host@
target_alias = @target_alias@
target_triplet = @target@

############################# Dirs #################################

WXDIR = $(top_srcdir)

# Subordinate library possibilities

SRCDIR   = $(WXDIR)/src
GENDIR   = $(WXDIR)/src/generic
COMMDIR  = $(WXDIR)/src/common
HTMLDIR  = $(WXDIR)/src/html
UNIXDIR  = $(WXDIR)/src/unix
PNGDIR   = $(WXDIR)/src/png
JPEGDIR  = $(WXDIR)/src/jpeg
ZLIBDIR  = $(WXDIR)/src/zlib
GTKDIR   = $(WXDIR)/src/gtk
MOTIFDIR = $(WXDIR)/src/motif
MSWDIR   = $(WXDIR)/src/msw
ODBCDIR  = $(WXDIR)/src/iodbc
INCDIR   = $(WXDIR)/include
SAMPDIR  = $(WXDIR)/samples
UTILSDIR = $(WXDIR)/utils
MISCDIR  = $(WXDIR)/misc

DOCDIR = $(WXDIR)/docs

########################## Archive name ###############################

WXARCHIVE = wx$(TOOLKIT)-$(WX_MAJOR_VERSION_NUMBER).$(WX_MINOR_VERSION_NUMBER).$(WX_RELEASE_NUMBER).tgz
DISTDIR = ./_dist_dir/wx$(TOOLKIT)

############################## Files ##################################

BASE_HEADERS = \
		#$ ExpandList("BASE_HEADERS");

WX_HEADERS = \
		#$ ExpandList("WX_HEADERS");

GTK_HEADERS = \
		#$ ExpandList("WXGTK_HEADERS");

MOTIF_HEADERS = \
		#$ ExpandList("WXMOTIF_HEADERS");

MSW_HEADERS = \
		#$ ExpandList("WXMSW_HEADERS");

UNIX_HEADERS = \
		#$ ExpandList("WXUNIX_HEADERS");

GENERIC_HEADERS = \
		#$ ExpandList("WXGENERIC_HEADERS");

PROTOCOL_HEADERS = \
		#$ ExpandList("WXPROTOCOL_HEADERS");

HTML_HEADERS = \
		#$ ExpandList("WXHTML_HEADERS");

GTK_GENERICOBJS = \
		#$ ExpandList("WXGTK_GENERICOBJS");

GTK_GENERICDEPS = \
		#$ ExpandList("WXGTK_GENERICDEPS");

GTK_COMMONOBJS = \
		parser.o \
		#$ ExpandList("WXGTK_COMMONOBJS");

GTK_COMMONDEPS = \
		parser.d \
		#$ ExpandList("WXGTK_COMMONDEPS");

GTK_GUIOBJS = \
		#$ ExpandList("WXGTK_GUIOBJS");

GTK_GUIDEPS = \
		#$ ExpandList("WXGTK_GUIDEPS");

MOTIF_GENERICOBJS = \
		#$ ExpandList("WXMOTIF_GENERICOBJS");

MOTIF_GENERICDEPS = \
		#$ ExpandList("WXMOTIF_GENERICDEPS");

MOTIF_COMMONOBJS = \
		parser.o \
		#$ ExpandList("WXMOTIF_COMMONOBJS");

MOTIF_COMMONDEPS = \
		parser.d \
		#$ ExpandList("WXMOTIF_COMMONDEPS");

MOTIF_GUIOBJS = \
		xmcombo.o \
		#$ ExpandList("WXMOTIF_GUIOBJS");

MOTIF_GUIDEPS = \
		xmcombo.d \
		#$ ExpandList("WXMOTIF_GUIDEPS");

MSW_GENERICOBJS = \
		#$ ExpandList("WXMSW_GENERICOBJS");

MSW_GENERICDEPS = \
		#$ ExpandList("WXMSW_GENERICDEPS");

MSW_COMMONOBJS = \
		parser.o \
		#$ ExpandList("WXMSW_COMMONOBJS");

MSW_COMMONDEPS = \
		parser.d \
		#$ ExpandList("WXMSW_COMMONDEPS");

MSW_GUIOBJS = \
		#$ ExpandList("WXMSW_GUIOBJS");

MSW_GUIDEPS = \
		#$ ExpandList("WXMSW_GUIDEPS");

BASE_OBJS = \
		#$ ExpandList("BASE_OBJS");

BASE_DEPS = \
		#$ ExpandList("BASE_DEPS");

HTMLOBJS = \
		#$ ExpandList("WXHTMLOBJS");

HTMLDEPS = \
		#$ ExpandList("WXHTMLDEPS");

UNIX_OBJS = \
		#$ ExpandList("WXUNIX_OBJS");

UNIX_DEPS = \
		#$ ExpandList("WXUNIX_DEPS");

ZLIBOBJS    = \
		adler32.o \
		compress.o \
		crc32.o \
		gzio.o \
		uncompr.o \
		deflate.o \
		trees.o \
		zutil.o \
		inflate.o \
		infblock.o \
		inftrees.o \
		infcodes.o \
		infutil.o \
		inffast.o

PNGOBJS     = \
		png.o \
		pngread.o \
		pngrtran.o \
		pngrutil.o \
		pngpread.o \
		pngtrans.o \
		pngwrite.o \
		pngwtran.o \
		pngwutil.o \
		pngerror.o \
		pngmem.o \
		pngwio.o \
		pngrio.o \
		pngget.o \
		pngset.o


JPEGOBJS    = \
		jcomapi.o \
		jutils.o \
		jerror.o \
		jmemmgr.o \
		jmemnobs.o \
		jcapimin.o \
		jcapistd.o \
		jctrans.o \
		jcparam.o \
		jdatadst.o \
		jcinit.o \
		jcmaster.o \
		jcmarker.o \
		jcmainct.o \
		jcprepct.o \
		jccoefct.o \
		jccolor.o \
		jcsample.o \
		jchuff.o \
		jcphuff.o \
		jcdctmgr.o \
		jfdctfst.o \
		jfdctflt.o \
		jfdctint.o \
		jdapimin.o \
		jdapistd.o \
		jdtrans.o \
		jdatasrc.o \
		jdmaster.o \
		jdinput.o \
		jdmarker.o \
		jdhuff.o \
		jdphuff.o \
		jdmainct.o \
		jdcoefct.o \
		jdpostct.o \
		jddctmgr.o \
		jidctfst.o \
		jidctflt.o \
		jidctint.o \
		jidctred.o \
		jdsample.o \
		jdcolor.o \
		jquant1.o \
		jquant2.o \
		jdmerge.o

IODBC_OBJS = \
		catalog.o \
		connect.o \
		dlf.o \
		dlproc.o \
		execute.o \
		fetch.o \
		hdbc.o \
		henv.o \
		herr.o \
		hstmt.o \
		info.o \
		itrace.o \
		misc.o \
		prepare.o \
		result.o

GUIOBJS = @GUIOBJS@
GUIDEPS = @GUIDEPS@
GUIHEADERS = @GUIHEADERS@
COMMONOBJS = @COMMONOBJS@
COMMONDEPS = @COMMONDEPS@
GENERICOBJS = @GENERICOBJS@
GENERICDEPS = @GENERICDEPS@
UNIXOBJS = @UNIXOBJS@
UNIXDEPS = @UNIXDEPS@
IODBCOBJS = @IODBCOBJS@

OBJECTS = @ALL_OBJECTS@

DEPFILES = @ALL_DEPFILES@

HEADERS = @ALL_HEADERS@

all: @WX_ALL@

@WX_LIBRARY_NAME_STATIC@:  $(OBJECTS)
	@$(INSTALL) -d ./lib
	$(AR) $(AROPTIONS) ./lib/$@ $(OBJECTS)
	$(RANLIB) ./lib/$@

@WX_LIBRARY_NAME_SHARED@:  $(OBJECTS)
	@$(INSTALL) -d ./lib
	$(SHARED_LD) ./lib/$@ $(OBJECTS) $(EXTRALIBS)
	
CREATE_LINKS: @WX_LIBRARY_NAME_SHARED@
	@$(RM) ./lib/@WX_LIBRARY_LINK1@
	@$(RM) ./lib/@WX_LIBRARY_LINK2@
	@$(RM) ./lib/@WX_LIBRARY_LINK3@
	$(LN_S) @WX_TARGET_LIBRARY@ ./lib/@WX_LIBRARY_LINK1@
	$(LN_S) @WX_TARGET_LIBRARY@ ./lib/@WX_LIBRARY_LINK2@
	$(LN_S) @WX_TARGET_LIBRARY@ ./lib/@WX_LIBRARY_LINK3@
	
CREATE_INSTALLED_LINKS:  $(libdir)/@WX_LIBRARY_NAME_SHARED@
	$(RM) $(libdir)/@WX_LIBRARY_LINK1@
	$(RM) $(libdir)/@WX_LIBRARY_LINK2@
	$(RM) $(libdir)/@WX_LIBRARY_LINK3@
	$(LN_S) @WX_LIBRARY_NAME_SHARED@ $(libdir)/@WX_LIBRARY_LINK1@
	$(LN_S) @WX_LIBRARY_NAME_SHARED@ $(libdir)/@WX_LIBRARY_LINK2@
	$(LN_S) @WX_LIBRARY_NAME_SHARED@ $(libdir)/@WX_LIBRARY_LINK3@
	
$(OBJECTS):	$(WXDIR)/include/wx/defs.h $(WXDIR)/include/wx/object.h $(WXDIR)/include/wx/setup.h

parser.o:    parser.c lexer.c
	$(CCLEX) -c $(CFLAGS) $(PICFLAGS) -o $@ parser.c

parser.c:	$(COMMDIR)/parser.y lexer.c
	$(YACC) $(COMMDIR)/parser.y
	@sed -e "s;$(COMMDIR)/y.tab.c;parser.y;g" < y.tab.c | \
	sed -e "s/BUFSIZ/5000/g"            | \
	sed -e "s/YYLMAX 200/YYLMAX 5000/g" | \
	sed -e "s/yy/PROIO_yy/g"            | \
	sed -e "s/input/PROIO_input/g"      | \
	sed -e "s/unput/PROIO_unput/g"      > parser.c
	@$(RM) y.tab.c

lexer.c:	$(COMMDIR)/lexer.l
	$(LEX) $(COMMDIR)/lexer.l
	@sed -e "s;$(COMMDIR)/lex.yy.c;lexer.l;g" < lex.yy.c | \
	sed -e "s/yy/PROIO_yy/g"            | \
	sed -e "s/input/PROIO_input/g"      | \
	sed -e "s/unput/PROIO_unput/g"      > lexer.c
	@$(RM) lex.yy.c

-include $(DEPFILES)

preinstall: $(top_builddir)/lib/@WX_TARGET_LIBRARY@ $(top_builddir)/wx-config $(top_builddir)/setup.h
	@echo " "
	@echo " Installing wxWindows..."
	@echo " "

	$(INSTALL) -d $(prefix)
	$(INSTALL) -d $(bindir)
	$(INSTALL) -d $(libdir)
	$(INSTALL) -d $(datadir)

	$(INSTALL_SCRIPT) $(top_builddir)/wx-config $(bindir)/wx-config
	$(INSTALL_PROGRAM) $(top_builddir)/lib/@WX_TARGET_LIBRARY@ $(libdir)/@WX_TARGET_LIBRARY@

	$(INSTALL) -d $(libdir)/wx
	$(INSTALL) -d $(libdir)/wx/include
	$(INSTALL) -d $(libdir)/wx/include/wx
	$(INSTALL) -d $(libdir)/wx/include/wx/@TOOLKIT_DIR@
	$(INSTALL_DATA) $(top_builddir)/setup.h $(libdir)/wx/include/wx/@TOOLKIT_DIR@/setup.h
	
	$(INSTALL) -d $(datadir)/wx
	$(INSTALL) -d $(datadir)/wx/afm
	$(INSTALL) -d $(datadir)/wx/gs_afm
	$(INSTALL_DATA) $(top_srcdir)/misc/afm/*.afm $(datadir)/wx/afm
	$(INSTALL_DATA) $(top_srcdir)/misc/gs_afm/*.afm $(datadir)/wx/gs_afm
	
	$(INSTALL) -d $(includedir)/wx
	$(INSTALL) -d $(includedir)/wx/msw
	$(INSTALL) -d $(includedir)/wx/gtk
	$(INSTALL) -d $(includedir)/wx/motif
	$(INSTALL) -d $(includedir)/wx/html
	$(INSTALL) -d $(includedir)/wx/protocol
	$(INSTALL) -d $(includedir)/wx/unix
	$(INSTALL) -d $(includedir)/wx/generic
	@list='$(HEADERS)'; for p in $$list; do \
	  $(INSTALL_DATA) $(top_srcdir)/include/wx/$$p $(includedir)/wx/$$p; \
	  echo "$(INSTALL_DATA) $(top_srcdir)/include/wx/$$p $(includedir)/wx/$$p"; \
	done
	
write_message:
	@echo " "
	@echo " The installation of wxWindows is finished.  On certain"
	@echo " platforms (e.g. Linux) you'll now have to run ldconfig"
	@echo " if you installed a shared library."
	@echo " "
	@echo " wxWindows comes with  no guarantees  and doesn't claim"
	@echo " to be suitable for any purpose."
	@echo " "
	@echo " Read the wxWindows Licence on licencing conditions."
	@echo " "

install: preinstall @WX_ALL_INSTALLED@ write_message

uninstall:
	@echo " "
	@echo " Uninstalling wxWindows..."
	@echo " "
	@echo " Removing library..."
	@$(RM) $(libdir)/@WX_TARGET_LIBRARY@
	@$(RM) $(libdir)/@WX_LIBRARY_LINK1@
	@$(RM) $(libdir)/@WX_LIBRARY_LINK2@
	@$(RM) $(libdir)/@WX_LIBRARY_LINK3@
	@echo " Removing helper files..."
	@$(RM) $(libdir)/wx/include/wx/@TOOLKIT_DIR@/setup.h
	@$(RM) $(bindir)/wx-config
	@$(RM) $(datadir)/wx/afm/*
	@$(RM) $(datadir)/wx/gs_afm/*
	@rmdir $(datadir)/wx/gs_afm
	@rmdir $(datadir)/wx/afm
	@rmdir $(datadir)/wx
	@echo " Removing headers..."
	@list='$(HEADERS)'; for p in $$list; do \
	  $(RM) $(includedir)/wx/$$p; \
	done
	@echo " Removing directories..."
	@if test -d $(libdir)/wx/include/wx/@TOOLKIT_DIR@; then rmdir $(libdir)/wx/include/wx/@TOOLKIT_DIR@; fi
	@if test -d $(libdir)/wx/include/wx; then rmdir $(libdir)/wx/include/wx; fi
	@if test -d $(libdir)/wx/include; then rmdir $(libdir)/wx/include; fi
	@if test -d $(libdir)/wx; then rmdir $(libdir)/wx; fi
	@if test -d $(includedir)/wx/gtk; then rmdir $(includedir)/wx/gtk; fi
	@if test -d $(includedir)/wx/motif; then rmdir $(includedir)/wx/motif; fi
	@if test -d $(includedir)/wx/msw; then rmdir $(includedir)/wx/msw; fi
	@if test -d $(includedir)/wx/html; then rmdir $(includedir)/wx/html; fi
	@if test -d $(includedir)/wx/unix; then rmdir $(includedir)/wx/unix; fi
	@if test -d $(includedir)/wx/generic; then rmdir $(includedir)/wx/generic; fi
	@if test -d $(includedir)/wx/protocol; then rmdir $(includedir)/wx/protocol; fi
	@if test -d $(includedir)/wx; then rmdir $(includedir)/wx; fi

ALL_DIST:
	mkdir _dist_dir
	mkdir $(DISTDIR)
	cp $(WXDIR)/wx$(TOOLKIT).spec $(DISTDIR)
	cp $(WXDIR)/configure $(DISTDIR)
	cp $(WXDIR)/config.sub $(DISTDIR)
	cp $(WXDIR)/config.guess $(DISTDIR)
	cp $(WXDIR)/install-sh $(DISTDIR)
	cp $(WXDIR)/mkinstalldirs $(DISTDIR)
	cp $(WXDIR)/wx-config.in $(DISTDIR)
	cp $(WXDIR)/setup.h.in $(DISTDIR)
	cp $(WXDIR)/Makefile.in $(DISTDIR)
	cp $(DOCDIR)/lgpl.txt $(DISTDIR)/COPYING.LIB
	cp $(DOCDIR)/licence.txt $(DISTDIR)/LICENCE.txt
	cp $(DOCDIR)/symbols.txt $(DISTDIR)/SYMBOLS.txt
	cp $(DOCDIR)/$(TOOLKITDIR)/install.txt $(DISTDIR)/INSTALL.txt
	cp $(DOCDIR)/$(TOOLKITDIR)/changes.txt $(DISTDIR)/CHANGES.txt
	cp $(DOCDIR)/$(TOOLKITDIR)/readme.txt $(DISTDIR)/README.txt
	cp $(DOCDIR)/$(TOOLKITDIR)/todo.txt $(DISTDIR)/TODO.txt
	mkdir $(DISTDIR)/include
	mkdir $(DISTDIR)/include/wx
	mkdir $(DISTDIR)/include/wx/$(TOOLKITDIR)
	mkdir $(DISTDIR)/include/wx/generic
	mkdir $(DISTDIR)/include/wx/html
	mkdir $(DISTDIR)/include/wx/unix
	mkdir $(DISTDIR)/include/wx/protocol
	cp $(INCDIR)/wx/*.h $(DISTDIR)/include/wx 
	cp $(INCDIR)/wx/*.cpp $(DISTDIR)/include/wx
	cp $(INCDIR)/wx/generic/*.h $(DISTDIR)/include/wx/generic
	cp $(INCDIR)/wx/generic/*.xpm $(DISTDIR)/include/wx/generic
	cp $(INCDIR)/wx/html/*.h $(DISTDIR)/include/wx/html
	cp $(INCDIR)/wx/unix/*.h $(DISTDIR)/include/wx/unix
	cp $(INCDIR)/wx/protocol/*.h $(DISTDIR)/include/wx/protocol
	mkdir $(DISTDIR)/src
	mkdir $(DISTDIR)/src/common
	mkdir $(DISTDIR)/src/generic
	mkdir $(DISTDIR)/src/html
	mkdir $(DISTDIR)/src/html/bitmaps
	mkdir $(DISTDIR)/src/$(TOOLKITDIR)
	mkdir $(DISTDIR)/src/unix
	mkdir $(DISTDIR)/src/png
	mkdir $(DISTDIR)/src/jpeg
	mkdir $(DISTDIR)/src/zlib
	mkdir $(DISTDIR)/src/iodbc
	cp $(SRCDIR)/*.in $(DISTDIR)/src
	cp $(COMMDIR)/*.cpp $(DISTDIR)/src/common
	cp $(COMMDIR)/*.c $(DISTDIR)/src/common
	cp $(COMMDIR)/*.inc $(DISTDIR)/src/common
	cp $(COMMDIR)/*.l $(DISTDIR)/src/common
	cp $(COMMDIR)/*.h $(DISTDIR)/src/common
	cp $(COMMDIR)/*.y $(DISTDIR)/src/common
	cp $(GENDIR)/*.cpp $(DISTDIR)/src/generic
	cp $(HTMLDIR)/*.cpp $(DISTDIR)/src/html
	cp $(HTMLDIR)/bitmaps/*.xpm $(DISTDIR)/src/html/bitmaps
	cp $(UNIXDIR)/*.c $(DISTDIR)/src/unix
	cp $(UNIXDIR)/*.cpp $(DISTDIR)/src/unix
	cp $(PNGDIR)/*.h $(DISTDIR)/src/png
	cp $(PNGDIR)/*.c $(DISTDIR)/src/png
	cp $(PNGDIR)/README $(DISTDIR)/src/png
	cp $(ZLIBDIR)/*.h $(DISTDIR)/src/zlib
	cp $(ZLIBDIR)/*.c $(DISTDIR)/src/zlib
	cp $(ZLIBDIR)/README $(DISTDIR)/src/zlib
	cp $(JPEGDIR)/*.h $(DISTDIR)/src/jpeg
	cp $(JPEGDIR)/*.c $(DISTDIR)/src/jpeg
	cp $(JPEGDIR)/README $(DISTDIR)/src/jpeg
	cp $(ODBCDIR)/*.h $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/*.c $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/*.ci $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/*.exp $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/README $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/NEWS $(DISTDIR)/src/iodbc
	cp $(ODBCDIR)/Changes.log $(DISTDIR)/src/iodbc

GTK_DIST:
	cp $(WXDIR)/wxGTK.spec $(DISTDIR)
	cp $(INCDIR)/wx/gtk/*.h $(DISTDIR)/include/wx/gtk
	cp $(INCDIR)/wx/gtk/*.xpm $(DISTDIR)/include/wx/gtk
	cp $(GTKDIR)/*.cpp $(DISTDIR)/src/gtk
	cp $(GTKDIR)/*.c $(DISTDIR)/src/gtk
	cp $(GTKDIR)/*.xbm $(DISTDIR)/src/gtk

MOTIF_DIST:
	cp $(WXDIR)/wxMOTIF.spec $(DISTDIR)
	cp $(INCDIR)/wx/motif/*.h $(DISTDIR)/include/wx/motif
	cp $(MOTIFDIR)/*.cpp $(DISTDIR)/src/motif
	cp $(MOTIFDIR)/*.xbm $(DISTDIR)/src/motif
	mkdir $(DISTDIR)/src/motif/xmcombo
	cp $(MOTIFDIR)/xmcombo/*.c $(DISTDIR)/src/motif/xmcombo
	cp $(MOTIFDIR)/xmcombo/*.h $(DISTDIR)/src/motif/xmcombo
	cp $(MOTIFDIR)/xmcombo/copying.txt $(DISTDIR)/src/motif/xmcombo

MSW_DIST:
	cp $(WXDIR)/wxWINE.spec $(DISTDIR)
	cp $(INCDIR)/wx/msw/*.h $(DISTDIR)/include/wx/msw
	cp $(INCDIR)/wx/msw/*.cur $(DISTDIR)/include/wx/msw
	cp $(INCDIR)/wx/msw/*.ico $(DISTDIR)/include/wx/msw
	cp $(INCDIR)/wx/msw/*.bmp $(DISTDIR)/include/wx/msw
	cp $(INCDIR)/wx/msw/*.rc $(DISTDIR)/include/wx/msw
	cp $(MSWDIR)/*.cpp $(DISTDIR)/src/msw
	cp $(MSWDIR)/*.c $(DISTDIR)/src/msw
	cp $(MSWDIR)/*.def $(DISTDIR)/src/msw
	mkdir $(DISTDIR)/src/msw/ole
	cp $(MSWDIR)/ole/*.cpp $(DISTDIR)/src/msw/ole

SAMPLES_DIST:
	mkdir $(DISTDIR)/samples
	cp $(SAMPDIR)/Makefile.in $(DISTDIR)/samples
	mkdir $(DISTDIR)/samples/bombs
	cp $(SAMPDIR)/bombs/Makefile.in $(DISTDIR)/samples/bombs
	cp $(SAMPDIR)/bombs/*.cpp $(DISTDIR)/samples/bombs
	cp $(SAMPDIR)/bombs/*.h $(DISTDIR)/samples/bombs
	cp $(SAMPDIR)/bombs/*.xpm $(DISTDIR)/samples/bombs
	cp $(SAMPDIR)/bombs/readme.txt $(DISTDIR)/samples/bombs
	mkdir $(DISTDIR)/samples/caret
	cp $(SAMPDIR)/caret/Makefile.in $(DISTDIR)/samples/caret
	cp $(SAMPDIR)/caret/*.cpp $(DISTDIR)/samples/caret
	cp $(SAMPDIR)/caret/*.xpm $(DISTDIR)/samples/caret
	mkdir $(DISTDIR)/samples/config
	cp $(SAMPDIR)/config/Makefile.in $(DISTDIR)/samples/config
	cp $(SAMPDIR)/config/*.cpp $(DISTDIR)/samples/config
	mkdir $(DISTDIR)/samples/controls
	mkdir $(DISTDIR)/samples/controls/icons
	cp $(SAMPDIR)/controls/Makefile.in $(DISTDIR)/samples/controls
	cp $(SAMPDIR)/controls/*.cpp $(DISTDIR)/samples/controls
	cp $(SAMPDIR)/controls/*.xpm $(DISTDIR)/samples/controls
	cp $(SAMPDIR)/controls/icons/*.??? $(DISTDIR)/samples/controls/icons
	mkdir $(DISTDIR)/samples/checklst
	cp $(SAMPDIR)/checklst/Makefile.in $(DISTDIR)/samples/checklst
	cp $(SAMPDIR)/checklst/*.cpp $(DISTDIR)/samples/checklst
	cp $(SAMPDIR)/checklst/*.xpm $(DISTDIR)/samples/checklst
	mkdir $(DISTDIR)/samples/printing
	cp $(SAMPDIR)/printing/Makefile.in $(DISTDIR)/samples/printing
	cp $(SAMPDIR)/printing/*.cpp $(DISTDIR)/samples/printing
	cp $(SAMPDIR)/printing/*.h $(DISTDIR)/samples/printing
	cp $(SAMPDIR)/printing/*.xpm $(DISTDIR)/samples/printing
	cp $(SAMPDIR)/printing/*.xbm $(DISTDIR)/samples/printing
	mkdir $(DISTDIR)/samples/db
	cp $(SAMPDIR)/db/Makefile.in $(DISTDIR)/samples/db
	cp $(SAMPDIR)/db/*.cpp $(DISTDIR)/samples/db
	cp $(SAMPDIR)/db/*.h $(DISTDIR)/samples/db
	cp $(SAMPDIR)/db/*.xpm $(DISTDIR)/samples/db
	mkdir $(DISTDIR)/samples/dialogs
	cp $(SAMPDIR)/dialogs/Makefile.in $(DISTDIR)/samples/dialogs
	cp $(SAMPDIR)/dialogs/*.cpp $(DISTDIR)/samples/dialogs
	cp $(SAMPDIR)/dialogs/*.h $(DISTDIR)/samples/dialogs
	cp $(SAMPDIR)/dialogs/*.txt $(DISTDIR)/samples/dialogs
	mkdir $(DISTDIR)/samples/dnd
	cp $(SAMPDIR)/dnd/Makefile.in $(DISTDIR)/samples/dnd
	cp $(SAMPDIR)/dnd/*.cpp $(DISTDIR)/samples/dnd
	cp $(SAMPDIR)/dnd/*.xpm $(DISTDIR)/samples/dnd
	cp $(SAMPDIR)/dnd/*.txt $(DISTDIR)/samples/dnd
	cp $(SAMPDIR)/dnd/*.png $(DISTDIR)/samples/dnd
	mkdir $(DISTDIR)/samples/docview
	cp $(SAMPDIR)/docview/Makefile.in $(DISTDIR)/samples/docview
	cp $(SAMPDIR)/docview/*.cpp $(DISTDIR)/samples/docview
	cp $(SAMPDIR)/docview/*.h $(DISTDIR)/samples/docview
	cp $(SAMPDIR)/docview/*.xpm $(DISTDIR)/samples/docview
	mkdir $(DISTDIR)/samples/docvwmdi
	cp $(SAMPDIR)/docvwmdi/Makefile.in $(DISTDIR)/samples/docvwmdi
	cp $(SAMPDIR)/docvwmdi/*.cpp $(DISTDIR)/samples/docvwmdi
	cp $(SAMPDIR)/docvwmdi/*.h $(DISTDIR)/samples/docvwmdi
	mkdir $(DISTDIR)/samples/drawing
	cp $(SAMPDIR)/drawing/Makefile.in $(DISTDIR)/samples/drawing
	cp $(SAMPDIR)/drawing/*.cpp $(DISTDIR)/samples/drawing
	cp $(SAMPDIR)/drawing/*.xpm $(DISTDIR)/samples/drawing
	mkdir $(DISTDIR)/samples/dynamic
	cp $(SAMPDIR)/dynamic/Makefile.in $(DISTDIR)/samples/dynamic
	cp $(SAMPDIR)/dynamic/*.cpp $(DISTDIR)/samples/dynamic
	cp $(SAMPDIR)/dynamic/*.xpm $(DISTDIR)/samples/dynamic
	mkdir $(DISTDIR)/samples/forty
	cp $(SAMPDIR)/forty/Makefile.in $(DISTDIR)/samples/forty
	cp $(SAMPDIR)/forty/*.cpp $(DISTDIR)/samples/forty
	cp $(SAMPDIR)/forty/*.xpm $(DISTDIR)/samples/forty
	cp $(SAMPDIR)/forty/*.xbm $(DISTDIR)/samples/forty
	mkdir $(DISTDIR)/samples/fractal
	cp $(SAMPDIR)/fractal/Makefile.in $(DISTDIR)/samples/fractal
	cp $(SAMPDIR)/fractal/*.cpp $(DISTDIR)/samples/fractal
	mkdir $(DISTDIR)/samples/html
	cp $(SAMPDIR)/html/Makefile.in $(DISTDIR)/samples/html
	mkdir $(DISTDIR)/samples/html/about
	cp $(SAMPDIR)/html/about/Makefile.in $(DISTDIR)/samples/html/about
	cp $(SAMPDIR)/html/about/*.cpp $(DISTDIR)/samples/html/about
	mkdir $(DISTDIR)/samples/html/about/data
	cp $(SAMPDIR)/html/about/data/*.htm $(DISTDIR)/samples/html/about/data
	cp $(SAMPDIR)/html/about/data/*.png $(DISTDIR)/samples/html/about/data
	mkdir $(DISTDIR)/samples/html/help
	cp $(SAMPDIR)/html/help/Makefile.in $(DISTDIR)/samples/html/help
	cp $(SAMPDIR)/html/help/*.cpp $(DISTDIR)/samples/html/help
	mkdir $(DISTDIR)/samples/html/help/helpfiles
	cp $(SAMPDIR)/html/help/helpfiles/*.??? $(DISTDIR)/samples/html/help/helpfiles
	mkdir $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/Makefile.in $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/*.xpm $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/*.cpp $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/*.h $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/*.png $(DISTDIR)/samples/html/printing
	cp $(SAMPDIR)/html/printing/*.htm $(DISTDIR)/samples/html/printing
	mkdir $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/Makefile.in $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/*.cpp $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/*.bmp $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/*.png $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/*.htm $(DISTDIR)/samples/html/test
	cp $(SAMPDIR)/html/test/*.html $(DISTDIR)/samples/html/test
	mkdir $(DISTDIR)/samples/html/virtual
	cp $(SAMPDIR)/html/virtual/Makefile.in $(DISTDIR)/samples/html/virtual
	cp $(SAMPDIR)/html/virtual/*.cpp $(DISTDIR)/samples/html/virtual
	cp $(SAMPDIR)/html/virtual/*.htm $(DISTDIR)/samples/html/virtual
	mkdir $(DISTDIR)/samples/html/widget
	cp $(SAMPDIR)/html/widget/Makefile.in $(DISTDIR)/samples/html/widget
	cp $(SAMPDIR)/html/widget/*.cpp $(DISTDIR)/samples/html/widget
	cp $(SAMPDIR)/html/widget/*.htm $(DISTDIR)/samples/html/widget
	mkdir $(DISTDIR)/samples/html/zip
	cp $(SAMPDIR)/html/zip/Makefile.in $(DISTDIR)/samples/html/zip
	cp $(SAMPDIR)/html/zip/*.cpp $(DISTDIR)/samples/html/zip
	cp $(SAMPDIR)/html/zip/*.htm $(DISTDIR)/samples/html/zip
	cp $(SAMPDIR)/html/zip/*.zip $(DISTDIR)/samples/html/zip
	mkdir $(DISTDIR)/samples/image
	cp $(SAMPDIR)/image/Makefile.in $(DISTDIR)/samples/image
	cp $(SAMPDIR)/image/*.cpp $(DISTDIR)/samples/image
	cp $(SAMPDIR)/image/horse.* $(DISTDIR)/samples/image
	mkdir $(DISTDIR)/samples/internat
	mkdir $(DISTDIR)/samples/internat/de
	mkdir $(DISTDIR)/samples/internat/fr
	cp $(SAMPDIR)/internat/Makefile.in $(DISTDIR)/samples/internat
	cp $(SAMPDIR)/internat/*.cpp $(DISTDIR)/samples/internat
	cp $(SAMPDIR)/internat/*.xpm $(DISTDIR)/samples/internat
	cp $(SAMPDIR)/internat/*.txt $(DISTDIR)/samples/internat
	cp $(SAMPDIR)/internat/*.po $(DISTDIR)/samples/internat
	cp $(SAMPDIR)/internat/fr/*.po $(DISTDIR)/samples/internat/fr
	cp $(SAMPDIR)/internat/de/*.mo $(DISTDIR)/samples/internat/de
	cp $(SAMPDIR)/internat/fr/*.po $(DISTDIR)/samples/internat/fr
	cp $(SAMPDIR)/internat/de/*.mo $(DISTDIR)/samples/internat/de
	mkdir $(DISTDIR)/samples/layout
	cp $(SAMPDIR)/layout/Makefile.in $(DISTDIR)/samples/layout
	cp $(SAMPDIR)/layout/*.cpp $(DISTDIR)/samples/layout
	cp $(SAMPDIR)/layout/*.h $(DISTDIR)/samples/layout
	mkdir $(DISTDIR)/samples/listctrl
	cp $(SAMPDIR)/listctrl/Makefile.in $(DISTDIR)/samples/listctrl
	cp $(SAMPDIR)/listctrl/*.cpp $(DISTDIR)/samples/listctrl
	cp $(SAMPDIR)/listctrl/*.h $(DISTDIR)/samples/listctrl
	cp $(SAMPDIR)/listctrl/*.xpm $(DISTDIR)/samples/listctrl
	mkdir $(DISTDIR)/samples/listctrl/bitmap
	cp $(SAMPDIR)/listctrl/*.xpm $(DISTDIR)/samples/listctrl/bitmaps
	mkdir $(DISTDIR)/samples/mdi
	cp $(SAMPDIR)/mdi/Makefile.in $(DISTDIR)/samples/mdi
	cp $(SAMPDIR)/mdi/*.cpp $(DISTDIR)/samples/mdi
	cp $(SAMPDIR)/mdi/*.h $(DISTDIR)/samples/mdi
	cp $(SAMPDIR)/mdi/*.xpm $(DISTDIR)/samples/mdi
	mkdir $(DISTDIR)/samples/minifram
	cp $(SAMPDIR)/minifram/Makefile.in $(DISTDIR)/samples/minifram
	cp $(SAMPDIR)/minifram/*.cpp $(DISTDIR)/samples/minifram
	cp $(SAMPDIR)/minifram/*.h $(DISTDIR)/samples/minifram
	cp $(SAMPDIR)/minifram/*.xpm $(DISTDIR)/samples/minifram
	mkdir $(DISTDIR)/samples/minifram/bitmap
	cp $(SAMPDIR)/minifram/*.xpm $(DISTDIR)/samples/minifram/bitmaps
	mkdir $(DISTDIR)/samples/minimal
	cp $(SAMPDIR)/minimal/Makefile.in $(DISTDIR)/samples/minimal
	cp $(SAMPDIR)/minimal/*.cpp $(DISTDIR)/samples/minimal
	cp $(SAMPDIR)/minimal/*.xpm $(DISTDIR)/samples/minimal
	mkdir $(DISTDIR)/samples/newgrid
	cp $(SAMPDIR)/newgrid/Makefile.in $(DISTDIR)/samples/newgrid
	cp $(SAMPDIR)/newgrid/*.cpp $(DISTDIR)/samples/newgrid
	cp $(SAMPDIR)/newgrid/*.h $(DISTDIR)/samples/newgrid
	mkdir $(DISTDIR)/samples/notebook
	cp $(SAMPDIR)/notebook/Makefile.in $(DISTDIR)/samples/notebook
	cp $(SAMPDIR)/notebook/*.cpp $(DISTDIR)/samples/notebook
	cp $(SAMPDIR)/notebook/*.h $(DISTDIR)/samples/notebook
	mkdir $(DISTDIR)/samples/png
	cp $(SAMPDIR)/png/Makefile.in $(DISTDIR)/samples/png
	cp $(SAMPDIR)/png/*.cpp $(DISTDIR)/samples/png
	cp $(SAMPDIR)/png/*.h $(DISTDIR)/samples/png
	cp $(SAMPDIR)/png/*.png $(DISTDIR)/samples/png
	mkdir $(DISTDIR)/samples/resource
	cp $(SAMPDIR)/resource/Makefile.in $(DISTDIR)/samples/resource
	cp $(SAMPDIR)/resource/*.cpp $(DISTDIR)/samples/resource
	cp $(SAMPDIR)/resource/*.h $(DISTDIR)/samples/resource
	cp $(SAMPDIR)/resource/*.wxr $(DISTDIR)/samples/resource
	mkdir $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/Makefile.in $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/*.cpp $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/*.h $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/*.xpm $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/README $(DISTDIR)/samples/richedit
	cp $(SAMPDIR)/richedit/TODO $(DISTDIR)/samples/richedit
	mkdir $(DISTDIR)/samples/proplist
	cp $(SAMPDIR)/proplist/Makefile.in $(DISTDIR)/samples/proplist
	cp $(SAMPDIR)/proplist/*.cpp $(DISTDIR)/samples/proplist
	cp $(SAMPDIR)/proplist/*.h $(DISTDIR)/samples/proplist
	mkdir $(DISTDIR)/samples/sashtest
	cp $(SAMPDIR)/sashtest/Makefile.in $(DISTDIR)/samples/sashtest
	cp $(SAMPDIR)/sashtest/*.cpp $(DISTDIR)/samples/sashtest
	cp $(SAMPDIR)/sashtest/*.h $(DISTDIR)/samples/sashtest
	mkdir $(DISTDIR)/samples/scroll
	cp $(SAMPDIR)/scroll/Makefile.in $(DISTDIR)/samples/scroll
	cp $(SAMPDIR)/scroll/*.cpp $(DISTDIR)/samples/scroll
	mkdir $(DISTDIR)/samples/splitter
	cp $(SAMPDIR)/splitter/Makefile.in $(DISTDIR)/samples/splitter
	cp $(SAMPDIR)/splitter/*.cpp $(DISTDIR)/samples/splitter
	mkdir $(DISTDIR)/samples/text
	cp $(SAMPDIR)/text/Makefile.in $(DISTDIR)/samples/text
	cp $(SAMPDIR)/text/*.cpp $(DISTDIR)/samples/text
	cp $(SAMPDIR)/text/*.xpm $(DISTDIR)/samples/text
	mkdir $(DISTDIR)/samples/thread
	cp $(SAMPDIR)/thread/Makefile.in $(DISTDIR)/samples/thread
	cp $(SAMPDIR)/thread/*.cpp $(DISTDIR)/samples/thread
	mkdir $(DISTDIR)/samples/toolbar
	cp $(SAMPDIR)/toolbar/Makefile.in $(DISTDIR)/samples/toolbar
	cp $(SAMPDIR)/toolbar/*.cpp $(DISTDIR)/samples/toolbar
	cp $(SAMPDIR)/toolbar/*.h $(DISTDIR)/samples/toolbar
	cp $(SAMPDIR)/toolbar/*.xpm $(DISTDIR)/samples/toolbar
	mkdir $(DISTDIR)/samples/toolbar/bitmap
	cp $(SAMPDIR)/toolbar/*.xpm $(DISTDIR)/samples/toolbar/bitmaps
	mkdir $(DISTDIR)/samples/treectrl
	cp $(SAMPDIR)/treectrl/Makefile.in $(DISTDIR)/samples/treectrl
	cp $(SAMPDIR)/treectrl/*.cpp $(DISTDIR)/samples/treectrl
	cp $(SAMPDIR)/treectrl/*.h $(DISTDIR)/samples/treectrl
	cp $(SAMPDIR)/treectrl/*.xpm $(DISTDIR)/samples/treectrl
	mkdir $(DISTDIR)/samples/typetest
	cp $(SAMPDIR)/typetest/Makefile.in $(DISTDIR)/samples/typetest
	cp $(SAMPDIR)/typetest/*.cpp $(DISTDIR)/samples/typetest
	cp $(SAMPDIR)/typetest/*.h $(DISTDIR)/samples/typetest
	cp $(SAMPDIR)/typetest/*.xpm $(DISTDIR)/samples/typetest
	mkdir $(DISTDIR)/samples/validate
	cp $(SAMPDIR)/validate/Makefile.in $(DISTDIR)/samples/validate
	cp $(SAMPDIR)/validate/*.cpp $(DISTDIR)/samples/validate
	cp $(SAMPDIR)/validate/*.h $(DISTDIR)/samples/validate
	cp $(SAMPDIR)/validate/*.xpm $(DISTDIR)/samples/validate
	mkdir $(DISTDIR)/samples/wizard
	cp $(SAMPDIR)/wizard/Makefile.in $(DISTDIR)/samples/wizard
	cp $(SAMPDIR)/wizard/*.cpp $(DISTDIR)/samples/wizard
	cp $(SAMPDIR)/wizard/*.xpm $(DISTDIR)/samples/wizard
	mkdir $(DISTDIR)/samples/wxpoem
	cp $(SAMPDIR)/wxpoem/Makefile.in $(DISTDIR)/samples/wxpoem
	cp $(SAMPDIR)/wxpoem/*.cpp $(DISTDIR)/samples/wxpoem
	cp $(SAMPDIR)/wxpoem/*.xpm $(DISTDIR)/samples/wxpoem
	cp $(SAMPDIR)/wxpoem/*.dat $(DISTDIR)/samples/wxpoem
	cp $(SAMPDIR)/wxpoem/*.txt $(DISTDIR)/samples/wxpoem
	mkdir $(DISTDIR)/samples/wxsocket
	cp $(SAMPDIR)/wxsocket/Makefile.in $(DISTDIR)/samples/wxsocket
	cp $(SAMPDIR)/wxsocket/*.cpp $(DISTDIR)/samples/wxsocket
	cp $(SAMPDIR)/wxsocket/*.xpm $(DISTDIR)/samples/wxsocket

UTILS_DIST:
	mkdir $(DISTDIR)/utils
	cp $(UTILSDIR)/Makefile.in $(DISTDIR)/utils
	
	mkdir $(DISTDIR)/utils/wxMMedia2
	mkdir $(DISTDIR)/utils/wxMMedia2/lib
	mkdir $(DISTDIR)/utils/wxMMedia2/sample
	cp $(UTILSDIR)/wxMMedia2/Makefile.in $(DISTDIR)/utils/wxMMedia2
	cp $(UTILSDIR)/wxMMedia2/lib/Makefile.in $(DISTDIR)/utils/wxMMedia2/lib
	cp $(UTILSDIR)/wxMMedia2/lib/*.h $(DISTDIR)/utils/wxMMedia2/lib
	cp $(UTILSDIR)/wxMMedia2/lib/*.cpp $(DISTDIR)/utils/wxMMedia2/lib
	cp $(UTILSDIR)/wxMMedia2/lib/*.def $(DISTDIR)/utils/wxMMedia2/lib
	cp $(UTILSDIR)/wxMMedia2/sample/Makefile.in $(DISTDIR)/utils/wxMMedia2/sample
	cp $(UTILSDIR)/wxMMedia2/sample/*.cpp $(DISTDIR)/utils/wxMMedia2/sample
	
	mkdir $(DISTDIR)/utils/glcanvas
	mkdir $(DISTDIR)/utils/glcanvas/$(TOOLKITDIR)
	cp $(UTILSDIR)/glcanvas/Makefile.in $(DISTDIR)/utils/glcanvas
	cp $(UTILSDIR)/glcanvas/docs/notes.txt $(DISTDIR)/utils/glcanvas/NOTES.txt
	cp $(UTILSDIR)/glcanvas/$(TOOLKITDIR)/Makefile.in $(DISTDIR)/utils/glcanvas/$(TOOLKITDIR)
	cp $(UTILSDIR)/glcanvas/$(TOOLKITDIR)/*.h $(DISTDIR)/utils/glcanvas/$(TOOLKITDIR)
	cp $(UTILSDIR)/glcanvas/$(TOOLKITDIR)/*.cpp $(DISTDIR)/utils/glcanvas/$(TOOLKITDIR)
	
	mkdir $(DISTDIR)/utils/ogl
	mkdir $(DISTDIR)/utils/ogl/src
	cp $(UTILSDIR)/ogl/Makefile.in $(DISTDIR)/utils/ogl
	cp $(UTILSDIR)/ogl/src/Makefile.in $(DISTDIR)/utils/ogl/src
	cp $(UTILSDIR)/ogl/src/*.h $(DISTDIR)/utils/ogl/src
	cp $(UTILSDIR)/ogl/src/*.cpp $(DISTDIR)/utils/ogl/src
	
MISC_DIST:
	mkdir $(DISTDIR)/misc
	mkdir $(DISTDIR)/misc/afm
	cp $(MISCDIR)/afm/*.afm  $(DISTDIR)/misc/afm
	mkdir $(DISTDIR)/misc/gs_afm
	cp $(MISCDIR)/gs_afm/*.afm  $(DISTDIR)/misc/gs_afm
	
dist: ALL_DIST @GUIDIST@ SAMPLES_DIST UTILS_DIST MISC_DIST
	cd _dist_dir; tar ch wx$(TOOLKIT) | gzip -f9 > $(WXARCHIVE); mv $(WXARCHIVE) ..
	$(RM) -r _dist_dir

clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) parser.c
	$(RM) lexer.c
	$(RM) ./lib/*

cleanall: clean
