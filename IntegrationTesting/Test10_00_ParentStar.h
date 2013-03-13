#ifndef T11_TEST10_00_PARENT_STAR_H
#define T11_TEST10_00_PARENT_STAR_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_ParentStar: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_ParentStar);
CPPUNIT_TEST(test_parentstar_while_assign);
CPPUNIT_TEST(test_parentstar_while_prog_line);
CPPUNIT_TEST(test_parentstar_while_call);
CPPUNIT_TEST(test_parentstar_while_if);
CPPUNIT_TEST(test_parentstar_while_while);

CPPUNIT_TEST(test_parentstar_if_while);
CPPUNIT_TEST(test_parentstar_if_assign);
CPPUNIT_TEST(test_parentstar_if_prog_line);
CPPUNIT_TEST(test_parentstar_if_call);
CPPUNIT_TEST(test_parentstar_if_if);

CPPUNIT_TEST(test_parentstar_prog_line_assign);
CPPUNIT_TEST(test_parentstar_prog_line_prog_line);
CPPUNIT_TEST(test_parentstar_prog_line_call);
CPPUNIT_TEST(test_parentstar_prog_line_if);
CPPUNIT_TEST(test_parentstar_prog_line_while);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SELECT_ONE_SIMPLEPROG;
    void test_parentstar_while_assign();
    void test_parentstar_while_prog_line();
    void test_parentstar_while_call();
    void test_parentstar_while_if();
    void test_parentstar_while_while();

    void test_parentstar_if_while();
    void test_parentstar_if_assign();
    void test_parentstar_if_prog_line();
    void test_parentstar_if_call();
    void test_parentstar_if_if();

    void test_parentstar_prog_line_assign();
    void test_parentstar_prog_line_prog_line();
    void test_parentstar_prog_line_call();
    void test_parentstar_prog_line_if();
    void test_parentstar_prog_line_while();

    std::string TEST_PROG;
};

#endif