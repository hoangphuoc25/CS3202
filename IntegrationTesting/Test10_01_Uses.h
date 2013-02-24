#ifndef T11_TEST10_01_USES_H
#define T11_TEST10_01_USES_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_01_Uses: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_01_Uses);
CPPUNIT_TEST(test_uses_assign_var);
CPPUNIT_TEST(test_uses_procedure_var);
CPPUNIT_TEST(test_uses_call_var);
CPPUNIT_TEST(test_uses_if_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_uses_assign_var();
    void test_uses_procedure_var();
    void test_uses_call_var();
    void test_uses_if_var();
    std::string USES_00_SIMPLE_PROG;
};

#endif