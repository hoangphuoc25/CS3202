#ifndef T11_TEST_INTEGRATION_MODIFIES_H
#define T11_TEST_INTEGRATION_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include "TestHelper.h"

class TestModifies: public TestHelper {
CPPUNIT_TEST_SUITE(TestModifies);
CPPUNIT_TEST(test_modifies_single);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_modifies_single();
};

#endif