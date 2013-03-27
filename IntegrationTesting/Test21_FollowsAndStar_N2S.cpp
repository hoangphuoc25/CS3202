#include <list>
#include <set>
#include <string>
#include "Test21_FollowsAndStar_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_FollowsAndStar_N2S::setUp()
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

void Test21_FollowsAndStar_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_FollowsAndStar_N2S);

void Test21_FollowsAndStar_N2S::test_follows_syn_X()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Follows(syn,int) 0
    queryStr = " call c; Select c such that Follows(c,5)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"),
            stringSet);
    queryStr = " assign a; Select a such that Follows(a,5)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Follows(syn,int) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Follows(w,22)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"),
            stringSet);
    // Follows(syn,_) 0
    queryStr = " assign a; Select a such that Follows(a,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1", "3", "6", "8",
            "17", "22"),
            stringSet);
    // Follows(syn,_) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Follows(w,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "5", "7", "20"),
            stringSet);
}

void Test21_FollowsAndStar_N2S::test_followsStar_syn_X()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Follows*(syn,int) 0
    queryStr = " call c; Select c such that Follows*(c,5)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"),
            stringSet);
    queryStr = " assign a; Select a such that Follows*(a,5)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    // Follows*(syn,int) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Follows*(w,22)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"),
            stringSet);
    // Follows*(syn,_) 0
    queryStr = " assign a; Select a such that Follows*(a,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1", "3", "6", "8",
            "17", "22"),
            stringSet);
    // Follows*(syn,_) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Follows*(w,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "5", "7", "20"),
            stringSet);
}

void Test21_FollowsAndStar_N2S::test_follows_X_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Follows(int,syn) 0
    queryStr = " while w; Select w such that Follows(4,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    queryStr = " assign a; Select a such that Follows(4,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Follows(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Follows(6,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    // Follows(_,syn) 0
    queryStr = " assign a; Select a such that Follows(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "12", "13", "19", "22"),
            stringSet);
    // Follows(_,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Follows(_,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5", "7"),
            stringSet);
}

void Test21_FollowsAndStar_N2S::test_followsStar_X_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    evaluator.parseSimple(this->SIMPLE_PROG);
    // Follows*(int,syn) 0
    queryStr = " if if1; Select if1 such that Follows*(4,if1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    queryStr = " assign a; Select a such that Follows*(4,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Follows*(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Follows*(6,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    queryStr = " stmt s; variable v; ";
    queryStr += " Select s such that Modifies(s,v) and ";
    queryStr += " Follows*(6,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"),
            stringSet);
    // Follows*(_,syn) 0
    queryStr = " assign a; Select a such that Follows*(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "12", "13", "19", "22"),
            stringSet);
    // Follows*(_,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and Follows*(_,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5", "7"),
            stringSet);
}