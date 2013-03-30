#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include "Test_20_PQLParser_With.h"
#include "../SPA/PQLParser.h"

using std::string;
using std::map;
using std::ostringstream;
using std::set;
using std::pair;

void Test_20_PQLParser_With::setUp()
{
    this->buf = new char[Test_20_PQLParser_With::BUFLEN+5];
}

void Test_20_PQLParser_With::tearDown()
{
    delete[] this->buf;
}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_PQLParser_With);

void Test_20_PQLParser_With::test_with_string_string_same()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // 1 string with
    queryStr = " assign a; Select a with \"bad\"\t\n= \n\t \"bad\"  ";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    // strings which are the same dont get reflected
    out = "ALIVE\nDECLARATIONS\n  assign a\nSELECT TUPLE\n  assign a\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // 4 string with
    queryStr = "assign a; call c; Select <c,a> with \"utc\" = \"utc\" ";
    queryStr += "\t\t\n and\t\n \"joke\"\n\n\t =\n\n\t\t \"joke\" and ";
    queryStr += " \"Sfv\" = \"Sfv\" and \"sharp\" = \"sharp\"";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a\n  call c\nSELECT TUPLE\n";
    out += "  call c\n  assign a\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // mixed Relation clauses and WithClause
    queryStr = " assign a1, a2; while w1, w2; call c1, c2; ";
    queryStr += " variable v1, v2; procedure p1, p2; ";
    queryStr += " Select <a1.stmt#, c2.procName, c1, p2, v1.varName> ";
    queryStr += " such that Modifies(a1, v1) and Calls(p1, p2) ";
    queryStr += " with \"cbd\" = \"cbd\" and \"Teller\" = \"Teller\" ";
    queryStr += " and \"Mike\" = \"Mike\" such that Parent(w1, c2) and ";
    queryStr += " Affects*(a1, a2) with \"brave\" = \"brave\" and ";
    queryStr += " \"andrea\" = \"andrea\" and \"google\" = \"google\" ";
    queryStr += " and \"Georgia\" = \"Georgia\" such that Uses(a1, v1) ";
    queryStr += " and Uses(p1, v2) with \"friend\" = \"friend\"";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n  while w1\n";
    out += "  while w2\n  call c1\n  call c2\n  variable v1\n";
    out += "  variable v2\n  procedure p1\n  procedure p2\n";
    out += "SELECT TUPLE\n  assign a1 stmt#\n  call c2 procName\n";
    out += "  call c1\n  procedure p2\n  variable v1 varName\n";
    out += "Modifies(a1,v1)\nCalls(p1,p2)\nParent(w1,c2)\n";
    out += "Affects*(a1,a2)\nUses(a1,v1)\nUses(p1,v2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::test_with_string_string_different_halt()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // LHS of 1st WithClause is not equal
    queryStr = "assign a1; Select a1 with \"first\" = \"second\"";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // RHS of 3rd WithClause is not equal
    queryStr = "procedure p1; variable v2; Select <p1, v2> with ";
    queryStr += " \"single\" = \"single\" and \"T\" = \"T\" and ";
    queryStr += " \"friend\" = \"Friend\" and \"junk\" = \"junk\" ";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // query above is alive without 3rd WithClause
    queryStr = "procedure p1; variable v2; Select <p1, v2> with ";
    queryStr += " \"single\" = \"single\" and \"T\" = \"T\" and ";
    queryStr += " \"junk\" = \"junk\" ";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  procedure p1\n  variable v2\n";
    out += "SELECT TUPLE\n  procedure p1\n  variable v2\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());

    // Relation + With, 6th WithClause is different
    queryStr = " assign a1, a2; while w1, w2; if if1, if2; call c1, c2;";
    queryStr += " procedure p1, p2; variable v1, v2; ";
    queryStr += " Select <w1, w2.stmt#, if1, c1.procName, p2, a1> ";
    queryStr += " with \"jack\" = \"jack\" and \"reacher\" = \"reacher\"";
    queryStr += " such that Modifies(a2, v1) and Parent(if1, c2) ";
    queryStr += " with \"b\" = \"b\" and \"Ch\" = \"Ch\" and ";
    queryStr += " \"Tree\" = \"Tree\" such that Parent*(w2, if2) and ";
    queryStr += " Affects(a2,a1) and Uses(p2, v2) ";
    queryStr += " with \"Bull\" = \"crap\" and \"book\" = \"book\" ";
    queryStr += " such that Calls(p2, p1) and Modifies(c2, v2)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above query is true with corrected 6th WithClause
    queryStr = " assign a1, a2; while w1, w2; if if1, if2; call c1, c2;";
    queryStr += " procedure p1, p2; variable v1, v2; ";
    queryStr += " Select <w1, w2.stmt#, if1, c1.procName, p2, a1> ";
    queryStr += " with \"jack\" = \"jack\" and \"reacher\" = \"reacher\"";
    queryStr += " such that Modifies(a2, v1) and Parent(if1, c2) ";
    queryStr += " with \"b\" = \"b\" and \"Ch\" = \"Ch\" and ";
    queryStr += " \"Tree\" = \"Tree\" such that Parent*(w2, if2) and ";
    queryStr += " Affects(a2,a1) and Uses(p2, v2) ";
    queryStr += " with \"Bull\" = \"Bull\" and \"book\" = \"book\" ";
    queryStr += " such that Calls(p2, p1) and Modifies(c2, v2)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n  while w1\n";
    out += "  while w2\n  if if1\n  if if2\n  call c1\n  call c2\n";
    out += "  procedure p1\n  procedure p2\n  variable v1\n";
    out += "  variable v2\nSELECT TUPLE\n  while w1\n  while w2 stmt#\n";
    out += "  if if1\n  call c1 procName\n  procedure p2\n  assign a1\n";
    out += "Modifies(a2,v1)\nParent(if1,c2)\nParent*(w2,if2)\n";
    out += "Affects(a2,a1)\nUses(p2,v2)\nCalls(p2,p1)\nModifies(c2,v2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
}

void Test_20_PQLParser_With::test_with_int_int_same()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // 1 WithClause
    queryStr = " call callOne; Select callOne with 6575 = 6575";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  call callOne\nSELECT TUPLE\n";
    out += "  call callOne\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    // 1 WithClause, negative integers
    queryStr = " Select BOOLEAN with -3468 = -3468";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    // 1 WithClause, largest integer
    queryStr = " Select BOOLEAN with 2147483647 = 2147483647";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    // 1 WithClause, smallest integer
    queryStr = " Select BOOLEAN with -2147483648 = -2147483648";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // 6 WithClause with max int, min int, negative int
    queryStr = " assign a1; variable v2; Select <v2, a1> with ";
    queryStr += " 2147483647 = 2147483647 and 125 = 125 and ";
    queryStr += " -735 = -735 and -2147483648 = -2147483648 and 0=0 ";
    queryStr += " and 1=1";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  variable v2\n";
    out += "SELECT TUPLE\n  variable v2\n  assign a1\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Mixed Relation + WithClauses with max int, min int, negative int
    queryStr = " variable var1, var2, var3; procedure proc1, proc2; ";
    queryStr += " call c1, c2; assign a1, a2; stmt s1, s2; ";
    queryStr += " Select <c1.procName, a2, var3, proc2.procName, s2> ";
    queryStr += " with 687= 687 such that Modifies(c2, var3) and ";
    queryStr += " Parent(s1, a1) with 2147483647 = 2147483647 and ";
    queryStr += " -166=-166 such that Calls(proc1, proc2) and ";
    queryStr += " Next*(c1, a2) with 0 = 0 and ";
    queryStr += " -2147483648 = -2147483648 and 5755=5755 such that ";
    queryStr += " Affects*(a1,a2) and Next(s2, s1)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable var1\n  variable var2\n";
    out += "  variable var3\n  procedure proc1\n  procedure proc2\n";
    out += "  call c1\n  call c2\n  assign a1\n  assign a2\n  stmt s1\n";
    out += "  stmt s2\nSELECT TUPLE\n  call c1 procName\n  assign a2\n";
    out += "  variable var3\n  procedure proc2 procName\n  stmt s2\n";
    out += "Modifies(c2,var3)\nParent(s1,a1)\nCalls(proc1,proc2)\n";
    out += "Next*(c1,a2)\nAffects*(a1,a2)\nNext(s2,s1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::test_with_int_int_different_halt()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // 1 different integer
    queryStr = "assign a24; Select a24  with 77 = 88 ";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // 3 WithClause, different integer at 3rd WithClause
    queryStr = "Select BOOLEAN with 777=777 and -146 = -146 and ";
    queryStr += " 35757 = -11";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // Relations + WithClause. different integer at 7th WithClause
    queryStr = " call c1, c2; procedure proc1, proc2; assign a1, a2; ";
    queryStr += " variable var1, var2; while w1, w2; prog_line pl1, pl2;";
    queryStr += " Select <var1.varName, proc2, pl1, a2.stmt#> such that ";
    queryStr += " Modifies(c2, var2) with 2334 = 2334 and 0 = 0 ";
    queryStr += " such that Uses(proc2, var1) and Next(pl2, a2) and ";
    queryStr += " Affects(a2, a1) with 777 = 777 and ";
    queryStr += " 2147483644 = 2147483644 and 688 = 688 such that ";
    queryStr += " Calls(proc1, proc2) and Parent(w2, c2) with ";
    queryStr += " 56879 = 56879 and 2456 = -2456 such that ";
    queryStr += " Follows(pl1, c2) and Next*(a2, c2)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above query corrected
    queryStr = " call c1, c2; procedure proc1, proc2; assign a1, a2; ";
    queryStr += " variable var1, var2; while w1, w2; prog_line pl1, pl2;";
    queryStr += " Select <var1.varName, proc2, pl1, a2.stmt#> such that ";
    queryStr += " Modifies(c2, var2) with 2334 = 2334 and 0 = 0 ";
    queryStr += " such that Uses(proc2, var1) and Next(pl2, a2) and ";
    queryStr += " Affects(a2, a1) with 777 = 777 and ";
    queryStr += " 2147483644 = 2147483644 and 688 = 688 such that ";
    queryStr += " Calls(proc1, proc2) and Parent(w2, c2) with ";
    queryStr += " 56879 = 56879 and -2456 = -2456 such that ";
    queryStr += " Follows(pl1, c2) and Next*(a2, c2)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  call c1\n  call c2\n";
    out += "  procedure proc1\n  procedure proc2\n  assign a1\n";
    out += "  assign a2\n  variable var1\n  variable var2\n  while w1\n";
    out += "  while w2\n  prog_line pl1\n  prog_line pl2\nSELECT TUPLE\n";
    out += "  variable var1 varName\n  procedure proc2\n";
    out += "  prog_line pl1\n  assign a2 stmt#\nModifies(c2,var2)\n";
    out += "Uses(proc2,var1)\nNext(pl2,a2)\nAffects(a2,a1)\n";
    out += "Calls(proc1,proc2)\nParent(w2,c2)\nFollows(pl1,c2)\n";
    out += "Next*(a2,c2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
}

void Test_20_PQLParser_With::test_with_normalize()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // normalize insertion
    queryStr = " assign a; Select a with 3 = a.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a\nSELECT TUPLE\n";
    out += "  assign a\na.stmt# = 3\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // duplicated with clause but different LHS and RHS ordering
    queryStr = " assign a; prog_line pl; call c; procedure p; ";
    queryStr += " Select <a,pl.prog_line#> such that Modifies(a,\"v\") ";
    queryStr += " and Uses(c,\"someVar\") with a.stmt# = 33 and ";
    queryStr += " pl = 56 such that Next*(a,pl) with ";
    queryStr += " p.procName = c.procName and c.procName = p.procName ";
    queryStr += " and c.procName = \"someProc\"";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a\n  prog_line pl\n  call c\n";
    out += "  procedure p\nSELECT TUPLE\n  assign a\n";
    out += "  prog_line pl prog_line#\nModifies(a,\"v\")\n";
    out += "Uses(c,\"someVar\")\na.stmt# = 33\npl = 56\nNext*(a,pl)\n";
    out += "c.procName = p.procName\nc.procName = \"someProc\"\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::test_with_contradiction()
{
    string queryStr, out;
    PQLParser parser;
    QueryInfo *qinfo;

    // value mismatch
    queryStr = "assign a; Select a with 1 = 267";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    queryStr = " call c1; Select c1 with \"abc\" = \"def\"";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_VALUE_MISMATCH,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // 2 synonym contradiction
    queryStr = " assign a; prog_line pl; variable v; while w; ";
    queryStr += " Select <a,pl,v.varName> such that Modifies(a,\"v\")";
    queryStr += " and Parent(w,a) with pl = 56 and v.varName = \"x\" ";
    queryStr += " such that Uses(w,v) with w.stmt# = a.stmt# and ";
    queryStr += " w.stmt# = 89";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_CONTRADICTION,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above corrected
    queryStr = " assign a; prog_line pl; variable v; while w; ";
    queryStr += " Select <a,pl,v.varName> such that Modifies(a,\"v\")";
    queryStr += " and Parent(w,a) with pl = 56 and v.varName = \"x\" ";
    queryStr += " such that Uses(w,v) with 123 = a.stmt# and ";
    queryStr += " w.stmt# = 89";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
    out = "ALIVE\nDECLARATIONS\n  assign a\n  prog_line pl\n";
    out += "  variable v\n  while w\nSELECT TUPLE\n  assign a\n";
    out += "  prog_line pl\n  variable v varName\nModifies(a,\"v\")\n";
    out += "Parent(w,a)\npl = 56\nv.varName = \"x\"\nUses(w,v)\n";
    out += "a.stmt# = 123\nw.stmt# = 89\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::test_err_parse_dquoted_ident_invalid()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // 1st argument not valid identifier
    queryStr = "assign a; Select a with \"1ab\" = \"c\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "1ab");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // 2nd argument not valid identifier
    queryStr = "assign a; Select a with \"pkb\"  = \"#tyh\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "#tyh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // 1st argument of 3rd with clause is an invalid identifier
    queryStr = "while w; procedure p;";
    queryStr += " Select <w,p> with \"a\" = \"a\" and \t \n ";
    queryStr += " w.stmt# \n\t = \t\t13 and \"#gff\" = \"bcd\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "#gff");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // 2nd argument of 4th with clause is an invalid identifier
    queryStr = "procedure p; assign a1, a2; variable v; ";
    queryStr += " Select <a1,v,p> such that Modifies(p,v) and ";
    queryStr += " Uses(a1, v) with \"alpha\" = \"alpha\" and ";
    queryStr += " 2 = 2 and a1.stmt# = a2.stmt# and \"brave\" = \",s1\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, ",s1");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
}

void Test_20_PQLParser_With::
             test_err_parse_dquoted_ident_missing_close_quote()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // LHS of 1st with clause missing close quote
    queryStr = " call c; Select c with \"ableh = \"b\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "ableh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // RHS of 2nd with clause missing close quote
    queryStr = " assign aS1; variable VaR; while w1; ";
    queryStr += " Select <aS1, VaR, w1> with 1 = 1 and ";
    queryStr += " \"bomb\" = \"tim and 35 = 35";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "tim");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());

    // LHS of 4th with clause missing close quote
    queryStr = "assign a1, a2; variable v; call c1; procedure p1; ";
    queryStr += "Select <a1.stmt#, c1.procName, v.varName> ";
    queryStr += " such that Modifies(a1,v) and Uses(p1, v) ";
    queryStr += " with \"abc\" = \"abc\" and 6324 = 6324 ";
    queryStr += " such that Modifies(c1, v) and Affects(a2,a1) ";
    queryStr += " with a1.stmt# = c1.stmt# and \"done\" = \"haha and";
    queryStr += " 6775 = 6775";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "haha");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
}

void Test_20_PQLParser_With::test_err_parse_ref_integer_error_str()
{
    string queryStr, out, warningStr;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    long long tmpLL;

    // string is too long
    queryStr = " assign a; Select a with 57 = 12345678901";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_TOO_LONG);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "12345678901", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // string is too long for RHS of 3rd WithClause
    queryStr = "assign a; procedure procN; Select <procN, a> with ";
    queryStr += " 65 = 65 and 1=1 and 99=75562484845445";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_TOO_LONG);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "75562484845445", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // Relations + WithClause
    // string is too long for RHS of 5th WithClause
    queryStr = " assign as1, as2; procedure proc1, proc2; call c1, c2; ";
    queryStr += " while w1, w2; if if1, if2; variable var1, var2; ";
    queryStr += " Select <as1, w2.stmt#, if2, proc2.procName, c2.stmt#> ";
    queryStr += " with 1=1 and -6246 = -6246 such that ";
    queryStr += " Modifies(as1, var1) and Calls(proc1, proc2) with ";
    queryStr += " 3664=3664 such that Parent*(w2, if2) and ";
    queryStr += " Uses(if2,var2) and Modifies(c1, var1) with ";
    queryStr += " 75633=887967845652 and 39=39 such that ";
    queryStr += " Uses(proc2,var2) and Follows(if1, c2) with 18=18";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_TOO_LONG);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "887967845652", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above query is correct without 5th WithClause
    queryStr = " assign as1, as2; procedure proc1, proc2; call c1, c2; ";
    queryStr += " while w1, w2; if if1, if2; variable var1, var2; ";
    queryStr += " Select <as1, w2.stmt#, if2, proc2.procName, c2.stmt#> ";
    queryStr += " with 1=1 and -6246 = -6246 such that ";
    queryStr += " Modifies(as1, var1) and Calls(proc1, proc2) with ";
    queryStr += " 3664=3664 such that Parent*(w2, if2) and ";
    queryStr += " Uses(if2,var2) and Modifies(c1, var1) with ";
    queryStr += " 39=39 such that ";
    queryStr += " Uses(proc2,var2) and Follows(if1, c2) with 18=18";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign as1\n  assign as2\n";
    out += "  procedure proc1\n  procedure proc2\n  call c1\n  call c2\n";
    out += "  while w1\n  while w2\n  if if1\n  if if2\n";
    out += "  variable var1\n  variable var2\nSELECT TUPLE\n";
    out += "  assign as1\n  while w2 stmt#\n  if if2\n";
    out += "  procedure proc2 procName\n  call c2 stmt#\n";
    out += "Modifies(as1,var1)\nCalls(proc1,proc2)\nParent*(w2,if2)\n";
    out += "Uses(if2,var2)\nModifies(c1,var1)\nUses(proc2,var2)\n";
    out += "Follows(if1,c2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());

    // overflow by 1
    queryStr = " assign a; Select a with 15636 = 2147483648";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 2147483648LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "2147483648", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // overflow by 1 in 4th WithClause
    queryStr = "Select BOOLEAN with 17=17 and 236=236 and ";
    queryStr += " 775 = 2147483648";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 2147483648LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "2147483648", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // Relations + WithClause. overflow by 1 in 8th WithClause
    queryStr = "assign a1, a2; while w1, w2; procedure p1, p2; ";
    queryStr += " stmt s1, s2; call c1, c2; variable v1, v2; ";
    queryStr += " Select <s1.stmt#, c1> with 166 = 166 and 1=1  ";
    queryStr += " such that Modifies(a2, v1) and Uses(p2, v1) and ";
    queryStr += " Parent*(s2,w2) ";
    queryStr += " with 3466 = 3466 and -1246 = -1246 and 7457 = 7457 ";
    queryStr += " such that Calls*(p2, p1) and Next(a2, c2) with ";
    queryStr += " 66 = 66 and 89 = 89 and 677 = 2147483648 and 22 = 22 ";
    queryStr += " such that Modifies(s2, v2)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 2147483648LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "2147483648", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above query corrected
    queryStr = "assign a1, a2; while w1, w2; procedure p1, p2; ";
    queryStr += " stmt s1, s2; call c1, c2; variable v1, v2; ";
    queryStr += " Select <s1.stmt#, c1> with 166 = 166 and 1=1  ";
    queryStr += " such that Modifies(a2, v1) and Uses(p2, v1) and ";
    queryStr += " Parent*(s2,w2) ";
    queryStr += " with 3466 = 3466 and -1246 = -1246 and 7457 = 7457 ";
    queryStr += " such that Calls*(p2, p1) and Next(a2, c2) with ";
    queryStr += " 66 = 66 and 89 = 89 and 677 = 677 and 22 = 22 ";
    queryStr += " such that Modifies(s2, v2)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n  while w1\n";
    out += "  while w2\n  procedure p1\n  procedure p2\n  stmt s1\n";
    out += "  stmt s2\n  call c1\n  call c2\n  variable v1\n";
    out += "  variable v2\nSELECT TUPLE\n  stmt s1 stmt#\n  call c1\n";
    out += "Modifies(a2,v1)\nUses(p2,v1)\nParent*(s2,w2)\n";
    out += "Calls*(p2,p1)\nNext(a2,c2)\nModifies(s2,v2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());

    // overflow by a lot
    queryStr = "Select BOOLEAN with 33 = 3234567890";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 3234567890LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "3234567890", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // overflow by a lot in 4th WithClause
    queryStr = " while whg; procedure Bsd; Select <whg, Bsd> with ";
    queryStr += " 1245 = 1245 and 77 = 77 and 7457 = 7457 and ";
    queryStr += " 27568 = 5634567890";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 5634567890LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "5634567890", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // Relations + WithClause. overflow by a lot in 6th WithClause
    queryStr = " procedure pr1, pr2; variable v1, v2; assign a2, a1; ";
    queryStr += " call c2, c1; while w1, w2; prog_line pl1, pl2; ";
    queryStr += " Select <c2.procName, pl1, w2.stmt#, a1, v2.varName> ";
    queryStr += " with 1=1 and 777= 777 such that Modifies(pl2, v2) ";
    queryStr += " and Follows(w1, pl2) and Uses(a2, v2) with 6=6 and ";
    queryStr += " 87763= 87763 such that Parent(w1, a1) with ";
    queryStr += " 8688=8688 and 346636= 7684567890 and 77=77 such that ";
    queryStr += " Calls*(pr2,pr1) and Follows(pl2, c1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REF_INTEGER_ERROR,
            parser.get_parse_result());
    tmpLL = 7684567890LL;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            S_TO_INT_OVERFLOW, tmpLL);
    warningStr = string(this->buf);
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_REF_INTEGER_ERROR_STR,
            "7684567890", warningStr.c_str());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    // above query corrected
    queryStr = " procedure pr1, pr2; variable v1, v2; assign a2, a1; ";
    queryStr += " call c2, c1; while w1, w2; prog_line pl1, pl2; ";
    queryStr += " Select <c2.procName, pl1, w2.stmt#, a1, v2.varName> ";
    queryStr += " with 1=1 and 777= 777 such that Modifies(pl2, v2) ";
    queryStr += " and Follows(w1, pl2) and Uses(a2, v2) with 6=6 and ";
    queryStr += " 87763= 87763 such that Parent(w1, a1) with ";
    queryStr += " 8688=8688 and 346636= 346636 and 77=77 such that ";
    queryStr += " Calls*(pr2,pr1) and Follows(pl2, c1)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  procedure pr1\n  procedure pr2\n";
    out += "  variable v1\n  variable v2\n  assign a2\n  assign a1\n";
    out += "  call c2\n  call c1\n  while w1\n  while w2\n";
    out += "  prog_line pl1\n  prog_line pl2\nSELECT TUPLE\n";
    out += "  call c2 procName\n  prog_line pl1\n  while w2 stmt#\n";
    out += "  assign a1\n  variable v2 varName\nModifies(pl2,v2)\n";
    out += "Follows(w1,pl2)\nUses(a2,v2)\nParent(w1,a1)\n";
    out += "Calls*(pr2,pr1)\nFollows(pl2,c1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
}

void Test_20_PQLParser_With::
        test_err_parse_withclause_ref_synonym_undeclared()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;

    // LHS of 1st WithClause is undeclared synonym
    queryStr = "assign a; Select a with as1 = a.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "as1");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // RHS of 1st WithClause is undeclared synonym
    queryStr = "call c1; Select c1 with c1.stmt# = B2i";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "B2i");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // LHS of 3rd WithClause is undeclared synonym
    queryStr = "call c1, c2; assign a1, a2; ";
    queryStr += " Select <a1,c1> with 12 = 12 and 13 = 13 and ";
    queryStr += " asc = a1.stmt# and 157 = 157";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "asc");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // RHS of 3rd WithClause is undeclared synonym
    queryStr = " assign a1; procedure p2; ";
    queryStr += " Select <p2.procName, a1> with 1=1 and 2=2 and ";
    queryStr += " a1.stmt# = basic and 3 = 3";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "basic");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // LHS of 6th WithClause is undeclared synonym
    queryStr = " assign a1, a2; procedure proc1, proc2; call c1, c2;";
    queryStr += " stmt s1, s2; prog_line pl1, pl2; variable v1, v2;";
    queryStr += " Select <a2.stmt#, proc2.procName, c1.stmt#, pl1> ";
    queryStr += " with 1=1 and 36=36 such that Uses(pl2, v2) and ";
    queryStr += " Modifies(proc1, v1) with 377= 377 and 0=0 and -1=-1";
    queryStr += " such that Parent(pl1, s1) and Next*(s1, c1) with ";
    queryStr += " pl1 = somePL and 856=856 such that ";
    queryStr += " Calls(proc2, proc1) and Affects(a2,a1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "somePL");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // above query corrected
    queryStr = " assign a1, a2; procedure proc1, proc2; call c1, c2;";
    queryStr += " stmt s1, s2; prog_line pl1, pl2; variable v1, v2;";
    queryStr += " Select <a2.stmt#, proc2.procName, c1.stmt#, pl1> ";
    queryStr += " with 1=1 and 36=36 such that Uses(pl2, v2) and ";
    queryStr += " Modifies(proc1, v1) with 377= 377 and 0=0 and -1=-1";
    queryStr += " such that Parent(pl1, s1) and Next*(s1, c1) with ";
    queryStr += " pl1 = pl1 and 856=856 such that ";
    queryStr += " Calls(proc2, proc1) and Affects(a2,a1)";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n";
    out += "  procedure proc1\n  procedure proc2\n  call c1\n";
    out += "  call c2\n  stmt s1\n  stmt s2\n  prog_line pl1\n";
    out += "  prog_line pl2\n  variable v1\n  variable v2\n";
    out += "SELECT TUPLE\n  assign a2 stmt#\n  procedure proc2 procName\n";
    out += "  call c1 stmt#\n  prog_line pl1\nUses(pl2,v2)\n";
    out += "Modifies(proc1,v1)\nParent(pl1,s1)\nNext*(s1,c1)\n";
    out += "Calls(proc2,proc1)\nAffects(a2,a1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // RHS of 7th WithClause is undeclared synonym
    queryStr = " prog_line pl1, pl2; stmt s1, s2; constant c1, c2; ";
    queryStr += " procedure proc1, proc2; variable var1, var2; ";
    queryStr += " assign a1, a2; if if1, if2; ";
    queryStr += " Select <pl1, if1.stmt#, var2.varName, c1.value, ";
    queryStr += "  proc1.procName> with 1=1 and 25=25 such that ";
    queryStr += " Modifies(if2, var2) and Calls(proc2, \"game\") and ";
    queryStr += " Affects*(a2,a1) with 77=77 and 11566=11566 and ";
    queryStr += " 89 = 89 such that Parent*(if1, pl2) and ";
    queryStr += " Follows*(pl2, a2) with 0=0 and pl1 = anotherPL ";
    queryStr += " such that Next(s1,pl1) and Parent(s2, pl1) with ";
    queryStr += " 78889 = 78889";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    qinfo = parser.get_queryinfo();
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
            parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(false, qinfo->is_alive());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, "anotherPL");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // above query corrected
    queryStr = " prog_line pl1, pl2; stmt s1, s2; constant c1, c2; ";
    queryStr += " procedure proc1, proc2; variable var1, var2; ";
    queryStr += " assign a1, a2; if if1, if2; ";
    queryStr += " Select <pl1, if1.stmt#, var2.varName, c1.value, ";
    queryStr += "  proc1.procName> with 1=1 and 25=25 such that ";
    queryStr += " Modifies(if2, var2) and Calls(proc2, \"game\") and ";
    queryStr += " Affects*(a2,a1) with 77=77 and 11566=11566 and ";
    queryStr += " 89 = 89 such that Parent*(if1, pl2) and ";
    queryStr += " Follows*(pl2, a2) with 0=0 and pl1 = pl1 ";
    queryStr += " such that Next(s1,pl1) and Parent(s2, pl1) with ";
    queryStr += " 78889 = 78889";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(true, qinfo->is_alive());
    out = "ALIVE\nDECLARATIONS\n  prog_line pl1\n  prog_line pl2\n";
    out += "  stmt s1\n  stmt s2\n  constant c1\n  constant c2\n";
    out += "  procedure proc1\n  procedure proc2\n  variable var1\n";
    out += "  variable var2\n  assign a1\n  assign a2\n  if if1\n";
    out += "  if if2\nSELECT TUPLE\n  prog_line pl1\n  if if1 stmt#\n";
    out += "  variable var2 varName\n  constant c1 value\n";
    out += "  procedure proc1 procName\nModifies(if2,var2)\n";
    out += "Calls(proc2,\"game\")\nAffects*(a2,a1)\nParent*(if1,pl2)\n";
    out += "Follows*(pl2,a2)\nNext(s1,pl1)\nParent(s2,pl1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::
test_err_parse_withclause_ref_synonym_not_progline()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    // LHS of 1st WithClause has missing attr
    queryStr = " assign a; stmt s; Select a with a = s.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR,
            "a", entity_type_to_string(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // Above Corrected
    queryStr = "assign a; stmt s; Select a with a.stmt# = s.stmt#";
    parser.parse(queryStr);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a\n  stmt s\nSELECT TUPLE\n";
    out += "  assign a\na.stmt# = s.stmt#\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // LHS of 3rd with clause missing attr
    queryStr = "while w; if if1; variable v1, v2; assign a1, a2; ";
    queryStr += " Select <w,if1, a1.stmt#> such that Parent(w,if1) and ";
    queryStr += " Parent(w,a1) with a1.stmt# = 15 and ";
    queryStr += " a1.stmt# = a2.stmt# such that Modifies(a2,v2) and ";
    queryStr += " Affects(a2,a1) with w = 23";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR,
            "w", entity_type_to_string(ENT_WHILE));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // Above corrected
    queryStr = "while w; if if1; variable v1, v2; assign a1, a2; ";
    queryStr += " Select <w,if1, a1.stmt#> such that Parent(w,if1) and ";
    queryStr += " Parent(w,a1) with a1.stmt# = 15 and ";
    queryStr += " a1.stmt# = a2.stmt# such that Modifies(a2,v2) and ";
    queryStr += " Affects(a2,a1) with w.stmt# = 23";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while w\n  if if1\n  variable v1\n";
    out += "  variable v2\n  assign a1\n  assign a2\nSELECT TUPLE\n";
    out += "  while w\n  if if1\n  assign a1 stmt#\n";
    out += "Parent(w,if1)\nParent(w,a1)\na1.stmt# = 15\n";
    out += "a1.stmt# = a2.stmt#\nModifies(a2,v2)\nAffects(a2,a1)\n";
    out += "w.stmt# = 23\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // RHS of 1st with clause missing attr
    queryStr = " procedure someP; variable ynna; ";
    queryStr += " Select ynna with someP.procName = ynna";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR,
            "ynna", entity_type_to_string(ENT_VAR));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // Above corrected
    queryStr = " procedure someP; variable ynna; ";
    queryStr += " Select ynna with someP.procName = ynna.varName ";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  procedure someP\n  variable ynna\n";
    out += "SELECT TUPLE\n  variable ynna\nsomeP.procName = ynna.varName\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // RHS of 4th with clause missing attr
    queryStr = "procedure p1, p2; assign a1, a2; while w1, w2; ";
    queryStr += " call c1, c2; constant const1, const2; variable v1, v2; ";
    queryStr += " Select <c1.procName, const1.value, w1, a2, ";
    queryStr += " p2.procName> with p1.procName = v1.varName such that ";
    queryStr += " Modifies(p1, v1) and Uses(w1, v1) with ";
    queryStr += " const1.value = w1.stmt# such that Affects(a1,a2) and ";
    queryStr += " Parent(w1,a2) with a2.stmt# = const2.value and ";
    queryStr += " c1 = v2.varName such that Modifies(c1,v1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR,
            "c1", entity_type_to_string(ENT_CALL));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // Above corrected
    queryStr = "procedure p1, p2; assign a1, a2; while w1, w2; ";
    queryStr += " call c1, c2; constant const1, const2; variable v1, v2; ";
    queryStr += " Select <c1.procName, const1.value, w1, a2, ";
    queryStr += " p2.procName> with p1.procName = v1.varName such that ";
    queryStr += " Modifies(p1, v1) and Uses(w1, v1) with ";
    queryStr += " const1.value = w1.stmt# such that Affects(a1,a2) and ";
    queryStr += " Parent(w1,a2) with a2.stmt# = const2.value and ";
    queryStr += " c1.procName = v2.varName such that Modifies(c1,v1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  procedure p1\n  procedure p2\n";
    out += "  assign a1\n  assign a2\n  while w1\n  while w2\n  call c1\n";
    out += "  call c2\n  constant const1\n  constant const2\n";
    out += "  variable v1\n  variable v2\nSELECT TUPLE\n";
    out += "  call c1 procName\n  constant const1 value\n  while w1\n";
    out += "  assign a2\n  procedure p2 procName\n";
    out += "p1.procName = v1.varName\nModifies(p1,v1)\nUses(w1,v1)\n";
    out += "const1.value = w1.stmt#\nAffects(a1,a2)\nParent(w1,a2)\n";
    out += "a2.stmt# = const2.value\nc1.procName = v2.varName\n";
    out += "Modifies(c1,v1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser_With::test_err_parse_withclause_type_mismatch()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    WithClause withCl;

    // 1st with clause, int vs. string
    queryStr = "Select BOOLEAN with 3 = \"string\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_INT;
    withCl.leftRef.refIntVal = 3;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "string";
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above but for 3rd With Clause
    queryStr = "assign a1, a2; variable v1, v2; procedure p1, p2; ";
    queryStr += " while w1, w2; ";
    queryStr += " Select <a1, v1, p2.procName, w2> such that ";
    queryStr += " Modifies(a1,v2) and Parent*(w2,a1) with ";
    queryStr += " a1.stmt# = 57 and v2.varName = p2.procName such that ";
    queryStr += " Affects(a2, a1) and Uses(a2,v2) with 661 = \"bbah\" ";
    queryStr += " and 677 = 677 ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_INT;
    withCl.leftRef.refIntVal = 661;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "bbah";
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st with clause, string vs. int
    queryStr = " assign a; Select a with \"top\" = -875";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_STRING;
    withCl.leftRef.refStringVal = "top";
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = -875;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above but for 4th with clause
    queryStr = " call call1, call2; procedure proc1, proc2; ";
    queryStr += " assign as1, as2; if if1, if2; variable var1, var2; ";
    queryStr += " constant const1, const2; ";
    queryStr += " Select <call1, proc2, as1.stmt#, const2.value>  ";
    queryStr += " such that Parent(if1, as2) and ";
    queryStr += " Modifies(as2, var2) with call2.procName = \"abcd\" ";
    queryStr += " and const1.value = 57 such that Calls(proc1,proc2) ";
    queryStr += " and Uses(call1, var2) with call2.stmt# = const1.value ";
    queryStr += " and \"sheep\" = 86992 such that Next(call2, call1) ";
    queryStr += " and Uses(call2, var1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_STRING;
    withCl.leftRef.refStringVal = "sheep";
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 86992;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st with clause, int syn vs. string
    queryStr = "assign a; Select a with a.stmt# = \"faker\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "a";
    withCl.leftRef.refSynType = REFSYN_ASSIGN;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "faker";
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but for 4th with clause
    queryStr = " prog_line pl1, pl2; assign a1, a2; variable v1, v2;";
    queryStr += " procedure proc1, proc2; while w1, w2; ";
    queryStr += " constant c1, c2; ";
    queryStr += " Select <pl1, a2.stmt#, v2, pl2.prog_line#> such that ";
    queryStr += " Modifies(pl1, v2) and Parent(56, a1) with ";
    queryStr += " pl1 = 577 and a1.stmt# = c1.value such that ";
    queryStr += " Affects(a1,a2) and Modifies(a2, \"someVar\") with ";
    queryStr += " \"al1\" = v2.varName and c1.value = \"ikk\" ";
    queryStr += " such that  Parent*(w1, pl1) and Next(w1, 896)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "c1";
    withCl.leftRef.refSynType = REFSYN_CONST;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "ikk";
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st with clause, string syn. vs. int
    queryStr = " call ca1; Select ca1 with ca1.procName = 7";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "ca1";
    withCl.leftRef.refSynType = REFSYN_CALL_PROCNAME;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 7;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but at 3rd with clause
    queryStr = " procedure p1, p2; while w1, w2; assign a1, a2; ";
    queryStr += " call call1, call2; variable v1, v2; ";
    queryStr += " Select <call1, v1.varName, w1, a1.stmt#> with ";
    queryStr += " a1.stmt# = 57 and \"abcd\" = v1.varName such that ";
    queryStr += " Modifies(a1, v1) and Uses(call1, v1) and ";
    queryStr += " Modifies(p1,v1) with p1.procName = 36787";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "p1";
    withCl.leftRef.refSynType = REFSYN_PROC;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 36787;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st with clause, int syn vs. string syn
    queryStr = " variable v1; assign a; ";
    queryStr += " Select <a,v1> with a.stmt# = v1.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "a";
    withCl.leftRef.refSynType = REFSYN_ASSIGN;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "v1";
    withCl.rightRef.refSynType = REFSYN_VAR;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but for 4th with clause
    queryStr = " if if1, if2; variable v1, v2; prog_line pl1, pl2; ";
    queryStr += " call c1, c2; ";
    queryStr += " Select <c1, v2.varName, if1.stmt#, pl1> with ";
    queryStr += " v1.varName = \"someVar\" such that ";
    queryStr += " Parent(if1, c1) and Modifies(c1, v1) and ";
    queryStr += " Next(c1, pl1) with pl1.prog_line# = 421 such that ";
    queryStr += " Uses(c1, v2) with if1.stmt# = c1.stmt# and ";
    queryStr += " if1.stmt# = c1.procName and ";
    queryStr += " c1.procName = \"someProc\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "if1";
    withCl.leftRef.refSynType = REFSYN_IF;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "c1";
    withCl.rightRef.refSynType = REFSYN_CALL_PROCNAME;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_INT_STR,
            BASETYPE_STRING_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st with clause, string syn vs. int syn
    queryStr = " prog_line pl1; call c1; ";
    queryStr += " Select <c1,pl1> with c1.procName = pl1";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "c1";
    withCl.leftRef.refSynType = REFSYN_CALL_PROCNAME;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "pl1";
    withCl.rightRef.refSynType = REFSYN_PROGLINE;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but in 5th with clause
    queryStr = "assign a1, a2; prog_line pl1, pl2; variable v1, v2; ";
    queryStr += " Select BOOLEAN with pl1 = 588 such that Uses(a1,v1) ";
    queryStr += " and Modifies(a1,\"v\") with \"uis\" = v1.varName and ";
    queryStr += " 125 = pl2.prog_line# such that Next(a1,pl2) and ";
    queryStr += " Parent(pl1, a1) with a1.stmt# = 336 and ";
    queryStr += " v1.varName = pl2.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_TYPE_MISMATCH,
            parser.get_parse_result());
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "v1";
    withCl.leftRef.refSynType = REFSYN_VAR;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "pl2";
    withCl.rightRef.refSynType = REFSYN_PROGLINE_PROGLINE_NO;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_TYPE_MISMATCH_STR,
            withCl.toString().c_str(), BASETYPE_STRING_STR,
            BASETYPE_INT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser_With::test_err_parse_withclause_and_nosep()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    WithClause withCl;

    queryStr = " assign a; prog_line pl; variable v; ";
    queryStr += " Select <a,pl.prog_line#, v> such that Uses(a,v) ";
    queryStr += " with a.stmt# = 13  and##% v.varName = \"bbb\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_AND_NOSEP,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_AND_NOSEP_STR,
            "##%");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser_With::test_err_parse_withclause_expect_ref_on_rhs()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    Ref leftRef;

    queryStr = "assign a; Select a with a.stmt# = ^&523";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS,
            parser.get_parse_result());
    leftRef.refType = REF_ATTRREF;
    leftRef.refStringVal = "a";
    leftRef.refSynType = REFSYN_ASSIGN;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS_STR,
            leftRef.toString().c_str(), "^&523");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but in 4th with clause
    queryStr = "assign a; prog_line pl; variable v; call c; ";
    queryStr += " Select <a.stmt#, pl, c.procName, v> such that ";
    queryStr += " Modifies(a,\"var1\") and Uses(a,v) with a.stmt# = 57 ";
    queryStr += " and v.varName = \"var2\" such that Next*(a,pl) ";
    queryStr += " with 52 = pl.prog_line# and c.procName = !^7347 and ";
    queryStr += " c.stmt# = 788 such that Modifies(c,v)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS,
            parser.get_parse_result());
    leftRef.refType = REF_ATTRREF;
    leftRef.refStringVal = "c";
    leftRef.refSynType = REFSYN_CALL_PROCNAME;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS_STR,
            leftRef.toString().c_str(), "!^7347");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser_With::test_err_parse_withclause_expect_with()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;
    QueryInfo *qinfo;
    WithClause prevWithCl;

    queryStr = "assign a; stmt s; Select a with a.stmt# = 123 and ";
    queryStr += " !@#$6 fhh";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_WITH,
            parser.get_parse_result());
    prevWithCl.leftRef.refType = REF_ATTRREF;
    prevWithCl.leftRef.refStringVal = "a";
    prevWithCl.leftRef.refSynType = REFSYN_ASSIGN;
    prevWithCl.rightRef.refType = REF_INT;
    prevWithCl.rightRef.refIntVal = 123;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_WITH_STR,
            "!@#$6 fhh", prevWithCl.toString().c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but for 4th with clause
    queryStr = "assign a; if if1; prog_line pl; variable v; ";
    queryStr += " Select <a,pl,v.varName> such that Uses(a,\"someV\") ";
    queryStr += " and Parent*(if1,a) with 67 = a.stmt# and ";
    queryStr += " \"a\" = v.varName such that Next*(a,pl) and ";
    queryStr += " Modifies(a,v) with 777 = pl and $Q#$#@4 = 68789 ";
    queryStr += " such that Affects(a,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_WITH,
            parser.get_parse_result());
    prevWithCl.leftRef.refType = REF_INT;
    prevWithCl.leftRef.refIntVal = 777;
    prevWithCl.rightRef.refType = REF_ATTRREF;
    prevWithCl.rightRef.refStringVal = "pl";
    prevWithCl.rightRef.refSynType = REFSYN_PROGLINE;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_WITH_STR,
            "$Q#$#@4 = 68789  such that Affects(a,_)",
            prevWithCl.toString().c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // failed to parse '='
    queryStr = " assign a; prog_line pl; variable v; ";
    queryStr += " Select <a,v.varName> with a.stmt# = pl and ";
    queryStr += " v.varName sdf";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_WITH,
            parser.get_parse_result());
    prevWithCl.leftRef.refType = REF_ATTRREF;
    prevWithCl.leftRef.refStringVal = "a";
    prevWithCl.leftRef.refSynType = REFSYN_ASSIGN;
    prevWithCl.rightRef.refType = REF_ATTRREF;
    prevWithCl.rightRef.refStringVal = "pl";
    prevWithCl.rightRef.refSynType = REFSYN_PROGLINE;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_WITH_STR,
            "v.varName sdf", prevWithCl.toString().c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // same as above, but in 5th with clause
    queryStr = " call c; procedure proc; variable v; assign a; if if1;";
    queryStr += " Select <c.procName, v, a.stmt#, if1> such that ";
    queryStr += " Modifies(if1,v) with v.varName = \"bn\" such that ";
    queryStr += " Uses(c,v) and Parent(if1,c) with 125 = c.stmt# ";
    queryStr += " such that Modifies(proc,\"avar\") with ";
    queryStr += " \"pOne\" = proc.procName and 66 = if1.stmt# and ";
    queryStr += " c.stmt# 78 ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_WITHCLAUSE_EXPECT_WITH,
            parser.get_parse_result());
    prevWithCl.leftRef.refType = REF_INT;
    prevWithCl.leftRef.refIntVal = 66;
    prevWithCl.rightRef.refType = REF_ATTRREF;
    prevWithCl.rightRef.refStringVal = "if1";
    prevWithCl.rightRef.refSynType = REFSYN_IF;
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_WITHCLAUSE_EXPECT_WITH_STR,
            "c.stmt# 78 ", prevWithCl.toString().c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}