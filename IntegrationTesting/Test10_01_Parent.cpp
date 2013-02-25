#include <list>
#include <set>
#include <string>

#include "Test10_01_Parent.h"
#include "../SPA/QueryEvaluator.h"
#include "../SPA/SetWrapper.h"

using std::list;
using std::set;
using std::string;

void Test10_01_Parent::setUp() {}

void Test10_01_Parent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Parent);

void Test10_01_Parent::test_parent_if_assign()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure progAnalyse { \
           ax = bc - seventy; \
           if conVar then { \
             call chopList; \
             while itsTrue { \
               dont = know; \
             } \
             while notTrue { \
               freak = man; \
               call chopList; \
             } \
           } else { \
             call chopList; \
           } \
           useless1 = 123; \
           while itsTrue { \
             bad = ax; \
             useless1 = 424 - 311; \
           } \
           mutiny = board; \
           if notTrue then { \
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
           } else { \
             useless2 = 14; \
           } \
         } \
         procedure chopList { \
           date = date; \
         } \
         procedure Aone { \
           if notTrue then { \
             if itsTrue then { \
               call chopList; \
             } else { \
               useless8 = 9; \
             } \
           } else { \
             call chopList; \
           } \
           useless3 = useless4; \
           if true then { \
             while useless8 { \
               useless10 = 101; \
             } \
           } else { \
             abc = xyz; \
           } \
         } \
         ";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a1; variable v1; if if1; ";
    queryStr += " Select <a1,v1,if1> such that ";
    queryStr += " Modifies(a1,v1) and Parent(if1,a1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // 1,ax 5,dont 7,freak 10,useless1 12,bad 13,useless1
    // 14,mutiny 16,useless2 18,useless4 20,useless5 21,useless6
    // 22,useless2 23,date 27,useless8 29,useless3 32,useless10 33,abc
    // ---
    // Parent(if1, a1)
    // a1 | v1 | if1
    // 16,useless2,15 18,useless4,17 20,useless5,19 21,useless6,19
    // 22,useless2,15 27,useless8,25 33,abc,30
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "16,useless2,15",
            "18,useless4,17", "20,useless5,19", "21,useless6,19",
            "22,useless2,15", "27,useless8,25", "33,abc,30"),
            stringSet);
}