#ifndef T11_TEST10_01_NEXT_H
#define T11_TEST10_01_NEXT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_01_Next: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_01_Next);
CPPUNIT_TEST(test_next_stmt_01);
CPPUNIT_TEST(test_next_assign_01);
CPPUNIT_TEST(test_next_while_01);
CPPUNIT_TEST(test_next_if_01);
CPPUNIT_TEST(test_next_call_01);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_next_stmt_01();
    void test_next_assign_01();
    void test_next_while_01();
    void test_next_if_01();
    void test_next_call_01();
    std::string NEXT_01_PROG;
};

#endif