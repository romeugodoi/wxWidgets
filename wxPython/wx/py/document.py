
"""Renamer stub: provides a way to drop the wx prefix from wxPython objects."""

from wx import _rename
from wxPython.py import document
_rename(globals(), document.__dict__, modulename='py.document')
del document
del _rename
