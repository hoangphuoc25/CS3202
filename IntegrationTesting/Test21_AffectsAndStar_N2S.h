#ifndef T11_TEST21_AFFECTSANDSTAR_N2S_H
#define T11_TEST21_AFFECTSANDSTAR_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Affects and Affects* Relation with 0 or 1
 * synonym arguments.
 */
class Test21_AffectsAndStar_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_AffectsAndStar_N2S);
CPPUNIT_TEST(test_affects_X_syn);
CPPUNIT_TEST(test_affectsStar_X_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_affects_X_syn();
    void test_affectsStar_X_syn();
};

#endif