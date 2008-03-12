/////////////////////////////////////////////////////////////////////////////
// Name:        grid.h
// Purpose:     topic overview
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**

 @page overview_grid wxGrid Overview

 Classes: wxGrid

 @li @ref overview_grid_intro
 @li @ref overview_grid_simpleexample
 @li @ref overview_grid_complexexample
 @li @ref overview_grid_classrelations
 @li @ref overview_grid_keyboardmouse


 <hr>


 @section overview_grid_intro Introduction

 wxGrid and its related classes are used for displaying and editing tabular data.


 @section overview_grid_simpleexample Getting started: a simple example

 For simple applications you need only refer to the wxGrid class in your
 code. This example shows how you might create a grid in a frame or
 dialog constructor and illustrates some of the formatting functions.

 @code
     // Create a wxGrid object

     grid = new wxGrid( this,
                        -1,
                        wxPoint( 0, 0 ),
                        wxSize( 400, 300 ) );

     // Then we call CreateGrid to set the dimensions of the grid
     // (100 rows and 10 columns in this example)
     grid->CreateGrid( 100, 10 );

     // We can set the sizes of individual rows and columns
     // in pixels
     grid->SetRowSize( 0, 60 );
     grid->SetColSize( 0, 120 );

     // And set grid cell contents as strings
     grid->SetCellValue( 0, 0, "wxGrid is good" );

     // We can specify that some cells are read->only
     grid->SetCellValue( 0, 3, "This is read->only" );
     grid->SetReadOnly( 0, 3 );

     // Colours can be specified for grid cell contents
     grid->SetCellValue(3, 3, "green on grey");
     grid->SetCellTextColour(3, 3, *wxGREEN);
     grid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);

     // We can specify the some cells will store numeric
     // values rather than strings. Here we set grid column 5
     // to hold floating point values displayed with width of 6
     // and precision of 2
     grid->SetColFormatFloat(5, 6, 2);
     grid->SetCellValue(0, 6, "3.1415");
 @endcode


 @section overview_grid_complexexample A more complex example

 Yet to be written


 @section overview_grid_classrelations How the wxGrid classes relate to each other

 Yet to be written


 @section overview_grid_keyboardmouse Keyboard and mouse actions

 Yet to be written

*/

