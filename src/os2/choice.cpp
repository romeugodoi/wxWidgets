/////////////////////////////////////////////////////////////////////////////
// Name:        choice.cpp
// Purpose:     wxChoice
// Author:      David Webster
// Modified by:
// Created:     10/13/99
// RCS-ID:      $Id$
// Copyright:   (c) David Webster
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/choice.h"
    #include "wx/utils.h"
    #include "wx/log.h"
#endif

#include "wx/os2/private.h"

IMPLEMENT_DYNAMIC_CLASS(wxChoice, wxControl)

bool wxChoice::Create(
  wxWindow*                         pParent
, wxWindowID                        vId
, const wxPoint&                    rPos
, const wxSize&                     rSize
, int                               n
, const wxString                    asChoices[]
, long                              lStyle
#if wxUSE_VALIDATORS
, const wxValidator&                rValidator
#endif
, const wxString&                   rsName
)
{
    long                            lSstyle;

    if (!OS2CreateControl( pParent
                          ,vId
                          ,rPos
                          ,rSize
                          ,lStyle
#if wxUSE_VALIDATORS
                          ,rValidator
#endif
                          ,rsName
                         ))
        return FALSE;
    lSstyle = CBS_DROPDOWNLIST |
              WS_TABSTOP       |
              WS_VISIBLE;

    if (lStyle & wxCLIP_SIBLINGS )
        lSstyle |= WS_CLIPSIBLINGS;

    wxASSERT_MSG( !(lStyle & wxCB_DROPDOWN) &&
                  !(lStyle & wxCB_READONLY) &&
                  !(lStyle & wxCB_SIMPLE),
                  wxT("this style flag is ignored by wxChoice, you "
                     "probably want to use a wxComboBox") );

    if (!OS2CreateControl( wxT("COMBOBOX")
                          ,lSstyle
                         ))
        return FALSE;

    //
    // A choice/combobox normally has a white background (or other, depending
    // on global settings) rather than inheriting the parent's background colour.
    //
    SetBackgroundColour(wxSystemSettings::GetSystemColour(wxSYS_COLOUR_WINDOW));
    for (int i = 0; i < n; i++)
    {
        Append(asChoices[i]);
    }
    SetSize( rPos.x
            ,rPos.y
            ,rSize.x
            ,rSize.y
           );

    return TRUE;
} // end of wxChoice::Create

// ----------------------------------------------------------------------------
// adding/deleting items to/from the list
// ----------------------------------------------------------------------------

int wxChoice::DoAppend(
  const wxString&                   rsItem
)
{
    int                             nIndex;
    SHORT                           nIndexType = 0;

    if (m_windowStyle & wxLB_SORT)
        nIndexType = LIT_SORTASCENDING;
    else
        nIndexType = LIT_END;
    nIndex = (int)::WinSendMsg( GetHwnd()
                               ,LM_INSERTITEM
                               ,(MPARAM)nIndexType
                               ,(MPARAM)rsItem.c_str()
                              );
    return nIndex;
} // end of wxChoice::DoAppend

void wxChoice::Delete(
  int                               n
)
{
    wxCHECK_RET( n < GetCount(), wxT("invalid item index in wxChoice::Delete") );
    ::WinSendMsg(GetHwnd(), LM_DELETEITEM, (MPARAM)n, (MPARAM)0);
} // end of wxChoice::Delete

void wxChoice::Clear()
{
    Free();
    ::WinSendMsg(GetHwnd(), LM_DELETEALL, (MPARAM)0, (MPARAM)0);
} // end of wxChoice::Clear

// ----------------------------------------------------------------------------
// selection
// ----------------------------------------------------------------------------

int wxChoice::GetSelection() const
{
    return((int)LONGFROMMR(::WinSendMsg(GetHwnd(), LM_QUERYSELECTION, (MPARAM)LIT_FIRST, (MPARAM)0)));
} // end of wxChoice::GetSelection

void wxChoice::SetSelection(
  int                               n
)
{
    ::WinSendMsg( GetHwnd()
                 ,LM_SELECTITEM
                 ,(MPARAM)n
                 ,(MPARAM)TRUE
                );
} // end of wxChoice::SetSelection

// ----------------------------------------------------------------------------
// string list functions
// ----------------------------------------------------------------------------

int wxChoice::GetCount() const
{
    return((int)LONGFROMMR(::WinSendMsg(GetHwnd(), LM_QUERYITEMCOUNT, (MPARAM)0, (MPARAM)0)));
} // end of wxChoice::GetCount

int wxChoice::FindString(
  const wxString&                   rsStr
) const
{
    int                             nPos;
    int                             nTextLength;
    PSZ                             zStr;
    int                             nItemCount;

    nItemCount = (int)LONGFROMMR(::WinSendMsg(GetHwnd(), LM_QUERYITEMCOUNT, (MPARAM)0, (MPARAM)0));
    for (nPos = 0; nPos < nItemCount; nPos++)
    {
        nTextLength = (int)LONGFROMMR(::WinSendMsg(GetHwnd(), LM_QUERYITEMTEXTLENGTH, (MPARAM)nPos, (MPARAM)0));
        zStr = new char[nTextLength + 1];
        ::WinSendMsg(GetHwnd(), LM_QUERYITEMTEXT, MPFROM2SHORT((SHORT)nPos, (SHORT)nTextLength), (MPARAM)zStr);
        if (rsStr == (char*)zStr)
        {
            delete [] zStr;
            break;
        }
        delete [] zStr;
    }
    return nPos;
} // end of wxChoice::FindString

void wxChoice::SetString(
  int                               n
, const wxString&                   rsStr
)
{
    wxFAIL_MSG(wxT("not implemented"));

#if 0 // should do this, but no Insert() so far
    Delete(n);
    Insert(n + 1, s);
#endif
} // end of wxChoice::SetString

wxString wxChoice::GetString(
  int                               n
) const
{
    size_t                          nLen = 0;
    wxString                        sStr = "";
    char*                           zBuf;

    nLen = (size_t)LONGFROMMR(::WinSendMsg(GetHwnd(), LM_QUERYITEMTEXTLENGTH, (MPARAM)n, (MPARAM)0));
    if (nLen)
    {
        zBuf = new char[nLen + 1];
        ::WinSendMsg( GetHwnd()
                     ,LM_QUERYITEMTEXT
                     ,MPFROM2SHORT((SHORT)n, (SHORT)nLen)
                     ,(MPARAM)zBuf
                    );
        sStr = zBuf;
        delete [] zBuf;
    }
    return sStr;
} // end of wxChoice::GetString

// ----------------------------------------------------------------------------
// client data
// ----------------------------------------------------------------------------

void wxChoice::DoSetItemClientData(
  int                               n
, void*                             pClientData
)
{
    ::WinSendMsg(GetHwnd(), LM_SETITEMHANDLE, (MPARAM)n, MPFROMP(pClientData));
} // end of wxChoice::DoSetItemClientData

void* wxChoice::DoGetItemClientData( int n ) const
{
    MRESULT                         rc = 0L;

    rc = ::WinSendMsg(GetHwnd(), LM_QUERYITEMHANDLE, (MPARAM)n, (MPARAM)0);
    return((void*)rc);
} // end of wxChoice::DoSetItemClientData

void wxChoice::DoSetItemClientObject(
  int                               n
, wxClientData*                     pClientData
)
{
    DoSetItemClientData( n
                        ,pClientData
                       );
} // end of wxChoice::DoSetItemClientObject

wxClientData* wxChoice::DoGetItemClientObject(
  int                               n
) const
{
    return (wxClientData *)DoGetItemClientData(n);
} // end of wxChoice::DoGetItemClientObject

// ----------------------------------------------------------------------------
// wxOS2 specific helpers
// ----------------------------------------------------------------------------

void wxChoice::DoSetSize(
  int                               nX
, int                               nY
, int                               nWidth
, int                               nHeight
, int                               nSizeFlags
)
{
    //
    // Ignore height parameter because height doesn't mean 'initially
    // displayed' height, it refers to the drop-down menu as well. The
    // wxWindows interpretation is different; also, getting the size returns
    // the _displayed_ size (NOT the drop down menu size) so
    // setting-getting-setting size would not work.
    //
    wxControl::DoSetSize( nX
                         ,nY
                         ,nWidth
                         ,-1
                         ,nSizeFlags
                        );
} // end of wxChoice::DoSetSize

wxSize wxChoice::DoGetBestSize() const
{
    //
    // Find the widest string
    //
    int                             nLineWidth;
    int                             nChoiceWidth = 0;
    int                             nItems = GetCount();
    int                             nCx;
    int                             nCy;

    for (int i = 0; i < nItems; i++)
    {
        wxString                    sStr(GetString(i));

        GetTextExtent( sStr
                      ,&nLineWidth
                      ,NULL
                     );
        if (nLineWidth > nChoiceWidth)
            nChoiceWidth = nLineWidth;
    }

    //
    // Give it some reasonable default value if there are no strings in the
    // list
    //
    if (nChoiceWidth == 0L)
        nChoiceWidth = 100L;

    //
    // The combobox should be larger than the widest string
    //
    wxGetCharSize( GetHWND()
                  ,&nCx
                  ,&nCy
                  ,(wxFont*)&GetFont()
                 );
    nChoiceWidth += 5 * nCx;

    //
    // Choice drop-down list depends on number of items (limited to 10)
    //
    size_t                          nStrings = nItems == 0 ? 10 : wxMin(10, nItems) + 1;
    int                             nChoiceHeight = EDIT_HEIGHT_FROM_CHAR_HEIGHT(nCy) * nStrings;

    return wxSize( nChoiceWidth
                  ,nChoiceHeight
                 );
} // end of wxChoice::DoGetBestSize

MRESULT wxChoice::OS2WindowProc(
  WXUINT                            uMsg
, WXWPARAM                          wParam
, WXLPARAM                          lParam
)
{
    return wxWindow::OS2WindowProc( uMsg
                                   ,wParam
                                   ,lParam
                                  );
} // end of wxChoice::OS2WindowProc

bool wxChoice::OS2Command(
  WXUINT                            uParam
, WXWORD                            WXUNUSED(wId)
)
{
    if (uParam != LN_SELECT)
    {
        //
        // "selection changed" is the only event we're after
        //
        return FALSE;
    }
    int                             n = GetSelection();

    if (n > -1)
    {
        wxCommandEvent              vEvent( wxEVT_COMMAND_CHOICE_SELECTED
                                           ,m_windowId
                                          );

        vEvent.SetInt(n);
        vEvent.SetEventObject(this);
        vEvent.SetString((char*)GetStringSelection().c_str());
        if (HasClientObjectData())
            vEvent.SetClientObject(GetClientObject(n));
        else if (HasClientUntypedData())
            vEvent.SetClientData(GetClientData(n));
        ProcessCommand(vEvent);
    }
    return TRUE;
} // end of wxChoice::OS2Command

void wxChoice::Free()
{
    if (HasClientObjectData())
    {
        size_t                      nCount = GetCount();

        for (size_t n = 0; n < nCount; n++)
        {
            delete GetClientObject(n);
        }
    }
} // end of wxhoice::Free
