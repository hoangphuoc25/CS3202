#include <cstdarg>
#include "TestHelper.h"

using std::set;
using std::string;

void TestHelper::setUp() {}
void TestHelper::tearDown() {}

void TestHelper::compare_string_set(const set<string>& S, int n, ...) const
{
    int expectedSize = (int)S.size();
    CPPUNIT_ASSERT_EQUAL(expectedSize, n);
    set<string> tmpSet;
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        string str = string(va_arg(ap, char *));
        CPPUNIT_ASSERT_EQUAL(1, (int)S.count(str));
        CPPUNIT_ASSERT_EQUAL(0, (int)tmpSet.count(str));
        tmpSet.insert(str);
    }
    CPPUNIT_ASSERT_EQUAL(expectedSize, (int)tmpSet.size());
    va_end(ap);
}