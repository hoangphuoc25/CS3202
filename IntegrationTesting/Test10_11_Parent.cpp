#include <list>
#include <set>
#include <string>

#include "Test10_11_Parent.h"
#include "../SPA/QueryEvaluator.h"
#include "../SPA/SetWrapper.h"

using std::list;
using std::set;
using std::string;

void Test10_11_Parent::setUp() {}

void Test10_11_Parent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_11_Parent);

void Test10_11_Parent::test_parent_while_assign()
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
    queryStr = "while w1; variable v1; assign a1; ";
    queryStr += "Select <w1, v1, a1> such that ";
    queryStr += " Modifies(w1, v1) and Modifies(a1, v1) and ";
    queryStr += " Parent(w1, a1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(w1, v1)
    // w1 | v1
    // 4,dont 6,freak 6,date 11,bad 11,useless1 31,useless10
    // ---
    // Modifies(a1, v1)
    // w1 | v1 | a1
    // 4,dont,5 6,freak,7 6,date,23 11,bad,12 11,useless1,10
    // 11,useless1,13 31,useless10,32
    // ---
    // Parent(w1, a1)
    // w1 | v1 | a1
    // 4,dont,5 6,freak,7 11,bad,12 11,useless1,13 31,useless10,32
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "4 dont 5",
            "6 freak 7", "11 bad 12", "11 useless1 13",
            "31 useless10 32"),
            stringSet);
}