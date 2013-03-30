#ifndef T11_TEST_30_PKB_HAS_X_H
#define T11_TEST_30_PKB_HAS_X_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests the has_any_X methods in the PKB
 */
class Test_30_PKB_has_X: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_has_X);
CPPUNIT_TEST(test_has_assign);
CPPUNIT_TEST(test_has_call);
CPPUNIT_TEST(test_has_if);
CPPUNIT_TEST(test_has_while);
CPPUNIT_TEST(test_has_stmt);
CPPUNIT_TEST(test_has_progline);
CPPUNIT_TEST(test_has_stmtLst);
CPPUNIT_TEST(test_has_const);
CPPUNIT_TEST(test_has_variable);
CPPUNIT_TEST(test_has_procedure);
CPPUNIT_TEST(test_has_call_procName);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:

    void test_has_assign();
    void test_has_call();
    void test_has_if();
    void test_has_while();
    void test_has_stmt();
    void test_has_progline();
    void test_has_stmtLst();
    void test_has_const();
    void test_has_variable();
    void test_has_procedure();
    void test_has_call_procName();

    std::string TEST_MODIFIES_SIMPLE_PROG;
};

#endif