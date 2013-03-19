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
CPPUNIT_TEST(test_select_while__no_while);
CPPUNIT_TEST(test_select_assign_while__no_while);
CPPUNIT_TEST(test_select_assign_while_true_query__no_while);
CPPUNIT_TEST(test_sx);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_select_boolean_no_clause();
    void test_select_a_a();
    void test_select_a1_a2();
    void test_select_while__no_while();
    void test_select_assign_while__no_while();
    void test_select_assign_while_true_query__no_while();
    void test_sx();

    std::string BASIC_PROG;
    std::string NOWHILE_PROG;
};

#endif