#ifndef T11_TEST_PQLPARSER_H
#define T11_TEST_PQLPARSER_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class TestPQLParser: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestPQLParser);
CPPUNIT_TEST(test_one_decl_one);
CPPUNIT_TEST(test_one_decl);
CPPUNIT_TEST(test_mult_decl);
CPPUNIT_TEST(test_select_bool);
CPPUNIT_TEST(test_select_tuple);
CPPUNIT_TEST(test_select_attrRef);
CPPUNIT_TEST(test_modifies);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_one_decl_one();
    void test_one_decl();
    void test_mult_decl();
    void test_select_bool();
    void test_select_tuple();
    void test_select_attrRef();
    void test_modifies();
};

#endif