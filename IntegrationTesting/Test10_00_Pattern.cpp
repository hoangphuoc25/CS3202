#include <list>
#include <set>
#include <string>
#include "Test10_00_Pattern.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_00_Pattern::setUp()
{
    SELECT_ONE_SIMPLEPROG =
        "procedure XProc { \
           a = b; \
           x = z2d; \
           ba = ba + black + sheep; \
           call yProc; \
           while i { \
             black = gold; \
             call godoSmth; \
           } \
		   if i then {\
			 gold = black;\
			 call godoSmth;\
			 } else {\
				black = gold; \
			 }\
           hell = yea; \
         } \
         procedure yProc { \
           no = time; \
           call aaaaa; \
         } \
         procedure godoSmth { \
           call cleanUp; \
           well = done; \
           call X; \
         } \
         procedure aaaaa { \
           aa = abb; \
         } \
         procedure cleanUp { \
           job = done; \
         } \
         procedure X { \
           x = y; \
           call cleanUp; \
         }";
}

void Test10_00_Pattern::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_Pattern);

void Test10_00_Pattern::test_select_one_syn()
{
    const string simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

	// Calls(p, q)
    // p | q
    // XProc,YProc YProc,aaaa godoSmth,cleanUp godoSmth,X godoSmth,XProc X,cleanUp
    
	//pattern i(v, _, _)
    queryStr = "if i; variable v;";
    queryStr += "Select i pattern i(v, _, _)";    
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "8"));

	//pattern i("x", _, _)
    /*queryStr = "if j; variable v;";
    queryStr += "Select j pattern j(\"i\", _, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "8"));*/

	//pattern i(_, _, _)
    queryStr = "if i; variable v;";
    queryStr += "Select i pattern i(_, _, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "8"));

	//pattern w(v, _, _)
    queryStr = "while w; variable v;";
    queryStr += "Select w pattern w(v, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "5"));

	//pattern w("x", _)
    /*queryStr = "while w; variable v;";
    queryStr += "Select i pattern w(\"i\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "6"));*/

	//pattern w(_, _)
    queryStr = "while w; variable v;";
    queryStr += "Select w pattern w(_, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "5"));
}

void Test10_00_Pattern::test_2() {
	const string simpleProg = "\
	procedure halo {\
		true = 5;\
		captain = 4;\
		chief = captain;\
		while dead {\
			revive = true;\
			life = life - 1;\
			call wts;\
		}\
		while life {\
			call kill;\
			hp = 1000;\
		}\
		if life then {\
			call kill;\
			number = number + 1 + hp + life;\
			if number then {\
				true = false;\
			} else {\
				false = true;\
			}\
		} else {\
			call me;\
			}\
		}\
		procedure wts {\
			abc = 1;\
			hello = abc + 2;\
		}\
		procedure me {\
			abc = 1;\
			hello = abc - 2;\
		}\
		procedure kill {\
			enemy = 1000;\
			while enemy {\
				enemy = enemy - 1;\
			}\
		}";
	string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

	//i(v, _, _)
	queryStr = "if i; variable v;";
    queryStr += "Select i pattern i(v, _, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "11", "14"));

	//i(_, _, _)
	queryStr = "if i;";
	queryStr += "Select i pattern i(_, _, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "11", "14"));

	//if("x", _, _)
	queryStr = "if i;";
	queryStr += "Select i pattern i(\"true\", _, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(0));


	//w(v, _)
	queryStr = "while w; variable v;";
	queryStr += "Select w pattern w(v, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "8", "23"));
	
	//w(_, _)
	queryStr = "while w;";
	queryStr += "Select w pattern w(_, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "8", "23"));

	//w("x", _)
	queryStr = "while w;";
	queryStr += "Select w pattern w(\"dead\", _)";
	//printf("%s",queryStr);
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "4"));

	//a(_, _)
	queryStr = "assign a;";
	queryStr += "Select a pattern a(_, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(15, "1", "2", "3", "5",
        "6", "10", "13", "15", "16", "18", "19", "20", "21", "22", "24"));

    //a(_, "b")
    queryStr = "assign a;";
    queryStr += "Select a pattern a(_, \"life - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "6"));

    queryStr = "assign a;";
    queryStr += "Select a pattern a(_, \"number + 1 + hp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(0));

    queryStr = "assign a;";
    queryStr += "Select a pattern a(_, \"number + 1 + hp + life\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "13"));

    queryStr = "assign a;";
    queryStr += "Select a pattern a(_, \"number + 1 + hp + life + hp\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(0));
    //-----------while(wildcard, expr) tested

	//a(v, _)
	queryStr = "assign a; variable v;";
	queryStr += "Select a pattern a(v, _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(15, "1", "2", "3", "5",
        "6", "10", "13", "15", "16", "18", "19", "20", "21", "22", "24"));

	//a("x", _)
	queryStr = "assign a; variable v;";
	queryStr += "Select a pattern a(\"life\", _)";
	evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(1, "6"));

	////a(_, "b")
	//queryStr = "assign a;";
	//queryStr += "Select a pattern a(_, \"captain\")";
	//evaluator.evaluate(queryStr, resultList);
 //   stringSet = SetWrapper<string>(resultList);
	//CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
}
