#include <list>
#include <set>
#include <string>
#include "Test21_AffectsAndStar_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_AffectsAndStar_N2S::setUp()
{
}

void Test21_AffectsAndStar_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_AffectsAndStar_N2S);

void Test21_AffectsAndStar_N2S::test_affects_X_syn()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           a = b; \
           x = y; \
           g = a; \
           if true then { \
             fine = x; \
           } else { \
             gj = x; \
             call procTwo; \
             smth = x; \
           } \
           fire = x; \
           b = 17; \
           x = a; \
           if false then { \
             gait = x; \
             call procTwo; \
             smth = x; \
           } else { \
             err = x; \
             call procTwo; \
             gg = x; \
           } \
           someVar = x; \
         } \
         procedure procTwo { \
           justice = served; \
           x = 52; \
           while someCond { \
             well = x; \
           } \
           g = bad; \
           while anotherCond { \
             dude = 6789; \
           } \
           f = gad; \
           while acond { \
             x = x; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    // Affects(int,syn) 0
    queryStr = "assign a; Select a such that Affects(1,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "11"),
            stringSet);
    // Affects(int,syn) 1
    queryStr = " while w; assign a; Select a such that Parent(w,a) and ";
    queryStr += " Affects(29,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "29"),
            stringSet);
    // Affects(_,syn) 0
    queryStr = "assign a; Select a such that Affects(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "6", "9", "11",
            "13", "16", "23", "29"),
            stringSet);
    // Affects(_,syn) 1
    queryStr = " while w; assign a; Select a such that Parent(w,a) and ";
    queryStr += " Affects(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "23", "29"),
            stringSet);
}

void Test21_AffectsAndStar_N2S::test_affectsStar_X_syn()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           a = b; \
           x = y; \
           b = c; \
           d = b; \
           xe = 5; \
           while smth { \
             y = man; \
           } \
           crux = x; \
           if acond then { \
             jack = d; \
             call doneProc; \
           } else { \
             fate = lands; \
             jack = d; \
           } \
           avar = jack; \
           if acond then { \
             lucky = avar; \
             call judo; \
           } else { \
             lucky = pal; \
             call judo; \
           } \
           gambler = lucky; \
           goo = y; \
           while damned { \
             jam = y; \
             freak = goo ;\
           } \
           code = jam; \
         } \
         procedure judo { \
           lucky = house; \
         } \
         procedure doneProc { \
           jack = 5; \
           while smth { \
             hope = cycle; \
             cycle = craps; \
             craps = hope; \
           } \
           arabia = 56; \
           while smth { \
             hope = cycle; \
             cycle = craps; \
             craps = poker; \
             craps = cycle; \
           } \
         }";

    evaluator.parseSimple(simpleProg);
    // Affects*(int,syn) 0
    queryStr = " assign a; Select a such that Affects*(3,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "4", "10", "13",
            "14", "16"),
            stringSet);
    // Affects*(int,syn) 1
    queryStr = " while w; assign a; ";
    queryStr += " Select a such that Parent(w,a) and ";
    queryStr += " Affects*(7,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "23", "24"),
            stringSet);
    // Affects*(_,syn) 0
    queryStr = " assign a; Select a such that Affects*(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "4", "8", "10", "13",
            "14", "16", "21", "23", "24", "25", "29", "30", "31",
            "34", "35", "37"),
            stringSet);
    // Affects*(_,syn) 1
    queryStr = " if if1; assign a; ";
    queryStr += " Select a such that Parent(if1,a) and Affects*(_,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "13", "16"),
            stringSet);
}