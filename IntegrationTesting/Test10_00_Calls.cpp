#include <list>
#include <set>
#include <string>
#include "Test10_00_Calls.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_00_Calls::setUp()
{
    // call stmt
    // Procedure xProc
    // 4 [yProc], 7 [godoSmth]
    // Procedure yProc
    // 10 [aaaaa]
    // Procedure godoSmth
    // 11 [cleanUp], 13 [X], 14 [XProc]
    // Procedure aaaaa
    // N/A
    // Procedure cleanUp
    // N/A
    // Procedure X
    // 18 [cleanUp]
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

    // call stmt
    // Procedure xProc
    // 4 [yProc], 7 [godoSmth]
    // Procedure yProc
    // 10 [aaaaa]
    // Procedure godoSmth
    // 11 [cleanUp], 13 [X], 14 [XProc]
    // Procedure aaaaa
    // N/A
    // Procedure cleanUp
    // N/A
    // Procedure X
    // 18 [cleanUp]
}

void Test10_00_Calls::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_Calls);

void Test10_00_Calls::test_select_one_syn()
{
    const string simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;
    
    queryStr = "procedure p, q;";
    queryStr += "Select p such that Calls(p, q)";
    // Calls(p, q)
    // p | q
    // XProc,YProc YProc,aaaa godoSmth,cleanUp godoSmth,X godoSmth,XProc X,cleanUp
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "XProc", "yProc", "godoSmth", "X"));

    queryStr = "procedure p, q; variable v;";
    queryStr += "Select q such that Calls(p, q) and Modifies(q, v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(5, "godoSmth", "cleanUp", "yProc", "X", "aaaaa"));
}