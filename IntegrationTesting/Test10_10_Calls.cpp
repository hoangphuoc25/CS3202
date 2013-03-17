#include <list>
#include <set>
#include <string>
#include "Test10_10_Calls.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_10_Calls::setUp() {
    SELECT_ONE_SIMPLE_PROG =
        "procedure XProc { \
           a = b; \
           x = z2d; \
           ba = ba + black + sheep; \
           call yProc; \
           while i { \
             black = gold; \
             call godoSmth; \
           } \
           hell = yea; \
         } \
         procedure yProc { \
           no = time; \
           call aaaaa; \
         } \
         procedure godoSmth { \
           call cleanUp; \
           well = done; \
           call X; \
         } \
         procedure aaaaa { \
           aa = abb; \
         } \
         procedure cleanUp { \
           job = done; \
         } \
         procedure X { \
           x = y; \
           call cleanUp; \
         }";
}

void Test10_10_Calls::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_10_Calls);

void Test10_10_Calls::test_calls_10 ()
{
	const string& simpleProg = this->SELECT_ONE_SIMPLE_PROG;
    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

	queryStr = "procedure p, q; variable v;";
	queryStr += "Select p such that Modifies(p, v) and Calls(p, q)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "godoSmth", "XProc", "yProc", "X"));

	queryStr = "procedure p, q, r;";
	queryStr += "Select p such that Calls(p, q) and Calls (q, r)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "godoSmth", "XProc"));
}