## This file reverse renames symbols in the wx package to give
## them their wx prefix again, for backwards compatibility.
##
## Generated by ./distrib/build_renamers.py

# This silly stuff here is so the wxPython.wx module doesn't conflict
# with the wx package.  We need to import modules from the wx package
# here, then we'll put the wxPython.wx entry back in sys.modules.
import sys
_wx = None
if sys.modules.has_key('wxPython.wx'):
    _wx = sys.modules['wxPython.wx']
    del sys.modules['wxPython.wx']

import wx.gdi

sys.modules['wxPython.wx'] = _wx
del sys, _wx


# Now assign all the reverse-renamed names:
wxGDIObject = wx.gdi.GDIObject
wxGDIObjectPtr = wx.gdi.GDIObjectPtr
wxColour = wx.gdi.Colour
wxColourPtr = wx.gdi.ColourPtr
wxNamedColour = wx.gdi.NamedColour
wxColourRGB = wx.gdi.ColourRGB
wxPalette = wx.gdi.Palette
wxPalettePtr = wx.gdi.PalettePtr
wxPen = wx.gdi.Pen
wxPenPtr = wx.gdi.PenPtr
wxPyPen = wx.gdi.PyPen
wxPyPenPtr = wx.gdi.PyPenPtr
wxBrush = wx.gdi.Brush
wxBrushPtr = wx.gdi.BrushPtr
wxBitmap = wx.gdi.Bitmap
wxBitmapPtr = wx.gdi.BitmapPtr
wxEmptyBitmap = wx.gdi.EmptyBitmap
wxBitmapFromIcon = wx.gdi.BitmapFromIcon
wxBitmapFromImage = wx.gdi.BitmapFromImage
wxBitmapFromXPMData = wx.gdi.BitmapFromXPMData
wxBitmapFromBits = wx.gdi.BitmapFromBits
wxMask = wx.gdi.Mask
wxMaskPtr = wx.gdi.MaskPtr
wxMaskColour = wx.gdi.MaskColour
wxIcon = wx.gdi.Icon
wxIconPtr = wx.gdi.IconPtr
wxEmptyIcon = wx.gdi.EmptyIcon
wxIconFromLocation = wx.gdi.IconFromLocation
wxIconFromBitmap = wx.gdi.IconFromBitmap
wxIconFromXPMData = wx.gdi.IconFromXPMData
wxIconLocation = wx.gdi.IconLocation
wxIconLocationPtr = wx.gdi.IconLocationPtr
wxIconBundle = wx.gdi.IconBundle
wxIconBundlePtr = wx.gdi.IconBundlePtr
wxIconBundleFromFile = wx.gdi.IconBundleFromFile
wxIconBundleFromIcon = wx.gdi.IconBundleFromIcon
wxCursor = wx.gdi.Cursor
wxCursorPtr = wx.gdi.CursorPtr
wxStockCursor = wx.gdi.StockCursor
wxCursorFromImage = wx.gdi.CursorFromImage
wxCursorFromBits = wx.gdi.CursorFromBits
wxOutRegion = wx.gdi.OutRegion
wxPartRegion = wx.gdi.PartRegion
wxInRegion = wx.gdi.InRegion
wxRegion = wx.gdi.Region
wxRegionPtr = wx.gdi.RegionPtr
wxRegionFromBitmap = wx.gdi.RegionFromBitmap
wxRegionFromPoints = wx.gdi.RegionFromPoints
wxRegionIterator = wx.gdi.RegionIterator
wxRegionIteratorPtr = wx.gdi.RegionIteratorPtr
wxFONTFAMILY_DEFAULT = wx.gdi.FONTFAMILY_DEFAULT
wxFONTFAMILY_DECORATIVE = wx.gdi.FONTFAMILY_DECORATIVE
wxFONTFAMILY_ROMAN = wx.gdi.FONTFAMILY_ROMAN
wxFONTFAMILY_SCRIPT = wx.gdi.FONTFAMILY_SCRIPT
wxFONTFAMILY_SWISS = wx.gdi.FONTFAMILY_SWISS
wxFONTFAMILY_MODERN = wx.gdi.FONTFAMILY_MODERN
wxFONTFAMILY_TELETYPE = wx.gdi.FONTFAMILY_TELETYPE
wxFONTFAMILY_MAX = wx.gdi.FONTFAMILY_MAX
wxFONTFAMILY_UNKNOWN = wx.gdi.FONTFAMILY_UNKNOWN
wxFONTSTYLE_NORMAL = wx.gdi.FONTSTYLE_NORMAL
wxFONTSTYLE_ITALIC = wx.gdi.FONTSTYLE_ITALIC
wxFONTSTYLE_SLANT = wx.gdi.FONTSTYLE_SLANT
wxFONTSTYLE_MAX = wx.gdi.FONTSTYLE_MAX
wxFONTWEIGHT_NORMAL = wx.gdi.FONTWEIGHT_NORMAL
wxFONTWEIGHT_LIGHT = wx.gdi.FONTWEIGHT_LIGHT
wxFONTWEIGHT_BOLD = wx.gdi.FONTWEIGHT_BOLD
wxFONTWEIGHT_MAX = wx.gdi.FONTWEIGHT_MAX
wxFONTFLAG_DEFAULT = wx.gdi.FONTFLAG_DEFAULT
wxFONTFLAG_ITALIC = wx.gdi.FONTFLAG_ITALIC
wxFONTFLAG_SLANT = wx.gdi.FONTFLAG_SLANT
wxFONTFLAG_LIGHT = wx.gdi.FONTFLAG_LIGHT
wxFONTFLAG_BOLD = wx.gdi.FONTFLAG_BOLD
wxFONTFLAG_ANTIALIASED = wx.gdi.FONTFLAG_ANTIALIASED
wxFONTFLAG_NOT_ANTIALIASED = wx.gdi.FONTFLAG_NOT_ANTIALIASED
wxFONTFLAG_UNDERLINED = wx.gdi.FONTFLAG_UNDERLINED
wxFONTFLAG_STRIKETHROUGH = wx.gdi.FONTFLAG_STRIKETHROUGH
wxFONTFLAG_MASK = wx.gdi.FONTFLAG_MASK
wxFONTENCODING_SYSTEM = wx.gdi.FONTENCODING_SYSTEM
wxFONTENCODING_DEFAULT = wx.gdi.FONTENCODING_DEFAULT
wxFONTENCODING_ISO8859_1 = wx.gdi.FONTENCODING_ISO8859_1
wxFONTENCODING_ISO8859_2 = wx.gdi.FONTENCODING_ISO8859_2
wxFONTENCODING_ISO8859_3 = wx.gdi.FONTENCODING_ISO8859_3
wxFONTENCODING_ISO8859_4 = wx.gdi.FONTENCODING_ISO8859_4
wxFONTENCODING_ISO8859_5 = wx.gdi.FONTENCODING_ISO8859_5
wxFONTENCODING_ISO8859_6 = wx.gdi.FONTENCODING_ISO8859_6
wxFONTENCODING_ISO8859_7 = wx.gdi.FONTENCODING_ISO8859_7
wxFONTENCODING_ISO8859_8 = wx.gdi.FONTENCODING_ISO8859_8
wxFONTENCODING_ISO8859_9 = wx.gdi.FONTENCODING_ISO8859_9
wxFONTENCODING_ISO8859_10 = wx.gdi.FONTENCODING_ISO8859_10
wxFONTENCODING_ISO8859_11 = wx.gdi.FONTENCODING_ISO8859_11
wxFONTENCODING_ISO8859_12 = wx.gdi.FONTENCODING_ISO8859_12
wxFONTENCODING_ISO8859_13 = wx.gdi.FONTENCODING_ISO8859_13
wxFONTENCODING_ISO8859_14 = wx.gdi.FONTENCODING_ISO8859_14
wxFONTENCODING_ISO8859_15 = wx.gdi.FONTENCODING_ISO8859_15
wxFONTENCODING_ISO8859_MAX = wx.gdi.FONTENCODING_ISO8859_MAX
wxFONTENCODING_KOI8 = wx.gdi.FONTENCODING_KOI8
wxFONTENCODING_ALTERNATIVE = wx.gdi.FONTENCODING_ALTERNATIVE
wxFONTENCODING_BULGARIAN = wx.gdi.FONTENCODING_BULGARIAN
wxFONTENCODING_CP437 = wx.gdi.FONTENCODING_CP437
wxFONTENCODING_CP850 = wx.gdi.FONTENCODING_CP850
wxFONTENCODING_CP852 = wx.gdi.FONTENCODING_CP852
wxFONTENCODING_CP855 = wx.gdi.FONTENCODING_CP855
wxFONTENCODING_CP866 = wx.gdi.FONTENCODING_CP866
wxFONTENCODING_CP874 = wx.gdi.FONTENCODING_CP874
wxFONTENCODING_CP932 = wx.gdi.FONTENCODING_CP932
wxFONTENCODING_CP936 = wx.gdi.FONTENCODING_CP936
wxFONTENCODING_CP949 = wx.gdi.FONTENCODING_CP949
wxFONTENCODING_CP950 = wx.gdi.FONTENCODING_CP950
wxFONTENCODING_CP1250 = wx.gdi.FONTENCODING_CP1250
wxFONTENCODING_CP1251 = wx.gdi.FONTENCODING_CP1251
wxFONTENCODING_CP1252 = wx.gdi.FONTENCODING_CP1252
wxFONTENCODING_CP1253 = wx.gdi.FONTENCODING_CP1253
wxFONTENCODING_CP1254 = wx.gdi.FONTENCODING_CP1254
wxFONTENCODING_CP1255 = wx.gdi.FONTENCODING_CP1255
wxFONTENCODING_CP1256 = wx.gdi.FONTENCODING_CP1256
wxFONTENCODING_CP1257 = wx.gdi.FONTENCODING_CP1257
wxFONTENCODING_CP12_MAX = wx.gdi.FONTENCODING_CP12_MAX
wxFONTENCODING_UTF7 = wx.gdi.FONTENCODING_UTF7
wxFONTENCODING_UTF8 = wx.gdi.FONTENCODING_UTF8
wxFONTENCODING_EUC_JP = wx.gdi.FONTENCODING_EUC_JP
wxFONTENCODING_UTF16BE = wx.gdi.FONTENCODING_UTF16BE
wxFONTENCODING_UTF16LE = wx.gdi.FONTENCODING_UTF16LE
wxFONTENCODING_UTF32BE = wx.gdi.FONTENCODING_UTF32BE
wxFONTENCODING_UTF32LE = wx.gdi.FONTENCODING_UTF32LE
wxFONTENCODING_MAX = wx.gdi.FONTENCODING_MAX
wxFONTENCODING_UTF16 = wx.gdi.FONTENCODING_UTF16
wxFONTENCODING_UTF32 = wx.gdi.FONTENCODING_UTF32
wxFONTENCODING_UNICODE = wx.gdi.FONTENCODING_UNICODE
wxFONTENCODING_GB2312 = wx.gdi.FONTENCODING_GB2312
wxFONTENCODING_BIG5 = wx.gdi.FONTENCODING_BIG5
wxFONTENCODING_SHIFT_JIS = wx.gdi.FONTENCODING_SHIFT_JIS
wxNativeFontInfo = wx.gdi.NativeFontInfo
wxNativeFontInfoPtr = wx.gdi.NativeFontInfoPtr
wxNativeEncodingInfo = wx.gdi.NativeEncodingInfo
wxNativeEncodingInfoPtr = wx.gdi.NativeEncodingInfoPtr
wxGetNativeFontEncoding = wx.gdi.GetNativeFontEncoding
wxTestFontEncoding = wx.gdi.TestFontEncoding
wxFontMapper = wx.gdi.FontMapper
wxFontMapperPtr = wx.gdi.FontMapperPtr
wxFontMapper_Get = wx.gdi.FontMapper_Get
wxFontMapper_Set = wx.gdi.FontMapper_Set
wxFontMapper_GetSupportedEncodingsCount = wx.gdi.FontMapper_GetSupportedEncodingsCount
wxFontMapper_GetEncoding = wx.gdi.FontMapper_GetEncoding
wxFontMapper_GetEncodingName = wx.gdi.FontMapper_GetEncodingName
wxFontMapper_GetEncodingDescription = wx.gdi.FontMapper_GetEncodingDescription
wxFontMapper_GetDefaultConfigPath = wx.gdi.FontMapper_GetDefaultConfigPath
wxFont = wx.gdi.Font
wxFontPtr = wx.gdi.FontPtr
wxFontFromNativeInfo = wx.gdi.FontFromNativeInfo
wxFontFromNativeInfoString = wx.gdi.FontFromNativeInfoString
wxFont2 = wx.gdi.Font2
wxFont_GetDefaultEncoding = wx.gdi.Font_GetDefaultEncoding
wxFont_SetDefaultEncoding = wx.gdi.Font_SetDefaultEncoding
wxFontEnumerator = wx.gdi.FontEnumerator
wxFontEnumeratorPtr = wx.gdi.FontEnumeratorPtr
wxLANGUAGE_DEFAULT = wx.gdi.LANGUAGE_DEFAULT
wxLANGUAGE_UNKNOWN = wx.gdi.LANGUAGE_UNKNOWN
wxLANGUAGE_ABKHAZIAN = wx.gdi.LANGUAGE_ABKHAZIAN
wxLANGUAGE_AFAR = wx.gdi.LANGUAGE_AFAR
wxLANGUAGE_AFRIKAANS = wx.gdi.LANGUAGE_AFRIKAANS
wxLANGUAGE_ALBANIAN = wx.gdi.LANGUAGE_ALBANIAN
wxLANGUAGE_AMHARIC = wx.gdi.LANGUAGE_AMHARIC
wxLANGUAGE_ARABIC = wx.gdi.LANGUAGE_ARABIC
wxLANGUAGE_ARABIC_ALGERIA = wx.gdi.LANGUAGE_ARABIC_ALGERIA
wxLANGUAGE_ARABIC_BAHRAIN = wx.gdi.LANGUAGE_ARABIC_BAHRAIN
wxLANGUAGE_ARABIC_EGYPT = wx.gdi.LANGUAGE_ARABIC_EGYPT
wxLANGUAGE_ARABIC_IRAQ = wx.gdi.LANGUAGE_ARABIC_IRAQ
wxLANGUAGE_ARABIC_JORDAN = wx.gdi.LANGUAGE_ARABIC_JORDAN
wxLANGUAGE_ARABIC_KUWAIT = wx.gdi.LANGUAGE_ARABIC_KUWAIT
wxLANGUAGE_ARABIC_LEBANON = wx.gdi.LANGUAGE_ARABIC_LEBANON
wxLANGUAGE_ARABIC_LIBYA = wx.gdi.LANGUAGE_ARABIC_LIBYA
wxLANGUAGE_ARABIC_MOROCCO = wx.gdi.LANGUAGE_ARABIC_MOROCCO
wxLANGUAGE_ARABIC_OMAN = wx.gdi.LANGUAGE_ARABIC_OMAN
wxLANGUAGE_ARABIC_QATAR = wx.gdi.LANGUAGE_ARABIC_QATAR
wxLANGUAGE_ARABIC_SAUDI_ARABIA = wx.gdi.LANGUAGE_ARABIC_SAUDI_ARABIA
wxLANGUAGE_ARABIC_SUDAN = wx.gdi.LANGUAGE_ARABIC_SUDAN
wxLANGUAGE_ARABIC_SYRIA = wx.gdi.LANGUAGE_ARABIC_SYRIA
wxLANGUAGE_ARABIC_TUNISIA = wx.gdi.LANGUAGE_ARABIC_TUNISIA
wxLANGUAGE_ARABIC_UAE = wx.gdi.LANGUAGE_ARABIC_UAE
wxLANGUAGE_ARABIC_YEMEN = wx.gdi.LANGUAGE_ARABIC_YEMEN
wxLANGUAGE_ARMENIAN = wx.gdi.LANGUAGE_ARMENIAN
wxLANGUAGE_ASSAMESE = wx.gdi.LANGUAGE_ASSAMESE
wxLANGUAGE_AYMARA = wx.gdi.LANGUAGE_AYMARA
wxLANGUAGE_AZERI = wx.gdi.LANGUAGE_AZERI
wxLANGUAGE_AZERI_CYRILLIC = wx.gdi.LANGUAGE_AZERI_CYRILLIC
wxLANGUAGE_AZERI_LATIN = wx.gdi.LANGUAGE_AZERI_LATIN
wxLANGUAGE_BASHKIR = wx.gdi.LANGUAGE_BASHKIR
wxLANGUAGE_BASQUE = wx.gdi.LANGUAGE_BASQUE
wxLANGUAGE_BELARUSIAN = wx.gdi.LANGUAGE_BELARUSIAN
wxLANGUAGE_BENGALI = wx.gdi.LANGUAGE_BENGALI
wxLANGUAGE_BHUTANI = wx.gdi.LANGUAGE_BHUTANI
wxLANGUAGE_BIHARI = wx.gdi.LANGUAGE_BIHARI
wxLANGUAGE_BISLAMA = wx.gdi.LANGUAGE_BISLAMA
wxLANGUAGE_BRETON = wx.gdi.LANGUAGE_BRETON
wxLANGUAGE_BULGARIAN = wx.gdi.LANGUAGE_BULGARIAN
wxLANGUAGE_BURMESE = wx.gdi.LANGUAGE_BURMESE
wxLANGUAGE_CAMBODIAN = wx.gdi.LANGUAGE_CAMBODIAN
wxLANGUAGE_CATALAN = wx.gdi.LANGUAGE_CATALAN
wxLANGUAGE_CHINESE = wx.gdi.LANGUAGE_CHINESE
wxLANGUAGE_CHINESE_SIMPLIFIED = wx.gdi.LANGUAGE_CHINESE_SIMPLIFIED
wxLANGUAGE_CHINESE_TRADITIONAL = wx.gdi.LANGUAGE_CHINESE_TRADITIONAL
wxLANGUAGE_CHINESE_HONGKONG = wx.gdi.LANGUAGE_CHINESE_HONGKONG
wxLANGUAGE_CHINESE_MACAU = wx.gdi.LANGUAGE_CHINESE_MACAU
wxLANGUAGE_CHINESE_SINGAPORE = wx.gdi.LANGUAGE_CHINESE_SINGAPORE
wxLANGUAGE_CHINESE_TAIWAN = wx.gdi.LANGUAGE_CHINESE_TAIWAN
wxLANGUAGE_CORSICAN = wx.gdi.LANGUAGE_CORSICAN
wxLANGUAGE_CROATIAN = wx.gdi.LANGUAGE_CROATIAN
wxLANGUAGE_CZECH = wx.gdi.LANGUAGE_CZECH
wxLANGUAGE_DANISH = wx.gdi.LANGUAGE_DANISH
wxLANGUAGE_DUTCH = wx.gdi.LANGUAGE_DUTCH
wxLANGUAGE_DUTCH_BELGIAN = wx.gdi.LANGUAGE_DUTCH_BELGIAN
wxLANGUAGE_ENGLISH = wx.gdi.LANGUAGE_ENGLISH
wxLANGUAGE_ENGLISH_UK = wx.gdi.LANGUAGE_ENGLISH_UK
wxLANGUAGE_ENGLISH_US = wx.gdi.LANGUAGE_ENGLISH_US
wxLANGUAGE_ENGLISH_AUSTRALIA = wx.gdi.LANGUAGE_ENGLISH_AUSTRALIA
wxLANGUAGE_ENGLISH_BELIZE = wx.gdi.LANGUAGE_ENGLISH_BELIZE
wxLANGUAGE_ENGLISH_BOTSWANA = wx.gdi.LANGUAGE_ENGLISH_BOTSWANA
wxLANGUAGE_ENGLISH_CANADA = wx.gdi.LANGUAGE_ENGLISH_CANADA
wxLANGUAGE_ENGLISH_CARIBBEAN = wx.gdi.LANGUAGE_ENGLISH_CARIBBEAN
wxLANGUAGE_ENGLISH_DENMARK = wx.gdi.LANGUAGE_ENGLISH_DENMARK
wxLANGUAGE_ENGLISH_EIRE = wx.gdi.LANGUAGE_ENGLISH_EIRE
wxLANGUAGE_ENGLISH_JAMAICA = wx.gdi.LANGUAGE_ENGLISH_JAMAICA
wxLANGUAGE_ENGLISH_NEW_ZEALAND = wx.gdi.LANGUAGE_ENGLISH_NEW_ZEALAND
wxLANGUAGE_ENGLISH_PHILIPPINES = wx.gdi.LANGUAGE_ENGLISH_PHILIPPINES
wxLANGUAGE_ENGLISH_SOUTH_AFRICA = wx.gdi.LANGUAGE_ENGLISH_SOUTH_AFRICA
wxLANGUAGE_ENGLISH_TRINIDAD = wx.gdi.LANGUAGE_ENGLISH_TRINIDAD
wxLANGUAGE_ENGLISH_ZIMBABWE = wx.gdi.LANGUAGE_ENGLISH_ZIMBABWE
wxLANGUAGE_ESPERANTO = wx.gdi.LANGUAGE_ESPERANTO
wxLANGUAGE_ESTONIAN = wx.gdi.LANGUAGE_ESTONIAN
wxLANGUAGE_FAEROESE = wx.gdi.LANGUAGE_FAEROESE
wxLANGUAGE_FARSI = wx.gdi.LANGUAGE_FARSI
wxLANGUAGE_FIJI = wx.gdi.LANGUAGE_FIJI
wxLANGUAGE_FINNISH = wx.gdi.LANGUAGE_FINNISH
wxLANGUAGE_FRENCH = wx.gdi.LANGUAGE_FRENCH
wxLANGUAGE_FRENCH_BELGIAN = wx.gdi.LANGUAGE_FRENCH_BELGIAN
wxLANGUAGE_FRENCH_CANADIAN = wx.gdi.LANGUAGE_FRENCH_CANADIAN
wxLANGUAGE_FRENCH_LUXEMBOURG = wx.gdi.LANGUAGE_FRENCH_LUXEMBOURG
wxLANGUAGE_FRENCH_MONACO = wx.gdi.LANGUAGE_FRENCH_MONACO
wxLANGUAGE_FRENCH_SWISS = wx.gdi.LANGUAGE_FRENCH_SWISS
wxLANGUAGE_FRISIAN = wx.gdi.LANGUAGE_FRISIAN
wxLANGUAGE_GALICIAN = wx.gdi.LANGUAGE_GALICIAN
wxLANGUAGE_GEORGIAN = wx.gdi.LANGUAGE_GEORGIAN
wxLANGUAGE_GERMAN = wx.gdi.LANGUAGE_GERMAN
wxLANGUAGE_GERMAN_AUSTRIAN = wx.gdi.LANGUAGE_GERMAN_AUSTRIAN
wxLANGUAGE_GERMAN_BELGIUM = wx.gdi.LANGUAGE_GERMAN_BELGIUM
wxLANGUAGE_GERMAN_LIECHTENSTEIN = wx.gdi.LANGUAGE_GERMAN_LIECHTENSTEIN
wxLANGUAGE_GERMAN_LUXEMBOURG = wx.gdi.LANGUAGE_GERMAN_LUXEMBOURG
wxLANGUAGE_GERMAN_SWISS = wx.gdi.LANGUAGE_GERMAN_SWISS
wxLANGUAGE_GREEK = wx.gdi.LANGUAGE_GREEK
wxLANGUAGE_GREENLANDIC = wx.gdi.LANGUAGE_GREENLANDIC
wxLANGUAGE_GUARANI = wx.gdi.LANGUAGE_GUARANI
wxLANGUAGE_GUJARATI = wx.gdi.LANGUAGE_GUJARATI
wxLANGUAGE_HAUSA = wx.gdi.LANGUAGE_HAUSA
wxLANGUAGE_HEBREW = wx.gdi.LANGUAGE_HEBREW
wxLANGUAGE_HINDI = wx.gdi.LANGUAGE_HINDI
wxLANGUAGE_HUNGARIAN = wx.gdi.LANGUAGE_HUNGARIAN
wxLANGUAGE_ICELANDIC = wx.gdi.LANGUAGE_ICELANDIC
wxLANGUAGE_INDONESIAN = wx.gdi.LANGUAGE_INDONESIAN
wxLANGUAGE_INTERLINGUA = wx.gdi.LANGUAGE_INTERLINGUA
wxLANGUAGE_INTERLINGUE = wx.gdi.LANGUAGE_INTERLINGUE
wxLANGUAGE_INUKTITUT = wx.gdi.LANGUAGE_INUKTITUT
wxLANGUAGE_INUPIAK = wx.gdi.LANGUAGE_INUPIAK
wxLANGUAGE_IRISH = wx.gdi.LANGUAGE_IRISH
wxLANGUAGE_ITALIAN = wx.gdi.LANGUAGE_ITALIAN
wxLANGUAGE_ITALIAN_SWISS = wx.gdi.LANGUAGE_ITALIAN_SWISS
wxLANGUAGE_JAPANESE = wx.gdi.LANGUAGE_JAPANESE
wxLANGUAGE_JAVANESE = wx.gdi.LANGUAGE_JAVANESE
wxLANGUAGE_KANNADA = wx.gdi.LANGUAGE_KANNADA
wxLANGUAGE_KASHMIRI = wx.gdi.LANGUAGE_KASHMIRI
wxLANGUAGE_KASHMIRI_INDIA = wx.gdi.LANGUAGE_KASHMIRI_INDIA
wxLANGUAGE_KAZAKH = wx.gdi.LANGUAGE_KAZAKH
wxLANGUAGE_KERNEWEK = wx.gdi.LANGUAGE_KERNEWEK
wxLANGUAGE_KINYARWANDA = wx.gdi.LANGUAGE_KINYARWANDA
wxLANGUAGE_KIRGHIZ = wx.gdi.LANGUAGE_KIRGHIZ
wxLANGUAGE_KIRUNDI = wx.gdi.LANGUAGE_KIRUNDI
wxLANGUAGE_KONKANI = wx.gdi.LANGUAGE_KONKANI
wxLANGUAGE_KOREAN = wx.gdi.LANGUAGE_KOREAN
wxLANGUAGE_KURDISH = wx.gdi.LANGUAGE_KURDISH
wxLANGUAGE_LAOTHIAN = wx.gdi.LANGUAGE_LAOTHIAN
wxLANGUAGE_LATIN = wx.gdi.LANGUAGE_LATIN
wxLANGUAGE_LATVIAN = wx.gdi.LANGUAGE_LATVIAN
wxLANGUAGE_LINGALA = wx.gdi.LANGUAGE_LINGALA
wxLANGUAGE_LITHUANIAN = wx.gdi.LANGUAGE_LITHUANIAN
wxLANGUAGE_MACEDONIAN = wx.gdi.LANGUAGE_MACEDONIAN
wxLANGUAGE_MALAGASY = wx.gdi.LANGUAGE_MALAGASY
wxLANGUAGE_MALAY = wx.gdi.LANGUAGE_MALAY
wxLANGUAGE_MALAYALAM = wx.gdi.LANGUAGE_MALAYALAM
wxLANGUAGE_MALAY_BRUNEI_DARUSSALAM = wx.gdi.LANGUAGE_MALAY_BRUNEI_DARUSSALAM
wxLANGUAGE_MALAY_MALAYSIA = wx.gdi.LANGUAGE_MALAY_MALAYSIA
wxLANGUAGE_MALTESE = wx.gdi.LANGUAGE_MALTESE
wxLANGUAGE_MANIPURI = wx.gdi.LANGUAGE_MANIPURI
wxLANGUAGE_MAORI = wx.gdi.LANGUAGE_MAORI
wxLANGUAGE_MARATHI = wx.gdi.LANGUAGE_MARATHI
wxLANGUAGE_MOLDAVIAN = wx.gdi.LANGUAGE_MOLDAVIAN
wxLANGUAGE_MONGOLIAN = wx.gdi.LANGUAGE_MONGOLIAN
wxLANGUAGE_NAURU = wx.gdi.LANGUAGE_NAURU
wxLANGUAGE_NEPALI = wx.gdi.LANGUAGE_NEPALI
wxLANGUAGE_NEPALI_INDIA = wx.gdi.LANGUAGE_NEPALI_INDIA
wxLANGUAGE_NORWEGIAN_BOKMAL = wx.gdi.LANGUAGE_NORWEGIAN_BOKMAL
wxLANGUAGE_NORWEGIAN_NYNORSK = wx.gdi.LANGUAGE_NORWEGIAN_NYNORSK
wxLANGUAGE_OCCITAN = wx.gdi.LANGUAGE_OCCITAN
wxLANGUAGE_ORIYA = wx.gdi.LANGUAGE_ORIYA
wxLANGUAGE_OROMO = wx.gdi.LANGUAGE_OROMO
wxLANGUAGE_PASHTO = wx.gdi.LANGUAGE_PASHTO
wxLANGUAGE_POLISH = wx.gdi.LANGUAGE_POLISH
wxLANGUAGE_PORTUGUESE = wx.gdi.LANGUAGE_PORTUGUESE
wxLANGUAGE_PORTUGUESE_BRAZILIAN = wx.gdi.LANGUAGE_PORTUGUESE_BRAZILIAN
wxLANGUAGE_PUNJABI = wx.gdi.LANGUAGE_PUNJABI
wxLANGUAGE_QUECHUA = wx.gdi.LANGUAGE_QUECHUA
wxLANGUAGE_RHAETO_ROMANCE = wx.gdi.LANGUAGE_RHAETO_ROMANCE
wxLANGUAGE_ROMANIAN = wx.gdi.LANGUAGE_ROMANIAN
wxLANGUAGE_RUSSIAN = wx.gdi.LANGUAGE_RUSSIAN
wxLANGUAGE_RUSSIAN_UKRAINE = wx.gdi.LANGUAGE_RUSSIAN_UKRAINE
wxLANGUAGE_SAMOAN = wx.gdi.LANGUAGE_SAMOAN
wxLANGUAGE_SANGHO = wx.gdi.LANGUAGE_SANGHO
wxLANGUAGE_SANSKRIT = wx.gdi.LANGUAGE_SANSKRIT
wxLANGUAGE_SCOTS_GAELIC = wx.gdi.LANGUAGE_SCOTS_GAELIC
wxLANGUAGE_SERBIAN = wx.gdi.LANGUAGE_SERBIAN
wxLANGUAGE_SERBIAN_CYRILLIC = wx.gdi.LANGUAGE_SERBIAN_CYRILLIC
wxLANGUAGE_SERBIAN_LATIN = wx.gdi.LANGUAGE_SERBIAN_LATIN
wxLANGUAGE_SERBO_CROATIAN = wx.gdi.LANGUAGE_SERBO_CROATIAN
wxLANGUAGE_SESOTHO = wx.gdi.LANGUAGE_SESOTHO
wxLANGUAGE_SETSWANA = wx.gdi.LANGUAGE_SETSWANA
wxLANGUAGE_SHONA = wx.gdi.LANGUAGE_SHONA
wxLANGUAGE_SINDHI = wx.gdi.LANGUAGE_SINDHI
wxLANGUAGE_SINHALESE = wx.gdi.LANGUAGE_SINHALESE
wxLANGUAGE_SISWATI = wx.gdi.LANGUAGE_SISWATI
wxLANGUAGE_SLOVAK = wx.gdi.LANGUAGE_SLOVAK
wxLANGUAGE_SLOVENIAN = wx.gdi.LANGUAGE_SLOVENIAN
wxLANGUAGE_SOMALI = wx.gdi.LANGUAGE_SOMALI
wxLANGUAGE_SPANISH = wx.gdi.LANGUAGE_SPANISH
wxLANGUAGE_SPANISH_ARGENTINA = wx.gdi.LANGUAGE_SPANISH_ARGENTINA
wxLANGUAGE_SPANISH_BOLIVIA = wx.gdi.LANGUAGE_SPANISH_BOLIVIA
wxLANGUAGE_SPANISH_CHILE = wx.gdi.LANGUAGE_SPANISH_CHILE
wxLANGUAGE_SPANISH_COLOMBIA = wx.gdi.LANGUAGE_SPANISH_COLOMBIA
wxLANGUAGE_SPANISH_COSTA_RICA = wx.gdi.LANGUAGE_SPANISH_COSTA_RICA
wxLANGUAGE_SPANISH_DOMINICAN_REPUBLIC = wx.gdi.LANGUAGE_SPANISH_DOMINICAN_REPUBLIC
wxLANGUAGE_SPANISH_ECUADOR = wx.gdi.LANGUAGE_SPANISH_ECUADOR
wxLANGUAGE_SPANISH_EL_SALVADOR = wx.gdi.LANGUAGE_SPANISH_EL_SALVADOR
wxLANGUAGE_SPANISH_GUATEMALA = wx.gdi.LANGUAGE_SPANISH_GUATEMALA
wxLANGUAGE_SPANISH_HONDURAS = wx.gdi.LANGUAGE_SPANISH_HONDURAS
wxLANGUAGE_SPANISH_MEXICAN = wx.gdi.LANGUAGE_SPANISH_MEXICAN
wxLANGUAGE_SPANISH_MODERN = wx.gdi.LANGUAGE_SPANISH_MODERN
wxLANGUAGE_SPANISH_NICARAGUA = wx.gdi.LANGUAGE_SPANISH_NICARAGUA
wxLANGUAGE_SPANISH_PANAMA = wx.gdi.LANGUAGE_SPANISH_PANAMA
wxLANGUAGE_SPANISH_PARAGUAY = wx.gdi.LANGUAGE_SPANISH_PARAGUAY
wxLANGUAGE_SPANISH_PERU = wx.gdi.LANGUAGE_SPANISH_PERU
wxLANGUAGE_SPANISH_PUERTO_RICO = wx.gdi.LANGUAGE_SPANISH_PUERTO_RICO
wxLANGUAGE_SPANISH_URUGUAY = wx.gdi.LANGUAGE_SPANISH_URUGUAY
wxLANGUAGE_SPANISH_US = wx.gdi.LANGUAGE_SPANISH_US
wxLANGUAGE_SPANISH_VENEZUELA = wx.gdi.LANGUAGE_SPANISH_VENEZUELA
wxLANGUAGE_SUNDANESE = wx.gdi.LANGUAGE_SUNDANESE
wxLANGUAGE_SWAHILI = wx.gdi.LANGUAGE_SWAHILI
wxLANGUAGE_SWEDISH = wx.gdi.LANGUAGE_SWEDISH
wxLANGUAGE_SWEDISH_FINLAND = wx.gdi.LANGUAGE_SWEDISH_FINLAND
wxLANGUAGE_TAGALOG = wx.gdi.LANGUAGE_TAGALOG
wxLANGUAGE_TAJIK = wx.gdi.LANGUAGE_TAJIK
wxLANGUAGE_TAMIL = wx.gdi.LANGUAGE_TAMIL
wxLANGUAGE_TATAR = wx.gdi.LANGUAGE_TATAR
wxLANGUAGE_TELUGU = wx.gdi.LANGUAGE_TELUGU
wxLANGUAGE_THAI = wx.gdi.LANGUAGE_THAI
wxLANGUAGE_TIBETAN = wx.gdi.LANGUAGE_TIBETAN
wxLANGUAGE_TIGRINYA = wx.gdi.LANGUAGE_TIGRINYA
wxLANGUAGE_TONGA = wx.gdi.LANGUAGE_TONGA
wxLANGUAGE_TSONGA = wx.gdi.LANGUAGE_TSONGA
wxLANGUAGE_TURKISH = wx.gdi.LANGUAGE_TURKISH
wxLANGUAGE_TURKMEN = wx.gdi.LANGUAGE_TURKMEN
wxLANGUAGE_TWI = wx.gdi.LANGUAGE_TWI
wxLANGUAGE_UIGHUR = wx.gdi.LANGUAGE_UIGHUR
wxLANGUAGE_UKRAINIAN = wx.gdi.LANGUAGE_UKRAINIAN
wxLANGUAGE_URDU = wx.gdi.LANGUAGE_URDU
wxLANGUAGE_URDU_INDIA = wx.gdi.LANGUAGE_URDU_INDIA
wxLANGUAGE_URDU_PAKISTAN = wx.gdi.LANGUAGE_URDU_PAKISTAN
wxLANGUAGE_UZBEK = wx.gdi.LANGUAGE_UZBEK
wxLANGUAGE_UZBEK_CYRILLIC = wx.gdi.LANGUAGE_UZBEK_CYRILLIC
wxLANGUAGE_UZBEK_LATIN = wx.gdi.LANGUAGE_UZBEK_LATIN
wxLANGUAGE_VIETNAMESE = wx.gdi.LANGUAGE_VIETNAMESE
wxLANGUAGE_VOLAPUK = wx.gdi.LANGUAGE_VOLAPUK
wxLANGUAGE_WELSH = wx.gdi.LANGUAGE_WELSH
wxLANGUAGE_WOLOF = wx.gdi.LANGUAGE_WOLOF
wxLANGUAGE_XHOSA = wx.gdi.LANGUAGE_XHOSA
wxLANGUAGE_YIDDISH = wx.gdi.LANGUAGE_YIDDISH
wxLANGUAGE_YORUBA = wx.gdi.LANGUAGE_YORUBA
wxLANGUAGE_ZHUANG = wx.gdi.LANGUAGE_ZHUANG
wxLANGUAGE_ZULU = wx.gdi.LANGUAGE_ZULU
wxLANGUAGE_USER_DEFINED = wx.gdi.LANGUAGE_USER_DEFINED
wxLanguageInfo = wx.gdi.LanguageInfo
wxLanguageInfoPtr = wx.gdi.LanguageInfoPtr
wxLOCALE_CAT_NUMBER = wx.gdi.LOCALE_CAT_NUMBER
wxLOCALE_CAT_DATE = wx.gdi.LOCALE_CAT_DATE
wxLOCALE_CAT_MONEY = wx.gdi.LOCALE_CAT_MONEY
wxLOCALE_CAT_MAX = wx.gdi.LOCALE_CAT_MAX
wxLOCALE_THOUSANDS_SEP = wx.gdi.LOCALE_THOUSANDS_SEP
wxLOCALE_DECIMAL_POINT = wx.gdi.LOCALE_DECIMAL_POINT
wxLOCALE_LOAD_DEFAULT = wx.gdi.LOCALE_LOAD_DEFAULT
wxLOCALE_CONV_ENCODING = wx.gdi.LOCALE_CONV_ENCODING
wxLocale = wx.gdi.Locale
wxLocalePtr = wx.gdi.LocalePtr
wxLocale_GetSystemLanguage = wx.gdi.Locale_GetSystemLanguage
wxLocale_GetSystemEncoding = wx.gdi.Locale_GetSystemEncoding
wxLocale_GetSystemEncodingName = wx.gdi.Locale_GetSystemEncodingName
wxLocale_AddCatalogLookupPathPrefix = wx.gdi.Locale_AddCatalogLookupPathPrefix
wxLocale_GetLanguageInfo = wx.gdi.Locale_GetLanguageInfo
wxLocale_GetLanguageName = wx.gdi.Locale_GetLanguageName
wxLocale_FindLanguageInfo = wx.gdi.Locale_FindLanguageInfo
wxLocale_AddLanguage = wx.gdi.Locale_AddLanguage
wxGetLocale = wx.gdi.GetLocale
wxGetTranslation = wx.gdi.GetTranslation
wxGetTranslation = wx.gdi.GetTranslation
wxCONVERT_STRICT = wx.gdi.CONVERT_STRICT
wxCONVERT_SUBSTITUTE = wx.gdi.CONVERT_SUBSTITUTE
wxPLATFORM_CURRENT = wx.gdi.PLATFORM_CURRENT
wxPLATFORM_UNIX = wx.gdi.PLATFORM_UNIX
wxPLATFORM_WINDOWS = wx.gdi.PLATFORM_WINDOWS
wxPLATFORM_OS2 = wx.gdi.PLATFORM_OS2
wxPLATFORM_MAC = wx.gdi.PLATFORM_MAC
wxEncodingConverter = wx.gdi.EncodingConverter
wxEncodingConverterPtr = wx.gdi.EncodingConverterPtr
wxEncodingConverter_GetPlatformEquivalents = wx.gdi.EncodingConverter_GetPlatformEquivalents
wxEncodingConverter_GetAllEquivalents = wx.gdi.EncodingConverter_GetAllEquivalents
wxEncodingConverter_CanConvert = wx.gdi.EncodingConverter_CanConvert
wxDC = wx.gdi.DC
wxDCPtr = wx.gdi.DCPtr
wxMemoryDC = wx.gdi.MemoryDC
wxMemoryDCPtr = wx.gdi.MemoryDCPtr
wxMemoryDCFromDC = wx.gdi.MemoryDCFromDC
wxBufferedDC = wx.gdi.BufferedDC
wxBufferedDCPtr = wx.gdi.BufferedDCPtr
wxBufferedDCInternalBuffer = wx.gdi.BufferedDCInternalBuffer
wxBufferedPaintDC = wx.gdi.BufferedPaintDC
wxBufferedPaintDCPtr = wx.gdi.BufferedPaintDCPtr
wxScreenDC = wx.gdi.ScreenDC
wxScreenDCPtr = wx.gdi.ScreenDCPtr
wxClientDC = wx.gdi.ClientDC
wxClientDCPtr = wx.gdi.ClientDCPtr
wxPaintDC = wx.gdi.PaintDC
wxPaintDCPtr = wx.gdi.PaintDCPtr
wxWindowDC = wx.gdi.WindowDC
wxWindowDCPtr = wx.gdi.WindowDCPtr
wxMirrorDC = wx.gdi.MirrorDC
wxMirrorDCPtr = wx.gdi.MirrorDCPtr
wxPostScriptDC = wx.gdi.PostScriptDC
wxPostScriptDCPtr = wx.gdi.PostScriptDCPtr
wxPostScriptDC_SetResolution = wx.gdi.PostScriptDC_SetResolution
wxPostScriptDC_GetResolution = wx.gdi.PostScriptDC_GetResolution
wxMetaFile = wx.gdi.MetaFile
wxMetaFilePtr = wx.gdi.MetaFilePtr
wxMetaFileDC = wx.gdi.MetaFileDC
wxMetaFileDCPtr = wx.gdi.MetaFileDCPtr
wxPrinterDC = wx.gdi.PrinterDC
wxPrinterDCPtr = wx.gdi.PrinterDCPtr
wxIMAGELIST_DRAW_NORMAL = wx.gdi.IMAGELIST_DRAW_NORMAL
wxIMAGELIST_DRAW_TRANSPARENT = wx.gdi.IMAGELIST_DRAW_TRANSPARENT
wxIMAGELIST_DRAW_SELECTED = wx.gdi.IMAGELIST_DRAW_SELECTED
wxIMAGELIST_DRAW_FOCUSED = wx.gdi.IMAGELIST_DRAW_FOCUSED
wxIMAGE_LIST_NORMAL = wx.gdi.IMAGE_LIST_NORMAL
wxIMAGE_LIST_SMALL = wx.gdi.IMAGE_LIST_SMALL
wxIMAGE_LIST_STATE = wx.gdi.IMAGE_LIST_STATE
wxImageList = wx.gdi.ImageList
wxImageListPtr = wx.gdi.ImageListPtr
wxPenList = wx.gdi.PenList
wxPenListPtr = wx.gdi.PenListPtr
wxBrushList = wx.gdi.BrushList
wxBrushListPtr = wx.gdi.BrushListPtr
wxColourDatabase = wx.gdi.ColourDatabase
wxColourDatabasePtr = wx.gdi.ColourDatabasePtr
wxFontList = wx.gdi.FontList
wxFontListPtr = wx.gdi.FontListPtr
wxNORMAL_FONT = wx.gdi.NORMAL_FONT
wxSMALL_FONT = wx.gdi.SMALL_FONT
wxITALIC_FONT = wx.gdi.ITALIC_FONT
wxSWISS_FONT = wx.gdi.SWISS_FONT
wxRED_PEN = wx.gdi.RED_PEN
wxCYAN_PEN = wx.gdi.CYAN_PEN
wxGREEN_PEN = wx.gdi.GREEN_PEN
wxBLACK_PEN = wx.gdi.BLACK_PEN
wxWHITE_PEN = wx.gdi.WHITE_PEN
wxTRANSPARENT_PEN = wx.gdi.TRANSPARENT_PEN
wxBLACK_DASHED_PEN = wx.gdi.BLACK_DASHED_PEN
wxGREY_PEN = wx.gdi.GREY_PEN
wxMEDIUM_GREY_PEN = wx.gdi.MEDIUM_GREY_PEN
wxLIGHT_GREY_PEN = wx.gdi.LIGHT_GREY_PEN
wxBLUE_BRUSH = wx.gdi.BLUE_BRUSH
wxGREEN_BRUSH = wx.gdi.GREEN_BRUSH
wxWHITE_BRUSH = wx.gdi.WHITE_BRUSH
wxBLACK_BRUSH = wx.gdi.BLACK_BRUSH
wxTRANSPARENT_BRUSH = wx.gdi.TRANSPARENT_BRUSH
wxCYAN_BRUSH = wx.gdi.CYAN_BRUSH
wxRED_BRUSH = wx.gdi.RED_BRUSH
wxGREY_BRUSH = wx.gdi.GREY_BRUSH
wxMEDIUM_GREY_BRUSH = wx.gdi.MEDIUM_GREY_BRUSH
wxLIGHT_GREY_BRUSH = wx.gdi.LIGHT_GREY_BRUSH
wxBLACK = wx.gdi.BLACK
wxWHITE = wx.gdi.WHITE
wxRED = wx.gdi.RED
wxBLUE = wx.gdi.BLUE
wxGREEN = wx.gdi.GREEN
wxCYAN = wx.gdi.CYAN
wxLIGHT_GREY = wx.gdi.LIGHT_GREY
wxSTANDARD_CURSOR = wx.gdi.STANDARD_CURSOR
wxHOURGLASS_CURSOR = wx.gdi.HOURGLASS_CURSOR
wxCROSS_CURSOR = wx.gdi.CROSS_CURSOR
wxNullBitmap = wx.gdi.NullBitmap
wxNullIcon = wx.gdi.NullIcon
wxNullCursor = wx.gdi.NullCursor
wxNullPen = wx.gdi.NullPen
wxNullBrush = wx.gdi.NullBrush
wxNullPalette = wx.gdi.NullPalette
wxNullFont = wx.gdi.NullFont
wxNullColour = wx.gdi.NullColour
wxTheFontList = wx.gdi.TheFontList
wxThePenList = wx.gdi.ThePenList
wxTheBrushList = wx.gdi.TheBrushList
wxTheColourDatabase = wx.gdi.TheColourDatabase
wxEffects = wx.gdi.Effects
wxEffectsPtr = wx.gdi.EffectsPtr
wxDC_old = wx.gdi.DC_old
wxMemoryDC_old = wx.gdi.MemoryDC_old
wxBufferedDC_old = wx.gdi.BufferedDC_old
wxBufferedPaintDC_old = wx.gdi.BufferedPaintDC_old
wxScreenDC_old = wx.gdi.ScreenDC_old
wxClientDC_old = wx.gdi.ClientDC_old
wxPaintDC_old = wx.gdi.PaintDC_old
wxWindowDC_old = wx.gdi.WindowDC_old
wxMirrorDC_old = wx.gdi.MirrorDC_old
wxPostScriptDC_old = wx.gdi.PostScriptDC_old
wxMetaFileDC_old = wx.gdi.MetaFileDC_old
wxPrinterDC_old = wx.gdi.PrinterDC_old


