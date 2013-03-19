#include <list>
#include <set>
#include <string>
#include "Test10_22_Uses.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_22_Uses::setUp() {}

void Test10_22_Uses::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_22_Uses);

void Test10_22_Uses::test_uses_while_var()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure progAnalyse { \
           ax = bc - seventy; \
           while conVar { \
             call chopList; \
             while itsTrue { \
               dont = know; \
             } \
             while notTrue { \
               freak = man; \
               call chopList; \
             } \
           } \
           useless1 = 123; \
           while itsTrue { \
             bad = ax; \
             useless1 = 424 - 311; \
           } \
           mutiny = board; \
           while notTrue { \
             useless2 = 15; \
             if useless3 then { \
               useless4 = 125; \
             } else { \
               if mutiny then { \
                 useless5 = 1676; \
               } else { \
                 useless6 = 15 * 41; \
               } \
             } \
           } \
         } \
         procedure chopList { \
           date = date; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w1; assign a1, a2; variable v1, v2; ";
    queryStr += " Select <w1,a1,a2,v1> such that ";
    queryStr += " Parent(w1, a1) and Modifies(a2, v1) and ";
    queryStr += " Uses(w1, v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Parent(w1,a1)
    // w1 | a1
    // 4,5 6,7 10,11 10,12 14,15
    // ---
    // Modifies(a2,v1)
    // a2 | v1
    // 1,ax 5,dont 7,freak 9,useless1 11,bad 12,useless1
    // 13,mutiny 15,useless2 17,useless4 19,useless5 20,useless6
    // 21,date
    // ---
    // Uses(w1,v1)
    // w1 | a1 | a2 | v1
    // 10,11,1,ax 10,12,1,ax 14,15,13,mutiny 6,7,21,date
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "10 11 1 ax",
            "10 12 1 ax", "14 15 13 mutiny", "6 7 21 date"),
            stringSet);
}