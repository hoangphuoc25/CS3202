#ifndef T11_TEST21_MODIFIES_N2S_H
#define T11_TEST21_MODIFIES_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Modifies Relation with 0 or 1
 * synonym arguments.
 */
class Test21_Modifies_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_Modifies_N2S);
CPPUNIT_TEST(test_modifies_int_string);
CPPUNIT_TEST(test_modifies_int_wild);
CPPUNIT_TEST(test_modifies_string_string);
CPPUNIT_TEST(test_modifies_string_wild);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_modifies_int_string();
    void test_modifies_int_wild();
    void test_modifies_string_string();
    void test_modifies_string_wild();
};

#endif