# This file was created automatically by SWIG.
import framesc

from misc import *

from gdi import *

from windows import *

from clip_dnd import *

from stattool import *

from controls import *

from events import *
import wx
class wxTopLevelWindowPtr(wxWindowPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_Create,(self,) + _args, _kwargs)
        return val
    def Maximize(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_Maximize,(self,) + _args, _kwargs)
        return val
    def Restore(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_Restore,(self,) + _args, _kwargs)
        return val
    def Iconize(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_Iconize,(self,) + _args, _kwargs)
        return val
    def IsMaximized(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_IsMaximized,(self,) + _args, _kwargs)
        return val
    def IsIconized(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_IsIconized,(self,) + _args, _kwargs)
        return val
    def GetIcon(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_GetIcon,(self,) + _args, _kwargs)
        if val: val = wxIconPtr(val) 
        return val
    def SetIcon(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_SetIcon,(self,) + _args, _kwargs)
        return val
    def ShowFullScreen(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_ShowFullScreen,(self,) + _args, _kwargs)
        return val
    def IsFullScreen(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_IsFullScreen,(self,) + _args, _kwargs)
        return val
    def SetTitle(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_SetTitle,(self,) + _args, _kwargs)
        return val
    def GetTitle(self, *_args, **_kwargs):
        val = apply(framesc.wxTopLevelWindow_GetTitle,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxTopLevelWindow instance at %s>" % (self.this,)
class wxTopLevelWindow(wxTopLevelWindowPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(framesc.new_wxTopLevelWindow,_args,_kwargs)
        self.thisown = 1



def wxPreTopLevelWindow(*_args,**_kwargs):
    val = wxTopLevelWindowPtr(apply(framesc.new_wxPreTopLevelWindow,_args,_kwargs))
    val.thisown = 1
    return val


class wxFramePtr(wxTopLevelWindowPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_Create,(self,) + _args, _kwargs)
        return val
    def GetClientAreaOrigin(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_GetClientAreaOrigin,(self,) + _args, _kwargs)
        if val: val = wxPointPtr(val) ; val.thisown = 1
        return val
    def SetMenuBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_SetMenuBar,(self,) + _args, _kwargs)
        return val
    def GetMenuBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_GetMenuBar,(self,) + _args, _kwargs)
        return val
    def Command(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_Command,(self,) + _args, _kwargs)
        return val
    def ProcessCommand(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_ProcessCommand,(self,) + _args, _kwargs)
        return val
    def CreateStatusBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_CreateStatusBar,(self,) + _args, _kwargs)
        return val
    def GetStatusBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_GetStatusBar,(self,) + _args, _kwargs)
        return val
    def SetStatusBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_SetStatusBar,(self,) + _args, _kwargs)
        return val
    def SetStatusText(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_SetStatusText,(self,) + _args, _kwargs)
        return val
    def SetStatusWidths(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_SetStatusWidths,(self,) + _args, _kwargs)
        return val
    def CreateToolBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_CreateToolBar,(self,) + _args, _kwargs)
        return val
    def GetToolBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_GetToolBar,(self,) + _args, _kwargs)
        return val
    def SetToolBar(self, *_args, **_kwargs):
        val = apply(framesc.wxFrame_SetToolBar,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxFrame instance at %s>" % (self.this,)
class wxFrame(wxFramePtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(framesc.new_wxFrame,_args,_kwargs)
        self.thisown = 1



def wxPreFrame(*_args,**_kwargs):
    val = wxFramePtr(apply(framesc.new_wxPreFrame,_args,_kwargs))
    val.thisown = 1
    return val


class wxDialogPtr(wxTopLevelWindowPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_Create,(self,) + _args, _kwargs)
        return val
    def Centre(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_Centre,(self,) + _args, _kwargs)
        return val
    def EndModal(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_EndModal,(self,) + _args, _kwargs)
        return val
    def SetModal(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_SetModal,(self,) + _args, _kwargs)
        return val
    def IsModal(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_IsModal,(self,) + _args, _kwargs)
        return val
    def ShowModal(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_ShowModal,(self,) + _args, _kwargs)
        return val
    def GetReturnCode(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_GetReturnCode,(self,) + _args, _kwargs)
        return val
    def SetReturnCode(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_SetReturnCode,(self,) + _args, _kwargs)
        return val
    def CreateTextSizer(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_CreateTextSizer,(self,) + _args, _kwargs)
        return val
    def CreateButtonSizer(self, *_args, **_kwargs):
        val = apply(framesc.wxDialog_CreateButtonSizer,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxDialog instance at %s>" % (self.this,)
class wxDialog(wxDialogPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(framesc.new_wxDialog,_args,_kwargs)
        self.thisown = 1



def wxPreDialog(*_args,**_kwargs):
    val = wxDialogPtr(apply(framesc.new_wxPreDialog,_args,_kwargs))
    val.thisown = 1
    return val


class wxMiniFramePtr(wxFramePtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = apply(framesc.wxMiniFrame_Create,(self,) + _args, _kwargs)
        return val
    def __repr__(self):
        return "<C wxMiniFrame instance at %s>" % (self.this,)
class wxMiniFrame(wxMiniFramePtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(framesc.new_wxMiniFrame,_args,_kwargs)
        self.thisown = 1



def wxPreMiniFrame(*_args,**_kwargs):
    val = wxMiniFramePtr(apply(framesc.new_wxPreMiniFrame,_args,_kwargs))
    val.thisown = 1
    return val


class wxTipWindowPtr(wxFramePtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __repr__(self):
        return "<C wxTipWindow instance at %s>" % (self.this,)
class wxTipWindow(wxTipWindowPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = apply(framesc.new_wxTipWindow,_args,_kwargs)
        self.thisown = 1






#-------------- FUNCTION WRAPPERS ------------------



#-------------- VARIABLE WRAPPERS ------------------

wxFULLSCREEN_NOMENUBAR = framesc.wxFULLSCREEN_NOMENUBAR
wxFULLSCREEN_NOTOOLBAR = framesc.wxFULLSCREEN_NOTOOLBAR
wxFULLSCREEN_NOSTATUSBAR = framesc.wxFULLSCREEN_NOSTATUSBAR
wxFULLSCREEN_NOBORDER = framesc.wxFULLSCREEN_NOBORDER
wxFULLSCREEN_NOCAPTION = framesc.wxFULLSCREEN_NOCAPTION
wxFULLSCREEN_ALL = framesc.wxFULLSCREEN_ALL
wxTOPLEVEL_EX_DIALOG = framesc.wxTOPLEVEL_EX_DIALOG
