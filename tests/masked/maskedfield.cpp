///////////////////////////////////////////////////////////////////////////////
// Name:        tests/filename/maskedfield.cpp
// Purpose:     wxMaskedField unit test
// Author:      Julien Weinzorn
// Created:     2004-07-25
// RCS-ID:      $Id: ??????????????? $
// Copyright:   (c) 2010 Julien Weinzorn
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif // WX_PRECOMP

#ifdef __WXMSW__
    #include "wx/msw/registry.h"
#endif // __WXMSW__

#include "wx/maskedfield.h"

// ----------------------------------------------------------------------------
// test data
// ----------------------------------------------------------------------------

static struct TestMaskedField
{
    wxString test;
    wxString mask;        
    wxString formatCode;
    wxString defaultValue;
    wxArrayString choices;
    bool autoSelect;
    wxChar groupChar;
    wxChar decimalPoint;
    bool useParensForNegatives;

}
masked[]=
    {
        //various mask and different format code
        {wxT("127.000.000.001") , wxT("###.###.###.###") , wxT("F") , wxT(" "), wxArrayString(), true , ' ' , '.', false},
        {wxT("127.AVc.bAc")     , wxT("###.CCC.aAC")     , wxT("F!"), wxT(" "), wxArrayString(), true , ' ', '.', false},
        {wxT("12#.AC?fA")       , wxT("##\\#.C\\C?a\\A") , wxT("F") , wxT(" "), wxArrayString(), false, ' ', '.', false},
    };

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class MaskedFieldTestCase : public CppUnit::TestCase
{
public:
    MaskedFieldTestCase() { }

private:
    CPPUNIT_TEST_SUITE( MaskedFieldTestCase );
        CPPUNIT_TEST( TestIsCharValid );
        CPPUNIT_TEST( TestIsValid     );
        CPPUNIT_TEST( TestIsEmpty     );
        CPPUNIT_TEST( TestApplyFormatsCode  );
        CPPUNIT_TEST( TestAddChoice   );
        CPPUNIT_TEST( TestAddChoices  );
        CPPUNIT_TEST( TestSetMask     );
        CPPUNIT_TEST( TestGetPlainValue     );

    CPPUNIT_TEST_SUITE_END();

    void TestIsCharValid();
    void TestIsValid();
    void TestIsEmpty();
    void TestApplyFormatsCode();
    void TestAddChoice();
    void TestAddChoices();
    void TestSetMask();
    void TestGetPlainValue();

    DECLARE_NO_COPY_CLASS(MaskedFieldTestCase)
};

// register in the unnamed registry.
CPPUNIT_TEST_SUITE_REGISTRATION( MaskedFieldTestCase );

// Include in it's own registry.
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( MaskedFieldTestCase, "MaskedFieldTestCase" );

void MaskedFieldTestCase::TestIsCharValid()
{
    static struct TestIsCharValid
    {
        wxChar maskTest;
        wxChar charTest;
        bool result;

    }
    maskedCharValid[]=
    {
        {'1' ,'#', true},
        {'1' ,'a', false},
        {'1' ,'A', false},
        {'1' ,'X', true},
        {'1' ,'&', false},
        {'1' ,'*', true},
        {'1' ,'C', false},
        {'1' ,'N', true},

        {'a' ,'#', false},
        {'a' ,'a', true},
        {'a' ,'A', false},
        {'a' ,'X', true},
        {'a' ,'&', false},
        {'a' ,'*', true},
        {'a' ,'C', true},
        {'a' ,'N', true},   
        
        {'A' ,'#', false},
        {'A' ,'a', false},
        {'A' ,'A', true},
        {'A' ,'X', true},
        {'A' ,'&', false},
        {'A' ,'*', true},
        {'A' ,'C', true},
        {'A' ,'N', true}, 
        
        {'.' ,'#', false},
        {'.' ,'a', false},
        {'.' ,'A', false},
        {'.' ,'X', true},
        {'.' ,'&', true},
        {'.' ,'*', true},
        {'.' ,'C', false},
        {'.' ,'N', false},    
        
        {'|' ,'#', false},
        {'|' ,'a', false},
        {'|' ,'A', false},
        {'|' ,'X', false},
        {'|' ,'&', false},
        {'|' ,'*', true},
        {'|' ,'C', false},
        {'|' ,'N', false},
    };


    for(unsigned int n = 0; n< WXSIZEOF(maskedCharValid); n++)
    {
        wxMaskedField mask(wxT("###"));
        CPPUNIT_ASSERT( mask.IsCharValid(maskedCharValid[n].maskTest, maskedCharValid[n].charTest) == maskedCharValid[n].result );    
    }

}


void MaskedFieldTestCase::TestIsValid()
{
    static struct TestValid
    {
        wxString mask;
        wxString test;
        bool result;
    }
    listTest[]=
    {
        {wxT("") , wxT("") , true}, 
        {wxT("") , wxT("azd") , false},
        {wxT("###") , wxT("123") , true},
        {wxT("###") , wxT("Az3") , false},
        {wxT("###") , wxT("wx.;") , false},
        {wxT("###") , wxT("12,") , false},

        {wxT("AAa.#X*") , wxT("AZc.3,|") , true},
        {wxT("AAa.#X*") , wxT("AZc3,|")  , false}, // correct or not?
        {wxT("AAa.#X*") , wxT("aZc.|.|") , false},
        {wxT("AAa.#X*") , wxT("")        , false},  // correct or not?
        {wxT("AAa.#X*") , wxT("AZc.3,|4"), false},

        {wxT("###\\*###") , wxT("") , true},
        {wxT("###\\*###") , wxT("123*593") , true},
        {wxT("###\\*###") , wxT("123456") , false}, //correct or not?
        {wxT("###\\*###") , wxT("124\\*45") , false}



    
    };

    for(unsigned int n = 0; n< WXSIZEOF(listTest); n++)
    {
        wxMaskedField mask(listTest[n].mask);
        CPPUNIT_ASSERT( mask.IsValid(listTest[n].test) == listTest[n].result); 
    }

}

void MaskedFieldTestCase::TestIsEmpty()
{
    static struct TestEmpty
    {
        wxString mask;      
        wxString formatCodes;
        wxString defaultValue;
        wxString test;
        bool result;


    }
    maskedEmpty[]=
    {
        {wxT("###.###.###.###"), wxT(""),   wxT("...")            , wxT("...")            , false},
        {wxT("###.###.###.###"), wxT("_"),  wxT("...")            , wxT("...")            , false},
        {wxT("###.###.###.###"), wxT("F_"), wxT("   .   .   .   "), wxT("   .   .   .   "), true},
        {wxT("###.###.###.###"), wxT("_"),  wxT("1  .2  .123.111"), wxT("1  .2  .123.111"), true },
        {wxT("###.###.###.###"), wxT(""),   wxT("123.000.000.111"), wxT("123.000.000.111"), true},
    };


    for(unsigned int n = 0; n< WXSIZEOF(maskedEmpty); n++)
    {
        wxMaskedField mask(maskedEmpty[n].mask, maskedEmpty[n].formatCodes, maskedEmpty[n].defaultValue); 
        CPPUNIT_ASSERT( mask.IsEmpty(maskedEmpty[n].test) == maskedEmpty[n].result );    
    }

}

void MaskedFieldTestCase::TestApplyFormatsCode()
{
    static struct TestFormatCode
    {
        wxString mask;      
        wxString formatCodes;
        wxString test;
        wxString result;


    }
    maskedFormatCode[]=
    {
        {wxT("###.###.###.###"), wxT("F_"), wxT("1.2.3.4"), wxT("1  .2  .3  .4  ")},
        {wxT("###.AAA.aC\\&"), wxT("F!"), wxT("111.aaa.a2&"), wxT("111.AAA.a2&  ")},
        {wxT("CXX."), wxT("F!_"), wxT("3rt."), wxT("3RT.")},
    };


    for(unsigned int n = 0; n< WXSIZEOF(maskedFormatCode); n++)
    {
        wxMaskedField mask(maskedFormatCode[n].mask, maskedFormatCode[n].formatCodes); 
        wxString res = mask.ApplyFormatCodes(maskedFormatCode[n].test); 
        CPPUNIT_ASSERT( res.Cmp(maskedFormatCode[n].result) == 0 );    
    }

}

void MaskedFieldTestCase::TestAddChoice()
{
    static struct TestChoice
    {
        wxString mask;      
        wxString test;
        bool result;


    }
    maskedChoice[]=
    {
        {wxT("###.###.###.###"), wxT("111.222.333.444"), true},
        {wxT("###.###.###.###"), wxT("111.2z2.333.444"), false},
        {wxT("###.###.###.###"), wxT("111.222.3.444"),   false},
        {wxT("###.###.###.###"), wxT(""), false},
    };


    for(unsigned int n = 0; n< WXSIZEOF(maskedChoice); n++)
    {
        wxMaskedField mask(maskedChoice[n].mask); 
        CPPUNIT_ASSERT( mask.AddChoice(maskedChoice[n].test) ==  
                        maskedChoice[n].result );    
    }

}
void MaskedFieldTestCase::TestAddChoices()
{
    wxMaskedField mask(wxT("###.###.AA\\#"));
        
    wxArrayString testChoices = wxArrayString();



    CPPUNIT_ASSERT( mask.AddChoices(testChoices) == true );    
    testChoices.Add(wxT("111.111.CD#"));
    CPPUNIT_ASSERT( mask.AddChoices(testChoices) == true );
    testChoices.Add(wxT("111.AAA.CD#"));
    CPPUNIT_ASSERT( mask.AddChoices(testChoices) == false );
    
    testChoices.Add(wxT("111.111.CD#"));
    CPPUNIT_ASSERT( mask.AddChoices(testChoices) == false );


}
//FIXME  how to test this
void MaskedFieldTestCase::TestSetMask()
{

    
}
void MaskedFieldTestCase::TestGetPlainValue()
{
    static struct TestPlainValue
    {
        wxString mask;      
        wxString formatCodes;
        wxString test;
        wxString result;


    }
    maskedPlainValue[]=
    {
        {wxT("###.###.###.###"), wxT("F_"), wxT("1.2.3.4"), wxT("1  2  3  4  ")},
        {wxT("###.AAA.aC\\&"), wxT("F!"), wxT("111.aaa.a2&"), wxT("111AAA.a2")},
        {wxT("CXX."), wxT("F!_"), wxT("3rt."), wxT("3RT")},
    };


    for(unsigned int n = 0; n< WXSIZEOF(maskedPlainValue); n++)
    {
        wxMaskedField mask(maskedPlainValue[n].mask, maskedPlainValue[n].formatCodes); 
        wxString res = mask.GetPlainValue(maskedPlainValue[n].test); 
        CPPUNIT_ASSERT( res.Cmp(maskedPlainValue[n].result) == 0 );    
    }


}


