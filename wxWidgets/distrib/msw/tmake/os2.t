#!################################################################################
#! File:    os2.t
#! Purpose: tmake template file from which src/os2/files.lst containing the
#!          list of files for wxPM library is generated by tmake
#! Author:  Vadim Zeitlin
#!          modified by Stefan Neis for OS/2
#! Created: 28.01.00
#! Version: $Id$
#!################################################################################
#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric, %wxHtml, %wxUNIX, %wxGTK, %wxMOTIF and
    #! %wxOS2PM hashes.
    IncludeTemplate("filelist.t");

    #! find all our sources
    $project{"COMMONOBJS"} .= "parser.o ";

    foreach $file (sort keys %wxGeneric) {
        next if $wxGeneric{$file} =~ /\bP\b/;

        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"OS2PM_SOURCES"} .= "generic/" . $file . " ";
        $project{"GENERICOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxCommon) {
        next if $wxCommon{$file} =~ /\bP\b/;

        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"OS2PM_SOURCES"} .= "common/" . $file . " ";
        $project{"COMMONOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxOS2PM) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"OS2PM_SOURCES"} .= "os2/" . $file . " ";
        $project{"GUIOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxHTML) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"OS2PM_SOURCES"} .= "html/" . $file . " ";
        $project{"HTMLOBJS"} .= $fileobj . " ";
    }
    #! find all our headers
    foreach $file (sort keys %wxWXINCLUDE) {
        next if $wxWXINCLUDE{$file} =~ /\bP\b/;

        $project{"OS2PM_HEADERS"} .= $file . " "
    }

    foreach $file (sort keys %wxOS2PMINCLUDE) {
        $project{"OS2PM_HEADERS"} .= "os2/" . $file . " "
    }

    foreach $file (sort keys %wxGENERICINCLUDE) {
        $project{"OS2PM_HEADERS"} .= "generic/" . $file . " "
    }

    foreach $file (sort keys %wxHTMLINCLUDE) {
        $project{"OS2PM_HEADERS"} .= "html/" . $file . " "
    }

    foreach $file (sort keys %wxPROTOCOLINCLUDE) {
        $project{"OS2PM_HEADERS"} .= "protocol/" . $file . " "
    }
#$}
# This file was automatically generated by tmake 
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE OS2.T!
ALL_SOURCES = \
		#$ ExpandList("OS2PM_SOURCES");

ALL_HEADERS = \
		#$ ExpandList("OS2PM_HEADERS");

COMMONOBJS = \
		#$ ExpandList("COMMONOBJS");

GENERICOBJS = \
		#$ ExpandList("GENERICOBJS");

GUIOBJS = \
		#$ ExpandList("GUIOBJS");

UNIXOBJS = \
		#$ ExpandList("UNIXOBJS");

HTMLOBJS = \
		#$ ExpandList("HTMLOBJS");

