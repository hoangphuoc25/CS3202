#include <list>
#include <set>
#include <string>
#include "Test10_01_Calls.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_01_Calls::setUp() {
    SELECT_ONE_SIMPLEPROG =
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

void Test10_01_Calls::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Calls);

void  Test10_01_Calls::test_select_calls_01() {
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

    queryStr = "procedure p, q; variable v;";
    queryStr += "Select p such that Modifies(p, v) and Calls(q, p)";
	// Calls(p, q)
    // p | q
    // XProc,YProc YProc,aaaa godoSmth,cleanUp godoSmth,X X,cleanUp
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(5, "aaaaa", "godoSmth", "yProc", "cleanUp", "X"));

	queryStr = "procedure p, q, r;";
	queryStr += "Select p such that Calls(p, r) and Calls(q, p)";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "X", "godoSmth", "yProc"));
}