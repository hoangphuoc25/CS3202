#ifndef T11_TEST10_10_MODIFIES_H
#define T11_TEST10_10_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_10_Modifies: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_10_Modifies);
CPPUNIT_TEST(test_modifies_assign_var_10);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_modifies_assign_var_10();
    std::string MODIFIES_10_PROG;
};

#endif