/////////////////////////////////////////////////////////////////////////////
// Name:        gtk/fontdlg.cpp
// Purpose:     wxFontDialog
// Author:      Robert Roebling
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/defs.h"

#if wxUSE_FONTDLG

#ifndef __WXGPE__

#include "wx/fontdlg.h"
#include "wx/fontutil.h"
#include "wx/utils.h"
#include "wx/intl.h"
#include "wx/debug.h"
#include "wx/msgdlg.h"

#include "wx/gtk/private.h"

//-----------------------------------------------------------------------------
// idle system
//-----------------------------------------------------------------------------

extern void wxapp_install_idle_handler();
extern bool g_isIdle;

//-----------------------------------------------------------------------------
// "delete_event"
//-----------------------------------------------------------------------------

extern "C" {
static
bool gtk_fontdialog_delete_callback( GtkWidget *WXUNUSED(widget), GdkEvent *WXUNUSED(event), wxDialog *win )
{
    if (g_isIdle)
        wxapp_install_idle_handler();

/*
    printf( "OnDelete from " );
    if (win->GetClassInfo() && win->GetClassInfo()->GetClassName())
        printf( win->GetClassInfo()->GetClassName() );
    printf( ".\n" );
*/

    win->Close();

    return TRUE;
}
}

//-----------------------------------------------------------------------------
// "clicked" for OK-button
//-----------------------------------------------------------------------------

extern "C" {
static
void gtk_fontdialog_ok_callback( GtkWidget *WXUNUSED(widget), wxFontDialog *dialog )
{
    if (g_isIdle)
        wxapp_install_idle_handler();

    GtkFontSelectionDialog *fontdlg = GTK_FONT_SELECTION_DIALOG(dialog->m_widget);

    gchar *fontname = gtk_font_selection_dialog_get_font_name(fontdlg);
    dialog->SetChosenFont( fontname);

    g_free( fontname );

    wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, wxID_OK);
    event.SetEventObject( dialog );
    dialog->GetEventHandler()->ProcessEvent( event );
}
}

//-----------------------------------------------------------------------------
// "clicked" for Cancel-button
//-----------------------------------------------------------------------------

extern "C" {
static
void gtk_fontdialog_cancel_callback( GtkWidget *WXUNUSED(w), wxFontDialog *dialog )
{
    if (g_isIdle)
        wxapp_install_idle_handler();

    wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, wxID_CANCEL);
    event.SetEventObject( dialog );
    dialog->GetEventHandler()->ProcessEvent( event );
}
}

//-----------------------------------------------------------------------------
// wxFontDialog
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxFontDialog, wxDialog)

bool wxFontDialog::DoCreate(wxWindow *parent)
{
    m_needParent = FALSE;

    if (!PreCreation( parent, wxDefaultPosition, wxDefaultSize ) ||
        !CreateBase( parent, -1, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE,
                     wxDefaultValidator, wxT("fontdialog") ))
    {
        wxFAIL_MSG( wxT("wxFontDialog creation failed") );
        return FALSE;
    }

    wxString m_message( _("Choose font") );
    m_widget = gtk_font_selection_dialog_new( wxGTK_CONV( m_message ) );

    if (parent)
        gtk_window_set_transient_for(GTK_WINDOW(m_widget),
                                     GTK_WINDOW(parent->m_widget));

    GtkFontSelectionDialog *sel = GTK_FONT_SELECTION_DIALOG(m_widget);

    g_signal_connect (sel->ok_button, "clicked",
                      G_CALLBACK (gtk_fontdialog_ok_callback), this);

    g_signal_connect (sel->cancel_button, "clicked",
                      G_CALLBACK (gtk_fontdialog_cancel_callback), this);

    g_signal_connect (m_widget, "delete_event",
                      G_CALLBACK (gtk_fontdialog_delete_callback), this);

    wxFont font = m_fontData.GetInitialFont();
    if( font.Ok() )
    {
        const wxNativeFontInfo *info = font.GetNativeFontInfo();

        if ( info )
        {

            const wxString& fontname = info->ToString();
            gtk_font_selection_dialog_set_font_name(sel, wxGTK_CONV(fontname));
        }
        else
        {
            // this is not supposed to happen!
            wxFAIL_MSG(_T("font is ok but no native font info?"));
        }
    }

    return TRUE;
}

wxFontDialog::~wxFontDialog()
{
}

void wxFontDialog::SetChosenFont(const char *fontname)
{
    m_fontData.SetChosenFont(wxFont( wxString::FromAscii(fontname) ));
}

#endif // wxUSE_FONTDLG

#endif // GPE

