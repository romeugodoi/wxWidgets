#
# Please note that wx.lib.floatbar is not formally supported as
# part of wxPython. If it works, fine. If not, unfortunate.
# GTK users can use the wx.TB_DOCKABLE flag with a regular
# wx.ToolBar, but everyone else has to take thier chances.
#

import  wx
import  wx.lib.floatbar

import  images


class TestFloatBar(wx.Frame):
    def __init__(self, parent, log):
        wx.Frame.__init__(
            self, parent, -1, 'Test ToolBar', wx.DefaultPosition, (500, 300)
            )

        self.log = log

        win = wx.Window(self, -1)
        win.SetBackgroundColour("WHITE")
        wx.StaticText(
            win, -1, "Drag the toolbar to float it,\n"  
            "Toggle the last tool to remove\nthe title.", (15,15)
            )

        tb = wx.lib.floatbar.FloatBar(self, -1)
        self.SetToolBar(tb)
        tb.SetFloatable(1)
        tb.SetTitle("Floating!")
        self.CreateStatusBar()

        tb.AddSimpleTool(10, images.getNewBitmap(), "New", "Long help for 'New'")
        self.Bind(wx.EVT_TOOL, self.OnToolClick, id=10)
        self.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolRClick, id=10)

        tb.AddSimpleTool(20, images.getOpenBitmap(), "Open")
        self.Bind(wx.EVT_TOOL, self.OnToolClick, id=20)
        self.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolRClick, id=20)

        tb.AddSeparator()
        tb.AddSimpleTool(30, images.getCopyBitmap(), "Copy")
        self.Bind(wx.EVT_TOOL, self.OnToolClick, id=30)
        self.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolRClick, id=30)

        tb.AddSimpleTool(40, images.getPasteBitmap(), "Paste")
        self.Bind(wx.EVT_TOOL, self.OnToolClick, id=40)
        self.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolRClick, id=40)

        tb.AddSeparator()

        tb.AddCheckTool(60, images.getTog1Bitmap(), images.getTog2Bitmap())
        self.Bind(wx.EVT_TOOL, self.OnToolClick, id=60)
        self.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolRClick, id=60)

        tb.Realize()

        self.tb = tb
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)


    def OnCloseWindow(self, event):
        self.Destroy()

    def OnToolClick(self, event):
        self.log.WriteText("tool %s clicked\n" % event.GetId())

        if event.GetId() == 60:
            print event.GetExtraLong(), event.IsChecked(), event.GetInt(), self.tb.GetToolState(60)

            if event.GetExtraLong():
                self.tb.SetTitle("")
            else:
                self.tb.SetTitle("Floating!")

    def OnToolRClick(self, event):
        self.log.WriteText("tool %s right-clicked\n" % event.GetId())

#---------------------------------------------------------------------------

def runTest(frame, nb, log):
    if wx.Platform == "__WXMAC__":
        dlg = wx.MessageDialog(
                frame, 'FloatBar does not work well on this platform.',
                'Sorry', wx.OK | wx.ICON_INFORMATION
                )
        dlg.ShowModal()
        dlg.Destroy()
    else:
        win = TestFloatBar(frame, log)
        frame.otherWin = win
        win.Show(True)

#---------------------------------------------------------------------------

overview = """\
FloatBar is a subclass of wx.ToolBar, implemented in Python, which
can be detached from its frame.

Drag the toolbar with the mouse to make it float, and drag it back, or
close it to make the toolbar return to its original position.

"""

if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])













