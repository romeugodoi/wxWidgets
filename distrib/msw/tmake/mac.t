#!################################################################################
#! File:    mac.t
#! Purpose: tmake template file from which src/mac/files.lst containing the
#!          list of files for wxMac library is generated by tmake
#! Author:  Gilles Depeyrot
#! Created: 04.10.01
#! Version: $Id$
#!################################################################################
#${
    #! include the code which parses filelist.txt file and initializes
    #! %wxCommon, %wxGeneric, %wxHtml, %wxUNIX, %wxMAC, %wxMOTIF and
    #! %wxOS2PM hashes.
    IncludeTemplate("filelist.t");

    #! find all our sources
    #! MoreFiles sources
    $project{"GUIOBJS"} .= "DirectoryCopy.o ";
    $project{"GUIOBJS"} .= "FSpCompat.o ";
    $project{"GUIOBJS"} .= "FileCopy.o ";
    $project{"GUIOBJS"} .= "FullPath.o ";
    $project{"GUIOBJS"} .= "IterateDirectory.o ";
    $project{"GUIOBJS"} .= "MoreDesktopMgr.o ";
    $project{"GUIOBJS"} .= "MoreFiles.o ";
    $project{"GUIOBJS"} .= "MoreFilesExtras.o ";
    $project{"GUIOBJS"} .= "Search.o ";

    foreach $file (sort keys %wxGeneric) {
        next if $wxGeneric{$file} =~ /\bNotMac\b/;

        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"MAC_SOURCES"} .= "generic/" . $file . " ";
        $project{"GENERICOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxCommon) {
        next if $wxCommon{$file} =~ /\bNotMac\b/;

        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"MAC_SOURCES"} .= "common/" . $file . " ";
        $project{"COMMONOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxMAC) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"MAC_SOURCES"} .= "mac/" . $file . " ";
        $project{"GUIOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxUNIX) {
        next if $wxUNIX{$file} =~ /\bNotMac\b/;

        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"MAC_SOURCES"} .= "unix/" . $file . " ";
        $project{"UNIXOBJS"} .= $fileobj . " ";
    }

    foreach $file (sort keys %wxHTML) {
        ($fileobj = $file) =~ s/cp?p?$/\o/;

        $project{"MAC_SOURCES"} .= "html/" . $file . " ";
        $project{"HTMLOBJS"} .= $fileobj . " ";
    }
    #! find all our headers
    foreach $file (sort keys %wxWXINCLUDE) {
        next if $wxWXINCLUDE{$file} =~ /\bX\b/;

        $project{"MAC_HEADERS"} .= $file . " "
    }

    foreach $file (sort keys %wxMACINCLUDE) {
        $project{"MAC_HEADERS"} .= "mac/" . $file . " "
    }

    foreach $file (sort keys %wxGENERICINCLUDE) {
        $project{"MAC_HEADERS"} .= "generic/" . $file . " "
    }

    foreach $file (sort keys %wxUNIXINCLUDE) {
        $project{"MAC_HEADERS"} .= "unix/" . $file . " "
    }

    foreach $file (sort keys %wxHTMLINCLUDE) {
        $project{"MAC_HEADERS"} .= "html/" . $file . " "
    }

    foreach $file (sort keys %wxPROTOCOLINCLUDE) {
        $project{"MAC_HEADERS"} .= "protocol/" . $file . " "
    }

    foreach $file (sort keys %wxMACRESOURCE) {
        $project{"MACRESOURCES"} .= $file . " "
    }
#$}
# This file was automatically generated by tmake 
# DO NOT CHANGE THIS FILE, YOUR CHANGES WILL BE LOST! CHANGE MAC.T!
ALL_SOURCES = \
		#$ ExpandList("MAC_SOURCES");

ALL_HEADERS = \
		#$ ExpandList("MAC_HEADERS");

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

MACRESOURCES = \
		#$ ExpandList("MACRESOURCES");
