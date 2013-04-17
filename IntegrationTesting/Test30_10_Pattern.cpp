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
    queryStr += "Select <w, v> such that Parent(w, a) pattern \
                a(v,\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5 energy"), stringSet);

    //a("x", "b+c")
    queryStr = "while w; assign a; variable v;";
    queryStr += "Select w such that Parent(w, a) pattern \
                a(\"health\",\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0), stringSet);

    queryStr = "while w; assign a; variable v;";
    queryStr += "Select <w, a> such that Parent(w, a) pattern \
                a(\"energy\",\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5 6"), stringSet);

    //a(_, _"b+c"_)
    queryStr = "while w; assign a;Select <w, a> such that ";
    queryStr += "Parent*(w, a) pattern a(_, _\"energy - 1\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5 6", "5 10"), stringSet);

    //a("x", _"b+c"_)
    queryStr = "while w; assign a;Select <w, a> such that ";
    queryStr += "Parent*(w, a) pattern a(\"health\", _\"health\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5 11"), stringSet);

    //a(v, _"b+c"_)
    queryStr = "while w; assign a; variable v; Select <w, a, v> such that ";
    queryStr += "Parent*(w, a) pattern a(v, _\"health\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5 11 health"), stringSet);

    //a(v, _)
    queryStr = "while w; assign a; variable v; Select <w, v> such that ";
    queryStr += "Parent*(w, a) pattern a(v, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "15 hp", "5 do",
        "5 energy", "5 health"), stringSet);

    //a("x", _)
    queryStr = "while w; assign a; variable v; Select w  such that ";
    queryStr += "Parent*(w, a) pattern a(\"do\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);

    //a(_, _)
    queryStr = "while w; assign a; variable v; Select <w, a>  such that ";
    queryStr += "Parent*(w, a) pattern a(_, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "5 6", "5 7",
        "5 10","5 11","15 16","15 18"), stringSet);

    queryStr = "while w; variable v; ";
    queryStr += " Select <w,v> with w.stmt# = 5 pattern w(v,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5 do"),
            stringSet);
    queryStr = "while w; variable v; ";
    queryStr += " Select <w,v> such that Uses(\"time\", v) ";
    queryStr += " pattern w(v,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5 do", "15 hp"),
            stringSet);
}

void Test30_10_Pattern::test_3()
{
    const string simpleProg = " \
    procedure Lazy { \
	    x = 1; \
	    y = 2; \
	    z = 3; \
	    if x then { \
	        home = 9; \
        } else { \
    	    c8g = 6 * x * y * z; \
		} \
	    y1 = y; \
	    y12 = y1; \
	    y123 = y12; \
	    y1234 = y * y1 * y12 * y123 * y1234 * 10; \
	    while y123 { \
	        if c8g then { \
	            a2b3c = 6 * 0 + 2; \
	            korean = sarang + haeyo; \
	            hello = annyeong; \
            } else { \
	            yesANDno = noANDyes; \
		    } \
	        if y12 then { \
	            here123 = efgh + z5; \
	        } else { \
	            mnop = lalala + happy; \
	            abcd = equals + piggydap; } \
	            z5 = 123456789; \
	            z5 = z5 + 1; \
            } \
	        yesANDNo = 999; \
	        while yesANDno { \
	            a2b3c = 32 + 28; \
	            while z5 { \
    	            abcd = 12345; \
	                efgh = 9876; \
	                while x { \
    	                call Hardworking; \
	                    chinese = 888; \
	                    while chinese { \
	                    english = abcd + efgh; \
	                    while english { \
    	                    happy = 313; \
	                        while y1 { \
	                        a2b3c = abcd + efgh; \
	                    while y12{ \
    	                    lalala = english + chinese; \
	                        yesANDno = lalala - y12 + f123g + english - happy; \
	                        if y12 then { \
	                            f123g = 1 + 2 - 3; \
	                            call Hardworking; \
	                            call p3; \
	                            call Hardworking; \
	                            call p3; \
	                            call p3;  \
		                    } else { \
        	                    gf456 = chinese; \
            	                if y123 then { \
	                                z5 = 5 * 3 + 1 - 2; \
        		                } else { \
        	                        y1234 = 2 * 9 - z5 + 2; \
			                    } \
                            } \
	                    } \
	                    noANDyes = 100 + 200 + 300 + lalala + 400; \
	                } \
	                yummy = 9; \
	                back = korean + chinese + english; \
	                hungry = yummy + english + chinese; \
	                while y1234 { \
	                    mnop = 3223; \
	                    call Hardworking; \
    	                call Hardworking; \
	                    lalala = 5 + 3 + 2 + chinese; \
	                    call p3; \
	                    mnop = (chinese + english + 1) - piggydap * somerset; \
	                    while mnop { \
	                        happy = happy - 1; \
	                        call p3; \
	                        while happy { \
	                            abcd = 224; \
	                            while y1 { \
        	                        egg99 = 2 + (3 + 5) - abcd; \
                                } \
   		                    } \
                        } \
                    } \
	            } \
	            noandyes = hungry; \
	            efgh = mnop + 86 + 23 - english; \
            } \
	        aAbBcCdD = 200 - 900 * 100; \
	        AaBbCcDd = aAbBcCdD; \
	        d7ia = 5; \
	        d7ib = 6; \
	        d7ic = 7; \
	        d7id = 8; \
	        d7ie = 9; \
	        if aAbBcCdD then { \
	            if d7ia then { \
    	            if d7ib then { \
	                    call Hardworking; \
	                    if d7ic then { \
	                        call p3; \
	                        if d7id then { \
	                            call p3; \
	                            if d7ie then { \
	                                AaBbCcDd = 7890 * 50 + 39 - 889 * 10; \
                                } else { \
    	                            z = ha99y * 8 + 5 - 2; \
                                } \
                            } else { \
	                            gf456 = abcd + egg99; \
				    	    } \
				        } else {  \
	                        aA12345bB = 7 * noANDyes; \
				        } \
			    } else {  \
	                yummy = gf456 - abcd; \
			    } \
		    } else { \
	            mnop = y123 - 123; \
		    } \
	            } else {  \
	                v123abc45 = z5 + d7id; \
	            } \
            } \
        } \
    } \
	    call Hardworking; \
    } \
    procedure Hardworking { \
	    a1 = 236; \
	    b2 = 123; \
	    c3 = 678; \
	    d4 = 0; \
	    equal99 = a1 + b2 + c3 - d4; \
	    if d4 then { \
	        call p3; \
	        x = 567; \
	        while x { \
	        c3 = c3 - 1; \
	    } \
	    somerset = 313; \
	    while b2 { \
	        d4 = somerset; \
        } \
						}else { \
	    yeah = 899; \
	    snore = happy + 9999; \
	    year = 2013; } \
	    total = a1 + b2 + c3 - (d4 + x) * somerset; \
	} \
    procedure p3 { \
	    prog1 = back + up; \
	    somerset = 456; \
	    pig = snore * lax; \
	    while here123 { \
	    if snore then { \
            prog1 = 17 + 200; \
	        equal99 = not + equals; \
	        if snoring then { \
	            back = pain + ouch; \
	            lax = 345 * snoring; \
	            call p4; \
        	}else { \
	            here123 = 99; \
            } \
		}else { \
	        helloWorld = pig + piggydap; \
	        not = 29 + 100 - 2; \
	        while snoring { \
	            piggydap = late4school + 1511; } \
	            equals = here123; \
	            annyeong = chinese; \
	            call p4; \
	            call p4; \
		    } \
	    } \
	    if not then { \
	        up = up + helloWorld; \
	        pig = 3 * 6; \
	        call p4; \
	    } else { \
	        back = piggydap + 1234; \
	    } \
	} \
	procedure p4 { \
		a =1; \
	}";

    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

    //82211
    queryStr = "while w1, w2; assign a1, a2;";
    queryStr += "Select <w1, a1, w2, a2> such that \
                Parent*(w1, a1) and Parent*(w2, a2) \
                pattern w1(\"yesANDno\", _) and w2(\"yesANDno\", _) \
                and a1(_, _\"noANDyes\"_) and a2(_, _\"noANDyes\"_)";
    string query2 = "assign a1, a2;";
    query2 += "Select a2 pattern a2(_, _\"noANDyes\"_)";
    evaluator.evaluate(query2, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "16", "91"),
        stringSet);

    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "24 91 24 91"),
        stringSet);
    
    //82210
    queryStr = "while w1, w2; assign a1, a2;";
    queryStr += "Select <a1, a2> such that Parent*(w1, a1) \
                and Parent*(w2, a2) pattern a1(_, _\"noANDyes\"_) \
                and a2(_, _\"noANDyes\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "16 16", "16 91", "91 16", "91 91"),
        stringSet);

    //8228
    queryStr = "while w; assign a1, a2;";
    queryStr += "Select <w, a1, a2> such that \
                Parent*(w, a1) and Parent*(w, a2) pattern \
                w(\"yesANDno\", _) and a1(_, _\"noANDyes\"_) and \
                a2(_, _\"noANDyes\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "24 91 91"), stringSet);

    //8229
    queryStr = "while w1, w2; assign a1, a2;";
    queryStr += "Select <w1, a1, w2, a2> such that \
                Parent*(w1, a1) and Parent*(w2, a2) \
                pattern a1(_, _\"noANDyes\"_) and \
                a2(_, _\"noANDyes\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "11 16 11 16", "11 16 24 91",
        "11 16 26 91", "11 16 29 91", "24 91 11 16", "24 91 24 91",
        "24 91 26 91", "24 91 29 91", "26 91 11 16", "26 91 24 91",
        "26 91 26 91", "26 91 29 91", "29 91 11 16", "29 91 24 91",
        "29 91 26 91", "29 91 29 91"), stringSet);
}