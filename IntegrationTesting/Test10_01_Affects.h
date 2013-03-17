#ifndef T11_TEST10_01_AFFECTS_H
#define T11_TEST10_01_AFFECTS_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_01_Affects: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_01_Affects);
CPPUNIT_TEST(test_affects_stmt_01);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_affects_stmt_01();
    std::string AFFECTS_01_PROG;
};

#endif