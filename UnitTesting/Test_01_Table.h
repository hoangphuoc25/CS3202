#ifndef T11_TEST_01_TABLE_H
#define T11_TEST_01_TABLE_H

#include <cppunit/extensions/HelperMacros.h>

class Test_01_Table: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_01_Table);
CPPUNIT_TEST(test_add_row_s);
CPPUNIT_TEST(test_add_row_i);
CPPUNIT_TEST(test_add_row_ss);
CPPUNIT_TEST(test_add_row_si);
CPPUNIT_TEST(test_add_row_is);
CPPUNIT_TEST(test_add_row_ii);
CPPUNIT_TEST(test_add_row_r_s);
CPPUNIT_TEST(test_add_row_r_i);
CPPUNIT_TEST(test_add_row_r_ss);
CPPUNIT_TEST(test_add_row_r_si);
CPPUNIT_TEST(test_add_row_r_is);
CPPUNIT_TEST(test_add_row_r_ii);
CPPUNIT_TEST(test_add_row_dead);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_add_row_s();
    void test_add_row_i();
    void test_add_row_ss();
    void test_add_row_si();
    void test_add_row_is();
    void test_add_row_ii();
    void test_add_row_r_s();
    void test_add_row_r_i();
    void test_add_row_r_ss();
    void test_add_row_r_si();
    void test_add_row_r_is();
    void test_add_row_r_ii();
    void test_add_row_dead();
};

#endif