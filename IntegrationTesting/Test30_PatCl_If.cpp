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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "4 itsTrue",
            "8 strong", "13 itsTrue", "18 notTrue", "20 useless3",
            "22 mutiny", "28 bad"),
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "4 6 itsTrue",
            "28 30 bad"),
            stringSet);
}

void Test30_PatCl_If::test_if_var_syn_22()
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
    queryStr = " while w; if if1 ; assign a1; variable v2; ";
    queryStr += " Select <w,if1,a1,v2> such that Parent(w, if1) and ";
    queryStr += " Uses(a1, v2) pattern if1(v2,_,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Parent(w,if1)
    // w | if1
    // 2,4 2,8
    // ---
    // Uses(a1,v2)
    // a1 | v2
    // 1,bc 1,seventy 5,know 6,itsTrue 9,man 14,ax 17,board
    // 25,notTrue 27,date 30,bad 31,strong
    // ---
    // pattern if1(v2,_,_)
    // w | if1 | a1 | v2
    // 2,4,6,itsTrue 2,8,31,strong
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2 4 6 itsTrue",
            "2 8 31 strong"),
            stringSet);

    queryStr = " stmt s2; if if1 ; while w; variable v2; ";
    queryStr += " Select <w,if1,s2,v2> such that Parent(w, if1) and ";
    queryStr += " Uses(s2, v2) pattern if1(v2,_,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Parent(w,if1)
    // w | if1
    // 2,4 2,8
    // ---
    // Uses(s2,v2)
    // s2 | v2
    // 1,bc 1,seventy 2,bad 2,conVar 2,date 2,itsTrue
    // 2,know 2,man 2,strong
    // 3,date 3,bad 3,strong 4,itsTrue 4,know 5,know 6,itsTrue
    // 8,bad 8,date 8,man 8,strong 9,man 10,date 10,bad 10,strong
    // 13,ax 13,itsTrue 14,ax 17,board 18,mutiny 18,notTrue 18,useless3
    // 20,mutiny 20,notTrue 20,useless3 22,mutiny 22,notTrue
    // 25,notTrue 27,date 28,bad 30,bad 31,strong
    // ---
    // pattern if1(v2,_,_)
    // w | if1 | s2 | v2
    // 2,4,2,itsTrue 2,4,4,itsTrue 2,4,6,itsTrue 2,4,13,itsTrue
    // 2,8,2,strong 2,8,3,strong 2,8,8,strong 2,8,10,strong
    // 2,8,31,strong
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "2 4 2 itsTrue",
            "2 4 4 itsTrue", "2 4 6 itsTrue", "2 4 13 itsTrue",
            "2 8 2 strong", "2 8 3 strong", "2 8 8 strong",
            "2 8 10 strong", "2 8 31 strong"),
            stringSet);
}