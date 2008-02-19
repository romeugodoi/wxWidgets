/////////////////////////////////////////////////////////////////////////////
// Name:        platdetails.h
// Purpose:     Platform details page of the Doxygen manual
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


/*!

 @page platformdetails_page Platform details

 wxWidgets defines a common API across platforms, but uses the native graphical
 user interface (GUI) on each platform, so your program will take on the native
 look and feel that users are familiar with. Unfortunately native toolkits and
 hardware do not always support the functionality that the wxWidgets API
 requires. This chapter collects notes about differences among supported platforms
 and ports.

 @li @ref nativedocs


 <hr>

 \input wxgtk.tex
 \input wxmsw.tex
 \input wxmac.tex
 \input wxpalm.tex
 \input wxos2.tex
 \input wxmgl.tex
 \input wxx11.tex


 @section nativedocs Documentation for the native toolkits

 It's sometimes useful to interface directly with the underlying toolkit
 used by wxWidgets to e.g. use toolkit-specific features.
 In such case (or when you want to e.g. write a port-specific patch) it can be
 necessary to use the underlying toolkit API directly:

 @li wxMSW port uses win32 API: see MSDN docs at http://msdn2.microsoft.com/en-us/library/ms649779.aspx
 @li wxGTK port uses GTK+: see GTK+ 2.x docs at http://developer.gnome.org/doc/API/2.0/gtk/index.html

*/
