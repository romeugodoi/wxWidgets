/////////////////////////////////////////////////////////////////////////////
// Name:        colour.h
// Purpose:     wxColour class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_COLOUR_H_
#define _WX_COLOUR_H_

#include "wx/object.h"

// Colour
class WXDLLEXPORT wxColour: public wxObject
{
public:
    // ctors
      // default
    wxColour();
      // from RGB
    wxColour(unsigned char red, unsigned char green, unsigned char blue)
        { Set(red, green, blue); }
    wxColour(unsigned long colRGB) { Set(colRGB); }

      // implicit conversion from the colour name
    wxColour(const wxString &colourName) { InitFromName(colourName); }
    wxColour(const char *colourName) { InitFromName(colourName); }


      // copy ctors and assignment operators
    wxColour(const wxColour& col);
    wxColour& operator = (const wxColour& col);

      // dtor
    ~wxColour();

    // Set() functions
    void Set(unsigned char red, unsigned char green, unsigned char blue);
    void Set(unsigned long colRGB)
    {
      // we don't need to know sizeof(long) here because we assume that the three
      // least significant bytes contain the R, G and B values
      Set((unsigned char)colRGB,
          (unsigned char)(colRGB >> 8),
          (unsigned char)(colRGB >> 16));
    }

    // accessors
    bool Ok() const { return m_isInit; }

    unsigned char Red() const { return m_red; }
    unsigned char Green() const { return m_green; }
    unsigned char Blue() const { return m_blue; }

    // comparison
    bool operator == (const wxColour& colour) const
    {
      return (m_red == colour.m_red &&
              m_green == colour.m_green &&
              m_blue == colour.m_blue &&
              m_isInit == colour.m_isInit);
    }
    bool operator != (const wxColour& colour) const { return !(*this == colour); }

    void InitFromName(const wxString& colourName);

protected:

    // Helper function
    void Init();

private:
    bool m_isInit;
    unsigned char m_red;
    unsigned char m_blue;
    unsigned char m_green;

private:
    DECLARE_DYNAMIC_CLASS(wxColour)
};

#endif
        // _WX_COLOUR_H_
