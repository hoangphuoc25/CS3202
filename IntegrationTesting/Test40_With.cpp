#include <list>
#include <set>
#include <string>
#include "Test40_With.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test40_With::setUp()
{
    this->IIProc =
        "procedure A { \
           a = b; \
           call Bob; \
           if true then { \
             x = y; \
             call Bob; \
             while false { \
               one = two; \
             } \
             mes = si; \
           } else { \
             des = cartes; \
           } \
           poly = gon; \
         } \
         procedure Bob { \
           while fine { \
             sun = day; \
           } \
           tgif = friday; \
         }";
}

void Test40_With::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test40_With);

void Test40_With::test_ii_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; stmt s; ";
    queryStr += " Select <a,s> with a.stmt# = s.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // 1, 4, 7, 8, 9, 10, 12, 13
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "1 1", "4 4", "7 7",
            "8 8", "9 9", "10 10", "12 12", "13 13"),
            stringSet);
}

void Test40_With::test_ii_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "call c; prog_line pl; ";
    queryStr += " Select c such that Modifies(pl,_) with c.stmt# = pl";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2", "5"),
            stringSet);
}

void Test40_With::test_ii_10()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "if if1; prog_line pl; ";
    queryStr += " Select if1 such that Parent(if1,_) ";
    queryStr += " with if1.stmt# = pl.prog_line#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
}

void Test40_With::test_ii_11()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w; prog_line pl; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Modifies(pl, v)";
    queryStr += " with w.stmt# = pl.prog_line#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6", "11"),
            stringSet);
}

void Test40_With::test_ii_22()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w; prog_line pl; ";
    queryStr += " Select w such that Parent(w,_) and ";
    queryStr += " Modifies(pl, _)";
    queryStr += " with pl.prog_line# = w.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6", "11"),
            stringSet);
}