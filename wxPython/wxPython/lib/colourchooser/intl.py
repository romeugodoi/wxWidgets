"""
wxPyColourChooser
Copyright (C) 2002 Michael Gilfix <mgilfix@eecs.tufts.edu>

This file is part of wxPyColourChooser.

This version of wxPyColourChooser is open source; you can redistribute it
and/or modify it under the licensed terms.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
"""

try:
    import gettext

    gettext.bindtextdomain('wxpycolourchooser')
    gettext.textdomain('wxpycolourchooser')
    _ = gettext.gettext
except Exception, strerror:
    print "Warning: Couldn't import translation function: %(str)s" %{ 'str' : strerror }
    print "Defaulting to En"
    _ = lambda x: x
