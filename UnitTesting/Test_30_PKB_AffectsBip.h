#ifndef T11_TEST_30_PKB_AFFECTS_BIP_H
#define T11_TEST_30_PKB_AFFECTS_BIP_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_30_PKB_AffectsBip: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_AffectsBip);
CPPUNIT_TEST(test_AffectsBip);
CPPUNIT_TEST(test_AffectsBip_multiproc);
CPPUNIT_TEST(test_AffectsBip_procBack);
CPPUNIT_TEST(test_AffectsBip_affectedby);
CPPUNIT_TEST(test_AffectsBipStar);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_AffectsBip();
    void test_AffectsBip_multiproc();
    void test_AffectsBip_procBack();
    void test_AffectsBip_affectedby();
    void test_AffectsBipStar();
};

#endif