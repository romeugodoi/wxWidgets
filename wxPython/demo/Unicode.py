

from wxPython.wx import *

#----------------------------------------------------------------------

# Some unicode strings
chi_uni = (u'Python \u662f\u6700\u597d\u7684\u7de8\u7a0b\u8a9e\u8a00\uff01',
            'Python is the best\nprogramming language!')

lt1_uni = (u'Pythonas yra \u017eaviausia \u0161neka',
            'Python is the best')
lt2_uni = (u'A\u0161 m\u0117gstu \u0161okolad\u0105',
            'I like chocolate')

kor_uni = (u'\ud30c\uc774\uc36c\uc740 \ucd5c\uace0\uc758 \ud504\ub85c\uadf8\ub798\ubc0d \uc5b8\uc5b4\uc774\ub2e4!',
           'Python is the best\nprogramming language!')

bul_uni = (u'\u041f\u0438\u0442\u043e\u043d \u0435 \u043d\u0430\u0439-\u0434\u043e\u0431\u0440\u0438\u044f \u043f\u0440\u043e\u0433\u0440\u0430\u043c\u0435\u043d \u0435\u0437\u0438\u043a!',
           'Python is the best\nprogramming language!')
rus_uni = (u'\u041f\u0438\u0442\u043e\u043d - \u043b\u0443\u0447\u0448\u0438\u0439 \u044f\u0437\u044b\u043a \n\u043f\u0440\u043e\u0433\u0440\u0430\u043c\u043c\u0438\u0440\u043e\u0432\u0430\u043d\u0438\u044f!',
           'Python is the best\nprogramming language!')


# Equivalents in UTF-8.  Should I demo these somehow???
chi_utf8 = ('Python \xe6\x98\xaf\xe6\x9c\x80\xe5\xa5\xbd\xe7\x9a\x84\xe7\xb7\xa8\xe7\xa8\x8b\xe8\xaa\x9e\xe8\xa8\x80\xef\xbc\x81',
            'Python is the best programming language')

lt1_utf8 = ('Pythonas yra \xc5\xbeaviausia \xc5\xa1neka',
            'Python is the best')
lt2_utf8 = ('A\xc5\xa1 m\xc4\x97gstu \xc5\xa1okolad\xc4\x85',
            'I like chocolate')

kor_utf8 = ('\xed\x8c\x8c\xec\x9d\xb4\xec\x8d\xac\xec\x9d\x80 \xec\xb5\x9c\xea\xb3\xa0\xec\x9d\x98 \xed\x94\x84\xeb\xa1\x9c\xea\xb7\xb8\xeb\x9e\x98\xeb\xb0\x8d \xec\x96\xb8\xec\x96\xb4\xec\x9d\xb4\xeb\x8b\xa4!',
            'Python is the best programming language!')

bul_utf8 = ('\xd0\x9f\xd0\xb8\xd1\x82\xd0\xbe\xd0\xbd \xd0\xb5 \xd0\xbd\xd0\xb0\xd0\xb9-\xd0\xb4\xd0\xbe\xd0\xb1\xd1\x80\xd0\xb8\xd1\x8f \xd0\xbf\xd1\x80\xd0\xbe\xd0\xb3\xd1\x80\xd0\xb0\xd0\xbc\xd0\xb5\xd0\xbd \xd0\xb5\xd0\xb7\xd0\xb8\xd0\xba!',
            'Python is the best programming language!')
rus_utf8 = ('\xd0\x9f\xd0\xb8\xd1\x82\xd0\xbe\xd0\xbd - \xd0\xbb\xd1\x83\xd1\x87\xd1\x88\xd0\xb8\xd0\xb9 \xd1\x8f\xd0\xb7\xd1\x8b\xd0\xba \xd0\xbf\xd1\x80\xd0\xbe\xd0\xb3\xd1\x80\xd0\xb0\xd0\xbc\xd0\xbc\xd0\xb8\xd1\x80\xd0\xbe\xd0\xb2\xd0\xb0\xd0\xbd\xd0\xb8\xd1\x8f!',
            'Python is the best programming language!')

#----------------------------------------------------------------------

class TestPanel(wxPanel):
    def __init__(self, parent, log):
        self.log = log
        wxPanel.__init__(self, parent, -1)

        box = wxBoxSizer(wxVERTICAL)

        if not wxUSE_UNICODE:
            self.AddLine(box)
            self.AddText(box, "Sorry, this wxPython was not built with Unicode support.",
                         font = wxFont(12, wxSWISS, wxNORMAL, wxBOLD))
            self.AddLine(box)

        else:
            f = self.GetFont()
            font = wxFont(14, f.GetFamily(), f.GetStyle(), wxBOLD, False,
                          f.GetFaceName(), f.GetEncoding())

            self.AddLine(box)
            self.AddText(box, chi_uni[0], chi_uni[1], 'Chinese:', font)
            self.AddLine(box)

            self.AddText(box, lt1_uni[0], lt1_uni[1], 'Lithuanian:', font)
            self.AddLine(box)
            self.AddText(box, lt2_uni[0], lt2_uni[1], 'Lithuanian:', font)
            self.AddLine(box)

            self.AddText(box, kor_uni[0], kor_uni[1], 'Korean:', font)
            self.AddLine(box)

            self.AddText(box, bul_uni[0], bul_uni[1], 'Bulgarian:', font)
            self.AddLine(box)
            self.AddText(box, rus_uni[0], rus_uni[1], 'Russian:', font)
            self.AddLine(box)


        border = wxBoxSizer(wxVERTICAL)
        border.Add(box, 1, wxEXPAND|wxALL, 10)
        self.SetAutoLayout(True)
        self.SetSizer(border)


    def AddLine(self, sizer):
        sizer.Add(wxStaticLine(self, -1), 0, wxEXPAND)

    def AddText(self, sizer, text1, text2='', lang='', font=None):
        # create some controls
        lang  = wxStaticText(self, -1, lang)
        text1 = wxStaticText(self, -1, text1)
        text2 = wxStaticText(self, -1, text2, style=wxALIGN_RIGHT)
        if font is not None:
            text1.SetFont(font)

        # put them in a sizer
        row = wxBoxSizer(wxHORIZONTAL)
        row.Add(lang)
        row.Add(15,10)
        row.Add(text1, 1, wxEXPAND)
        row.Add(text2)

        # put the row in the main sizer
        sizer.Add(row, 0, wxEXPAND|wxALL, 5)


#----------------------------------------------------------------------

def runTest(frame, nb, log):
    win = TestPanel(nb, log)
    return win

#----------------------------------------------------------------------



overview = """<html><body>
<h2><center>wxPython Unicode Support</center></h2>

wxWindows and wxPython can be compiled with unicode support enabled or
disabled.  Previous to wxPython 2.3.3 non-unicode mode was always
used.  Starting with 2.3.3 either mode is supported, but only if it is
also available in wxWindow on the platform.  Currently wxWindows only
supports unicode on MS Windows platforms, but with the recent release
of GTK+ 2.0 it is only a matter of time until it can be done on wxGTK
(Linux and other unixes) as well.
<p>
When unicode is enabled, then all functions and methods in wxPython
that return a wxString from the C++ function will return a Python
unicode object, and parameters to C++ functions/methods that expect a
wxString can accept either a Python string or unicode object.  If a
string object is passed then it will be decoded into unicode using the
converter pointed to by wxConvCurrent, which will use the default
system encoding.  If you need to use string in some other encoding
then you should convert it to unicode using the Python codecs first
and then pass the unicode to the wxPython method.


</body></html>
"""




if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])])

