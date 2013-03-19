#include <list>
#include <set>
#include <string>
#include "Test60_Evil.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test60_Evil::setUp()
{
    this->BASIC_PROG =
        "procedure g1 { \
           a = 1; \
           if bad then { \
             while true { \
               x = x + 1; \
             } \
             nipah = virus; \
           } else { \
             gain = time; \
           } \
           sand = man; \
         } \
         procedure g2 { \
           hell = cell; \
           call g1; \
           while someCond { \
             g = g + 2; \
           } \
           done = day; \
         } \
         procedure gitmain { \
           dry = land; \
           sheep = herd; \
           if youAreSheep then { \
             good = luck; \
           } else { \
             good = day; \
           } \
           follow = here; \
         }";

    this->NOWHILE_PROG =
        "procedure One { \
           arm = good; \
           blaster = laster; \
         } \
         procedure Two { \
           if true then { \
             cat = bad; \
           } else { \
             dog = pet; \
           } \
         } \
         procedure Three { \
           eva = lu + ator; \
         }";
}

void Test60_Evil::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test60_Evil);

void Test60_Evil::test_select_boolean_no_clause()
{
    const string& simpleProg = this->BASIC_PROG;
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    evaluator.parseSimple(simpleProg);
    queryStr = " Select BOOLEAN";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
}

void Test60_Evil::test_select_a_a()
{
    const string& simpleProg = this->BASIC_PROG;
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; Select <a,a>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "1,1", "4,4", "5,5",
            "6,6", "7,7", "8,8", "11,11", "12,12", "13,13", "14,14",
            "16,16", "17,17", "18,18"),
            stringSet);
}

void Test60_Evil::test_select_a1_a2()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->NOWHILE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a1, a2; Select <a1,a2>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(25, "1,1", "1,2", "1,4",
            "1,5", "1,6", "2,1", "2,2", "2,4", "2,5", "2,6", "4,1",
            "4,2", "4,4", "4,5", "4,6", "5,1", "5,2", "5,4", "5,5",
            "5,6", "6,1", "6,2", "6,4", "6,5", "6,6"),
            stringSet);
}

void Test60_Evil::test_select_while__no_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->NOWHILE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w; Select w";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test60_Evil::test_select_assign_while__no_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->NOWHILE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w123; assign ahh; Select <ahh,w123>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test60_Evil::test_select_assign_while_true_query__no_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->NOWHILE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w123; assign ahh; variable v; ";
    queryStr += " Select <ahh,w123> such that Modifies(ahh,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test60_Evil::test_sx()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg = "procedure Aproc { x = 1; b = 2; } ";
    simpleProg += " procedure Bproc { uy = 2; y = a + b; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " procedure p; variable v; ";
    queryStr += " Select p such that Modifies(p,v) and ";
    queryStr += " Modifies(p, \"x\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "Aproc"),
            stringSet);
    simpleProg = "procedure bab { x = 1; }";
    simpleProg += " procedure Bproc { call bab; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " procedure p; variable v; ";
    queryStr += " Select p such that Modifies(p,v) and ";
    queryStr += " Modifies(p, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bab", "Bproc"),
            stringSet);
    simpleProg = "procedure A { first = 2; second = 3; } ";
    simpleProg += " procedure B { x = y; first = gd; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a; variable v; ";
    queryStr += " Select a such that Modifies(a,v) and ";
    queryStr += " Modifies(a,\"first\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1", "4"),
            stringSet);
    simpleProg = "procedure A { first = 2; second = 3; } ";
    simpleProg += " procedure B { x = y; first = gd; call A; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a; variable v; ";
    queryStr += " Select a such that Modifies(a,v) and ";
    queryStr += " Modifies(a, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "1", "2", "3", "4"),
            stringSet);
    simpleProg = "procedure A { x = 1; while p { g = y; } } ";
    simpleProg += " procedure B { while xx { g = 17; } } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Parent(w, 3)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);
    // syn_X (string,string) 0
    simpleProg = "procedure uik { jut = 3; a = 1; } ";
    simpleProg += " procedure B { suck = it; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " procedure p; ";
    queryStr += " Select p such that Modifies(p, \"jut\")  ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "uik"),
            stringSet);
    // syn_X (string,_) 0
    simpleProg = "procedure xkb { jut = 3; a = bad; } ";
    simpleProg += "procedure Y { sgag = 33 - 45; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " procedure p; ";
    queryStr += " Select p such that Uses(p, _)  ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xkb"),
            stringSet);
    // syn_X (int,string) 0
    simpleProg = "procedure p1 { just = pl; hell = no; } ";
    simpleProg += "procedure p2 { a = 55; just = now; } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a; ";
    queryStr += " Select a such that Modifies(a, \"just\")  ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1", "4"),
            stringSet);
    // syn_X (int,_) 0
    simpleProg = "procedure p1 { a = 1; while x { a = sy ; } ";
    simpleProg += " while true { while x { a = b; } } a = 2; }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a; ";
    queryStr += " Select a such that Uses(a, _)  ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "6"),
            stringSet);
    // syn_X (int,int) 0
    simpleProg = "procedure p1 { a = b; while x { a = 3; b = 4; } } ";
    simpleProg += " procedure p2 { x = y; while p { as = sgg; } } ";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w; ";
    queryStr += " Select w such that Parent(w, 4)  ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);
}