#include <list>
#include <set>
#include <string>
#include "Test10_00_AffectsStar.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_00_AffectsStar::setUp()
{
    this->AFFECTS_STAR_00_PROG = 
        "procedure affects{\
            while w1 {\
                if i2 then {\
                    if i3 then {\
                        if i4 then {\
                            a = a + 5;\
                        } else {\
                            c = b + 6;\
                        }\
                    } else {\
                        if i7 then {\
                            b = a + 8;\
                        } else {\
                            d = c + 9;\
                        }\
                    }\
                } else {\
                    if i10 then {\
                        if i11 then {\
                            b = a +12;\
                        } else {\
                            d = c + 13;\
                        }\
                    } else {\
                        while w14 {\
                            b = e + 15;\
                            e = d + 16;\
                            d = 17;\
                        }\
                    }\
                }\
                call lala;\
            }\
        }\
        procedure lala{\
            f = 1;\
            call rara;\
            g = f;\
        }\
        procedure rara {\
            f = 2;\
        }";
}

void Test10_00_AffectsStar::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_AffectsStar);

/*
    assign: 5,6,8,9,12,13,14,15,16,17
    call: 18
    if: 2,3,4,5,10,11
    while: 1,14
    5 -> 8, 12 -> 6 -> 9, 13 -> 16
                  6 -<   15   <- 16 <- 17 
    Loop: 6, 9, 13, 16, 15
*/


void Test10_00_AffectsStar::test_affects_star_stmt_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->AFFECTS_STAR_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "assign a1,a2;";
    queryStr += " Select a1 such that Affects*(a1,a2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9,"5","8","12","6","9","13","17","16","15"),
            stringSet);

    queryStr = "assign a1,a2;";
    queryStr += " Select a2 such that Affects*(a1,a2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8,"5","8","12","6","9","13","16","15"),
            stringSet);

    queryStr = "assign a;";
    queryStr += " Select a such that Affects*(a,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"5","6","9","13","16","15"),
            stringSet);

    queryStr = "assign a1,a2,a3;";
    queryStr += " Select a3 such that Affects(a1,a2) and Affects*(a2,a3)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8,"5","8","12","6","9","13","16","15"),
            stringSet);

}