/////////////////////////////////////////////////////////////////////////////
// Name:        zstream.h
// Purpose:     Memory stream classes
// Author:      Guilhem Lavaux
// Modified by:
// Created:     11/07/98
// RCS-ID:      $Id$
// Copyright:   (c) Guilhem Lavaux
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_WXZSTREAM_H__
#define _WX_WXZSTREAM_H__

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "zstream.h"
#endif

#include "wx/defs.h"

#if wxUSE_ZLIB && wxUSE_STREAMS

#include "wx/stream.h"

class WXDLLIMPEXP_BASE wxZlibInputStream: public wxFilterInputStream {
 public:
  wxZlibInputStream(wxInputStream& stream);
  virtual ~wxZlibInputStream();

 protected:
  size_t OnSysRead(void *buffer, size_t size);

 protected:
  size_t m_z_size;
  unsigned char *m_z_buffer;
  struct z_stream_s *m_inflate;

    DECLARE_NO_COPY_CLASS(wxZlibInputStream)
};

class WXDLLIMPEXP_BASE wxZlibOutputStream: public wxFilterOutputStream {
 public:
  wxZlibOutputStream(wxOutputStream& stream, int level = -1);
  virtual ~wxZlibOutputStream();

  void Sync();

 protected:
  size_t OnSysWrite(const void *buffer, size_t size);

 protected:
  size_t m_z_size;
  unsigned char *m_z_buffer;
  struct z_stream_s *m_deflate;

    DECLARE_NO_COPY_CLASS(wxZlibOutputStream)
};

#endif
  // wxUSE_ZLIB && wxUSE_STREAMS

#endif
   // _WX_WXZSTREAM_H__

