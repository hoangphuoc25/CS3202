#include <string>
#include <set>
#include <list>
#include "Test_20_SynSyn_RelRef.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test_20_SynSyn_RelRef::setUp() {}

void Test_20_SynSyn_RelRef::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_SynSyn_RelRef);

void Test_20_SynSyn_RelRef::test_variables_both_modified_and_used()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "12,apple", "6,x5",
            "9,x5", "2,ab", "12,ab", "15,this"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_00_from_argOne()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "evRRss,a", "evRRss,iOne",
            "evRRss,mm", "evRRss,no", "evRRss,thats", "evRRss,be",
            "evRRss,my", "twoProc,yes", "twoProc,obey"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_01()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "me,secProc",
            "static,firstProc", "static,secProc"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_10()
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

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_11()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "Aone,today", "Aone,i",
            "Aone,help", "storyCont,you"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_00_from_argOne()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1,term", "3,version",
            "4,numb", "5,numb", "6,monotonic", "7,complete"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_01()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1,test", "2,white"),
            stringSet);
    // select all the tuples
    evaluator.parseSimple(simpleProg);
    queryStr = " assign axc, aeEx; variable pib#1; ";
    queryStr += " Select <aeEx, pib#1, axc> such that ";
    queryStr += " Modifies(aeEx,pib#1) and Uses(axc, pib#1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "1,test,3", "1,test,5",
            "1,test,10", "2,white,12"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_10()
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
            "this,1", "is,1", "a,2", "test,2", "stuff,4",
            "test,5", "way,7", "time,8", "techniques,9", "testing,10",
            "test,11"),
            stringSet);
    // Select all the tuples, duplicated "2,just,test" is eliminated
    queryStr = " assign gga; variable vy, v443; ";
    queryStr += " Select <gga, vy, v443> ";
    queryStr += " such that Modifies(gga, vy) and Uses(gga,v443)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "1,well,this",
            "1,well,is", "2,just,a", "2,just,test", "4,prioritize,stuff",
            "5,easy,test", "7,efficient,way", "8,limited,time",
            "9,different,techniques", "10,exhaustive,testing",
            "11,combination,test"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_11()
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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3,well", "5,point",
            "14,too", "18,too", "19,ter", "22,date"),
            stringSet);
}