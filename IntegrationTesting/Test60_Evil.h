#ifndef T11_TEST60_EVIL_H
#define T11_TEST60_EVIL_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Modifies Relation with 0 or 1
 * synonym arguments.
 */
class Test60_Evil: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test60_Evil);
CPPUNIT_TEST(test_select_boolean_no_clause);
CPPUNIT_TEST(test_select_a_a);
CPPUNIT_TEST(test_select_a1_a2);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_select_boolean_no_clause();
    void test_select_a_a();
    void test_select_a1_a2();

    std::string BASIC_PROG;
};

#endif