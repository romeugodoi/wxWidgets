
"""Renamer stub: provides a way to drop the wx prefix from wxPython objects."""

from wx import _rename
from wxPython.lib import intctrl
_rename(globals(), intctrl.__dict__, modulename='lib.intctrl')
del intctrl
del _rename
