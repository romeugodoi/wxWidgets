///////////////////////////////////////////////////////////////////////////////
// Name:        src/ribbon/buttonbar.cpp
// Purpose:     Ribbon control similar to a tool bar
// Author:      Peter Cawley
// Modified by:
// Created:     2009-07-01
// RCS-ID:      $Id$
// Copyright:   (C) Peter Cawley
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/ribbon/buttonbar.h"

#if wxUSE_RIBBON

#include "wx/ribbon/art.h"
#include "wx/dcbuffer.h"

#ifndef WX_PRECOMP
#endif

#ifdef __WXMSW__
#include "wx/msw/private.h"
#endif

IMPLEMENT_CLASS(wxRibbonButtonBar, wxRibbonControl)

BEGIN_EVENT_TABLE(wxRibbonButtonBar, wxRibbonControl)
    EVT_ERASE_BACKGROUND(wxRibbonButtonBar::OnEraseBackground)
    EVT_PAINT(wxRibbonButtonBar::OnPaint)
    EVT_SIZE(wxRibbonButtonBar::OnSize)
END_EVENT_TABLE()

class wxRibbonButtonBarButtonSizeInfo
{
public:
    bool is_supported;
    wxSize size;
    wxRect normal_region;
    wxRect dropdown_region;
};

class wxRibbonButtonBarButtonInstance
{
public:
    wxPoint position;
    wxRibbonButtonBarButtonBase* base;
    wxRibbonButtonBarButtonState size;
};

class wxRibbonButtonBarButtonBase
{
public:
    wxRibbonButtonBarButtonInstance NewInstance()
    {
        wxRibbonButtonBarButtonInstance i;
        i.base = this;
        return i;
    }

    wxRibbonButtonBarButtonState GetLargestSize()
    {
        if(sizes[wxRIBBON_BUTTONBAR_BUTTON_LARGE].is_supported)
            return wxRIBBON_BUTTONBAR_BUTTON_LARGE;
        if(sizes[wxRIBBON_BUTTONBAR_BUTTON_MEDIUM].is_supported)
            return wxRIBBON_BUTTONBAR_BUTTON_MEDIUM;
        wxASSERT(sizes[wxRIBBON_BUTTONBAR_BUTTON_SMALL].is_supported);
        return wxRIBBON_BUTTONBAR_BUTTON_SMALL;
    }

    bool GetSmallerSize(
        wxRibbonButtonBarButtonState* size, int n = 1)
    {
        for(; n > 0; --n)
        {
            switch(*size)
            {
            case wxRIBBON_BUTTONBAR_BUTTON_LARGE:
                if(sizes[wxRIBBON_BUTTONBAR_BUTTON_MEDIUM].is_supported)
                {
                    *size = wxRIBBON_BUTTONBAR_BUTTON_MEDIUM;
                    break;
                }
            case wxRIBBON_BUTTONBAR_BUTTON_MEDIUM:
                if(sizes[wxRIBBON_BUTTONBAR_BUTTON_SMALL].is_supported)
                {
                    *size = wxRIBBON_BUTTONBAR_BUTTON_SMALL;
                    break;
                }
            case wxRIBBON_BUTTONBAR_BUTTON_SMALL:
            default:
                return false;
            }
        }
        return true;
    }

    wxString label;
    wxString help_string;
    wxBitmap bitmap_large;
    wxBitmap bitmap_large_disabled;
    wxBitmap bitmap_small;
    wxBitmap bitmap_small_disabled;
    wxRibbonButtonBarButtonSizeInfo sizes[3];
    wxObject* client_data;
    int id;
    wxRibbonButtonBarButtonKind kind;
    long state;
};

WX_DECLARE_OBJARRAY(wxRibbonButtonBarButtonInstance, wxArrayRibbonButtonBarButtonInstance);
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayRibbonButtonBarButtonInstance);

class wxRibbonButtonBarLayout
{
public:
    wxSize overall_size;
    wxArrayRibbonButtonBarButtonInstance buttons;

    void CalculateOverallSize()
    {
        overall_size = wxSize(0, 0);
        size_t btn_count = buttons.Count();
        size_t btn_i;
        for(btn_i = 0; btn_i < btn_count; ++btn_i)
        {
            wxRibbonButtonBarButtonInstance& instance = buttons.Item(btn_i);
            wxSize size = instance.base->sizes[instance.size].size;
            int right = instance.position.x + size.GetWidth();
            int bottom = instance.position.y + size.GetHeight();
            if(right > overall_size.GetWidth())
            {
                overall_size.SetWidth(right);
            }
            if(bottom > overall_size.GetHeight())
            {
                overall_size.SetHeight(bottom);
            }
        }
    }
};

wxRibbonButtonBar::wxRibbonButtonBar()
{
    m_layouts_valid = false;
}

wxRibbonButtonBar::wxRibbonButtonBar(wxWindow* parent,
                  wxWindowID id,
                  const wxPoint& pos,
                  const wxSize& size,
                  long style)
    : wxRibbonControl(parent, id, pos, size, wxBORDER_NONE)
{
    m_layouts_valid = false;

    CommonInit(style);
}

wxRibbonButtonBar::~wxRibbonButtonBar()
{
    size_t count = m_buttons.GetCount();
    size_t i;
    for(i = 0; i < count; ++i)
    {
        wxRibbonButtonBarButtonBase* button = m_buttons.Item(i);
        delete button;
    }
    m_buttons.Clear();

    count = m_layouts.GetCount();
    for(i = 0; i < count; ++i)
    {
        wxRibbonButtonBarLayout* layout = m_layouts.Item(i);
        delete layout;
    }
    m_layouts.Clear();
}

bool wxRibbonButtonBar::Create(wxWindow* parent,
                wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style)
{
    if(!wxRibbonControl::Create(parent, id, pos, size, wxBORDER_NONE))
    {
        return false;
    }

    CommonInit(style);
    return true;
}

wxRibbonButtonBarButtonBase* wxRibbonButtonBar::AddButton(
                int button_id,
                const wxString& label,
                const wxBitmap& bitmap,
                const wxString& help_string,
                wxRibbonButtonBarButtonKind kind)
{
    return AddButton(button_id, label, bitmap, wxNullBitmap, wxNullBitmap,
        wxNullBitmap, kind, help_string);
}

wxRibbonButtonBarButtonBase* wxRibbonButtonBar::AddDropdownButton(
                int button_id,
                const wxString& label,
                const wxBitmap& bitmap,
                const wxString& help_string)
{
    return AddButton(button_id, label, bitmap, help_string,
        wxRIBBON_BUTTONBAR_BUTTON_DROPDOWN);
}

wxRibbonButtonBarButtonBase* wxRibbonButtonBar::AddHybridButton(
                int button_id,
                const wxString& label,
                const wxBitmap& bitmap,
                const wxString& help_string)
{
    return AddButton(button_id, label, bitmap, help_string,
        wxRIBBON_BUTTONBAR_BUTTON_HYBRID);
}
    
wxRibbonButtonBarButtonBase* wxRibbonButtonBar::AddButton(
                int button_id,
                const wxString& label,
                const wxBitmap& bitmap,
                const wxBitmap& bitmap_small,
                const wxBitmap& bitmap_disabled,
                const wxBitmap& bitmap_small_disabled,
                wxRibbonButtonBarButtonKind kind,
                const wxString& help_string,
                wxObject* client_data)
{
    wxASSERT(bitmap.IsOk() || bitmap_small.IsOk());
    if(m_buttons.IsEmpty())
    {
        if(bitmap.IsOk())
        {
            m_bitmap_size_large = bitmap.GetSize();
            if(!bitmap_small.IsOk())
            {
                m_bitmap_size_small = m_bitmap_size_large;
                m_bitmap_size_small *= 0.5;
            }
        }
        if(bitmap_small.IsOk())
        {
            m_bitmap_size_small = bitmap_small.GetSize();
            if(!bitmap.IsOk())
            {
                m_bitmap_size_large = m_bitmap_size_small;
                m_bitmap_size_large *= 2.0;
            }
        }
    }

    wxRibbonButtonBarButtonBase* base = new wxRibbonButtonBarButtonBase;
    base->id = button_id;
    base->label = label;
    base->bitmap_large = bitmap;
    if(!base->bitmap_large.IsOk())
    {
        base->bitmap_large = MakeResizedBitmap(base->bitmap_small,
            m_bitmap_size_large);
    }
    else if(base->bitmap_large.GetSize() != m_bitmap_size_large)
    {
        base->bitmap_large = MakeResizedBitmap(base->bitmap_large,
            m_bitmap_size_large);
    }
    base->bitmap_small = bitmap_small;
    if(!base->bitmap_small.IsOk())
    {
        base->bitmap_small = MakeResizedBitmap(base->bitmap_large,
            m_bitmap_size_small);
    }
    else if(base->bitmap_small.GetSize() != m_bitmap_size_small)
    {
        base->bitmap_small = MakeResizedBitmap(base->bitmap_small,
            m_bitmap_size_small);
    }
    base->bitmap_large_disabled = bitmap_disabled;
    if(!base->bitmap_large_disabled.IsOk())
    {
        base->bitmap_large_disabled = MakeDisabledBitmap(base->bitmap_large);
    }
    base->bitmap_small_disabled = bitmap_small_disabled;
    if(!base->bitmap_small_disabled.IsOk())
    {
        base->bitmap_small_disabled = MakeDisabledBitmap(base->bitmap_small);
    }
    base->kind = kind;
    base->help_string = help_string;
    base->client_data = client_data;
    base->state = 0;

    wxMemoryDC temp_dc;
    FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_SMALL, temp_dc);
    FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_MEDIUM, temp_dc);
    FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_LARGE, temp_dc);

    // TODO
    m_buttons.Add(base);
    m_layouts_valid = false;
    return base;
}

void wxRibbonButtonBar::FetchButtonSizeInfo(wxRibbonButtonBarButtonBase* button,
        wxRibbonButtonBarButtonState size, wxDC& dc)
{
    wxRibbonButtonBarButtonSizeInfo& info = button->sizes[size];
    info.is_supported = m_art->GetButtonBarButtonSize(dc, this,
        button->kind, size, button->label, m_bitmap_size_large,
        m_bitmap_size_small, &info.size, &info.normal_region,
        &info.dropdown_region);
}

wxBitmap wxRibbonButtonBar::MakeResizedBitmap(const wxBitmap& original, wxSize size)
{
    wxImage img(original.ConvertToImage());
    img.Rescale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH);
    return wxBitmap(img);
}

wxBitmap wxRibbonButtonBar::MakeDisabledBitmap(const wxBitmap& original)
{
    wxImage img(original.ConvertToImage());
    return wxBitmap(img.ConvertToGreyscale());
}

bool wxRibbonButtonBar::Realize()
{
    if(!m_layouts_valid)
    {
        MakeLayouts();
        m_layouts_valid = true;
    }
    return true;
}

void wxRibbonButtonBar::ClearButtons()
{
    m_layouts_valid = false;
    size_t count = m_buttons.GetCount();
    size_t i;
    for(i = 0; i < count; ++i)
    {
        wxRibbonButtonBarButtonBase* button = m_buttons.Item(i);
        delete button;
    }
    m_buttons.Clear();
    Realize();
}

bool wxRibbonButtonBar::DeleteButton(int button_id)
{
    size_t count = m_buttons.GetCount();
    size_t i;
    for(i = 0; i < count; ++i)
    {
        wxRibbonButtonBarButtonBase* button = m_buttons.Item(i);
        if(button->id == button_id)
        {
            m_layouts_valid = false;
            m_buttons.RemoveAt(i);
            Realize();
            Refresh();
            return true;
        }
    }
    return false;
}

void wxRibbonButtonBar::EnableButton(int button_id, bool enable)
{
    size_t count = m_buttons.GetCount();
    size_t i;
    for(i = 0; i < count; ++i)
    {
        wxRibbonButtonBarButtonBase* button = m_buttons.Item(i);
        if(button->id == button_id)
        {
            if(enable)
            {
                if(button->state & wxRIBBON_BUTTONBAR_BUTTON_DISABLED)
                {
                    button->state &= ~wxRIBBON_BUTTONBAR_BUTTON_DISABLED;
                    Refresh();
                }
            }
            else
            {
                if((button->state & wxRIBBON_BUTTONBAR_BUTTON_DISABLED) == 0)
                {
                    button->state |= wxRIBBON_BUTTONBAR_BUTTON_DISABLED;
                    Refresh();
                }
            }
            return;
        }
    }
}

void wxRibbonButtonBar::SetArtProvider(wxRibbonArtProvider* art)
{
    if(art == m_art)
    {
        return;
    }

    wxRibbonControl::SetArtProvider(art);

    wxMemoryDC temp_dc;
    size_t btn_count = m_buttons.Count();
    size_t btn_i;
    for(btn_i = 0; btn_i < btn_count; ++btn_i)
    {
        wxRibbonButtonBarButtonBase* base = m_buttons.Item(btn_i);

        FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_SMALL, temp_dc);
        FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_MEDIUM, temp_dc);
        FetchButtonSizeInfo(base, wxRIBBON_BUTTONBAR_BUTTON_LARGE, temp_dc);
    }

    m_layouts_valid = false;
    Realize();
}

bool wxRibbonButtonBar::IsSizingContinuous() const
{
    return false;
}

wxSize wxRibbonButtonBar::DoGetNextSmallerSize(wxOrientation direction,
                                             wxSize result) const
{
    size_t nlayouts = m_layouts.GetCount();
    size_t i;
    for(i = 0; i < nlayouts; ++i)
    {
        wxRibbonButtonBarLayout* layout = m_layouts.Item(i);
        wxSize size = layout->overall_size;
        switch(direction)
        {
        case wxHORIZONTAL:
            if(size.x < result.x && size.y <= result.y)
            {
                result.x = size.x;
                break;
            }
            else
                continue;
        case wxVERTICAL:
            if(size.x <= result.x && size.y < result.y)
            {
                result.y = size.y;
                break;
            }
            else
                continue;
        case wxBOTH:
            if(size.x < result.x && size.y < result.y)
            {
                result = size;
                break;
            }
            else
                continue;
        }
        break;
    }
    return result;
}

wxSize wxRibbonButtonBar::DoGetNextLargerSize(wxOrientation direction,
                                            wxSize result) const
{
    size_t nlayouts = m_layouts.GetCount();
    size_t i = nlayouts;
    while(i > 0)
    {
        --i;
        wxRibbonButtonBarLayout* layout = m_layouts.Item(i);
        wxSize size = layout->overall_size;
        switch(direction)
        {
        case wxHORIZONTAL:
            if(size.x > result.x && size.y <= result.y)
            {
                result.x = size.x;
                break;
            }
            else
                continue;
        case wxVERTICAL:
            if(size.x <= result.x && size.y > result.y)
            {
                result.y = size.y;
                break;
            }
            else
                continue;
        case wxBOTH:
            if(size.x > result.x && size.y > result.y)
            {
                result = size;
                break;
            }
            else
                continue;
        }
        break;
    }
    return result;
}

void wxRibbonButtonBar::OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
{
    // All painting done in main paint handler to minimise flicker
}

void wxRibbonButtonBar::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
    wxAutoBufferedPaintDC dc(this);
    m_art->DrawButtonBarBackground(dc, this, GetSize());

    wxRibbonButtonBarLayout* layout = m_layouts.Item(m_current_layout);

    size_t btn_count = layout->buttons.Count();
    size_t btn_i;
    for(btn_i = 0; btn_i < btn_count; ++btn_i)
    {
        wxRibbonButtonBarButtonInstance& button = layout->buttons.Item(btn_i);
        wxRibbonButtonBarButtonBase* base = button.base;

        wxBitmap* bitmap = &base->bitmap_large;
        wxBitmap* bitmap_small = &base->bitmap_small;
        if(base->state & wxRIBBON_BUTTONBAR_BUTTON_DISABLED)
        {
            bitmap = &base->bitmap_large_disabled;
            bitmap_small = &base->bitmap_small_disabled;
        }
        wxRect rect(button.position + m_layout_offset, base->sizes[button.size].size);
        
        m_art->DrawButtonBarButton(dc, this, rect, base->kind,
            base->state | button.size, base->label, *bitmap, *bitmap_small);
    }
}

void wxRibbonButtonBar::OnSize(wxSizeEvent& evt)
{
    wxSize new_size = evt.GetSize();
    size_t layout_count = m_layouts.GetCount();
    size_t layout_i;
    m_current_layout = layout_count - 1;
    for(layout_i = 0; layout_i < layout_count; ++layout_i)
    {
        wxSize layout_size = m_layouts.Item(layout_i)->overall_size;
        if(layout_size.x <= new_size.x && layout_size.y <= new_size.y)
        {
            m_layout_offset.x = (new_size.x - layout_size.x) / 2;
            m_layout_offset.y = (new_size.y - layout_size.y) / 2;
            m_current_layout = layout_i;
            break;
        }
    }
    Refresh();
}

void wxRibbonButtonBar::CommonInit(long WXUNUSED(style))
{
    m_bitmap_size_large = wxSize(32, 32);
    m_bitmap_size_small = wxSize(16, 16);

    wxRibbonButtonBarLayout* placeholder_layout = new wxRibbonButtonBarLayout;
    placeholder_layout->overall_size = wxSize(20, 20);
    m_layouts.Add(placeholder_layout);
    m_current_layout = 0;
    m_layout_offset = wxPoint(0, 0);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
};

wxSize wxRibbonButtonBar::GetMinSize() const
{
    return m_layouts.Last()->overall_size;
}

wxSize wxRibbonButtonBar::DoGetBestSize() const
{
    return m_layouts.Item(0)->overall_size;
}

void wxRibbonButtonBar::MakeLayouts()
{
    if(m_layouts_valid)
    {
        return;
    }
    {
        // Clear existing layouts
        size_t count = m_layouts.GetCount();
        size_t i;
        for(i = 0; i < count; ++i)
        {
            wxRibbonButtonBarLayout* layout = m_layouts.Item(i);
            delete layout;
        }
        m_layouts.Clear();
    }
    size_t btn_count = m_buttons.Count();
    size_t btn_i;
    {
        // Best layout : all buttons large, stacking horizontally
        wxRibbonButtonBarLayout* layout = new wxRibbonButtonBarLayout;
        wxPoint cursor(0, 0);
        layout->overall_size.SetHeight(0);
        for(btn_i = 0; btn_i < btn_count; ++btn_i)
        {
            wxRibbonButtonBarButtonBase* button = m_buttons.Item(btn_i);
            wxRibbonButtonBarButtonInstance instance = button->NewInstance();
            instance.position = cursor;
            instance.size = button->GetLargestSize();
            wxSize& size = button->sizes[instance.size].size;
            cursor.x += size.GetWidth();
            layout->overall_size.SetHeight(wxMax(layout->overall_size.GetHeight(),
                size.GetHeight()));
            layout->buttons.Add(instance);
        }
        layout->overall_size.SetWidth(cursor.x);
        m_layouts.Add(layout);
    }
    if(btn_count >= 2)
    {
        // Collapse the rightmost buttons and stack them vertically
        TryCollapseLayout(m_layouts.Item(0), btn_count - 1);
    }
}

bool wxRibbonButtonBar::TryCollapseLayout(wxRibbonButtonBarLayout* original,
                                          size_t first_btn)
{
    size_t btn_count = m_buttons.Count();
    size_t btn_i;
    int used_height = 0;
    int used_width = 0;
    int available_width = 0;
    int available_height = 0;

    for(btn_i = first_btn + 1; btn_i > 0; /* decrement is inside loop */)
    {
        --btn_i;
        wxRibbonButtonBarButtonBase* button = m_buttons.Item(btn_i);
        wxRibbonButtonBarButtonState large_size_class = button->GetLargestSize();
        wxSize large_size = button->sizes[large_size_class].size;
        int t_available_height = wxMax(available_height,
            large_size.GetHeight());
        int t_available_width = available_width + large_size.GetWidth();
        wxRibbonButtonBarButtonState small_size_class = large_size_class;
        if(!button->GetSmallerSize(&small_size_class))
        {
            return false;
        }
        wxSize small_size = button->sizes[small_size_class].size;
        int t_used_height = used_height + small_size.GetHeight();
        int t_used_width = wxMax(used_width, small_size.GetWidth());

        if(t_used_height > t_available_height)
        {
            ++btn_i;
            break;
        }
        else
        {
            used_height = t_used_height;
            used_width = t_used_width;
            available_width = t_available_width;
            available_height = t_available_height;
        }
    }

    if(btn_i >= first_btn || used_width >= available_width)
    {
        return false;
    }

    wxRibbonButtonBarLayout* layout = new wxRibbonButtonBarLayout;
    WX_APPEND_ARRAY(layout->buttons, original->buttons);
    wxPoint cursor(layout->buttons.Item(btn_i).position);
    bool preserve_height = false;
    if(btn_i == 0)
    {
        // If height isn't preserved (i.e. it is reduced), then the minimum
        // size for the button bar will decrease, preventing the original
        // layout from being used (in some cases).
        // It may be a good idea to always preverse the height, but for now
        // it is only done when the first button is involved in a collapse.
        preserve_height = true;
    }

    for(; btn_i <= first_btn; ++btn_i)
    {
        wxRibbonButtonBarButtonInstance& instance = layout->buttons.Item(btn_i);
        instance.base->GetSmallerSize(&instance.size);
        instance.position = cursor;
        cursor.y += instance.base->sizes[instance.size].size.GetHeight();
    }

    int x_adjust = available_width - used_width;

    for(; btn_i < btn_count; ++btn_i)
    {
        wxRibbonButtonBarButtonInstance& instance = layout->buttons.Item(btn_i);
        instance.position.x -= x_adjust;
    }

    layout->CalculateOverallSize();

    // Sanity check
    if(layout->overall_size.GetWidth() >= original->overall_size.GetWidth() ||
        layout->overall_size.GetHeight() > original->overall_size.GetHeight())
    {
        delete layout;
        wxASSERT_MSG(false, wxT("Layout collapse resulted in increased size"));
        return false;
    }

    if(preserve_height)
    {
        layout->overall_size.SetHeight(original->overall_size.GetHeight());
    }

    m_layouts.Add(layout);
    return true;
}

#endif // wxUSE_RIBBON
