/////////////////////////////////////////////////////////////////////////////
// Name:        xh_choicbk.cpp
// Purpose:     XRC resource for wxChoicebook
// Author:      Vaclav Slavik
// Created:     2000/03/21
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "xh_choicbk.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC && wxUSE_CHOICEBOOK

#include "wx/xrc/xh_choicbk.h"

#include "wx/log.h"
#include "wx/choicebk.h"
#include "wx/imaglist.h"
#include "wx/sizer.h"

IMPLEMENT_DYNAMIC_CLASS(wxChoicebookXmlHandler, wxXmlResourceHandler)

wxChoicebookXmlHandler::wxChoicebookXmlHandler()
: wxXmlResourceHandler(), m_isInside(false), m_choicebook(NULL)
{
    XRC_ADD_STYLE(wxCB_DEFAULT);
    XRC_ADD_STYLE(wxCB_LEFT);
    XRC_ADD_STYLE(wxCB_RIGHT);
    XRC_ADD_STYLE(wxCB_TOP);
    XRC_ADD_STYLE(wxCB_BOTTOM);

    AddWindowStyles();
}

wxObject *wxChoicebookXmlHandler::DoCreateResource()
{
    if (m_class == wxT("choicebookpage"))
    {
        wxXmlNode *n = GetParamNode(wxT("object"));

        if ( !n )
            n = GetParamNode(wxT("object_ref"));

        if (n)
        {
            bool old_ins = m_isInside;
            m_isInside = false;
            wxObject *item = CreateResFromNode(n, m_choicebook, NULL);
            m_isInside = old_ins;
            wxWindow *wnd = wxDynamicCast(item, wxWindow);

            if (wnd)
            {
                m_choicebook->AddPage(wnd, GetText(wxT("label")),
                                           GetBool(wxT("selected")));
                if ( HasParam(wxT("bitmap")) )
                {
                    wxBitmap bmp = GetBitmap(wxT("bitmap"), wxART_OTHER);
                    wxImageList *imgList = m_choicebook->GetImageList();
                    if ( imgList == NULL )
                    {
                        imgList = new wxImageList( bmp.GetWidth(), bmp.GetHeight() );
                        m_choicebook->AssignImageList( imgList );
                    }
                    int imgIndex = imgList->Add(bmp);
                    m_choicebook->SetPageImage(m_choicebook->GetPageCount()-1, imgIndex );
                }
            }
            else
                wxLogError(wxT("Error in resource."));
            return wnd;
        }
        else
        {
            wxLogError(wxT("Error in resource: no control within choicebook's <page> tag."));
            return NULL;
        }
    }

    else
    {
        XRC_MAKE_INSTANCE(nb, wxChoicebook)

        nb->Create(m_parentAsWindow,
                   GetID(),
                   GetPosition(), GetSize(),
                   GetStyle(wxT("style")),
                   GetName());

        wxChoicebook *old_par = m_choicebook;
        m_choicebook = nb;
        bool old_ins = m_isInside;
        m_isInside = true;
        CreateChildren(m_choicebook, true/*only this handler*/);
        m_isInside = old_ins;
        m_choicebook = old_par;

        return nb;
    }
}

bool wxChoicebookXmlHandler::CanHandle(wxXmlNode *node)
{
    return ((!m_isInside && IsOfClass(node, wxT("wxChoicebook"))) ||
            (m_isInside && IsOfClass(node, wxT("choicebookpage"))));
}

#endif // wxUSE_XRC && wxUSE_CHOICEBOOK
