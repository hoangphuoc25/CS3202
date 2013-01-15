#ifndef T11_TEST_INTEGRATION_MODIFIES_H
#define T11_TEST_INTEGRATION_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class TestModifies: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestModifies);
CPPUNIT_TEST(test_modifies_single);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void compare_string_set(const std::set<std::string>& S, int n, ...) const;
    void test_modifies_single();
};

#endif