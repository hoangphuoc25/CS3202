#include <string>
#include <set>
#include <list>
#include "Test20_SynSyn_RelRef.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test20_SynSyn_RelRef::setUp() {}

void Test20_SynSyn_RelRef::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test20_SynSyn_RelRef);

void Test20_SynSyn_RelRef::test_variables_both_modified_and_used()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "12 apple", "6 x5",
            "9 x5", "2 ab", "12 ab", "15 this"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_string_string_00_from_argOne()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure evRRss { \
           a = b + cd - efg; \
           iOne = iTwo + ple; \
           while i { \
             mm = 2 + 35 - 63; \
             if well then { \
               no = choice; \
             } else { \
               thats = what + youve + got; \
             } \
             be = a - man; \
           } \
           my = friend; \
         } \
         procedure twoProc { \
           yes = man; \
           obey = the + command; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "procedure psa; variable jsa; Select <psa,jsa> such that ";
    queryStr += " Modifies(psa,jsa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "evRRss a", "evRRss iOne",
            "evRRss mm", "evRRss no", "evRRss thats", "evRRss be",
            "evRRss my", "twoProc yes", "twoProc obey"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_string_string_01()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure firstProc { \
           a1 = hot + day; \
           if i then { \
             me = too; \
           } else { \
             assign = due; \
           } \
           hello = byebye + static; \
         } \
         procedure secProc { \
           static = analysis; \
           while m { \
             what = now; \
             nobody = is + answering - me; \
             if you then { \
               can = see; \
               thenIs = good; \
             } else { \
               otherwise = good + luck + to - me + static; \
             } \
           } \
         } ";
    queryStr = " assign bhb; variable tax; procedure Mira; ";
    queryStr += " Select <tax,Mira> such that Modifies(bhb, tax) ";
    queryStr += " and Uses(Mira, tax)";
    // Variables modified by assignment:
    //   a1, assign, can, hello, me, nobody, otherwise, static,
    //   thenIs, what
    // Variables above that are used by some procedure:
    //   me [secProc], static [firstProc, secProc]
    // Procedures: firstProc, secProc
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "me secProc",
            "static firstProc", "static secProc"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_string_string_10()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    // Modifies(proc,var1), Uses(proc,var2)
    simpleProg =
        "procedure Aleph { \
           song = of + burchess; \
           if nice then { \
             clap = your + hands; \
             while xt { \
               aa = bb; \
             } \
           } else { \
             melody = noise; \
           } \
           alittle = tired; \
         } \
         procedure GDay { \
           good = morning; \
           my = friends; \
           if cool then { \
             bb = alittle; \
           } else { \
             noise = met; \
           } \
         } \
         procedure UsesNothing { \
           this = 1 + 3; \
           proc = 5 + 7 - 162; \
           uses = 742; \
           nothing = 864 + 721; \
         } \
         procedure UseFromCall { \
           use = 73; \
           from = 1246; \
           call GDay; \
         }";
    // Procedures and variables they modify:
    // Aleph: song, clap, aa, melody, alittle
    // GDay: good, my, bb, noise
    // UsesNothing: this, proc, uses, nothing
    // UseFromCall: use, from, good, my, bb, noise
    //
    // Variables used by the procedures:
    // Aleph: of, burchess, nice, your, hands, xt, bb, noise, tired
    // GDay: morning, friends, cool, alittle, met
    // UsesNothing:
    // UseFromCall: morning, friends, alittle, met
    queryStr = "procedure asdf1; variable V1gds, Vjju; ";
    queryStr += " Select asdf1 such that Modifies(asdf1,V1gds) and ";
    queryStr += " Uses(asdf1, Vjju)";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(
            SetWrapper<string>(3, "Aleph", "GDay", "UseFromCall"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_string_string_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure Aone { \
           today = is + sunday; \
           i = am + coding - today; \
           while true { \
             this = is + an; \
             infinite = loop; \
             if my then { \
               teammates = can + help; \
               it = will - be * good; \
             } else { \
               but = they + just - cant; \
               help = me; \
             } \
             so = i + have; \
             to = solo; \
           } \
           end = time; \
         } \
         procedure storyCont { \
           you = will - not; \
           notice = this + message; \
           but = you + will - browse; \
           the = code; \
         } \
         procedure noCount { \
           my = 1; \
           a = 2; \
         }";
    // Select <procedure,var> such that procedure both uses and
    // modifies var
    // Aone: today, i, help
    // storyCont: you
    // noCount:
    evaluator.parseSimple(simpleProg);
    queryStr = "procedure pavaA1; variable GJA; Select <pavaA1, GJA> ";
    queryStr += " such that Modifies(pavaA1, GJA) and Uses(pavaA1, GJA)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "Aone today", "Aone i",
            "Aone help", "storyCont you"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_string_string_22()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
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

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_string_00_from_argOne()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure toDo { \
           term = factor + factor; \
           if fault then { \
             version = control; \
           } else { \
             numb = to + pain; \
           } \
           numb = yes; \
         } \
         procedure explodeStr { \
           monotonic = increasing + function; \
           complete = lattice - ascending; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a12; variable Tgs; Select <a12, Tgs> ";
    queryStr += " such that Modifies(a12, Tgs)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1 term", "3 version",
            "4 numb", "5 numb", "6 monotonic", "7 complete"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_string_01()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure iiProc { \
           test = pyramid; \
           white = box + testing; \
           unit = test; \
           while notTested { \
             unit = test - cases; \
             interactions = scenario; \
             less = integration; \
           } \
           blackbox = testing; \
         } \
         procedure burnMoney { \
           never = productive; \
           dont = test + function; \
           at = scheme - of * app; \
           select = white; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign axc, aeEx; variable pib#1; ";
    queryStr += " Select <aeEx, pib#1> such that Modifies(aeEx,pib#1) ";
    queryStr += " and Uses(axc, pib#1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // aeEx [assign] | pib#1 [var]
    // (1,test), (2,white), (3,unit), (5,unit), (6,interactions),
    // (7,less), (8,blackbox), (9,never), (10,dont), (11,at),
    // (12,select)
    // ---
    // aeEx [assign] | pib#1 [var] | axc [assign]
    // (1,test,3), (1,test,5), (1,test,10), (2,white,12)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1 test", "2 white"),
            stringSet);
    // select all the tuples
    evaluator.parseSimple(simpleProg);
    queryStr = " assign axc, aeEx; variable pib#1; ";
    queryStr += " Select <aeEx, pib#1, axc> such that ";
    queryStr += " Modifies(aeEx,pib#1) and Uses(axc, pib#1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "1 test 3", "1 test 5",
            "1 test 10", "2 white 12"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_string_10()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure Xone { \
           well = this + is; \
           just = test * a + test; \
           while true { \
             prioritize = stuff; \
           } \
           easy = test; \
           if t then { \
             efficient = way; \
           } else { \
             limited = time; \
           } \
           different = techniques; \
         } \
         procedure ptwo { \
           exhaustive = testing; \
           combination = test; \
           ncr = 15; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign gga; variable vy, v443; Select <v443, gga> ";
    queryStr += " such that Modifies(gga, vy) and Uses(gga,v443)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // gga [assign] | vy [var]
    // (1,well), (2,just), (4,prioritize), (5,easy), (7,efficient),
    // (8,limited), (9,different), (10,exhaustive), (11,combination),
    // (12,ncr)
    // ---
    // gga [assign] | vy [var] | v443 [var]
    // (1,well,this), (1,well,is), (2,just,a), (2,just,test),
    // (2,just,test), (4,prioritize,stuff), (5,easy,test),
    // (7,efficient,way), (8,limited,time), (9,different,techniques),
    // (10,exhaustive,testing), (11,combination,test)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11,
            "this 1", "is 1", "a 2", "test 2", "stuff 4",
            "test 5", "way 7", "time 8", "techniques 9", "testing 10",
            "test 11"),
            stringSet);
    // Select all the tuples, duplicated "2,just,test" is eliminated
    queryStr = " assign gga; variable vy, v443; ";
    queryStr += " Select <gga, vy, v443> ";
    queryStr += " such that Modifies(gga, vy) and Uses(gga,v443)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "1 well this",
            "1 well is", "2 just a", "2 just test", "4 prioritize stuff",
            "5 easy test", "7 efficient way", "8 limited time",
            "9 different techniques", "10 exhaustive testing",
            "11 combination test"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_string_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure progAnalyse { \
           ax = bc - seventy; \
           horse = rider; \
           well = i + am - well; \
           if true then { \
             point = here + point - there; \
           } else { \
             no = point; \
           } \
           while xt { \
             greater = than; \
             while good { \
               tt = gg; \
               if seen then { \
                 answer = this; \
               } else { \
                 hard = stuff; \
                 too = easy - too; \
               } \
               cannot = unsee; \
             } \
             if meet then { \
               cancel = it; \
               too = too - good; \
             } else { \
               ter = good + ter; \
             } \
           } \
           x5 = 4 + 7; \
         } \
         procedure chopList { \
           due = now; \
           date = date - now; \
           true = words; \
         }";
    // (3,well), (5,point), (14,too), (18,too), (19,ter), (22,date)
    evaluator.parseSimple(simpleProg);
    queryStr = "assign abc; variable vtya; Select <abc,vtya> such that ";
    queryStr += " Modifies(abc,vtya) and Uses(abc,vtya)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3 well", "5 point",
            "14 too", "18 too", "19 ter", "22 date"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_string_22()
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
             while itsTrue { \
               dont = know; \
             } \
             while notTrue { \
               freak = man; \
               call chopList; \
             } \
           } \
           useless1 = 123; \
           while itsTrue { \
             bad = ax; \
             useless1 = 424 - 311; \
           } \
           mutiny = board; \
           while notTrue { \
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
           } \
         } \
         procedure chopList { \
           date = date; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w1; assign a1, a2; variable v1, v2; ";
    queryStr += " Select <w1,a1,a2,v1> such that ";
    queryStr += " Parent(w1, a1) and Modifies(a2, v1) and ";
    queryStr += " Uses(w1, v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Parent(w1,a1)
    // w1 | a1
    // 4,5 6,7 10,11 10,12 14,15
    // ---
    // Modifies(a2,v1)
    // a2 | v1
    // 1,ax 5,dont 7,freak 9,useless1 11,bad 12,useless1
    // 13,mutiny 15,useless2 17,useless4 19,useless5 20,useless6
    // 21,date
    // ---
    // Uses(w1,v1)
    // w1 | a1 | a2 | v1
    // 10,11,1,ax 10,12,1,ax 14,15,13,mutiny 6,7,21,date
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "10 11 1 ax",
            "10 12 1 ax", "14 15 13 mutiny", "6 7 21 date"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_int_01()
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
    queryStr = " assign a1; variable v1; if if1; ";
    queryStr += " Select <a1,v1,if1> such that ";
    queryStr += " Modifies(a1,v1) and Parent(if1,a1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // 1,ax 5,dont 7,freak 10,useless1 12,bad 13,useless1
    // 14,mutiny 16,useless2 18,useless4 20,useless5 21,useless6
    // 22,useless2 23,date 27,useless8 29,useless3 32,useless10 33,abc
    // ---
    // Parent(if1, a1)
    // a1 | v1 | if1
    // 16,useless2,15 18,useless4,17 20,useless5,19 21,useless6,19
    // 22,useless2,15 27,useless8,25 33,abc,30
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "16 useless2 15",
            "18 useless4 17", "20 useless5 19", "21 useless6 19",
            "22 useless2 15", "27 useless8 25", "33 abc 30"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_int_10()
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

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_int_11()
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
    queryStr = "while w1; variable v1; assign a1; ";
    queryStr += "Select <w1, v1, a1> such that ";
    queryStr += " Modifies(w1, v1) and Modifies(a1, v1) and ";
    queryStr += " Parent(w1, a1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(w1, v1)
    // w1 | v1
    // 4,dont 6,freak 6,date 11,bad 11,useless1 31,useless10
    // ---
    // Modifies(a1, v1)
    // w1 | v1 | a1
    // 4,dont,5 6,freak,7 6,date,23 11,bad,12 11,useless1,10
    // 11,useless1,13 31,useless10,32
    // ---
    // Parent(w1, a1)
    // w1 | v1 | a1
    // 4,dont,5 6,freak,7 11,bad,12 11,useless1,13 31,useless10,32
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "4 dont 5",
            "6 freak 7", "11 bad 12", "11 useless1 13",
            "31 useless10 32"),
            stringSet);
}

void Test20_SynSyn_RelRef::test_ev_rr_ss_int_int_22()
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
    queryStr = " assign a1; variable v1; while w1; call c1; ";
    queryStr += " Select <a1,v1,w1,c1> such that ";
    queryStr += " Modifies(a1, v1) and Parent(w1, c1) and ";
    queryStr += " Parent(w1, a1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7 freak 6 8"),
            stringSet);
}