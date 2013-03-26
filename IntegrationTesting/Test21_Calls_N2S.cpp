#include <list>
#include <set>
#include <string>
#include "Test21_Calls_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_Calls_N2S::setUp() {}

void Test21_Calls_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_Calls_N2S);

void Test21_Calls_N2S::test_calls_string_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure fSharp { \
           call CSharp; \
         } \
         procedure CSharp { \
           call Java; \
         } \
         procedure Java { \
           assign = var; \
         }";
    evaluator.parseSimple(simpleProg);
    // Correct calls
    queryStr = "Select BOOLEAN such that Calls(\"fSharp\", \"CSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls(\"CSharp\", \"Java\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Non-existent calls
    queryStr = "Select BOOLEAN such that Calls(\"CSharp\", \"fSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls(\"Java\", \"fSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Calls_N2S::test_calls_string_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure fSharp { \
           call CSharp; \
         } \
         procedure CSharp { \
           call Java; \
         } \
         procedure Java { \
           assign = var; \
         }";
    evaluator.parseSimple(simpleProg);
    // Correct calls
    queryStr = "Select BOOLEAN such that Calls(\"fSharp\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls(\"CSharp\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Non-existent call
    queryStr = "Select BOOLEAN such that Calls(\"noSuchProc\", \"fSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                               ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Calls_N2S::test_calls_wild_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure fSharp { \
           call CSharp; \
         } \
         procedure CSharp { \
           call Java; \
         } \
         procedure Java { \
           assign = var; \
         }";
    evaluator.parseSimple(simpleProg);
    // Correct calls
    queryStr = "Select BOOLEAN such that Calls(_,\"CSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls(_,\"Java\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Non-existent calls
    queryStr = "Select BOOLEAN such that Calls(_,\"fSharp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls(_,\"noSuchProc\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Calls_N2S::test_calls_wild_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure fSharp { \
           call CSharp; \
         } \
         procedure CSharp { \
           call Java; \
         } \
         procedure Java { \
           assign = var; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Calls(_,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);

    // 1 call statement
    simpleProg =
        "procedure A { \
           call B; \
         } \
         procedure B { \
           a = b; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Calls(_,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);

    // No calls statement at all
    simpleProg =
        "procedure Astar { \
           search = is + futile; \
         } \
         procedure Bstar { \
           if b then { \
             a = is + not - good; \
           } else { \
             a = is + good; \
           } \
           my = friend; \
         }  \
         procedure DeathStar { \
           anakin = skywalker; \
           while true { \
             darth = vader; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Calls(_,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Calls_N2S::test_calls_X_syn()
{
    string queryStr, simpleProg;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           call B; \
           call C; \
         } \
         procedure B { \
           a = x; \
           } \
         procedure C { \
           call D; \
         } \
         procedure D { \
           call B; \
         } \
         procedure E { \
           gg = gg; \
         }";
    evaluator.parseSimple(simpleProg);
    // Calls(string,syn) 0
    queryStr = "procedure p; Select p such that Calls(\"A\", p)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "B", "C"),
            stringSet);
    // Calls(string,syn) 1
    queryStr = "procedure p; variable v; ";
    queryStr += " Select p such that Uses(p,v) and Calls(\"C\",p)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "D"),
            stringSet);
    // Calls(_,syn) 0
    queryStr = "procedure p; Select p such that Calls(_,p)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "B", "C", "D"),
            stringSet);
    // Calls(_,syn) 1
    queryStr = "procedure p; variable v; ";
    queryStr += " Select p such that Uses(p,v) and Calls(_,p)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "B", "C", "D"),
            stringSet);
}