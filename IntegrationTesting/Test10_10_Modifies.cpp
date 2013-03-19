#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "Test10_10_Modifies.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void Test10_10_Modifies::setUp()
{
    this->MODIFIES_10_PROG =
        "procedure pOne { \
           px = ty; \
           abc = sun; \
           if t then { \
             sun = rise; \
             while true { \
               heck = it + la; \
             } \
             pipe = dream; \
           } else { \
             dawn = now; \
             while smth { \
               snake = here; \
               if notTrue then { \
                 nobodyUses = 23; \
               } else { \
                 nobodyUses = abcd; \
               } \
             } \
           } \
           my = friend; \
           while germ { \
             sun = no + sun; \
           } \
           great = things; \
           come = hard; \
           call procTwo; \
         } \
         procedure procTwo { \
           hell = no; \
           while fine { \
             dont = heck; \
           } \
           no = go; \
           call procThree; \
         } \
         procedure procThree { \
           man = human; \
           whos = here; \
           hell = yes; \
         }";
}

void Test10_10_Modifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_10_Modifies);

void Test10_10_Modifies::test_modifies_assign_var_10()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_10_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a1, a2; variable v1, v2; ";
    queryStr += " Select <a1,v1,v2> such that Modifies(a1,v1) and ";
    queryStr += " Modifies(a1,v2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27,hell)
    // ---
    // Modifies(a1,v2)
    // a1 | v1
    // (1,px,px), (2,abc,abc), (4,sun,sun), (6,heck,heck), (7,pipe,pipe)
    // (8,dawn,dawn), (10,snake,snake), (12,nobodyUses,nobodyUses)
    // (13,nobodyUses,nobodyUses), (14,my,my), (16,sun,sun),
    // (17,great,great), (18,come,come), (20,hell,hell), (22,dont,dont)
    // (23,no,no), (25,man,man), (26,whos,whos), (27,hell,hell)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "1 px px", "2 abc abc",
            "4 sun sun", "6 heck heck", "7 pipe pipe", "8 dawn dawn",
            "10 snake snake", "12 nobodyUses nobodyUses",
            "13 nobodyUses nobodyUses", "14 my my", "16 sun sun",
            "17 great great", "18 come come", "20 hell hell",
            "22 dont dont", "23 no no", "25 man man", "26 whos whos",
            "27 hell hell"),
            stringSet);
}