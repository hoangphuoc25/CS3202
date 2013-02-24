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

// >= 41 + 2

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
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(43, "1,two", "1,three",
            "3,two", "5,delta", "8,quarters", "10,small", "11,y",
            "12,up", "14,up", "15,much", "16,eol", "18,haha", "20,this",
            "21,sky", "22,xe5", "23,wall", "26,yes", "27,up", "28,this",
            "30,destruct", "32,power", "33,will", "37,is", "37,this",
            "38,way", "42,isThis", "43,long", "44,away", "45,extinct",
            "47,know", "49,this", "50,cares", "52,are", "53,google",
            "54,are", "55,some", "55,other", "55,place", "57,deal",
            "58,slate", "59,star", "60,max", "61,five"),
            stringSet);
}

void Test10_00_Uses::test_uses_procedure_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = " variable hdh; procedure jpha#s; ";
    queryStr += " Select <jpha#s,hdh> such that Uses(jpha#s,hdh)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(106,
            // 46
            "Abcd,TT", "Abcd,aaa", "Abcd,are", "Abcd,away",
            "Abcd,cares", "Abcd,deal", "Abcd,delta", "Abcd,destruct",
            "Abcd,eol", "Abcd,extinct", "Abcd,five", "Abcd,google",
            "Abcd,haha", "Abcd,ifVar", "Abcd,is", "Abcd,isThis",
            "Abcd,know", "Abcd,long", "Abcd,max", "Abcd,much",
            "Abcd,nope", "Abcd,other", "Abcd,pForce", "Abcd,place",
            "Abcd,power", "Abcd,qed", "Abcd,quarters", "Abcd,sky",
            "Abcd,slate", "Abcd,small", "Abcd,star", "Abcd,some",
            "Abcd,there", "Abcd,this", "Abcd,thisNot", "Abcd,three",
            "Abcd,two", "Abcd,up", "Abcd,wall", "Abcd,way",
            "Abcd,whileVar", "Abcd,will", "Abcd,xe5", "Abcd,y",
            "Abcd,yes", "Abcd,youThere",
            // 1
            "TwoProng,yes",
            // 27
            "pForce,TT", "pForce,are", "pForce,away", "pForce,cares",
            "pForce,deal", "pForce,extinct", "pForce,five",
            "pForce,google", "pForce,is", "pForce,isThis", "pForce,know",
            "pForce,long", "pForce,max", "pForce,nope", "pForce,other",
            "pForce,pForce", "pForce,place", "pForce,power",
            "pForce,qed", "pForce,slate", "pForce,some", "pForce,star",
            "pForce,there", "pForce,this", "pForce,way", "pForce,will",
            "pForce,yes",
            // 2
            "recProc,five", "recProc,max",
            // 30
            "thirdProc,TT", "thirdProc,are", "thirdProc,away",
            "thirdProc,cares", "thirdProc,deal", "thirdProc,destruct",
            "thirdProc,extinct", "thirdProc,five", "thirdProc,google",
            "thirdProc,is", "thirdProc,isThis", "thirdProc,know",
            "thirdProc,long", "thirdProc,max", "thirdProc,nope",
            "thirdProc,other", "thirdProc,pForce", "thirdProc,place",
            "thirdProc,power", "thirdProc,qed", "thirdProc,slate",
            "thirdProc,some", "thirdProc,star", "thirdProc,there",
            "thirdProc,this", "thirdProc,up", "thirdProc,wall",
            "thirdProc,way", "thirdProc,will", "thirdProc,yes"),
            stringSet);
}

void Test10_00_Uses::test_uses_call_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "call mmbb; variable vv1; Select <mmbb,vv1> such that ";
    queryStr += " Uses(mmbb,vv1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(63,
            // 2
            "13,five", "13,max",
            // 30
            "24,TT", "24,away", "24,are", "24,cares", "24,deal",
            "24,destruct", "24,extinct", "24,five", "24,google",
            "24,is", "24,isThis", "24,know", "24,long", "24,max",
            "24,nope", "24,other", "24,pForce", "24,place", "24,power",
            "24,qed", "24,slate", "24,some", "24,star", "24,there",
            "24,this", "24,up", "24,wall", "24,way", "24,will", "24,yes",
            // 27
            "31,TT", "31,away", "31,are", "31,cares", "31,deal",
            "31,extinct", "31,five", "31,google", "31,is", "31,isThis",
            "31,know", "31,long", "31,max", "31,nope", "31,other",
            "31,pForce", "31,place", "31,power", "31,qed", "31,slate",
            "31,some", "31,star", "31,there", "31,this", "31,way",
            "31,will", "31,yes",
            // 2
            "40,five", "40,max",
            // 2
            "56,five", "56,max"),
            stringSet);
}

void Test10_00_Uses::test_uses_if_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = " if i1; variable v1; Select <i1,v1> such that ";
    queryStr += " Uses(i1, v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(65,
            // 9
            "6,aaa", "6,five", "6,ifVar", "6,max", "6,much",
            "6,quarters", "6,small", "6,up", "6,y",
            // 6
            "9,aaa", "9,five", "9,max", "9,small", "9,up", "9,y",
            // 6
            "17,haha", "17,sky", "17,this", "17,thisNot",
            "17,xe5", "17,youThere",
            // 24
            "34,TT", "34,away", "34,are", "34,cares", "34,deal",
            "34,extinct", "34,five", "34,google", "34,is", "34,isThis",
            "34,know", "34,long", "34,max", "34,nope", "34,other",
            "34,pForce", "34,place", "34,qed", "34,slate", "34,some",
            "34,there", "34,this", "34,way", "34,yes",
            // 12
            "48,are", "48,cares", "48,deal", "48,five", "48,google",
            "48,max", "48,other", "48,pForce", "48,place", "48,qed",
            "48,some", "48,this",
            // 8
            "51,are", "51,five", "51,google", "51,max", "51,other",
            "51,pForce", "51,place", "51,some"),
            stringSet);
}

void Test10_00_Uses::test_uses_while_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "while w412; variable Vgw1; Select <w412, Vgw1> ";
    queryStr += " such that Uses(w412, Vgw1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(48,
            // 11
            "4,aaa", "4,delta", "4,five", "4,ifVar", "4,max", "4,much",
            "4,quarters", "4,small", "4,up", "4,whileVar", "4,y",
            // 3
            "19,sky", "19,this", "19,youThere",
            // 2
            "29,destruct", "29,wall",
            // 9
            "35,five", "35,is", "35,isThis", "35,long", "35,max",
            "35,nope", "35,this", "35,way", "35,yes",
            // 6
            "36,five", "36,is", "36,max", "36,nope", "36,this",
            "36,way",
            // 2
            "41,nope", "41,isThis",
            // 15
            "46,TT", "46,are", "46,cares", "46,deal", "46,five",
            "46,google", "46,know", "46,max", "46,other", "46,pForce",
            "46,place", "46,qed", "46,slate", "46,some", "46,this"),
            stringSet);
}

void Test10_00_Uses::test_uses_stmt_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SIMPLE_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "stmt ha1; variable vy1; Select <ha1, vy1> such that ";
    queryStr += " Uses(ha1, vy1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(219,
            // 3
            "1,three", "1,two", "3,two",
            // 11
            "4,aaa", "4,delta", "4,five", "4,ifVar", "4,max", "4,much",
            "4,quarters", "4,small", "4,up", "4,whileVar", "4,y",
            // --- 1
            "5,delta",
            // 9
            "6,aaa", "6,five", "6,ifVar", "6,max", "6,much",
            "6,quarters", "6,small", "6,up", "6,y",
            // --- 1
            "8,quarters",
            // 6
            "9,aaa", "9,five", "9,max", "9,small", "9,up", "9,y",
            // --- 3
            "10,small", "11,y", "12,up",
            // 2
            "13,five", "13,max",
            // --- 3
            "14,up", "15,much", "16,eol",
            // 6
            "17,haha", "17,sky", "17,this", "17,thisNot", "17,youThere",
            "17,xe5",
            // --- 1
            "18,haha",
            // 3
            "19,sky", "19,this", "19,youThere",
            // --- 5
            "20,this", "21,sky", "22,xe5", "23,wall", "26,yes",
            // 30
            "24,TT", "24,are", "24,away", "24,cares", "24,deal",
            "24,destruct", "24,extinct", "24,five", "24,google", "24,is",
            "24,isThis", "24,know", "24,long", "24,max", "24,nope",
            "24,other", "24,pForce", "24,place", "24,power", "24,qed",
            "24,slate", "24,some", "24,star", "24,there", "24,this",
            "24,up", "24,wall", "24,way", "24,will", "24,yes",
            // --- 2
            "27,up", "28,this",
            // 2
            "29,destruct", "29,wall",
            // --- 1
            "30,destruct",
            // 27
            "31,TT", "31,are", "31,away", "31,cares", "31,deal",
            "31,extinct", "31,five", "31,google", "31,is",
            "31,isThis", "31,know", "31,long", "31,max", "31,nope",
            "31,other", "31,pForce", "31,place", "31,power", "31,qed",
            "31,slate", "31,some", "31,star", "31,there", "31,this",
            "31,way", "31,will", "31,yes",
            // --- 2
            "32,power", "33,will",
            // 24
            "34,TT", "34,are", "34,away", "34,cares", "34,deal",
            "34,extinct", "34,five", "34,google", "34,is", "34,isThis",
            "34,know", "34,long", "34,max", "34,nope", "34,other",
            "34,pForce", "34,place", "34,qed", "34,slate", "34,some",
            "34,there", "34,this", "34,way", "34,yes",
            // 9
            "35,five", "35,is", "35,isThis", "35,long", "35,max",
            "35,nope", "35,this", "35,way", "35,yes",
            // 6
            "36,five", "36,is", "36,max", "36,nope", "36,this", "36,way",
            // --- 3
            "37,is", "37,this", "38,way",
            // 2
            "40,five", "40,max",
            // 2
            "41,isThis", "41,nope",
            // --- 4
            "42,isThis", "43,long", "44,away", "45,extinct",
            // 15
            "46,TT", "46,are", "46,cares", "46,deal", "46,five",
            "46,google", "46,know", "46,max", "46,other", "46,pForce",
            "46,place", "46,qed", "46,slate", "46,some", "46,this",
            // --- 1
            "47,know",
            // 12
            "48,are", "48,cares", "48,deal", "48,five", "48,google",
            "48,max", "48,other", "48,pForce", "48,place", "48,qed",
            "48,some", "48,this",
            // -- 2
            "49,this", "50,cares",
            //  8
            "51,are", "51,five", "51,google", "51,max", "51,other",
            "51,pForce", "51,place", "51,some",
            // --- 6
            "52,are", "53,google", "54,are", "55,other", "55,place",
            "55,some",
            // 2
            "56,five", "56,max",
            // --- 5
            "57,deal", "58,slate", "59,star", "60,max", "61,five"),
            stringSet);
}