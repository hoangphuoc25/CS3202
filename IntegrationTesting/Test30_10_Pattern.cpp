#include <list>
#include <set>
#include <string>
#include "Test30_10_Pattern.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test30_10_Pattern::setUp()
{
	SELECT_ONE_SIMPLEPROG = "\
	procedure time {\
		I = 1231;\
		energy = I;\
		health = 0;\
		do = 1;\
		while do {\
			energy = energy - 1;\
			do = do - 1;\
			if do then {\
				call jobs;\
				energy = energy - 1;\
			} else {\
				health = (health + energy)/2;\
			}\
		}\
	}\
	procedure jobs {\
		task = 5;\
		done = 1;\
		hp = 1000;\
		while hp {\
			hp = hp - task * 50;\
			if hp then {\
				hp = hp - 50;\
			} else {\
				call relax;\
			}\
		}\
	}\
	procedure relax {\
		hp = hp + 500;\
		time = time - 1;\
		energy = energy + 100;\
	}";
}

void Test30_10_Pattern::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test30_10_Pattern);

void Test30_10_Pattern::test_2()
{
	const string simpleProg = "\
	procedure time {\
		I = 1231;\
		energy = I;\
		health = 0;\
		do = 1;\
		while do {\
			energy = energy - 1;\
			do = do - 1;\
			if do then {\
				call jobs;\
				energy = energy - 1;\
			} else {\
				health = (health + energy) * 2;\
			}\
		}\
	}\
	procedure jobs {\
		task = 5;\
		done = 1;\
		hp = 1000;\
		while hp {\
			hp = hp - task * 50;\
			if hp then {\
				hp = hp - 50;\
			} else {\
				call relax;\
			}\
		}\
	}\
	procedure relax {\
		hp = hp + 500;\
		time = time - 1;\
		energy = energy + 100;\
	}";

	string queryStr;
	QueryEvaluator evaluator;
	evaluator.parseSimple(simpleProg);
	list<string> resultList;
	SetWrapper<string> stringSet;

	//a(_, "b+c")
	queryStr = "while w; assign a; variable v;";
	queryStr += "Select w such that Parent(w, a) pattern a(_,\"energy - 1\")";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);

	//a(v, "b+c")
	queryStr = "while w; assign a; variable v;";
	queryStr += "Select <w, v> such that Parent(w, a) pattern a(v,\"energy - 1\")";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5,energy"), stringSet);

	//a("x", "b+c")
	queryStr = "while w; assign a; variable v;";
	queryStr += "Select w such that Parent(w, a) pattern a(\"health\",\"energy - 1\")";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0), stringSet);

	queryStr = "while w; assign a; variable v;";
	queryStr += "Select <w, a> such that Parent(w, a) pattern a(\"energy\",\"energy - 1\")";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5,6"), stringSet);

	//a(_, _"b+c"_)
	queryStr = "while w; assign a;Select <w, a> such that ";
	queryStr += "ParentStar(w, a) pattern a(_, _\"energy - 1\"_)";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5,6", "5,10"), stringSet);
}