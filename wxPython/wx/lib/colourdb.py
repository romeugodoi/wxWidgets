#----------------------------------------------------------------------
# Name:        wxPython.lib.colourdb.py
# Purpose:     Adds a bunch of colour names and RGB values to the
#              colour database so they can be found by name
#
# Author:      Robin Dunn
#
# Created:     13-March-2001
# RCS-ID:      $Id$
# Copyright:   (c) 2001 by Total Control Software
# Licence:     wxWindows license
#----------------------------------------------------------------------

"""
Load addition color names/values into the wx colour database.  These
names and values originally came from the rgb.txt file on my system...
"""


def getColourList():
    """Returns a list of just the colour names used by this module."""
    return [ x[0] for x in getColourInfoList() ]



def getColourInfoList():
    """Returns the list of colour name/value tuples used by this module."""
    return [
        ("SNOW", 255, 250, 250),
        ("GHOST WHITE", 248, 248, 255),
        ("GHOSTWHITE", 248, 248, 255),
        ("WHITE SMOKE", 245, 245, 245),
        ("WHITESMOKE", 245, 245, 245),
        ("GAINSBORO", 220, 220, 220),
        ("FLORAL WHITE", 255, 250, 240),
        ("FLORALWHITE", 255, 250, 240),
        ("OLD LACE", 253, 245, 230),
        ("OLDLACE", 253, 245, 230),
        ("LINEN", 250, 240, 230),
        ("ANTIQUE WHITE", 250, 235, 215),
        ("ANTIQUEWHITE", 250, 235, 215),
        ("PAPAYA WHIP", 255, 239, 213),
        ("PAPAYAWHIP", 255, 239, 213),
        ("BLANCHED ALMOND", 255, 235, 205),
        ("BLANCHEDALMOND", 255, 235, 205),
        ("BISQUE", 255, 228, 196),
        ("PEACH PUFF", 255, 218, 185),
        ("PEACHPUFF", 255, 218, 185),
        ("NAVAJO WHITE", 255, 222, 173),
        ("NAVAJOWHITE", 255, 222, 173),
        ("MOCCASIN", 255, 228, 181),
        ("CORNSILK", 255, 248, 220),
        ("IVORY", 255, 255, 240),
        ("LEMON CHIFFON", 255, 250, 205),
        ("LEMONCHIFFON", 255, 250, 205),
        ("SEASHELL", 255, 245, 238),
        ("HONEYDEW", 240, 255, 240),
        ("MINT CREAM", 245, 255, 250),
        ("MINTCREAM", 245, 255, 250),
        ("AZURE", 240, 255, 255),
        ("ALICE BLUE", 240, 248, 255),
        ("ALICEBLUE", 240, 248, 255),
        ("LAVENDER", 230, 230, 250),
        ("LAVENDER BLUSH", 255, 240, 245),
        ("LAVENDERBLUSH", 255, 240, 245),
        ("MISTY ROSE", 255, 228, 225),
        ("MISTYROSE", 255, 228, 225),
        ("WHITE", 255, 255, 255),
        ("BLACK",   0,   0,   0),
        ("DARK SLATE GREY",  47,  79,  79),
        ("DARKSLATEGREY",  47,  79,  79),
        ("DIM GREY", 105, 105, 105),
        ("DIMGREY", 105, 105, 105),
        ("SLATE GREY", 112, 128, 144),
        ("SLATEGREY", 112, 128, 144),
        ("LIGHT SLATE GREY", 119, 136, 153),
        ("LIGHTSLATEGREY", 119, 136, 153),
        ("GREY", 190, 190, 190),
        ("LIGHT GREY", 211, 211, 211),
        ("LIGHTGREY", 211, 211, 211),
        ("MIDNIGHT BLUE",  25,  25, 112),
        ("MIDNIGHTBLUE",  25,  25, 112),
        ("NAVY",   0,   0, 128),
        ("NAVY BLUE",   0,   0, 128),
        ("NAVYBLUE",   0,   0, 128),
        ("CORNFLOWER BLUE", 100, 149, 237),
        ("CORNFLOWERBLUE", 100, 149, 237),
        ("DARK SLATE BLUE",  72,  61, 139),
        ("DARKSLATEBLUE",  72,  61, 139),
        ("SLATE BLUE", 106,  90, 205),
        ("SLATEBLUE", 106,  90, 205),
        ("MEDIUM SLATE BLUE", 123, 104, 238),
        ("MEDIUMSLATEBLUE", 123, 104, 238),
        ("LIGHT SLATE BLUE", 132, 112, 255),
        ("LIGHTSLATEBLUE", 132, 112, 255),
        ("MEDIUM BLUE",   0,   0, 205),
        ("MEDIUMBLUE",   0,   0, 205),
        ("ROYAL BLUE",  65, 105, 225),
        ("ROYALBLUE",  65, 105, 225),
        ("BLUE",   0,   0, 255),
        ("DODGER BLUE",  30, 144, 255),
        ("DODGERBLUE",  30, 144, 255),
        ("DEEP SKY BLUE",   0, 191, 255),
        ("DEEPSKYBLUE",   0, 191, 255),
        ("SKY BLUE", 135, 206, 235),
        ("SKYBLUE", 135, 206, 235),
        ("LIGHT SKY BLUE", 135, 206, 250),
        ("LIGHTSKYBLUE", 135, 206, 250),
        ("STEEL BLUE",  70, 130, 180),
        ("STEELBLUE",  70, 130, 180),
        ("LIGHT STEEL BLUE", 176, 196, 222),
        ("LIGHTSTEELBLUE", 176, 196, 222),
        ("LIGHT BLUE", 173, 216, 230),
        ("LIGHTBLUE", 173, 216, 230),
        ("POWDER BLUE", 176, 224, 230),
        ("POWDERBLUE", 176, 224, 230),
        ("PALE TURQUOISE", 175, 238, 238),
        ("PALETURQUOISE", 175, 238, 238),
        ("DARK TURQUOISE",   0, 206, 209),
        ("DARKTURQUOISE",   0, 206, 209),
        ("MEDIUM TURQUOISE",  72, 209, 204),
        ("MEDIUMTURQUOISE",  72, 209, 204),
        ("TURQUOISE",  64, 224, 208),
        ("CYAN",   0, 255, 255),
        ("LIGHT CYAN", 224, 255, 255),
        ("LIGHTCYAN", 224, 255, 255),
        ("CADET BLUE",  95, 158, 160),
        ("CADETBLUE",  95, 158, 160),
        ("MEDIUM AQUAMARINE", 102, 205, 170),
        ("MEDIUMAQUAMARINE", 102, 205, 170),
        ("AQUAMARINE", 127, 255, 212),
        ("DARK GREEN",   0, 100,   0),
        ("DARKGREEN",   0, 100,   0),
        ("DARK OLIVE GREEN",  85, 107,  47),
        ("DARKOLIVEGREEN",  85, 107,  47),
        ("DARK SEA GREEN", 143, 188, 143),
        ("DARKSEAGREEN", 143, 188, 143),
        ("SEA GREEN",  46, 139,  87),
        ("SEAGREEN",  46, 139,  87),
        ("MEDIUM SEA GREEN",  60, 179, 113),
        ("MEDIUMSEAGREEN",  60, 179, 113),
        ("LIGHT SEA GREEN",  32, 178, 170),
        ("LIGHTSEAGREEN",  32, 178, 170),
        ("PALE GREEN", 152, 251, 152),
        ("PALEGREEN", 152, 251, 152),
        ("SPRING GREEN",   0, 255, 127),
        ("SPRINGGREEN",   0, 255, 127),
        ("LAWN GREEN", 124, 252,   0),
        ("LAWNGREEN", 124, 252,   0),
        ("GREEN",   0, 255,   0),
        ("CHARTREUSE", 127, 255,   0),
        ("MEDIUM SPRING GREEN",   0, 250, 154),
        ("MEDIUMSPRINGGREEN",   0, 250, 154),
        ("GREEN YELLOW", 173, 255,  47),
        ("GREENYELLOW", 173, 255,  47),
        ("LIME GREEN",  50, 205,  50),
        ("LIMEGREEN",  50, 205,  50),
        ("YELLOW GREEN", 154, 205,  50),
        ("YELLOWGREEN", 154, 205,  50),
        ("FOREST GREEN",  34, 139,  34),
        ("FORESTGREEN",  34, 139,  34),
        ("OLIVE DRAB", 107, 142,  35),
        ("OLIVEDRAB", 107, 142,  35),
        ("DARK KHAKI", 189, 183, 107),
        ("DARKKHAKI", 189, 183, 107),
        ("KHAKI", 240, 230, 140),
        ("PALE GOLDENROD", 238, 232, 170),
        ("PALEGOLDENROD", 238, 232, 170),
        ("LIGHT GOLDENROD YELLOW", 250, 250, 210),
        ("LIGHTGOLDENRODYELLOW", 250, 250, 210),
        ("LIGHT YELLOW", 255, 255, 224),
        ("LIGHTYELLOW", 255, 255, 224),
        ("YELLOW", 255, 255,   0),
        ("GOLD", 255, 215,   0),
        ("LIGHT GOLDENROD", 238, 221, 130),
        ("LIGHTGOLDENROD", 238, 221, 130),
        ("GOLDENROD", 218, 165,  32),
        ("DARK GOLDENROD", 184, 134,  11),
        ("DARKGOLDENROD", 184, 134,  11),
        ("ROSY BROWN", 188, 143, 143),
        ("ROSYBROWN", 188, 143, 143),
        ("INDIAN RED", 205,  92,  92),
        ("INDIANRED", 205,  92,  92),
        ("SADDLE BROWN", 139,  69,  19),
        ("SADDLEBROWN", 139,  69,  19),
        ("SIENNA", 160,  82,  45),
        ("PERU", 205, 133,  63),
        ("BURLYWOOD", 222, 184, 135),
        ("BEIGE", 245, 245, 220),
        ("WHEAT", 245, 222, 179),
        ("SANDY BROWN", 244, 164,  96),
        ("SANDYBROWN", 244, 164,  96),
        ("TAN", 210, 180, 140),
        ("CHOCOLATE", 210, 105,  30),
        ("FIREBRICK", 178,  34,  34),
        ("BROWN", 165,  42,  42),
        ("DARK SALMON", 233, 150, 122),
        ("DARKSALMON", 233, 150, 122),
        ("SALMON", 250, 128, 114),
        ("LIGHT SALMON", 255, 160, 122),
        ("LIGHTSALMON", 255, 160, 122),
        ("ORANGE", 255, 165,   0),
        ("DARK ORANGE", 255, 140,   0),
        ("DARKORANGE", 255, 140,   0),
        ("CORAL", 255, 127,  80),
        ("LIGHT CORAL", 240, 128, 128),
        ("LIGHTCORAL", 240, 128, 128),
        ("TOMATO", 255,  99,  71),
        ("ORANGE RED", 255,  69,   0),
        ("ORANGERED", 255,  69,   0),
        ("RED", 255,   0,   0),
        ("HOT PINK", 255, 105, 180),
        ("HOTPINK", 255, 105, 180),
        ("DEEP PINK", 255,  20, 147),
        ("DEEPPINK", 255,  20, 147),
        ("PINK", 255, 192, 203),
        ("LIGHT PINK", 255, 182, 193),
        ("LIGHTPINK", 255, 182, 193),
        ("PALE VIOLET RED", 219, 112, 147),
        ("PALEVIOLETRED", 219, 112, 147),
        ("MAROON", 176,  48,  96),
        ("MEDIUM VIOLET RED", 199,  21, 133),
        ("MEDIUMVIOLETRED", 199,  21, 133),
        ("VIOLET RED", 208,  32, 144),
        ("VIOLETRED", 208,  32, 144),
        ("MAGENTA", 255,   0, 255),
        ("VIOLET", 238, 130, 238),
        ("PLUM", 221, 160, 221),
        ("ORCHID", 218, 112, 214),
        ("MEDIUM ORCHID", 186,  85, 211),
        ("MEDIUMORCHID", 186,  85, 211),
        ("DARK ORCHID", 153,  50, 204),
        ("DARKORCHID", 153,  50, 204),
        ("DARK VIOLET", 148,   0, 211),
        ("DARKVIOLET", 148,   0, 211),
        ("BLUE VIOLET", 138,  43, 226),
        ("BLUEVIOLET", 138,  43, 226),
        ("PURPLE", 160,  32, 240),
        ("MEDIUM PURPLE", 147, 112, 219),
        ("MEDIUMPURPLE", 147, 112, 219),
        ("THISTLE", 216, 191, 216),
        ("SNOW1", 255, 250, 250),
        ("SNOW2", 238, 233, 233),
        ("SNOW3", 205, 201, 201),
        ("SNOW4", 139, 137, 137),
        ("SEASHELL1", 255, 245, 238),
        ("SEASHELL2", 238, 229, 222),
        ("SEASHELL3", 205, 197, 191),
        ("SEASHELL4", 139, 134, 130),
        ("ANTIQUEWHITE1", 255, 239, 219),
        ("ANTIQUEWHITE2", 238, 223, 204),
        ("ANTIQUEWHITE3", 205, 192, 176),
        ("ANTIQUEWHITE4", 139, 131, 120),
        ("BISQUE1", 255, 228, 196),
        ("BISQUE2", 238, 213, 183),
        ("BISQUE3", 205, 183, 158),
        ("BISQUE4", 139, 125, 107),
        ("PEACHPUFF1", 255, 218, 185),
        ("PEACHPUFF2", 238, 203, 173),
        ("PEACHPUFF3", 205, 175, 149),
        ("PEACHPUFF4", 139, 119, 101),
        ("NAVAJOWHITE1", 255, 222, 173),
        ("NAVAJOWHITE2", 238, 207, 161),
        ("NAVAJOWHITE3", 205, 179, 139),
        ("NAVAJOWHITE4", 139, 121,  94),
        ("LEMONCHIFFON1", 255, 250, 205),
        ("LEMONCHIFFON2", 238, 233, 191),
        ("LEMONCHIFFON3", 205, 201, 165),
        ("LEMONCHIFFON4", 139, 137, 112),
        ("CORNSILK1", 255, 248, 220),
        ("CORNSILK2", 238, 232, 205),
        ("CORNSILK3", 205, 200, 177),
        ("CORNSILK4", 139, 136, 120),
        ("IVORY1", 255, 255, 240),
        ("IVORY2", 238, 238, 224),
        ("IVORY3", 205, 205, 193),
        ("IVORY4", 139, 139, 131),
        ("HONEYDEW1", 240, 255, 240),
        ("HONEYDEW2", 224, 238, 224),
        ("HONEYDEW3", 193, 205, 193),
        ("HONEYDEW4", 131, 139, 131),
        ("LAVENDERBLUSH1", 255, 240, 245),
        ("LAVENDERBLUSH2", 238, 224, 229),
        ("LAVENDERBLUSH3", 205, 193, 197),
        ("LAVENDERBLUSH4", 139, 131, 134),
        ("MISTYROSE1", 255, 228, 225),
        ("MISTYROSE2", 238, 213, 210),
        ("MISTYROSE3", 205, 183, 181),
        ("MISTYROSE4", 139, 125, 123),
        ("AZURE1", 240, 255, 255),
        ("AZURE2", 224, 238, 238),
        ("AZURE3", 193, 205, 205),
        ("AZURE4", 131, 139, 139),
        ("SLATEBLUE1", 131, 111, 255),
        ("SLATEBLUE2", 122, 103, 238),
        ("SLATEBLUE3", 105,  89, 205),
        ("SLATEBLUE4",  71,  60, 139),
        ("ROYALBLUE1",  72, 118, 255),
        ("ROYALBLUE2",  67, 110, 238),
        ("ROYALBLUE3",  58,  95, 205),
        ("ROYALBLUE4",  39,  64, 139),
        ("BLUE1",   0,   0, 255),
        ("BLUE2",   0,   0, 238),
        ("BLUE3",   0,   0, 205),
        ("BLUE4",   0,   0, 139),
        ("DODGERBLUE1",  30, 144, 255),
        ("DODGERBLUE2",  28, 134, 238),
        ("DODGERBLUE3",  24, 116, 205),
        ("DODGERBLUE4",  16,  78, 139),
        ("STEELBLUE1",  99, 184, 255),
        ("STEELBLUE2",  92, 172, 238),
        ("STEELBLUE3",  79, 148, 205),
        ("STEELBLUE4",  54, 100, 139),
        ("DEEPSKYBLUE1",   0, 191, 255),
        ("DEEPSKYBLUE2",   0, 178, 238),
        ("DEEPSKYBLUE3",   0, 154, 205),
        ("DEEPSKYBLUE4",   0, 104, 139),
        ("SKYBLUE1", 135, 206, 255),
        ("SKYBLUE2", 126, 192, 238),
        ("SKYBLUE3", 108, 166, 205),
        ("SKYBLUE4",  74, 112, 139),
        ("LIGHTSKYBLUE1", 176, 226, 255),
        ("LIGHTSKYBLUE2", 164, 211, 238),
        ("LIGHTSKYBLUE3", 141, 182, 205),
        ("LIGHTSKYBLUE4",  96, 123, 139),
        ("LIGHTSTEELBLUE1", 202, 225, 255),
        ("LIGHTSTEELBLUE2", 188, 210, 238),
        ("LIGHTSTEELBLUE3", 162, 181, 205),
        ("LIGHTSTEELBLUE4", 110, 123, 139),
        ("LIGHTBLUE1", 191, 239, 255),
        ("LIGHTBLUE2", 178, 223, 238),
        ("LIGHTBLUE3", 154, 192, 205),
        ("LIGHTBLUE4", 104, 131, 139),
        ("LIGHTCYAN1", 224, 255, 255),
        ("LIGHTCYAN2", 209, 238, 238),
        ("LIGHTCYAN3", 180, 205, 205),
        ("LIGHTCYAN4", 122, 139, 139),
        ("PALETURQUOISE1", 187, 255, 255),
        ("PALETURQUOISE2", 174, 238, 238),
        ("PALETURQUOISE3", 150, 205, 205),
        ("PALETURQUOISE4", 102, 139, 139),
        ("CADETBLUE1", 152, 245, 255),
        ("CADETBLUE2", 142, 229, 238),
        ("CADETBLUE3", 122, 197, 205),
        ("CADETBLUE4",  83, 134, 139),
        ("TURQUOISE1",   0, 245, 255),
        ("TURQUOISE2",   0, 229, 238),
        ("TURQUOISE3",   0, 197, 205),
        ("TURQUOISE4",   0, 134, 139),
        ("CYAN1",   0, 255, 255),
        ("CYAN2",   0, 238, 238),
        ("CYAN3",   0, 205, 205),
        ("CYAN4",   0, 139, 139),
        ("AQUAMARINE1", 127, 255, 212),
        ("AQUAMARINE2", 118, 238, 198),
        ("AQUAMARINE3", 102, 205, 170),
        ("AQUAMARINE4",  69, 139, 116),
        ("DARKSEAGREEN1", 193, 255, 193),
        ("DARKSEAGREEN2", 180, 238, 180),
        ("DARKSEAGREEN3", 155, 205, 155),
        ("DARKSEAGREEN4", 105, 139, 105),
        ("SEAGREEN1",  84, 255, 159),
        ("SEAGREEN2",  78, 238, 148),
        ("SEAGREEN3",  67, 205, 128),
        ("SEAGREEN4",  46, 139,  87),
        ("PALEGREEN1", 154, 255, 154),
        ("PALEGREEN2", 144, 238, 144),
        ("PALEGREEN3", 124, 205, 124),
        ("PALEGREEN4",  84, 139,  84),
        ("SPRINGGREEN1",   0, 255, 127),
        ("SPRINGGREEN2",   0, 238, 118),
        ("SPRINGGREEN3",   0, 205, 102),
        ("SPRINGGREEN4",   0, 139,  69),
        ("GREEN1",   0, 255,   0),
        ("GREEN2",   0, 238,   0),
        ("GREEN3",   0, 205,   0),
        ("GREEN4",   0, 139,   0),
        ("CHARTREUSE1", 127, 255,   0),
        ("CHARTREUSE2", 118, 238,   0),
        ("CHARTREUSE3", 102, 205,   0),
        ("CHARTREUSE4",  69, 139,   0),
        ("OLIVEDRAB1", 192, 255,  62),
        ("OLIVEDRAB2", 179, 238,  58),
        ("OLIVEDRAB3", 154, 205,  50),
        ("OLIVEDRAB4", 105, 139,  34),
        ("DARKOLIVEGREEN1", 202, 255, 112),
        ("DARKOLIVEGREEN2", 188, 238, 104),
        ("DARKOLIVEGREEN3", 162, 205,  90),
        ("DARKOLIVEGREEN4", 110, 139,  61),
        ("KHAKI1", 255, 246, 143),
        ("KHAKI2", 238, 230, 133),
        ("KHAKI3", 205, 198, 115),
        ("KHAKI4", 139, 134,  78),
        ("LIGHTGOLDENROD1", 255, 236, 139),
        ("LIGHTGOLDENROD2", 238, 220, 130),
        ("LIGHTGOLDENROD3", 205, 190, 112),
        ("LIGHTGOLDENROD4", 139, 129,  76),
        ("LIGHTYELLOW1", 255, 255, 224),
        ("LIGHTYELLOW2", 238, 238, 209),
        ("LIGHTYELLOW3", 205, 205, 180),
        ("LIGHTYELLOW4", 139, 139, 122),
        ("YELLOW1", 255, 255,   0),
        ("YELLOW2", 238, 238,   0),
        ("YELLOW3", 205, 205,   0),
        ("YELLOW4", 139, 139,   0),
        ("GOLD1", 255, 215,   0),
        ("GOLD2", 238, 201,   0),
        ("GOLD3", 205, 173,   0),
        ("GOLD4", 139, 117,   0),
        ("GOLDENROD1", 255, 193,  37),
        ("GOLDENROD2", 238, 180,  34),
        ("GOLDENROD3", 205, 155,  29),
        ("GOLDENROD4", 139, 105,  20),
        ("DARKGOLDENROD1", 255, 185,  15),
        ("DARKGOLDENROD2", 238, 173,  14),
        ("DARKGOLDENROD3", 205, 149,  12),
        ("DARKGOLDENROD4", 139, 101,   8),
        ("ROSYBROWN1", 255, 193, 193),
        ("ROSYBROWN2", 238, 180, 180),
        ("ROSYBROWN3", 205, 155, 155),
        ("ROSYBROWN4", 139, 105, 105),
        ("INDIANRED1", 255, 106, 106),
        ("INDIANRED2", 238,  99,  99),
        ("INDIANRED3", 205,  85,  85),
        ("INDIANRED4", 139,  58,  58),
        ("SIENNA1", 255, 130,  71),
        ("SIENNA2", 238, 121,  66),
        ("SIENNA3", 205, 104,  57),
        ("SIENNA4", 139,  71,  38),
        ("BURLYWOOD1", 255, 211, 155),
        ("BURLYWOOD2", 238, 197, 145),
        ("BURLYWOOD3", 205, 170, 125),
        ("BURLYWOOD4", 139, 115,  85),
        ("WHEAT1", 255, 231, 186),
        ("WHEAT2", 238, 216, 174),
        ("WHEAT3", 205, 186, 150),
        ("WHEAT4", 139, 126, 102),
        ("TAN1", 255, 165,  79),
        ("TAN2", 238, 154,  73),
        ("TAN3", 205, 133,  63),
        ("TAN4", 139,  90,  43),
        ("CHOCOLATE1", 255, 127,  36),
        ("CHOCOLATE2", 238, 118,  33),
        ("CHOCOLATE3", 205, 102,  29),
        ("CHOCOLATE4", 139,  69,  19),
        ("FIREBRICK1", 255,  48,  48),
        ("FIREBRICK2", 238,  44,  44),
        ("FIREBRICK3", 205,  38,  38),
        ("FIREBRICK4", 139,  26,  26),
        ("BROWN1", 255,  64,  64),
        ("BROWN2", 238,  59,  59),
        ("BROWN3", 205,  51,  51),
        ("BROWN4", 139,  35,  35),
        ("SALMON1", 255, 140, 105),
        ("SALMON2", 238, 130,  98),
        ("SALMON3", 205, 112,  84),
        ("SALMON4", 139,  76,  57),
        ("LIGHTSALMON1", 255, 160, 122),
        ("LIGHTSALMON2", 238, 149, 114),
        ("LIGHTSALMON3", 205, 129,  98),
        ("LIGHTSALMON4", 139,  87,  66),
        ("ORANGE1", 255, 165,   0),
        ("ORANGE2", 238, 154,   0),
        ("ORANGE3", 205, 133,   0),
        ("ORANGE4", 139,  90,   0),
        ("DARKORANGE1", 255, 127,   0),
        ("DARKORANGE2", 238, 118,   0),
        ("DARKORANGE3", 205, 102,   0),
        ("DARKORANGE4", 139,  69,   0),
        ("CORAL1", 255, 114,  86),
        ("CORAL2", 238, 106,  80),
        ("CORAL3", 205,  91,  69),
        ("CORAL4", 139,  62,  47),
        ("TOMATO1", 255,  99,  71),
        ("TOMATO2", 238,  92,  66),
        ("TOMATO3", 205,  79,  57),
        ("TOMATO4", 139,  54,  38),
        ("ORANGERED1", 255,  69,   0),
        ("ORANGERED2", 238,  64,   0),
        ("ORANGERED3", 205,  55,   0),
        ("ORANGERED4", 139,  37,   0),
        ("RED1", 255,   0,   0),
        ("RED2", 238,   0,   0),
        ("RED3", 205,   0,   0),
        ("RED4", 139,   0,   0),
        ("DEEPPINK1", 255,  20, 147),
        ("DEEPPINK2", 238,  18, 137),
        ("DEEPPINK3", 205,  16, 118),
        ("DEEPPINK4", 139,  10,  80),
        ("HOTPINK1", 255, 110, 180),
        ("HOTPINK2", 238, 106, 167),
        ("HOTPINK3", 205,  96, 144),
        ("HOTPINK4", 139,  58,  98),
        ("PINK1", 255, 181, 197),
        ("PINK2", 238, 169, 184),
        ("PINK3", 205, 145, 158),
        ("PINK4", 139,  99, 108),
        ("LIGHTPINK1", 255, 174, 185),
        ("LIGHTPINK2", 238, 162, 173),
        ("LIGHTPINK3", 205, 140, 149),
        ("LIGHTPINK4", 139,  95, 101),
        ("PALEVIOLETRED1", 255, 130, 171),
        ("PALEVIOLETRED2", 238, 121, 159),
        ("PALEVIOLETRED3", 205, 104, 137),
        ("PALEVIOLETRED4", 139,  71,  93),
        ("MAROON1", 255,  52, 179),
        ("MAROON2", 238,  48, 167),
        ("MAROON3", 205,  41, 144),
        ("MAROON4", 139,  28,  98),
        ("VIOLETRED1", 255,  62, 150),
        ("VIOLETRED2", 238,  58, 140),
        ("VIOLETRED3", 205,  50, 120),
        ("VIOLETRED4", 139,  34,  82),
        ("MAGENTA1", 255,   0, 255),
        ("MAGENTA2", 238,   0, 238),
        ("MAGENTA3", 205,   0, 205),
        ("MAGENTA4", 139,   0, 139),
        ("ORCHID1", 255, 131, 250),
        ("ORCHID2", 238, 122, 233),
        ("ORCHID3", 205, 105, 201),
        ("ORCHID4", 139,  71, 137),
        ("PLUM1", 255, 187, 255),
        ("PLUM2", 238, 174, 238),
        ("PLUM3", 205, 150, 205),
        ("PLUM4", 139, 102, 139),
        ("MEDIUMORCHID1", 224, 102, 255),
        ("MEDIUMORCHID2", 209,  95, 238),
        ("MEDIUMORCHID3", 180,  82, 205),
        ("MEDIUMORCHID4", 122,  55, 139),
        ("DARKORCHID1", 191,  62, 255),
        ("DARKORCHID2", 178,  58, 238),
        ("DARKORCHID3", 154,  50, 205),
        ("DARKORCHID4", 104,  34, 139),
        ("PURPLE1", 155,  48, 255),
        ("PURPLE2", 145,  44, 238),
        ("PURPLE3", 125,  38, 205),
        ("PURPLE4",  85,  26, 139),
        ("MEDIUMPURPLE1", 171, 130, 255),
        ("MEDIUMPURPLE2", 159, 121, 238),
        ("MEDIUMPURPLE3", 137, 104, 205),
        ("MEDIUMPURPLE4",  93,  71, 139),
        ("THISTLE1", 255, 225, 255),
        ("THISTLE2", 238, 210, 238),
        ("THISTLE3", 205, 181, 205),
        ("THISTLE4", 139, 123, 139),
        ("GREY0",   0,   0,   0),
        ("GREY1",   3,   3,   3),
        ("GREY2",   5,   5,   5),
        ("GREY3",   8,   8,   8),
        ("GREY4",  10,  10,  10),
        ("GREY5",  13,  13,  13),
        ("GREY6",  15,  15,  15),
        ("GREY7",  18,  18,  18),
        ("GREY8",  20,  20,  20),
        ("GREY9",  23,  23,  23),
        ("GREY10",  26,  26,  26),
        ("GREY11",  28,  28,  28),
        ("GREY12",  31,  31,  31),
        ("GREY13",  33,  33,  33),
        ("GREY14",  36,  36,  36),
        ("GREY15",  38,  38,  38),
        ("GREY16",  41,  41,  41),
        ("GREY17",  43,  43,  43),
        ("GREY18",  46,  46,  46),
        ("GREY19",  48,  48,  48),
        ("GREY20",  51,  51,  51),
        ("GREY21",  54,  54,  54),
        ("GREY22",  56,  56,  56),
        ("GREY23",  59,  59,  59),
        ("GREY24",  61,  61,  61),
        ("GREY25",  64,  64,  64),
        ("GREY26",  66,  66,  66),
        ("GREY27",  69,  69,  69),
        ("GREY28",  71,  71,  71),
        ("GREY29",  74,  74,  74),
        ("GREY30",  77,  77,  77),
        ("GREY31",  79,  79,  79),
        ("GREY32",  82,  82,  82),
        ("GREY33",  84,  84,  84),
        ("GREY34",  87,  87,  87),
        ("GREY35",  89,  89,  89),
        ("GREY36",  92,  92,  92),
        ("GREY37",  94,  94,  94),
        ("GREY38",  97,  97,  97),
        ("GREY39",  99,  99,  99),
        ("GREY40", 102, 102, 102),
        ("GREY41", 105, 105, 105),
        ("GREY42", 107, 107, 107),
        ("GREY43", 110, 110, 110),
        ("GREY44", 112, 112, 112),
        ("GREY45", 115, 115, 115),
        ("GREY46", 117, 117, 117),
        ("GREY47", 120, 120, 120),
        ("GREY48", 122, 122, 122),
        ("GREY49", 125, 125, 125),
        ("GREY50", 127, 127, 127),
        ("GREY51", 130, 130, 130),
        ("GREY52", 133, 133, 133),
        ("GREY53", 135, 135, 135),
        ("GREY54", 138, 138, 138),
        ("GREY55", 140, 140, 140),
        ("GREY56", 143, 143, 143),
        ("GREY57", 145, 145, 145),
        ("GREY58", 148, 148, 148),
        ("GREY59", 150, 150, 150),
        ("GREY60", 153, 153, 153),
        ("GREY61", 156, 156, 156),
        ("GREY62", 158, 158, 158),
        ("GREY63", 161, 161, 161),
        ("GREY64", 163, 163, 163),
        ("GREY65", 166, 166, 166),
        ("GREY66", 168, 168, 168),
        ("GREY67", 171, 171, 171),
        ("GREY68", 173, 173, 173),
        ("GREY69", 176, 176, 176),
        ("GREY70", 179, 179, 179),
        ("GREY71", 181, 181, 181),
        ("GREY72", 184, 184, 184),
        ("GREY73", 186, 186, 186),
        ("GREY74", 189, 189, 189),
        ("GREY75", 191, 191, 191),
        ("GREY76", 194, 194, 194),
        ("GREY77", 196, 196, 196),
        ("GREY78", 199, 199, 199),
        ("GREY79", 201, 201, 201),
        ("GREY80", 204, 204, 204),
        ("GREY81", 207, 207, 207),
        ("GREY82", 209, 209, 209),
        ("GREY83", 212, 212, 212),
        ("GREY84", 214, 214, 214),
        ("GREY85", 217, 217, 217),
        ("GREY86", 219, 219, 219),
        ("GREY87", 222, 222, 222),
        ("GREY88", 224, 224, 224),
        ("GREY89", 227, 227, 227),
        ("GREY90", 229, 229, 229),
        ("GREY91", 232, 232, 232),
        ("GREY92", 235, 235, 235),
        ("GREY93", 237, 237, 237),
        ("GREY94", 240, 240, 240),
        ("GREY95", 242, 242, 242),
        ("GREY96", 245, 245, 245),
        ("GREY97", 247, 247, 247),
        ("GREY98", 250, 250, 250),
        ("GREY99", 252, 252, 252),
        ("GREY100", 255, 255, 255),
        ("DARK GREY", 169, 169, 169),
        ("DARKGREY", 169, 169, 169),
        ("DARK BLUE", 0,     0, 139),
        ("DARKBLUE", 0,     0, 139),
        ("DARK CYAN", 0,   139, 139),
        ("DARKCYAN", 0,   139, 139),
        ("DARK MAGENTA", 139,   0, 139),
        ("DARKMAGENTA", 139,   0, 139),
        ("DARK RED", 139,   0,   0),
        ("DARKRED", 139,   0,   0),
        ("LIGHT GREEN", 144, 238, 144),
        ("LIGHTGREEN", 144, 238, 144),
        ]


_haveUpdated = False

def updateColourDB():
    """Updates the wx colour database by adding new colour names and RGB values."""
    global _haveUpdated
    if not _haveUpdated:
        import wx
        assert wx.GetApp() is not None, "You must have a wx.App object before you can use the colour database."
        cl = getColourInfoList()
        
        for info in cl:
            wx.TheColourDatabase.Append(*info)
            
        _haveUpdated = True

