#include <list>
#include <set>
#include <string>
#include "Test30_PatCl_If.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test30_PatCl_If::setUp() {}

void Test30_PatCl_If::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test30_PatCl_If);

void Test30_PatCl_If::test_if_var_syn_11()
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
             if itsTrue then { \
               dont = know; \
               damn = itsTrue; \
             } else { \
               useless = 8; \
             } \
             if strong then { \
               freak = man; \
               call chopList; \
             } else { \
               useless = 9; \
             } \
           } \
           useless1 = 123; \
           if itsTrue then { \
             bad = ax; \
             useless1 = 424 - 311; \
           } else { \
             useless1 = 15; \
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
                 useless6 = notTrue; \
               } \
             } \
           } else { \
             useless = 1516 - 12; \
           } \
         } \
         procedure chopList { \
           date = date; \
           if bad then { \
             useless6 = 124; \
           } else { \
             useless6 = bad; \
           } \
           useless6 = strong; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " if if1 ; variable v2; ";
    queryStr += " Select <if1,v2> such that Uses(if1,v2) ";
    queryStr += " pattern if1 (v2,  _,  _) ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Uses(if1, v2)
    // if1 | v2
    // 4,itsTrue 4,know 8,man 8,date 8,bad 8,strong
    // 13,itsTrue 13,ax 18,notTrue 18,useless3 18,mutiny
    // 20,useless3 20,mutiny 20,notTrue 22,mutiny 22,notTrue
    // 28,bad
    // ---
    // pattern if1(v2,_,_)
    // if1 | v2
    // 4,itsTrue 8,strong 13,itsTrue 18,notTrue 20,useless3
    // 22,mutiny 28,bad
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "4,itsTrue",
            "8,strong", "13,itsTrue", "18,notTrue", "20,useless3",
            "22,mutiny", "28,bad"),
            stringSet);

    queryStr = " if if1; assign a1; variable v2; ";
    queryStr += " Select <if1,a1,v2> such that Parent(if1, a1) and ";
    queryStr += " Uses(a1, v2)  pattern if1(v2,_,_) ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Parent(if1, a1)
    // if1 | a1
    // 4,5 4,6 4,7 8,9 8,11 13,14 13,15 13,16 18,19 18,26
    // 20,21 22,23 22,24 22,25 28,29 28,30
    // ---
    // Uses(a1,v2)
    // if1 | a1 | v2
    // 4,5,know 4,6,itsTrue 8,9,man 13,14,ax 22,25,notTrue
    // 28,30,bad
    // ---
    // pattern if1(v2,_,_)
    // if1 | a1 | v2
    // 4,6,itsTrue 28,30,bad
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4,6,itsTrue",
            "28,30,bad"),
            stringSet);
}