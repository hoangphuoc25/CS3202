#ifndef T11_TEST10_01_MODIFIES_H
#define T11_TEST10_01_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_01_Modifies: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_01_Modifies);
CPPUNIT_TEST(test_modifies_assign_var_01);
CPPUNIT_TEST(test_modifies_proc_var_01);
CPPUNIT_TEST(test_modifies_call_var_01);
CPPUNIT_TEST(test_modifies_while_var_01);
CPPUNIT_TEST(test_modifies_if_var_01);
CPPUNIT_TEST(test_modifies_stmt_var_01);
CPPUNIT_TEST(test_modifies_progline_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_modifies_assign_var_01();
    void test_modifies_proc_var_01();
    void test_modifies_call_var_01();
    void test_modifies_while_var_01();
    void test_modifies_if_var_01();
    void test_modifies_stmt_var_01();
    void test_modifies_progline_var();
    std::string MODIFIES_01_PROG;
};

#endif