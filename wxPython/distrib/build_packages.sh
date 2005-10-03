#!/bin/bash

PY_VERSION=$1
shift

unicode=no
debug=no

for flag in $*; do
    case ${flag} in
      debug)       debug=yes              ;;
      unicode)     unicode=yes            ;;
    esac
done

if [ "$WXWIN" = "" ]; then
  export WXWIN=`pwd`/../..
fi

echo "wxWidgets directory is: $WXWIN"

if [ "$OSTYPE" = "cygwin" ]; then
  # do setup of build environment vars
  if [ "$TOOLS" = "" ]; then
    export TOOLS=`cygpath C:\\`
  fi

  if [ "$SWIGDIR" = "" ]; then
    export SWIGDIR=$TOOLS/SWIG-1.3.24
  fi

  DEBUG_FLAG=
  UNICODE_FLAG=
  if [ $debug = yes ]; then
    DEBUG_FLAG=--debug
  fi
  if [ $unicode = yes ]; then
    UNICODE_FLAG="UNICODE=1"
  fi

  # copy wxPython build scripts
  cp $WXWIN/wxPython/distrib/msw/.m* $WXWIN/build/msw
  
  # setup wxPython defines
  cp $WXWIN/include/wx/msw/setup0.h $WXWIN/include/wx/msw/setup.h
  $TOOLS/Python$PY_VERSION/python `cygpath -d $WXWIN/wxPython/distrib/create_setup.h.py` $UNICODE_FLAG
  
  export PATH=${PATH}:${WXWIN}/lib/vc_dll:${TOOLS}/Python${PY_VERSION}
  
  cd $WXWIN/build/msw
  # remove old build files
  rm -rf vc_msw*
  UNI=
  if [ $unicode = yes ]; then
      UNI=-uni
  fi
  ./.make hybrid$UNI
  
  # make tools for docs creation, etc.
  ./.make_tools
  
  # update the language files
  cd $WXWIN/locale
  make allmo
  
  $TOOLS/Python$PY_VERSION/python `cygpath -d $WXWIN/wxPython/distrib/makemo.py`

  cd $WXWIN/wxPython

  rm -rf build build.unicode
  rm -rf wx/*.pyd
  
  # re-generate SWIG files
  $WXWIN/wxPython/b $PY_VERSION t
  
  # build the hybrid extension
  # NOTE: Win Python needs Windows-style pathnames, so we 
  # need to convert
  export WXWIN=`cygpath -w $WXWIN`
  export SWIGDIR=`cygpath -w $SWIGDIR`
  
  $WXWIN/wxPython/b $PY_VERSION h $DEBUG_FLAG $UNICODE_FLAG
  
  # make the dev package
  $WXWIN/wxPython/distrib/makedev
  
  $TOOLS/Python$PY_VERSION/python `cygpath -d $WXWIN/wxPython/distrib/make_installer_inno4.py` $UNICODE_FLAG
elif [ "$OSTYPE" = "darwin" ]; then
  cd $WXWIN/wxPython
  
  # re-generate SWIG files
  $WXWIN/wxPython/b $PY_VERSION t
  
  PY_DOT_VER=2.3
  if [ "$PY_VERSION" = "24" ]; then
    PY_DOT_VER=2.4
  fi
  
  UNICODE_OPT=
  if [ $unicode = yes ]; then
    UNICODE_OPT=unicode
  fi 
  
  sudo distrib/mac/wxPythonOSX/build $PY_DOT_VER panther inplace $UNICODE_OPT
else
  echo "OSTYPE $OSTYPE not yet supported by this build script."
fi

# Now make the demo and docs tarballs
cd $WXWIN/wxPython
$WXWIN/wxPython/distrib/makedocs
$WXWIN/wxPython/distrib/makedemo

