#include <list>
#include <set>
#include <string>
#include "Test21_ParentAndStar_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_ParentAndStar_N2S::setUp()
{
    this->SIMPLE_PROG =
        "procedure hanoi { \
           first = 13 + a1; \
           if true then { \
             x = abc; \
             call five; \
             while notThis { \
               man = eater; \
               while someCond { \
                 dont = do + this; \
                 if bad then { \
                   great = day; \
                 } else { \
                   bad = day; \
                 } \
                 merge = sort; \
               } \
               hoho = gogo; \
             } \
             if false then { \
               hell = no; \
             } else { \
               hell = yea; \
             } \
           } else { \
             helions = everywhere; \
             call sureFire; \
           } \
           gj = great - job; \
         } \
         procedure sureFire { \
           while smth { \
             you = are + fired; \
           } \
           hat = tin; \
           if bad then { \
             foil = plan; \
           } else { \
             man = fen; \
           } \
         } \
         procedure five { \
           a = b; \
         }";
}

void Test21_ParentAndStar_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_ParentAndStar_N2S);

void Test21_ParentAndStar_N2S::test_parent_X_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Parent(int,syn) 0
    queryStr = "call c; Select c such that Parent(2,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4", "18"),
            stringSet);
    // Parent(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Uses(w,v) and Parent(5,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    // Parent(_,syn) 0
    queryStr = " if if1; Select if1 such that Parent(_,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "9", "14"),
            stringSet);
    // Parent(_,syn) 1
    queryStr = " assign a; if if1; ";
    queryStr += " Select a such that Parent(if1,a) and Parent(_,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "10", "11", "15", "16"),
            stringSet);
}

void Test21_ParentAndStar_N2S::test_parentStar_X_syn()
{
        string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Parent*(int,syn) 0
    queryStr = "while w; Select w such that Parent*(2,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5", "7"),
            stringSet);
    // Parent*(int,syn) 1
    queryStr = " while w; assign a; variable v; ";
    queryStr += " Select a such that Uses(w,v) and Parent*(5,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "6", "8", "10", "11",
            "12", "13"),
            stringSet);
    // Parent*(_,syn) 0
    queryStr = " if if1; Select if1 such that Parent*(_,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "9", "14"),
            stringSet);
    // Parent*(_,syn) 1
    queryStr = " assign a; if if1; ";
    queryStr += " Select a such that Parent(if1,a) and Parent*(_,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "10", "11", "15", "16"),
            stringSet);
}