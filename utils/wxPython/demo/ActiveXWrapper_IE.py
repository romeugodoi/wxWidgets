"""
"""

from wxPython.wx import *

if wxPlatform == '__WXMSW__':
    from wxPython.lib.activexwrapper import MakeActiveXClass
    import win32com.client.gencache

    try:
        browserModule = win32com.client.gencache.EnsureModule("{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}", 0, 1, 1)
    except:
        raise ImportError("IE4 or greater does not appear to be installed.")


#----------------------------------------------------------------------

class TestPanel(wxWindow):
    def __init__(self, parent, log, frame=None):
        wxWindow.__init__(self, parent, -1)#, style=wxCLIP_CHILDREN)
        self.log = log
        self.current = "http://alldunn.com/"
        self.frame = frame
        if frame:
            self.titleBase = frame.GetTitle()


        sizer = wxBoxSizer(wxVERTICAL)
        btnSizer = wxBoxSizer(wxHORIZONTAL)

        # Make a new class that derives from the WebBrowser class in the
        # COM module imported above.  This class also derives from wxWindow and
        # implements the machinery needed to integrate the two worlds.
        theClass = MakeActiveXClass(browserModule.WebBrowser,
                                    eventObj = self)

        # Create an instance of that class
        self.ie = theClass(self, -1, style=wxSUNKEN_BORDER)


        btn = wxButton(self, wxNewId(), " Open ")
        EVT_BUTTON(self, btn.GetId(), self.OnOpenButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 5)

        btn = wxButton(self, wxNewId(), " <-- ")
        EVT_BUTTON(self, btn.GetId(), self.OnPrevPageButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 5)

        btn = wxButton(self, wxNewId(), " --> ")
        EVT_BUTTON(self, btn.GetId(), self.OnNextPageButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 5)

        txt = wxStaticText(self, -1, "Location:")
        btnSizer.Add(txt, 0, wxCENTER|wxALL, 5)

        self.location = wxComboBox(self, wxNewId(), "", style=wxCB_DROPDOWN)
        EVT_COMBOBOX(self, self.location.GetId(), self.OnLocationSelect)
        EVT_KEY_UP(self.location, self.OnLocationKey)
        #EVT_CHAR(self.location, self.IgnoreReturn)
        btnSizer.Add(self.location, 1, wxEXPAND|wxALL, 5)

        sizer.Add(btnSizer, 0, wxEXPAND)
        sizer.Add(self.ie, 1, wxEXPAND)

        self.ie.Navigate(self.current)
        self.location.Append(self.current)

        self.SetSizer(sizer)
        self.SetAutoLayout(true)


    def OnSize(self, evt):
        self.Layout()

    def __del__(self):
        self.ie.Cleanup()
        self.ie = None

    def OnLocationSelect(self, evt):
        url = self.location.GetStringSelection()
        self.log.write('OnLocationSelect: %s\n' % url)
        self.ie.Navigate(url)

    def OnLocationKey(self, evt):
        if evt.KeyCode() == WXK_RETURN:
            URL = self.location.GetValue()
            self.location.Append(URL)
            self.ie.Navigate(URL)
        else:
            evt.Skip()

    def IgnoreReturn(self, evt):
        print 'IgnoreReturn'
        if evt.KeyCode() != WXK_RETURN:
            evt.Skip()

    def OnOpenButton(self, event):
        dlg = wxTextEntryDialog(self, "Open Location",
                                "Enter a full URL or local path",
                                self.current, wxOK|wxCANCEL)
        dlg.CentreOnParent()
        if dlg.ShowModal() == wxID_OK:
            self.current = dlg.GetValue()
            self.ie.Navigate(self.current)
        dlg.Destroy()


    def OnPrevPageButton(self, event):
        self.ie.GoBack()


    def OnNextPageButton(self, event):
        self.ie.GoForward()


    # The following event handlers are called by the web browser COM
    # control since  we passed self to MakeActiveXClass.  It will look
    # here for matching attributes and call them if they exist.  See the
    # module generated by makepy for details of method names, etc.
    def OnBeforeNavigate2(self, pDisp, URL, *args):
        self.log.write('OnBeforeNavigate2: %s\n' % URL)

    def OnNavigateComplete2(self, pDisp, URL):
        self.log.write('OnNavigateComplete2: %s\n' % URL)
        self.current = URL
        self.location.SetValue(URL)

    def OnTitleChange(self, text):
        self.log.write('OnTitleChange: %s\n' % text)
        if self.frame:
            self.frame.SetTitle(self.titleBase + ' -- ' + text)

    def OnStatusTextChange(self, text):
        self.log.write('OnStatusTextChange: %s\n' % text)
        if self.frame:
            self.frame.SetStatusText(text)


#----------------------------------------------------------------------
# for the demo framework...

def runTest(frame, nb, log):
    if wxPlatform == '__WXMSW__':
        win = TestPanel(nb, log, frame)
        return win
    else:
        dlg = wxMessageDialog(frame, 'This demo only works on MSW.',
                          'Sorry', wxOK | wxICON_INFORMATION)
        dlg.ShowModal()
        dlg.Destroy()


overview = __doc__

#----------------------------------------------------------------------


if __name__ == '__main__':
    class TestFrame(wxFrame):
        def __init__(self):
            wxFrame.__init__(self, None, -1, "ActiveX test -- Internet Explorer",
                             size=(640, 480),
                             style=wxDEFAULT_FRAME_STYLE|wxNO_FULL_REPAINT_ON_RESIZE)
            self.CreateStatusBar()
            self.tp = TestPanel(self, sys.stdout, self)

        def OnCloseWindow(self, event):
            self.tp.ie.Cleanup()
            self.Destroy()


    app = wxPySimpleApp()
    frame = TestFrame()
    frame.Show(true)
    app.MainLoop()



