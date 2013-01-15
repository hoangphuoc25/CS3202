#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "TestModifies.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void TestModifies::setUp() {}

void TestModifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(TestModifies);

void TestModifies::compare_string_set(const set<string>& S, int n, ...) const
{
    int expectedSize = (int)S.size();
    CPPUNIT_ASSERT_EQUAL(expectedSize, n);
    set<string> tmpSet;
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        string str = string(va_arg(ap, char *));
        CPPUNIT_ASSERT_EQUAL(1, (int)S.count(str));
        CPPUNIT_ASSERT_EQUAL(0, (int)tmpSet.count(str));
        tmpSet.insert(str);
    }
    CPPUNIT_ASSERT_EQUAL(expectedSize, (int)tmpSet.size());
    va_end(ap);
}

void TestModifies::test_modifies_single()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;

    simpleProg =
        "procedure procOne { \
           x = y + 3; \
           a = 5; \
           b = bad + amp + 41; \
           while itsTrue { \
             y = 5 + 6 + a; \
             if xab then { \
               kerb = s + 2; \
             } else { \
               big = trouble + 11; \
               a = a + a; \
             } \
             g2 = g1 + 1; \
             if bad then { \
               call ascP; \
               xyz = 123; \
             } else { \
               aa = aabbx; \
             } \
           } \
           call doSmth; \
           well = goodness - me; \
           if x then { \
             aa = ta; \
           } else { \
             aa = b; \
           } \
           xc = 3 + 56 + ab; \
         } \
         \
         procedure ascP { \
           if gax then { \
             xcz = 12; \
             while xg { \
               while bb { \
                 a = b + bad + good; \
                 well = bbz; \
               } \
               x = vv; \
             } \
             vv = 2 + g; \
           } else { \
             noway = yesway + 2; \
             x = 5; \
           } \
           hi = bye + 113; \
           thank = goodness; \
        } \
        \
        \
        \
        procedure doSmth { \
          yes = hell + no; \
          call cleanUp; \
          dont = do + this; \
        } \
        procedure cleanUp { \
          im = done; \
        }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v; Select v such that Modifies(a,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 19, "x", "a", "b", "y", "kerb", "big",
            "g2", "xcz", "well", "vv", "noway", "hi", "thank", "xyz",
            "aa", "yes", "im", "dont", "xc");
    queryStr = "assign abb; variable jnah#; Select abb such that ";
    queryStr += " Modifies(abb, jnah#   \n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1", "2", "3", "5", "7", "8",
            "9", "10", "13", "14", "16", "18", "19", "20", "22", "25", "26",
            "27", "28", "29", "30", "31", "32", "33", "35", "36");
}