#ifndef T11_TEST10_00_USES_H
#define T11_TEST10_00_USES_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Uses: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Uses);
CPPUNIT_TEST(test_uses_assign_var);
CPPUNIT_TEST(test_uses_procedure_var);
CPPUNIT_TEST(test_uses_call_var);
CPPUNIT_TEST(test_uses_if_var);
CPPUNIT_TEST(test_uses_while_var);
CPPUNIT_TEST(test_uses_stmt_var);
CPPUNIT_TEST(test_uses_progline_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_uses_assign_var();
    void test_uses_procedure_var();
    void test_uses_call_var();
    void test_uses_if_var();
    void test_uses_while_var();
    void test_uses_stmt_var();
    void test_uses_progline_var();
    std::string SIMPLE_PROG;
};

#endif

/*
     procedure Abcd { \
01     one = two + three; \
02     cee = 26 + 61; \
03     f = 123 - two + 7; \
04     while whileVar { \
05       eps = delta; \
06       if ifVar then { \
07         destruct = 71; \
08         head = quarters; \
09         if aaa then { \
10           big = small + 515; \
11           x = y; \
           } else { \
12           shoulders = up; \
13           call recProc; \
           } \
14         seven = up; \
         } else { \
15         nothing = much; \
         } \
       } \
16     fol = eol; \
17     if thisNot then { \
18       hoho = haha; \
       } else { \
19       while youThere { \
20         google = this; \
21         red = sky; \
         } \
22       aaa = xe5; \
       } \
23     fire = wall; \
24     call thirdProc; \
      } \
      procedure TwoProng { \
25      this = 151 + 61 * 4156; \
26      erm = yes; \
      } \
      procedure thirdProc { \
27      bottles = up; \
28      beat = this; \
29      while wall { \
30        building = destruct; \
        } \
31      call pForce; \
      } \
      procedure pForce { \
32      force = power; \
33      strength = will; \
34      if there then { \
35        while yes { \
36          while nope { \
37            what = is - this; \
38            no = way; \
39            ss = 77; \
40            call recProc; \
            } \
41          while nope { \
42            what = isThis; \
            } \
43          journey = long; \
          } \
44        far = away; \
        } else { \
45        die = extinct; \
46        while TT { \
47          dont = know; \
48          if qed then { \
49            heck = this; \
            } else { \
50            who = cares; \
51            if pForce then { \
52              you = are; \
53              at = google; \
              } else { \
54              you = are; \
55              at = some - other * place - 14; \
56              call recProc; \
              } \
57            done = deal; \
            } \
58          clean = slate; \
          } \
        } \
59      follow = star; \
      }
      procedure recProc { \
60      min = max; \
61      high = five; \
      }";
*/