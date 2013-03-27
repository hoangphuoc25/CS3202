#include <list>
#include <set>
#include <string>
#include "Test21_NextAndStar_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_NextAndStar_N2S::setUp()
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
         } \
         procedure useless { \
           call five; \
         }";
}

void Test21_NextAndStar_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_NextAndStar_N2S);

void Test21_NextAndStar_N2S::test_next_syn_X()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Next(syn,int) 0
    queryStr = " call c; Select c such that Next(c,5)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"),
            stringSet);
    queryStr = " while w; Select w such that Next(w,4)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Next(syn,int) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Next(w,21)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"),
            stringSet);
    // Next(syn,_) 0
    queryStr = " call c; Select c such that Next(c,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4", "18"),
            stringSet);
    // Next(syn,_) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Next(w,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "5", "7", "20"),
            stringSet);
}

void Test21_NextAndStar_N2S::test_nextStar_syn_X()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    evaluator.parseSimple(this->SIMPLE_PROG);
    // Next*(syn,int) 0
    queryStr = " assign a; Select a such that Next*(a,4)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1", "3"),
            stringSet);
    queryStr = "stmt s; Select s such that Next*(s,4)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "1", "2", "3"),
            stringSet);
    // Next*(syn,int) 1
    queryStr = " assign a; variable v; ";
    queryStr += " Select a such that Modifies(a,v) and Next*(a,24)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "21", "22"),
            stringSet);
    // Next*(syn,_) 0
    queryStr = "call c; Select c such that Next*(c,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4", "18"),
            stringSet);
    // Next*(syn,_) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Next*(w,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "5", "7", "20"),
            stringSet);
}

void Test21_NextAndStar_N2S::test_next_X_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    evaluator.parseSimple(this->SIMPLE_PROG);
    // Next(int,syn) 0
    queryStr = " while w; Select w such that Next(4,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    queryStr = " assign a; Select a such that Next(4,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Next(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Next(21,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"),
            stringSet);
    // Next(_,syn) 0
    queryStr = " call c; Select c such that Next(_,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4", "18"),
            stringSet);
    // Next(_,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Next(_,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "5", "7", "20"),
            stringSet);
}

void Test21_NextAndStar_N2S::test_nextStar_X_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    evaluator.parseSimple(this->SIMPLE_PROG);
    // Next*(int,syn) 0
    queryStr = " while w; Select w such that Next*(4,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5", "7"),
            stringSet);
    queryStr = " assign a; Select a such that Next*(4,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "6", "8", "10", "11",
            "12", "13", "15", "16", "19"),
            stringSet);
    // Next*(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Next*(21,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"),
            stringSet);
    // Next*(_,syn) 0
    queryStr = " call c; Select c such that Next*(_,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4", "18"),
            stringSet);
    // Next*(_,syn) 1
    queryStr = " if if1; variable v; ";
    queryStr += " Select if1 such that Modifies(if1,v) and Next*(_,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "2", "9", "14", "23"),
            stringSet);
}