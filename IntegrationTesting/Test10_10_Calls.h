#ifndef T11_TEST10_10_CALLS_H
#define T11_TEST10_10_CALLS_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_10_Calls: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_10_Calls);
CPPUNIT_TEST(test_calls_10);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
	std::string SELECT_ONE_SIMPLE_PROG;
	void test_calls_10();
};

#endif