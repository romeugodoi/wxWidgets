# Microsoft Developer Studio Project File - Name="wxrc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=wxrc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxrc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxrc.mak" CFG="wxrc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxrc - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Universal Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Universal Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Unicode Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Unicode Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Universal Unicode Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Universal Unicode Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Universal Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Universal Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Unicode Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Unicode Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wxrc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxrc - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivudll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivudll"
# PROP Intermediate_Dir "vc_mswunivudll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivudll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivudll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivu" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivu" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivudll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivudll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivuddll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivuddll"
# PROP Intermediate_Dir "vc_mswunivuddll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivuddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivuddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivud" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivud" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivuddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivuddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivdll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivdll"
# PROP Intermediate_Dir "vc_mswunivdll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivdll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswuniv" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivdll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswuniv" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswuniv" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswuniv" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivdll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivdll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivddll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivddll"
# PROP Intermediate_Dir "vc_mswunivddll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswunivd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivd" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswunivd" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswudll"
# PROP BASE Intermediate_Dir "vc_mswudll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswudll"
# PROP Intermediate_Dir "vc_mswudll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswudll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswudll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswu" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswu" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswudll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswudll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswuddll"
# PROP BASE Intermediate_Dir "vc_mswuddll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswuddll"
# PROP Intermediate_Dir "vc_mswuddll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswuddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswuddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswud" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswud" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswdll"
# PROP BASE Intermediate_Dir "vc_mswdll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswdll"
# PROP Intermediate_Dir "vc_mswdll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswdll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\msw" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswdll\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\msw" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\msw" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\msw" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswdll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswdll\wxrc.exe" /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswddll"
# PROP BASE Intermediate_Dir "vc_mswddll\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswddll"
# PROP Intermediate_Dir "vc_mswddll\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswddll\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_dll\mswd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswd" /i "." /d "WXUSINGDLL" /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_dll\mswd" /i "." /d "WXUSINGDLL" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console
# ADD LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswddll\wxrc.exe" /debug /libpath:".\..\..\lib\vc_dll" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivu"
# PROP BASE Intermediate_Dir "vc_mswunivu\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivu"
# PROP Intermediate_Dir "vc_mswunivu\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivu\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivu\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivu" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivu" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivu\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivu\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivud"
# PROP BASE Intermediate_Dir "vc_mswunivud\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivud"
# PROP Intermediate_Dir "vc_mswunivud\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivud\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivud\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivud" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivud" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivud\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivud\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswuniv"
# PROP BASE Intermediate_Dir "vc_mswuniv\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswuniv"
# PROP Intermediate_Dir "vc_mswuniv\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswuniv\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswuniv" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswuniv\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswuniv" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswuniv" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswuniv" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuniv\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuniv\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivd"
# PROP BASE Intermediate_Dir "vc_mswunivd\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivd"
# PROP Intermediate_Dir "vc_mswunivd\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivd\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswunivd\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswunivd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivd" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswunivd" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivd\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivd\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswu"
# PROP BASE Intermediate_Dir "vc_mswu\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswu"
# PROP Intermediate_Dir "vc_mswu\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswu\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswu\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswu" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswu" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswu" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswu\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25u_xml.lib wxbase25u.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregexu25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswu\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswud"
# PROP BASE Intermediate_Dir "vc_mswud\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswud"
# PROP Intermediate_Dir "vc_mswud\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswud\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswud\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswud" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswud" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswud" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswud\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25ud_xml.lib wxbase25ud.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexud25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswud\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_msw"
# PROP BASE Intermediate_Dir "vc_msw\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_msw"
# PROP Intermediate_Dir "vc_msw\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_msw\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\msw" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdvc_msw\wxrc.pdb /O1 /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\msw" /W4 /I "." /D "WIN32" /D "__WXMSW__" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "__WXMSW__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\msw" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "__WXMSW__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\msw" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_msw\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25_xml.lib wxbase25.lib wxtiff25.lib wxjpeg25.lib wxpng25.lib wxzlib25.lib wxregex25.lib wxexpat25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_msw\wxrc.exe" /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ELSEIF  "$(CFG)" == "wxrc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswd"
# PROP BASE Intermediate_Dir "vc_mswd\wxrc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswd"
# PROP Intermediate_Dir "vc_mswd\wxrc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswd\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvc_mswd\wxrc.pdb /Od /GR /GX /I ".\..\..\include" /I ".\..\..\lib\vc_lib\mswd" /W4 /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswd" /i "." /d _CONSOLE
# ADD RSC /l 0x405 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\..\..\include" /i ".\..\..\lib\vc_lib\mswd" /i "." /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswd\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console
# ADD LINK32 wxbase25d_xml.lib wxbase25d.lib wxtiffd25.lib wxjpegd25.lib wxpngd25.lib wxzlibd25.lib wxregexd25.lib wxexpatd25.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswd\wxrc.exe" /debug /libpath:".\..\..\lib\vc_lib" /subsystem:console

!ENDIF

# Begin Target

# Name "wxrc - Win32 DLL Universal Unicode Release"
# Name "wxrc - Win32 DLL Universal Unicode Debug"
# Name "wxrc - Win32 DLL Universal Release"
# Name "wxrc - Win32 DLL Universal Debug"
# Name "wxrc - Win32 DLL Unicode Release"
# Name "wxrc - Win32 DLL Unicode Debug"
# Name "wxrc - Win32 DLL Release"
# Name "wxrc - Win32 DLL Debug"
# Name "wxrc - Win32 Universal Unicode Release"
# Name "wxrc - Win32 Universal Unicode Debug"
# Name "wxrc - Win32 Universal Release"
# Name "wxrc - Win32 Universal Debug"
# Name "wxrc - Win32 Unicode Release"
# Name "wxrc - Win32 Unicode Debug"
# Name "wxrc - Win32 Release"
# Name "wxrc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wxrc.cpp
# End Source File
# End Group
# End Target
# End Project

