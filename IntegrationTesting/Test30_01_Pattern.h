#ifndef T11_TEST30_01_SELECT_PATTERN_H
#define T11_TEST30_01_SELECT_PATTERN_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test30_01_Pattern: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test30_01_Pattern);
//CPPUNIT_TEST(test_select_one_syn);
CPPUNIT_TEST(test_2);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SELECT_ONE_SIMPLEPROG;
    //void test_select_one_syn();
    void test_2();
};

#endif