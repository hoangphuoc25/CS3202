#include <list>
#include <set>
#include <string>

#include "Test10_10_Parent.h"
#include "../SPA/QueryEvaluator.h"
#include "../SPA/SetWrapper.h"

using std::list;
using std::set;
using std::string;

void Test10_10_Parent::setUp() {}

void Test10_10_Parent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_10_Parent);

void Test10_10_Parent::test_parent_while_call()
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
    queryStr = "while w1; variable v1; call c1; ";
    queryStr += "Select <w1, v1, c1> such that ";
    queryStr += " Modifies(w1, v1) and Parent(w1, c1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6 date 8",
            "6 freak 8"),
            stringSet);
}