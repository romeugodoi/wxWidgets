
import wx
from wx.lib.evtmgr import eventManager

class FoldOutWindow(wx.PopupWindow):
    def __init__(self,parent,style=0):
        wx.PopupWindow.__init__(self,parent,style)
        self.SetAutoLayout(True)
        self.sizer=wx.BoxSizer(wx.HORIZONTAL)
        self.SetSizer(self.sizer, deleteOld=False)
        self.handlers={}
        self.InitColors()
        self.inWindow=False
        wx.EVT_ENTER_WINDOW(self,self.evEnter)
        wx.EVT_LEAVE_WINDOW(self,self.evLeave)
        
    def InitColors(self):
        faceClr      = wx.SystemSettings_GetSystemColour(wx.SYS_COLOUR_WINDOW)
        self.SetBackgroundColour(faceClr)

    def AddButton(self,bitmap,handler=None):
        id=wx.NewId()
        btn=wx.BitmapButton(self,id,bitmap)
        self.sizer.Add(btn, 1, wx.ALIGN_CENTER|wx.ALL|wx.EXPAND, 2)
        wx.EVT_BUTTON(self,id,self.OnBtnClick)
        self.sizer.Fit(self)
        self.Layout()
        if handler:
            self.handlers[id]=handler
        return id

    def Popup(self):
        if not self.IsShown():
            self.Show()

    def OnBtnClick(self,event):
        id=event.GetEventObject().GetId()
        if self.handlers.has_key(id):
            self.handlers[id](event)
        self.Hide()
        self.inWindow=False
        event.Skip()

    def evEnter(self,event):
        self.inWindow=True
        self.rect=self.GetRect()
        event.Skip()
        
    def evLeave(self,event):
        if self.inWindow:
            if not self.rect.Inside(self.ClientToScreen(event.GetPosition())):
                self.Hide()
        event.Skip()


        

        
class FoldOutMenu(wx.BitmapButton):
    def __init__(self,parent,id,bitmap,pos = wx.DefaultPosition,
                 size = wx.DefaultSize, style = wx.BU_AUTODRAW,
                 validator = wx.DefaultValidator, name = "button"):
        wx.BitmapButton.__init__(self,parent,id,bitmap,pos = wx.DefaultPosition,
                                 size = wx.DefaultSize, style = wx.BU_AUTODRAW,
                                 validator = wx.DefaultValidator, name = "button")
        self.parent=parent
        wx.EVT_BUTTON(self.parent, self.GetId(), self.click)
        self.popwin=FoldOutWindow(self.parent)

    def AddButton(self,bitmap,handler=None):
        return self.popwin.AddButton(bitmap,handler=handler)

    def click(self,event):
        pos=self.GetPosition()
        sz=self.GetSize()
        pos.x=pos.x+sz.width
        pos.y=pos.y+sz.height/2
        self.popwin.Position(pos,sz)
        self.popwin.Popup()
