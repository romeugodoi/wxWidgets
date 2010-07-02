///////////////////////////////////////////////////////////////////////////////
// Name:        tests/controls/itemcontainertest.h
// Purpose:     wxItemContainer unit test
// Author:      Steven Lamerton
// Created:     2010-06-29
// RCS-ID:      $Id$
// Copyright:   (c) 2010 Steven Lamerton
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_TESTS_CONTROLS_ITEMCONTAINERTEST_H_
#define _WX_TESTS_CONTROLS_ITEMCONTAINERTEST_H_

class ItemContainerTestCase : public CppUnit::TestCase
{
public:
    ItemContainerTestCase() { }

protected:
    // this function must be overridden by the derived classes to return the
    // text entry object we're testing, typically this is done by creating a
    // control implementing wxItemContainer interface in setUp() virtual method and
    // just returning it from here
    virtual wxItemContainer *GetContainer() const = 0;

    // and this one must be overridden to return the window which implements
    // wxItemContainer interface -- usually it will return the same pointer as
    // GetTestEntry(), just as a different type
    virtual wxWindow *GetContainerWindow() const = 0;

    // this should be inserted in the derived class CPPUNIT_TEST_SUITE
    // definition to run all wxItemContainer tests as part of it
    #define wxITEM_CONTAINER_TESTS() \
        CPPUNIT_TEST( Append ); \
        CPPUNIT_TEST( Insert ); \
        CPPUNIT_TEST( Count ); \
        CPPUNIT_TEST( Selection ); \
        CPPUNIT_TEST( FindString )

    void Append();
    void Insert();
    void Count();
    void Selection();
    void FindString();

private:
    DECLARE_NO_COPY_CLASS(ItemContainerTestCase)
};

#endif // _WX_TESTS_CONTROLS_ITEMCONTAINERTEST_H_
