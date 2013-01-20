#ifndef T11_TEST_10_PARENT_H
#define T11_TEST_10_PARENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_10_Parent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_10_Parent);
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