/////////////////////////////////////////////////////////////////////////////
// Name:        No names yet.
// Purpose:     Contrib. demo
// Author:      Aleksandras Gluchovas
// Modified by:
// Created:     22/09/98
// RCS-ID:      $Id$
// Copyright:   (c) Aleskandars Gluchovas
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "docripper.h"

#if wxUSE_IOSTREAMH
    #include <iostream.h>
#else
    #include <iostream>
#endif

// script templates

// ***** currently only HTML versions of variouse templates available ***** //

static const char* HTM_TopTempl =

"<html><body bgcolor=#FFFFFF>\n\
\n\n<!------ Automatically Generated by \"wxDocRipper\"------->\n\n\n\
<p><h2>$(NAME)</h2><p>\n\
<ul>\n\
$(REFLIST)\
</ul><p>\n\n\
";

static const char* HTM_ContentIdxTempl =

"\
<a name=\"r$(ID)_$(NAME)\">\n\
<p><hr>\n\
<h2><p>$(NAME)<p></h2>\
<ul>\n\
$(REFLIST)\
</ul><p>\n\n\
";

static const char* HTM_SuperContentTempl =

"\
<a name=\"r$(ID)_$(NAME)\">\n\
<p><hr>\n\
<p><h2>$(NAME)<p></h2>\
$(BODY)\n\
";

static const char* HTM_SubContentTempl =

"\
<a name=\"r$(ID)_$(NAME)\">\n\
<p><hr>\n\
<p><h3>$(NAME)<p></h3>\
$(BODY)\n\
";

static const char* HTM_OutLineTempl =

"\
<p>\n\
<b><font color=\"#FF0000\">$(NAME)</font></b><p>\n\
";

static const char* HTM_OutLine1Templ =

"\
<p>\n\
<b><i><font color=\"#101010\">$(NAME)</font></i></b>\n\
<ul>\n\
$(REFLIST)\
</ul>\n\n\
";

static const char* HTM_RefTempl =

"\
<li><a href=\"#r$(ID)_$(NAME)\">$(NAME)</A>\n\
";

static const char* HTM_DeadRefTempl =

"\
<li></b>$(NAME)\n\
";

/***** Implementation for class RipperDocGen *****/

RipperDocGen::RipperDocGen()

    : mTopTempl         ( HTM_TopTempl ),
      mContentIdxTempl  ( HTM_ContentIdxTempl ),
      mSuperContentTempl( HTM_SuperContentTempl ),
      mSubContentTempl  ( HTM_SubContentTempl ),
      mOutLineTempl     ( HTM_OutLineTempl ),
      mOutLine1Templ    ( HTM_OutLine1Templ ),

      mRefTempl         ( HTM_RefTempl ),
      mDeadRefTempl     ( HTM_DeadRefTempl ),

      mpCurClassSect(0)
{
    // topIndex is not referenced
    mpTopIdx        = new ScriptSection( "Source Code Contents"       , wxEmptyString, &mTopTempl       , 0          );
    mpClassIdx      = new ScriptSection( "Classes Reference"          , wxEmptyString, &mContentIdxTempl, &mRefTempl );
    mpEnumIdx       = new ScriptSection( "Enumerations  Reference"    , wxEmptyString, &mContentIdxTempl,  &mRefTempl );
    mpTypeDefIdx    = new ScriptSection( "Type Definitions Reference" , wxEmptyString, &mContentIdxTempl, &mRefTempl );
    mpMacroIdx      = new ScriptSection( "Macros Reference"           , wxEmptyString, &mContentIdxTempl, &mRefTempl );
    mpGlobalVarsIdx = new ScriptSection( "Global Variables Reference" , wxEmptyString, &mContentIdxTempl, &mRefTempl );
    mpGlobalFuncIdx = new ScriptSection( "Global Functions  Reference", wxEmptyString, &mContentIdxTempl, &mRefTempl );
    mpConstIdx      = new ScriptSection( "Constants  Reference"       , wxEmptyString, &mContentIdxTempl, &mRefTempl );

    // assemble top index
    mpTopIdx->AddSection( mpClassIdx     , 1 );
    mpTopIdx->AddSection( mpEnumIdx      , 1 );
    mpTopIdx->AddSection( mpTypeDefIdx   , 1 );
    mpTopIdx->AddSection( mpMacroIdx     , 1 );
    mpTopIdx->AddSection( mpGlobalVarsIdx, 1 );
    mpTopIdx->AddSection( mpGlobalFuncIdx, 1 );
    mpTopIdx->AddSection( mpConstIdx     , 1 );

    // register reserved variables for index and description templates
    ScriptSection::RegisterTemplate( mTopTempl );
    ScriptSection::RegisterTemplate( mContentIdxTempl );
    ScriptSection::RegisterTemplate( mSuperContentTempl );
    ScriptSection::RegisterTemplate( mSubContentTempl );
    ScriptSection::RegisterTemplate( mOutLineTempl );
    ScriptSection::RegisterTemplate( mOutLine1Templ );
    ScriptSection::RegisterTemplate( mRefTempl );
    ScriptSection::RegisterTemplate( mDeadRefTempl );

    // create the top-most (interfile) context
    mpFileBinderCtx = new spFile();

    // the default script is HTML
    m_Tags = get_HTML_markup_tags();

    mpParser = 0; // no default parser!
}

void RipperDocGen::Init( SourceParserBase* pParser )
{
    mpParser = pParser;
}

RipperDocGen::~RipperDocGen()
{
    delete mpFileBinderCtx;
}

void RipperDocGen::AppendComments( spContext& fromContext, wxString& str )
{
    if ( !fromContext.HasComments() ) return;

    size_t start = str.length();

    str += m_Tags[TAG_BOLD].end;
    str += m_Tags[TAG_PARAGRAPH].start;

    MCommentListT& lst = fromContext.GetCommentList();

    for( size_t i = 0; i != lst.size(); ++i )
    {

        if ( i != 0 )

            if ( lst[i]->StartsParagraph() )
            {
                str += m_Tags[TAG_PARAGRAPH].start;
            }

        str += lst[i]->m_Text;
    }

    // remove new lines, and insert paragraph breaks

    // if empty lines found

    size_t len = str.length();

    for( size_t n = start; n != len; ++n )

        if ( str[n] == 10 ||
             str[n] == 13  )
        {
            if ( n + 2 < len )
            {
                if ( ( str[n] == 13 && str[n+1] == 10 &&  // FIXME:: quick-hack
                       str[n+2] == 13 ) ||
                     ( str[n] == 10 && str[n+1] == 10 )
                   )
                {
                    str.insert( n + 1, _T("<p>") ); // FIXME:: quick-hack
                    len += 3;
                }
            }
            str[n] = _T(' ');
        }
    str += m_Tags[TAG_PARAGRAPH].end;
}

void RipperDocGen::AppendMulitilineStr( wxString& st, wxString& mlStr )
{
    st = m_Tags[TAG_FIXED_FONT].start;
    st += mlStr;
    st += m_Tags[TAG_FIXED_FONT].end;
}

void RipperDocGen::AppendHighlightedSource( wxString& st, wxString source )
{
    // FIXME:: below should not be fixed :)
    char buf[1024*32];

    // DBG:::
//    ASSERT( source.length() + 1 < sizeof(buf) );

    wxStrcpy( buf, source.c_str() );

    // highlight things
    mSrcPainter.Init();
    mSrcPainter.ProcessSource( buf, strlen(buf) );
    mSrcPainter.GetResultString( st, m_Tags );
}

bool RipperDocGen::CheckIfUncommented( spContext& ctx, ScriptSection& toSect )
{
    if ( ctx.HasComments() ) return 0;

    toSect.AddReference(
        new ScriptSection( GetScopedName( ctx ), wxEmptyString, 0, &mDeadRefTempl )
    );

    return 1;
}

ScriptTemplate* RipperDocGen::GetRefTemplFor( spContext& ctx )
{
    if ( ctx.HasComments() )
        return &mRefTempl;
    else
        return &mDeadRefTempl;
}

wxString RipperDocGen::GetScopedName( spContext& ofCtx )
{
    if ( ofCtx.IsInFile() )
        return ofCtx.GetName();
    else
        return ofCtx.GetOutterContext()->GetName() +
               _T("::") + ofCtx.GetName();
}

void RipperDocGen::AddToCurrentClass( ScriptSection* pSection, spContext& ctx,
                                      const char* subSectionName )
{
    wxString sName;

    if ( ctx.mVisibility == SP_VIS_PROTECTED )
        sName = "Protected members/";
    else
        if ( ctx.mVisibility == SP_VIS_PRIVATE )
            sName = "Private members/";
        else
            sName = "Public members/";

    sName += subSectionName;

    ScriptSection* pSect = mpCurClassSect->GetSubsection( sName.c_str() );

    if ( CheckIfUncommented( ctx, *pSect ) )
    {
        delete pSection;
        return;
    }

    pSect->AddReference( pSection );

    mpCurClassSect->AddSection( pSection );
}

void RipperDocGen::LinkSuperClassRefs()
{
    MMemberListT clLst;

    // collect all classes in the context tree
    mpFileBinderCtx->GetContextList( clLst, SP_CTX_CLASS );

    for( size_t i = 0; i != clLst.size(); ++i )
    {
        spClass& cl = *((spClass*)clLst[i]);

        // FIXME:: why sometimes GetUserData() returns NULL?
        if ( !cl.GetUserData() )
            continue;

        ScriptSection* pClSect = (ScriptSection*)cl.GetUserData();
        ScriptSection* pSuperSect = pClSect->GetSubsection("Derived from");

        for( size_t n = 0; n != cl.m_SuperClassNames.size(); ++n )
        {
            wxString& superClName = cl.m_SuperClassNames[n];

            spClass* pFound = NULL;

            for( size_t k = 0; k != clLst.size(); ++k )
            {
                if ( clLst[k]->GetName() == superClName )
                {
                    pFound = (spClass*)clLst[k];
                    break;
                }
            }

            if ( !pFound )
            {
                ScriptSection* pNotFound =
                    new ScriptSection( superClName, wxEmptyString, 0, &mDeadRefTempl );

                pSuperSect->AddReference( pNotFound );
            }
            else
                if ( pFound->GetUserData() )

                    pSuperSect->AddReference(
                        (ScriptSection*)pFound->GetUserData() );
        }
    }
}

void RipperDocGen::ProcessFile( const char* sourceFile )
{
    wxSTD cout << "Processing file " << sourceFile << "..." << wxSTD endl;

    spFile* pCtx = mpParser->ParseFile( sourceFile );

    if ( pCtx == NULL )
    {
        wxSTD cout << "Cannot open file " << sourceFile << ", skipped..." << wxSTD endl;

        return;
    }

    VisitAll( *pCtx, true );

    mpFileBinderCtx->AddMember( pCtx );
}

// implementations of "visiting procedures"

void RipperDocGen::VisitEnumeration( spEnumeration& en )
{
    // FOR NOW:: do not reference "nameless" enums
    if ( en.GetName().empty() ) return;

    if ( CheckIfUncommented( en, *mpEnumIdx ) )
        return;

    wxString body;
    body += m_Tags[TAG_BOLD].start;

    AppendMulitilineStr( body, en.m_EnumContent );

    body += m_Tags[TAG_BOLD].end;

    wxString line;
    AppendHighlightedSource( line, body );
    AppendComments( en, line );

    mpEnumIdx->AddSection(
        new ScriptSection( en.GetName(), line,
                           &mSubContentTempl,
                           GetRefTemplFor( en ) ), 1
    );
}

void RipperDocGen::VisitTypeDef( spTypeDef& td )
{
    if ( CheckIfUncommented( td, *mpTypeDefIdx ) )
        return;

    wxString body;
    body += m_Tags[TAG_BOLD].start;
    body += "typdef ";
    body += m_Tags[TAG_BOLD].end;

    AppendMulitilineStr( body, td.m_OriginalType );
    body += td.m_OriginalType;
    body += ' ';

    body += m_Tags[TAG_BOLD].start;
    body += td.GetName();
    body += m_Tags[TAG_BOLD].end;

    wxString line;
    AppendHighlightedSource( line, body );
    AppendComments( td, line );

    mpTypeDefIdx->AddSection(
        new ScriptSection( td.GetName(), line,
                           &mSubContentTempl,
                           GetRefTemplFor( td ) ), true
    );
}

void RipperDocGen::VisitPreprocessorLine( spPreprocessorLine& pd )
{
    if ( pd.mDefType != SP_PREP_DEF_REDEFINE_SYMBOL )
        return;

    if ( CheckIfUncommented( pd, *mpMacroIdx ) )
        return;

    wxString body;
    body += m_Tags[TAG_FIXED_FONT].start;

    wxString coloredLine = pd.m_Line;
    AppendHighlightedSource( coloredLine, pd.m_Line );

    AppendMulitilineStr( body, coloredLine );

    body += m_Tags[TAG_FIXED_FONT].end;

    AppendComments( pd, body );

    mpMacroIdx->AddSection(
        new ScriptSection( pd.GetName(), body,
                           &mSubContentTempl,
                           GetRefTemplFor( pd ) ), true
    );
}

void RipperDocGen::VisitClass( spClass& cl )
{
    // FOR NOW:: do not document nested classes -
    //           nicier visiting method yet needed

    if ( cl.IsInClass() )
    {
        SkipChildren(); // spVisitor's method
        return;
    }

    wxString body;
    AppendComments( cl, body );

    mpCurClassSect =
        new ScriptSection( cl.GetName(), body, &mSuperContentTempl, &mRefTempl );

    // set up reference in the class context, pointing back
    // to the section where this class is represented
    cl.SetUserData( mpCurClassSect );

    ScriptSection* pSuper    = new ScriptSection( "Derived from"       ,wxEmptyString, &mOutLine1Templ,0, 1 );

    ScriptSection* pPublic    = new ScriptSection( "Public members"    ,wxEmptyString, &mOutLineTempl,0, 1 );
    ScriptSection* pProtected = new ScriptSection( "Protected members" ,wxEmptyString, &mOutLineTempl,0, 1 );
    ScriptSection* pPrivate   = new ScriptSection( "Private members"   ,wxEmptyString, &mOutLineTempl,0, 1 );

    pPublic->AddSection( new ScriptSection( "Operations", wxEmptyString, &mOutLine1Templ, 0, 1 ) );
    pPublic->AddSection( new ScriptSection( "Attributes", wxEmptyString, &mOutLine1Templ, 0, 1 ) );

    pProtected->AddSection( new ScriptSection( "Operations", wxEmptyString, &mOutLine1Templ, 0, 1 ) );
    pProtected->AddSection( new ScriptSection( "Attributes", wxEmptyString, &mOutLine1Templ, 0, 1 ) );

    pPrivate->AddSection( new ScriptSection( "Operations", wxEmptyString, &mOutLine1Templ, 0, 1 ) );
    pPrivate->AddSection( new ScriptSection( "Attributes", wxEmptyString, &mOutLine1Templ, 0, 1 ) );

    mpCurClassSect->AddSection( pSuper    );
    mpCurClassSect->AddSection( pPublic    );
    mpCurClassSect->AddSection( pProtected );
    mpCurClassSect->AddSection( pPrivate   );

    mpClassIdx->AddSection( mpCurClassSect, true );
}

void RipperDocGen::VisitAttribute( spAttribute& attr )
{
    wxString body;
    body += m_Tags[TAG_BOLD].start;
    body += attr.m_Type;
    body += m_Tags[TAG_BOLD].end;

    body += m_Tags[TAG_ITALIC].start;
    body += ' ';
    body += attr.GetName();
    body += m_Tags[TAG_ITALIC].end;

    wxString line;
    AppendHighlightedSource( line, body );
    AppendComments( attr, line );

    ScriptSection* pSection =
        new ScriptSection( GetScopedName( attr ), line,
                           &mSubContentTempl,
                           GetRefTemplFor( attr ) );

    if ( attr.mIsConstant )
        mpConstIdx->AddSection( pSection, true );
    else
        if ( !attr.IsInClass() )
        {
            if ( CheckIfUncommented( attr, *mpGlobalVarsIdx ) )
                return;
            mpGlobalVarsIdx->AddSection( pSection, true );
        }
        else
            AddToCurrentClass( pSection, attr, "Attributes" );
}

void RipperDocGen::VisitOperation( spOperation& op )
{
    wxString body;

    AppendHighlightedSource( body, op.GetFullName(m_Tags) );

    AppendComments( op, body );

    ScriptSection* pSection =
        new ScriptSection( GetScopedName( op ), body,
                           &mSubContentTempl,
                           GetRefTemplFor( op ) );

    if ( !op.IsInClass() )
    {
        if ( CheckIfUncommented( op, *mpGlobalFuncIdx ) )
            return;

        mpGlobalFuncIdx->AddSection( pSection, 1 );
    }
    else
        AddToCurrentClass( pSection, op, "Operations" );
}

bool RipperDocGen::OnSaveDocument( ScriptStream& WXUNUSED(stm) )
{
    LinkSuperClassRefs();

    // FOR NOW:: doesn't work yet
    //mpTopIdx->RemoveEmptySections();

    return 1; // saving can proceed now
}

