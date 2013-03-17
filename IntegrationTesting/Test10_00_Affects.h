#ifndef T11_TEST10_00_AFFECTS_H
#define T11_TEST10_00_AFFECTS_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Affects: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Affects);
CPPUNIT_TEST(test_affects_stmt_00);
//CPPUNIT_TEST(test_affects_assign_00);
//CPPUNIT_TEST(test_affects_while_00);
//CPPUNIT_TEST(test_affects_if_00);
//CPPUNIT_TEST(test_affects_call_00);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_affects_stmt_00();
    void test_affects_assign_00();
    void test_affects_while_00();
    void test_affects_if_00();
    void test_affects_call_00();
    std::string AFFECTS_00_PROG;
};

#endif