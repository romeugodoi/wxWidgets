/////////////////////////////////////////////////////////////////////////////
// Name:        dirdlg.cpp
// Purpose:     wxDirDialog
// Author:      Harm van der Heijden, Robert Roebling & Julian Smart
// Modified by:
// Created:     12/12/98
// RCS-ID:      $Id$
// Copyright:   (c) Harm van der Heijden, Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "dirdlgg.h"
#endif


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/defs.h"

#if wxUSE_DIRDLG

#ifndef WX_PRECOMP
    #include "wx/textctrl.h"
    #include "wx/button.h"
    #include "wx/checkbox.h"
    #include "wx/sizer.h"
    #include "wx/intl.h"
    #include "wx/log.h"
    #include "wx/msgdlg.h"
#endif

#include "wx/statline.h"
#include "wx/dirctrl.h"
#include "wx/generic/dirdlgg.h"
#include "wx/artprov.h"
#include "wx/bmpbuttn.h"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

static const int ID_DIRCTRL = 1000;
static const int ID_TEXTCTRL = 1001;
static const int ID_OK = 1002;
static const int ID_CANCEL = 1003;
static const int ID_NEW = 1004;
static const int ID_SHOW_HIDDEN = 1005;
static const int ID_GO_HOME = 1006;

// ---------------------------------------------------------------------------
// macros
// ---------------------------------------------------------------------------

/* Macro for avoiding #ifdefs when value have to be different depending on size of
   device we display on - take it from something like wxDesktopPolicy in the future
 */

#if defined(__SMARTPHONE__)
    #define wxLARGESMALL(large,small) small
#else
    #define wxLARGESMALL(large,small) large
#endif

//-----------------------------------------------------------------------------
// wxGenericDirDialog
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxGenericDirDialog, wxDialog)

BEGIN_EVENT_TABLE(wxGenericDirDialog, wxDialog)
    EVT_CLOSE                (wxGenericDirDialog::OnCloseWindow)
    EVT_BUTTON               (wxID_OK,        wxGenericDirDialog::OnOK)
    EVT_BUTTON               (ID_NEW,         wxGenericDirDialog::OnNew)
    EVT_BUTTON               (ID_GO_HOME,     wxGenericDirDialog::OnGoHome)
    EVT_TREE_KEY_DOWN        (wxID_ANY,       wxGenericDirDialog::OnTreeKeyDown)
    EVT_TREE_SEL_CHANGED     (wxID_ANY,       wxGenericDirDialog::OnTreeSelected)
    EVT_TEXT_ENTER           (ID_TEXTCTRL,    wxGenericDirDialog::OnOK)
    EVT_CHECKBOX             (ID_SHOW_HIDDEN, wxGenericDirDialog::OnShowHidden)
END_EVENT_TABLE()

wxGenericDirDialog::wxGenericDirDialog(wxWindow* parent, const wxString& title,
                                       const wxString& defaultPath, long style,
                                       const wxPoint& pos, const wxSize& sz,
                                       const wxString& name):
                wxDialog(parent, ID_DIRCTRL, title, pos, sz, style, name)
{
    wxBusyCursor cursor;

    m_path = defaultPath;
    if (m_path == wxT("~"))
        wxGetHomeDir(&m_path);
    if (m_path == wxT("."))
        m_path = wxGetCwd();

    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    // smart phones does not support or do not waste space for wxButtons
#if defined(__SMARTPHONE__)

    wxMenu *dirMenu = new wxMenu;
    dirMenu->Append(ID_GO_HOME, _("Home"));

    if (style & wxDD_NEW_DIR_BUTTON)
    {
        dirMenu->Append(ID_NEW, _("New directory"));
    }

    dirMenu->AppendCheckItem(ID_SHOW_HIDDEN, _("Show hidden directories"));
    dirMenu->AppendSeparator();
    dirMenu->Append(wxID_CANCEL, _("Cancel"));

    SetRightMenu(wxID_ANY, _("Options"), dirMenu);

#else

    // 0) 'New' and 'Home' Buttons
    wxSizer* buttonsizer = new wxBoxSizer( wxHORIZONTAL );

    // VS: 'Home directory' concept is unknown to MS-DOS
#if !defined(__DOS__)
    wxBitmapButton* homeButton =
        new wxBitmapButton(this, ID_GO_HOME,
                           wxArtProvider::GetBitmap(wxART_GO_HOME, wxART_BUTTON));
    buttonsizer->Add( homeButton, 0, wxLEFT|wxRIGHT, 10 );
#endif

    // I'm not convinced we need a New button, and we tend to get annoying
    // accidental-editing with label editing enabled.
    if (style & wxDD_NEW_DIR_BUTTON)
    {
        wxBitmapButton* newButton =
            new wxBitmapButton(this, ID_NEW,
                            wxArtProvider::GetBitmap(wxART_NEW_DIR, wxART_BUTTON));
        buttonsizer->Add( newButton, 0, wxRIGHT, 10 );
#if wxUSE_TOOLTIPS
        newButton->SetToolTip(_("Create new directory"));
#endif
    }

#if wxUSE_TOOLTIPS
    homeButton->SetToolTip(_("Go to home directory"));
#endif

    topsizer->Add( buttonsizer, 0, wxTOP | wxALIGN_RIGHT, 10 );

#endif // __SMARTPHONE__/!__SMARTPHONE__

    // 1) dir ctrl
    m_dirCtrl = NULL; // this is necessary, event handler called from
                      // wxGenericDirCtrl would crash otherwise!
    long dirStyle = wxDIRCTRL_DIR_ONLY | wxDEFAULT_CONTROL_BORDER;

#ifdef __WXMSW__
    if (style & wxDD_NEW_DIR_BUTTON)
    {
        // Only under Windows do we need the wxTR_EDIT_LABEL tree control style
        // before we can call EditLabel (required for "New directory")
        dirStyle |= wxDIRCTRL_EDIT_LABELS;
    }
#endif

    m_dirCtrl = new wxGenericDirCtrl(this, ID_DIRCTRL,
                                     m_path, wxDefaultPosition,
                                     wxSize(300, 200),
                                     dirStyle);

    topsizer->Add( m_dirCtrl, 1, wxTOP|wxLEFT|wxRIGHT | wxEXPAND, wxLARGESMALL(10,0) );

#ifndef __SMARTPHONE__
    // Make the an option depending on a flag?
    wxCheckBox* check = new wxCheckBox( this, ID_SHOW_HIDDEN, _("Show hidden directories") );
    topsizer->Add( check, 0, wxLEFT|wxRIGHT|wxTOP | wxALIGN_RIGHT, 10 );
#endif // !__SMARTPHONE__

    // 2) text ctrl
    m_input = new wxTextCtrl( this, ID_TEXTCTRL, m_path, wxDefaultPosition );
    topsizer->Add( m_input, 0, wxTOP|wxLEFT|wxRIGHT | wxEXPAND, wxLARGESMALL(10,0) );

#ifndef __SMARTPHONE__

#if wxUSE_STATLINE
    // 3) Static line
    topsizer->Add( new wxStaticLine( this, wxID_ANY ), 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10 );
#endif

    // 4) Buttons
    topsizer->Add( CreateButtonSizer( wxOK|wxCANCEL ), 0, wxEXPAND | wxALL, 10 );

#endif // !__SMARTPHONE__

    m_input->SetFocus();

    SetAutoLayout( true );
    SetSizer( topsizer );

#if !defined(__SMARTPHONE__) && !defined(__POCKETPC__)
    topsizer->SetSizeHints( this );
    topsizer->Fit( this );

    Centre( wxBOTH );
#endif
}

void wxGenericDirDialog::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
    EndModal(wxID_CANCEL);
}

void wxGenericDirDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
    m_path = m_input->GetValue();
    // Does the path exist? (User may have typed anything in m_input)
    if (wxDirExists(m_path)) {
        // OK, path exists, we're done.
        EndModal(wxID_OK);
        return;
    }
    // Interact with user, find out if the dir is a typo or to be created
    wxString msg;
    msg.Printf(_("The directory '%s' does not exist\nCreate it now?"),
               m_path.c_str());
    wxMessageDialog dialog(this, msg, _("Directory does not exist"),
                           wxYES_NO | wxICON_WARNING);

    if ( dialog.ShowModal() == wxID_YES ) {
        // Okay, let's make it
        wxLogNull log;
        if (wxMkdir(m_path)) {
            // The new dir was created okay.
            EndModal(wxID_OK);
            return;
        }
        else {
            // Trouble...
            msg.Printf(_("Failed to create directory '%s'\n(Do you have the required permissions?)"),
                       m_path.c_str());
            wxMessageDialog errmsg(this, msg, _("Error creating directory"), wxOK | wxICON_ERROR);
            errmsg.ShowModal();
            // We still don't have a valid dir. Back to the main dialog.
        }
    }
    // User has answered NO to create dir.
}

void wxGenericDirDialog::SetPath(const wxString& path)
{
    m_dirCtrl->SetPath(path);
    m_path = path;
}

wxString wxGenericDirDialog::GetPath(void) const
{
    return m_path;
}

int wxGenericDirDialog::ShowModal()
{
    m_input->SetValue( m_path );
    return wxDialog::ShowModal();
}

void wxGenericDirDialog::OnTreeSelected( wxTreeEvent &event )
{
    if (!m_dirCtrl)
        return;

    wxTreeItemId item = event.GetItem();

    wxDirItemData *data = NULL;

    if(item.IsOk())
        data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(item);

    if (data)
       m_input->SetValue( data->m_path );
};

void wxGenericDirDialog::OnTreeKeyDown( wxTreeEvent &WXUNUSED(event) )
{
    if (!m_dirCtrl)
        return;

    wxDirItemData *data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(m_dirCtrl->GetTreeCtrl()->GetSelection());
    if (data)
        m_input->SetValue( data->m_path );
};

void wxGenericDirDialog::OnShowHidden( wxCommandEvent& event )
{
    if (!m_dirCtrl)
        return;

    m_dirCtrl->ShowHidden( event.GetInt() != 0 );
}

void wxGenericDirDialog::OnNew( wxCommandEvent& WXUNUSED(event) )
{
    wxTreeItemId id = m_dirCtrl->GetTreeCtrl()->GetSelection();
    if ((id == m_dirCtrl->GetTreeCtrl()->GetRootItem()) ||
        (m_dirCtrl->GetTreeCtrl()->GetItemParent(id) == m_dirCtrl->GetTreeCtrl()->GetRootItem()))
    {
        wxMessageDialog msg(this, _("You cannot add a new directory to this section."),
                            _("Create directory"), wxOK | wxICON_INFORMATION );
        msg.ShowModal();
        return;
    }

    wxTreeItemId parent = id ; // m_dirCtrl->GetTreeCtrl()->GetItemParent( id );
    wxDirItemData *data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData( parent );
    wxASSERT( data );

    wxString new_name( _("NewName") );
    wxString path( data->m_path );
    if (!wxEndsWithPathSeparator(path))
        path += wxFILE_SEP_PATH;
    path += new_name;
    if (wxDirExists(path))
    {
        // try NewName0, NewName1 etc.
        int i = 0;
        do {
            new_name = _("NewName");
            wxString num;
            num.Printf( wxT("%d"), i );
            new_name += num;

            path = data->m_path;
            if (!wxEndsWithPathSeparator(path))
                path += wxFILE_SEP_PATH;
            path += new_name;
            i++;
        } while (wxDirExists(path));
    }

    wxLogNull log;
    if (!wxMkdir(path))
    {
        wxMessageDialog dialog(this, _("Operation not permitted."), _("Error"), wxOK | wxICON_ERROR );
        dialog.ShowModal();
        return;
    }

    wxDirItemData *new_data = new wxDirItemData( path, new_name, true );

    // TODO: THIS CODE DOESN'T WORK YET. We need to avoid duplication of the first child
    // of the parent.
    wxTreeItemId new_id = m_dirCtrl->GetTreeCtrl()->AppendItem( parent, new_name, 0, 0, new_data );
    m_dirCtrl->GetTreeCtrl()->EnsureVisible( new_id );
    m_dirCtrl->GetTreeCtrl()->EditLabel( new_id );
}

void wxGenericDirDialog::OnGoHome(wxCommandEvent& WXUNUSED(event))
{
    SetPath(wxGetUserHome());
}

#endif // wxUSE_DIRDLG
