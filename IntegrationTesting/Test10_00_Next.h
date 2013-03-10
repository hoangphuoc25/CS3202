#ifndef T11_TEST10_00_NEXT_H
#define T11_TEST10_00_NEXT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Next: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Next);
CPPUNIT_TEST(test_next_stmt_00);
CPPUNIT_TEST(test_next_assign_00);
CPPUNIT_TEST(test_next_while_00);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_next_stmt_00();
    void test_next_assign_00();
    void test_next_while_00();
    void test_next_if_00();
    void test_next_call_00();
    std::string NEXT_00_PROG;
};

#endif