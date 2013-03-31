#ifndef T11_TEST40_WITH_H
#define T11_TEST40_WITH_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test40_With: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test40_With);
CPPUNIT_TEST(test_ii_00);
CPPUNIT_TEST(test_ii_01);
CPPUNIT_TEST(test_ii_10);
CPPUNIT_TEST(test_ii_11);
CPPUNIT_TEST(test_ii_22);
CPPUNIT_TEST(test_ss_cpn_cpn_00);
CPPUNIT_TEST(test_ss_cpn_X_00);
CPPUNIT_TEST(test_ss_00);
CPPUNIT_TEST(test_ss_cpn_cpn_01);
CPPUNIT_TEST(test_ss_cpn_X_01);
CPPUNIT_TEST(test_ss_cpn_X_10);
CPPUNIT_TEST(test_ss_01);
CPPUNIT_TEST(test_ss_cpn_cpn_11);
CPPUNIT_TEST(test_ss_cpn_X_11);
CPPUNIT_TEST(test_ss_11);
CPPUNIT_TEST(test_ss_cpn_cpn_22);
CPPUNIT_TEST(test_ss_cpn_X_22);
CPPUNIT_TEST(test_ss_22);
CPPUNIT_TEST(test_i_0);
CPPUNIT_TEST(test_i_1);
CPPUNIT_TEST(test_s_0);
CPPUNIT_TEST(test_cpn_0);
CPPUNIT_TEST(test_s_1);
CPPUNIT_TEST(test_cpn_1);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string IIProc;
    std::string CALL_PROC;

    /// Test with clause with both arguments being AttrRef int
    /// and not seen
    void test_ii_00();
    /// Test with clause with both arguments being AttrRef int
    /// and arg 2 was seen
    void test_ii_01();
    /// Test with clause with both arguments being AttrRef int
    /// and arg 1 was seen
    void test_ii_10();
    /// Test with clause with both arguments being AttrRef int
    /// and both args were seen in same Table
    void test_ii_11();
    /// Test with clause with both arguments being AttrRef int
    /// and both args were seen but in different Table
    void test_ii_22();
    /// Test with clause with both arguments being call.procName
    /// and not seen
    void test_ss_cpn_cpn_00();
    /// Test with clause with arg 1 being call.procName and
    /// arg 2 a string RefSynType (not call.procName), both unseen
    void test_ss_cpn_X_00();
    /// Test with clause with both args being string RefSynType
    /// (not call.procName), both unseen
    void test_ss_00();
    /// Test with clause with both arguments being call.procName
    /// and arg 2 is seen
    void test_ss_cpn_cpn_01();
    /// Test with clause with arg 1 being call.procName and
    /// arg 2 a string RefSynType (not call.procName), arg 2 seen
    void test_ss_cpn_X_01();
    /// Test with clause with arg 1 being call.procName and
    /// arg 2 a string RefSynType (not call.procName), arg 1 seen
    void test_ss_cpn_X_10();
    /// Test with clause with both args being string RefSynType
    /// (not call.procName), arg 2 seen
    void test_ss_01();
    /// Test with clause with both arguments being call.procName
    /// and seen in same Table
    void test_ss_cpn_cpn_11();
    /// Test with clause with arg 1 being call.procName and
    /// arg 2 a string RefSynType (not call.procName), both seen
    /// in same Table
    void test_ss_cpn_X_11();
    /// Test with clause with both args being string RefSynType
    /// (not call.procName), both seen in same Table
    void test_ss_11();
    /// Test with clause with both arguments being call.procName
    /// and seen in different Table
    void test_ss_cpn_cpn_22();
    /// Test with clause with arg 1 being call.procName and
    /// arg 2 a string RefSynType (not call.procName), both seen
    /// but in different Table
    void test_ss_cpn_X_22();
    /// Test with clause with both args being string RefSynType
    /// (not call.procName), both seen in but in different Table
    void test_ss_22();
    /// Test with clause where arg 1 is unseen int AttrRef and
    /// arg 2 is concrete integer value
    void test_i_0();
    /// Test with clause where arg 1 is seen int AttrRef and
    /// arg 2 is concrete integer value
    void test_i_1();
    /// Test with clause where arg 1 is unseen string AttrRef
    /// (not call.procName) and arg 2 is concrete string value
    void test_s_0();
    /// Test with clause where arg 1 is call.procName and arg 2
    /// is concrete string value
    void test_cpn_0();
    /// Test with clause where arg 1 is seen string AttrRef
    /// (not call.procName) and arg 2 is concrete string value
    void test_s_1();
    /// Test with clause where arg 1 is call.procName and arg 2
    /// is concrete string value
    void test_cpn_1();
};

#endif