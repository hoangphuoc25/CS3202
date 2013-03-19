#include <list>
#include <set>
#include <string>

#include "Test11_SelectDisjointTables.h"
#include "../SPA/QueryEvaluator.h"
#include "../SPA/SetWrapper.h"

using std::list;
using std::set;
using std::string;

void Test11_SelectDisjointTables::setUp() {}
void Test11_SelectDisjointTables::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test11_SelectDisjointTables);

void Test11_SelectDisjointTables::test_select_disjoint_tables()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    simpleProg =
        "procedure Test11 { \
           this = is + a - very; \
           busy = day; \
           while true { \
             i = have + been; \
             working = all + day; \
             if tired then { \
               you = may + take; \
               a = rest; \
             } else { \
               please = continue; \
               working = 156; \
             } \
             call grepNFA; \
             x5 = 1561 + 75; \
           } \
           echo = out; \
           if heard then { \
             sound = alarm; \
           } else { \
             continue = sleeping; \
           } \
           last = stmt; \
          } \
          procedure grepNFA { \
            there = is + a; \
            tsunami = 616; \
            so = grab + hold; \
            if of then { \
              smth = solid; \
              and = heavy; \
            } else { \
              otherwise = you; \
              might = perish; \
            } \
            signing = out; \
            continue = 62; \
          }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a1, a2, a3, a4; while w1, w2; ";
    queryStr += " variable v1, v2, v3, v4; ";
    queryStr += " procedure p1, p2; ";
    queryStr += " Select <a3, v1, p1> such that ";
    queryStr += " Modifies(a1,v1) and Uses(a2,v1) and ";
    queryStr += " Parent(w1, a3) and Uses(a3, v3) and ";
    queryStr += " Modifies(p1, v4) and Uses(a4, v4)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Here, we have 3 separate tables
    // Table 1: a1, v1, a2
    // Table 1 after Modifies(a1,v1)
    // (1,this), (2,busy), (4,i), (5,working), (7,you), (8,a)
    // (9,please), (10,working), (12,x5), (13,echo), (15,sound),
    // (16,continue), (17,last), (18,there), (19,tsunami), (20,so),
    // (22,smth), (23,and), (24,otherwise), (25,might), (26,signing)
    // (27,continue)
    // --- Table 1 after Uses(a2,v1)
    // (7,you,24), (8,a,1), (8,a,18), (16,continue,9), (27,continue,9)
    //
    // Table 2: w1, a3, v3
    // Table 2 after Parent(w1,a3)
    // (3,4), (3,5), (3,12)
    // -- Table 2 after Uses(a3,v3)
    // (3,4,have), (3,4,been), (3,5,all), (3,5,day)
    //
    // Table 3: p1, v4, a4
    // Table 3 after Modifies(p1,v4)
    // (Test11,this), (Test11,busy), (Test11,i), (Test11,working),
    // (Test11,you), (Test11,a), (Test11,please), (Test11,working),
    // (Test11,x5), (Test11,echo), (Test11,sound), (Test11,continue),
    // (Test11,last), (grepNFA,there), (grepNFA,tsunami), (grepNFA,so),
    // (grepNFA,smth), (grepNFA,and), (grepNFA,otherwise),
    // (grepNFA,might), (grepNFA,signing), (grepNFA, continue)
    // -- Table 3 after Uses(a4,v4)
    // (Test11,you,24), (Test11,a,1), (Test11,a,18), (Test11,continue,9),
    // (grepNFA,continue,9)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12, "4 you Test11",
            "4 you grepNFA", "4 a Test11", "4 a grepNFA",
            "4 continue Test11", "4 continue grepNFA",
            "5 you Test11",
            "5 you grepNFA", "5 a Test11", "5 a grepNFA",
            "5 continue Test11", "5 continue grepNFA"),
            stringSet);
}