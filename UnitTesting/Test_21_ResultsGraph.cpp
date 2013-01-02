#include <cstdio>
#include <string>
#include <map>
#include <set>
#include "Test_21_ResultsGraph.h"
#include "../SPA/ResultsGraph.h"
#include "../SPA/StringBuffer.h"

using std::string;
using std::map;
using std::set;
using std::pair;

void Test_21_ResultsGraph::setUp() {}

void Test_21_ResultsGraph::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_21_ResultsGraph);

void Test_21_ResultsGraph::test_empty_graph()
{
    ResultsGraph g;
    string s = g.toString();
    CPPUNIT_ASSERT_EQUAL(string(""), s);
}

void Test_21_ResultsGraph::test_add_vertex()
{
    ResultsGraph g;
    string s;
    g.add_vertex("avar", 3);
    g.add_vertex("secondVar", 5);
    g.add_vertex("avar", 8);
    g.add_vertex("avar", 9);
    g.add_vertex("bag", "a");
    g.add_vertex("bag", "testString");
    g.add_vertex("tummy", "hell");
    // Both Repeated
    g.add_vertex("avar", 3);
    // 2nd arg repeated
    g.add_vertex("bag", "hell");
    // Both repeated
    g.add_vertex("bag", "testString");

    // avar = 3, avar = 8, avar = 9
    s = "1 3 ->\n1 8 ->\n1 9 ->\n";
    // secondVar = 5
    s += "2 5 ->\n";
    // bag = "a", bag = "testString", bag = "hell"
    s += "3 1 ->\n3 2 ->\n3 3 ->\n";
    // tummy = "hell"
    s += "4 3 ->\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("avar"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("secondVar"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("bag"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("tummy"));
}

void Test_21_ResultsGraph::test_add_edge()
{
    ResultsGraph g;
    g.add_edge("some", 1, "to", 3);
    g.add_edge("me", 61, "isnot", 146);
    g.add_edge("some", 6, "other", 62);
    g.add_edge("some", 72, "another", 34);
    g.add_edge("me", 2, "animal", "first");
    g.add_edge("me", 5, "another", 65);
    g.add_edge("some", 52, "another", 99);
    // Repeated edge
    g.add_edge("some", 1, "to", 3);
    g.add_edge("gvar", "second", "animal", "third");
    g.add_edge("gvar", "fourth", "x", "fifth");
    // Repeated edge
    g.add_edge("animal", "third", "gvar", "second");
    // Repeated edge
    g.add_edge("me", 2, "animal", "first");
    g.add_edge("gvar", "sixth", "rage", "first");
    // Repeated edge
    g.add_edge("animal", "first", "me", 2);
    g.add_edge("other", 62, "me", 2);

    // syn mapping
    // some = 1
    // to = 2
    // me = 3
    // isnot = 4
    // other = 5
    // another = 6
    // animal = 7
    // gvar = 8
    // x = 9
    // rage = 10

    // string mapping
    // first = 1, second = 2, third = 3, fourth = 4, fifth = 5
    string s = "1 1 -> [2 3]\n1 6 -> [5 62]\n1 52 -> [6 99]\n";
    s += "1 72 -> [6 34]\n";
    s += "2 3 -> [1 1]\n";
    s += "3 2 -> [5 62] [7 1]\n3 5 -> [6 65]\n3 61 -> [4 146]\n";
    s += "4 146 -> [3 61]\n";
    s += "5 62 -> [1 6] [3 2]\n";
    s += "6 34 -> [1 72]\n6 65 -> [3 5]\n6 99 -> [1 52]\n";
    s += "7 1 -> [3 2]\n7 3 -> [8 2]\n";
    s += "8 2 -> [7 3]\n8 4 -> [9 5]\n8 6 -> [10 1]\n";
    s += "9 5 -> [8 4]\n";
    s += "10 1 -> [8 6]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("some"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("to"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("me"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("isnot"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("other"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("another"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("animal"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("gvar"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("x"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("rage"));
}

void Test_21_ResultsGraph::test_prune_add_all()
{
    ResultsGraph g;
    string s;

    g.add_edge("assembly", 1, "c", 2);
    g.add_edge("assembly", 1, "c", 6);
    g.add_edge("assembly", 5, "c", 67);
    g.add_edge("assembly", 7, "c", 9);
    g.prune("assembly", "c");
    s = "1 1 -> [2 2] [2 6]\n1 5 -> [2 67]\n1 7 -> [2 9]\n";
    s += "2 2 -> [1 1]\n2 6 -> [1 1]\n2 9 -> [1 7]\n2 67 -> [1 5]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("assembly"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("c"));

    // this prune will kill off everything
    // but the super vertices still exist
    g.prune("assembly", "c");
    s = "";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("assembly"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("c"));
}

void Test_21_ResultsGraph::test_prune_1()
{
    // This test case represents the following program fragment:
    // 1. while x {
    // 2.      a = g
    // 3.      y = a + b + c }
    //
    // along with the following clauses, executed in order:
    // Parent(w,a)
    // Uses(a,v)
    // Modifies(a2,v)

    // synmap
    // w -> 1, a -> 2
    ResultsGraph g;
    string s;
    g.add_edge("w", 1, "a", 2);
    g.add_edge("w", 1, "a", 3);
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1]\n2 3 -> [1 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("w", "a");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // synmap
    // w -> 1, a -> 2, v -> 3
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4
    g.add_edge("a", 2, "v", "g");
    g.add_edge("a", 3, "v", "a");
    g.add_edge("a", 3, "v", "b");
    g.add_edge("a", 3, "v", "c");
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1] [3 1]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("a", "v");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // synmap
    // w -> 1, a -> 2, v -> 3, a2 -> 4
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4
    g.add_edge("a2", 2, "v", "a");
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1] [3 1]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [4 2]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    s += "4 2 -> [3 2]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("a2", "v");
    s = "1 1 -> [2 3]\n2 3 -> [1 1] [3 2]\n3 2 -> [2 3] [4 2]\n";
    s += "4 2 -> [3 2]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
}

void Test_21_ResultsGraph::test_prune_2()
{
    // This test case represents the following program fragment:
    // 1. a = 5 + c
    // 2. b = 7
    // 3. g = a + 5
    // 4. p = 13 + z
    // 5. f = a + b
    // 6. c = a + 13
    // 7. a = 8
    // 8. g = a + 2
    //
    // and these clauses executed in order:
    // Uses(a,v)
    // Modifies(a2,v)
    // Affects(a,a2)
    ResultsGraph g;
    string s;

    // synmap
    // a -> 1, v -> 2
    // string map
    // c -> 1, a -> 2, z -> 3, b -> 4
    g.add_edge("a", 1, "v", "c");
    g.add_edge("a", 3, "v", "a");
    g.add_edge("a", 4, "v", "z");
    g.add_edge("a", 8, "v", "a");
    g.add_edge("a", 6, "v", "a");
    g.add_edge("a", 5, "v", "a");
    g.add_edge("a", 5, "v", "b");

    s = "1 1 -> [2 1]\n1 3 -> [2 2]\n1 4 -> [2 3]\n";
    s += "1 5 -> [2 2] [2 4]\n1 6 -> [2 2]\n1 8 -> [2 2]\n";
    s += "2 1 -> [1 1]\n2 2 -> [1 3] [1 5] [1 6] [1 8]\n";
    s += "2 3 -> [1 4]\n2 4 -> [1 5]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    // prune - no effect
    g.prune("a", "v");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // synmap
    // a -> 1, v -> 2, a2 -> 3
    // string map
    // c -> 1, a -> 2, z -> 3, b -> 4
    // add some stuff and prune non-existent
    g.add_edge("a2", 6, "v", "c");
    g.add_edge("a2", 1, "v", "a");
    g.add_edge("a2", 2, "v", "b");
    s = "1 1 -> [2 1]\n1 3 -> [2 2]\n1 4 -> [2 3]\n";
    s += "1 5 -> [2 2] [2 4]\n1 6 -> [2 2]\n1 8 -> [2 2]\n";
    s += "2 1 -> [1 1] [3 6]\n2 2 -> [1 3] [1 5] [1 6] [1 8] [3 1]\n";
    s += "2 3 -> [1 4]\n2 4 -> [1 5] [3 2]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 4]\n3 6 -> [2 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    // prune v that hasnt been attached to a2
    g.prune("a2", "v");
    s = "1 1 -> [2 1]\n1 3 -> [2 2]\n1 5 -> [2 2] [2 4]\n";
    s += "1 6 -> [2 2]\n1 8 -> [2 2]\n";
    s += "2 1 -> [1 1] [3 6]\n2 2 -> [1 3] [1 5] [1 6] [1 8] [3 1]\n";
    s += "2 4 -> [1 5] [3 2]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 4]\n3 6 -> [2 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    g.add_edge("a", 1, "a2", 6);
    g.prune("a", "a2");
    s = "1 1 -> [2 1] [3 6]\n2 1 -> [1 1] [3 6]\n3 6 -> [1 1] [2 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
}

void Test_21_ResultsGraph::test_prune_3()
{
    ResultsGraph g;
    string s;

    // This test case represents the following program:
    // 1. while x {
    // 2.      a = g
    // 3.      y = a + b + c
    // 4.      x = 3 + a
    // 5.      b = y }
    // 6. c = 2 + 7
    // 7. w = 2 + b
    // 8. z = a + x
    // 9. b = y + 10
    //
    // and the following clauses executed in order:
    // Parent(w,a)
    // Uses(a,v)
    // Modifies(a2,v2)
    // Affects(a,a2)

    // Parent(w,a)
    g.add_edge("w", 1, "a", 2);
    g.add_edge("w", 1, "a", 3);
    g.add_edge("w", 1, "a", 4);
    g.add_edge("w", 1, "a", 5);
    s = "1 1 -> [2 2] [2 3] [2 4] [2 5]\n2 2 -> [1 1]\n2 3 -> [1 1]\n";
    s += "2 4 -> [1 1]\n2 5 -> [1 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("w", "a");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // Uses(a,v)
    // synmap
    // w -> 1, a -> 2, v -> 3
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4
    g.add_edge("a", 2, "v", "g");
    g.add_edge("a", 3, "v", "a");
    g.add_edge("a", 3, "v", "b");
    g.add_edge("a", 3, "v", "c");
    g.add_edge("a", 4, "v", "a");
    s = "1 1 -> [2 2] [2 3] [2 4] [2 5]\n2 2 -> [1 1] [3 1]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "2 4 -> [1 1] [3 2]\n2 5 -> [1 1]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [2 4]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("a", "v");
    s = "1 1 -> [2 2] [2 3] [2 4]\n";
    s += "2 2 -> [1 1] [3 1]\n2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "2 4 -> [1 1] [3 2]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [2 4]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // Modifies(a2,v2)
    // Uses(a,v)
    // synmap
    // w -> 1, a -> 2, v -> 3, a2 -> 4, v2 -> 5
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4, y -> 5, x -> 6, w -> 7, z -> 8
    g.add_edge("a2", 2, "v2", "a");
    g.add_edge("a2", 3, "v2", "y");
    g.add_edge("a2", 4, "v2", "x");
    g.add_edge("a2", 5, "v2", "b");
    g.add_edge("a2", 6, "v2", "c");
    g.add_edge("a2", 7, "v2", "w");
    g.add_edge("a2", 8, "v2", "z");
    g.add_edge("a2", 9, "v2", "b");
    s = "1 1 -> [2 2] [2 3] [2 4]\n";
    s += "2 2 -> [1 1] [3 1]\n2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "2 4 -> [1 1] [3 2]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [2 4]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    s += "4 2 -> [5 2]\n4 3 -> [5 5]\n4 4 -> [5 6]\n4 5 -> [5 3]\n";
    s += "4 6 -> [5 4]\n4 7 -> [5 7]\n4 8 -> [5 8]\n4 9 -> [5 3]\n";
    s += "5 2 -> [4 2]\n5 3 -> [4 5] [4 9]\n5 4 -> [4 6]\n5 5 -> [4 3]\n";
    s += "5 6 -> [4 4]\n5 7 -> [4 7]\n5 8 -> [4 8]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    g.prune("a2", "v2");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());

    // Affects(a,a2)
    // synmap
    // w -> 1, a -> 2, v -> 3, a2 -> 4, v2 -> 5
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4, y -> 5, x -> 6, w -> 7, z -> 8
    g.add_edge("a", 2, "a2", 3);
    g.add_edge("a", 2, "a2", 4);
    g.add_edge("a", 2, "a2", 8);
    g.add_edge("a", 3, "a2", 9);
    g.add_edge("a", 4, "a2", 8);
    s = "1 1 -> [2 2] [2 3] [2 4]\n";
    s += "2 2 -> [1 1] [3 1] [4 3] [4 4] [4 8]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4] [4 9]\n";
    s += "2 4 -> [1 1] [3 2] [4 8]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [2 4]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    s += "4 2 -> [5 2]\n4 3 -> [2 2] [5 5]\n4 4 -> [2 2] [5 6]\n";
    s += "4 5 -> [5 3]\n4 6 -> [5 4]\n4 7 -> [5 7]\n";
    s += "4 8 -> [2 2] [2 4] [5 8]\n4 9 -> [2 3] [5 3]\n";
    s += "5 2 -> [4 2]\n5 3 -> [4 5] [4 9]\n5 4 -> [4 6]\n5 5 -> [4 3]\n";
    s += "5 6 -> [4 4]\n5 7 -> [4 7]\n5 8 -> [4 8]\n";
    g.prune("a", "a2");
    s = "1 1 -> [2 2] [2 3] [2 4]\n";
    s += "2 2 -> [1 1] [3 1] [4 3] [4 4] [4 8]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4] [4 9]\n";
    s += "2 4 -> [1 1] [3 2] [4 8]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [2 4]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    s += "4 3 -> [2 2] [5 5]\n4 4 -> [2 2] [5 6]\n";
    s += "4 8 -> [2 2] [2 4] [5 8]\n4 9 -> [2 3] [5 3]\n";
    s += "5 3 -> [4 9]\n5 5 -> [4 3]\n5 6 -> [4 4]\n5 8 -> [4 8]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
}