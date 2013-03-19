#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "Test10_22_Modifies.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void Test10_22_Modifies::setUp()
{
    this->MODIFIES_10_SIMPLE_PROG =
        "procedure pOne { \
           px = ty; \
           abc = sun; \
           if t then { \
             sun = rise; \
             while true { \
               heck = it + la; \
             } \
             pipe = dream; \
           } else { \
             dawn = now; \
             while smth { \
               snake = here; \
               if notTrue then { \
                 nobodyUses = 23; \
               } else { \
                 nobodyUses = abcd; \
                 someVar = sun; \
               } \
             } \
           } \
           my = friend; \
           while germ { \
             sun = no + sun; \
           } \
           great = things; \
           come = hard; \
           call procTwo; \
         } \
         procedure procTwo { \
           hell = no; \
           while fine { \
             dont = heck; \
           } \
           no = go; \
           call procThree; \
         } \
         procedure procThree { \
           man = human; \
           whos = here; \
           hell = yes; \
         }";
}

void Test10_22_Modifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_22_Modifies);

void Test10_22_Modifies::test_modifies_assign_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_10_SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "procedure pOne; variable v1, v2; while wad; ";
    queryStr += " Select <pOne,v1,wad,v2> such that ";
    queryStr += " Modifies(pOne,v1) and ";
    queryStr += " Uses(wad,v2) and ";
    queryStr += " Modifies(pOne,v2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(pOne,v1)
    // pOne | v1
    // pOne,abc pOne,come pOne,dawn pOne,dont
    // pOne,great
    // pOne,heck pOne,hell pOne,man pOne,my pOne,no
    // pOne,nobodyUses pOne,pipe
    // pOne,px pOne,snake pOne,someVar pOne,sun pOne,whos
    //
    // procTwo,dont procTwo,hell procTwo,man procTwo,no
    // procTwo,whos
    //
    // procThree,hell procThree,man procThree,whos
    // ---
    // Uses(wad,v2)
    // wad | v2
    // 5,it 5,la 5,true
    // 9,abcd 9,here 9,notTrue 9,smth 9,sun
    // 16,germ 16,no 16,sun
    // 22,fine 22,heck
    // ---
    // Modifies(pOne,v2)
    // pOne | v1 | wad | v2
    // pOne,abc,9,sun pOne,come,9,sun pOne,dawn,9,sun
    // pOne,dont,9,sun pOne,great,9,sun pOne,heck,9,sun
    // pOne,hell,9,sun pOne,man,9,sun pOne,my,9,sun
    // pOne,no,9,sun pOne,nobodyUses,9,sun pOne,pipe,9,sun
    // pOne,px,9,sun pOne,snake,9,sun pOne,someVar,9,sun
    // pOne,sun,9,sun pOne,whos,9,sun
    //
    // pOne,abc,16,no pOne,come,16,no pOne,dawn,16,no
    // pOne,dont,16,no pOne,great,16,no pOne,heck,16,no
    // pOne,hell,16,no pOne,man,16,no pOne,my,16,no
    // pOne,no,16,no pOne,nobodyUses,16,no pOne,pipe,16,no
    // pOne,px,16,no pOne,snake,16,no pOne,someVar,16,no
    // pOne,sun,16,no pOne,whos,16,no
    //
    // pOne,abc,16,sun pOne,come,16,sun pOne,dawn,16,sun
    // pOne,dont,16,sun pOne,great,16,sun pOne,heck,16,sun
    // pOne,hell,16,sun pOne,man,16,sun pOne,my,16,sun
    // pOne,no,16,sun pOne,nobodyUses,16,sun pOne,pipe,16,sun
    // pOne,px,16,sun pOne,snake,16,sun pOne,someVar,16,sun
    // pOne,sun,16,sun pOne,whos,16,sun
    //
    // pOne,abc,22,heck pOne,come,22,heck pOne,dawn,22,heck
    // pOne,dont,22,heck pOne,great,22,heck pOne,heck,22,heck
    // pOne,hell,22,heck pOne,man,22,heck pOne,my,22,heck
    // pOne,no,22,heck pOne,nobodyUses,22,heck pOne,pipe,22,heck
    // pOne,px,22,heck pOne,snake,22,heck pOne,someVar,22,heck
    // pOne,sun,22,heck pOne,whos,22,heck
    //
    // procTwo,dont,16,no procTwo,hell,16,no procTwo,man,16,no
    // procTwo,no,16,no procTwo,whos,16,no
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(73,
            // 17
            "pOne abc 9 sun", "pOne come 9 sun", "pOne dawn 9 sun",
            "pOne dont 9 sun", "pOne great 9 sun", "pOne heck 9 sun",
            "pOne hell 9 sun", "pOne man 9 sun", "pOne my 9 sun",
            "pOne no 9 sun", "pOne nobodyUses 9 sun", "pOne pipe 9 sun",
            "pOne px 9 sun", "pOne snake 9 sun", "pOne someVar 9 sun",
            "pOne sun 9 sun", "pOne whos 9 sun",
            // 17
            "pOne abc 16 no", "pOne come 16 no", "pOne dawn 16 no",
            "pOne dont 16 no", "pOne great 16 no", "pOne heck 16 no",
            "pOne hell 16 no", "pOne man 16 no", "pOne my 16 no",
            "pOne no 16 no", "pOne nobodyUses 16 no", "pOne pipe 16 no",
            "pOne px 16 no", "pOne snake 16 no", "pOne someVar 16 no",
            "pOne sun 16 no", "pOne whos 16 no",
            // 17
            "pOne abc 16 sun", "pOne come 16 sun", "pOne dawn 16 sun",
            "pOne dont 16 sun", "pOne great 16 sun", "pOne heck 16 sun",
            "pOne hell 16 sun", "pOne man 16 sun", "pOne my 16 sun",
            "pOne no 16 sun", "pOne nobodyUses 16 sun",
            "pOne pipe 16 sun",
            "pOne px 16 sun", "pOne snake 16 sun", "pOne someVar 16 sun",
            "pOne sun 16 sun", "pOne whos 16 sun",
            // 17
            "pOne abc 22 heck", "pOne come 22 heck", "pOne dawn 22 heck",
            "pOne dont 22 heck", "pOne great 22 heck", "pOne heck 22 heck",
            "pOne hell 22 heck", "pOne man 22 heck", "pOne my 22 heck",
            "pOne no 22 heck", "pOne nobodyUses 22 heck",
            "pOne pipe 22 heck",
            "pOne px 22 heck", "pOne snake 22 heck",
            "pOne someVar 22 heck",
            "pOne sun 22 heck", "pOne whos 22 heck",
            // 5
            "procTwo dont 16 no", "procTwo hell 16 no",
            "procTwo man 16 no", "procTwo no 16 no", "procTwo whos 16 no"),
            stringSet);
}