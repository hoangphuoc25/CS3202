#include <list>
#include <set>
#include <string>
#include "Test30_11_Pattern.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test30_11_Pattern::setUp()
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
}

void Test30_11_Pattern::test_2()
{
	const string simpleProg = "\
							  ";
	string queryStr;
	QueryEvaluator evaluator;
	evaluator.parseSimple(simpleProg);
	list<string> resultList;
	SetWrapper<string> stringSet;

	//a(v, _)
	queryStr = "procedure p; while w; assign a; variable v;";
	queryStr += "Select <p, a> such that Modifies(p, v) and Parent(w, a) pattern a(v, _)";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(21, "time,6","time,7", "time,10","time,11",
		"time,16","time,18","time,19","jobs,16","relax,16","relax,18","relax,19","jobs,16","jobs,18","jobs,19",
		"jobs,6","jobs,7","jobs,10","jobs,11","relax,6","relax,7","relax,10","relax,11"), stringSet);

	//a(v, "b+c")
	queryStr = "procedure p; while w; assign a; variable v;";
	queryStr += "Select <p, a> such that Modifies(p, v) and Parent(w, a) pattern a(v, \"energy - 1\")";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "time,6", "time,10", "jobs,6",
		"jobs,10", "relax,6", "relax,10"), stringSet);

	//a(v, _"b+c"_)
	queryStr = "procedure p; while w; assign a; variable v;";
	queryStr += "Select <p, a> such that Modifies(p, v) and Parent(w, a) pattern a(v, _\"energy - 1\"_)";
	evaluator.evaluate(queryStr, resultList);
	stringSet = SetWrapper<string>(resultList);
	CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "time,6", "time,10", "jobs,6", "jobs,10", 
		"relax,6","relax,10"), stringSet);
}
