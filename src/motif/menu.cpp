/////////////////////////////////////////////////////////////////////////////
// Name:        menu.cpp
// Purpose:     wxMenu, wxMenuBar, wxMenuItem
// Author:      Julian Smart
// Modified by:
// Created:     17/09/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


// ============================================================================
// declarations
// ============================================================================

#ifdef __GNUG__
    #pragma implementation "menu.h"
#endif

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/menu.h"
#include "wx/menuitem.h"
#include "wx/log.h"
#include "wx/utils.h"
#include "wx/app.h"
#include "wx/frame.h"
#include "wx/settings.h"

#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/CascadeBG.h>
#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushBG.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/RowColumn.h>

#include "wx/motif/private.h"

// other standard headers
#include <string.h>

#if !USE_SHARED_LIBRARY
IMPLEMENT_DYNAMIC_CLASS(wxMenu, wxEvtHandler)
IMPLEMENT_DYNAMIC_CLASS(wxMenuBar, wxEvtHandler)
#endif

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// Menus
// ----------------------------------------------------------------------------

// Construct a menu with optional title (then use append)
void wxMenu::Init(const wxString& title,
                  long style
#ifdef WXWIN_COMPATIBILITY
                  , const wxFunction func
#endif
                 )
{
    m_title = title;
    m_eventHandler = this;
    m_noItems = 0;
    m_menuBar = NULL;
    m_pInvokingWindow = NULL;
    m_style = style;

    //// Motif-specific members
    m_numColumns = 1;
    m_menuWidget = (WXWidget) NULL;
    m_popupShell = (WXWidget) NULL;
    m_buttonWidget = (WXWidget) NULL;
    m_menuId = 0;
    m_topLevelMenu  = (wxMenu*) NULL;
    m_ownedByMenuBar = FALSE;
    m_menuParent = (wxMenu*) NULL;
    m_clientData = (void*) NULL;

    if (m_title != "")
    {
        Append(ID_SEPARATOR, m_title) ;
        AppendSeparator() ;
    }
    m_backgroundColour = wxSystemSettings::GetSystemColour(wxSYS_COLOUR_MENU);
    m_foregroundColour = wxSystemSettings::GetSystemColour(wxSYS_COLOUR_MENUTEXT);
    m_font = wxSystemSettings::GetSystemFont(wxSYS_DEFAULT_GUI_FONT);

#ifdef WXWIN_COMPATIBILITY
    Callback(func);
#endif
}

// The wxWindow destructor will take care of deleting the submenus.
wxMenu::~wxMenu()
{
    if (m_menuWidget)
    {
        if (m_menuParent)
            DestroyMenu(TRUE);
        else
            DestroyMenu(FALSE);
    }

    // Not sure if this is right
    if (m_menuParent && m_menuBar)
    {
        m_menuParent = NULL;
        //      m_menuBar = NULL;
    }

    wxNode *node = m_menuItems.First();
    while (node)
    {
        wxMenuItem *item = (wxMenuItem *)node->Data();

        /*
        if (item->GetSubMenu())
        item->DeleteSubMenu();
        */

        wxNode *next = node->Next();
        delete item;
        delete node;
        node = next;
    }
}

void wxMenu::Break()
{
    m_numColumns ++;
}

// function appends a new item or submenu to the menu
void wxMenu::Append(wxMenuItem *pItem)
{
    wxCHECK_RET( pItem != NULL, "can't append NULL item to the menu" );

    m_menuItems.Append(pItem);

    if (m_menuWidget)
        pItem->CreateItem (m_menuWidget, m_menuBar, m_topLevelMenu); // this is a dynamic Append

    m_noItems++;
}

void wxMenu::AppendSeparator()
{
    Append(new wxMenuItem(this, ID_SEPARATOR));
}

// Pullright item
// N.B.: difference between old and new code.
// Old code stores subMenu in 'children' for later deletion,
// as well as in m_menuItems, whereas we only store it in
// m_menuItems here. What implications does this have?

void wxMenu::Append(int id, const wxString& label, wxMenu *subMenu,
                    const wxString& helpString)
{
    Append(new wxMenuItem(this, id, label, helpString, FALSE, subMenu));

    subMenu->m_topLevelMenu = m_topLevelMenu;
}

// Ordinary menu item
void wxMenu::Append(int id, const wxString& label,
                    const wxString& helpString, bool checkable)
{
    // 'checkable' parameter is useless for Windows.
    Append(new wxMenuItem(this, id, label, helpString, checkable));
}

void wxMenu::Delete(int id)
{
    wxNode *node;
    wxMenuItem *item;
    int pos;

    for (pos = 0, node = m_menuItems.First(); node; node = node->Next(), pos++)
    {
        item = (wxMenuItem *)node->Data();
        if (item->GetId() == id)
            break;
    }

    if (!node)
        return;

    item->DestroyItem(TRUE);

    // See also old code - don't know if this is needed (seems redundant).
    /*
    if (item->GetSubMenu()) {
    item->subMenu->top_level_menu = item->GetSubMenu();
    item->subMenu->window_parent = NULL;
    children->DeleteObject(item->GetSubMenu());
    }
    */

    m_menuItems.DeleteNode(node);
    delete item;
}

void wxMenu::Enable(int id, bool flag)
{
    wxMenuItem *item = FindItemForId(id);
    wxCHECK_RET( item != NULL, "can't enable non-existing menu item" );

    item->Enable(flag);
}

bool wxMenu::Enabled(int Id) const
{
    wxMenuItem *item = FindItemForId(Id);
    wxCHECK( item != NULL, FALSE );

    return item->IsEnabled();
}

void wxMenu::Check(int Id, bool Flag)
{
    wxMenuItem *item = FindItemForId(Id);
    wxCHECK_RET( item != NULL, "can't get status of non-existing menu item" );

    item->Check(Flag);
}

bool wxMenu::Checked(int id) const
{
    wxMenuItem *item = FindItemForId(id);
    wxCHECK( item != NULL, FALSE );

    return item->IsChecked();
}

void wxMenu::SetTitle(const wxString& label)
{
    m_title = label ;

    wxNode *node = m_menuItems.First ();
    if (!node)
        return;

    wxMenuItem *item = (wxMenuItem *) node->Data ();
    Widget widget = (Widget) item->GetButtonWidget();
    if (!widget)
        return;

    XmString title_str = XmStringCreateSimple ((char*) (const char*) label);
    XtVaSetValues (widget,
        XmNlabelString, title_str,
        NULL);
    // TODO: should we delete title_str now?
}

const wxString wxMenu::GetTitle() const
{
    return m_title;
}

void wxMenu::SetLabel(int id, const wxString& label)
{
    wxMenuItem *item = FindItemForId(id);
    if (item == (wxMenuItem*) NULL)
        return;

    item->SetText(label);
}

wxString wxMenu::GetLabel(int id) const
{
    wxMenuItem *it = NULL;
    WXWidget w = FindMenuItem (id, &it);
    if (w)
    {
        XmString text;
        char *s;
        XtVaGetValues ((Widget) w,
            XmNlabelString, &text,
            NULL);

        if (XmStringGetLtoR (text, XmSTRING_DEFAULT_CHARSET, &s))
        {
            wxString str(s);
            XtFree (s);
            return str;
        }
        else
        {
            XmStringFree (text);
            return wxEmptyString;
        }
    }
    else
        return wxEmptyString;
}

// Finds the item id matching the given string, -1 if not found.
int wxMenu::FindItem (const wxString& itemString) const
{
    char buf1[200];
    char buf2[200];
    wxStripMenuCodes ((char *)(const char *)itemString, buf1);

    for (wxNode * node = m_menuItems.First (); node; node = node->Next ())
    {
        wxMenuItem *item = (wxMenuItem *) node->Data ();
        if (item->GetSubMenu())
        {
            int ans = item->GetSubMenu()->FindItem(itemString);
            if (ans > -1)
                return ans;
        }
        if ( !item->IsSeparator() )
        {
            wxStripMenuCodes((char *)item->GetName().c_str(), buf2);
            if (strcmp(buf1, buf2) == 0)
                return item->GetId();
        }
    }

    return -1;
}

wxMenuItem *wxMenu::FindItemForId(int itemId, wxMenu ** itemMenu) const
{
    if (itemMenu)
        *itemMenu = NULL;
    for (wxNode * node = m_menuItems.First (); node; node = node->Next ())
    {
        wxMenuItem *item = (wxMenuItem *) node->Data ();

        if (item->GetId() == itemId)
        {
            if (itemMenu)
                *itemMenu = (wxMenu *) this;
            return item;
        }

        if (item->GetSubMenu())
        {
            wxMenuItem *ans = item->GetSubMenu()->FindItemForId (itemId, itemMenu);
            if (ans)
                return ans;
        }
    }

    if (itemMenu)
        *itemMenu = NULL;
    return NULL;
}

void wxMenu::SetHelpString(int itemId, const wxString& helpString)
{
    wxMenuItem *item = FindItemForId (itemId);
    if (item)
        item->SetHelp(helpString);
}

wxString wxMenu::GetHelpString (int itemId) const
{
    wxMenuItem *item = FindItemForId (itemId);
    wxString str("");
    return (item == NULL) ? str : item->GetHelp();
}

void wxMenu::ProcessCommand(wxCommandEvent & event)
{
    bool processed = FALSE;

    // Try a callback
    if (m_callback)
    {
        (void) (*(m_callback)) (*this, event);
        processed = TRUE;
    }

    // Try the menu's event handler
    if ( !processed && GetEventHandler())
    {
        processed = GetEventHandler()->ProcessEvent(event);
    }
    // Try the window the menu was popped up from (and up
    // through the hierarchy)
    if ( !processed && GetInvokingWindow())
    processed = GetInvokingWindow()->ProcessEvent(event);
}

// Update a menu and all submenus recursively.
// source is the object that has the update event handlers
// defined for it. If NULL, the menu or associated window
// will be used.
void wxMenu::UpdateUI(wxEvtHandler* source)
{
  if (!source && GetInvokingWindow())
    source = GetInvokingWindow()->GetEventHandler();
  if (!source)
    source = GetEventHandler();
  if (!source)
    source = this;

  wxNode* node = GetItems().First();
  while (node)
  {
    wxMenuItem* item = (wxMenuItem*) node->Data();
    if ( !item->IsSeparator() )
    {
      wxWindowID id = item->GetId();
      wxUpdateUIEvent event(id);
      event.SetEventObject( source );

      if (source->ProcessEvent(event))
      {
        if (event.GetSetText())
          SetLabel(id, event.GetText());
        if (event.GetSetChecked())
          Check(id, event.GetChecked());
        if (event.GetSetEnabled())
          Enable(id, event.GetEnabled());
      }

      if (item->GetSubMenu())
        item->GetSubMenu()->UpdateUI(source);
    }
    node = node->Next();
  }
}

// ----------------------------------------------------------------------------
// Menu Bar
// ----------------------------------------------------------------------------

void wxMenuBar::Init()
{
    m_eventHandler = this;
    m_menuBarFrame = NULL;
    m_mainWidget = (WXWidget) NULL;
    m_backgroundColour = wxSystemSettings::GetSystemColour(wxSYS_COLOUR_MENU);
    m_foregroundColour = wxSystemSettings::GetSystemColour(wxSYS_COLOUR_MENUTEXT);
    m_font = wxSystemSettings::GetSystemFont(wxSYS_DEFAULT_GUI_FONT);
}

wxMenuBar::wxMenuBar(int n, wxMenu *menus[], const wxString titles[])
{
    Init();

    for ( int i = 0; i < n; i++ )
    {
        m_menus.Append(menus[i]);
        m_titles.Add(titles[i]);
    }
}

wxMenuBar::~wxMenuBar()
{
    // nothing to do: wxMenuBarBase will delete the menus
}

void wxMenuBar::EnableTop(size_t WXUNUSED(pos), bool WXUNUSED(flag))
{
    wxFAIL_MSG("TODO");
}

void wxMenuBar::SetLabelTop(size_t pos, const wxString& label)
{
    wxMenu *menu = GetMenu(pos);
    if ( !menu )
        return;

    Widget w = (Widget)menu->GetButtonWidget();
    if (w)
    {
        wxXmString label_str(label);

        XtVaSetValues(w,
                      XmNlabelString, label_str(),
                      NULL);
    }
}

wxString wxMenuBar::GetLabelTop(size_t pos) const
{
    wxString str;

    wxMenu *menu = GetMenu(pos);
    if ( menu )
    {
        Widget w = (Widget)menu->GetButtonWidget();
        if (w)
        {
            XmString text;
            XtVaGetValues(w,
                          XmNlabelString, &text,
                          NULL);

            char *s;
            if ( XmStringGetLtoR(text, XmSTRING_DEFAULT_CHARSET, &s) )
            {
                str = s;

                XtFree(s);
            }
        }
    }

    return str;
}

bool wxMenuBar::Append(wxMenu * menu, const wxString& title)
{
    wxCHECK_MSG( menu, FALSE, wxT("invalid menu") );
    wxCHECK_MSG( !menu->GetParent() && !menu->GetButtonWidget(), FALSE,
                 wxT("menu already appended") );

    if ( m_menuBarFrame )
    {
        WXWidget w = menu->CreateMenu(this, GetMainWidget(), menu, title, TRUE);
        wxCHECK_MSG( w, FALSE, wxT("failed to create menu") );
        menu->SetButtonWidget(w);
    }

    menu->SetMenuBar(this);

    m_titles.Add(title);

    return wxMenuBarBase::Append(menu, title);
}

bool wxMenuBar::Insert(size_t pos, wxMenu *menu, const wxString& title)
{
    if ( !wxMenuBarBase::Insert(pos, menu, title) )
        return FALSE;

    wxFAIL_MSG(wxT("TODO"));

    return FALSE;
}

wxMenu *wxMenuBar::Replace(size_t pos, wxMenu *menu, const wxString& title)
{
    if ( !wxMenuBarBase::Replace(pos, menu, title) )
        return FALSE;

    wxFAIL_MSG(wxT("TODO"));

    return NULL;
}

wxMenu *wxMenuBar::Remove(size_t pos)
{
    wxMenu *menu = wxMenuBarBase::Remove(pos);
    if ( !menu )
        return NULL;

    if ( m_menuBarFrame )
        menu->DestroyMenu(TRUE);

    menu->SetMenuBar(NULL);

    m_titles.Remove(pos);

    return menu;
}

// Find the menu menuString, item itemString, and return the item id.
// Returns -1 if none found.
int wxMenuBar::FindMenuItem (const wxString& menuString, const wxString& itemString) const
{
    char buf1[200];
    char buf2[200];
    wxStripMenuCodes ((char *)(const char *)menuString, buf1);

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
    {
        wxStripMenuCodes ((char *)(const char *)m_titles[i], buf2);
        if (strcmp (buf1, buf2) == 0)
            return m_menus[i]->FindItem (itemString);
    }
    return -1;
}

wxMenuItem *wxMenuBar::FindItem(int id, wxMenu ** itemMenu) const
{
    if (itemMenu)
        *itemMenu = NULL;

    wxMenuItem *item = NULL;
    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
        if ((item = m_menus[i]->FindItemForId (id, itemMenu)))
            return item;
        return NULL;
}

// Create menubar
bool wxMenuBar::CreateMenuBar(wxFrame* parent)
{
    if (m_mainWidget)
    {
        XtVaSetValues((Widget) parent->GetMainWindowWidget(), XmNmenuBar, (Widget) m_mainWidget, NULL);
        /*
        if (!XtIsManaged((Widget) m_mainWidget))
        XtManageChild((Widget) m_mainWidget);
        */
        XtMapWidget((Widget) m_mainWidget);
        return TRUE;
    }

    Widget menuBarW = XmCreateMenuBar ((Widget) parent->GetMainWindowWidget(), "MenuBar", NULL, 0);
    m_mainWidget = (WXWidget) menuBarW;

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
    {
        wxMenu *menu = GetMenu(i);
        wxString title(m_titles[i]);
        menu->SetButtonWidget(menu->CreateMenu (this, menuBarW, menu, title, TRUE));

        if (strcmp (wxStripMenuCodes(title), "Help") == 0)
            XtVaSetValues ((Widget) menuBarW, XmNmenuHelpWidget, (Widget) menu->GetButtonWidget(), NULL);

        // tear off menu support
#if (XmVersion >= 1002)
        if ( menu->IsTearOff() )
        {
            XtVaSetValues(GetWidget(menu),
                          XmNtearOffModel, XmTEAR_OFF_ENABLED,
                          NULL);
#endif
        }
    }

    SetBackgroundColour(m_backgroundColour);
    SetForegroundColour(m_foregroundColour);
    SetFont(m_font);

    XtVaSetValues((Widget) parent->GetMainWindowWidget(), XmNmenuBar, (Widget) m_mainWidget, NULL);
    XtRealizeWidget ((Widget) menuBarW);
    XtManageChild ((Widget) menuBarW);
    SetMenuBarFrame(parent);

    return TRUE;
}

// Destroy menubar, but keep data structures intact so we can recreate it.
bool wxMenuBar::DestroyMenuBar()
{
    if (!m_mainWidget)
    {
        SetMenuBarFrame((wxFrame*) NULL);
        return FALSE;
    }

    XtUnmanageChild ((Widget) m_mainWidget);
    XtUnrealizeWidget ((Widget) m_mainWidget);

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
    {
        wxMenu *menu = GetMenu(i);
        menu->DestroyMenu(TRUE);

    }
    XtDestroyWidget((Widget) m_mainWidget);
    m_mainWidget = (WXWidget) 0;

    SetMenuBarFrame((wxFrame*) NULL);

    return TRUE;
}

//// Motif-specific
static XtWorkProcId WorkProcMenuId;

/* Since PopupMenu under Motif stills grab right mouse button events
* after it was closed, we need to delete the associated widgets to
* allow next PopUpMenu to appear...
*/

int PostDeletionOfMenu( XtPointer* clientData )
{
    XtRemoveWorkProc(WorkProcMenuId);
    wxMenu *menu = (wxMenu *)clientData;

    if (menu->GetMainWidget()) {
        if (menu->GetParent())
        {
            wxList& list = menu->GetParent()->GetItems();
            list.DeleteObject(menu);
        }
        menu->DestroyMenu(TRUE);
    }
    /* Mark as no longer popped up */
    menu->m_menuId = -1;
    return TRUE;
}

void
wxMenuPopdownCallback(Widget WXUNUSED(w), XtPointer clientData,
                      XtPointer WXUNUSED(ptr))
{
    wxMenu *menu = (wxMenu *)clientData;

    // Added by JOREL Jean-Charles <jjorel@silr.ireste.fr>
    /* Since Callbacks of MenuItems are not yet processed, we put a
    * background job which will be done when system will be idle.
    * What awful hack!! :(
    */

    WorkProcMenuId = XtAppAddWorkProc(
        (XtAppContext) wxTheApp->GetAppContext(),
        (XtWorkProc) PostDeletionOfMenu,
        (XtPointer) menu );
    // Apparently not found in Motif headers
    //  XtVaSetValues( w, XmNpopupEnabled, XmPOPUP_DISABLED, NULL );
}

/*
* Create a popup or pulldown menu.
* Submenus of a popup will be pulldown.
*
*/

WXWidget wxMenu::CreateMenu (wxMenuBar * menuBar, WXWidget parent, wxMenu * topMenu, const wxString& title, bool pullDown)
{
    Widget menu = (Widget) 0;
    Widget buttonWidget = (Widget) 0;
    Arg args[5];
    XtSetArg (args[0], XmNnumColumns, m_numColumns);
    XtSetArg (args[1], XmNpacking, XmPACK_COLUMN);

    if (!pullDown)
    {
        menu = XmCreatePopupMenu ((Widget) parent, "popup", args, 2);
        XtAddCallback(menu,
            XmNunmapCallback,
            (XtCallbackProc)wxMenuPopdownCallback,
            (XtPointer)this);
    }
    else
    {
        char mnem = wxFindMnemonic (title);
        wxStripMenuCodes ((char*) (const char*) title, wxBuffer);

        menu = XmCreatePulldownMenu ((Widget) parent, "pulldown", args, 2);

        wxString title2(wxStripMenuCodes(title));
        wxXmString label_str(title2);
        buttonWidget = XtVaCreateManagedWidget(title2,
#if wxUSE_GADGETS
            xmCascadeButtonGadgetClass, (Widget) parent,
#else
            xmCascadeButtonWidgetClass, (Widget) parent,
#endif
            XmNlabelString, label_str(),
            XmNsubMenuId, menu,
            NULL);

        if (mnem != 0)
            XtVaSetValues (buttonWidget, XmNmnemonic, mnem, NULL);
    }

    m_menuWidget = (WXWidget) menu;

    m_menuBar = menuBar;
    m_topLevelMenu = topMenu;

    for (wxNode * node = m_menuItems.First (); node; node = node->Next ())
    {
        wxMenuItem *item = (wxMenuItem *) node->Data ();
        item->CreateItem (menu, menuBar, topMenu);
    }

    SetBackgroundColour(m_backgroundColour);
    SetForegroundColour(m_foregroundColour);
    SetFont(m_font);

    return buttonWidget;
}

// Destroys the Motif implementation of the menu,
// but maintains the wxWindows data structures so we can
// do a CreateMenu again.
void wxMenu::DestroyMenu (bool full)
{
    for (wxNode * node = m_menuItems.First (); node; node = node->Next ())
    {
        wxMenuItem *item = (wxMenuItem *) node->Data ();
        item->SetMenuBar((wxMenuBar*) NULL);

        item->DestroyItem(full);
    }// for()

    if (m_buttonWidget)
    {
        if (full)
        {
            XtVaSetValues((Widget) m_buttonWidget, XmNsubMenuId, NULL, NULL);
            XtDestroyWidget ((Widget) m_buttonWidget);
            m_buttonWidget = (WXWidget) 0;
        }
    }
    if (m_menuWidget && full)
    {
        XtDestroyWidget((Widget) m_menuWidget);
        m_menuWidget = (WXWidget) NULL;
    }
}

WXWidget wxMenu::FindMenuItem (int id, wxMenuItem ** it) const
{
    if (id == m_menuId)
    {
        if (it)
            *it = (wxMenuItem*) NULL;
        return m_buttonWidget;
    }

    for (wxNode * node = m_menuItems.First (); node; node = node->Next ())
    {
        wxMenuItem *item = (wxMenuItem *) node->Data ();
        if (item->GetId() == id)
        {
            if (it)
                *it = item;
            return item->GetButtonWidget();
        }

        if (item->GetSubMenu())
        {
            WXWidget w = item->GetSubMenu()->FindMenuItem (id, it);
            if (w)
            {
                return w;
            }
        }
    }// for()

    if (it)
        *it = (wxMenuItem*) NULL;
    return (WXWidget) NULL;
}

void wxMenu::SetBackgroundColour(const wxColour& col)
{
    m_backgroundColour = col;
    if (m_menuWidget)
        wxDoChangeBackgroundColour(m_menuWidget, (wxColour&) col);
    if (m_buttonWidget)
        wxDoChangeBackgroundColour(m_buttonWidget, (wxColour&) col, TRUE);

    wxNode* node = m_menuItems.First();
    while (node)
    {
        wxMenuItem* item = (wxMenuItem*) node->Data();
        if (item->GetButtonWidget())
        {
            // This crashes because it uses gadgets
            //            wxDoChangeBackgroundColour(item->GetButtonWidget(), (wxColour&) col, TRUE);
        }
        if (item->GetSubMenu())
            item->GetSubMenu()->SetBackgroundColour((wxColour&) col);
        node = node->Next();
    }
}

void wxMenu::SetForegroundColour(const wxColour& col)
{
    m_foregroundColour = col;
    if (m_menuWidget)
        wxDoChangeForegroundColour(m_menuWidget, (wxColour&) col);
    if (m_buttonWidget)
        wxDoChangeForegroundColour(m_buttonWidget, (wxColour&) col);

    wxNode* node = m_menuItems.First();
    while (node)
    {
        wxMenuItem* item = (wxMenuItem*) node->Data();
        if (item->GetButtonWidget())
        {
            // This crashes because it uses gadgets
            //            wxDoChangeForegroundColour(item->GetButtonWidget(), (wxColour&) col);
        }
        if (item->GetSubMenu())
            item->GetSubMenu()->SetForegroundColour((wxColour&) col);
        node = node->Next();
    }
}

void wxMenu::ChangeFont(bool keepOriginalSize)
{
    // lesstif 0.87 hangs when setting XmNfontList
#ifndef LESSTIF_VERSION
    if (!m_font.Ok() || !m_menuWidget)
        return;

    XmFontList fontList = (XmFontList) m_font.GetFontList(1.0, XtDisplay((Widget) m_menuWidget));

    XtVaSetValues ((Widget) m_menuWidget,
        XmNfontList, fontList,
        NULL);
    if (m_buttonWidget)
    {
        XtVaSetValues ((Widget) m_buttonWidget,
            XmNfontList, fontList,
            NULL);
    }
    wxNode* node = m_menuItems.First();
    while (node)
    {
        wxMenuItem* item = (wxMenuItem*) node->Data();
        if (m_menuWidget && item->GetButtonWidget() && m_font.Ok())
        {
            XtVaSetValues ((Widget) item->GetButtonWidget(),
                XmNfontList, fontList,
                NULL);
        }
        if (item->GetSubMenu())
            item->GetSubMenu()->ChangeFont(keepOriginalSize);
        node = node->Next();
    }
#endif
}

void wxMenu::SetFont(const wxFont& font)
{
    m_font = font;
    ChangeFont();
}

bool wxMenuBar::SetBackgroundColour(const wxColour& col)
{
    m_backgroundColour = col;
    if (m_mainWidget)
        wxDoChangeBackgroundColour(m_mainWidget, (wxColour&) col);

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
        m_menus[i]->SetBackgroundColour((wxColour&) col);

    return TRUE;
}

bool wxMenuBar::SetForegroundColour(const wxColour& col)
{
    m_foregroundColour = col;
    if (m_mainWidget)
        wxDoChangeForegroundColour(m_mainWidget, (wxColour&) col);

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
        m_menus[i]->SetForegroundColour((wxColour&) col);

    return TRUE;
}

void wxMenuBar::ChangeFont(bool WXUNUSED(keepOriginalSize))
{
    // Nothing to do for menubar, fonts are kept in wxMenus
}

bool wxMenuBar::SetFont(const wxFont& font)
{
    m_font = font;
    ChangeFont();

    size_t menuCount = GetMenuCount();
    for (size_t i = 0; i < menuCount; i++)
        m_menus[i]->SetFont(font);

    return TRUE;
}

