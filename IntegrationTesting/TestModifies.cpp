#include <cstdio>
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

void TestModifies::test_modifies_single()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> resultSet;

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
           } \
           well = goodness - me; \
           if x then { \
             aa = ta; \
           } else { \
             aa = b; \
           } \
           xc = 3 + 56 + ab; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v; Select v such that Modifies(a,v)";
    evaluator.evaluate(queryStr, resultList);
    // x, a, b, y, kerb, big, g2, well, aa, xc
    CPPUNIT_ASSERT_EQUAL(10, (int)resultList.size());
    resultSet = set<string>(resultList.begin(), resultList.end());
    CPPUNIT_ASSERT_EQUAL(10, (int)resultSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("x"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("a"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("b"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("y"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("kerb"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("big"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("g2"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("well"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("aa"));
    CPPUNIT_ASSERT_EQUAL(1, (int)resultSet.count("xc"));
}