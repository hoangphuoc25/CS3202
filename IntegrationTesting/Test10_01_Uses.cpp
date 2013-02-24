#include <list>
#include <set>
#include <string>
#include "Test10_01_Uses.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_01_Uses::setUp()
{
    this->USES_00_SIMPLE_PROG =
        "procedure Abcd { \
           one = two + three; \
           cee = 26 + 61; \
           f = 123 - two + 7; \
           while whileVar { \
             eps = delta; \
             if ifVar then { \
               destruct = 71; \
               head = quarters; \
               if aaa then { \
                 big = small + 515; \
                 x = y; \
               } else { \
                 shoulders = up; \
                 call recProc; \
               } \
               seven = up; \
             } else { \
               nothing = much; \
             } \
           } \
           fol = eol; \
           if thisNot then { \
             hoho = haha; \
           } else { \
             while youThere { \
               google = this; \
               red = sky; \
             } \
             aaa = xe5; \
           } \
           fire = wall; \
           call thirdProc; \
          } \
          procedure TwoProng { \
            this = 151 + 61 * 4156; \
            erm = yes; \
          } \
          procedure thirdProc { \
            bottles = up; \
            beat = this; \
            while wall { \
              building = destruct; \
            } \
            call pForce; \
          } \
          procedure pForce { \
            force = power; \
            strength = will; \
            if there then { \
              while yes { \
                while nope { \
                  what = is - this; \
                  no = way; \
                  ss = 77; \
                  call recProc; \
                } \
                while nope { \
                  what = isThis; \
                } \
                journey = long; \
              } \
              far = away; \
            } else { \
              die = extinct; \
              while TT { \
                dont = know; \
                if qed then { \
                  heck = this; \
                } else { \
                  who = cares; \
                  if pForce then { \
                    you = are; \
                    at = google; \
                  } else { \
                    you = are; \
                    at = some - other * place - 14; \
                    call recProc; \
                  } \
                  done = deal; \
                } \
                clean = slate; \
              } \
            } \
            follow = star; \
          } \
          procedure recProc { \
            min = max; \
            high = five; \
          } ";
}

void Test10_01_Uses::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Uses);

void Test10_01_Uses::test_uses_assign_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    string simpleProg =
        "procedure Fone { \
           xyz = 123; \
           axe = hero; \
           if true then { \
             hail = axe; \
           } else { \
             gangnam = style; \
           } \
           mr = bombastic; \
           hair = style; \
           while peace { \
             true = not; \
             if manny then { \
               jquery = rocks; \
             } else { \
               no = time; \
             } \
             tornado = server - 5; \
           } \
           style = this; \
           call forkBomb; \
           all = done; \
         } \
         procedure forkBomb { \
           time = bomb; \
           since = when; \
           got = axe; \
           manny = pacquiao; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a1, a2; variable v1; ";
    queryStr += " Select <a1,v1,a2> such that ";
    queryStr += " Modifies(a1,v1) and Uses(a2,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,xyz), (2,axe), (4,hail), (5,gangnam), (6,mr), (7,hair)
    // (9,true), (11,jquery), (12,no), (13,tornado), (14,style),
    // (16,all), (17,time), (18,since), (19,got), (20,manny)
    // ---
    // Uses(a2,v1)
    // a1 | a2 | v1
    // (2,axe,4), (2,axe,19), (14,style,5), (14,style,7), (17,time,12)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "2,axe,4", "2,axe,19",
            "14,style,5", "14,style,7", "17,time,12"),
            stringSet);
}

void Test10_01_Uses::test_uses_procedure_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    string simpleProg =
        "procedure Fone { \
           xyz = 123; \
           axe = hero; \
           if true then { \
             hail = axe; \
           } else { \
             gangnam = style; \
           } \
           mr = bombastic; \
           hair = style; \
           while peace { \
             true = not; \
             if manny then { \
               jquery = rocks; \
             } else { \
               no = time; \
             } \
             tornado = server - 5; \
           } \
           style = this; \
           call forkBomb; \
           all = done; \
         } \
         procedure forkBomb { \
           time = bomb; \
           since = when; \
           got = axe; \
           manny = pacquiao; \
           not = true; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a1; procedure procOne; variable v1; ";
    queryStr += " Select <a1,v1,procOne> such that ";
    queryStr += " Modifies(a1,v1) and Uses(procOne,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,xyz), (2,axe), (4,hail), (5,gangnam), (6,mr), (7,hair)
    // (9,true), (11,jquery), (12,no), (13,tornado), (14,style),
    // (16,all), (17,time), (18,since), (19,got), (20,manny),
    // (21,not)
    // ---
    // Uses(a2,v1)
    // a1 | a2 | v1
    // (2,axe,Fone), (2,axe,forkBomb), (9,true,Fone)
    // (9,true,forkBomb), (14,style,Fone)
    // (17,time,Fone), (20,many,Fone), (21,not,Fone)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "2,axe,Fone",
            "2,axe,forkBomb", "9,true,Fone", "9,true,forkBomb",
            "14,style,Fone", "17,time,Fone", "20,manny,Fone",
            "21,not,Fone"),
            stringSet);
}

void Test10_01_Uses::test_uses_call_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->USES_00_SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a1; variable v1; call callbbA; ";
    queryStr += " Select <a1,v1,callbbA> such that ";
    queryStr += " Modifies(a1,v1) and Uses(callbbA, v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,one), (2,cee), (3,f), (5,eps), (7,destruct), (8,head)
    // (10,big), (11,x), (12,shoulders), (14,seven), (15,nothing)
    // (16,fol), (18,hoho), (20,google), (21,red), (22,aaa)
    // (23,fire), (25,this), (26,erm), (27,bottles), (28,beat)
    // (30,building), (32,force), (33,strength), (37,what)
    // (38,no), (39,ss), (42,what), (43,journey), (44,far)
    // (45,die), (47,dont), (49,heck), (50,who), (52,you)
    // (53,at), (54,you), (55,at), (57,done), (58,clean), (60,min)
    // (61,high)
    // ---
    // Modifies(callbbA,v1)
    // a1 | v1 | callbbA
    // (7,destruct,24), (20,google,24), (20,google,31), (25,this,24)
    // (25,this,31)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "7,destruct,24",
            "20,google,24", "20,google,31", "25,this,24", "25,this,31"),
            stringSet);
}

void Test10_01_Uses::test_uses_if_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->USES_00_SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a1; variable v1; if ib1; ";
    queryStr += " Select <a1,v1,ib1> such that ";
    queryStr += " Modifies(a1,v1) and Uses(ib1, v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,one), (2,cee), (3,f), (5,eps), (7,destruct), (8,head)
    // (10,big), (11,x), (12,shoulders), (14,seven), (15,nothing)
    // (16,fol), (18,hoho), (20,google), (21,red), (22,aaa)
    // (23,fire), (25,this), (26,erm), (27,bottles), (28,beat)
    // (30,building), (32,force), (33,strength), (37,what)
    // (38,no), (39,ss), (42,what), (43,journey), (44,far)
    // (45,die), (47,dont), (49,heck), (50,who), (52,you)
    // (53,at), (54,you), (55,at), (57,done), (58,clean), (60,min)
    // (61,high)
    // ---
    // Modifies(ib1,v1)
    // a1 | v1 | ib1
    // (20,google,34), (20,google,48), (20,google,51), (22,aaa,6)
    // (22,aaa,9),  (25,this,17), (25,this,34), (25,this,48)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "20,google,34",
            "20,google,48", "20,google,51", "22,aaa,6", "22,aaa,9",
            "25,this,17", "25,this,34", "25,this,48"),
            stringSet);
}