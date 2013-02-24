#ifndef T11_TEST10_00_SELECT_CALLS_H
#define T11_TEST10_00_SELECT_CALLS_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Calls: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Calls);
CPPUNIT_TEST(test_select_one_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SELECT_ONE_SIMPLEPROG;
    void test_select_one_syn();
};

#endif