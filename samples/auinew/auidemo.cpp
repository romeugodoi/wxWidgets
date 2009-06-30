///////////////////////////////////////////////////////////////////////////////
// Name:        auidemo.cpp
// Purpose:     wxaui: wx advanced user interface - sample/test program
// Author:      Benjamin I. Williams
// Modified by:
// Created:     2005-10-03
// RCS-ID:      $Id: auidemo.cpp 59860 2009-03-26 08:34:27Z BIW $
// Copyright:   (C) Copyright 2005, Kirix Corporation, All Rights Reserved.
// Licence:     wxWindows Library Licence, Version 3.1
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/app.h"
#include "wx/grid.h"
#include "wx/treectrl.h"
#include "wx/spinctrl.h"
#include "wx/artprov.h"
#include "wx/clipbrd.h"
#include "wx/image.h"
#include "wx/colordlg.h"
#include "wx/wxhtml.h"
#include "wx/imaglist.h"
#include "wx/dataobj.h"
#include "wx/dcclient.h"
#include "wx/bmpbuttn.h"
#include "wx/menu.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/msgdlg.h"
#include "wx/textdlg.h"

#include "wx/aui/aui.h"
#include "../sample.xpm"

// -- application --

class MyApp : public wxApp
{
public:
    bool OnInit();
};

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)


class wxSizeReportCtrl;

// -- frame --

class MyFrame : public wxFrame
{
    enum
    {
        ID_CreateTree = wxID_HIGHEST+1,
        ID_CreateGrid,
        ID_CreateText,
        ID_CreateHTML,
        ID_CreateSizeReport,
        ID_GridContent,
        ID_TextContent,
        ID_TreeContent,
        ID_HTMLContent,
        ID_SizeReportContent,
        ID_CreatePerspective,
        ID_CopyPerspectiveCode,
        ID_AllowFloating,
        ID_AllowActivePane,
        ID_TabsTop,
        ID_TabsLeft,
        ID_TabsRight,
        ID_TabsBottom,
        ID_TabWindowList,
        ID_FixedWidth,
        ID_CloseButton,
        ID_CloseButtonActiveTab,
        ID_CloseButtonAllTabs,
        ID_NoCloseButton,
        ID_TransparentHint,
        ID_VenetianBlindsHint,
        ID_RectangleHint,
        ID_NoHint,
        ID_HintFade,
        ID_NoVenetianFade,
        ID_TransparentDrag,
        ID_NoGradient,
        ID_VerticalGradient,
        ID_HorizontalGradient,
        ID_LiveUpdate,
        ID_Settings,
        ID_CustomizeToolbar,
        ID_DropDownToolbarItem,
        ID_SampleItem,
        ID_FirstPerspective = ID_CreatePerspective+1000
    };

public:
    MyFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

    ~MyFrame();

    wxAuiDockArt* GetDockArt();
    void DoUpdate();

private:
    wxTextCtrl* CreateTextCtrl(const wxString& text = wxEmptyString);
    wxGrid* CreateGrid();
    wxTreeCtrl* CreateTreeCtrl();
    wxSizeReportCtrl* CreateSizeReportCtrl(int width = 80, int height = 80);
    wxPoint GetStartPosition();
    wxHtmlWindow* CreateHTMLCtrl(wxWindow* parent = NULL);

    wxString GetIntroText();

private:

    void OnEraseBackground(wxEraseEvent& evt);
    void OnSize(wxSizeEvent& evt);

    void OnCreateTree(wxCommandEvent& evt);
    void OnCreateGrid(wxCommandEvent& evt);
    void OnCreateHTML(wxCommandEvent& evt);
    void OnCreateText(wxCommandEvent& evt);
    void OnCreateSizeReport(wxCommandEvent& evt);
    void OnChangeContentPane(wxCommandEvent& evt);
    void OnDropDownToolbarItem(wxAuiToolBarEvent& evt);
    void OnCreatePerspective(wxCommandEvent& evt);
    void OnCopyPerspectiveCode(wxCommandEvent& evt);
    void OnRestorePerspective(wxCommandEvent& evt);
    void OnSettings(wxCommandEvent& evt);
    void OnCustomizeToolbar(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnGradient(wxCommandEvent& evt);
    void OnManagerFlag(wxCommandEvent& evt);
    void OnUpdateUI(wxUpdateUIEvent& evt);

    void OnPaneClose(wxAuiManagerEvent& evt);

private:

    wxAuiManager m_mgr;
    wxArrayString m_perspectives;
    wxMenu* m_perspectives_menu;

    DECLARE_EVENT_TABLE()
};


// -- wxSizeReportCtrl --
// (a utility control that always reports it's client size)

class wxSizeReportCtrl : public wxControl
{
public:

    wxSizeReportCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     wxAuiManager* mgr = NULL)
                     : wxControl(parent, id, pos, size, wxNO_BORDER)
    {
        m_mgr = mgr;
    }

private:

    void OnPaint(wxPaintEvent& WXUNUSED(evt))
    {
        wxPaintDC dc(this);
        wxSize size = GetClientSize();
        wxString s;
        int h, w, height;

        s.Printf(wxT("Size: %d x %d"), size.x, size.y);

        dc.SetFont(*wxNORMAL_FONT);
        dc.GetTextExtent(s, &w, &height);
        height += 3;
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.SetPen(*wxWHITE_PEN);
        dc.DrawRectangle(0, 0, size.x, size.y);
        dc.SetPen(*wxLIGHT_GREY_PEN);
        dc.DrawLine(0, 0, size.x, size.y);
        dc.DrawLine(0, size.y, size.x, 0);
        dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2));

        if (m_mgr)
        {
            wxAuiPaneInfo pi = m_mgr->GetPane(this);

            s.Printf(wxT("Layer: %d"), pi.GetLayer());
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*1));

            s.Printf(wxT("Dock: %d Row: %d"), pi.GetDirection(), pi.GetRow());
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*2));

            s.Printf(wxT("Position: %d"), pi.GetPosition());
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*3));

            s.Printf(wxT("Proportion: %d"), pi.GetProportion());
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*4));
        }
    }

    void OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
    {
        // intentionally empty
    }

    void OnSize(wxSizeEvent& WXUNUSED(evt))
    {
        Refresh();
    }
private:

    wxAuiManager* m_mgr;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxSizeReportCtrl, wxControl)
    EVT_PAINT(wxSizeReportCtrl::OnPaint)
    EVT_SIZE(wxSizeReportCtrl::OnSize)
    EVT_ERASE_BACKGROUND(wxSizeReportCtrl::OnEraseBackground)
END_EVENT_TABLE()


class SettingsPanel : public wxPanel
{
    enum
    {
        ID_PaneBorderSize = wxID_HIGHEST+1,
        ID_SashSize,
        ID_CaptionSize,
        ID_BackgroundColor,
        ID_SashColor,
        ID_InactiveCaptionColor,
        ID_InactiveCaptionGradientColor,
        ID_InactiveCaptionTextColor,
        ID_ActiveCaptionColor,
        ID_ActiveCaptionGradientColor,
        ID_ActiveCaptionTextColor,
        ID_BorderColor,
        ID_GripperColor
    };

public:

    SettingsPanel(wxWindow* parent, MyFrame* frame)
            : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize),
              m_frame(frame)
    {
        //wxBoxSizer* vert = new wxBoxSizer(wxVERTICAL);

        //vert->Add(1, 1, 1, wxEXPAND);

        wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
        m_border_size = new wxSpinCtrl(this, ID_PaneBorderSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE)), wxDefaultPosition, wxSize(50,20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
        s1->Add(1, 1, 1, wxEXPAND);
        s1->Add(new wxStaticText(this, wxID_ANY, wxT("Pane Border Size:")));
        s1->Add(m_border_size);
        s1->Add(1, 1, 1, wxEXPAND);
        s1->SetItemMinSize((size_t)1, 180, 20);
        //vert->Add(s1, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

        wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
        m_sash_size = new wxSpinCtrl(this, ID_SashSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE)), wxDefaultPosition, wxSize(50,20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE));
        s2->Add(1, 1, 1, wxEXPAND);
        s2->Add(new wxStaticText(this, wxID_ANY, wxT("Sash Size:")));
        s2->Add(m_sash_size);
        s2->Add(1, 1, 1, wxEXPAND);
        s2->SetItemMinSize((size_t)1, 180, 20);
        //vert->Add(s2, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

        wxBoxSizer* s3 = new wxBoxSizer(wxHORIZONTAL);
        m_caption_size = new wxSpinCtrl(this, ID_CaptionSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE)), wxDefaultPosition, wxSize(50,20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE));
        s3->Add(1, 1, 1, wxEXPAND);
        s3->Add(new wxStaticText(this, wxID_ANY, wxT("Caption Size:")));
        s3->Add(m_caption_size);
        s3->Add(1, 1, 1, wxEXPAND);
        s3->SetItemMinSize((size_t)1, 180, 20);
        //vert->Add(s3, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

        //vert->Add(1, 1, 1, wxEXPAND);


        wxBitmap b = CreateColorBitmap(*wxBLACK);

        wxBoxSizer* s4 = new wxBoxSizer(wxHORIZONTAL);
        m_background_color = new wxBitmapButton(this, ID_BackgroundColor, b, wxDefaultPosition, wxSize(50,25));
        s4->Add(1, 1, 1, wxEXPAND);
        s4->Add(new wxStaticText(this, wxID_ANY, wxT("Background Color:")));
        s4->Add(m_background_color);
        s4->Add(1, 1, 1, wxEXPAND);
        s4->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s5 = new wxBoxSizer(wxHORIZONTAL);
        m_sash_color = new wxBitmapButton(this, ID_SashColor, b, wxDefaultPosition, wxSize(50,25));
        s5->Add(1, 1, 1, wxEXPAND);
        s5->Add(new wxStaticText(this, wxID_ANY, wxT("Sash Color:")));
        s5->Add(m_sash_color);
        s5->Add(1, 1, 1, wxEXPAND);
        s5->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s6 = new wxBoxSizer(wxHORIZONTAL);
        m_inactive_caption_color = new wxBitmapButton(this, ID_InactiveCaptionColor, b, wxDefaultPosition, wxSize(50,25));
        s6->Add(1, 1, 1, wxEXPAND);
        s6->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption:")));
        s6->Add(m_inactive_caption_color);
        s6->Add(1, 1, 1, wxEXPAND);
        s6->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s7 = new wxBoxSizer(wxHORIZONTAL);
        m_inactive_caption_gradient_color = new wxBitmapButton(this, ID_InactiveCaptionGradientColor, b, wxDefaultPosition, wxSize(50,25));
        s7->Add(1, 1, 1, wxEXPAND);
        s7->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption Gradient:")));
        s7->Add(m_inactive_caption_gradient_color);
        s7->Add(1, 1, 1, wxEXPAND);
        s7->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s8 = new wxBoxSizer(wxHORIZONTAL);
        m_inactive_caption_text_color = new wxBitmapButton(this, ID_InactiveCaptionTextColor, b, wxDefaultPosition, wxSize(50,25));
        s8->Add(1, 1, 1, wxEXPAND);
        s8->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption Text:")));
        s8->Add(m_inactive_caption_text_color);
        s8->Add(1, 1, 1, wxEXPAND);
        s8->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s9 = new wxBoxSizer(wxHORIZONTAL);
        m_active_caption_color = new wxBitmapButton(this, ID_ActiveCaptionColor, b, wxDefaultPosition, wxSize(50,25));
        s9->Add(1, 1, 1, wxEXPAND);
        s9->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption:")));
        s9->Add(m_active_caption_color);
        s9->Add(1, 1, 1, wxEXPAND);
        s9->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s10 = new wxBoxSizer(wxHORIZONTAL);
        m_active_caption_gradient_color = new wxBitmapButton(this, ID_ActiveCaptionGradientColor, b, wxDefaultPosition, wxSize(50,25));
        s10->Add(1, 1, 1, wxEXPAND);
        s10->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption Gradient:")));
        s10->Add(m_active_caption_gradient_color);
        s10->Add(1, 1, 1, wxEXPAND);
        s10->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s11 = new wxBoxSizer(wxHORIZONTAL);
        m_active_caption_text_color = new wxBitmapButton(this, ID_ActiveCaptionTextColor, b, wxDefaultPosition, wxSize(50,25));
        s11->Add(1, 1, 1, wxEXPAND);
        s11->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption Text:")));
        s11->Add(m_active_caption_text_color);
        s11->Add(1, 1, 1, wxEXPAND);
        s11->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s12 = new wxBoxSizer(wxHORIZONTAL);
        m_border_color = new wxBitmapButton(this, ID_BorderColor, b, wxDefaultPosition, wxSize(50,25));
        s12->Add(1, 1, 1, wxEXPAND);
        s12->Add(new wxStaticText(this, wxID_ANY, wxT("Border Color:")));
        s12->Add(m_border_color);
        s12->Add(1, 1, 1, wxEXPAND);
        s12->SetItemMinSize((size_t)1, 180, 20);

        wxBoxSizer* s13 = new wxBoxSizer(wxHORIZONTAL);
        m_gripper_color = new wxBitmapButton(this, ID_GripperColor, b, wxDefaultPosition, wxSize(50,25));
        s13->Add(1, 1, 1, wxEXPAND);
        s13->Add(new wxStaticText(this, wxID_ANY, wxT("Gripper Color:")));
        s13->Add(m_gripper_color);
        s13->Add(1, 1, 1, wxEXPAND);
        s13->SetItemMinSize((size_t)1, 180, 20);

        wxGridSizer* grid_sizer = new wxGridSizer(2);
        grid_sizer->SetHGap(5);
        grid_sizer->Add(s1);  grid_sizer->Add(s4);
        grid_sizer->Add(s2);  grid_sizer->Add(s5);
        grid_sizer->Add(s3);  grid_sizer->Add(s13);
        grid_sizer->Add(1,1); grid_sizer->Add(s12);
        grid_sizer->Add(s6);  grid_sizer->Add(s9);
        grid_sizer->Add(s7);  grid_sizer->Add(s10);
        grid_sizer->Add(s8);  grid_sizer->Add(s11);

        wxBoxSizer* cont_sizer = new wxBoxSizer(wxVERTICAL);
        cont_sizer->Add(grid_sizer, 1, wxEXPAND | wxALL, 5);
        SetSizer(cont_sizer);
        GetSizer()->SetSizeHints(this);

        m_border_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
        m_sash_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE));
        m_caption_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE));

        UpdateColors();
    }

private:

    wxBitmap CreateColorBitmap(const wxColour& c)
    {
        wxImage image;
        image.Create(25,14);
        for (int x = 0; x < 25; ++x)
            for (int y = 0; y < 14; ++y)
            {
                wxColour pixcol = c;
                if (x == 0 || x == 24 || y == 0 || y == 13)
                    pixcol = *wxBLACK;
                image.SetRGB(x, y, pixcol.Red(), pixcol.Green(), pixcol.Blue());
            }
        return wxBitmap(image);
    }

    void UpdateColors()
    {
        wxColour bk = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_BACKGROUND_COLOUR);
        m_background_color->SetBitmapLabel(CreateColorBitmap(bk));

        wxColour cap = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR);
        m_inactive_caption_color->SetBitmapLabel(CreateColorBitmap(cap));

        wxColour capgrad = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR);
        m_inactive_caption_gradient_color->SetBitmapLabel(CreateColorBitmap(capgrad));

        wxColour captxt = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR);
        m_inactive_caption_text_color->SetBitmapLabel(CreateColorBitmap(captxt));

        wxColour acap = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR);
        m_active_caption_color->SetBitmapLabel(CreateColorBitmap(acap));

        wxColour acapgrad = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR);
        m_active_caption_gradient_color->SetBitmapLabel(CreateColorBitmap(acapgrad));

        wxColour acaptxt = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR);
        m_active_caption_text_color->SetBitmapLabel(CreateColorBitmap(acaptxt));

        wxColour sash = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_SASH_COLOUR);
        m_sash_color->SetBitmapLabel(CreateColorBitmap(sash));

        wxColour border = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_BORDER_COLOUR);
        m_border_color->SetBitmapLabel(CreateColorBitmap(border));

        wxColour gripper = m_frame->GetDockArt()->GetColor(wxAUI_DOCKART_GRIPPER_COLOUR);
        m_gripper_color->SetBitmapLabel(CreateColorBitmap(gripper));
    }

    void OnPaneBorderSize(wxSpinEvent& event)
    {
        m_frame->GetDockArt()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE,
                                         event.GetPosition());
        m_frame->DoUpdate();
    }

    void OnSashSize(wxSpinEvent& event)
    {
        m_frame->GetDockArt()->SetMetric(wxAUI_DOCKART_SASH_SIZE,
                                         event.GetPosition());
        m_frame->DoUpdate();
    }

    void OnCaptionSize(wxSpinEvent& event)
    {
        m_frame->GetDockArt()->SetMetric(wxAUI_DOCKART_CAPTION_SIZE,
                                         event.GetPosition());
        m_frame->DoUpdate();
    }

    void OnSetColor(wxCommandEvent& event)
    {
        wxColourDialog dlg(m_frame);
        dlg.SetTitle(_("Color Picker"));
        if (dlg.ShowModal() != wxID_OK)
            return;

        int var = 0;
        switch (event.GetId())
        {
            case ID_BackgroundColor:              var = wxAUI_DOCKART_BACKGROUND_COLOUR; break;
            case ID_SashColor:                    var = wxAUI_DOCKART_SASH_COLOUR; break;
            case ID_InactiveCaptionColor:         var = wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR; break;
            case ID_InactiveCaptionGradientColor: var = wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR; break;
            case ID_InactiveCaptionTextColor:     var = wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR; break;
            case ID_ActiveCaptionColor:           var = wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR; break;
            case ID_ActiveCaptionGradientColor:   var = wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR; break;
            case ID_ActiveCaptionTextColor:       var = wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR; break;
            case ID_BorderColor:                  var = wxAUI_DOCKART_BORDER_COLOUR; break;
            case ID_GripperColor:                 var = wxAUI_DOCKART_GRIPPER_COLOUR; break;
            default: return;
        }

        m_frame->GetDockArt()->SetColor(var, dlg.GetColourData().GetColour());
        m_frame->DoUpdate();
        UpdateColors();
    }

private:

    MyFrame* m_frame;
    wxSpinCtrl* m_border_size;
    wxSpinCtrl* m_sash_size;
    wxSpinCtrl* m_caption_size;
    wxBitmapButton* m_inactive_caption_text_color;
    wxBitmapButton* m_inactive_caption_gradient_color;
    wxBitmapButton* m_inactive_caption_color;
    wxBitmapButton* m_active_caption_text_color;
    wxBitmapButton* m_active_caption_gradient_color;
    wxBitmapButton* m_active_caption_color;
    wxBitmapButton* m_sash_color;
    wxBitmapButton* m_background_color;
    wxBitmapButton* m_border_color;
    wxBitmapButton* m_gripper_color;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(SettingsPanel, wxPanel)
    EVT_SPINCTRL(ID_PaneBorderSize, SettingsPanel::OnPaneBorderSize)
    EVT_SPINCTRL(ID_SashSize, SettingsPanel::OnSashSize)
    EVT_SPINCTRL(ID_CaptionSize, SettingsPanel::OnCaptionSize)
    EVT_BUTTON(ID_BackgroundColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_SashColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionGradientColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionTextColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionGradientColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionTextColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_BorderColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_GripperColor, SettingsPanel::OnSetColor)
END_EVENT_TABLE()


bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxFrame* frame = new MyFrame(NULL,
                                 wxID_ANY,
                                 wxT("wxAUI Sample Application"),
                                 wxDefaultPosition,
                                 wxSize(800, 600));
    SetTopWindow(frame);
    frame->Show();

    return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_ERASE_BACKGROUND(MyFrame::OnEraseBackground)
    EVT_SIZE(MyFrame::OnSize)
    EVT_MENU(MyFrame::ID_CreateTree, MyFrame::OnCreateTree)
    EVT_MENU(MyFrame::ID_CreateGrid, MyFrame::OnCreateGrid)
    EVT_MENU(MyFrame::ID_CreateText, MyFrame::OnCreateText)
    EVT_MENU(MyFrame::ID_CreateHTML, MyFrame::OnCreateHTML)
    EVT_MENU(MyFrame::ID_CreateSizeReport, MyFrame::OnCreateSizeReport)
    EVT_MENU(MyFrame::ID_CreatePerspective, MyFrame::OnCreatePerspective)
    EVT_MENU(MyFrame::ID_CopyPerspectiveCode, MyFrame::OnCopyPerspectiveCode)
    EVT_MENU(ID_AllowFloating, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TabsTop, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TabsLeft, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TabsRight, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TabsBottom, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TabWindowList, MyFrame::OnManagerFlag)
    EVT_MENU(ID_FixedWidth, MyFrame::OnManagerFlag)
    EVT_MENU(ID_CloseButton, MyFrame::OnManagerFlag)
    EVT_MENU(ID_CloseButtonActiveTab, MyFrame::OnManagerFlag)
    EVT_MENU(ID_CloseButtonAllTabs, MyFrame::OnManagerFlag)
    EVT_MENU(ID_NoCloseButton, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentHint, MyFrame::OnManagerFlag)
    EVT_MENU(ID_VenetianBlindsHint, MyFrame::OnManagerFlag)
    EVT_MENU(ID_RectangleHint, MyFrame::OnManagerFlag)
    EVT_MENU(ID_NoHint, MyFrame::OnManagerFlag)
    EVT_MENU(ID_HintFade, MyFrame::OnManagerFlag)
    EVT_MENU(ID_NoVenetianFade, MyFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentDrag, MyFrame::OnManagerFlag)
    EVT_MENU(ID_LiveUpdate, MyFrame::OnManagerFlag)
    EVT_MENU(ID_AllowActivePane, MyFrame::OnManagerFlag)
    EVT_MENU(ID_NoGradient, MyFrame::OnGradient)
    EVT_MENU(ID_VerticalGradient, MyFrame::OnGradient)
    EVT_MENU(ID_HorizontalGradient, MyFrame::OnGradient)
    EVT_MENU(ID_Settings, MyFrame::OnSettings)
    EVT_MENU(ID_CustomizeToolbar, MyFrame::OnCustomizeToolbar)
    EVT_MENU(ID_GridContent, MyFrame::OnChangeContentPane)
    EVT_MENU(ID_TreeContent, MyFrame::OnChangeContentPane)
    EVT_MENU(ID_TextContent, MyFrame::OnChangeContentPane)
    EVT_MENU(ID_SizeReportContent, MyFrame::OnChangeContentPane)
    EVT_MENU(ID_HTMLContent, MyFrame::OnChangeContentPane)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_UPDATE_UI(ID_AllowFloating, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentHint, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VenetianBlindsHint, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_RectangleHint, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoHint, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HintFade, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoVenetianFade, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentDrag, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_LiveUpdate, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoGradient, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VerticalGradient, MyFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HorizontalGradient, MyFrame::OnUpdateUI)
    EVT_MENU_RANGE(MyFrame::ID_FirstPerspective, MyFrame::ID_FirstPerspective+1000,
                   MyFrame::OnRestorePerspective)
    EVT_AUITOOLBAR_TOOL_DROPDOWN(ID_DropDownToolbarItem, MyFrame::OnDropDownToolbarItem)
    EVT_AUI_PANE_CLOSE(MyFrame::OnPaneClose)
END_EVENT_TABLE()


MyFrame::MyFrame(wxWindow* parent,
                 wxWindowID id,
                 const wxString& title,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style)
        : wxFrame(parent, id, title, pos, size, style)
{
    // tell wxAuiManager to manage this frame
    m_mgr.SetManagedWindow(this);

    // set frame icon
    SetIcon(wxIcon(sample_xpm));

    // create menu
    wxMenuBar* mb = new wxMenuBar;

    wxMenu* file_menu = new wxMenu;
    file_menu->Append(wxID_EXIT);

    wxMenu* view_menu = new wxMenu;
    view_menu->Append(ID_CreateText, _("Create Text Control"));
    view_menu->Append(ID_CreateHTML, _("Create HTML Control"));
    view_menu->Append(ID_CreateTree, _("Create Tree"));
    view_menu->Append(ID_CreateGrid, _("Create Grid"));
    view_menu->Append(ID_CreateSizeReport, _("Create Size Reporter"));
    view_menu->AppendSeparator();
    view_menu->Append(ID_GridContent, _("Use a Grid for the Content Pane"));
    view_menu->Append(ID_TextContent, _("Use a Text Control for the Content Pane"));
    view_menu->Append(ID_HTMLContent, _("Use an HTML Control for the Content Pane"));
    view_menu->Append(ID_TreeContent, _("Use a Tree Control for the Content Pane"));
    view_menu->Append(ID_SizeReportContent, _("Use a Size Reporter for the Content Pane"));

    wxMenu* options_menu = new wxMenu;
    options_menu->AppendRadioItem(ID_TabsTop, _("Notebook tabs at top"));
    options_menu->AppendRadioItem(ID_TabsBottom, _("Notebook tabs at bottom"));
    options_menu->AppendRadioItem(ID_TabsLeft, _("Notebook tabs on left"));
    options_menu->AppendRadioItem(ID_TabsRight, _("Notebook tabs on right"));
    options_menu->AppendSeparator();
    options_menu->AppendCheckItem(ID_TabWindowList, _("Show pulldown list of tabs in notebook"));
    options_menu->AppendSeparator();
    options_menu->AppendCheckItem(ID_FixedWidth, _("Use fixed tab width for notebook tabs"));
    options_menu->AppendSeparator();
    options_menu->AppendRadioItem(ID_CloseButtonActiveTab, _("Close button on active tab of notebook"));
    options_menu->AppendRadioItem(ID_CloseButtonAllTabs, _("Close button on all tabs of notebook"));
    options_menu->AppendRadioItem(ID_CloseButton, _("Close button on right of notebook"));
    options_menu->AppendRadioItem(ID_NoCloseButton, _("No close button on notebook"));
    options_menu->AppendSeparator();
    options_menu->AppendRadioItem(ID_TransparentHint, _("Transparent Hint"));
    options_menu->AppendRadioItem(ID_VenetianBlindsHint, _("Venetian Blinds Hint"));
    options_menu->AppendRadioItem(ID_RectangleHint, _("Rectangle Hint"));
    options_menu->AppendRadioItem(ID_NoHint, _("No Hint"));
    options_menu->AppendSeparator();
    options_menu->AppendCheckItem(ID_HintFade, _("Hint Fade-in"));
    options_menu->AppendCheckItem(ID_AllowFloating, _("Allow Floating"));
    options_menu->AppendCheckItem(ID_NoVenetianFade, _("Disable Venetian Blinds Hint Fade-in"));
    options_menu->AppendCheckItem(ID_TransparentDrag, _("Transparent Drag"));
    options_menu->AppendCheckItem(ID_AllowActivePane, _("Allow Active Pane"));
    options_menu->AppendCheckItem(ID_LiveUpdate, _("Live Resize Update"));
    options_menu->AppendSeparator();
    options_menu->AppendRadioItem(ID_NoGradient, _("No Caption Gradient"));
    options_menu->AppendRadioItem(ID_VerticalGradient, _("Vertical Caption Gradient"));
    options_menu->AppendRadioItem(ID_HorizontalGradient, _("Horizontal Caption Gradient"));
    options_menu->AppendSeparator();
    options_menu->Append(ID_Settings, _("Settings Pane"));

    m_perspectives_menu = new wxMenu;
    m_perspectives_menu->Append(ID_CreatePerspective, _("Create Perspective"));
    m_perspectives_menu->Append(ID_CopyPerspectiveCode, _("Copy Perspective Data To Clipboard"));
    m_perspectives_menu->AppendSeparator();
    m_perspectives_menu->Append(ID_FirstPerspective+0, _("Default Startup"));
    m_perspectives_menu->Append(ID_FirstPerspective+1, _("All Panes"));

    wxMenu* help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT);

    mb->Append(file_menu, _("&File"));
    mb->Append(view_menu, _("&View"));
    mb->Append(m_perspectives_menu, _("&Perspectives"));
    mb->Append(options_menu, _("&Options"));
    mb->Append(help_menu, _("&Help"));

    SetMenuBar(mb);

    CreateStatusBar();
    GetStatusBar()->SetStatusText(_("Ready"));


    // min size for the frame itself isn't completely done.
    // see the end up wxAuiManager::Update() for the test
    // code. For now, just hard code a frame minimum size
    SetMinSize(wxSize(400,300));

/*

    // prepare a few custom overflow elements for the toolbars' overflow buttons

    wxAuiToolBarItemArray prepend_items;
    wxAuiToolBarItemArray append_items;
    wxAuiToolBarItem item;
    item.SetKind(wxITEM_SEPARATOR);
    append_items.Add(item);
    item.SetKind(wxITEM_NORMAL);
    item.SetId(ID_CustomizeToolbar);
    item.SetLabel(_("Customize..."));
    append_items.Add(item);


    // create some toolbars
    wxAuiToolBar* tb1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
    tb1->SetToolBitmapSize(wxSize(48,48));
    tb1->AddTool(ID_SampleItem+1, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
    tb1->AddSeparator();
    tb1->AddTool(ID_SampleItem+2, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
    tb1->AddTool(ID_SampleItem+3, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
    tb1->AddTool(ID_SampleItem+4, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
    tb1->AddTool(ID_SampleItem+5, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
    tb1->SetCustomOverflowItems(prepend_items, append_items);
    tb1->Realize();


    wxAuiToolBar* tb2 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
    tb2->SetToolBitmapSize(wxSize(16,16));

    wxBitmap tb2_bmp1 = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));
    tb2->AddTool(ID_SampleItem+6, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+7, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+8, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+9, wxT("Test"), tb2_bmp1);
    tb2->AddSeparator();
    tb2->AddTool(ID_SampleItem+10, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+11, wxT("Test"), tb2_bmp1);
    tb2->AddSeparator();
    tb2->AddTool(ID_SampleItem+12, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+13, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+14, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+15, wxT("Test"), tb2_bmp1);
    tb2->SetCustomOverflowItems(prepend_items, append_items);
    tb2->Realize();


    wxAuiToolBar* tb3 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
    tb3->SetToolBitmapSize(wxSize(16,16));
    wxBitmap tb3_bmp1 = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16));
    tb3->AddTool(ID_SampleItem+16, wxT("Check 1"), tb3_bmp1, wxT("Check 1"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+17, wxT("Check 2"), tb3_bmp1, wxT("Check 2"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+18, wxT("Check 3"), tb3_bmp1, wxT("Check 3"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+19, wxT("Check 4"), tb3_bmp1, wxT("Check 4"), wxITEM_CHECK);
    tb3->AddSeparator();
    tb3->AddTool(ID_SampleItem+20, wxT("Radio 1"), tb3_bmp1, wxT("Radio 1"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+21, wxT("Radio 2"), tb3_bmp1, wxT("Radio 2"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+22, wxT("Radio 3"), tb3_bmp1, wxT("Radio 3"), wxITEM_RADIO);
    tb3->AddSeparator();
    tb3->AddTool(ID_SampleItem+23, wxT("Radio 1 (Group 2)"), tb3_bmp1, wxT("Radio 1 (Group 2)"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+24, wxT("Radio 2 (Group 2)"), tb3_bmp1, wxT("Radio 2 (Group 2)"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+25, wxT("Radio 3 (Group 2)"), tb3_bmp1, wxT("Radio 3 (Group 2)"), wxITEM_RADIO);
    tb3->SetCustomOverflowItems(prepend_items, append_items);
    tb3->Realize();


    wxAuiToolBar* tb4 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE |
                                         wxAUI_TB_OVERFLOW |
                                         wxAUI_TB_TEXT |
                                         wxAUI_TB_HORZ_TEXT);
    tb4->SetToolBitmapSize(wxSize(16,16));
    wxBitmap tb4_bmp1 = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
    tb4->AddTool(ID_DropDownToolbarItem, wxT("Item 1"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+23, wxT("Item 2"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+24, wxT("Item 3"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+25, wxT("Item 4"), tb4_bmp1);
    tb4->AddSeparator();
    tb4->AddTool(ID_SampleItem+26, wxT("Item 5"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+27, wxT("Item 6"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+28, wxT("Item 7"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+29, wxT("Item 8"), tb4_bmp1);
    tb4->SetToolDropDown(ID_DropDownToolbarItem, true);
    tb4->SetCustomOverflowItems(prepend_items, append_items);
    tb4->Realize();


    wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_VERTICAL);
    tb5->SetToolBitmapSize(wxSize(48,48));
    tb5->AddTool(ID_SampleItem+30, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
    tb5->AddSeparator();
    tb5->AddTool(ID_SampleItem+31, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
    tb5->AddTool(ID_SampleItem+32, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
    tb5->AddTool(ID_SampleItem+33, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
    tb5->AddTool(ID_SampleItem+34, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
    tb5->SetCustomOverflowItems(prepend_items, append_items);
    tb5->Realize();*/

    // add a bunch of panes
    /*m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test1")).SetCaption(wxT("Pane Caption")).
                  SetDirectionTop());

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test2")).SetCaption(wxT("Client Size Reporter")).
                  SetDirectionBottom().SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test3")).SetCaption(wxT("Client Size Reporter")).
                  SetDirectionBottom().
                  SetCloseButton(true).SetMaximizeButton(true));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test4")).SetCaption(wxT("Pane Caption")).
                  SetDirectionLeft());

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test5")).SetCaption(wxT("No Close Button")).
                  SetDirectionRight().SetCloseButton(false));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test6")).SetCaption(wxT("Client Size Reporter")).
                  SetDirectionRight().SetRow(1).
                  SetCloseButton(true).SetMaximizeButton(true));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test7")).SetCaption(wxT("Client Size Reporter")).
                  SetDirectionLeft().SetLayer(1).
                  SetCloseButton(true).SetMaximizeButton(true));

    //m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
    //              SetName(wxT("test8")).SetCaption(wxT("Tree Pane")).
    //              SetDirectionLeft().SetLayer(1).SetPosition(1).
    //              SetCloseButton(true).SetMaximizeButton(true));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test9")).SetCaption(wxT("Min Size 200x100")).
                  SetBestSize(wxSize(200,100)).SetMinSize(wxSize(200,100)).
                  SetDirectionBottom().SetLayer(1).
                  SetCloseButton(true).SetMaximizeButton(true));

    wxWindow* wnd10 = CreateTextCtrl(wxT("This pane will prompt the user before hiding."));
    m_mgr.AddPane(wnd10, wxAuiPaneInfo().
                  SetName(wxT("test10")).SetCaption(wxT("Text Pane with Hide Prompt")).
                  SetDirectionBottom().SetLayer(1).SetPosition(1));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetName(wxT("test11")).SetCaption(wxT("Fixed Pane")).
                  SetDirectionBottom().SetLayer(1).SetPosition(2).SetFixed());


    m_mgr.AddPane(new SettingsPanel(this,this), wxAuiPaneInfo().
                  SetName(wxT("settings")).SetCaption(wxT("Dock Manager Settings")).
                  SetDockable(false).Float().Hide());

    // create some center panes

    m_mgr.AddPane(CreateGrid(), wxAuiPaneInfo().SetName(wxT("grid_content")).
                  SetCenterPane().Hide());

    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().SetName(wxT("tree_content")).
                  SetCenterPane().Hide());

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().SetName(wxT("sizereport_content")).
                  SetCenterPane().Hide());

    m_mgr.AddPane(CreateTextCtrl(), wxAuiPaneInfo().SetName(wxT("text_content")).
                  SetCenterPane().Hide());

    m_mgr.AddPane(CreateHTMLCtrl(), wxAuiPaneInfo().SetName(wxT("html_content")).
                  SetCenterPane().Hide());*/

    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("above")).SetCaption(wxT("Tree Pane")).
                  SetDirectionLeft().SetLayer(1).SetPosition(0).
                  SetCloseButton(true).SetMaximizeButton(true).SetBitmap(wxArtProvider::GetBitmap(wxART_QUESTION)));
    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("below")).SetCaption(wxT("Tree Pane")).
                  SetDirectionLeft().SetLayer(1).SetPosition(4).
                  SetCloseButton(true).SetMaximizeButton(true));
	//create some panes that should form into a notebook
	/*{
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
					  SetName(wxT("below2")).SetCaption(wxT("Tree Pane")).
					  SetDirectionLeft().SetLayer(1).SetPosition(0).SetRow(2).
					  SetCloseButton(true).SetMaximizeButton(true));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
					  SetName(wxT("below22")).SetCaption(wxT("Tree Pane")).
					  SetDirectionLeft().SetLayer(1).SetPosition(0).SetRow(2).SetPage(5).
					  SetCloseButton(true).SetMaximizeButton(true));
	}*/
                  

	/*m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("floating0")).SetCaption(wxT("Tree Pane")).
                  Float().SetCloseButton(true).SetMaximizeButton(true).SetFloatingPosition(10,15).
				  SetFloatingSize(40,40));
	//create some floating panes that should form into a notebook
	{
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("floating1")).SetCaption(wxT("Tree Pane")).
                  Float().SetCloseButton(true).SetMaximizeButton(true).SetFloatingPosition(10,20).
				  SetFloatingSize(40,40).SetPage(1));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("floating2")).SetCaption(wxT("Tree Pane")).
                  Float().SetCloseButton(true).SetMaximizeButton(true).SetFloatingPosition(10,20).
				  SetFloatingSize(40,40).SetPage(2));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("floating3")).SetCaption(wxT("Tree Pane")).
                  Float().SetCloseButton(true).SetMaximizeButton(true).SetFloatingPosition(10,20).
				  SetFloatingSize(40,40).SetPage(3));
	}*/

    //create some more panes that should form into a notebook
    {
        m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("tabtest1")).SetCaption(wxT("Tree Pane (Long Caption)")).
                  SetDirectionLeft().SetLayer(1).SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true).SetPage(1).SetBitmap(wxArtProvider::GetBitmap(wxART_ERROR)));
        m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("tabtest3")).SetCaption(wxT("Tree Pane 3")).
                  SetDirectionLeft().SetLayer(1).SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true).SetPage(3));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("tabtest2")).SetCaption(wxT("Tree Pane 2")).
                  SetDirectionLeft().SetLayer(1).SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true).SetPage(2).SetFlag(wxAuiPaneInfo::optionActiveNotebook,true));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("tabtest5")).SetCaption(wxT("Tree Pane 4")).
                  SetDirectionLeft().SetLayer(1).SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true).SetPage(4));
		m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetName(wxT("tabtest6")).SetCaption(wxT("Tree Pane 5")).
                  SetDirectionLeft().SetLayer(1).SetPosition(1).
                  SetCloseButton(true).SetMaximizeButton(true).SetPage(5));
    }

    // add the toolbars to the manager
  /*  m_mgr.AddPane(tb1, wxAuiPaneInfo().
                  SetName(wxT("tb1")).SetCaption(wxT("Big Toolbar")).
                  SetToolbarPane().SetDirectionTop().
                  SetLeftDockable(false).SetRightDockable(false));

    m_mgr.AddPane(tb2, wxAuiPaneInfo().
                  SetName(wxT("tb2")).SetCaption(wxT("Toolbar 2")).
                  SetToolbarPane().SetDirectionTop().SetRow(1).
                  SetLeftDockable(false).SetRightDockable(false));

    m_mgr.AddPane(tb3, wxAuiPaneInfo().
                  SetName(wxT("tb3")).SetCaption(wxT("Toolbar 3")).
                  SetToolbarPane().SetDirectionTop().SetRow(1).SetPosition(1).
                  SetLeftDockable(false).SetRightDockable(false));

    m_mgr.AddPane(tb4, wxAuiPaneInfo().
                  SetName(wxT("tb4")).SetCaption(wxT("Sample Bookmark Toolbar")).
                  SetToolbarPane().SetDirectionTop().SetRow(2).
                  SetLeftDockable(false).SetRightDockable(false));

    m_mgr.AddPane(tb5, wxAuiPaneInfo().
                  SetName(wxT("tb5")).SetCaption(wxT("Sample Vertical Toolbar")).
                  SetToolbarPane().SetDirectionLeft().
                  SetGripperTop().
                  SetTopDockable(false).SetBottomDockable(false));

    m_mgr.AddPane(new wxButton(this, wxID_ANY, _("Test Button")),
                  wxAuiPaneInfo().SetName(wxT("tb6")).
                  SetToolbarPane().SetDirectionTop().SetRow(2).SetPosition(1).
                  SetLeftDockable(false).SetRightDockable(false));*/

    // make some default perspectives

    wxString perspective_all = m_mgr.SavePerspective();

   /* int i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
        if (!all_panes.Item(i).IsToolbar())
            all_panes.Item(i).Hide();
    m_mgr.GetPane(wxT("tb1")).Hide();
    m_mgr.GetPane(wxT("tb6")).Hide();
    m_mgr.GetPane(wxT("test8")).Show().SetDirectionLeft().SetLayer(0).SetRow(0).SetPosition(0);
    m_mgr.GetPane(wxT("test10")).Show().SetDirectionBottom().SetLayer(0).SetRow(0).SetPosition(0);
    wxString perspective_default = m_mgr.SavePerspective();

    m_perspectives.Add(perspective_default);
    m_perspectives.Add(perspective_all);*/

    // "commit" all changes made to wxAuiManager
    m_mgr.Update();
}

MyFrame::~MyFrame()
{
    m_mgr.UnInit();
}

wxAuiDockArt* MyFrame::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void MyFrame::DoUpdate()
{
    m_mgr.Update();
}

void MyFrame::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

void MyFrame::OnSize(wxSizeEvent& event)
{
    event.Skip();
}

void MyFrame::OnSettings(wxCommandEvent& WXUNUSED(evt))
{
    // show the settings pane, and float it
    wxAuiPaneInfo& floating_pane = m_mgr.GetPane(wxT("settings")).Float().Show();

    if (floating_pane.GetFloatingPosition() == wxDefaultPosition)
        floating_pane.SetFloatingPosition(GetStartPosition());

    m_mgr.Update();
}

void MyFrame::OnCustomizeToolbar(wxCommandEvent& WXUNUSED(evt))
{
    wxMessageBox(_("Customize Toolbar clicked"));
}

void MyFrame::OnGradient(wxCommandEvent& event)
{
    int gradient = 0;

    switch (event.GetId())
    {
        case ID_NoGradient:         gradient = wxAUI_GRADIENT_NONE; break;
        case ID_VerticalGradient:   gradient = wxAUI_GRADIENT_VERTICAL; break;
        case ID_HorizontalGradient: gradient = wxAUI_GRADIENT_HORIZONTAL; break;
    }

    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, gradient);
    m_mgr.Update();
}

void MyFrame::OnManagerFlag(wxCommandEvent& event)
{
#if !defined(__WXMSW__) && !defined(__WXMAC__) && !defined(__WXGTK__)
    if (event.GetId() == ID_TransparentDrag ||
        event.GetId() == ID_TransparentHint ||
        event.GetId() == ID_HintFade)
    {
        wxMessageBox(wxT("This option is presently only available on wxGTK, wxMSW and wxMac"));
        return;
    }
#endif

    int id = event.GetId();

    if (id == ID_CloseButton ||
        id == ID_CloseButtonActiveTab ||
        id == ID_CloseButtonAllTabs ||
        id == ID_NoCloseButton)
    {
        m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_BUTTON,false);
        m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB,false);
        m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_ON_ALL_TABS,false);
    }
    else if (id == ID_TabWindowList)
    {
        m_mgr.SetFlag(wxAUI_MGR_NB_WINDOWLIST_BUTTON,event.IsChecked());
    }
    else if(id == ID_FixedWidth)
    {
        m_mgr.SetFlag(wxAUI_MGR_NB_TAB_FIXED_WIDTH,event.IsChecked());
    }
    else if (id == ID_TabsTop ||
        id == ID_TabsLeft ||
        id == ID_TabsRight ||
        id == ID_TabsBottom
        )
    {
        m_mgr.SetFlag(wxAUI_MGR_NB_TOP,false);
        m_mgr.SetFlag(wxAUI_MGR_NB_LEFT,false);
        m_mgr.SetFlag(wxAUI_MGR_NB_RIGHT,false);
        m_mgr.SetFlag(wxAUI_MGR_NB_BOTTOM,false);
    }
    else if (id == ID_TransparentHint ||
        id == ID_VenetianBlindsHint ||
        id == ID_RectangleHint ||
        id == ID_NoHint)
    {
        m_mgr.SetFlag(wxAUI_MGR_TRANSPARENT_HINT,false);
        m_mgr.SetFlag(wxAUI_MGR_VENETIAN_BLINDS_HINT,false);
        m_mgr.SetFlag(wxAUI_MGR_RECTANGLE_HINT,false);
    }

    switch (id)
    {
        case ID_AllowFloating: m_mgr.SetFlag(wxAUI_MGR_ALLOW_FLOATING,true); break;
        case ID_TransparentDrag: m_mgr.SetFlag(wxAUI_MGR_TRANSPARENT_DRAG,true); break;
        case ID_HintFade: m_mgr.SetFlag(wxAUI_MGR_HINT_FADE,true); break;
        case ID_NoVenetianFade: m_mgr.SetFlag(wxAUI_MGR_NO_VENETIAN_BLINDS_FADE,true); break;
        case ID_AllowActivePane: m_mgr.SetFlag(wxAUI_MGR_ALLOW_ACTIVE_PANE,true); break;
        case ID_TransparentHint: m_mgr.SetFlag(wxAUI_MGR_TRANSPARENT_HINT,true); break;
        case ID_VenetianBlindsHint: m_mgr.SetFlag(wxAUI_MGR_VENETIAN_BLINDS_HINT,true); break;
        case ID_RectangleHint: m_mgr.SetFlag(wxAUI_MGR_RECTANGLE_HINT,true); break;
        case ID_LiveUpdate: m_mgr.SetFlag(wxAUI_MGR_LIVE_RESIZE,true); break;
        case ID_TabsTop: m_mgr.SetFlag(wxAUI_MGR_NB_TOP,true); break;
        case ID_TabsLeft: m_mgr.SetFlag(wxAUI_MGR_NB_LEFT,true); break;
        case ID_TabsRight: m_mgr.SetFlag(wxAUI_MGR_NB_RIGHT,true); break;
        case ID_TabsBottom: m_mgr.SetFlag(wxAUI_MGR_NB_BOTTOM,true); break;
        case ID_CloseButton: m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_BUTTON,true); break;
        case ID_CloseButtonActiveTab: m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB,true); break;
        case ID_CloseButtonAllTabs: m_mgr.SetFlag(wxAUI_MGR_NB_CLOSE_ON_ALL_TABS,true); break;
    }

    m_mgr.Update();
}


void MyFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
    unsigned int flags = m_mgr.GetFlags();

    switch (event.GetId())
    {
        case ID_NoGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_NONE);
            break;
        case ID_VerticalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_VERTICAL);
            break;
        case ID_HorizontalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_HORIZONTAL);
            break;
        case ID_AllowFloating:
            event.Check((flags & wxAUI_MGR_ALLOW_FLOATING) != 0);
            break;
        case ID_TransparentDrag:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_DRAG) != 0);
            break;
        case ID_TransparentHint:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_HINT) != 0);
            break;
        case ID_LiveUpdate:
            event.Check((flags & wxAUI_MGR_LIVE_RESIZE) != 0);
            break;
        case ID_VenetianBlindsHint:
            event.Check((flags & wxAUI_MGR_VENETIAN_BLINDS_HINT) != 0);
            break;
        case ID_RectangleHint:
            event.Check((flags & wxAUI_MGR_RECTANGLE_HINT) != 0);
            break;
        case ID_NoHint:
            event.Check(((wxAUI_MGR_TRANSPARENT_HINT |
                          wxAUI_MGR_VENETIAN_BLINDS_HINT |
                          wxAUI_MGR_RECTANGLE_HINT) & flags) == 0);
            break;
        case ID_HintFade:
            event.Check((flags & wxAUI_MGR_HINT_FADE) != 0);
            break;
        case ID_NoVenetianFade:
            event.Check((flags & wxAUI_MGR_NO_VENETIAN_BLINDS_FADE) != 0);
            break;
    }
}

void MyFrame::OnPaneClose(wxAuiManagerEvent& evt)
{
    if (evt.pane->GetName() == wxT("test10"))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this pane?"),
                               wxT("wxAUI"),
                               wxYES_NO,
                               this);
        if (res != wxYES)
            evt.Veto();
    }
}

void MyFrame::OnCreatePerspective(wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog dlg(this, wxT("Enter a name for the new perspective:"),
                          wxT("wxAUI Test"));

    dlg.SetValue(wxString::Format(wxT("Perspective %u"), unsigned(m_perspectives.GetCount() + 1)));
    if (dlg.ShowModal() != wxID_OK)
        return;

    if (m_perspectives.GetCount() == 0)
    {
        m_perspectives_menu->AppendSeparator();
    }

    m_perspectives_menu->Append(ID_FirstPerspective + m_perspectives.GetCount(), dlg.GetValue());
    m_perspectives.Add(m_mgr.SavePerspective());
}

void MyFrame::OnCopyPerspectiveCode(wxCommandEvent& WXUNUSED(evt))
{
    wxString s = m_mgr.SavePerspective();

#if wxUSE_CLIPBOARD
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(s));
        wxTheClipboard->Close();
    }
#endif
}

void MyFrame::OnRestorePerspective(wxCommandEvent& evt)
{
    m_mgr.LoadPerspective(m_perspectives.Item(evt.GetId() - ID_FirstPerspective));
}


wxPoint MyFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}

void MyFrame::OnCreateTree(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  SetCaption(wxT("Tree Control")).
                  Float().SetFloatingPosition(GetStartPosition()).
                  SetFloatingSize(wxSize(150,300)));
    m_mgr.Update();
}

void MyFrame::OnCreateGrid(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateGrid(), wxAuiPaneInfo().
                  SetCaption(wxT("Grid")).
                  Float().SetFloatingPosition(GetStartPosition()).
                  SetFloatingSize(wxSize(300,200)));
    m_mgr.Update();
}

void MyFrame::OnCreateHTML(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateHTMLCtrl(), wxAuiPaneInfo().
                  SetCaption(wxT("HTML Control")).
                  Float().SetFloatingPosition(GetStartPosition()).
                  SetFloatingSize(wxSize(300,200)));
    m_mgr.Update();
}

void MyFrame::OnCreateText(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTextCtrl(), wxAuiPaneInfo().
                  SetCaption(wxT("Text Control")).
                  Float().SetFloatingPosition(GetStartPosition()));
    m_mgr.Update();
}

void MyFrame::OnCreateSizeReport(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  SetCaption(wxT("Client Size Reporter")).
                  Float().SetFloatingPosition(GetStartPosition()).
                  SetCloseButton(true).SetMaximizeButton(true));
    m_mgr.Update();
}

void MyFrame::OnChangeContentPane(wxCommandEvent& evt)
{
    m_mgr.GetPane(wxT("grid_content")).Show(evt.GetId() == ID_GridContent);
    m_mgr.GetPane(wxT("text_content")).Show(evt.GetId() == ID_TextContent);
    m_mgr.GetPane(wxT("tree_content")).Show(evt.GetId() == ID_TreeContent);
    m_mgr.GetPane(wxT("sizereport_content")).Show(evt.GetId() == ID_SizeReportContent);
    m_mgr.GetPane(wxT("html_content")).Show(evt.GetId() == ID_HTMLContent);
    m_mgr.Update();
}

void MyFrame::OnDropDownToolbarItem(wxAuiToolBarEvent& evt)
{
    if (evt.IsDropDownClicked())
    {
        wxAuiToolBar* tb = static_cast<wxAuiToolBar*>(evt.GetEventObject());

        tb->SetToolSticky(evt.GetId(), true);

        // create the popup menu
        wxMenu menuPopup;

        wxBitmap bmp = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));

        wxMenuItem* m1 =  new wxMenuItem(&menuPopup, 10001, _("Drop Down Item 1"));
        m1->SetBitmap(bmp);
        menuPopup.Append(m1);

        wxMenuItem* m2 =  new wxMenuItem(&menuPopup, 10002, _("Drop Down Item 2"));
        m2->SetBitmap(bmp);
        menuPopup.Append(m2);

        wxMenuItem* m3 =  new wxMenuItem(&menuPopup, 10003, _("Drop Down Item 3"));
        m3->SetBitmap(bmp);
        menuPopup.Append(m3);

        wxMenuItem* m4 =  new wxMenuItem(&menuPopup, 10004, _("Drop Down Item 4"));
        m4->SetBitmap(bmp);
        menuPopup.Append(m4);

        // line up our menu with the button
        wxRect rect = tb->GetToolRect(evt.GetId());
        wxPoint pt = tb->ClientToScreen(rect.GetBottomLeft());
        pt = ScreenToClient(pt);


        PopupMenu(&menuPopup, pt);


        // make sure the button is "un-stuck"
        tb->SetToolSticky(evt.GetId(), false);
    }
}


void MyFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_("wxAUI Demo\nAn advanced window management library for wxWidgets\n(c) Copyright 2005-2006, Kirix Corporation"), _("About wxAUI Demo"), wxOK, this);
}

wxTextCtrl* MyFrame::CreateTextCtrl(const wxString& ctrl_text)
{
    static int n = 0;

    wxString text;
    if (ctrl_text.Length() > 0)
        text = ctrl_text;
    else
        text.Printf(wxT("This is text box %d"), ++n);

    return new wxTextCtrl(this,wxID_ANY, text,
                          wxPoint(0,0), wxSize(150,90),
                          wxNO_BORDER | wxTE_MULTILINE);
}


wxGrid* MyFrame::CreateGrid()
{
    wxGrid* grid = new wxGrid(this, wxID_ANY,
                              wxPoint(0,0),
                              wxSize(150,250),
                              wxNO_BORDER | wxWANTS_CHARS);
    grid->CreateGrid(50, 20);
    return grid;
}

wxTreeCtrl* MyFrame::CreateTreeCtrl()
{
    wxTreeCtrl* tree = new wxTreeCtrl(this, wxID_ANY,
                                      wxPoint(0,0), wxSize(160,250),
                                      wxTR_DEFAULT_STYLE | wxNO_BORDER);

    wxImageList* imglist = new wxImageList(16, 16, true, 2);
    imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
    imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
    tree->AssignImageList(imglist);

    wxTreeItemId root = tree->AddRoot(wxT("wxAUI Project"), 0);
    wxArrayTreeItemIds items;



    items.Add(tree->AppendItem(root, wxT("Item 1"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 2"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 3"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 4"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 5"), 0));


    int i, count;
    for (i = 0, count = items.Count(); i < count; ++i)
    {
        wxTreeItemId id = items.Item(i);
        tree->AppendItem(id, wxT("Subitem 1"), 1);
        tree->AppendItem(id, wxT("Subitem 2"), 1);
        tree->AppendItem(id, wxT("Subitem 3"), 1);
        tree->AppendItem(id, wxT("Subitem 4"), 1);
        tree->AppendItem(id, wxT("Subitem 5"), 1);
    }


    tree->Expand(root);

    return tree;
}

wxSizeReportCtrl* MyFrame::CreateSizeReportCtrl(int width, int height)
{
    wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(this, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(width, height), &m_mgr);
    return ctrl;
}

wxHtmlWindow* MyFrame::CreateHTMLCtrl(wxWindow* parent)
{
    if (!parent)
        parent = this;

    wxHtmlWindow* ctrl = new wxHtmlWindow(parent, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(400,300));
    ctrl->SetPage(GetIntroText());
    return ctrl;
}

wxString MyFrame::GetIntroText()
{
    const char* text =
        "<html><body>"
        "<h3>Welcome to wxAUI</h3>"
        "<br/><b>Overview</b><br/>"
        "<p>wxAUI is an Advanced User Interface library for the wxWidgets toolkit "
        "that allows developers to create high-quality, cross-platform user "
        "interfaces quickly and easily.</p>"
        "<p><b>Features</b></p>"
        "<p>With wxAUI, developers can create application frameworks with:</p>"
        "<ul>"
        "<li>Native, dockable floating frames</li>"
        "<li>Perspective saving and loading</li>"
        "<li>Native toolbars incorporating real-time, &quot;spring-loaded&quot; dragging</li>"
        "<li>Customizable floating/docking behavior</li>"
        "<li>Completely customizable look-and-feel</li>"
        "<li>Optional transparent window effects (while dragging or docking)</li>"
        "<li>Splittable notebook control</li>"
        "</ul>"
        "<p><b>What's new in 0.9.4?</b></p>"
        "<p>wxAUI 0.9.4, which is bundled with wxWidgets, adds the following features:"
        "<ul>"
        "<li>New wxAuiToolBar class, a toolbar control which integrates more "
        "cleanly with wxAuiFrameManager.</li>"
        "<li>Lots of bug fixes</li>"
        "</ul>"
        "<p><b>What's new in 0.9.3?</b></p>"
        "<p>wxAUI 0.9.3, which is now bundled with wxWidgets, adds the following features:"
        "<ul>"
        "<li>New wxAuiNotebook class, a dynamic splittable notebook control</li>"
        "<li>New wxAuiMDI* classes, a tab-based MDI and drop-in replacement for classic MDI</li>"
        "<li>Maximize/Restore buttons implemented</li>"
        "<li>Better hinting with wxGTK</li>"
        "<li>Class rename.  'wxAui' is now the standard class prefix for all wxAUI classes</li>"
        "<li>Lots of bug fixes</li>"
        "</ul>"
        "<p><b>What's new in 0.9.2?</b></p>"
        "<p>The following features/fixes have been added since the last version of wxAUI:</p>"
        "<ul>"
        "<li>Support for wxMac</li>"
        "<li>Updates for wxWidgets 2.6.3</li>"
        "<li>Fix to pass more unused events through</li>"
        "<li>Fix to allow floating windows to receive idle events</li>"
        "<li>Fix for minimizing/maximizing problem with transparent hint pane</li>"
        "<li>Fix to not paint empty hint rectangles</li>"
        "<li>Fix for 64-bit compilation</li>"
        "</ul>"
        "<p><b>What changed in 0.9.1?</b></p>"
        "<p>The following features/fixes were added in wxAUI 0.9.1:</p>"
        "<ul>"
        "<li>Support for MDI frames</li>"
        "<li>Gradient captions option</li>"
        "<li>Active/Inactive panes option</li>"
        "<li>Fix for screen artifacts/paint problems</li>"
        "<li>Fix for hiding/showing floated window problem</li>"
        "<li>Fix for floating pane sizing problem</li>"
        "<li>Fix for drop position problem when dragging around center pane margins</li>"
        "<li>LF-only text file formatting for source code</li>"
        "</ul>"
        "<p>See README.txt for more information.</p>"
        "</body></html>";

    return wxString::FromAscii(text);
}
