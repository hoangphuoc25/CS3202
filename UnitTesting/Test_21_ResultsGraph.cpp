#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <utility>
#include "Test_21_ResultsGraph.h"
#include "../SPA/ResultsGraph.h"
#include "../SPA/StringBuffer.h"

using std::string;
using std::map;
using std::set;
using std::pair;
using std::make_pair;

void Test_21_ResultsGraph::setUp() {}

void Test_21_ResultsGraph::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_21_ResultsGraph);

void Test_21_ResultsGraph::test_empty_graph()
{
    ResultsGraph g;
    string s = g.toString();
    CPPUNIT_ASSERT_EQUAL(string(""), s);
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
}

void Test_21_ResultsGraph::test_add_vertex()
{
    ResultsGraph g;
    string s;
    g.add_vertex(ENT_ASSIGN, "avar", 3);
    g.add_vertex(ENT_STMT, "secondVar", 5);
    g.add_vertex(ENT_ASSIGN, "avar", 8);
    g.add_vertex(ENT_ASSIGN, "avar", 9);
    g.add_vertex(ENT_VAR, "bag", "a");
    g.add_vertex(ENT_VAR, "bag", "testString");
    g.add_vertex(ENT_PROC, "tummy", "hell");
    // Both Repeated
    g.add_vertex(ENT_ASSIGN, "avar", 3);
    // 2nd arg repeated
    g.add_vertex(ENT_VAR, "bag", "hell");
    // Both repeated
    g.add_vertex(ENT_VAR, "bag", "testString");

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
    set<pair<int, string> > vertexSet = g.get_synonym("avar");
    CPPUNIT_ASSERT_EQUAL(3, (int)vertexSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vertexSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vertexSet.count(make_pair(8, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vertexSet.count(make_pair(9, "")));
    vertexSet = g.get_synonym("secondVar");
    CPPUNIT_ASSERT_EQUAL(1, (int)vertexSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vertexSet.count(make_pair(5, "")));
    // string map:
    // a -> 1, testString -> 2, hell -> 3
    vertexSet = g.get_synonym("bag");
    CPPUNIT_ASSERT_EQUAL(3, (int)vertexSet.size());
    CPPUNIT_ASSERT_EQUAL(1,
            (int)vertexSet.count(make_pair(1, "a")));
    CPPUNIT_ASSERT_EQUAL(1,
            (int)vertexSet.count(make_pair(2, "testString")));
    CPPUNIT_ASSERT_EQUAL(1,
            (int)vertexSet.count(make_pair(3, "hell")));
    vertexSet = g.get_synonym("tummy");
    CPPUNIT_ASSERT_EQUAL(1,
            (int)vertexSet.count(make_pair(3, "hell")));
}

void Test_21_ResultsGraph::test_add_edge()
{
    ResultsGraph g;
    set<pair<int, string> > vSet;
    g.add_edge(ENT_ASSIGN, "some", 1, ENT_STMT, "to", 3);
    g.add_edge(ENT_WHILE, "me", 61, ENT_PROGLINE, "isnot", 146);
    g.add_edge(ENT_ASSIGN, "some", 6, ENT_ASSIGN, "other", 62);
    g.add_edge(ENT_ASSIGN, "some", 72, ENT_STMT, "another", 34);
    g.add_edge(ENT_WHILE, "me", 2, ENT_VAR, "animal", "first");
    g.add_edge(ENT_WHILE, "me", 5, ENT_STMT, "another", 65);
    g.add_edge(ENT_ASSIGN, "some", 52, ENT_STMT, "another", 99);
    // Repeated edge
    g.add_edge(ENT_ASSIGN, "some", 1, ENT_STMT, "to", 3);
    g.add_edge(ENT_PROC, "gvar", "second", ENT_VAR, "animal", "third");
    g.add_edge(ENT_PROC, "gvar", "fourth", ENT_VAR, "x", "fifth");
    // Repeated edge
    g.add_edge(ENT_VAR, "animal", "third", ENT_PROC, "gvar", "second");
    // Repeated edge
    g.add_edge(ENT_WHILE, "me", 2, ENT_VAR, "animal", "first");
    g.add_edge(ENT_PROC, "gvar", "sixth", ENT_PROC, "rage", "first");
    // Repeated edge
    g.add_edge(ENT_VAR, "animal", "first", ENT_WHILE, "me", 2);
    g.add_edge(ENT_ASSIGN, "other", 62, ENT_WHILE, "me", 2);

    // syn mapping
    // some = 1    [assign]
    // to = 2      [stmt]
    // me = 3      [while]
    // isnot = 4   [progline]
    // other = 5   [assign]
    // another = 6 [stmt]
    // animal = 7  [variable]
    // gvar = 8    [procedure]
    // x = 9       [variable]
    // rage = 10   [procedure]

    // string mapping
    // first = 1, second = 2, third = 3, fourth = 4, fifth = 5
    // sixth = 6
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
    vSet = g.get_synonym("some");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(6, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(52, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(72, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("to"));
    vSet = g.get_synonym("to");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("me"));
    vSet = g.get_synonym("me");
    CPPUNIT_ASSERT_EQUAL(3, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(5, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(61, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("isnot"));
    vSet = g.get_synonym("isnot");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(146, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("other"));
    vSet = g.get_synonym("other");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(62, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("another"));
    vSet = g.get_synonym("another");
    CPPUNIT_ASSERT_EQUAL(3, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(34, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(65, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(99, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("animal"));
    vSet = g.get_synonym("animal");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "first")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "third")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("gvar"));
    vSet = g.get_synonym("gvar");
    CPPUNIT_ASSERT_EQUAL(3, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "second")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "fourth")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(6, "sixth")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("x"));
    vSet = g.get_synonym("x");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(5, "fifth")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("rage"));
    vSet = g.get_synonym("rage");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "first")));
}

void Test_21_ResultsGraph::test_prune_add_all()
{
    ResultsGraph g;
    string s;
    set<pair<int, string> > vSet;

    g.add_edge(ENT_ASSIGN, "assembly", 1, ENT_STMT, "c", 2);
    g.add_edge(ENT_ASSIGN, "assembly", 1, ENT_STMT, "c", 6);
    g.add_edge(ENT_ASSIGN, "assembly", 5, ENT_STMT, "c", 67);
    g.add_edge(ENT_ASSIGN, "assembly", 7, ENT_STMT, "c", 9);
    g.prune("assembly", "c");
    s = "1 1 -> [2 2] [2 6]\n1 5 -> [2 67]\n1 7 -> [2 9]\n";
    s += "2 2 -> [1 1]\n2 6 -> [1 1]\n2 9 -> [1 7]\n2 67 -> [1 5]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("assembly"));
    vSet = g.get_synonym("assembly");
    CPPUNIT_ASSERT_EQUAL(3, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(5, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(7, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("c"));
    vSet = g.get_synonym("c");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(6, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(9, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(67, "")));

    // this prune will kill off everything
    // but the super vertices still exist
    g.prune("assembly", "c");
    s = "";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("assembly"));
    vSet = g.get_synonym("assembly");
    CPPUNIT_ASSERT_EQUAL(0, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("c"));
    vSet = g.get_synonym("c");
    CPPUNIT_ASSERT_EQUAL(0, (int)vSet.size());
    // graph is now dead
    CPPUNIT_ASSERT_EQUAL(false, g.is_alive());
}

void Test_21_ResultsGraph::test_prune_nonempty_death()
{
    // 1. a = b + c
    // 2. g = 3 + d
    ResultsGraph g;
    set<pair<int, string> > vSet;
    string s;

    // evaluate:
    // Uses(a,v)
    // Uses(a2,v2)
    // Modifies(a3,v)
    g.add_edge(ENT_ASSIGN, "a", 1, ENT_VAR, "v", "b");
    g.add_edge(ENT_ASSIGN, "a", 1, ENT_VAR, "v", "c");
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_VAR, "v", "d");
    g.prune("a", "v");
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
    g.add_edge(ENT_ASSIGN, "a2", 1, ENT_VAR, "v2", "b");
    g.add_edge(ENT_ASSIGN, "a2", 1, ENT_VAR, "v2", "c");
    g.add_edge(ENT_ASSIGN, "a2", 2, ENT_VAR, "v2", "d");
    g.prune("a2", "v2");
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
    g.prune("a3", "v");
    CPPUNIT_ASSERT_EQUAL(false, g.is_alive());
    // syn map:
    // a -> 1, v -> 2, a2 -> 3, v2 -> 4
    // string map:
    // b -> 1, c -> 2, d -> 3
    s = "1 1 -> [2 1] [2 2]\n1 2 -> [2 3]\n";
    s += "2 1 -> [1 1]\n2 2 -> [1 1]\n2 3 -> [1 2]\n";
    s += "3 1 -> [4 1] [4 2]\n3 2 -> [4 3]\n";
    s += "4 1 -> [3 1]\n4 2 -> [3 1]\n4 3 -> [3 2]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
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
    set<pair<int, string> > vSet;
    string s;
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 2);
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 3);
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1]\n2 3 -> [1 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    // same after pruning
    g.prune("w", "a");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));

    // synmap
    // w -> 1, a -> 2, v -> 3
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_VAR, "v", "g");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "b");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "c");
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1] [3 1]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("w"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "g")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "a")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "b")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "c")));
    // same after pruning
    g.prune("a", "v");
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("w"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a"));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "g")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "a")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "b")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "c")));

    // synmap
    // w -> 1, a -> 2, v -> 3, a2 -> 4
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4
    g.add_edge(ENT_ASSIGN, "a2", 2, ENT_VAR, "v", "a");
    s = "1 1 -> [2 2] [2 3]\n2 2 -> [1 1] [3 1]\n";
    s += "2 3 -> [1 1] [3 2] [3 3] [3 4]\n";
    s += "3 1 -> [2 2]\n3 2 -> [2 3] [4 2]\n3 3 -> [2 3]\n3 4 -> [2 3]\n";
    s += "4 2 -> [3 2]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("w"));
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a"));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(2, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "g")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "a")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "b")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "c")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a2"));
    vSet = g.get_synonym("a2");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    // pruning changes graph
    g.prune("a2", "v");
    s = "1 1 -> [2 3]\n2 3 -> [1 1] [3 2]\n3 2 -> [2 3] [4 2]\n";
    s += "4 2 -> [3 2]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("w"));
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "a")));
    vSet = g.get_synonym("a2");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
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
    set<pair<int, string> > vSet;
    string s;

    // synmap
    // a -> 1, v -> 2
    // string map
    // c -> 1, a -> 2, z -> 3, b -> 4
    g.add_edge(ENT_ASSIGN, "a", 1, ENT_VAR, "v", "c");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 4, ENT_VAR, "v", "z");
    g.add_edge(ENT_ASSIGN, "a", 8, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 6, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 5, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 5, ENT_VAR, "v", "b");

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
    g.add_edge(ENT_ASSIGN, "a2", 6, ENT_VAR, "v", "c");
    g.add_edge(ENT_ASSIGN, "a2", 1, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a2", 2, ENT_VAR, "v", "b");
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

    g.add_edge(ENT_ASSIGN, "a", 1, ENT_ASSIGN, "a2", 6);
    g.prune("a", "a2");
    s = "1 1 -> [2 1] [3 6]\n2 1 -> [1 1] [3 6]\n3 6 -> [1 1] [2 1]\n";
    CPPUNIT_ASSERT_EQUAL(s, g.toString());
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a"));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "c")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a2"));
    vSet = g.get_synonym("a2");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(6, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
}

void Test_21_ResultsGraph::test_prune_3()
{
    ResultsGraph g;
    set<pair<int, string> > vSet;
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
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 2);
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 3);
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 4);
    g.add_edge(ENT_WHILE, "w", 1, ENT_ASSIGN, "a", 5);
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
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_VAR, "v", "g");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "a");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "b");
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_VAR, "v", "c");
    g.add_edge(ENT_ASSIGN, "a", 4, ENT_VAR, "v", "a");
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
    g.add_edge(ENT_ASSIGN, "a2", 2, ENT_VAR, "v2", "a");
    g.add_edge(ENT_ASSIGN, "a2", 3, ENT_VAR, "v2", "y");
    g.add_edge(ENT_ASSIGN, "a2", 4, ENT_VAR, "v2", "x");
    g.add_edge(ENT_ASSIGN, "a2", 5, ENT_VAR, "v2", "b");
    g.add_edge(ENT_ASSIGN, "a2", 6, ENT_VAR, "v2", "c");
    g.add_edge(ENT_ASSIGN, "a2", 7, ENT_VAR, "v2", "w");
    g.add_edge(ENT_ASSIGN, "a2", 8, ENT_VAR, "v2", "z");
    g.add_edge(ENT_ASSIGN, "a2", 9, ENT_VAR, "v2", "b");
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
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_ASSIGN, "a2", 3);
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_ASSIGN, "a2", 4);
    g.add_edge(ENT_ASSIGN, "a", 2, ENT_ASSIGN, "a2", 8);
    g.add_edge(ENT_ASSIGN, "a", 3, ENT_ASSIGN, "a2", 9);
    g.add_edge(ENT_ASSIGN, "a", 4, ENT_ASSIGN, "a2", 8);
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
    // w -> 1, a -> 2, v -> 3, a2 -> 4, v2 -> 5
    // stringmap
    // g -> 1, a -> 2, b -> 3, c -> 4, y -> 5, x -> 6, w -> 7, z -> 8
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("w"));
    vSet = g.get_synonym("w");
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a"));
    vSet = g.get_synonym("a");
    CPPUNIT_ASSERT_EQUAL(3, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v"));
    vSet = g.get_synonym("v");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(1, "g")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(2, "a")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "b")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "c")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("a2"));
    vSet = g.get_synonym("a2");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(4, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(8, "")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(9, "")));
    CPPUNIT_ASSERT_EQUAL(true, g.has_syn("v2"));
    vSet = g.get_synonym("v2");
    CPPUNIT_ASSERT_EQUAL(4, (int)vSet.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(3, "b")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(5, "y")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(6, "x")));
    CPPUNIT_ASSERT_EQUAL(1, (int)vSet.count(make_pair(8, "z")));
    CPPUNIT_ASSERT_EQUAL(true, g.is_alive());
}