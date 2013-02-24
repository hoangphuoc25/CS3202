#include <list>
#include <set>
#include <string>
#include "Test10_00_Uses.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_00_Uses::setUp()
{
    this->SIMPLE_PROG =
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
                  } \
                  done = deal; \
                } \
                clean = slate; \
              } \
            } \
            follow = star; \
          }";
}

void Test10_00_Uses::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_Uses);

void Test10_00_Uses::test_uses_assign_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "assign aggh; variable gdfg1; Select <aggh,gdfg1> ";
    queryStr += " such that Uses(aggh, gdfg1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(40, "1,two", "1,three",
            "3,two", "5,delta", "8,quarters", "10,small", "11,y",
            "12,up", "13,up", "14,much", "15,eol", "17,haha", "19,this",
            "20,sky", "21,xe5", "22,wall", "25,yes", "26,up", "27,this",
            "29,destruct", "31,power", "32,will", "36,is", "36,this",
            "37,way", "39,long", "40,away", "41,extinct", "43,know",
            "45,this", "46,cares", "48,are", "49,google", "50,are",
            "51,some", "51,other", "51,place", "52,deal", "53,slate",
            "54,star"),
            stringSet);
}