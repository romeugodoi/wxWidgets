## This file reverse renames symbols in the wx package to give
## them their wx prefix again, for backwards compatibility.
##
## Generated by ./distrib/build_renamers.py

# This silly stuff here is so the wxPython.wx module doesn't conflict
# with the wx package.  We need to import modules from the wx package
# here, then we'll put the entry back in sys.modules.
import sys
_wx = None
if sys.modules.has_key('wxPython.wx'):
    _wx = sys.modules['wxPython.wx']
    del sys.modules['wxPython.wx']

import wx.stc

sys.modules['wxPython.wx'] = _wx
del sys, _wx


# Now assign all the reverse-renamed names:
STC_USE_DND = wx.stc.STC_USE_DND
wxSTC_USE_POPUP = wx.stc.STC_USE_POPUP
wxSTC_INVALID_POSITION = wx.stc.STC_INVALID_POSITION
wxSTC_START = wx.stc.STC_START
wxSTC_OPTIONAL_START = wx.stc.STC_OPTIONAL_START
wxSTC_LEXER_START = wx.stc.STC_LEXER_START
wxSTC_WS_INVISIBLE = wx.stc.STC_WS_INVISIBLE
wxSTC_WS_VISIBLEALWAYS = wx.stc.STC_WS_VISIBLEALWAYS
wxSTC_WS_VISIBLEAFTERINDENT = wx.stc.STC_WS_VISIBLEAFTERINDENT
wxSTC_EOL_CRLF = wx.stc.STC_EOL_CRLF
wxSTC_EOL_CR = wx.stc.STC_EOL_CR
wxSTC_EOL_LF = wx.stc.STC_EOL_LF
wxSTC_CP_UTF8 = wx.stc.STC_CP_UTF8
wxSTC_CP_DBCS = wx.stc.STC_CP_DBCS
wxSTC_MARKER_MAX = wx.stc.STC_MARKER_MAX
wxSTC_MARK_CIRCLE = wx.stc.STC_MARK_CIRCLE
wxSTC_MARK_ROUNDRECT = wx.stc.STC_MARK_ROUNDRECT
wxSTC_MARK_ARROW = wx.stc.STC_MARK_ARROW
wxSTC_MARK_SMALLRECT = wx.stc.STC_MARK_SMALLRECT
wxSTC_MARK_SHORTARROW = wx.stc.STC_MARK_SHORTARROW
wxSTC_MARK_EMPTY = wx.stc.STC_MARK_EMPTY
wxSTC_MARK_ARROWDOWN = wx.stc.STC_MARK_ARROWDOWN
wxSTC_MARK_MINUS = wx.stc.STC_MARK_MINUS
wxSTC_MARK_PLUS = wx.stc.STC_MARK_PLUS
wxSTC_MARK_VLINE = wx.stc.STC_MARK_VLINE
wxSTC_MARK_LCORNER = wx.stc.STC_MARK_LCORNER
wxSTC_MARK_TCORNER = wx.stc.STC_MARK_TCORNER
wxSTC_MARK_BOXPLUS = wx.stc.STC_MARK_BOXPLUS
wxSTC_MARK_BOXPLUSCONNECTED = wx.stc.STC_MARK_BOXPLUSCONNECTED
wxSTC_MARK_BOXMINUS = wx.stc.STC_MARK_BOXMINUS
wxSTC_MARK_BOXMINUSCONNECTED = wx.stc.STC_MARK_BOXMINUSCONNECTED
wxSTC_MARK_LCORNERCURVE = wx.stc.STC_MARK_LCORNERCURVE
wxSTC_MARK_TCORNERCURVE = wx.stc.STC_MARK_TCORNERCURVE
wxSTC_MARK_CIRCLEPLUS = wx.stc.STC_MARK_CIRCLEPLUS
wxSTC_MARK_CIRCLEPLUSCONNECTED = wx.stc.STC_MARK_CIRCLEPLUSCONNECTED
wxSTC_MARK_CIRCLEMINUS = wx.stc.STC_MARK_CIRCLEMINUS
wxSTC_MARK_CIRCLEMINUSCONNECTED = wx.stc.STC_MARK_CIRCLEMINUSCONNECTED
wxSTC_MARK_BACKGROUND = wx.stc.STC_MARK_BACKGROUND
wxSTC_MARK_DOTDOTDOT = wx.stc.STC_MARK_DOTDOTDOT
wxSTC_MARK_ARROWS = wx.stc.STC_MARK_ARROWS
wxSTC_MARK_PIXMAP = wx.stc.STC_MARK_PIXMAP
wxSTC_MARK_CHARACTER = wx.stc.STC_MARK_CHARACTER
wxSTC_MARKNUM_FOLDEREND = wx.stc.STC_MARKNUM_FOLDEREND
wxSTC_MARKNUM_FOLDEROPENMID = wx.stc.STC_MARKNUM_FOLDEROPENMID
wxSTC_MARKNUM_FOLDERMIDTAIL = wx.stc.STC_MARKNUM_FOLDERMIDTAIL
wxSTC_MARKNUM_FOLDERTAIL = wx.stc.STC_MARKNUM_FOLDERTAIL
wxSTC_MARKNUM_FOLDERSUB = wx.stc.STC_MARKNUM_FOLDERSUB
wxSTC_MARKNUM_FOLDER = wx.stc.STC_MARKNUM_FOLDER
wxSTC_MARKNUM_FOLDEROPEN = wx.stc.STC_MARKNUM_FOLDEROPEN
wxSTC_MASK_FOLDERS = wx.stc.STC_MASK_FOLDERS
wxSTC_MARGIN_SYMBOL = wx.stc.STC_MARGIN_SYMBOL
wxSTC_MARGIN_NUMBER = wx.stc.STC_MARGIN_NUMBER
wxSTC_STYLE_DEFAULT = wx.stc.STC_STYLE_DEFAULT
wxSTC_STYLE_LINENUMBER = wx.stc.STC_STYLE_LINENUMBER
wxSTC_STYLE_BRACELIGHT = wx.stc.STC_STYLE_BRACELIGHT
wxSTC_STYLE_BRACEBAD = wx.stc.STC_STYLE_BRACEBAD
wxSTC_STYLE_CONTROLCHAR = wx.stc.STC_STYLE_CONTROLCHAR
wxSTC_STYLE_INDENTGUIDE = wx.stc.STC_STYLE_INDENTGUIDE
wxSTC_STYLE_LASTPREDEFINED = wx.stc.STC_STYLE_LASTPREDEFINED
wxSTC_STYLE_MAX = wx.stc.STC_STYLE_MAX
wxSTC_CHARSET_ANSI = wx.stc.STC_CHARSET_ANSI
wxSTC_CHARSET_DEFAULT = wx.stc.STC_CHARSET_DEFAULT
wxSTC_CHARSET_BALTIC = wx.stc.STC_CHARSET_BALTIC
wxSTC_CHARSET_CHINESEBIG5 = wx.stc.STC_CHARSET_CHINESEBIG5
wxSTC_CHARSET_EASTEUROPE = wx.stc.STC_CHARSET_EASTEUROPE
wxSTC_CHARSET_GB2312 = wx.stc.STC_CHARSET_GB2312
wxSTC_CHARSET_GREEK = wx.stc.STC_CHARSET_GREEK
wxSTC_CHARSET_HANGUL = wx.stc.STC_CHARSET_HANGUL
wxSTC_CHARSET_MAC = wx.stc.STC_CHARSET_MAC
wxSTC_CHARSET_OEM = wx.stc.STC_CHARSET_OEM
wxSTC_CHARSET_RUSSIAN = wx.stc.STC_CHARSET_RUSSIAN
wxSTC_CHARSET_SHIFTJIS = wx.stc.STC_CHARSET_SHIFTJIS
wxSTC_CHARSET_SYMBOL = wx.stc.STC_CHARSET_SYMBOL
wxSTC_CHARSET_TURKISH = wx.stc.STC_CHARSET_TURKISH
wxSTC_CHARSET_JOHAB = wx.stc.STC_CHARSET_JOHAB
wxSTC_CHARSET_HEBREW = wx.stc.STC_CHARSET_HEBREW
wxSTC_CHARSET_ARABIC = wx.stc.STC_CHARSET_ARABIC
wxSTC_CHARSET_VIETNAMESE = wx.stc.STC_CHARSET_VIETNAMESE
wxSTC_CHARSET_THAI = wx.stc.STC_CHARSET_THAI
wxSTC_CASE_MIXED = wx.stc.STC_CASE_MIXED
wxSTC_CASE_UPPER = wx.stc.STC_CASE_UPPER
wxSTC_CASE_LOWER = wx.stc.STC_CASE_LOWER
wxSTC_INDIC_MAX = wx.stc.STC_INDIC_MAX
wxSTC_INDIC_PLAIN = wx.stc.STC_INDIC_PLAIN
wxSTC_INDIC_SQUIGGLE = wx.stc.STC_INDIC_SQUIGGLE
wxSTC_INDIC_TT = wx.stc.STC_INDIC_TT
wxSTC_INDIC_DIAGONAL = wx.stc.STC_INDIC_DIAGONAL
wxSTC_INDIC_STRIKE = wx.stc.STC_INDIC_STRIKE
wxSTC_INDIC_HIDDEN = wx.stc.STC_INDIC_HIDDEN
wxSTC_INDIC0_MASK = wx.stc.STC_INDIC0_MASK
wxSTC_INDIC1_MASK = wx.stc.STC_INDIC1_MASK
wxSTC_INDIC2_MASK = wx.stc.STC_INDIC2_MASK
wxSTC_INDICS_MASK = wx.stc.STC_INDICS_MASK
wxSTC_PRINT_NORMAL = wx.stc.STC_PRINT_NORMAL
wxSTC_PRINT_INVERTLIGHT = wx.stc.STC_PRINT_INVERTLIGHT
wxSTC_PRINT_BLACKONWHITE = wx.stc.STC_PRINT_BLACKONWHITE
wxSTC_PRINT_COLOURONWHITE = wx.stc.STC_PRINT_COLOURONWHITE
wxSTC_PRINT_COLOURONWHITEDEFAULTBG = wx.stc.STC_PRINT_COLOURONWHITEDEFAULTBG
wxSTC_FIND_WHOLEWORD = wx.stc.STC_FIND_WHOLEWORD
wxSTC_FIND_MATCHCASE = wx.stc.STC_FIND_MATCHCASE
wxSTC_FIND_WORDSTART = wx.stc.STC_FIND_WORDSTART
wxSTC_FIND_REGEXP = wx.stc.STC_FIND_REGEXP
wxSTC_FIND_POSIX = wx.stc.STC_FIND_POSIX
wxSTC_FOLDLEVELBASE = wx.stc.STC_FOLDLEVELBASE
wxSTC_FOLDLEVELWHITEFLAG = wx.stc.STC_FOLDLEVELWHITEFLAG
wxSTC_FOLDLEVELHEADERFLAG = wx.stc.STC_FOLDLEVELHEADERFLAG
wxSTC_FOLDLEVELBOXHEADERFLAG = wx.stc.STC_FOLDLEVELBOXHEADERFLAG
wxSTC_FOLDLEVELBOXFOOTERFLAG = wx.stc.STC_FOLDLEVELBOXFOOTERFLAG
wxSTC_FOLDLEVELCONTRACTED = wx.stc.STC_FOLDLEVELCONTRACTED
wxSTC_FOLDLEVELUNINDENT = wx.stc.STC_FOLDLEVELUNINDENT
wxSTC_FOLDLEVELNUMBERMASK = wx.stc.STC_FOLDLEVELNUMBERMASK
wxSTC_FOLDFLAG_LINEBEFORE_EXPANDED = wx.stc.STC_FOLDFLAG_LINEBEFORE_EXPANDED
wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED = wx.stc.STC_FOLDFLAG_LINEBEFORE_CONTRACTED
wxSTC_FOLDFLAG_LINEAFTER_EXPANDED = wx.stc.STC_FOLDFLAG_LINEAFTER_EXPANDED
wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED = wx.stc.STC_FOLDFLAG_LINEAFTER_CONTRACTED
wxSTC_FOLDFLAG_LEVELNUMBERS = wx.stc.STC_FOLDFLAG_LEVELNUMBERS
wxSTC_FOLDFLAG_BOX = wx.stc.STC_FOLDFLAG_BOX
wxSTC_TIME_FOREVER = wx.stc.STC_TIME_FOREVER
wxSTC_WRAP_NONE = wx.stc.STC_WRAP_NONE
wxSTC_WRAP_WORD = wx.stc.STC_WRAP_WORD
wxSTC_CACHE_NONE = wx.stc.STC_CACHE_NONE
wxSTC_CACHE_CARET = wx.stc.STC_CACHE_CARET
wxSTC_CACHE_PAGE = wx.stc.STC_CACHE_PAGE
wxSTC_CACHE_DOCUMENT = wx.stc.STC_CACHE_DOCUMENT
wxSTC_EDGE_NONE = wx.stc.STC_EDGE_NONE
wxSTC_EDGE_LINE = wx.stc.STC_EDGE_LINE
wxSTC_EDGE_BACKGROUND = wx.stc.STC_EDGE_BACKGROUND
wxSTC_CURSORNORMAL = wx.stc.STC_CURSORNORMAL
wxSTC_CURSORWAIT = wx.stc.STC_CURSORWAIT
wxSTC_VISIBLE_SLOP = wx.stc.STC_VISIBLE_SLOP
wxSTC_VISIBLE_STRICT = wx.stc.STC_VISIBLE_STRICT
wxSTC_CARET_SLOP = wx.stc.STC_CARET_SLOP
wxSTC_CARET_STRICT = wx.stc.STC_CARET_STRICT
wxSTC_CARET_JUMPS = wx.stc.STC_CARET_JUMPS
wxSTC_CARET_EVEN = wx.stc.STC_CARET_EVEN
wxSTC_KEYWORDSET_MAX = wx.stc.STC_KEYWORDSET_MAX
wxSTC_MOD_INSERTTEXT = wx.stc.STC_MOD_INSERTTEXT
wxSTC_MOD_DELETETEXT = wx.stc.STC_MOD_DELETETEXT
wxSTC_MOD_CHANGESTYLE = wx.stc.STC_MOD_CHANGESTYLE
wxSTC_MOD_CHANGEFOLD = wx.stc.STC_MOD_CHANGEFOLD
wxSTC_PERFORMED_USER = wx.stc.STC_PERFORMED_USER
wxSTC_PERFORMED_UNDO = wx.stc.STC_PERFORMED_UNDO
wxSTC_PERFORMED_REDO = wx.stc.STC_PERFORMED_REDO
wxSTC_LASTSTEPINUNDOREDO = wx.stc.STC_LASTSTEPINUNDOREDO
wxSTC_MOD_CHANGEMARKER = wx.stc.STC_MOD_CHANGEMARKER
wxSTC_MOD_BEFOREINSERT = wx.stc.STC_MOD_BEFOREINSERT
wxSTC_MOD_BEFOREDELETE = wx.stc.STC_MOD_BEFOREDELETE
wxSTC_MODEVENTMASKALL = wx.stc.STC_MODEVENTMASKALL
wxSTC_KEY_DOWN = wx.stc.STC_KEY_DOWN
wxSTC_KEY_UP = wx.stc.STC_KEY_UP
wxSTC_KEY_LEFT = wx.stc.STC_KEY_LEFT
wxSTC_KEY_RIGHT = wx.stc.STC_KEY_RIGHT
wxSTC_KEY_HOME = wx.stc.STC_KEY_HOME
wxSTC_KEY_END = wx.stc.STC_KEY_END
wxSTC_KEY_PRIOR = wx.stc.STC_KEY_PRIOR
wxSTC_KEY_NEXT = wx.stc.STC_KEY_NEXT
wxSTC_KEY_DELETE = wx.stc.STC_KEY_DELETE
wxSTC_KEY_INSERT = wx.stc.STC_KEY_INSERT
wxSTC_KEY_ESCAPE = wx.stc.STC_KEY_ESCAPE
wxSTC_KEY_BACK = wx.stc.STC_KEY_BACK
wxSTC_KEY_TAB = wx.stc.STC_KEY_TAB
wxSTC_KEY_RETURN = wx.stc.STC_KEY_RETURN
wxSTC_KEY_ADD = wx.stc.STC_KEY_ADD
wxSTC_KEY_SUBTRACT = wx.stc.STC_KEY_SUBTRACT
wxSTC_KEY_DIVIDE = wx.stc.STC_KEY_DIVIDE
wxSTC_SCMOD_SHIFT = wx.stc.STC_SCMOD_SHIFT
wxSTC_SCMOD_CTRL = wx.stc.STC_SCMOD_CTRL
wxSTC_SCMOD_ALT = wx.stc.STC_SCMOD_ALT
wxSTC_LEX_CONTAINER = wx.stc.STC_LEX_CONTAINER
wxSTC_LEX_NULL = wx.stc.STC_LEX_NULL
wxSTC_LEX_PYTHON = wx.stc.STC_LEX_PYTHON
wxSTC_LEX_CPP = wx.stc.STC_LEX_CPP
wxSTC_LEX_HTML = wx.stc.STC_LEX_HTML
wxSTC_LEX_XML = wx.stc.STC_LEX_XML
wxSTC_LEX_PERL = wx.stc.STC_LEX_PERL
wxSTC_LEX_SQL = wx.stc.STC_LEX_SQL
wxSTC_LEX_VB = wx.stc.STC_LEX_VB
wxSTC_LEX_PROPERTIES = wx.stc.STC_LEX_PROPERTIES
wxSTC_LEX_ERRORLIST = wx.stc.STC_LEX_ERRORLIST
wxSTC_LEX_MAKEFILE = wx.stc.STC_LEX_MAKEFILE
wxSTC_LEX_BATCH = wx.stc.STC_LEX_BATCH
wxSTC_LEX_XCODE = wx.stc.STC_LEX_XCODE
wxSTC_LEX_LATEX = wx.stc.STC_LEX_LATEX
wxSTC_LEX_LUA = wx.stc.STC_LEX_LUA
wxSTC_LEX_DIFF = wx.stc.STC_LEX_DIFF
wxSTC_LEX_CONF = wx.stc.STC_LEX_CONF
wxSTC_LEX_PASCAL = wx.stc.STC_LEX_PASCAL
wxSTC_LEX_AVE = wx.stc.STC_LEX_AVE
wxSTC_LEX_ADA = wx.stc.STC_LEX_ADA
wxSTC_LEX_LISP = wx.stc.STC_LEX_LISP
wxSTC_LEX_RUBY = wx.stc.STC_LEX_RUBY
wxSTC_LEX_EIFFEL = wx.stc.STC_LEX_EIFFEL
wxSTC_LEX_EIFFELKW = wx.stc.STC_LEX_EIFFELKW
wxSTC_LEX_TCL = wx.stc.STC_LEX_TCL
wxSTC_LEX_NNCRONTAB = wx.stc.STC_LEX_NNCRONTAB
wxSTC_LEX_BULLANT = wx.stc.STC_LEX_BULLANT
wxSTC_LEX_VBSCRIPT = wx.stc.STC_LEX_VBSCRIPT
wxSTC_LEX_ASP = wx.stc.STC_LEX_ASP
wxSTC_LEX_PHP = wx.stc.STC_LEX_PHP
wxSTC_LEX_BAAN = wx.stc.STC_LEX_BAAN
wxSTC_LEX_MATLAB = wx.stc.STC_LEX_MATLAB
wxSTC_LEX_SCRIPTOL = wx.stc.STC_LEX_SCRIPTOL
wxSTC_LEX_ASM = wx.stc.STC_LEX_ASM
wxSTC_LEX_CPPNOCASE = wx.stc.STC_LEX_CPPNOCASE
wxSTC_LEX_FORTRAN = wx.stc.STC_LEX_FORTRAN
wxSTC_LEX_F77 = wx.stc.STC_LEX_F77
wxSTC_LEX_CSS = wx.stc.STC_LEX_CSS
wxSTC_LEX_POV = wx.stc.STC_LEX_POV
wxSTC_LEX_LOUT = wx.stc.STC_LEX_LOUT
wxSTC_LEX_ESCRIPT = wx.stc.STC_LEX_ESCRIPT
wxSTC_LEX_PS = wx.stc.STC_LEX_PS
wxSTC_LEX_NSIS = wx.stc.STC_LEX_NSIS
wxSTC_LEX_MMIXAL = wx.stc.STC_LEX_MMIXAL
wxSTC_LEX_AUTOMATIC = wx.stc.STC_LEX_AUTOMATIC
wxSTC_P_DEFAULT = wx.stc.STC_P_DEFAULT
wxSTC_P_COMMENTLINE = wx.stc.STC_P_COMMENTLINE
wxSTC_P_NUMBER = wx.stc.STC_P_NUMBER
wxSTC_P_STRING = wx.stc.STC_P_STRING
wxSTC_P_CHARACTER = wx.stc.STC_P_CHARACTER
wxSTC_P_WORD = wx.stc.STC_P_WORD
wxSTC_P_TRIPLE = wx.stc.STC_P_TRIPLE
wxSTC_P_TRIPLEDOUBLE = wx.stc.STC_P_TRIPLEDOUBLE
wxSTC_P_CLASSNAME = wx.stc.STC_P_CLASSNAME
wxSTC_P_DEFNAME = wx.stc.STC_P_DEFNAME
wxSTC_P_OPERATOR = wx.stc.STC_P_OPERATOR
wxSTC_P_IDENTIFIER = wx.stc.STC_P_IDENTIFIER
wxSTC_P_COMMENTBLOCK = wx.stc.STC_P_COMMENTBLOCK
wxSTC_P_STRINGEOL = wx.stc.STC_P_STRINGEOL
wxSTC_C_DEFAULT = wx.stc.STC_C_DEFAULT
wxSTC_C_COMMENT = wx.stc.STC_C_COMMENT
wxSTC_C_COMMENTLINE = wx.stc.STC_C_COMMENTLINE
wxSTC_C_COMMENTDOC = wx.stc.STC_C_COMMENTDOC
wxSTC_C_NUMBER = wx.stc.STC_C_NUMBER
wxSTC_C_WORD = wx.stc.STC_C_WORD
wxSTC_C_STRING = wx.stc.STC_C_STRING
wxSTC_C_CHARACTER = wx.stc.STC_C_CHARACTER
wxSTC_C_UUID = wx.stc.STC_C_UUID
wxSTC_C_PREPROCESSOR = wx.stc.STC_C_PREPROCESSOR
wxSTC_C_OPERATOR = wx.stc.STC_C_OPERATOR
wxSTC_C_IDENTIFIER = wx.stc.STC_C_IDENTIFIER
wxSTC_C_STRINGEOL = wx.stc.STC_C_STRINGEOL
wxSTC_C_VERBATIM = wx.stc.STC_C_VERBATIM
wxSTC_C_REGEX = wx.stc.STC_C_REGEX
wxSTC_C_COMMENTLINEDOC = wx.stc.STC_C_COMMENTLINEDOC
wxSTC_C_WORD2 = wx.stc.STC_C_WORD2
wxSTC_C_COMMENTDOCKEYWORD = wx.stc.STC_C_COMMENTDOCKEYWORD
wxSTC_C_COMMENTDOCKEYWORDERROR = wx.stc.STC_C_COMMENTDOCKEYWORDERROR
wxSTC_C_GLOBALCLASS = wx.stc.STC_C_GLOBALCLASS
wxSTC_H_DEFAULT = wx.stc.STC_H_DEFAULT
wxSTC_H_TAG = wx.stc.STC_H_TAG
wxSTC_H_TAGUNKNOWN = wx.stc.STC_H_TAGUNKNOWN
wxSTC_H_ATTRIBUTE = wx.stc.STC_H_ATTRIBUTE
wxSTC_H_ATTRIBUTEUNKNOWN = wx.stc.STC_H_ATTRIBUTEUNKNOWN
wxSTC_H_NUMBER = wx.stc.STC_H_NUMBER
wxSTC_H_DOUBLESTRING = wx.stc.STC_H_DOUBLESTRING
wxSTC_H_SINGLESTRING = wx.stc.STC_H_SINGLESTRING
wxSTC_H_OTHER = wx.stc.STC_H_OTHER
wxSTC_H_COMMENT = wx.stc.STC_H_COMMENT
wxSTC_H_ENTITY = wx.stc.STC_H_ENTITY
wxSTC_H_TAGEND = wx.stc.STC_H_TAGEND
wxSTC_H_XMLSTART = wx.stc.STC_H_XMLSTART
wxSTC_H_XMLEND = wx.stc.STC_H_XMLEND
wxSTC_H_SCRIPT = wx.stc.STC_H_SCRIPT
wxSTC_H_ASP = wx.stc.STC_H_ASP
wxSTC_H_ASPAT = wx.stc.STC_H_ASPAT
wxSTC_H_CDATA = wx.stc.STC_H_CDATA
wxSTC_H_QUESTION = wx.stc.STC_H_QUESTION
wxSTC_H_VALUE = wx.stc.STC_H_VALUE
wxSTC_H_XCCOMMENT = wx.stc.STC_H_XCCOMMENT
wxSTC_H_SGML_DEFAULT = wx.stc.STC_H_SGML_DEFAULT
wxSTC_H_SGML_COMMAND = wx.stc.STC_H_SGML_COMMAND
wxSTC_H_SGML_1ST_PARAM = wx.stc.STC_H_SGML_1ST_PARAM
wxSTC_H_SGML_DOUBLESTRING = wx.stc.STC_H_SGML_DOUBLESTRING
wxSTC_H_SGML_SIMPLESTRING = wx.stc.STC_H_SGML_SIMPLESTRING
wxSTC_H_SGML_ERROR = wx.stc.STC_H_SGML_ERROR
wxSTC_H_SGML_SPECIAL = wx.stc.STC_H_SGML_SPECIAL
wxSTC_H_SGML_ENTITY = wx.stc.STC_H_SGML_ENTITY
wxSTC_H_SGML_COMMENT = wx.stc.STC_H_SGML_COMMENT
wxSTC_H_SGML_1ST_PARAM_COMMENT = wx.stc.STC_H_SGML_1ST_PARAM_COMMENT
wxSTC_H_SGML_BLOCK_DEFAULT = wx.stc.STC_H_SGML_BLOCK_DEFAULT
wxSTC_HJ_START = wx.stc.STC_HJ_START
wxSTC_HJ_DEFAULT = wx.stc.STC_HJ_DEFAULT
wxSTC_HJ_COMMENT = wx.stc.STC_HJ_COMMENT
wxSTC_HJ_COMMENTLINE = wx.stc.STC_HJ_COMMENTLINE
wxSTC_HJ_COMMENTDOC = wx.stc.STC_HJ_COMMENTDOC
wxSTC_HJ_NUMBER = wx.stc.STC_HJ_NUMBER
wxSTC_HJ_WORD = wx.stc.STC_HJ_WORD
wxSTC_HJ_KEYWORD = wx.stc.STC_HJ_KEYWORD
wxSTC_HJ_DOUBLESTRING = wx.stc.STC_HJ_DOUBLESTRING
wxSTC_HJ_SINGLESTRING = wx.stc.STC_HJ_SINGLESTRING
wxSTC_HJ_SYMBOLS = wx.stc.STC_HJ_SYMBOLS
wxSTC_HJ_STRINGEOL = wx.stc.STC_HJ_STRINGEOL
wxSTC_HJ_REGEX = wx.stc.STC_HJ_REGEX
wxSTC_HJA_START = wx.stc.STC_HJA_START
wxSTC_HJA_DEFAULT = wx.stc.STC_HJA_DEFAULT
wxSTC_HJA_COMMENT = wx.stc.STC_HJA_COMMENT
wxSTC_HJA_COMMENTLINE = wx.stc.STC_HJA_COMMENTLINE
wxSTC_HJA_COMMENTDOC = wx.stc.STC_HJA_COMMENTDOC
wxSTC_HJA_NUMBER = wx.stc.STC_HJA_NUMBER
wxSTC_HJA_WORD = wx.stc.STC_HJA_WORD
wxSTC_HJA_KEYWORD = wx.stc.STC_HJA_KEYWORD
wxSTC_HJA_DOUBLESTRING = wx.stc.STC_HJA_DOUBLESTRING
wxSTC_HJA_SINGLESTRING = wx.stc.STC_HJA_SINGLESTRING
wxSTC_HJA_SYMBOLS = wx.stc.STC_HJA_SYMBOLS
wxSTC_HJA_STRINGEOL = wx.stc.STC_HJA_STRINGEOL
wxSTC_HJA_REGEX = wx.stc.STC_HJA_REGEX
wxSTC_HB_START = wx.stc.STC_HB_START
wxSTC_HB_DEFAULT = wx.stc.STC_HB_DEFAULT
wxSTC_HB_COMMENTLINE = wx.stc.STC_HB_COMMENTLINE
wxSTC_HB_NUMBER = wx.stc.STC_HB_NUMBER
wxSTC_HB_WORD = wx.stc.STC_HB_WORD
wxSTC_HB_STRING = wx.stc.STC_HB_STRING
wxSTC_HB_IDENTIFIER = wx.stc.STC_HB_IDENTIFIER
wxSTC_HB_STRINGEOL = wx.stc.STC_HB_STRINGEOL
wxSTC_HBA_START = wx.stc.STC_HBA_START
wxSTC_HBA_DEFAULT = wx.stc.STC_HBA_DEFAULT
wxSTC_HBA_COMMENTLINE = wx.stc.STC_HBA_COMMENTLINE
wxSTC_HBA_NUMBER = wx.stc.STC_HBA_NUMBER
wxSTC_HBA_WORD = wx.stc.STC_HBA_WORD
wxSTC_HBA_STRING = wx.stc.STC_HBA_STRING
wxSTC_HBA_IDENTIFIER = wx.stc.STC_HBA_IDENTIFIER
wxSTC_HBA_STRINGEOL = wx.stc.STC_HBA_STRINGEOL
wxSTC_HP_START = wx.stc.STC_HP_START
wxSTC_HP_DEFAULT = wx.stc.STC_HP_DEFAULT
wxSTC_HP_COMMENTLINE = wx.stc.STC_HP_COMMENTLINE
wxSTC_HP_NUMBER = wx.stc.STC_HP_NUMBER
wxSTC_HP_STRING = wx.stc.STC_HP_STRING
wxSTC_HP_CHARACTER = wx.stc.STC_HP_CHARACTER
wxSTC_HP_WORD = wx.stc.STC_HP_WORD
wxSTC_HP_TRIPLE = wx.stc.STC_HP_TRIPLE
wxSTC_HP_TRIPLEDOUBLE = wx.stc.STC_HP_TRIPLEDOUBLE
wxSTC_HP_CLASSNAME = wx.stc.STC_HP_CLASSNAME
wxSTC_HP_DEFNAME = wx.stc.STC_HP_DEFNAME
wxSTC_HP_OPERATOR = wx.stc.STC_HP_OPERATOR
wxSTC_HP_IDENTIFIER = wx.stc.STC_HP_IDENTIFIER
wxSTC_HPA_START = wx.stc.STC_HPA_START
wxSTC_HPA_DEFAULT = wx.stc.STC_HPA_DEFAULT
wxSTC_HPA_COMMENTLINE = wx.stc.STC_HPA_COMMENTLINE
wxSTC_HPA_NUMBER = wx.stc.STC_HPA_NUMBER
wxSTC_HPA_STRING = wx.stc.STC_HPA_STRING
wxSTC_HPA_CHARACTER = wx.stc.STC_HPA_CHARACTER
wxSTC_HPA_WORD = wx.stc.STC_HPA_WORD
wxSTC_HPA_TRIPLE = wx.stc.STC_HPA_TRIPLE
wxSTC_HPA_TRIPLEDOUBLE = wx.stc.STC_HPA_TRIPLEDOUBLE
wxSTC_HPA_CLASSNAME = wx.stc.STC_HPA_CLASSNAME
wxSTC_HPA_DEFNAME = wx.stc.STC_HPA_DEFNAME
wxSTC_HPA_OPERATOR = wx.stc.STC_HPA_OPERATOR
wxSTC_HPA_IDENTIFIER = wx.stc.STC_HPA_IDENTIFIER
wxSTC_HPHP_DEFAULT = wx.stc.STC_HPHP_DEFAULT
wxSTC_HPHP_HSTRING = wx.stc.STC_HPHP_HSTRING
wxSTC_HPHP_SIMPLESTRING = wx.stc.STC_HPHP_SIMPLESTRING
wxSTC_HPHP_WORD = wx.stc.STC_HPHP_WORD
wxSTC_HPHP_NUMBER = wx.stc.STC_HPHP_NUMBER
wxSTC_HPHP_VARIABLE = wx.stc.STC_HPHP_VARIABLE
wxSTC_HPHP_COMMENT = wx.stc.STC_HPHP_COMMENT
wxSTC_HPHP_COMMENTLINE = wx.stc.STC_HPHP_COMMENTLINE
wxSTC_HPHP_HSTRING_VARIABLE = wx.stc.STC_HPHP_HSTRING_VARIABLE
wxSTC_HPHP_OPERATOR = wx.stc.STC_HPHP_OPERATOR
wxSTC_PL_DEFAULT = wx.stc.STC_PL_DEFAULT
wxSTC_PL_ERROR = wx.stc.STC_PL_ERROR
wxSTC_PL_COMMENTLINE = wx.stc.STC_PL_COMMENTLINE
wxSTC_PL_POD = wx.stc.STC_PL_POD
wxSTC_PL_NUMBER = wx.stc.STC_PL_NUMBER
wxSTC_PL_WORD = wx.stc.STC_PL_WORD
wxSTC_PL_STRING = wx.stc.STC_PL_STRING
wxSTC_PL_CHARACTER = wx.stc.STC_PL_CHARACTER
wxSTC_PL_PUNCTUATION = wx.stc.STC_PL_PUNCTUATION
wxSTC_PL_PREPROCESSOR = wx.stc.STC_PL_PREPROCESSOR
wxSTC_PL_OPERATOR = wx.stc.STC_PL_OPERATOR
wxSTC_PL_IDENTIFIER = wx.stc.STC_PL_IDENTIFIER
wxSTC_PL_SCALAR = wx.stc.STC_PL_SCALAR
wxSTC_PL_ARRAY = wx.stc.STC_PL_ARRAY
wxSTC_PL_HASH = wx.stc.STC_PL_HASH
wxSTC_PL_SYMBOLTABLE = wx.stc.STC_PL_SYMBOLTABLE
wxSTC_PL_REGEX = wx.stc.STC_PL_REGEX
wxSTC_PL_REGSUBST = wx.stc.STC_PL_REGSUBST
wxSTC_PL_LONGQUOTE = wx.stc.STC_PL_LONGQUOTE
wxSTC_PL_BACKTICKS = wx.stc.STC_PL_BACKTICKS
wxSTC_PL_DATASECTION = wx.stc.STC_PL_DATASECTION
wxSTC_PL_HERE_DELIM = wx.stc.STC_PL_HERE_DELIM
wxSTC_PL_HERE_Q = wx.stc.STC_PL_HERE_Q
wxSTC_PL_HERE_QQ = wx.stc.STC_PL_HERE_QQ
wxSTC_PL_HERE_QX = wx.stc.STC_PL_HERE_QX
wxSTC_PL_STRING_Q = wx.stc.STC_PL_STRING_Q
wxSTC_PL_STRING_QQ = wx.stc.STC_PL_STRING_QQ
wxSTC_PL_STRING_QX = wx.stc.STC_PL_STRING_QX
wxSTC_PL_STRING_QR = wx.stc.STC_PL_STRING_QR
wxSTC_PL_STRING_QW = wx.stc.STC_PL_STRING_QW
wxSTC_B_DEFAULT = wx.stc.STC_B_DEFAULT
wxSTC_B_COMMENT = wx.stc.STC_B_COMMENT
wxSTC_B_NUMBER = wx.stc.STC_B_NUMBER
wxSTC_B_KEYWORD = wx.stc.STC_B_KEYWORD
wxSTC_B_STRING = wx.stc.STC_B_STRING
wxSTC_B_PREPROCESSOR = wx.stc.STC_B_PREPROCESSOR
wxSTC_B_OPERATOR = wx.stc.STC_B_OPERATOR
wxSTC_B_IDENTIFIER = wx.stc.STC_B_IDENTIFIER
wxSTC_B_DATE = wx.stc.STC_B_DATE
wxSTC_PROPS_DEFAULT = wx.stc.STC_PROPS_DEFAULT
wxSTC_PROPS_COMMENT = wx.stc.STC_PROPS_COMMENT
wxSTC_PROPS_SECTION = wx.stc.STC_PROPS_SECTION
wxSTC_PROPS_ASSIGNMENT = wx.stc.STC_PROPS_ASSIGNMENT
wxSTC_PROPS_DEFVAL = wx.stc.STC_PROPS_DEFVAL
wxSTC_L_DEFAULT = wx.stc.STC_L_DEFAULT
wxSTC_L_COMMAND = wx.stc.STC_L_COMMAND
wxSTC_L_TAG = wx.stc.STC_L_TAG
wxSTC_L_MATH = wx.stc.STC_L_MATH
wxSTC_L_COMMENT = wx.stc.STC_L_COMMENT
wxSTC_LUA_DEFAULT = wx.stc.STC_LUA_DEFAULT
wxSTC_LUA_COMMENT = wx.stc.STC_LUA_COMMENT
wxSTC_LUA_COMMENTLINE = wx.stc.STC_LUA_COMMENTLINE
wxSTC_LUA_COMMENTDOC = wx.stc.STC_LUA_COMMENTDOC
wxSTC_LUA_NUMBER = wx.stc.STC_LUA_NUMBER
wxSTC_LUA_WORD = wx.stc.STC_LUA_WORD
wxSTC_LUA_STRING = wx.stc.STC_LUA_STRING
wxSTC_LUA_CHARACTER = wx.stc.STC_LUA_CHARACTER
wxSTC_LUA_LITERALSTRING = wx.stc.STC_LUA_LITERALSTRING
wxSTC_LUA_PREPROCESSOR = wx.stc.STC_LUA_PREPROCESSOR
wxSTC_LUA_OPERATOR = wx.stc.STC_LUA_OPERATOR
wxSTC_LUA_IDENTIFIER = wx.stc.STC_LUA_IDENTIFIER
wxSTC_LUA_STRINGEOL = wx.stc.STC_LUA_STRINGEOL
wxSTC_LUA_WORD2 = wx.stc.STC_LUA_WORD2
wxSTC_LUA_WORD3 = wx.stc.STC_LUA_WORD3
wxSTC_LUA_WORD4 = wx.stc.STC_LUA_WORD4
wxSTC_LUA_WORD5 = wx.stc.STC_LUA_WORD5
wxSTC_LUA_WORD6 = wx.stc.STC_LUA_WORD6
wxSTC_LUA_WORD7 = wx.stc.STC_LUA_WORD7
wxSTC_LUA_WORD8 = wx.stc.STC_LUA_WORD8
wxSTC_ERR_DEFAULT = wx.stc.STC_ERR_DEFAULT
wxSTC_ERR_PYTHON = wx.stc.STC_ERR_PYTHON
wxSTC_ERR_GCC = wx.stc.STC_ERR_GCC
wxSTC_ERR_MS = wx.stc.STC_ERR_MS
wxSTC_ERR_CMD = wx.stc.STC_ERR_CMD
wxSTC_ERR_BORLAND = wx.stc.STC_ERR_BORLAND
wxSTC_ERR_PERL = wx.stc.STC_ERR_PERL
wxSTC_ERR_NET = wx.stc.STC_ERR_NET
wxSTC_ERR_LUA = wx.stc.STC_ERR_LUA
wxSTC_ERR_CTAG = wx.stc.STC_ERR_CTAG
wxSTC_ERR_DIFF_CHANGED = wx.stc.STC_ERR_DIFF_CHANGED
wxSTC_ERR_DIFF_ADDITION = wx.stc.STC_ERR_DIFF_ADDITION
wxSTC_ERR_DIFF_DELETION = wx.stc.STC_ERR_DIFF_DELETION
wxSTC_ERR_DIFF_MESSAGE = wx.stc.STC_ERR_DIFF_MESSAGE
wxSTC_ERR_PHP = wx.stc.STC_ERR_PHP
wxSTC_ERR_ELF = wx.stc.STC_ERR_ELF
wxSTC_ERR_IFC = wx.stc.STC_ERR_IFC
wxSTC_BAT_DEFAULT = wx.stc.STC_BAT_DEFAULT
wxSTC_BAT_COMMENT = wx.stc.STC_BAT_COMMENT
wxSTC_BAT_WORD = wx.stc.STC_BAT_WORD
wxSTC_BAT_LABEL = wx.stc.STC_BAT_LABEL
wxSTC_BAT_HIDE = wx.stc.STC_BAT_HIDE
wxSTC_BAT_COMMAND = wx.stc.STC_BAT_COMMAND
wxSTC_BAT_IDENTIFIER = wx.stc.STC_BAT_IDENTIFIER
wxSTC_BAT_OPERATOR = wx.stc.STC_BAT_OPERATOR
wxSTC_MAKE_DEFAULT = wx.stc.STC_MAKE_DEFAULT
wxSTC_MAKE_COMMENT = wx.stc.STC_MAKE_COMMENT
wxSTC_MAKE_PREPROCESSOR = wx.stc.STC_MAKE_PREPROCESSOR
wxSTC_MAKE_IDENTIFIER = wx.stc.STC_MAKE_IDENTIFIER
wxSTC_MAKE_OPERATOR = wx.stc.STC_MAKE_OPERATOR
wxSTC_MAKE_TARGET = wx.stc.STC_MAKE_TARGET
wxSTC_MAKE_IDEOL = wx.stc.STC_MAKE_IDEOL
wxSTC_DIFF_DEFAULT = wx.stc.STC_DIFF_DEFAULT
wxSTC_DIFF_COMMENT = wx.stc.STC_DIFF_COMMENT
wxSTC_DIFF_COMMAND = wx.stc.STC_DIFF_COMMAND
wxSTC_DIFF_HEADER = wx.stc.STC_DIFF_HEADER
wxSTC_DIFF_POSITION = wx.stc.STC_DIFF_POSITION
wxSTC_DIFF_DELETED = wx.stc.STC_DIFF_DELETED
wxSTC_DIFF_ADDED = wx.stc.STC_DIFF_ADDED
wxSTC_CONF_DEFAULT = wx.stc.STC_CONF_DEFAULT
wxSTC_CONF_COMMENT = wx.stc.STC_CONF_COMMENT
wxSTC_CONF_NUMBER = wx.stc.STC_CONF_NUMBER
wxSTC_CONF_IDENTIFIER = wx.stc.STC_CONF_IDENTIFIER
wxSTC_CONF_EXTENSION = wx.stc.STC_CONF_EXTENSION
wxSTC_CONF_PARAMETER = wx.stc.STC_CONF_PARAMETER
wxSTC_CONF_STRING = wx.stc.STC_CONF_STRING
wxSTC_CONF_OPERATOR = wx.stc.STC_CONF_OPERATOR
wxSTC_CONF_IP = wx.stc.STC_CONF_IP
wxSTC_CONF_DIRECTIVE = wx.stc.STC_CONF_DIRECTIVE
wxSTC_AVE_DEFAULT = wx.stc.STC_AVE_DEFAULT
wxSTC_AVE_COMMENT = wx.stc.STC_AVE_COMMENT
wxSTC_AVE_NUMBER = wx.stc.STC_AVE_NUMBER
wxSTC_AVE_WORD = wx.stc.STC_AVE_WORD
wxSTC_AVE_STRING = wx.stc.STC_AVE_STRING
wxSTC_AVE_ENUM = wx.stc.STC_AVE_ENUM
wxSTC_AVE_STRINGEOL = wx.stc.STC_AVE_STRINGEOL
wxSTC_AVE_IDENTIFIER = wx.stc.STC_AVE_IDENTIFIER
wxSTC_AVE_OPERATOR = wx.stc.STC_AVE_OPERATOR
wxSTC_AVE_WORD1 = wx.stc.STC_AVE_WORD1
wxSTC_AVE_WORD2 = wx.stc.STC_AVE_WORD2
wxSTC_AVE_WORD3 = wx.stc.STC_AVE_WORD3
wxSTC_AVE_WORD4 = wx.stc.STC_AVE_WORD4
wxSTC_AVE_WORD5 = wx.stc.STC_AVE_WORD5
wxSTC_AVE_WORD6 = wx.stc.STC_AVE_WORD6
wxSTC_ADA_DEFAULT = wx.stc.STC_ADA_DEFAULT
wxSTC_ADA_WORD = wx.stc.STC_ADA_WORD
wxSTC_ADA_IDENTIFIER = wx.stc.STC_ADA_IDENTIFIER
wxSTC_ADA_NUMBER = wx.stc.STC_ADA_NUMBER
wxSTC_ADA_DELIMITER = wx.stc.STC_ADA_DELIMITER
wxSTC_ADA_CHARACTER = wx.stc.STC_ADA_CHARACTER
wxSTC_ADA_CHARACTEREOL = wx.stc.STC_ADA_CHARACTEREOL
wxSTC_ADA_STRING = wx.stc.STC_ADA_STRING
wxSTC_ADA_STRINGEOL = wx.stc.STC_ADA_STRINGEOL
wxSTC_ADA_LABEL = wx.stc.STC_ADA_LABEL
wxSTC_ADA_COMMENTLINE = wx.stc.STC_ADA_COMMENTLINE
wxSTC_ADA_ILLEGAL = wx.stc.STC_ADA_ILLEGAL
wxSTC_BAAN_DEFAULT = wx.stc.STC_BAAN_DEFAULT
wxSTC_BAAN_COMMENT = wx.stc.STC_BAAN_COMMENT
wxSTC_BAAN_COMMENTDOC = wx.stc.STC_BAAN_COMMENTDOC
wxSTC_BAAN_NUMBER = wx.stc.STC_BAAN_NUMBER
wxSTC_BAAN_WORD = wx.stc.STC_BAAN_WORD
wxSTC_BAAN_STRING = wx.stc.STC_BAAN_STRING
wxSTC_BAAN_PREPROCESSOR = wx.stc.STC_BAAN_PREPROCESSOR
wxSTC_BAAN_OPERATOR = wx.stc.STC_BAAN_OPERATOR
wxSTC_BAAN_IDENTIFIER = wx.stc.STC_BAAN_IDENTIFIER
wxSTC_BAAN_STRINGEOL = wx.stc.STC_BAAN_STRINGEOL
wxSTC_BAAN_WORD2 = wx.stc.STC_BAAN_WORD2
wxSTC_LISP_DEFAULT = wx.stc.STC_LISP_DEFAULT
wxSTC_LISP_COMMENT = wx.stc.STC_LISP_COMMENT
wxSTC_LISP_NUMBER = wx.stc.STC_LISP_NUMBER
wxSTC_LISP_KEYWORD = wx.stc.STC_LISP_KEYWORD
wxSTC_LISP_STRING = wx.stc.STC_LISP_STRING
wxSTC_LISP_STRINGEOL = wx.stc.STC_LISP_STRINGEOL
wxSTC_LISP_IDENTIFIER = wx.stc.STC_LISP_IDENTIFIER
wxSTC_LISP_OPERATOR = wx.stc.STC_LISP_OPERATOR
wxSTC_EIFFEL_DEFAULT = wx.stc.STC_EIFFEL_DEFAULT
wxSTC_EIFFEL_COMMENTLINE = wx.stc.STC_EIFFEL_COMMENTLINE
wxSTC_EIFFEL_NUMBER = wx.stc.STC_EIFFEL_NUMBER
wxSTC_EIFFEL_WORD = wx.stc.STC_EIFFEL_WORD
wxSTC_EIFFEL_STRING = wx.stc.STC_EIFFEL_STRING
wxSTC_EIFFEL_CHARACTER = wx.stc.STC_EIFFEL_CHARACTER
wxSTC_EIFFEL_OPERATOR = wx.stc.STC_EIFFEL_OPERATOR
wxSTC_EIFFEL_IDENTIFIER = wx.stc.STC_EIFFEL_IDENTIFIER
wxSTC_EIFFEL_STRINGEOL = wx.stc.STC_EIFFEL_STRINGEOL
wxSTC_NNCRONTAB_DEFAULT = wx.stc.STC_NNCRONTAB_DEFAULT
wxSTC_NNCRONTAB_COMMENT = wx.stc.STC_NNCRONTAB_COMMENT
wxSTC_NNCRONTAB_TASK = wx.stc.STC_NNCRONTAB_TASK
wxSTC_NNCRONTAB_SECTION = wx.stc.STC_NNCRONTAB_SECTION
wxSTC_NNCRONTAB_KEYWORD = wx.stc.STC_NNCRONTAB_KEYWORD
wxSTC_NNCRONTAB_MODIFIER = wx.stc.STC_NNCRONTAB_MODIFIER
wxSTC_NNCRONTAB_ASTERISK = wx.stc.STC_NNCRONTAB_ASTERISK
wxSTC_NNCRONTAB_NUMBER = wx.stc.STC_NNCRONTAB_NUMBER
wxSTC_NNCRONTAB_STRING = wx.stc.STC_NNCRONTAB_STRING
wxSTC_NNCRONTAB_ENVIRONMENT = wx.stc.STC_NNCRONTAB_ENVIRONMENT
wxSTC_NNCRONTAB_IDENTIFIER = wx.stc.STC_NNCRONTAB_IDENTIFIER
wxSTC_MATLAB_DEFAULT = wx.stc.STC_MATLAB_DEFAULT
wxSTC_MATLAB_COMMENT = wx.stc.STC_MATLAB_COMMENT
wxSTC_MATLAB_COMMAND = wx.stc.STC_MATLAB_COMMAND
wxSTC_MATLAB_NUMBER = wx.stc.STC_MATLAB_NUMBER
wxSTC_MATLAB_KEYWORD = wx.stc.STC_MATLAB_KEYWORD
wxSTC_MATLAB_STRING = wx.stc.STC_MATLAB_STRING
wxSTC_MATLAB_OPERATOR = wx.stc.STC_MATLAB_OPERATOR
wxSTC_MATLAB_IDENTIFIER = wx.stc.STC_MATLAB_IDENTIFIER
wxSTC_SCRIPTOL_DEFAULT = wx.stc.STC_SCRIPTOL_DEFAULT
wxSTC_SCRIPTOL_COMMENT = wx.stc.STC_SCRIPTOL_COMMENT
wxSTC_SCRIPTOL_COMMENTLINE = wx.stc.STC_SCRIPTOL_COMMENTLINE
wxSTC_SCRIPTOL_COMMENTDOC = wx.stc.STC_SCRIPTOL_COMMENTDOC
wxSTC_SCRIPTOL_NUMBER = wx.stc.STC_SCRIPTOL_NUMBER
wxSTC_SCRIPTOL_WORD = wx.stc.STC_SCRIPTOL_WORD
wxSTC_SCRIPTOL_STRING = wx.stc.STC_SCRIPTOL_STRING
wxSTC_SCRIPTOL_CHARACTER = wx.stc.STC_SCRIPTOL_CHARACTER
wxSTC_SCRIPTOL_UUID = wx.stc.STC_SCRIPTOL_UUID
wxSTC_SCRIPTOL_PREPROCESSOR = wx.stc.STC_SCRIPTOL_PREPROCESSOR
wxSTC_SCRIPTOL_OPERATOR = wx.stc.STC_SCRIPTOL_OPERATOR
wxSTC_SCRIPTOL_IDENTIFIER = wx.stc.STC_SCRIPTOL_IDENTIFIER
wxSTC_SCRIPTOL_STRINGEOL = wx.stc.STC_SCRIPTOL_STRINGEOL
wxSTC_SCRIPTOL_VERBATIM = wx.stc.STC_SCRIPTOL_VERBATIM
wxSTC_SCRIPTOL_REGEX = wx.stc.STC_SCRIPTOL_REGEX
wxSTC_SCRIPTOL_COMMENTLINEDOC = wx.stc.STC_SCRIPTOL_COMMENTLINEDOC
wxSTC_SCRIPTOL_WORD2 = wx.stc.STC_SCRIPTOL_WORD2
wxSTC_SCRIPTOL_COMMENTDOCKEYWORD = wx.stc.STC_SCRIPTOL_COMMENTDOCKEYWORD
wxSTC_SCRIPTOL_COMMENTDOCKEYWORDERROR = wx.stc.STC_SCRIPTOL_COMMENTDOCKEYWORDERROR
wxSTC_SCRIPTOL_COMMENTBASIC = wx.stc.STC_SCRIPTOL_COMMENTBASIC
wxSTC_ASM_DEFAULT = wx.stc.STC_ASM_DEFAULT
wxSTC_ASM_COMMENT = wx.stc.STC_ASM_COMMENT
wxSTC_ASM_NUMBER = wx.stc.STC_ASM_NUMBER
wxSTC_ASM_STRING = wx.stc.STC_ASM_STRING
wxSTC_ASM_OPERATOR = wx.stc.STC_ASM_OPERATOR
wxSTC_ASM_IDENTIFIER = wx.stc.STC_ASM_IDENTIFIER
wxSTC_ASM_CPUINSTRUCTION = wx.stc.STC_ASM_CPUINSTRUCTION
wxSTC_ASM_MATHINSTRUCTION = wx.stc.STC_ASM_MATHINSTRUCTION
wxSTC_ASM_REGISTER = wx.stc.STC_ASM_REGISTER
wxSTC_ASM_DIRECTIVE = wx.stc.STC_ASM_DIRECTIVE
wxSTC_ASM_DIRECTIVEOPERAND = wx.stc.STC_ASM_DIRECTIVEOPERAND
wxSTC_F_DEFAULT = wx.stc.STC_F_DEFAULT
wxSTC_F_COMMENT = wx.stc.STC_F_COMMENT
wxSTC_F_NUMBER = wx.stc.STC_F_NUMBER
wxSTC_F_STRING1 = wx.stc.STC_F_STRING1
wxSTC_F_STRING2 = wx.stc.STC_F_STRING2
wxSTC_F_STRINGEOL = wx.stc.STC_F_STRINGEOL
wxSTC_F_OPERATOR = wx.stc.STC_F_OPERATOR
wxSTC_F_IDENTIFIER = wx.stc.STC_F_IDENTIFIER
wxSTC_F_WORD = wx.stc.STC_F_WORD
wxSTC_F_WORD2 = wx.stc.STC_F_WORD2
wxSTC_F_WORD3 = wx.stc.STC_F_WORD3
wxSTC_F_PREPROCESSOR = wx.stc.STC_F_PREPROCESSOR
wxSTC_F_OPERATOR2 = wx.stc.STC_F_OPERATOR2
wxSTC_F_LABEL = wx.stc.STC_F_LABEL
wxSTC_F_CONTINUATION = wx.stc.STC_F_CONTINUATION
wxSTC_CSS_DEFAULT = wx.stc.STC_CSS_DEFAULT
wxSTC_CSS_TAG = wx.stc.STC_CSS_TAG
wxSTC_CSS_CLASS = wx.stc.STC_CSS_CLASS
wxSTC_CSS_PSEUDOCLASS = wx.stc.STC_CSS_PSEUDOCLASS
wxSTC_CSS_UNKNOWN_PSEUDOCLASS = wx.stc.STC_CSS_UNKNOWN_PSEUDOCLASS
wxSTC_CSS_OPERATOR = wx.stc.STC_CSS_OPERATOR
wxSTC_CSS_IDENTIFIER = wx.stc.STC_CSS_IDENTIFIER
wxSTC_CSS_UNKNOWN_IDENTIFIER = wx.stc.STC_CSS_UNKNOWN_IDENTIFIER
wxSTC_CSS_VALUE = wx.stc.STC_CSS_VALUE
wxSTC_CSS_COMMENT = wx.stc.STC_CSS_COMMENT
wxSTC_CSS_ID = wx.stc.STC_CSS_ID
wxSTC_CSS_IMPORTANT = wx.stc.STC_CSS_IMPORTANT
wxSTC_CSS_DIRECTIVE = wx.stc.STC_CSS_DIRECTIVE
wxSTC_CSS_DOUBLESTRING = wx.stc.STC_CSS_DOUBLESTRING
wxSTC_CSS_SINGLESTRING = wx.stc.STC_CSS_SINGLESTRING
wxSTC_POV_DEFAULT = wx.stc.STC_POV_DEFAULT
wxSTC_POV_COMMENT = wx.stc.STC_POV_COMMENT
wxSTC_POV_COMMENTLINE = wx.stc.STC_POV_COMMENTLINE
wxSTC_POV_NUMBER = wx.stc.STC_POV_NUMBER
wxSTC_POV_OPERATOR = wx.stc.STC_POV_OPERATOR
wxSTC_POV_IDENTIFIER = wx.stc.STC_POV_IDENTIFIER
wxSTC_POV_STRING = wx.stc.STC_POV_STRING
wxSTC_POV_STRINGEOL = wx.stc.STC_POV_STRINGEOL
wxSTC_POV_DIRECTIVE = wx.stc.STC_POV_DIRECTIVE
wxSTC_POV_BADDIRECTIVE = wx.stc.STC_POV_BADDIRECTIVE
wxSTC_POV_WORD2 = wx.stc.STC_POV_WORD2
wxSTC_POV_WORD3 = wx.stc.STC_POV_WORD3
wxSTC_POV_WORD4 = wx.stc.STC_POV_WORD4
wxSTC_POV_WORD5 = wx.stc.STC_POV_WORD5
wxSTC_POV_WORD6 = wx.stc.STC_POV_WORD6
wxSTC_POV_WORD7 = wx.stc.STC_POV_WORD7
wxSTC_POV_WORD8 = wx.stc.STC_POV_WORD8
wxSTC_LOUT_DEFAULT = wx.stc.STC_LOUT_DEFAULT
wxSTC_LOUT_COMMENT = wx.stc.STC_LOUT_COMMENT
wxSTC_LOUT_NUMBER = wx.stc.STC_LOUT_NUMBER
wxSTC_LOUT_WORD = wx.stc.STC_LOUT_WORD
wxSTC_LOUT_WORD2 = wx.stc.STC_LOUT_WORD2
wxSTC_LOUT_WORD3 = wx.stc.STC_LOUT_WORD3
wxSTC_LOUT_WORD4 = wx.stc.STC_LOUT_WORD4
wxSTC_LOUT_STRING = wx.stc.STC_LOUT_STRING
wxSTC_LOUT_OPERATOR = wx.stc.STC_LOUT_OPERATOR
wxSTC_LOUT_IDENTIFIER = wx.stc.STC_LOUT_IDENTIFIER
wxSTC_LOUT_STRINGEOL = wx.stc.STC_LOUT_STRINGEOL
wxSTC_ESCRIPT_DEFAULT = wx.stc.STC_ESCRIPT_DEFAULT
wxSTC_ESCRIPT_COMMENT = wx.stc.STC_ESCRIPT_COMMENT
wxSTC_ESCRIPT_COMMENTLINE = wx.stc.STC_ESCRIPT_COMMENTLINE
wxSTC_ESCRIPT_COMMENTDOC = wx.stc.STC_ESCRIPT_COMMENTDOC
wxSTC_ESCRIPT_NUMBER = wx.stc.STC_ESCRIPT_NUMBER
wxSTC_ESCRIPT_WORD = wx.stc.STC_ESCRIPT_WORD
wxSTC_ESCRIPT_STRING = wx.stc.STC_ESCRIPT_STRING
wxSTC_ESCRIPT_OPERATOR = wx.stc.STC_ESCRIPT_OPERATOR
wxSTC_ESCRIPT_IDENTIFIER = wx.stc.STC_ESCRIPT_IDENTIFIER
wxSTC_ESCRIPT_BRACE = wx.stc.STC_ESCRIPT_BRACE
wxSTC_ESCRIPT_WORD2 = wx.stc.STC_ESCRIPT_WORD2
wxSTC_ESCRIPT_WORD3 = wx.stc.STC_ESCRIPT_WORD3
wxSTC_PS_DEFAULT = wx.stc.STC_PS_DEFAULT
wxSTC_PS_COMMENT = wx.stc.STC_PS_COMMENT
wxSTC_PS_DSC_COMMENT = wx.stc.STC_PS_DSC_COMMENT
wxSTC_PS_DSC_VALUE = wx.stc.STC_PS_DSC_VALUE
wxSTC_PS_NUMBER = wx.stc.STC_PS_NUMBER
wxSTC_PS_NAME = wx.stc.STC_PS_NAME
wxSTC_PS_KEYWORD = wx.stc.STC_PS_KEYWORD
wxSTC_PS_LITERAL = wx.stc.STC_PS_LITERAL
wxSTC_PS_IMMEVAL = wx.stc.STC_PS_IMMEVAL
wxSTC_PS_PAREN_ARRAY = wx.stc.STC_PS_PAREN_ARRAY
wxSTC_PS_PAREN_DICT = wx.stc.STC_PS_PAREN_DICT
wxSTC_PS_PAREN_PROC = wx.stc.STC_PS_PAREN_PROC
wxSTC_PS_TEXT = wx.stc.STC_PS_TEXT
wxSTC_PS_HEXSTRING = wx.stc.STC_PS_HEXSTRING
wxSTC_PS_BASE85STRING = wx.stc.STC_PS_BASE85STRING
wxSTC_PS_BADSTRINGCHAR = wx.stc.STC_PS_BADSTRINGCHAR
wxSTC_NSIS_DEFAULT = wx.stc.STC_NSIS_DEFAULT
wxSTC_NSIS_COMMENT = wx.stc.STC_NSIS_COMMENT
wxSTC_NSIS_STRINGDQ = wx.stc.STC_NSIS_STRINGDQ
wxSTC_NSIS_STRINGLQ = wx.stc.STC_NSIS_STRINGLQ
wxSTC_NSIS_STRINGRQ = wx.stc.STC_NSIS_STRINGRQ
wxSTC_NSIS_FUNCTION = wx.stc.STC_NSIS_FUNCTION
wxSTC_NSIS_VARIABLE = wx.stc.STC_NSIS_VARIABLE
wxSTC_NSIS_LABEL = wx.stc.STC_NSIS_LABEL
wxSTC_NSIS_USERDEFINED = wx.stc.STC_NSIS_USERDEFINED
wxSTC_NSIS_SECTIONDEF = wx.stc.STC_NSIS_SECTIONDEF
wxSTC_NSIS_SUBSECTIONDEF = wx.stc.STC_NSIS_SUBSECTIONDEF
wxSTC_NSIS_IFDEFINEDEF = wx.stc.STC_NSIS_IFDEFINEDEF
wxSTC_NSIS_MACRODEF = wx.stc.STC_NSIS_MACRODEF
wxSTC_NSIS_STRINGVAR = wx.stc.STC_NSIS_STRINGVAR
wxSTC_MMIXAL_LEADWS = wx.stc.STC_MMIXAL_LEADWS
wxSTC_MMIXAL_COMMENT = wx.stc.STC_MMIXAL_COMMENT
wxSTC_MMIXAL_LABEL = wx.stc.STC_MMIXAL_LABEL
wxSTC_MMIXAL_OPCODE = wx.stc.STC_MMIXAL_OPCODE
wxSTC_MMIXAL_OPCODE_PRE = wx.stc.STC_MMIXAL_OPCODE_PRE
wxSTC_MMIXAL_OPCODE_VALID = wx.stc.STC_MMIXAL_OPCODE_VALID
wxSTC_MMIXAL_OPCODE_UNKNOWN = wx.stc.STC_MMIXAL_OPCODE_UNKNOWN
wxSTC_MMIXAL_OPCODE_POST = wx.stc.STC_MMIXAL_OPCODE_POST
wxSTC_MMIXAL_OPERANDS = wx.stc.STC_MMIXAL_OPERANDS
wxSTC_MMIXAL_NUMBER = wx.stc.STC_MMIXAL_NUMBER
wxSTC_MMIXAL_REF = wx.stc.STC_MMIXAL_REF
wxSTC_MMIXAL_CHAR = wx.stc.STC_MMIXAL_CHAR
wxSTC_MMIXAL_STRING = wx.stc.STC_MMIXAL_STRING
wxSTC_MMIXAL_REGISTER = wx.stc.STC_MMIXAL_REGISTER
wxSTC_MMIXAL_HEX = wx.stc.STC_MMIXAL_HEX
wxSTC_MMIXAL_OPERATOR = wx.stc.STC_MMIXAL_OPERATOR
wxSTC_MMIXAL_SYMBOL = wx.stc.STC_MMIXAL_SYMBOL
wxSTC_MMIXAL_INCLUDE = wx.stc.STC_MMIXAL_INCLUDE
wxSTC_CMD_REDO = wx.stc.STC_CMD_REDO
wxSTC_CMD_SELECTALL = wx.stc.STC_CMD_SELECTALL
wxSTC_CMD_UNDO = wx.stc.STC_CMD_UNDO
wxSTC_CMD_CUT = wx.stc.STC_CMD_CUT
wxSTC_CMD_COPY = wx.stc.STC_CMD_COPY
wxSTC_CMD_PASTE = wx.stc.STC_CMD_PASTE
wxSTC_CMD_CLEAR = wx.stc.STC_CMD_CLEAR
wxSTC_CMD_LINEDOWN = wx.stc.STC_CMD_LINEDOWN
wxSTC_CMD_LINEDOWNEXTEND = wx.stc.STC_CMD_LINEDOWNEXTEND
wxSTC_CMD_LINEUP = wx.stc.STC_CMD_LINEUP
wxSTC_CMD_LINEUPEXTEND = wx.stc.STC_CMD_LINEUPEXTEND
wxSTC_CMD_CHARLEFT = wx.stc.STC_CMD_CHARLEFT
wxSTC_CMD_CHARLEFTEXTEND = wx.stc.STC_CMD_CHARLEFTEXTEND
wxSTC_CMD_CHARRIGHT = wx.stc.STC_CMD_CHARRIGHT
wxSTC_CMD_CHARRIGHTEXTEND = wx.stc.STC_CMD_CHARRIGHTEXTEND
wxSTC_CMD_WORDLEFT = wx.stc.STC_CMD_WORDLEFT
wxSTC_CMD_WORDLEFTEXTEND = wx.stc.STC_CMD_WORDLEFTEXTEND
wxSTC_CMD_WORDRIGHT = wx.stc.STC_CMD_WORDRIGHT
wxSTC_CMD_WORDRIGHTEXTEND = wx.stc.STC_CMD_WORDRIGHTEXTEND
wxSTC_CMD_HOME = wx.stc.STC_CMD_HOME
wxSTC_CMD_HOMEEXTEND = wx.stc.STC_CMD_HOMEEXTEND
wxSTC_CMD_LINEEND = wx.stc.STC_CMD_LINEEND
wxSTC_CMD_LINEENDEXTEND = wx.stc.STC_CMD_LINEENDEXTEND
wxSTC_CMD_DOCUMENTSTART = wx.stc.STC_CMD_DOCUMENTSTART
wxSTC_CMD_DOCUMENTSTARTEXTEND = wx.stc.STC_CMD_DOCUMENTSTARTEXTEND
wxSTC_CMD_DOCUMENTEND = wx.stc.STC_CMD_DOCUMENTEND
wxSTC_CMD_DOCUMENTENDEXTEND = wx.stc.STC_CMD_DOCUMENTENDEXTEND
wxSTC_CMD_PAGEUP = wx.stc.STC_CMD_PAGEUP
wxSTC_CMD_PAGEUPEXTEND = wx.stc.STC_CMD_PAGEUPEXTEND
wxSTC_CMD_PAGEDOWN = wx.stc.STC_CMD_PAGEDOWN
wxSTC_CMD_PAGEDOWNEXTEND = wx.stc.STC_CMD_PAGEDOWNEXTEND
wxSTC_CMD_EDITTOGGLEOVERTYPE = wx.stc.STC_CMD_EDITTOGGLEOVERTYPE
wxSTC_CMD_CANCEL = wx.stc.STC_CMD_CANCEL
wxSTC_CMD_DELETEBACK = wx.stc.STC_CMD_DELETEBACK
wxSTC_CMD_TAB = wx.stc.STC_CMD_TAB
wxSTC_CMD_BACKTAB = wx.stc.STC_CMD_BACKTAB
wxSTC_CMD_NEWLINE = wx.stc.STC_CMD_NEWLINE
wxSTC_CMD_FORMFEED = wx.stc.STC_CMD_FORMFEED
wxSTC_CMD_VCHOME = wx.stc.STC_CMD_VCHOME
wxSTC_CMD_VCHOMEEXTEND = wx.stc.STC_CMD_VCHOMEEXTEND
wxSTC_CMD_ZOOMIN = wx.stc.STC_CMD_ZOOMIN
wxSTC_CMD_ZOOMOUT = wx.stc.STC_CMD_ZOOMOUT
wxSTC_CMD_DELWORDLEFT = wx.stc.STC_CMD_DELWORDLEFT
wxSTC_CMD_DELWORDRIGHT = wx.stc.STC_CMD_DELWORDRIGHT
wxSTC_CMD_LINECUT = wx.stc.STC_CMD_LINECUT
wxSTC_CMD_LINEDELETE = wx.stc.STC_CMD_LINEDELETE
wxSTC_CMD_LINETRANSPOSE = wx.stc.STC_CMD_LINETRANSPOSE
wxSTC_CMD_LINEDUPLICATE = wx.stc.STC_CMD_LINEDUPLICATE
wxSTC_CMD_LOWERCASE = wx.stc.STC_CMD_LOWERCASE
wxSTC_CMD_UPPERCASE = wx.stc.STC_CMD_UPPERCASE
wxSTC_CMD_LINESCROLLDOWN = wx.stc.STC_CMD_LINESCROLLDOWN
wxSTC_CMD_LINESCROLLUP = wx.stc.STC_CMD_LINESCROLLUP
wxSTC_CMD_DELETEBACKNOTLINE = wx.stc.STC_CMD_DELETEBACKNOTLINE
wxSTC_CMD_HOMEDISPLAY = wx.stc.STC_CMD_HOMEDISPLAY
wxSTC_CMD_HOMEDISPLAYEXTEND = wx.stc.STC_CMD_HOMEDISPLAYEXTEND
wxSTC_CMD_LINEENDDISPLAY = wx.stc.STC_CMD_LINEENDDISPLAY
wxSTC_CMD_LINEENDDISPLAYEXTEND = wx.stc.STC_CMD_LINEENDDISPLAYEXTEND
wxSTC_CMD_HOMEWRAP = wx.stc.STC_CMD_HOMEWRAP
wxSTC_CMD_HOMEWRAPEXTEND = wx.stc.STC_CMD_HOMEWRAPEXTEND
wxSTC_CMD_LINEENDWRAP = wx.stc.STC_CMD_LINEENDWRAP
wxSTC_CMD_LINEENDWRAPEXTEND = wx.stc.STC_CMD_LINEENDWRAPEXTEND
wxSTC_CMD_VCHOMEWRAP = wx.stc.STC_CMD_VCHOMEWRAP
wxSTC_CMD_VCHOMEWRAPEXTEND = wx.stc.STC_CMD_VCHOMEWRAPEXTEND
wxSTC_CMD_WORDPARTLEFT = wx.stc.STC_CMD_WORDPARTLEFT
wxSTC_CMD_WORDPARTLEFTEXTEND = wx.stc.STC_CMD_WORDPARTLEFTEXTEND
wxSTC_CMD_WORDPARTRIGHT = wx.stc.STC_CMD_WORDPARTRIGHT
wxSTC_CMD_WORDPARTRIGHTEXTEND = wx.stc.STC_CMD_WORDPARTRIGHTEXTEND
wxSTC_CMD_DELLINELEFT = wx.stc.STC_CMD_DELLINELEFT
wxSTC_CMD_DELLINERIGHT = wx.stc.STC_CMD_DELLINERIGHT
wxSTC_CMD_PARADOWN = wx.stc.STC_CMD_PARADOWN
wxSTC_CMD_PARADOWNEXTEND = wx.stc.STC_CMD_PARADOWNEXTEND
wxSTC_CMD_PARAUP = wx.stc.STC_CMD_PARAUP
wxSTC_CMD_PARAUPEXTEND = wx.stc.STC_CMD_PARAUPEXTEND
wxPreStyledTextCtrl = wx.stc.PreStyledTextCtrl
wxStyledTextCtrl = wx.stc.StyledTextCtrl
wxStyledTextEvent = wx.stc.StyledTextEvent
wxEVT_STC_CHANGE = wx.stc.wxEVT_STC_CHANGE
wxEVT_STC_STYLENEEDED = wx.stc.wxEVT_STC_STYLENEEDED
wxEVT_STC_CHARADDED = wx.stc.wxEVT_STC_CHARADDED
wxEVT_STC_SAVEPOINTREACHED = wx.stc.wxEVT_STC_SAVEPOINTREACHED
wxEVT_STC_SAVEPOINTLEFT = wx.stc.wxEVT_STC_SAVEPOINTLEFT
wxEVT_STC_ROMODIFYATTEMPT = wx.stc.wxEVT_STC_ROMODIFYATTEMPT
wxEVT_STC_KEY = wx.stc.wxEVT_STC_KEY
wxEVT_STC_DOUBLECLICK = wx.stc.wxEVT_STC_DOUBLECLICK
wxEVT_STC_UPDATEUI = wx.stc.wxEVT_STC_UPDATEUI
wxEVT_STC_MODIFIED = wx.stc.wxEVT_STC_MODIFIED
wxEVT_STC_MACRORECORD = wx.stc.wxEVT_STC_MACRORECORD
wxEVT_STC_MARGINCLICK = wx.stc.wxEVT_STC_MARGINCLICK
wxEVT_STC_NEEDSHOWN = wx.stc.wxEVT_STC_NEEDSHOWN
wxEVT_STC_POSCHANGED = wx.stc.wxEVT_STC_POSCHANGED
wxEVT_STC_PAINTED = wx.stc.wxEVT_STC_PAINTED
wxEVT_STC_USERLISTSELECTION = wx.stc.wxEVT_STC_USERLISTSELECTION
wxEVT_STC_URIDROPPED = wx.stc.wxEVT_STC_URIDROPPED
wxEVT_STC_DWELLSTART = wx.stc.wxEVT_STC_DWELLSTART
wxEVT_STC_DWELLEND = wx.stc.wxEVT_STC_DWELLEND
wxEVT_STC_START_DRAG = wx.stc.wxEVT_STC_START_DRAG
wxEVT_STC_DRAG_OVER = wx.stc.wxEVT_STC_DRAG_OVER
wxEVT_STC_DO_DROP = wx.stc.wxEVT_STC_DO_DROP
wxEVT_STC_ZOOM = wx.stc.wxEVT_STC_ZOOM
wxEVT_STC_HOTSPOT_CLICK = wx.stc.wxEVT_STC_HOTSPOT_CLICK
wxEVT_STC_HOTSPOT_DCLICK = wx.stc.wxEVT_STC_HOTSPOT_DCLICK
wxEVT_STC_CALLTIP_CLICK = wx.stc.wxEVT_STC_CALLTIP_CLICK


d = globals()
for k, v in wx.stc.__dict__.iteritems():
    if k.startswith('EVT'):
        d[k] = v
del d, k, v



