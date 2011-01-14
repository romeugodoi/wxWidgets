/////////////////////////////////////////////////////////////////////////////
// Name:        src/richtext/richtextxml.cpp
// Purpose:     XML and HTML I/O for wxRichTextCtrl
// Author:      Julian Smart
// Modified by:
// Created:     2005-09-30
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_RICHTEXT && wxUSE_XML

#include "wx/richtext/richtextxml.h"

#ifndef WX_PRECOMP
    #include "wx/intl.h"
    #include "wx/module.h"
    #include "wx/log.h"
#endif

#include "wx/filename.h"
#include "wx/clipbrd.h"
#include "wx/wfstream.h"
#include "wx/sstream.h"
#include "wx/txtstrm.h"
#include "wx/mstream.h"
#include "wx/tokenzr.h"
#include "wx/stopwatch.h"
#include "wx/xml/xml.h"

// Set to 1 for slower wxXmlDocument method, 0 for faster direct method.
// If we make wxXmlDocument::Save more efficient, we might switch to this
// method.
#define wxRICHTEXT_USE_XMLDOCUMENT_OUTPUT 0

#if wxRICHTEXT_USE_XMLDOCUMENT_OUTPUT && !wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
#   error Must define wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT in richtextxml.h to use this method.
#endif

#if !wxRICHTEXT_USE_XMLDOCUMENT_OUTPUT && !wxRICHTEXT_HAVE_DIRECT_OUTPUT
#   error Must define wxRICHTEXT_HAVE_DIRECT_OUTPUT in richtextxml.h to use this method.
#endif

// Set to 1 to time file saving
#define wxRICHTEXT_USE_OUTPUT_TIMINGS 0

// Convert a colour to a 6-digit hex string
static wxString ColourToHexString(const wxColour& col)
{
    wxString hex;

    hex += wxDecToHex(col.Red());
    hex += wxDecToHex(col.Green());
    hex += wxDecToHex(col.Blue());

    return hex;
}

// Convert 6-digit hex string to a colour
static wxColour HexStringToColour(const wxString& hex)
{
    unsigned char r = (unsigned char)wxHexToDec(hex.Mid(0, 2));
    unsigned char g = (unsigned char)wxHexToDec(hex.Mid(2, 2));
    unsigned char b = (unsigned char)wxHexToDec(hex.Mid(4, 2));

    return wxColour(r, g, b);
}

static inline wxString MakeString(const int& v) { return wxString::Format(wxT("%d"), v); }
static inline wxString MakeString(const long& v) { return wxString::Format(wxT("%ld"), v); }
static inline wxString MakeString(const double& v) { return wxString::Format(wxT("%.2f"), (float) v); }
static inline wxString MakeString(const wxString& s) { return s; }
static inline wxString MakeString(const wxColour& col) { return wxT("#") + ColourToHexString(col); }

static inline void AddString(wxString& str, const int& v) { str << wxString::Format(wxT("%d"), v); }
static inline void AddString(wxString& str, const long& v) { str << wxString::Format(wxT("%ld"), v); }
static inline void AddString(wxString& str, const double& v) { str << wxString::Format(wxT("%.2f"), (float) v); }
static inline void AddString(wxString& str, const wxChar* s) { str << s; }
static inline void AddString(wxString& str, const wxString& s) { str << s; }
static inline void AddString(wxString& str, const wxColour& col) { str << wxT("#") << ColourToHexString(col); }

IMPLEMENT_DYNAMIC_CLASS(wxRichTextXMLHandler, wxRichTextFileHandler)

void wxRichTextXMLHandler::Init()
{
#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
    // Used during saving
    m_convMem = NULL;
    m_convFile = NULL;
#endif
}

#if wxUSE_STREAMS
bool wxRichTextXMLHandler::DoLoadFile(wxRichTextBuffer *buffer, wxInputStream& stream)
{
    if (!stream.IsOk())
        return false;

    buffer->ResetAndClearCommands();
    buffer->Clear();

    wxXmlDocument* xmlDoc = new wxXmlDocument;
    bool success = true;

    // This is the encoding to convert to (memory encoding rather than file encoding)
    wxString encoding(wxT("UTF-8"));

#if !wxUSE_UNICODE && wxUSE_INTL
    encoding = wxLocale::GetSystemEncodingName();
#endif

    if (!xmlDoc->Load(stream, encoding))
    {
        buffer->ResetAndClearCommands();
        success = false;
    }
    else
    {
        if (xmlDoc->GetRoot() && xmlDoc->GetRoot()->GetType() == wxXML_ELEMENT_NODE && xmlDoc->GetRoot()->GetName() == wxT("richtext"))
        {
            wxXmlNode* child = xmlDoc->GetRoot()->GetChildren();
            while (child)
            {
                if (child->GetType() == wxXML_ELEMENT_NODE)
                {
                    wxString name = child->GetName();
                    if (name == wxT("richtext-version"))
                    {
                    }
                    else
                        ImportXML(buffer, buffer, child);
                }

                child = child->GetNext();
            }
        }
        else
        {
            success = false;
        }
    }

    delete xmlDoc;

    buffer->UpdateRanges();

    return success;
}

/// Creates an object given an XML element name
wxRichTextObject* wxRichTextXMLHandler::CreateObjectForXMLName(wxRichTextObject* WXUNUSED(parent), const wxString& name) const
{
    if (name == wxT("text") || name == wxT("symbol"))
        return new wxRichTextPlainText;
    else if (name == wxT("image"))
        return new wxRichTextImage;
    else if (name == wxT("paragraph"))
        return new wxRichTextParagraph;
    else if (name == wxT("paragraphlayout"))
        return new wxRichTextParagraphLayoutBox;
    else if (name == wxT("textbox"))
        return new wxRichTextBox;
    else if (name == wxT("cell"))
        return new wxRichTextBox;
    else if (name == wxT("table"))
        return new wxRichTextBox;
    else
        return NULL;
}

/// Recursively import an object
bool wxRichTextXMLHandler::ImportXML(wxRichTextBuffer* buffer, wxRichTextObject* obj, wxXmlNode* node)
{
    bool recurse = false;
    obj->ImportFromXML(buffer, node, this, & recurse);
    
    // TODO: how to control whether to import children.
    
    wxRichTextCompositeObject* compositeParent = wxDynamicCast(obj, wxRichTextCompositeObject);
    if (recurse && compositeParent)
    {
        wxXmlNode* child = node->GetChildren();
        while (child)
        {
            if (child->GetName() != wxT("stylesheet"))
            {
                wxRichTextObject* childObj = CreateObjectForXMLName(obj, child->GetName());
                if (childObj)
                {
                    compositeParent->AppendChild(childObj);
                    ImportXML(buffer, childObj, child);
                }
            }
            child = child->GetNext();
        }
    }

    return true;
}

bool wxRichTextXMLHandler::ImportProperties(wxRichTextObject* obj, wxXmlNode* node)
{
    wxXmlNode* child = node->GetChildren();
    while (child)
    {
        if (child->GetName() == wxT("properties"))
        {
            wxXmlNode* propertyChild = child->GetChildren();
            while (propertyChild)
            {
                if (propertyChild->GetName() == wxT("property"))
                {
                    wxString name = propertyChild->GetAttribute(wxT("name"), wxEmptyString);
                    wxString value = propertyChild->GetAttribute(wxT("value"), wxEmptyString);
                    wxString type = propertyChild->GetAttribute(wxT("type"), wxEmptyString);
                    
                    wxVariant var = MakePropertyFromString(name, value, type);
                    if (!var.IsNull())
                    {
                        obj->GetProperties().SetProperty(var);
                    }
                }
                propertyChild = propertyChild->GetNext();
            }
        }
        child = child->GetNext();
    }
    return true;
}

bool wxRichTextXMLHandler::ImportStyleDefinition(wxRichTextStyleSheet* sheet, wxXmlNode* node)
{
    wxString styleType = node->GetName();
    wxString styleName = node->GetAttribute(wxT("name"), wxEmptyString);
    wxString baseStyleName = node->GetAttribute(wxT("basestyle"), wxEmptyString);

    if (styleName.empty())
        return false;

    if (styleType == wxT("characterstyle"))
    {
        wxRichTextCharacterStyleDefinition* def = new wxRichTextCharacterStyleDefinition(styleName);
        def->SetBaseStyle(baseStyleName);

        wxXmlNode* child = node->GetChildren();
        while (child)
        {
            if (child->GetName() == wxT("style"))
            {
                wxRichTextAttr attr;
                ImportStyle(attr, child, false);
                def->SetStyle(attr);
            }
            child = child->GetNext();
        }

        sheet->AddCharacterStyle(def);
    }
    else if (styleType == wxT("paragraphstyle"))
    {
        wxRichTextParagraphStyleDefinition* def = new wxRichTextParagraphStyleDefinition(styleName);

        wxString nextStyleName = node->GetAttribute(wxT("nextstyle"), wxEmptyString);
        def->SetNextStyle(nextStyleName);
        def->SetBaseStyle(baseStyleName);

        wxXmlNode* child = node->GetChildren();
        while (child)
        {
            if (child->GetName() == wxT("style"))
            {
                wxRichTextAttr attr;
                ImportStyle(attr, child, true);
                def->SetStyle(attr);
            }
            child = child->GetNext();
        }

        sheet->AddParagraphStyle(def);
    }
    else if (styleType == wxT("boxstyle"))
    {
        wxRichTextBoxStyleDefinition* def = new wxRichTextBoxStyleDefinition(styleName);

        def->SetBaseStyle(baseStyleName);

        wxXmlNode* child = node->GetChildren();
        while (child)
        {
            if (child->GetName() == wxT("style"))
            {
                wxRichTextAttr attr;
                ImportStyle(attr, child, true);
                def->SetStyle(attr);
            }
            child = child->GetNext();
        }

        sheet->AddBoxStyle(def);
    }
    else if (styleType == wxT("liststyle"))
    {
        wxRichTextListStyleDefinition* def = new wxRichTextListStyleDefinition(styleName);

        wxString nextStyleName = node->GetAttribute(wxT("nextstyle"), wxEmptyString);
        def->SetNextStyle(nextStyleName);
        def->SetBaseStyle(baseStyleName);

        wxXmlNode* child = node->GetChildren();
        while (child)
        {
            if (child->GetName() == wxT("style"))
            {
                wxRichTextAttr attr;
                ImportStyle(attr, child, true);

                wxString styleLevel = child->GetAttribute(wxT("level"), wxEmptyString);
                if (styleLevel.empty())
                {
                    def->SetStyle(attr);
                }
                else
                {
                    int level = wxAtoi(styleLevel);
                    if (level > 0 && level <= 10)
                    {
                        def->SetLevelAttributes(level-1, attr);
                    }
                }
            }
            child = child->GetNext();
        }

        sheet->AddListStyle(def);
    }

    return true;
}

//-----------------------------------------------------------------------------
//  xml support routines
//-----------------------------------------------------------------------------

bool wxRichTextXMLHandler::HasParam(wxXmlNode* node, const wxString& param)
{
    return (GetParamNode(node, param) != NULL);
}

wxXmlNode *wxRichTextXMLHandler::GetParamNode(wxXmlNode* node, const wxString& param)
{
    wxCHECK_MSG(node, NULL, wxT("You can't access node data before it was initialized!"));

    wxXmlNode *n = node->GetChildren();

    while (n)
    {
        if (n->GetType() == wxXML_ELEMENT_NODE && n->GetName() == param)
            return n;
        n = n->GetNext();
    }
    return NULL;
}


wxString wxRichTextXMLHandler::GetNodeContent(wxXmlNode *node)
{
    wxXmlNode *n = node;
    if (n == NULL) return wxEmptyString;
    n = n->GetChildren();

    while (n)
    {
        if (n->GetType() == wxXML_TEXT_NODE ||
            n->GetType() == wxXML_CDATA_SECTION_NODE)
            return n->GetContent();
        n = n->GetNext();
    }
    return wxEmptyString;
}


wxString wxRichTextXMLHandler::GetParamValue(wxXmlNode *node, const wxString& param)
{
    if (param.empty())
        return GetNodeContent(node);
    else
        return GetNodeContent(GetParamNode(node, param));
}

wxString wxRichTextXMLHandler::GetText(wxXmlNode *node, const wxString& param, bool WXUNUSED(translate))
{
    wxXmlNode *parNode = GetParamNode(node, param);
    if (!parNode)
        parNode = node;
    wxString str1(GetNodeContent(parNode));
    return str1;
}

wxXmlNode* wxRichTextXMLHandler::FindNode(wxXmlNode* node, const wxString& name)
{
    wxXmlNode* child = node->GetChildren();
    while (child)
    {
        if (child->GetName() == name)
            return child;
    }
    return NULL;
}

// For use with earlier versions of wxWidgets
#ifndef WXUNUSED_IN_UNICODE
#if wxUSE_UNICODE
#define WXUNUSED_IN_UNICODE(x) WXUNUSED(x)
#else
#define WXUNUSED_IN_UNICODE(x) x
#endif
#endif

// write string to output
inline static void OutputString(wxOutputStream& stream, const wxString& str,
                                wxMBConv *WXUNUSED_IN_UNICODE(convMem), wxMBConv *convFile)
{
    if (str.empty()) return;
#if wxUSE_UNICODE
    if (convFile)
    {
        const wxWX2MBbuf buf(str.mb_str(*convFile));
        stream.Write((const char*)buf, strlen((const char*)buf));
    }
    else
    {
        const wxWX2MBbuf buf(str.mb_str(wxConvUTF8));
        stream.Write((const char*)buf, strlen((const char*)buf));
    }
#else
    if ( convFile == NULL )
        stream.Write(str.mb_str(), str.Len());
    else
    {
        wxString str2(str.wc_str(*convMem), *convFile);
        stream.Write(str2.mb_str(), str2.Len());
    }
#endif
}

static void OutputIndentation(wxOutputStream& stream, int indent)
{
    wxString str = wxT("\n");
    for (int i = 0; i < indent; i++)
        str << wxT(' ') << wxT(' ');
    ::OutputString(stream, str, NULL, NULL);
}

// Same as above, but create entities first.
// Translates '<' to "&lt;", '>' to "&gt;" and '&' to "&amp;"
static void OutputStringEnt(wxOutputStream& stream, const wxString& str,
                            wxMBConv *convMem = NULL, wxMBConv *convFile = NULL)
{
    wxString buf;
    size_t i, last, len;
    wxChar c;

    len = str.Len();
    last = 0;
    for (i = 0; i < len; i++)
    {
        c = str.GetChar(i);

        // Original code excluded "&amp;" but we _do_ want to convert
        // the ampersand beginning &amp; because otherwise when read in,
        // the original "&amp;" becomes "&".

        if (c == wxT('<') || c == wxT('>') || c == wxT('"') ||
            (c == wxT('&') /* && (str.Mid(i+1, 4) != wxT("amp;")) */ ))
        {
            OutputString(stream, str.Mid(last, i - last), convMem, convFile);
            switch (c)
            {
            case wxT('<'):
                OutputString(stream, wxT("&lt;"), NULL, NULL);
                break;
            case wxT('>'):
                OutputString(stream, wxT("&gt;"), NULL, NULL);
                break;
            case wxT('&'):
                OutputString(stream, wxT("&amp;"), NULL, NULL);
                break;
            case wxT('"'):
                OutputString(stream, wxT("&quot;"), NULL, NULL);
                break;
            default: break;
            }
            last = i + 1;
        }
        else if (wxUChar(c) > 127)
        {
            OutputString(stream, str.Mid(last, i - last), convMem, convFile);

            wxString s(wxT("&#"));
#if wxUSE_UNICODE
            s << (int) c;
#else
            s << (int) wxUChar(c);
#endif
            s << wxT(";");
            OutputString(stream, s, NULL, NULL);
            last = i + 1;
        }
    }
    OutputString(stream, str.Mid(last, i - last), convMem, convFile);
}

void wxRichTextXMLHandler::OutputString(wxOutputStream& stream, const wxString& str)
{
    ::OutputString(stream, str, m_convMem, m_convFile);
}

void wxRichTextXMLHandler::OutputStringEnt(wxOutputStream& stream, const wxString& str)
{
    ::OutputStringEnt(stream, str, m_convMem, m_convFile);
}

void wxRichTextXMLHandler::OutputIndentation(wxOutputStream& stream, int indent)
{
    wxString str = wxT("\n");
    for (int i = 0; i < indent; i++)
        str << wxT(' ') << wxT(' ');
    ::OutputString(stream, str, NULL, NULL);
}

wxString wxRichTextXMLHandler::AttributeToXML(const wxString& str)
{
    wxString str1;
    size_t i, last, len;
    wxChar c;

    len = str.Len();
    last = 0;
    for (i = 0; i < len; i++)
    {
        c = str.GetChar(i);

        // Original code excluded "&amp;" but we _do_ want to convert
        // the ampersand beginning &amp; because otherwise when read in,
        // the original "&amp;" becomes "&".

        if (c == wxT('<') || c == wxT('>') || c == wxT('"') ||
            (c == wxT('&') /* && (str.Mid(i+1, 4) != wxT("amp;")) */ ))
        {
            str1 += str.Mid(last, i - last);
            switch (c)
            {
            case wxT('<'):
                str1 += wxT("&lt;");
                break;
            case wxT('>'):
                str1 += wxT("&gt;");
                break;
            case wxT('&'):
                str1 += wxT("&amp;");
                break;
            case wxT('"'):
                str1 += wxT("&quot;");
                break;
            default: break;
            }
            last = i + 1;
        }
        else if (wxUChar(c) > 127)
        {
            str1 += str.Mid(last, i - last);

            wxString s(wxT("&#"));
#if wxUSE_UNICODE
            s << (int) c;
#else
            s << (int) wxUChar(c);
#endif
            s << wxT(";");
            str1 += s;
            last = i + 1;
        }
    }
    str1 += str.Mid(last, i - last);
    return str1;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT

static inline void AddAttribute(wxString& str, const wxString& name, const int& v)
{
    str << wxT(" ") << name << wxT("=\"") << wxString::Format(wxT("%d"), v) << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const long& v)
{
    str << wxT(" ") << name << wxT("=\"") << wxString::Format(wxT("%ld"), v) << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const double& v)
{
    str << wxT(" ") << name << wxT("=\"") << wxString::Format(wxT("%.2f"), (float) v) << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const wxChar* s)
{
    str << wxT(" ") << name << wxT("=\"") << s << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const wxString& s)
{
    str << wxT(" ") << name << wxT("=\"") << s << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const wxColour& col)
{
    str << wxT(" ") << name << wxT("=\"") << wxT("#") << ColourToHexString(col) << wxT("\"");
}

static inline void AddAttribute(wxString& str, const wxString& name, const wxTextAttrDimension& dim)
{
    if (dim.IsValid())
    {
        wxString value = MakeString(dim.GetValue()) + wxT(",") + MakeString((int) dim.GetFlags());
        str << wxT(" ") << name << wxT("=\"");
        str << value;
        str << wxT("\"");
    }
}

static inline void AddAttribute(wxString& str, const wxString& rootName, const wxTextAttrDimensions& dims)
{
    if (dims.GetLeft().IsValid())
        AddAttribute(str, rootName + wxString(wxT("-left")), dims.GetLeft());
    if (dims.GetRight().IsValid())
        AddAttribute(str, rootName + wxString(wxT("-right")), dims.GetRight());
    if (dims.GetTop().IsValid())
        AddAttribute(str, rootName + wxString(wxT("-top")), dims.GetTop());
    if (dims.GetBottom().IsValid())
        AddAttribute(str, rootName + wxString(wxT("-bottom")), dims.GetBottom());
}

static inline void AddAttribute(wxString& str, const wxString& rootName, const wxTextAttrBorder& border)
{
    if (border.HasStyle())
        AddAttribute(str, rootName + wxString(wxT("-style")), border.GetStyle());
    if (border.HasColour())
        AddAttribute(str, rootName + wxString(wxT("-color")), border.GetColour());
    if (border.HasWidth())
        AddAttribute(str, rootName + wxString(wxT("-width")), border.GetWidth());
}

static inline void AddAttribute(wxString& str, const wxString& rootName, const wxTextAttrBorders& borders)
{
    AddAttribute(str, rootName + wxString(wxT("-left")), borders.GetLeft());
    AddAttribute(str, rootName + wxString(wxT("-right")), borders.GetRight());
    AddAttribute(str, rootName + wxString(wxT("-top")), borders.GetTop());
    AddAttribute(str, rootName + wxString(wxT("-bottom")), borders.GetBottom());
}

#endif
    // wxRICHTEXT_HAVE_DIRECT_OUTPUT

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const int& v)
{
    node->AddAttribute(name, MakeString(v));
}

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const long& v)
{
    node->AddAttribute(name, MakeString(v));
}

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const double& v)
{
    node->AddAttribute(name, MakeString(v));
}

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const wxString& s)
{
    node->AddAttribute(name, s);
}

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const wxColour& col)
{
    node->AddAttribute(name, MakeString(col));
}

static inline void AddAttribute(wxXmlNode* node, const wxString& name, const wxTextAttrDimension& dim)
{
    if (dim.IsValid())
    {
        wxString value = MakeString(dim.GetValue()) + wxT(",") + MakeString(dim.GetFlags());
        AddAttribute(node, name, value);
    }
}

static inline void AddAttribute(wxXmlNode* node, const wxString& rootName, const wxTextAttrDimensions& dims)
{
    if (dims.GetLeft().IsValid())
        AddAttribute(node, rootName + wxString(wxT("-left")), dims.GetLeft());
    if (dims.GetRight().IsValid())
        AddAttribute(node, rootName + wxString(wxT("-right")), dims.GetRight());
    if (dims.GetTop().IsValid())
        AddAttribute(node, rootName + wxString(wxT("-top")), dims.GetTop());
    if (dims.GetBottom().IsValid())
        AddAttribute(node, rootName + wxString(wxT("-bottom")), dims.GetBottom());
}

static inline void AddAttribute(wxXmlNode* node, const wxString& rootName, const wxTextAttrBorder& border)
{
    if (border.HasStyle())
        AddAttribute(node, rootName + wxString(wxT("-style")), border.GetStyle());
    if (border.HasColour())
        AddAttribute(node, rootName + wxString(wxT("-color")), border.GetColour());
    if (border.HasWidth())
        AddAttribute(node, rootName + wxString(wxT("-width")), border.GetWidth());
}

static inline void AddAttribute(wxXmlNode* node, const wxString& rootName, const wxTextAttrBorders& borders)
{
    AddAttribute(node, rootName + wxString(wxT("-left")), borders.GetLeft());
    AddAttribute(node, rootName + wxString(wxT("-right")), borders.GetRight());
    AddAttribute(node, rootName + wxString(wxT("-top")), borders.GetTop());
    AddAttribute(node, rootName + wxString(wxT("-bottom")), borders.GetBottom());
}
#endif
    // wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT

bool wxRichTextXMLHandler::DoSaveFile(wxRichTextBuffer *buffer, wxOutputStream& stream)
{
    if (!stream.IsOk())
        return false;

    wxString version(wxT("1.0") ) ;
    
    bool deleteConvFile = false;
    wxString fileEncoding;
    //wxMBConv* convFile = NULL;

#if wxUSE_UNICODE
    fileEncoding = wxT("UTF-8");
    m_convFile = & wxConvUTF8;
#else
    fileEncoding = wxT("ISO-8859-1");
    m_convFile = & wxConvISO8859_1;
#endif

    // If SetEncoding has been called, change the output encoding.
    if (!m_encoding.empty() && m_encoding.Lower() != fileEncoding.Lower())
    {
        if (m_encoding == wxT("<System>"))
        {
#if wxUSE_INTL
            fileEncoding = wxLocale::GetSystemEncodingName();
            // if !wxUSE_INTL, we fall back to UTF-8 or ISO-8859-1 below
#endif
        }
        else
        {
            fileEncoding = m_encoding;
        }

        // GetSystemEncodingName may not have returned a name
        if (fileEncoding.empty())
#if wxUSE_UNICODE
            fileEncoding = wxT("UTF-8");
#else
            fileEncoding = wxT("ISO-8859-1");
#endif
        m_convFile = new wxCSConv(fileEncoding);
        deleteConvFile = true;
    }

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT && wxRICHTEXT_USE_XMLDOCUMENT_OUTPUT
#if wxRICHTEXT_USE_OUTPUT_TIMINGS
    wxStopWatch stopwatch;
#endif
    wxXmlDocument* doc = new wxXmlDocument;
    doc->SetFileEncoding(fileEncoding);
    
    wxXmlNode* rootNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("richtext"));
    doc->SetRoot(rootNode);
    rootNode->AddAttribute(wxT("version"), wxT("1.0.0.0"));
    rootNode->AddAttribute(wxT("xmlns"), wxT("http://www.wxwidgets.org"));

    if (buffer->GetStyleSheet() && (GetFlags() & wxRICHTEXT_HANDLER_INCLUDE_STYLESHEET))
    {
        wxXmlNode* styleSheetNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("stylesheet"));
        rootNode->AddChild(styleSheetNode);
        
        wxString nameAndDescr;
        
        if (!buffer->GetStyleSheet()->GetName().empty())
            styleSheetNode->AddAttribute(wxT("name"), buffer->GetStyleSheet()->GetName());
            
        if (!buffer->GetStyleSheet()->GetDescription().empty())
            styleSheetNode->AddAttribute(wxT("description"), buffer->GetStyleSheet()->GetDescription());

        int i;
        for (i = 0; i < (int) buffer->GetStyleSheet()->GetCharacterStyleCount(); i++)
        {
            wxRichTextCharacterStyleDefinition* def = buffer->GetStyleSheet()->GetCharacterStyle(i);
            ExportStyleDefinition(styleSheetNode, def);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetParagraphStyleCount(); i++)
        {
            wxRichTextParagraphStyleDefinition* def = buffer->GetStyleSheet()->GetParagraphStyle(i);
            ExportStyleDefinition(styleSheetNode, def);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetListStyleCount(); i++)
        {
            wxRichTextListStyleDefinition* def = buffer->GetStyleSheet()->GetListStyle(i);
            ExportStyleDefinition(styleSheetNode, def);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetBoxStyleCount(); i++)
        {
            wxRichTextBoxStyleDefinition* def = buffer->GetStyleSheet()->GetBoxStyle(i);
            ExportStyleDefinition(styleSheetNode, def);
        }
    }
    bool success = ExportXML(rootNode, *buffer);
#if wxRICHTEXT_USE_OUTPUT_TIMINGS
    long t = stopwatch.Time();
    wxLogDebug(wxT("Creating the document took %ldms"), t);
    wxMessageBox(wxString::Format(wxT("Creating the document took %ldms"), t));
#endif
    if (success)
    {
#if wxRICHTEXT_USE_OUTPUT_TIMINGS
        wxStopWatch s2;
#endif
        success = doc->Save(stream);
#if wxRICHTEXT_USE_OUTPUT_TIMINGS
        long t2 = s2.Time();
        wxLogDebug(wxT("Save() took %ldms"), t2);
        wxMessageBox(wxString::Format(wxT("Save() took %ldms"), t2));
#endif
    }
    delete doc;
    doc = NULL;

#else
    // !(wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT && wxRICHTEXT_USE_XMLDOCUMENT_OUTPUT)

#if !wxUSE_UNICODE
    m_convMem = wxConvCurrent;
#else
    m_convMem = NULL;
#endif

    wxString s ;
    s.Printf(wxT("<?xml version=\"%s\" encoding=\"%s\"?>\n"),
             version, fileEncoding);
    OutputString(stream, s);
    OutputString(stream, wxT("<richtext version=\"1.0.0.0\" xmlns=\"http://www.wxwidgets.org\">"));

    int level = 1;

    if (buffer->GetStyleSheet() && (GetFlags() & wxRICHTEXT_HANDLER_INCLUDE_STYLESHEET))
    {
        OutputIndentation(stream, level);
        wxString nameAndDescr;
        if (!buffer->GetStyleSheet()->GetName().empty())
            nameAndDescr << wxT(" name=\"") << buffer->GetStyleSheet()->GetName() << wxT("\"");
        if (!buffer->GetStyleSheet()->GetDescription().empty())
            nameAndDescr << wxT(" description=\"") << buffer->GetStyleSheet()->GetDescription() << wxT("\"");
        OutputString(stream, wxString(wxT("<stylesheet")) + nameAndDescr + wxT(">"));

        int i;

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetCharacterStyleCount(); i++)
        {
            wxRichTextCharacterStyleDefinition* def = buffer->GetStyleSheet()->GetCharacterStyle(i);
            ExportStyleDefinition(stream, def, level + 1);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetParagraphStyleCount(); i++)
        {
            wxRichTextParagraphStyleDefinition* def = buffer->GetStyleSheet()->GetParagraphStyle(i);
            ExportStyleDefinition(stream, def, level + 1);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetListStyleCount(); i++)
        {
            wxRichTextListStyleDefinition* def = buffer->GetStyleSheet()->GetListStyle(i);
            ExportStyleDefinition(stream, def, level + 1);
        }

        for (i = 0; i < (int) buffer->GetStyleSheet()->GetBoxStyleCount(); i++)
        {
            wxRichTextBoxStyleDefinition* def = buffer->GetStyleSheet()->GetBoxStyle(i);
            ExportStyleDefinition(stream, def, level + 1);
        }

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</stylesheet>"));
    }


    bool success = ExportXML(stream, *buffer, level);

    OutputString(stream, wxT("\n</richtext>"));
    OutputString(stream, wxT("\n"));

    if (deleteConvFile)
        delete m_convFile;
    m_convFile = NULL;
    m_convMem = NULL;
#endif

    return success;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT

/// Recursively export an object
bool wxRichTextXMLHandler::ExportXML(wxOutputStream& stream, wxRichTextObject& obj, int indent)
{
    obj.ExportXML(stream, indent, this);

    return true;
}

bool wxRichTextXMLHandler::ExportStyleDefinition(wxOutputStream& stream, wxRichTextStyleDefinition* def, int level)
{
    wxRichTextCharacterStyleDefinition* charDef = wxDynamicCast(def, wxRichTextCharacterStyleDefinition);
    wxRichTextParagraphStyleDefinition* paraDef = wxDynamicCast(def, wxRichTextParagraphStyleDefinition);
    wxRichTextListStyleDefinition* listDef = wxDynamicCast(def, wxRichTextListStyleDefinition);
    wxRichTextBoxStyleDefinition* boxDef = wxDynamicCast(def, wxRichTextBoxStyleDefinition);

    wxString baseStyle = def->GetBaseStyle();
    wxString baseStyleProp;
    if (!baseStyle.empty())
        baseStyleProp = wxT(" basestyle=\"") + baseStyle + wxT("\"");

    wxString descr = def->GetDescription();
    wxString descrProp;
    if (!descr.empty())
        descrProp = wxT(" description=\"") + descr + wxT("\"");

    if (charDef)
    {
        OutputIndentation(stream, level);
        OutputString(stream, wxT("<characterstyle") + baseStyleProp + descrProp + wxT(">"));

        level ++;

        wxString style = AddAttributes(def->GetStyle(), false);

        OutputIndentation(stream, level);
        OutputString(stream, wxT("<style ") + style + wxT(">"));

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</style>"));

        level --;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</characterstyle>"));
    }
    else if (listDef)
    {
        OutputIndentation(stream, level);

        if (!listDef->GetNextStyle().empty())
            baseStyleProp << wxT(" nextstyle=\"") << listDef->GetNextStyle() << wxT("\"");

        OutputString(stream, wxT("<liststyle") + baseStyleProp + descrProp + wxT(">"));

        level ++;

        wxString style = AddAttributes(def->GetStyle(), true);

        OutputIndentation(stream, level);
        OutputString(stream, wxT("<style ") + style + wxT(">"));

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</style>"));

        int i;
        for (i = 0; i < 10; i ++)
        {
            wxRichTextAttr* levelAttr = listDef->GetLevelAttributes(i);
            if (levelAttr)
            {
                wxString style = AddAttributes(def->GetStyle(), true);
                wxString levelStr = wxString::Format(wxT(" level=\"%d\" "), (i+1));

                OutputIndentation(stream, level);
                OutputString(stream, wxT("<style ") + levelStr + style + wxT(">"));

                OutputIndentation(stream, level);
                OutputString(stream, wxT("</style>"));
            }
        }

        level --;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</liststyle>"));
    }
    else if (paraDef)
    {
        OutputIndentation(stream, level);

        if (!paraDef->GetNextStyle().empty())
            baseStyleProp << wxT(" nextstyle=\"") << paraDef->GetNextStyle() << wxT("\"");

        OutputString(stream, wxT("<paragraphstyle") + baseStyleProp + descrProp + wxT(">"));

        level ++;

        wxString style = AddAttributes(def->GetStyle(), true);

        OutputIndentation(stream, level);
        OutputString(stream, wxT("<style ") + style + wxT(">"));

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</style>"));

        level --;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</paragraphstyle>"));
    }
    else if (boxDef)
    {
        OutputIndentation(stream, level);

        OutputString(stream, wxT("<boxstyle") + baseStyleProp + descrProp + wxT(">"));

        level ++;

        wxString style = AddAttributes(def->GetStyle(), true);

        OutputIndentation(stream, level);
        OutputString(stream, wxT("<style ") + style + wxT(">"));

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</style>"));

        level --;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</boxstyle>"));
    }


    return true;
}

/// Create a string containing style attributes
wxString wxRichTextXMLHandler::AddAttributes(const wxRichTextAttr& attr, bool isPara)
{
    wxString str;
    if (attr.HasTextColour() && attr.GetTextColour().Ok())
        AddAttribute(str, wxT("textcolor"), attr.GetTextColour());

    if (attr.HasBackgroundColour() && attr.GetBackgroundColour().Ok())
        AddAttribute(str, wxT("bgcolor"), attr.GetBackgroundColour());

    if (attr.HasFontSize())
        AddAttribute(str, wxT("fontsize"), attr.GetFontSize());

    if (attr.HasFontFamily())
        AddAttribute(str, wxT("fontfamily"), attr.GetFontFamily());

    if (attr.HasFontItalic())
        AddAttribute(str, wxT("fontstyle"), attr.GetFontStyle());

    if (attr.HasFontWeight())
        AddAttribute(str, wxT("fontweight"), attr.GetFontWeight());

    if (attr.HasFontUnderlined())
        AddAttribute(str, wxT("fontunderlined"), (int) attr.GetFontUnderlined());

    if (attr.HasFontFaceName())
        AddAttribute(str, wxT("fontface"), attr.GetFontFaceName());

    if (attr.HasTextEffects())
    {
        AddAttribute(str, wxT("texteffects"), attr.GetTextEffects());
        AddAttribute(str, wxT("texteffectflags"), attr.GetTextEffectFlags());
    }

    if (!attr.GetCharacterStyleName().empty())
        AddAttribute(str, wxT("characterstyle"), attr.GetCharacterStyleName());

    if (attr.HasURL())
        AddAttribute(str, wxT("url"), AttributeToXML(attr.GetURL()));

    if (isPara)
    {
        if (attr.HasAlignment())
            AddAttribute(str, wxT("alignment"), (int) attr.GetAlignment());

        if (attr.HasLeftIndent())
        {
            AddAttribute(str, wxT("leftindent"), (int) attr.GetLeftIndent());
            AddAttribute(str, wxT("leftsubindent"), (int) attr.GetLeftSubIndent());
        }

        if (attr.HasRightIndent())
            AddAttribute(str, wxT("rightindent"), (int) attr.GetRightIndent());

        if (attr.HasParagraphSpacingAfter())
            AddAttribute(str, wxT("parspacingafter"), (int) attr.GetParagraphSpacingAfter());

        if (attr.HasParagraphSpacingBefore())
            AddAttribute(str, wxT("parspacingbefore"), (int) attr.GetParagraphSpacingBefore());

        if (attr.HasLineSpacing())
            AddAttribute(str, wxT("linespacing"), (int) attr.GetLineSpacing());

        if (attr.HasBulletStyle())
            AddAttribute(str, wxT("bulletstyle"), (int) attr.GetBulletStyle());

        if (attr.HasBulletNumber())
            AddAttribute(str, wxT("bulletnumber"), (int) attr.GetBulletNumber());

        if (attr.HasBulletText())
        {
            // If using a bullet symbol, convert to integer in case it's a non-XML-friendly character.
            // Otherwise, assume it's XML-friendly text such as outline numbering, e.g. 1.2.3.1
            if (!attr.GetBulletText().empty() && (attr.GetBulletStyle() & wxTEXT_ATTR_BULLET_STYLE_SYMBOL))
                AddAttribute(str, wxT("bulletsymbol"), (int) (attr.GetBulletText()[0]));
            else
                AddAttribute(str, wxT("bullettext"), attr.GetBulletText());

            AddAttribute(str, wxT("bulletfont"), attr.GetBulletFont());
        }

        if (attr.HasBulletName())
            AddAttribute(str, wxT("bulletname"), attr.GetBulletName());

        if (!attr.GetParagraphStyleName().empty())
            AddAttribute(str, wxT("parstyle"), attr.GetParagraphStyleName());

        if (!attr.GetListStyleName().empty())
            AddAttribute(str, wxT("liststyle"), attr.GetListStyleName());

        if (attr.HasTabs())
        {
            wxString strTabs;
            size_t i;
            for (i = 0; i < attr.GetTabs().GetCount(); i++)
            {
                if (i > 0) strTabs << wxT(",");
                strTabs << attr.GetTabs()[i];
            }
            AddAttribute(str, wxT("tabs"), strTabs);
        }

        if (attr.HasPageBreak())
        {
            AddAttribute(str, wxT("pagebreak"), 1);
        }

        if (attr.HasOutlineLevel())
            AddAttribute(str, wxT("outlinelevel"), (int) attr.GetOutlineLevel());
    }
    
    AddAttribute(str, wxT("margin"), attr.GetTextBoxAttr().GetMargins());
    AddAttribute(str, wxT("padding"), attr.GetTextBoxAttr().GetPadding());
    AddAttribute(str, wxT("position"), attr.GetTextBoxAttr().GetPosition());
    AddAttribute(str, wxT("border"), attr.GetTextBoxAttr().GetBorder());
    AddAttribute(str, wxT("outline"), attr.GetTextBoxAttr().GetOutline());
    AddAttribute(str, wxT("width"), attr.GetTextBoxAttr().GetWidth());
    AddAttribute(str, wxT("height"), attr.GetTextBoxAttr().GetWidth());
    
    if (attr.GetTextBoxAttr().HasFloatMode())
    {
        wxString value;
        if (attr.GetTextBoxAttr().GetFloatMode() == wxTEXT_BOX_ATTR_FLOAT_LEFT)
            value = wxT("left");
        else if (attr.GetTextBoxAttr().GetFloatMode() == wxTEXT_BOX_ATTR_FLOAT_RIGHT)
            value = wxT("right");
        else
            value = wxT("none");
        AddAttribute(str, wxT("float"), value);
    }

    if (attr.GetTextBoxAttr().HasClearMode())
    {
        wxString value;
        if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_LEFT)
            value = wxT("left");
        else if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_RIGHT)
            value = wxT("right");
        else if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_BOTH)
            value = wxT("both");
        else
            value = wxT("none");
        AddAttribute(str, wxT("clear"), value);
    }

    if (attr.GetTextBoxAttr().HasCollapseBorders())
        AddAttribute(str, wxT("collapse-borders"), (int) attr.GetTextBoxAttr().GetCollapseBorders());

    return str;
}

// Make a string from the given property. This can be overridden for custom variants.
wxString wxRichTextXMLHandler::MakeStringFromProperty(const wxVariant& var)
{
    return var.MakeString();
}

// Create a proprty from the string read from the XML file.
wxVariant wxRichTextXMLHandler::MakePropertyFromString(const wxString& name, const wxString& value, const wxString& WXUNUSED(type))
{
    wxVariant var(value, name);
    // TODO: use type to create using common types
    return var;
}

// Write the properties
bool wxRichTextXMLHandler::WriteProperties(wxOutputStream& stream, const wxRichTextProperties& properties, int level)
{
    if (properties.GetCount() > 0)
    {
        level ++;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("<properties"));

        level ++;

        size_t i;
        for (i = 0; i < properties.GetCount(); i++)
        {
            const wxVariant& var = properties[i];
            if (!var.IsNull())
            {            
                const wxString& name = var.GetName();
                wxString value = MakeStringFromProperty(var);

                OutputIndentation(stream, level);
                OutputString(stream, wxT("<property name=\"") + name +
                    wxT("\" type=\"") + var.GetType() + wxT("\" value=\""));
                OutputStringEnt(stream, value);
                OutputString(stream, wxT("\"/>\n"));
            }
        }

        level --;

        OutputIndentation(stream, level);
        OutputString(stream, wxT("</properties>\n"));

        level --;
    }

    return true;
}


#endif
    // wxRICHTEXT_HAVE_DIRECT_OUTPUT

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
bool wxRichTextXMLHandler::ExportXML(wxXmlNode* parent, wxRichTextObject& obj)
{
    obj.ExportXML(parent, this);

    return true;
}

bool wxRichTextXMLHandler::ExportStyleDefinition(wxXmlNode* parent, wxRichTextStyleDefinition* def)
{
    wxRichTextCharacterStyleDefinition* charDef = wxDynamicCast(def, wxRichTextCharacterStyleDefinition);
    wxRichTextParagraphStyleDefinition* paraDef = wxDynamicCast(def, wxRichTextParagraphStyleDefinition);
    wxRichTextBoxStyleDefinition* boxDef = wxDynamicCast(def, wxRichTextBoxStyleDefinition);
    wxRichTextListStyleDefinition* listDef = wxDynamicCast(def, wxRichTextListStyleDefinition);

    wxString baseStyle = def->GetBaseStyle();
    wxString descr = def->GetDescription();
    
    wxXmlNode* defNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxEmptyString);
    parent->AddChild(defNode);
    if (!baseStyle.empty())
        defNode->AddAttribute(wxT("basestyle"), baseStyle);
    if (!descr.empty())
        defNode->AddAttribute(wxT("description"), descr);
        
    wxXmlNode* styleNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("style"));
    defNode->AddChild(styleNode);
        
    if (charDef)
    {
        defNode->SetName(wxT("characterstyle"));
        AddAttributes(styleNode, def->GetStyle(), false);
    }
    else if (listDef)
    {
        defNode->SetName(wxT("liststyle"));

        if (!listDef->GetNextStyle().empty())
            defNode->AddAttribute(wxT("nextstyle"), listDef->GetNextStyle());

        AddAttributes(styleNode, def->GetStyle(), true);

        int i;
        for (i = 0; i < 10; i ++)
        {
            wxRichTextAttr* levelAttr = listDef->GetLevelAttributes(i);
            if (levelAttr)
            {
                wxXmlNode* levelNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("style"));
                defNode->AddChild(levelNode);
                levelNode->AddAttribute(wxT("level"), MakeString(i+1));
                AddAttributes(levelNode, * levelAttr, true);
            }
        }
    }
    else if (boxDef)
    {
        defNode->SetName(wxT("boxstyle"));

        AddAttributes(styleNode, def->GetStyle(), true);
    }
    else if (paraDef)
    {
        defNode->SetName(wxT("paragraphstyle"));

        if (!paraDef->GetNextStyle().empty())
            defNode->AddAttribute(wxT("nextstyle"), paraDef->GetNextStyle());

        AddAttributes(styleNode, def->GetStyle(), true);
    }

    return true;
}

bool wxRichTextXMLHandler::AddAttributes(wxXmlNode* node, wxRichTextAttr& attr, bool isPara)
{
    if (attr.HasTextColour() && attr.GetTextColour().Ok())
        node->AddAttribute(wxT("textcolor"), MakeString(attr.GetTextColour()));
    if (attr.HasBackgroundColour() && attr.GetBackgroundColour().Ok())
        node->AddAttribute(wxT("bgcolor"), MakeString(attr.GetBackgroundColour()));

    if (attr.HasFontSize())
        node->AddAttribute(wxT("fontsize"), MakeString(attr.GetFontSize()));
    if (attr.HasFontFamily())
        node->AddAttribute(wxT("fontfamily"), MakeString(attr.GetFontFamily()));
    if (attr.HasFontItalic())
        node->AddAttribute(wxT("fontstyle"), MakeString(attr.GetFontStyle()));
    if (attr.HasFontWeight())
        node->AddAttribute(wxT("fontweight"), MakeString(attr.GetFontWeight()));
    if (attr.HasFontUnderlined())
        node->AddAttribute(wxT("fontunderlined"), MakeString((int) attr.GetFontUnderlined()));
    if (attr.HasFontFaceName())
        node->AddAttribute(wxT("fontface"), attr.GetFontFaceName());

    if (attr.HasTextEffects())
    {
        node->AddAttribute(wxT("texteffects"), MakeString(attr.GetTextEffects()));
        node->AddAttribute(wxT("texteffectflags"), MakeString(attr.GetTextEffectFlags()));
    }
    if (attr.HasCharacterStyleName() && !attr.GetCharacterStyleName().empty())
        node->AddAttribute(wxT("characterstyle"), attr.GetCharacterStyleName());

    if (attr.HasURL())
        node->AddAttribute(wxT("url"), attr.GetURL()); // TODO: do we need to wrap this in AttributeToXML?

    if (isPara)
    {
        if (attr.HasAlignment())
            node->AddAttribute(wxT("alignment"), MakeString((int) attr.GetAlignment()));

        if (attr.HasLeftIndent())
        {
            node->AddAttribute(wxT("leftindent"), MakeString((int) attr.GetLeftIndent()));
            node->AddAttribute(wxT("leftsubindent"), MakeString((int) attr.GetLeftSubIndent()));
        }

        if (attr.HasRightIndent())
            node->AddAttribute(wxT("rightindent"), MakeString((int) attr.GetRightIndent()));

        if (attr.HasParagraphSpacingAfter())
            node->AddAttribute(wxT("parspacingafter"), MakeString((int) attr.GetParagraphSpacingAfter()));

        if (attr.HasParagraphSpacingBefore())
            node->AddAttribute(wxT("parspacingbefore"), MakeString((int) attr.GetParagraphSpacingBefore()));

        if (attr.HasLineSpacing())
            node->AddAttribute(wxT("linespacing"), MakeString((int) attr.GetLineSpacing()));

        if (attr.HasBulletStyle())
            node->AddAttribute(wxT("bulletstyle"), MakeString((int) attr.GetBulletStyle()));

        if (attr.HasBulletNumber())
            node->AddAttribute(wxT("bulletnumber"), MakeString((int) attr.GetBulletNumber()));

        if (attr.HasBulletText())
        {
            // If using a bullet symbol, convert to integer in case it's a non-XML-friendly character.
            // Otherwise, assume it's XML-friendly text such as outline numbering, e.g. 1.2.3.1
            if (!attr.GetBulletText().empty() && (attr.GetBulletStyle() & wxTEXT_ATTR_BULLET_STYLE_SYMBOL))
                node->AddAttribute(wxT("bulletsymbol"), MakeString((int) (attr.GetBulletText()[0])));
            else
                node->AddAttribute(wxT("bullettext"), attr.GetBulletText());

            if (!attr.GetBulletFont().empty())
                node->AddAttribute(wxT("bulletfont"), attr.GetBulletFont());
        }

        if (attr.HasBulletName())
            node->AddAttribute(wxT("bulletname"), attr.GetBulletName());

        if (!attr.GetParagraphStyleName().empty())
            node->AddAttribute(wxT("parstyle"), attr.GetParagraphStyleName());

        if (!attr.GetListStyleName().empty())
            node->AddAttribute(wxT("liststyle"), attr.GetListStyleName());

        if (attr.HasTabs())
        {
            wxString tabs;
            size_t i;
            for (i = 0; i < attr.GetTabs().GetCount(); i++)
            {
                if (i > 0)
                    tabs << wxT(",");
                tabs << attr.GetTabs()[i];
            }
            node->AddAttribute(wxT("tabs"), tabs);
        }

        if (attr.HasPageBreak())
            node->AddAttribute(wxT("pagebreak"), wxT("1"));

        if (attr.HasOutlineLevel())
            node->AddAttribute(wxT("outlinelevel"), MakeString((int) attr.GetOutlineLevel()));
    }

    AddAttribute(node, wxT("margin"), attr.GetTextBoxAttr().GetMargins());
    AddAttribute(node, wxT("padding"), attr.GetTextBoxAttr().GetPadding());
    AddAttribute(node, wxT("position"), attr.GetTextBoxAttr().GetPosition());
    AddAttribute(node, wxT("border"), attr.GetTextBoxAttr().GetBorder());
    AddAttribute(node, wxT("outline"), attr.GetTextBoxAttr().GetOutline());
    AddAttribute(node, wxT("width"), attr.GetTextBoxAttr().GetWidth());
    AddAttribute(node, wxT("height"), attr.GetTextBoxAttr().GetWidth());

    if (attr.GetTextBoxAttr().HasFloatMode())
    {
        wxString value;
        if (attr.GetTextBoxAttr().GetFloatMode() == wxTEXT_BOX_ATTR_FLOAT_LEFT)
            value = wxT("left");
        else if (attr.GetTextBoxAttr().GetFloatMode() == wxTEXT_BOX_ATTR_FLOAT_RIGHT)
            value = wxT("right");
        else
            value = wxT("none");
        AddAttribute(node, wxT("float"), value);
    }

    if (attr.GetTextBoxAttr().HasClearMode())
    {
        wxString value;
        if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_LEFT)
            value = wxT("left");
        else if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_RIGHT)
            value = wxT("right");
        else if (attr.GetTextBoxAttr().GetClearMode() == wxTEXT_BOX_ATTR_CLEAR_BOTH)
            value = wxT("both");
        else
            value = wxT("none");
        AddAttribute(node, wxT("clear"), value);
    }

    if (attr.GetTextBoxAttr().HasCollapseBorders())
        AddAttribute(node, wxT("collapse-borders"), (int) attr.GetTextBoxAttr().GetCollapseBorders());

    return true;
}

bool wxRichTextXMLHandler::WriteProperties(wxXmlNode* node, const wxRichTextProperties& properties)
{
    if (properties.GetCount() > 0)
    {
        wxXmlNode* propertiesNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("properties"));
        node->AddChild(propertiesNode);
        size_t i;
        for (i = 0; i < properties.GetCount(); i++)
        {
            const wxVariant& var = properties[i];
            if (!var.IsNull())
            {
                wxXmlNode* propertyNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("property"));
                propertiesNode->AddChild(propertyNode);

                const wxString& name = var.GetName();
                wxString value = MakeStringFromProperty(var);

                AddAttribute(propertyNode, wxT("name"), name);
                AddAttribute(propertyNode, wxT("type"), var.GetType());
                AddAttribute(propertyNode, wxT("value"), value);
            }
        }
    }
    return true;
}

#endif
    // wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT

/// Replace face name with current name for platform.
/// TODO: introduce a virtual function or settable table to
/// do this comprehensively.
bool wxRichTextFixFaceName(wxString& facename)
{
    if (facename.empty())
        return false;

#ifdef __WXMSW__
    if (facename == wxT("Times"))
    {
        facename = wxT("Times New Roman");
        return true;
    }
    else if (facename == wxT("Helvetica"))
    {
        facename = wxT("Arial");
        return true;
    }
    else if (facename == wxT("Courier"))
    {
        facename = wxT("Courier New");
        return true;
    }
    else
        return false;
#else
    if (facename == wxT("Times New Roman"))
    {
        facename = wxT("Times");
        return true;
    }
    else if (facename == wxT("Arial"))
    {
        facename = wxT("Helvetica");
        return true;
    }
    else if (facename == wxT("Courier New"))
    {
        facename = wxT("Courier");
        return true;
    }
    else
        return false;
#endif
}

static inline long wxRichTextColourStringToLong(const wxString& colStr)
{
    if (!colStr.IsEmpty())
    {
        wxColour col(colStr);
        return col.GetRGB();
    }
    else
        return 0;
}

static inline wxTextAttrDimension wxRichTextParseDimension(const wxString& dimStr)
{
    wxString valuePart = dimStr.BeforeFirst(wxT(','));
    wxString flagsPart;
    if (dimStr.Contains(wxT(",")))
        flagsPart = dimStr.AfterFirst(wxT(','));
    wxTextAttrDimension dim;
    dim.SetValue(wxAtoi(valuePart));
    dim.SetFlags(wxAtoi(flagsPart));

    return dim;
}

/// Import style parameters
bool wxRichTextXMLHandler::ImportStyle(wxRichTextAttr& attr, wxXmlNode* node, bool isPara)
{
    wxXmlAttribute* xmlAttr = node->GetAttributes();
    bool found;
    while (xmlAttr)
    {
        const wxString& name = xmlAttr->GetName();
        const wxString& value = xmlAttr->GetValue();
        found = true;

        if (name == wxT("fontface"))
        {
            if (!value.empty())
            {
                wxString v = value;
                if (GetFlags() & wxRICHTEXT_HANDLER_CONVERT_FACENAMES)
                    wxRichTextFixFaceName(v);
                attr.SetFontFaceName(v);
            }
        }
        else if (name == wxT("fontfamily"))
        {
            if (!value.empty())
                attr.SetFontFamily((wxFontFamily)wxAtoi(value));
        }
        else if (name == wxT("fontstyle"))
        {
            if (!value.empty())
                attr.SetFontStyle((wxFontStyle)wxAtoi(value));
        }
        else if (name == wxT("fontsize"))
        {
            if (!value.empty())
                attr.SetFontSize(wxAtoi(value));
        }
        else if (name == wxT("fontweight"))
        {
            if (!value.empty())
                attr.SetFontWeight((wxFontWeight) wxAtoi(value));
        }
        else if (name == wxT("fontunderlined"))
        {
            if (!value.empty())
                attr.SetFontUnderlined(wxAtoi(value) != 0);
        }
        else if (name == wxT("textcolor"))
        {
            if (!value.empty())
            {
                if (value[0] == wxT('#'))
                    attr.SetTextColour(HexStringToColour(value.Mid(1)));
                else
                    attr.SetTextColour(value);
            }
        }
        else if (name == wxT("bgcolor"))
        {
            if (!value.empty())
            {
                if (value[0] == wxT('#'))
                    attr.SetBackgroundColour(HexStringToColour(value.Mid(1)));
                else
                    attr.SetBackgroundColour(value);
            }
        }
        else if (name == wxT("characterstyle"))
        {
            if (!value.empty())
                attr.SetCharacterStyleName(value);
        }
        else if (name == wxT("texteffects"))
        {
            if (!value.empty())
                attr.SetTextEffects(wxAtoi(value));
        }
        else if (name == wxT("texteffectflags"))
        {
            if (!value.empty())
                attr.SetTextEffectFlags(wxAtoi(value));
        }
        else if (name == wxT("url"))
        {
            if (!value.empty())
                attr.SetURL(value);
        }
        else if (isPara)
        {
            if (name == wxT("alignment"))
            {
                if (!value.empty())
                    attr.SetAlignment((wxTextAttrAlignment) wxAtoi(value));
            }
            else if (name == wxT("leftindent"))
            {
                if (!value.empty())
                    attr.SetLeftIndent(wxAtoi(value), attr.GetLeftSubIndent());
            }
            else if (name == wxT("leftsubindent"))
            {
                if (!value.empty())
                    attr.SetLeftIndent(attr.GetLeftIndent(), wxAtoi(value));
            }
            else if (name == wxT("rightindent"))
            {
                if (!value.empty())
                    attr.SetRightIndent(wxAtoi(value));
            }
            else if (name == wxT("parspacingbefore"))
            {
                if (!value.empty())
                    attr.SetParagraphSpacingBefore(wxAtoi(value));
            }
            else if (name == wxT("parspacingafter"))
            {
                if (!value.empty())
                    attr.SetParagraphSpacingAfter(wxAtoi(value));
            }
            else if (name == wxT("linespacing"))
            {
                if (!value.empty())
                    attr.SetLineSpacing(wxAtoi(value));
            }
            else if (name == wxT("bulletstyle"))
            {
                if (!value.empty())
                    attr.SetBulletStyle(wxAtoi(value));
            }
            else if (name == wxT("bulletnumber"))
            {
                if (!value.empty())
                    attr.SetBulletNumber(wxAtoi(value));
            }
            else if (name == wxT("bulletsymbol"))
            {
                if (!value.empty())
                {
                    wxChar ch = wxAtoi(value);
                    wxString s;
                    s << ch;
                    attr.SetBulletText(s);
                }
            }
            else if (name == wxT("bullettext"))
            {
                if (!value.empty())
                {
                    attr.SetBulletText(value);
                }
            }
            else if (name == wxT("bulletfont"))
            {
                if (!value.empty())
                {
                    attr.SetBulletFont(value);
                }
            }
            else if (name == wxT("bulletname"))
            {
                if (!value.empty())
                {
                    attr.SetBulletName(value);
                }
            }
            else if (name == wxT("parstyle"))
            {
                if (!value.empty())
                {
                    attr.SetParagraphStyleName(value);
                }
            }
            else if (name == wxT("liststyle"))
            {
                if (!value.empty())
                {
                    attr.SetListStyleName(value);
                }
            }
            else if (name == wxT("tabs"))
            {
                if (!value.empty())
                {
                    wxArrayInt tabs;
                    wxStringTokenizer tkz(value, wxT(","));
                    while (tkz.HasMoreTokens())
                    {
                        wxString token = tkz.GetNextToken();
                        tabs.Add(wxAtoi(token));
                    }
                    attr.SetTabs(tabs);
                }
            }
            else if (name == wxT("pagebreak"))
            {
                if (!value.empty())
                {
                    attr.SetPageBreak(wxAtoi(value) != 0);
                }
            }
            else if (name == wxT("outlinelevel"))
            {
                if (!value.empty())
                {
                    attr.SetOutlineLevel(wxAtoi(value));
                }
            }
            else
                found = false;
        }
        else
            found = false;

        if (!found)
        {
            // Box attributes

            if (name == wxT("width"))
            {
                attr.GetTextBoxAttr().GetWidth().SetValue(wxRichTextParseDimension(value));
            }
            else if (name == wxT("height"))
            {
                attr.GetTextBoxAttr().GetHeight().SetValue(wxRichTextParseDimension(value));
            }

            else if (name == wxT("float"))
            {
                if (value == wxT("left"))
                    attr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_LEFT);
                else if (value == wxT("right"))
                    attr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_RIGHT);
                else if (value == wxT("none"))
                    attr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_NONE);
            }
            else if (name == wxT("clear"))
            {
                if (value == wxT("left"))
                    attr.GetTextBoxAttr().SetClearMode(wxTEXT_BOX_ATTR_CLEAR_LEFT);
                else if (value == wxT("right"))
                    attr.GetTextBoxAttr().SetClearMode(wxTEXT_BOX_ATTR_CLEAR_RIGHT);
                else if (value == wxT("both"))
                    attr.GetTextBoxAttr().SetClearMode(wxTEXT_BOX_ATTR_CLEAR_BOTH);
                else if (value == wxT("none"))
                    attr.GetTextBoxAttr().SetClearMode(wxTEXT_BOX_ATTR_CLEAR_NONE);
            }
            else if (name == wxT("collapse-borders"))
                attr.GetTextBoxAttr().SetCollapseBorders((wxTextBoxAttrCollapseMode) wxAtoi(value));

            else if (name.Contains(wxT("border-")))
            {
                if (name == wxT("border-left-style"))
                    attr.GetTextBoxAttr().GetBorder().GetLeft().SetStyle(wxAtoi(value));
                else if (name == wxT("border-right-style"))
                    attr.GetTextBoxAttr().GetBorder().GetRight().SetStyle(wxAtoi(value));
                else if (name == wxT("border-top-style"))
                    attr.GetTextBoxAttr().GetBorder().GetTop().SetStyle(wxAtoi(value));
                else if (name == wxT("border-bottom-style"))
                    attr.GetTextBoxAttr().GetBorder().GetBottom().SetStyle(wxAtoi(value));

                else if (name == wxT("border-left-colour"))
                    attr.GetTextBoxAttr().GetBorder().GetLeft().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("border-right-colour"))
                    attr.GetTextBoxAttr().GetBorder().GetRight().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("border-top-colour"))
                    attr.GetTextBoxAttr().GetBorder().GetTop().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("border-bottom-colour"))
                    attr.GetTextBoxAttr().GetBorder().GetBottom().SetColour(wxRichTextColourStringToLong(value));

                else if (name == wxT("border-left-width"))
                    attr.GetTextBoxAttr().GetBorder().GetLeft().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("border-right-width"))
                    attr.GetTextBoxAttr().GetBorder().GetRight().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("border-top-width"))
                    attr.GetTextBoxAttr().GetBorder().GetTop().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("border-bottom-width"))
                    attr.GetTextBoxAttr().GetBorder().GetBottom().SetWidth(wxRichTextParseDimension(value));
            }
            else if (name.Contains(wxT("outline-")))
            {
                if (name == wxT("outline-left-style"))
                    attr.GetTextBoxAttr().GetOutline().GetLeft().SetStyle(wxAtoi(value));
                else if (name == wxT("outline-right-style"))
                    attr.GetTextBoxAttr().GetOutline().GetRight().SetStyle(wxAtoi(value));
                else if (name == wxT("outline-top-style"))
                    attr.GetTextBoxAttr().GetOutline().GetTop().SetStyle(wxAtoi(value));
                else if (name == wxT("outline-bottom-style"))
                    attr.GetTextBoxAttr().GetOutline().GetBottom().SetStyle(wxAtoi(value));

                else if (name == wxT("outline-left-colour"))
                    attr.GetTextBoxAttr().GetOutline().GetLeft().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("outline-right-colour"))
                    attr.GetTextBoxAttr().GetOutline().GetRight().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("outline-top-colour"))
                    attr.GetTextBoxAttr().GetOutline().GetTop().SetColour(wxRichTextColourStringToLong(value));
                else if (name == wxT("outline-bottom-colour"))
                    attr.GetTextBoxAttr().GetOutline().GetBottom().SetColour(wxRichTextColourStringToLong(value));

                else if (name == wxT("outline-left-width"))
                    attr.GetTextBoxAttr().GetOutline().GetLeft().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("outline-right-width"))
                    attr.GetTextBoxAttr().GetOutline().GetRight().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("outline-top-width"))
                    attr.GetTextBoxAttr().GetOutline().GetTop().SetWidth(wxRichTextParseDimension(value));
                else if (name == wxT("outline-bottom-width"))
                    attr.GetTextBoxAttr().GetOutline().GetBottom().SetWidth(wxRichTextParseDimension(value));
            }
            else if (name.Contains(wxT("margin-")))
            {
                if (name == wxT("margin-left"))
                    attr.GetTextBoxAttr().GetMargins().GetLeft().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("margin-right"))
                    attr.GetTextBoxAttr().GetMargins().GetRight().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("margin-top"))
                    attr.GetTextBoxAttr().GetMargins().GetTop().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("margin-bottom"))
                    attr.GetTextBoxAttr().GetMargins().GetBottom().SetValue(wxRichTextParseDimension(value));
            }
            else if (name.Contains(wxT("padding-")))
            {
                if (name == wxT("padding-left"))
                    attr.GetTextBoxAttr().GetPadding().GetLeft().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("padding-right"))
                    attr.GetTextBoxAttr().GetPadding().GetRight().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("padding-top"))
                    attr.GetTextBoxAttr().GetPadding().GetTop().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("padding-bottom"))
                    attr.GetTextBoxAttr().GetPadding().GetBottom().SetValue(wxRichTextParseDimension(value));
            }
            else if (name.Contains(wxT("position-")))
            {
                if (name == wxT("position-left"))
                    attr.GetTextBoxAttr().GetPosition().GetLeft().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("position-right"))
                    attr.GetTextBoxAttr().GetPosition().GetRight().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("position-top"))
                    attr.GetTextBoxAttr().GetPosition().GetTop().SetValue(wxRichTextParseDimension(value));
                else if (name == wxT("position-bottom"))
                    attr.GetTextBoxAttr().GetPosition().GetBottom().SetValue(wxRichTextParseDimension(value));
            }
        }
        
        xmlAttr = xmlAttr->GetNext();
    }

    return true;
}

#endif
    // wxUSE_STREAMS

// Import this object from XML
bool wxRichTextObject::ImportFromXML(wxRichTextBuffer* WXUNUSED(buffer), wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    handler->ImportProperties(this, node);
    handler->ImportStyle(GetAttributes(), node, UsesParagraphAttributes());
    
    *recurse = false;

    return true;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
// Export this object directly to the given stream.
bool wxRichTextObject::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("<") + GetXMLNodeName(), handler->GetConvMem(), handler->GetConvFile());

    wxString style = handler->AddAttributes(GetAttributes(), true);

    ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());

    if (GetProperties().GetCount() > 0)
    {
        handler->WriteProperties(stream, GetProperties(), indent);
    }
    
    wxRichTextCompositeObject* composite = wxDynamicCast(this, wxRichTextCompositeObject);
    if (composite)
    {
        size_t i;
        for (i = 0; i < composite->GetChildCount(); i++)
        {
            wxRichTextObject* child = composite->GetChild(i);
            child->ExportXML(stream, indent+1, handler);
        }
    }

    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("</") + GetXMLNodeName() + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
    return true;
}
#endif

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
// Export this object to the given parent node, usually creating at least one child node.
bool wxRichTextObject::ExportXML(wxXmlNode* parent, wxRichTextXMLHandler* handler)
{
    wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, GetXMLNodeName());
    parent->AddChild(elementNode);
    handler->AddAttributes(elementNode, GetAttributes(), true);
    handler->WriteProperties(elementNode, GetProperties());

    wxRichTextCompositeObject* composite = wxDynamicCast(this, wxRichTextCompositeObject);
    if (composite)
    {
        size_t i;
        for (i = 0; i < composite->GetChildCount(); i++)
        {
            wxRichTextObject* child = composite->GetChild(i);
            child->ExportXML(elementNode, handler);
        }
    }
    return true;
}
#endif


// Import this object from XML
bool wxRichTextPlainText::ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    wxRichTextObject::ImportFromXML(buffer, node, handler, recurse);
    
    if (node->GetName() == wxT("text"))
    {
        wxString text;
        wxXmlNode* textChild = node->GetChildren();
        while (textChild)
        {
            if (textChild->GetType() == wxXML_TEXT_NODE ||
                textChild->GetType() == wxXML_CDATA_SECTION_NODE)
            {
                wxString text2 = textChild->GetContent();

                // Strip whitespace from end
                if (!text2.empty() && text2[text2.length()-1] == wxT('\n'))
                    text2 = text2.Mid(0, text2.length()-1);

                if (!text2.empty() && text2[0] == wxT('"'))
                    text2 = text2.Mid(1);
                if (!text2.empty() && text2[text2.length()-1] == wxT('"'))
                    text2 = text2.Mid(0, text2.length() - 1);

                text += text2;
            }
            textChild = textChild->GetNext();
        }
        
        SetText(text);
    }
    else if (node->GetName() == wxT("symbol"))
    {
        // This is a symbol that XML can't read in the normal way
        wxString text;
        wxXmlNode* textChild = node->GetChildren();
        while (textChild)
        {
            if (textChild->GetType() == wxXML_TEXT_NODE ||
                textChild->GetType() == wxXML_CDATA_SECTION_NODE)
            {
                wxString text2 = textChild->GetContent();
                text += text2;
            }
            textChild = textChild->GetNext();
        }

        wxString actualText;
        actualText << (wxChar) wxAtoi(text);
        SetText(actualText);
    }
    else
        return false;

    return true;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
// Export this object directly to the given stream.
bool wxRichTextPlainText::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    wxString style = handler->AddAttributes(GetAttributes(), false);

    int i;
    int last = 0;
    const wxString& text = GetText();
    int len = (int) text.Length();

    if (len == 0)
    {
        i = 0;
        ::OutputIndentation(stream, indent);
        ::OutputString(stream, wxT("<text"), handler->GetConvMem(), handler->GetConvFile());
        ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
        if (GetProperties().GetCount() > 0)
        {
            handler->WriteProperties(stream, GetProperties(), indent);
            ::OutputIndentation(stream, indent);
        }
        ::OutputString(stream, wxT("</text>"), handler->GetConvMem(), handler->GetConvFile());
    }
    else for (i = 0; i < len; i++)
    {
#if wxUSE_UNICODE
        int c = (int) text[i];
#else
        int c = (int) wxUChar(text[i]);
#endif
        if ((c < 32 || c == 34) && /* c != 9 && */ c != 10 && c != 13)
        {
            if (i > 0)
            {
                wxString fragment(text.Mid(last, i-last));
                if (!fragment.empty())
                {
                    ::OutputIndentation(stream, indent);
                    ::OutputString(stream, wxT("<text"), handler->GetConvMem(), handler->GetConvFile());

                    ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());

                    if (!fragment.empty() && (fragment[0] == wxT(' ') || fragment[fragment.length()-1] == wxT(' ')))
                    {
                        ::OutputString(stream, wxT("\""), handler->GetConvMem(), handler->GetConvFile());
                        ::OutputStringEnt(stream, fragment, handler->GetConvMem(), handler->GetConvFile());
                        ::OutputString(stream, wxT("\""), handler->GetConvMem(), handler->GetConvFile());
                    }
                    else
                        ::OutputStringEnt(stream, fragment, handler->GetConvMem(), handler->GetConvFile());

                    if (GetProperties().GetCount() > 0)
                    {
                        handler->WriteProperties(stream, GetProperties(), indent);
                        ::OutputIndentation(stream, indent);
                    }
                    ::OutputString(stream, wxT("</text>"), handler->GetConvMem(), handler->GetConvFile());
                }
            }


            // Output this character as a number in a separate tag, because XML can't cope
            // with entities below 32 except for 10 and 13
            last = i + 1;
            ::OutputIndentation(stream, indent);
            ::OutputString(stream, wxT("<symbol"), handler->GetConvMem(), handler->GetConvFile());

            ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
            ::OutputString(stream, wxString::Format(wxT("%d"), c), handler->GetConvMem(), handler->GetConvFile());

            if (GetProperties().GetCount() > 0)
            {
                handler->WriteProperties(stream, GetProperties(), indent);
                ::OutputIndentation(stream, indent);
            }
            ::OutputString(stream, wxT("</symbol>"), handler->GetConvMem(), handler->GetConvFile());
        }
    }

    wxString fragment;
    if (last == 0)
        fragment = text;
    else
        fragment = text.Mid(last, i-last);

    if (last < len)
    {
        ::OutputIndentation(stream, indent);
        ::OutputString(stream, wxT("<text"), handler->GetConvMem(), handler->GetConvFile());

        ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
        
        if (GetProperties().GetCount() > 0)
        {
            handler->WriteProperties(stream, GetProperties(), indent);
            ::OutputIndentation(stream, indent);
        }

        if (!fragment.empty() && (fragment[0] == wxT(' ') || fragment[fragment.length()-1] == wxT(' ')))
        {
            ::OutputString(stream, wxT("\""), handler->GetConvMem(), handler->GetConvFile());
            ::OutputStringEnt(stream, fragment, handler->GetConvMem(), handler->GetConvFile());
            ::OutputString(stream, wxT("\""), handler->GetConvMem(), handler->GetConvFile());
        }
        else
            ::OutputStringEnt(stream, fragment, handler->GetConvMem(), handler->GetConvFile());

        ::OutputString(stream, wxT("</text>"), handler->GetConvMem(), handler->GetConvFile());
    }
    return true;
}
#endif

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
// Export this object to the given parent node, usually creating at least one child node.
bool wxRichTextPlainText::ExportXML(wxXmlNode* parent, wxRichTextXMLHandler* handler)
{
    int i;
    int last = 0;
    const wxString& text = GetText();
    int len = (int) text.Length();

    if (len == 0)
    {
        i = 0;

        wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("text"));
        parent->AddChild(elementNode);

        handler->AddAttributes(elementNode, GetAttributes(), false);
        handler->WriteProperties(elementNode, GetProperties());
    }
    else for (i = 0; i < len; i++)
    {
#if wxUSE_UNICODE
        int c = (int) text[i];
#else
        int c = (int) wxUChar(text[i]);
#endif
        if ((c < 32 || c == 34) && c != 10 && c != 13)
        {
            if (i > 0)
            {
                wxString fragment(text.Mid(last, i-last));
                if (!fragment.empty())
                {
                    // TODO: I'm assuming wxXmlDocument will output quotes if necessary
                    wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("text"));
                    parent->AddChild(elementNode);
                    handler->AddAttributes(elementNode, GetAttributes(), false);
                    handler->WriteProperties(elementNode, GetProperties());
                    
                    wxXmlNode* textNode = new wxXmlNode(wxXML_TEXT_NODE, wxT("text"));
                    elementNode->AddChild(textNode);

                    if (fragment[0] == wxT(' ') || fragment[fragment.length()-1] == wxT(' '))
                        fragment = wxT("\"") + fragment + wxT("\"");

                    textNode->SetContent(fragment);
                }
            }


            // Output this character as a number in a separate tag, because XML can't cope
            // with entities below 32 except for 10 and 13
            
            wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("symbol"));
            parent->AddChild(elementNode);

            handler->AddAttributes(elementNode, GetAttributes(), false);
            handler->WriteProperties(elementNode, GetProperties());

            wxXmlNode* textNode = new wxXmlNode(wxXML_TEXT_NODE, wxT("text"));
            elementNode->AddChild(textNode);
            textNode->SetContent(wxString::Format(wxT("%d"), c));

            last = i + 1;
        }
    }

    wxString fragment;
    if (last == 0)
        fragment = text;
    else
        fragment = text.Mid(last, i-last);

    if (last < len)
    {
        wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("text"));
        parent->AddChild(elementNode);
        handler->AddAttributes(elementNode, GetAttributes(), false);
                    
        wxXmlNode* textNode = new wxXmlNode(wxXML_TEXT_NODE, wxT("text"));
        elementNode->AddChild(textNode);

        if (fragment[0] == wxT(' ') || fragment[fragment.length()-1] == wxT(' '))
            fragment = wxT("\"") + fragment + wxT("\"");

        textNode->SetContent(fragment);            
    }
    return true;
}
#endif


// Import this object from XML
bool wxRichTextImage::ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    wxRichTextObject::ImportFromXML(buffer, node, handler, recurse);

    wxBitmapType imageType = wxBITMAP_TYPE_PNG;
    wxString value = node->GetAttribute(wxT("imagetype"), wxEmptyString);
    if (!value.empty())
    {
        int type = wxAtoi(value);

        // note: 0 == wxBITMAP_TYPE_INVALID
        if (type <= 0 || type >= wxBITMAP_TYPE_MAX)
        {
            wxLogWarning("Invalid bitmap type specified for <image> tag: %d", type);
        }
        else
        {
            imageType = (wxBitmapType)type;
        }
    }

    wxString data;

    wxXmlNode* imageChild = node->GetChildren();
    while (imageChild)
    {
        wxString childName = imageChild->GetName();
        if (childName == wxT("data"))
        {
            wxXmlNode* dataChild = imageChild->GetChildren();
            while (dataChild)
            {
                data = dataChild->GetContent();
                // wxLogDebug(data);
                dataChild = dataChild->GetNext();
            }

        }
        imageChild = imageChild->GetNext();
    }

    if (!data.empty())
    {
        wxStringInputStream strStream(data);

        GetImageBlock().ReadHex(strStream, data.length(), imageType);
        
        return true;
    }
    else
        return false;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
// Export this object directly to the given stream.
bool wxRichTextImage::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    wxString style = handler->AddAttributes(GetAttributes(), false);

    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("<image"), handler->GetConvMem(), handler->GetConvFile());
    if (!GetImageBlock().Ok())
    {
        // No data
        ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
    }
    else
    {
        ::OutputString(stream, wxString::Format(wxT(" imagetype=\"%d\""), (int) GetImageBlock().GetImageType()) + style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
    }
    if (GetProperties().GetCount() > 0)
    {
        handler->WriteProperties(stream, GetProperties(), indent);
        ::OutputIndentation(stream, indent);
    }

    ::OutputIndentation(stream, indent+1);
    ::OutputString(stream, wxT("<data>"), handler->GetConvMem(), handler->GetConvFile());

    // wxStopWatch stopwatch;

    GetImageBlock().WriteHex(stream);

    // wxLogDebug(wxT("Image conversion to hex took %ldms"), stopwatch.Time());

    ::OutputString(stream, wxT("</data>\n"), handler->GetConvMem(), handler->GetConvFile());
    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("</image>"), handler->GetConvMem(), handler->GetConvFile());
    return true;
}
#endif

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
// Export this object to the given parent node, usually creating at least one child node.
bool wxRichTextImage::ExportXML(wxXmlNode* parent, wxRichTextXMLHandler* handler)
{
    wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("image"));
    parent->AddChild(elementNode);

    if (GetImageBlock().Ok())
        elementNode->AddAttribute(wxT("imagetype"), MakeString((int) GetImageBlock().GetImageType()));

    handler->AddAttributes(elementNode, GetAttributes(), false);
    handler->WriteProperties(elementNode, GetProperties());

    wxXmlNode* dataNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("data"));
    elementNode->AddChild(dataNode);
    wxXmlNode* textNode = new wxXmlNode(wxXML_TEXT_NODE, wxT("text"));
    dataNode->AddChild(textNode);

    wxString strData;
#if 1        
    {
        wxMemoryOutputStream stream;
        if (GetImageBlock().WriteHex(stream))
        {
            if (stream.GetSize() > 0)
            {
                int size = stream.GetSize();
#ifdef __WXDEBUG__
                int size2 = stream.GetOutputStreamBuffer()->GetIntPosition();
                wxASSERT(size == size2);
#endif
                unsigned char* data = new unsigned char[size];
                stream.CopyTo(data, size);
                strData = wxString((const char*) data, wxConvUTF8, size);
                delete[] data;
            }
            else
                strData = wxEmptyString;
        }
    
    }
#else
    {
        wxStringOutputStream strStream(& strData);
        GetImageBlock().WriteHex(strStream);        
    }
#endif

    textNode->SetContent(strData);
    textNode->SetNoConversion(true); // optimize speed

    return true;
}
#endif


// Import this object from XML
bool wxRichTextParagraphLayoutBox::ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    wxRichTextObject::ImportFromXML(buffer, node, handler, recurse);
    
    *recurse = true;

    wxString partial = node->GetAttribute(wxT("partialparagraph"), wxEmptyString);
    if (partial == wxT("true"))
        SetPartialParagraph(true);

    wxXmlNode* child = wxRichTextXMLHandler::FindNode(node, wxT("stylesheet"));
    if (child && (handler->GetFlags() & wxRICHTEXT_HANDLER_INCLUDE_STYLESHEET))
    {
        wxRichTextStyleSheet* sheet = new wxRichTextStyleSheet;
        wxString sheetName = child->GetAttribute(wxT("name"), wxEmptyString);
        wxString sheetDescription = child->GetAttribute(wxT("description"), wxEmptyString);
        sheet->SetName(sheetName);
        sheet->SetDescription(sheetDescription);

        wxXmlNode* child2 = child->GetChildren();
        while (child2)
        {
            handler->ImportStyleDefinition(sheet, child2);

            child2 = child2->GetNext();
        }

        // Notify that styles have changed. If this is vetoed by the app,
        // the new sheet will be deleted. If it is not vetoed, the
        // old sheet will be deleted and replaced with the new one.
        buffer->SetStyleSheetAndNotify(sheet);
    }

    return true;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
// Export this object directly to the given stream.
bool wxRichTextParagraphLayoutBox::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    ::OutputIndentation(stream, indent);
    wxString nodeName = GetXMLNodeName();
    ::OutputString(stream, wxT("<") + nodeName, handler->GetConvMem(), handler->GetConvFile());

    wxString style = handler->AddAttributes(GetAttributes(), true);

    if (GetPartialParagraph())
        style << wxT(" partialparagraph=\"true\"");

    ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());

    if (GetProperties().GetCount() > 0)
    {
        handler->WriteProperties(stream, GetProperties(), indent);
    }
    
    size_t i;
    for (i = 0; i < GetChildCount(); i++)
    {
        wxRichTextObject* child = GetChild(i);
        child->ExportXML(stream, indent+1, handler);
    }

    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("</") + nodeName + wxT(">"), handler->GetConvMem(), handler->GetConvFile());
    return true;
}
#endif

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
// Export this object to the given parent node, usually creating at least one child node.
bool wxRichTextParagraphLayoutBox::ExportXML(wxXmlNode* parent, wxRichTextXMLHandler* handler)
{
    wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, GetXMLNodeName());
    parent->AddChild(elementNode);
    handler->AddAttributes(elementNode, GetAttributes(), true);
    handler->WriteProperties(elementNode, GetProperties());

    if (GetPartialParagraph())
        elementNode->AddAttribute(wxT("partialparagraph"), wxT("true"));

    size_t i;
    for (i = 0; i < GetChildCount(); i++)
    {
        wxRichTextObject* child = GetChild(i);
        child->ExportXML(elementNode, handler);
    }

    return true;
}
#endif

// Import this object from XML
bool wxRichTextTable::ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    wxRichTextBox::ImportFromXML(buffer, node, handler, recurse);
    
    *recurse = false;

    m_rowCount = wxAtoi(node->GetAttribute(wxT("rows"), wxEmptyString));
    m_colCount = wxAtoi(node->GetAttribute(wxT("cols"), wxEmptyString));
    
    wxXmlNode* child = node->GetChildren();
    while (child)
    {
        wxRichTextObject* childObj = handler->CreateObjectForXMLName(this, child->GetName());
        if (childObj)
        {
            AppendChild(childObj);
            handler->ImportXML(buffer, childObj, child);
        }
        child = child->GetNext();
    }

    m_cells.Add(wxRichTextObjectPtrArray(), m_rowCount);
    int i, j;
    for (i = 0; i < m_rowCount; i++)
    {
        wxRichTextObjectPtrArray& colArray = m_cells[i];
        for (j = 0; j < m_colCount; j++)
        {
            int idx = i * m_colCount + j;
            if (idx < (int) GetChildren().GetCount())
            {
                wxRichTextCell* cell = wxDynamicCast(GetChildren().Item(idx)->GetData(), wxRichTextCell);
                if (cell)
                    colArray.Add(cell);
            }
        }
    }

    return true;
}

#if wxRICHTEXT_HAVE_DIRECT_OUTPUT
// Export this object directly to the given stream.
bool wxRichTextTable::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    ::OutputIndentation(stream, indent);
    wxString nodeName = GetXMLNodeName();
    ::OutputString(stream, wxT("<") + nodeName, handler->GetConvMem(), handler->GetConvFile());

    wxString style = handler->AddAttributes(GetAttributes(), true);

    style << wxT(" rows=\"") << m_rowCount << wxT("\"");
    style << wxT(" cols=\"") << m_colCount << wxT("\"");

    ::OutputString(stream, style + wxT(">"), handler->GetConvMem(), handler->GetConvFile());

    if (GetProperties().GetCount() > 0)
    {
        handler->WriteProperties(stream, GetProperties(), indent);
    }
    
    int i, j;
    for (i = 0; i < m_rowCount; i++)
    {
        for (j = 0; j < m_colCount; j ++)
        {
            wxRichTextCell* cell = GetCell(i, j);
            cell->ExportXML(stream, indent+1, handler);
        }
    }

    ::OutputIndentation(stream, indent);
    ::OutputString(stream, wxT("</") + nodeName + wxT(">"), handler->GetConvMem(), handler->GetConvFile());

    return true;
}
#endif

#if wxRICHTEXT_HAVE_XMLDOCUMENT_OUTPUT
// Export this object to the given parent node, usually creating at least one child node.
bool wxRichTextTable::ExportXML(wxXmlNode* parent, wxRichTextXMLHandler* handler)
{
    wxXmlNode* elementNode = new wxXmlNode(wxXML_ELEMENT_NODE, GetXMLNodeName());
    parent->AddChild(elementNode);
    handler->AddAttributes(elementNode, GetAttributes(), true);
    handler->WriteProperties(elementNode, GetProperties());

    elementNode->AddAttribute(wxT("rows"), wxString::Format(wxT("%d"), m_rowCount));
    elementNode->AddAttribute(wxT("cols"), wxString::Format(wxT("%d"), m_colCount));

    int i, j;
    for (i = 0; i < m_rowCount; i++)
    {
        for (j = 0; j < m_colCount; j ++)
        {
            wxRichTextCell* cell = GetCell(i, j);
            cell->ExportXML(elementNode, handler);
        }
    }

    return true;
}
#endif


#endif
    // wxUSE_RICHTEXT && wxUSE_XML

