/////////////////////////////////////////////////////////////////////////////
// Name:        src/qt/brush.cpp
// Author:      Peter Most, Javier Torres
// Id:          $Id$
// Copyright:   (c) Peter Most, Javier Torres
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/brush.h"
#include "wx/colour.h"
#include "wx/qt/utils.h"

#include <QtGui/QBrush>


static Qt::BrushStyle ConvertBrushStyle(wxBrushStyle style)
{
    switch (style) {
        case wxBRUSHSTYLE_SOLID: return Qt::SolidPattern;
        case wxBRUSHSTYLE_TRANSPARENT: return Qt::NoBrush;
        case wxBRUSHSTYLE_STIPPLE_MASK_OPAQUE:
        case wxBRUSHSTYLE_STIPPLE_MASK: wxMISSING_IMPLEMENTATION( "wxBrush stipple masks" );
        case wxBRUSHSTYLE_STIPPLE: return Qt::TexturePattern;
        case wxBRUSHSTYLE_BDIAGONAL_HATCH: return Qt::BDiagPattern;
        case wxBRUSHSTYLE_CROSSDIAG_HATCH: return Qt::DiagCrossPattern;
        case wxBRUSHSTYLE_FDIAGONAL_HATCH: return Qt::FDiagPattern;
        case wxBRUSHSTYLE_CROSS_HATCH: return Qt::CrossPattern;
        case wxBRUSHSTYLE_HORIZONTAL_HATCH: return Qt::HorPattern;
        case wxBRUSHSTYLE_VERTICAL_HATCH: return Qt::VerPattern;
        
        default: return Qt::SolidPattern;
    }
}

static wxBrushStyle ConvertBrushStyle(Qt::BrushStyle style)
{
    switch (style) {
        case Qt::SolidPattern: return wxBRUSHSTYLE_SOLID;
        case Qt::NoBrush: return wxBRUSHSTYLE_TRANSPARENT;
        case Qt::TexturePattern: return wxBRUSHSTYLE_STIPPLE;
        case Qt::BDiagPattern: return wxBRUSHSTYLE_BDIAGONAL_HATCH;
        case Qt::DiagCrossPattern: return wxBRUSHSTYLE_CROSSDIAG_HATCH;
        case Qt::FDiagPattern: return wxBRUSHSTYLE_FDIAGONAL_HATCH;
        case Qt::CrossPattern: return wxBRUSHSTYLE_CROSS_HATCH;
        case Qt::HorPattern: return wxBRUSHSTYLE_HORIZONTAL_HATCH;
        case Qt::VerPattern: return wxBRUSHSTYLE_VERTICAL_HATCH;
        
        default: wxFAIL_MSG( "Unknown QBrush style" );
    }
    
    return wxBRUSHSTYLE_SOLID;
}

//-----------------------------------------------------------------------------
// wxBrush
//-----------------------------------------------------------------------------

class wxBrushRefData: public wxGDIRefData
{
    public:
        wxBrushRefData()
        {
        }
        
        wxBrushRefData( const wxBrushRefData& data )
        : wxGDIRefData()
        {
            m_qtBrush = data.m_qtBrush;
        }
        
        bool operator == (const wxBrushRefData& data) const
        {
            return m_qtBrush == data.m_qtBrush;
        }
        
        QBrush m_qtBrush;
};

//-----------------------------------------------------------------------------

#define M_BRUSHDATA ((wxBrushRefData *)m_refData)->m_qtBrush

wxBrush::wxBrush()
{
    m_refData = new wxBrushRefData();
}

wxBrush::wxBrush(const wxColour& col, wxBrushStyle style )
{
    m_refData = new wxBrushRefData();
    M_BRUSHDATA.setColor(col.GetHandle());
    M_BRUSHDATA.setStyle(ConvertBrushStyle(style));
}

#if FUTURE_WXWIN_COMPATIBILITY_3_0
wxBrush::wxBrush(const wxColour& col, int style)
{
    m_refData = new wxBrushRefData();
    M_BRUSHDATA.setColor(col.GetHandle());
    M_BRUSHDATA.setStyle(ConvertBrushStyle((wxBrushStyle)style));
}

#endif
wxBrush::wxBrush(const wxBitmap& WXUNUSED(stipple))
{
    wxMISSING_IMPLEMENTATION( "wxBrush stipples" );
}


void wxBrush::SetColour(const wxColour& col)
{
    AllocExclusive();
    M_BRUSHDATA.setColor(col.GetHandle());
}

void wxBrush::SetColour(unsigned char r, unsigned char g, unsigned char b)
{
    AllocExclusive();
    M_BRUSHDATA.setColor(QColor(r, g, b));
}

void wxBrush::SetStyle(wxBrushStyle style)
{
    AllocExclusive();
    M_BRUSHDATA.setStyle(ConvertBrushStyle((wxBrushStyle)style));
}

void wxBrush::SetStipple(const wxBitmap& WXUNUSED(stipple))
{
    wxMISSING_IMPLEMENTATION( "wxBrush stipples" );
}


bool wxBrush::operator==(const wxBrush& brush) const
{
    if (m_refData == brush.m_refData) return true;
    
    if (!m_refData || !brush.m_refData) return false;
    
    return ( *(wxBrushRefData*)m_refData == *(wxBrushRefData*)brush.m_refData );
}


wxColour wxBrush::GetColour() const
{
    return wxColour(M_BRUSHDATA.color());
}

wxBrushStyle wxBrush::GetStyle() const
{
    return ConvertBrushStyle(M_BRUSHDATA.style());
}

wxBitmap *wxBrush::GetStipple() const
{
    wxMISSING_IMPLEMENTATION( "wxBrush stipples" );
    return NULL;
}

QBrush wxBrush::GetHandle() const
{
    return M_BRUSHDATA;
}

wxGDIRefData *wxBrush::CreateGDIRefData() const
{
    return new wxBrushRefData;
}

wxGDIRefData *wxBrush::CloneGDIRefData(const wxGDIRefData *data) const
{
    return new wxBrushRefData(*(wxBrushRefData *)data);
}
