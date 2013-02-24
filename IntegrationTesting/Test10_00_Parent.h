#ifndef T11_TEST10_00_PARENT_H
#define T11_TEST10_00_PARENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Parent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Parent);
CPPUNIT_TEST(test_parent_while_assign);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SELECT_ONE_SIMPLEPROG;
    void test_parent_while_assign();
};

#endif