#ifndef TEST20_SELECT_SYN_SYN_RELREF_H
#define TEST20_SELECT_SYN_SYN_RELREF_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test20_SynSyn_RelRef: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test20_SynSyn_RelRef);
CPPUNIT_TEST(test_variables_both_modified_and_used);
CPPUNIT_TEST(test_ev_rr_ss_string_string_00_from_argOne);
CPPUNIT_TEST(test_ev_rr_ss_string_string_01);
CPPUNIT_TEST(test_ev_rr_ss_string_string_10);
CPPUNIT_TEST(test_ev_rr_ss_string_string_11);
CPPUNIT_TEST(test_ev_rr_ss_string_string_22);
CPPUNIT_TEST(test_ev_rr_ss_int_string_00_from_argOne);
CPPUNIT_TEST(test_ev_rr_ss_int_string_01);
CPPUNIT_TEST(test_ev_rr_ss_int_string_10);
CPPUNIT_TEST(test_ev_rr_ss_int_string_11);
CPPUNIT_TEST(test_ev_rr_ss_int_string_22);
CPPUNIT_TEST(test_ev_rr_ss_int_int_01);
CPPUNIT_TEST(test_ev_rr_ss_int_int_10);
CPPUNIT_TEST(test_ev_rr_ss_int_int_11);
CPPUNIT_TEST(test_ev_rr_ss_int_int_22);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_variables_both_modified_and_used();
    void test_ev_rr_ss_string_string_00_from_argOne();
    void test_ev_rr_ss_string_string_01();
    void test_ev_rr_ss_string_string_10();
    void test_ev_rr_ss_string_string_11();
    void test_ev_rr_ss_string_string_22();
    void test_ev_rr_ss_int_string_00_from_argOne();
    void test_ev_rr_ss_int_string_01();
    void test_ev_rr_ss_int_string_10();
    void test_ev_rr_ss_int_string_11();
    void test_ev_rr_ss_int_string_22();
    void test_ev_rr_ss_int_int_01();
    void test_ev_rr_ss_int_int_10();
    void test_ev_rr_ss_int_int_11();
    void test_ev_rr_ss_int_int_22();
};

#endif