
"""Renamer stub: provides a way to drop the wx prefix from wxPython objects."""

from wx import _rename
from wxPython.tools.XRCed import encode_bitmaps
_rename(globals(), encode_bitmaps.__dict__, modulename='tools.XRCed.encode_bitmaps')
del encode_bitmaps
del _rename
