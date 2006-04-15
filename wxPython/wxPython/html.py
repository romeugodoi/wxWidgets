## This file reverse renames symbols in the wx package to give
## them their wx prefix again, for backwards compatibility.
##
## Generated by BuildRenamers in config.py

# This silly stuff here is so the wxPython.wx module doesn't conflict
# with the wx package.  We need to import modules from the wx package
# here, then we'll put the wxPython.wx entry back in sys.modules.
import sys
_wx = None
if sys.modules.has_key('wxPython.wx'):
    _wx = sys.modules['wxPython.wx']
    del sys.modules['wxPython.wx']

import wx.html

sys.modules['wxPython.wx'] = _wx
del sys, _wx


# Now assign all the reverse-renamed names:
wxHtmlWindowNameStr = wx.html.HtmlWindowNameStr
wxHtmlPrintoutTitleStr = wx.html.HtmlPrintoutTitleStr
wxHtmlPrintingTitleStr = wx.html.HtmlPrintingTitleStr
wxHTML_ALIGN_LEFT = wx.html.HTML_ALIGN_LEFT
wxHTML_ALIGN_CENTER = wx.html.HTML_ALIGN_CENTER
wxHTML_ALIGN_RIGHT = wx.html.HTML_ALIGN_RIGHT
wxHTML_ALIGN_BOTTOM = wx.html.HTML_ALIGN_BOTTOM
wxHTML_ALIGN_TOP = wx.html.HTML_ALIGN_TOP
wxHTML_CLR_FOREGROUND = wx.html.HTML_CLR_FOREGROUND
wxHTML_CLR_BACKGROUND = wx.html.HTML_CLR_BACKGROUND
wxHTML_UNITS_PIXELS = wx.html.HTML_UNITS_PIXELS
wxHTML_UNITS_PERCENT = wx.html.HTML_UNITS_PERCENT
wxHTML_INDENT_LEFT = wx.html.HTML_INDENT_LEFT
wxHTML_INDENT_RIGHT = wx.html.HTML_INDENT_RIGHT
wxHTML_INDENT_TOP = wx.html.HTML_INDENT_TOP
wxHTML_INDENT_BOTTOM = wx.html.HTML_INDENT_BOTTOM
wxHTML_INDENT_HORIZONTAL = wx.html.HTML_INDENT_HORIZONTAL
wxHTML_INDENT_VERTICAL = wx.html.HTML_INDENT_VERTICAL
wxHTML_INDENT_ALL = wx.html.HTML_INDENT_ALL
wxHTML_COND_ISANCHOR = wx.html.HTML_COND_ISANCHOR
wxHTML_COND_ISIMAGEMAP = wx.html.HTML_COND_ISIMAGEMAP
wxHTML_COND_USER = wx.html.HTML_COND_USER
wxHTML_FONT_SIZE_1 = wx.html.HTML_FONT_SIZE_1
wxHTML_FONT_SIZE_2 = wx.html.HTML_FONT_SIZE_2
wxHTML_FONT_SIZE_3 = wx.html.HTML_FONT_SIZE_3
wxHTML_FONT_SIZE_4 = wx.html.HTML_FONT_SIZE_4
wxHTML_FONT_SIZE_5 = wx.html.HTML_FONT_SIZE_5
wxHTML_FONT_SIZE_6 = wx.html.HTML_FONT_SIZE_6
wxHTML_FONT_SIZE_7 = wx.html.HTML_FONT_SIZE_7
wxHW_SCROLLBAR_NEVER = wx.html.HW_SCROLLBAR_NEVER
wxHW_SCROLLBAR_AUTO = wx.html.HW_SCROLLBAR_AUTO
wxHW_NO_SELECTION = wx.html.HW_NO_SELECTION
wxHW_DEFAULT_STYLE = wx.html.HW_DEFAULT_STYLE
wxHTML_OPEN = wx.html.HTML_OPEN
wxHTML_BLOCK = wx.html.HTML_BLOCK
wxHTML_REDIRECT = wx.html.HTML_REDIRECT
wxHTML_URL_PAGE = wx.html.HTML_URL_PAGE
wxHTML_URL_IMAGE = wx.html.HTML_URL_IMAGE
wxHTML_URL_OTHER = wx.html.HTML_URL_OTHER
wxHtmlLinkInfo = wx.html.HtmlLinkInfo
wxHtmlTag = wx.html.HtmlTag
wxHtmlParser = wx.html.HtmlParser
wxHtmlWinParser = wx.html.HtmlWinParser
wxHtmlTagHandler = wx.html.HtmlTagHandler
wxHtmlTagHandler = wx.html.HtmlTagHandler
wxHtmlWinTagHandler = wx.html.HtmlWinTagHandler
wxHtmlWinTagHandler = wx.html.HtmlWinTagHandler
wxHtmlWinParser_AddTagHandler = wx.html.HtmlWinParser_AddTagHandler
wxHtmlSelection = wx.html.HtmlSelection
wxHTML_SEL_OUT = wx.html.HTML_SEL_OUT
wxHTML_SEL_IN = wx.html.HTML_SEL_IN
wxHTML_SEL_CHANGING = wx.html.HTML_SEL_CHANGING
wxHtmlRenderingState = wx.html.HtmlRenderingState
wxHtmlRenderingStyle = wx.html.HtmlRenderingStyle
wxDefaultHtmlRenderingStyle = wx.html.DefaultHtmlRenderingStyle
wxHtmlRenderingInfo = wx.html.HtmlRenderingInfo
wxHTML_FIND_EXACT = wx.html.HTML_FIND_EXACT
wxHTML_FIND_NEAREST_BEFORE = wx.html.HTML_FIND_NEAREST_BEFORE
wxHTML_FIND_NEAREST_AFTER = wx.html.HTML_FIND_NEAREST_AFTER
wxHtmlCell = wx.html.HtmlCell
wxHtmlWordCell = wx.html.HtmlWordCell
wxHtmlContainerCell = wx.html.HtmlContainerCell
wxHtmlColourCell = wx.html.HtmlColourCell
wxHtmlFontCell = wx.html.HtmlFontCell
wxHtmlWidgetCell = wx.html.HtmlWidgetCell
wxHtmlFilter = wx.html.HtmlFilter
wxHtmlFilter = wx.html.HtmlFilter
wxHtmlWindowInterface = wx.html.HtmlWindowInterface
wxHtmlWindow = wx.html.HtmlWindow
wxHtmlWindow = wx.html.HtmlWindow
wxPreHtmlWindow = wx.html.PreHtmlWindow
wxHtmlWindow_AddFilter = wx.html.HtmlWindow_AddFilter
wxHtmlWindow_GetClassDefaultAttributes = wx.html.HtmlWindow_GetClassDefaultAttributes
wxHtmlWindow_GetDefaultHTMLCursor = wx.html.HtmlWindow_GetDefaultHTMLCursor
wxHtmlDCRenderer = wx.html.HtmlDCRenderer
wxPAGE_ODD = wx.html.PAGE_ODD
wxPAGE_EVEN = wx.html.PAGE_EVEN
wxPAGE_ALL = wx.html.PAGE_ALL
wxHtmlPrintout = wx.html.HtmlPrintout
wxHtmlPrintout_AddFilter = wx.html.HtmlPrintout_AddFilter
wxHtmlPrintout_CleanUpStatics = wx.html.HtmlPrintout_CleanUpStatics
wxHtmlEasyPrinting = wx.html.HtmlEasyPrinting
wxHtmlBookRecord = wx.html.HtmlBookRecord
wxHtmlSearchStatus = wx.html.HtmlSearchStatus
wxHtmlHelpData = wx.html.HtmlHelpData
wxHF_TOOLBAR = wx.html.HF_TOOLBAR
wxHF_CONTENTS = wx.html.HF_CONTENTS
wxHF_INDEX = wx.html.HF_INDEX
wxHF_SEARCH = wx.html.HF_SEARCH
wxHF_BOOKMARKS = wx.html.HF_BOOKMARKS
wxHF_OPEN_FILES = wx.html.HF_OPEN_FILES
wxHF_PRINT = wx.html.HF_PRINT
wxHF_FLAT_TOOLBAR = wx.html.HF_FLAT_TOOLBAR
wxHF_MERGE_BOOKS = wx.html.HF_MERGE_BOOKS
wxHF_ICONS_BOOK = wx.html.HF_ICONS_BOOK
wxHF_ICONS_BOOK_CHAPTER = wx.html.HF_ICONS_BOOK_CHAPTER
wxHF_ICONS_FOLDER = wx.html.HF_ICONS_FOLDER
wxHF_DEFAULT_STYLE = wx.html.HF_DEFAULT_STYLE
wxHF_EMBEDDED = wx.html.HF_EMBEDDED
wxHF_DIALOG = wx.html.HF_DIALOG
wxHF_FRAME = wx.html.HF_FRAME
wxHF_MODAL = wx.html.HF_MODAL
wxID_HTML_PANEL = wx.html.ID_HTML_PANEL
wxID_HTML_BACK = wx.html.ID_HTML_BACK
wxID_HTML_FORWARD = wx.html.ID_HTML_FORWARD
wxID_HTML_UPNODE = wx.html.ID_HTML_UPNODE
wxID_HTML_UP = wx.html.ID_HTML_UP
wxID_HTML_DOWN = wx.html.ID_HTML_DOWN
wxID_HTML_PRINT = wx.html.ID_HTML_PRINT
wxID_HTML_OPENFILE = wx.html.ID_HTML_OPENFILE
wxID_HTML_OPTIONS = wx.html.ID_HTML_OPTIONS
wxID_HTML_BOOKMARKSLIST = wx.html.ID_HTML_BOOKMARKSLIST
wxID_HTML_BOOKMARKSADD = wx.html.ID_HTML_BOOKMARKSADD
wxID_HTML_BOOKMARKSREMOVE = wx.html.ID_HTML_BOOKMARKSREMOVE
wxID_HTML_TREECTRL = wx.html.ID_HTML_TREECTRL
wxID_HTML_INDEXPAGE = wx.html.ID_HTML_INDEXPAGE
wxID_HTML_INDEXLIST = wx.html.ID_HTML_INDEXLIST
wxID_HTML_INDEXTEXT = wx.html.ID_HTML_INDEXTEXT
wxID_HTML_INDEXBUTTON = wx.html.ID_HTML_INDEXBUTTON
wxID_HTML_INDEXBUTTONALL = wx.html.ID_HTML_INDEXBUTTONALL
wxID_HTML_NOTEBOOK = wx.html.ID_HTML_NOTEBOOK
wxID_HTML_SEARCHPAGE = wx.html.ID_HTML_SEARCHPAGE
wxID_HTML_SEARCHTEXT = wx.html.ID_HTML_SEARCHTEXT
wxID_HTML_SEARCHLIST = wx.html.ID_HTML_SEARCHLIST
wxID_HTML_SEARCHBUTTON = wx.html.ID_HTML_SEARCHBUTTON
wxID_HTML_SEARCHCHOICE = wx.html.ID_HTML_SEARCHCHOICE
wxID_HTML_COUNTINFO = wx.html.ID_HTML_COUNTINFO
wxHtmlHelpWindow = wx.html.HtmlHelpWindow
wxPreHtmlHelpWindow = wx.html.PreHtmlHelpWindow
wxHtmlWindowEvent = wx.html.HtmlWindowEvent
wxHtmlHelpFrame = wx.html.HtmlHelpFrame
wxPreHtmlHelpFrame = wx.html.PreHtmlHelpFrame
wxHtmlHelpDialog = wx.html.HtmlHelpDialog
wxPreHtmlHelpDialog = wx.html.PreHtmlHelpDialog
wxHelpControllerBase = wx.html.HelpControllerBase
wxHtmlHelpController = wx.html.HtmlHelpController
wxHtmlModalHelp = wx.html.HtmlModalHelp


