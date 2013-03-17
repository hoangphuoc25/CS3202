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
}

void Test_20_PQLParser_With::test_err_parse_dquoted_ident_invalid()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // 1st argument not valid identifier
    queryStr = "assign a; Select a with \"1ab\" = \"c\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "1ab");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 2nd argument not valid identifier
    queryStr = "assign a; Select a with \"pkb\"  = \"#tyh\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "#tyh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 1st argument of 3rd with clause is an invalid identifier
    queryStr = "while w; procedure p;";
    queryStr += " Select <w,p> with \"a\" = \"a\" and \t \n ";
    queryStr += " w.stmt# \n\t = \t\t13 and \"#gff\" = \"bcd\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, "#gff");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // 2nd argument of 4th with clause is an invalid identifier
    queryStr = "procedure p; assign a1, a2; variable v; ";
    queryStr += " Select <a1,v,p> such that Modifies(p,v) and ";
    queryStr += " Uses(a1, v) with \"alpha\" = \"alpha\" and ";
    queryStr += " 2 = 2 and a1.stmt# = a2.stmt# and \"brave\" = \",s1\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_INVALID_STR, ",s1");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser_With::
             test_err_parse_dquoted_ident_missing_close_quote()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // LHS of 1st with clause missing close quote
    queryStr = " call c; Select c with \"ableh = \"b\"";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "ableh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // RHS of 2nd with clause missing close quote
    queryStr = " assign aS1; variable VaR; while w1; ";
    queryStr += " Select <aS1, VaR, w1> with 1 = 1 and ";
    queryStr += " \"bomb\" = \"tim and 35 = 35";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "tim");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

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
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR,
            "haha");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
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
    // string is too long for RHS of 3rd WithClause
    queryStr = "assign a; procedure procN; Select <procN, a> with ";
    queryStr += " 65 = 65 and 1=1 and 99=75562484845445";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
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

    // overflow by 1
    queryStr = " assign a; Select a with 15636 = 2147483648";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
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
    // overflow by 1 in 4th WithClause
    queryStr = "Select BOOLEAN with 17=17 and 236=236 and ";
    queryStr += " 775 = 2147483648";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
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

    // overflow by a lot
    queryStr = "Select BOOLEAN with 33 = 3234567890";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
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
    // overflow by a lot in 4th WithClause
    queryStr = " while whg; procedure Bsd; Select <whg, Bsd> with ";
    queryStr += " 1245 = 1245 and 77 = 77 and 7457 = 7457 and ";
    queryStr += " 27568 = 5634567890";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
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
}