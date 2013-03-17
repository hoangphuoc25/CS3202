#ifndef T11_TEST10_00_NEXT_STAR_H
#define T11_TEST10_00_NEXT_STAR_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_NextStar: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_NextStar);
CPPUNIT_TEST(test_next_star_stmt_00);
CPPUNIT_TEST(test_next_star_assign_00);
CPPUNIT_TEST(test_next_star_while_00);
CPPUNIT_TEST(test_next_star_if_00);
CPPUNIT_TEST(test_next_star_call_00);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_next_star_stmt_00();
    void test_next_star_assign_00();
    void test_next_star_while_00();
    void test_next_star_if_00();
    void test_next_star_call_00();
    std::string NEXT_STAR_00_PROG;

};

#endif