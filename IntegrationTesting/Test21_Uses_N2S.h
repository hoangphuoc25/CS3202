#ifndef T11_TEST21_USES_N2S_H
#define T11_TEST21_USES_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Uses Relation with 0 or 1
 * synonym arguments.
 */
class Test21_Uses_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_Uses_N2S);
CPPUNIT_TEST(test_uses_string_string);
CPPUNIT_TEST(test_uses_string_wild);
CPPUNIT_TEST(test_uses_int_string);
CPPUNIT_TEST(test_uses_int_wild);
CPPUNIT_TEST(test_uses_wild_string);
CPPUNIT_TEST(test_uses_wild_wild);
CPPUNIT_TEST(test_uses_X_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_uses_string_string();
    void test_uses_string_wild();
    void test_uses_int_string();
    void test_uses_int_wild();
    void test_uses_wild_string();
    void test_uses_wild_wild();
    void test_uses_X_syn();
};

#endif