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