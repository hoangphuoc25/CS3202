#ifndef T11_TEST_30_PKB_NextBIP_H
#define T11_TEST_30_PKB_NextBIP_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_30_PKB_NextBIP: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_NextBIP);
CPPUNIT_TEST(test_nextBIP);
CPPUNIT_TEST(test_nextBIP2);
CPPUNIT_TEST(test_nextBIP_if);
CPPUNIT_TEST(test_nextBIP_while);
CPPUNIT_TEST(test_nextBIP_multiproc);
CPPUNIT_TEST(test_nextBipStar);
CPPUNIT_TEST(test_nextBipStar_multiproc);
CPPUNIT_TEST(test_nextBipStar_procback);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_nextBIP();
    void test_nextBIP2();
    void test_nextBIP_if();
    void test_nextBIP_while();
    void test_nextBIP_multiproc();
    void test_nextBipStar();
    void test_nextBipStar_multiproc();
    void test_nextBipStar_procback();
};

#endif