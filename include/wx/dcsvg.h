/////////////////////////////////////////////////////////////////////////////
// Name:        wx/dcsvg.h
// Purpose:     wxSVGFileDC
// Author:      Chris Elliott
// Modified by:
// Created:
// Copyright:   (c) Chris Elliott
// RCS-ID:      $Id$
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_DCSVG_H_
#define _WX_DCSVG_H_

#include "wx/string.h"
#include "wx/dc.h"

#if wxUSE_SVG

#define wxSVGVersion wxT("v0100")

#ifdef __BORLANDC__
#pragma warn -8008
#pragma warn -8066
#endif

class WXDLLIMPEXP_FWD_BASE wxFileOutputStream;

class WXDLLIMPEXP_CORE wxSVGFileDC : public wxDC
{
public:
    wxSVGFileDC (wxString f);
    wxSVGFileDC (wxString f, int Width, int Height);
    wxSVGFileDC (wxString f, int Width, int Height, float dpi);

    virtual ~wxSVGFileDC();

    virtual bool CanDrawBitmap() const { return true; }
    virtual bool CanGetTextExtent() const { return true; }

    virtual int GetDepth() const
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::GetDepth Call not implemented"));
        return -1;
    }

    virtual void Clear()
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::Clear() Call not implemented \nNot sensible for an output file?"));
    }

    virtual void DestroyClippingRegion()
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::void Call not yet implemented"));
    }

    virtual wxCoord GetCharHeight() const;
    virtual wxCoord GetCharWidth() const;

    virtual void SetClippingRegion(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y),
                                   wxCoord WXUNUSED(w), wxCoord WXUNUSED(h))
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::SetClippingRegion not implemented"));
    }

    virtual void SetPalette(const wxPalette&  WXUNUSED(palette))
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::SetPalette not implemented"));
    }

    virtual void GetClippingBox(wxCoord *WXUNUSED(x), wxCoord *WXUNUSED(y),
                                wxCoord *WXUNUSED(w), wxCoord *WXUNUSED(h))
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::GetClippingBox not implemented"));
    }

    virtual void SetLogicalFunction(int WXUNUSED(function))
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::SetLogicalFunction Call not implemented"));
    }

    virtual int GetLogicalFunction() const
    {
        wxFAIL_MSG(wxT("wxSVGFILEDC::GetLogicalFunction() not implemented"));
        return -1;
    }

    virtual void SetBackground( const wxBrush &brush );
    virtual void SetBackgroundMode( int mode );
    virtual void SetBrush(const wxBrush& brush);
    virtual void SetFont(const wxFont& font);
    virtual void SetPen(const wxPen& pen);

    virtual bool IsOk() const {return m_OK;}

    virtual void SetMapMode( int mode );
    virtual void SetUserScale( double x, double y );
    virtual void SetLogicalScale( double x, double y );
    virtual void SetLogicalOrigin( wxCoord x, wxCoord y );
    virtual void SetDeviceOrigin( wxCoord x, wxCoord y );
    virtual void SetAxisOrientation( bool xLeftRight, bool yBottomUp );

private:
   virtual bool DoGetPixel(wxCoord, wxCoord, wxColour *) const
   {
       wxFAIL_MSG(wxT("wxSVGFILEDC::DoGetPixel Call not implemented"));
       return true;
   }

   virtual bool DoBlit(wxCoord, wxCoord, wxCoord, wxCoord, wxDC *,
                       wxCoord, wxCoord, int = wxCOPY,
                       bool = 0, int = -1, int = -1);

   virtual void DoCrossHair(wxCoord, wxCoord)
   {
       wxFAIL_MSG(wxT("wxSVGFILEDC::CrossHair Call not implemented"));
   }

   virtual void DoDrawArc(wxCoord, wxCoord, wxCoord, wxCoord, wxCoord, wxCoord);

   virtual void DoDrawBitmap(const wxBitmap &, wxCoord, wxCoord, bool = 0);

   virtual void DoDrawCheckMark(wxCoord x, wxCoord y, wxCoord w, wxCoord h);

   virtual void DoDrawEllipse(wxCoord x, wxCoord y, wxCoord w, wxCoord h);

   virtual void DoDrawEllipticArc(wxCoord x, wxCoord y, wxCoord w, wxCoord h,
                                  double sa, double ea);

   virtual void DoDrawIcon(const wxIcon &, wxCoord, wxCoord);

   virtual void DoDrawLine (wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2);

   virtual void DoDrawLines(int n, wxPoint points[],
                            wxCoord xoffset = 0, wxCoord yoffset = 0);

   virtual void DoDrawPoint(wxCoord, wxCoord);

   virtual void DoDrawPolygon(int n, wxPoint points[], wxCoord xoffset, wxCoord yoffset,int fillStyle);

   virtual void DoDrawRectangle(wxCoord x, wxCoord y, wxCoord w, wxCoord h);

   virtual void DoDrawRotatedText(const wxString& text, wxCoord x, wxCoord y,
                                  double angle);

   virtual void DoDrawRoundedRectangle(wxCoord x, wxCoord y,
                                       wxCoord w, wxCoord h,
                                       double radius = 20) ;

   virtual void DoDrawText(const wxString& text, wxCoord x, wxCoord y);

   virtual bool DoFloodFill(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y),
                            const wxColour& WXUNUSED(col),
                            int WXUNUSED(style) = wxFLOOD_SURFACE)
   {
       wxFAIL_MSG(wxT("wxSVGFILEDC::DoFloodFill Call not implemented"));
       return false;
   }

   virtual void DoGetSize(int * x, int *y) const
   {
       if ( x )
           *x = m_width;
       if ( y )
           *y = m_height;
   }

   virtual void DoGetTextExtent(const wxString& string, wxCoord *w, wxCoord *h,
                                wxCoord *descent = NULL,
                                wxCoord *externalLeading = NULL,
                                const wxFont *font = NULL) const;

   virtual void DoSetClippingRegionAsRegion(const wxRegion& WXUNUSED(region))
   {
       wxFAIL_MSG(wxT("wxSVGFILEDC::DoSetClippingRegionAsRegion Call not yet implemented"));
   }

   void Init (wxString f, int Width, int Height, float dpi);

   void NewGraphics();

   void write( const wxString &s );

private:
   wxFileOutputStream *m_outfile;
   wxString            m_filename;
   int                 m_sub_images; // number of png format images we have
   bool                m_OK;
   bool                m_graphics_changed;
   int                 m_width, m_height;

private:
   DECLARE_ABSTRACT_CLASS(wxSVGFileDC)
};

#endif // wxUSE_SVG

#endif // _WX_DCSVG_H_
