#ifndef T11_TEST40_WITH_H
#define T11_TEST40_WITH_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test40_With: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test40_With);
CPPUNIT_TEST(test_ii_00);
CPPUNIT_TEST(test_ii_01);
CPPUNIT_TEST(test_ii_10);
CPPUNIT_TEST(test_ii_11);
CPPUNIT_TEST(test_ii_22);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string IIProc;
    /// Test with clause with both arguments being AttrRef int
    /// and not seen
    void test_ii_00();
    /// Test with clause with both arguments being AttrRef int
    /// and arg 2 was seen
    void test_ii_01();
    /// Test with clause with both arguments being AttrRef int
    /// and arg 1 was seen
    void test_ii_10();
    /// Test with clause with both arguments being AttrRef int
    /// and both args were seen in same Table
    void test_ii_11();
    /// Test with clause with both arguments being AttrRef int
    /// and both args were seen but in different Table
    void test_ii_22();
};

#endif