#include <list>
#include <set>
#include <string>

#include "Test_10_Parent.h"
#include "../SPA/QueryEvaluator.h"
#include "../SPA/SetWrapper.h"

using std::list;
using std::set;
using std::string;

void Test_10_Parent::setUp()
{
    // stmt 2 [while]
    //   assign: 3, 22
    //   if: 4
    // line 4 [if]
    //   assign: 5, 6, 16
    //   if: 7, 17
    // line 7 [if]
    //   assign: 8, 12, 13
    //   while: 9, 14
    // line 9 [while]
    //   call: 10
    //   assign: 11
    // line 14 [while]
    //   assign: 15
    // line 17 [if]
    //   assign: 18
    //   while: 19
    // line 19 [while]
    //   call: 20
    //   assign: 21
    // line 24 [while]
    //   assign: 25, 26
    //   if: 27
    // line 27 [if]
    //   assign: 28, 29
    // line 31 [while]
    //   if: 32
    // line 32 [if]
    //   assign: 33, 34
    // line 35 [if]
    //   while: 36, 39
    //   call: 38
    // line 36 [while]
    //   assign: 37
    // line 39 [while]
    //   assign: 40
    this->SELECT_ONE_SIMPLEPROG =
        "procedure pOne { \
           a = b;\
           while good { \
             damn = it; \
             if hell then { \
               try = x; \
               follow = star; \
               if gg then { \
                 get = lost; \
                 while p { \
                   call QQ; \
                   q = xp; \
                 } \
                 dang = it; \
               } else { \
                 fun = times; \
                 while aa { \
                   stuff = lost; \
                 } \
               } \
               lol = lol; \
             } else { \
               if true then { \
                 dont = go; \
               } else { \
                 while go { \
                   call prq; \
                   forecast = cloudy; \
                 } \
               } \
             } \
             low = blow; \
           } \
           blast = off; \
         } \
         procedure QQ { \
           while par { \
             find = stuff; \
             great = food; \
             if pal then { \
               drive = by; \
             } else { \
               owe = money; \
             } \
           } \
         } \
         procedure prq { \
           last = assign; \
         } \
         procedure whileNoAssign { \
           while x { \
             if ab then { \
               a = a; \
             } else { \
               b = b; \
             } \
           } \
         } \
         procedure ifNoAssign { \
           if i then { \
             while g { \
               f = f; \
             } \
             call whileNoAssign; \
           } else { \
             while f { \
               g = g; \
             } \
           } \
         } \
         ";
}

void Test_10_Parent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_10_Parent);

void Test_10_Parent::test_select_one_syn()
{
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    evaluator.parseSimple(simpleProg);

    // Parent(while,assign)
    queryStr = " while hty; assign Msq; Select hty such that ";
    queryStr += " Parent(hty, Msq)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(7, "2", "9",
            "14", "19", "24", "36", "39"));
}