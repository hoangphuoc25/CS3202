#ifndef T11_TEST21_CALLS_N2S_H
#define T11_TEST21_CALLS_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Uses Relation with 0 or 1
 * synonym arguments.
 */
class Test21_Calls_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_Calls_N2S);
CPPUNIT_TEST(test_calls_string_string);
CPPUNIT_TEST(test_calls_string_wild);
CPPUNIT_TEST(test_calls_wild_string);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_calls_string_string();
    void test_calls_string_wild();
    void test_calls_wild_string();
};

#endif