#ifndef T11_TEST_HELPER_H
#define T11_TEST_HELPER_H

#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class TestHelper: public CPPUNIT_NS::TestFixture {
public:
    void setUp();
    void tearDown();

protected:
    void compare_string_set(const std::set<std::string>& S, int n, ...) const;
};

#endif