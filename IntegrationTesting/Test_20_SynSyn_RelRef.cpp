#include <string>
#include <set>
#include <list>
#include "Test_20_SynSyn_RelRef.h"
#include "SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test_20_SynSyn_RelRef::setUp() {}

void Test_20_SynSyn_RelRef::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_SynSyn_RelRef);

void Test_20_SynSyn_RelRef::test_uses_modifies_same_variable()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure Pone { \
           apple = orange; \
           x5 = 2 + ab + 7; \
           while i { \
             ab = mk + yong; \
             apple = 5; \
           } \
           x = x5 + c2; \
           if p then { \
             call PTwo; \
           } else { \
             inscope = here + x5; \
           } \
           twoB = 1 + 3 + 7; \
         } \
         procedure PTwo { \
           end = game; \
           hates = apple * ab; \
           fun = stuff + goods; \
           if true then { \
             fear = this; \
           } else { \
             this = train; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign ahh, mbb; variable vv1; Select <mbb, vv1> ";
    queryStr += " such that Modifies(ahh, vv1) and Uses(mbb, vv1)";
    evaluator.evaluate(queryStr, resultList);
    // variables both used and modified by assign:
    //   apple, x5, ab, this
    // assignment that uses them:
    //   apple [12], x5 [6, 9], ab [2, 12], this [15]
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(20, "2,apple", "2,x5",
            "2,ab", "2,this", "6,apple", "6,x5", "6,ab", "6,this",
            "9,apple", "9,x5", "9,ab", "9,this", "12,apple", "12,x5",
            "12,ab", "12,this", "15,apple", "15,x5", "15,ab", "15,this"),
            stringSet);
}