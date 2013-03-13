#include <cstdio>
#include <string>
#include <set>
#include <list>
#include <fstream>
#include "Test60_ParseFromFile.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;
using std::ofstream;

void Test60_ParseFromFile::setUp() {}

void Test60_ParseFromFile::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test60_ParseFromFile);

void Test60_ParseFromFile::test_parse_from_file()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \n\
           a = b + cd; \
           g = a * xc; \
           if i then { \
             true = 0; \
             while xp { \
               good = evil + bad; \
               call twoProng; \
               while cd { \n\
                 blah = f; \
                 if gt then { \
                   hi = bye; \n \
                 } else { \
                   no = tify; \
                 } \
                 down = out; \
               } \
               hell = yea; \
               call GGG; \
             } \
             good = good; \
             heat = sink + 55; \
           } else { \
             i = am + evil; \
             while two { \
               eye = ee; \
             } \
           } \
           tree = ish; \
         } \n\
         procedure twoProng { \n \
           harryPotter = not - harryPuttar; \
           if x then { \
             y = aa + gadfly; \
           } else { \
             red = yellow + orange; \
           }\
         }\
         procedure GGG { \
           gg = ggGGggGG; \
         }";
    // Write SIMPLE program out to file
    ofstream ofs("tmp.txt");
    ofs << simpleProg;
    ofs.close();
    evaluator.parseSimple_from_file("tmp.txt");
    queryStr = "while w1, w2; call c1; ";
    queryStr += " Select <w2,c1> such that Parent(w1,c1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "5,15", "8,15", "19,15",
            "5,7", "8,7", "19,7"),
            stringSet);
    remove("tmp.txt");
}