#Makefile from wxHatch for Symantec/Digital Mars compiler 
WXDIR=..\..\..\wxWindows
TARGET=image
OBJECTS = $(TARGET).obj 
EXTRALIBS =
include $(WXDIR)\src\makeprog.sc
