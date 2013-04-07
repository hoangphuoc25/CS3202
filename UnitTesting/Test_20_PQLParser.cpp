// disable warnings about using _snprintf
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include "Test_20_PQLParser.h"
#include "../SPA/PQLParser.h"

using std::string;
using std::map;
using std::ostringstream;
using std::set;
using std::pair;

void Test_20_PQLParser::setUp()
{
    this->buf = new char[Test_20_PQLParser::BUFLEN+5];
}

void Test_20_PQLParser::tearDown()
{
    delete[] this->buf;
}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_PQLParser);

void Test_20_PQLParser::test_one_decl_one()
{
    PQLParser parser;
    QueryInfo *qinfo;
    map<string, DesignEnt> entTable;
    map<string, DesignEnt>::iterator it;
    string queryStr = "assign al3t; Select al3t";
    string s;
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("al3t");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "ALIVE\nDECLARATIONS\n  assign al3t\nSELECT TUPLE\n  assign al3t\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "procedure bnvb#; Select bnvb#";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("bnvb#");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "ALIVE\nDECLARATIONS\n  procedure bnvb#\n";
    s += "SELECT TUPLE\n  procedure bnvb#\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "stmtLst H1bvg; Select H1bvg";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("H1bvg");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "ALIVE\nDECLARATIONS\n  stmtLst H1bvg\n";
    s += "SELECT TUPLE\n  stmtLst H1bvg\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "stmt s7772a;   \n Select s7772a  ";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("s7772a");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "ALIVE\nDECLARATIONS\n  stmt s7772a\n";
    s += "SELECT TUPLE\n  stmt s7772a\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "call Gbcv1;   \t\n  \t Select  \n \t Gbcv1  \t";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("Gbcv1");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "ALIVE\nDECLARATIONS\n  call Gbcv1\n";
    s += "SELECT TUPLE\n  call Gbcv1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "while KMB2vx;Select KMB2vx";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("KMB2vx");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "ALIVE\nDECLARATIONS\n  while KMB2vx\n";
    s += "SELECT TUPLE\n  while KMB2vx\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "if u; Select u";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("u");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "ALIVE\nDECLARATIONS\n  if u\nSELECT TUPLE\n  if u\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "variable x; Select x";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("x");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "ALIVE\nDECLARATIONS\n  variable x\n";
    s += "SELECT TUPLE\n  variable x\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "constant c2; \n Select \n\n c2\n \t";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("c2");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "ALIVE\nDECLARATIONS\n  constant c2\n";
    s += "SELECT TUPLE\n  constant c2\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
       
    queryStr = "prog_line plbc;  Select plbc ";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("plbc");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "ALIVE\nDECLARATIONS\n  prog_line plbc\n";
    s += "SELECT TUPLE\n  prog_line plbc\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    // whitespace test
    queryStr = "\t  assign  \t \n nbnesdf1#bvsAA   \n;";
    queryStr += "   \n Select nbnesdf1#bvsAA ";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(1, (int)entTable.size());
    s = string("nbnesdf1#bvsAA");
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "ALIVE\nDECLARATIONS\n  assign nbnesdf1#bvsAA\nSELECT TUPLE\n";
    s += "  assign nbnesdf1#bvsAA\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_one_decl()
{
    PQLParser parser;
    string queryStr = "assign afC,bca,ncvb1;  Select  ncvb1";
    string s;
    map<string, DesignEnt> entTable;
    QueryInfo *qinfo;
    map<string, DesignEnt>::iterator it, endIt;
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(3, (int)entTable.size());
    endIt = entTable.end();
    s = "afC";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "bca";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "bca";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "ALIVE\nDECLARATIONS\n  assign afC\n  assign bca\n";
    s += "  assign ncvb1\n";
    s += "SELECT TUPLE\n  assign ncvb1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "  procedure  pl123,\nABsx1,\tgawdvbS1\n\t,  xujrE1;";
    queryStr += "Select ABsx1";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(4, (int)entTable.size());
    endIt = entTable.end();
    s = "pl123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "ABsx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "gawdvbS1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "xujrE1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "ALIVE\nDECLARATIONS\n  procedure pl123\n  procedure ABsx1\n";
    s += "  procedure gawdvbS1\n  procedure xujrE1\n";
    s += "SELECT TUPLE\n  procedure ABsx1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "stmtLst   bhvx1, CVS1\n\n\t, MBMcb1,\nHH123,YFS1cvx; \n";
    queryStr += "  Select MBMcb1";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(5, (int)entTable.size());
    endIt = entTable.end();
    s = "bhvx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "CVS1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "MBMcb1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "HH123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "YFS1cvx";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "ALIVE\nDECLARATIONS\n  stmtLst bhvx1\n  stmtLst CVS1\n";
    s += "  stmtLst MBMcb1\n  stmtLst HH123\n  stmtLst YFS1cvx\n";
    s += "SELECT TUPLE\n  stmtLst MBMcb1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "stmt a,b, f#1sdc;  Select b";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(3, (int)entTable.size());
    endIt = entTable.end();
    s = "a";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "b";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "f#1sdc";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "ALIVE\nDECLARATIONS\n  stmt a\n  stmt b\n  stmt f#1sdc\n";
    s += "SELECT TUPLE\n  stmt b\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "\t\n\t \tcall gbd1  , ccAS123\n  \t;\tSelect gbd1";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(2, (int)entTable.size());
    endIt = entTable.end();
    s = "gbd1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "ccAS123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "ALIVE\nDECLARATIONS\n  call gbd1\n  call ccAS123\n";
    s += "SELECT TUPLE\n  call gbd1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "while W123v, qfdf1t5,\t\n bv11bv\t\n,x\n\t,nbnx1;";
    queryStr += "\n  Select bv11bv\n";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(5, (int)entTable.size());
    endIt = entTable.end();
    s = "W123v";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "qfdf1t5";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "bv11bv";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "x";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "nbnx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "ALIVE\nDECLARATIONS\n  while W123v\n  while qfdf1t5\n";
    s += "  while bv11bv\n  while x\n  while nbnx1\n";
    s += "SELECT TUPLE\n  while bv11bv\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "\n\n\n\tif nmb1, \n  xgcx1;  Select xgcx1";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(2, (int)entTable.size());
    endIt = entTable.end();
    s = "nmb1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "xgcx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "ALIVE\nDECLARATIONS\n  if nmb1\n  if xgcx1\n";
    s += "SELECT TUPLE\n  if xgcx1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = " variable   Bb1, cvx1, \n v1sbaA12# ;  Select Bb1";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(3, (int)entTable.size());
    endIt = entTable.end();
    s = "Bb1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "cvx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "v1sbaA12#";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "ALIVE\nDECLARATIONS\n  variable Bb1\n  variable cvx1\n";
    s += "  variable v1sbaA12#\nSELECT TUPLE\n  variable Bb1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    queryStr = "constant  Cb#zsd1, Jvd11a, \n\t   y1123h,  kkj1#n;";
    queryStr += "Select kkj1#n";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(4, (int)entTable.size());
    endIt = entTable.end();
    s = "Cb#zsd1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "Jvd11a";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "y1123h";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "kkj1#n";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "ALIVE\nDECLARATIONS\n  constant Cb#zsd1\n  constant Jvd11a\n";
    s += "  constant y1123h\n  constant kkj1#n\n";
    s += "SELECT TUPLE\n  constant kkj1#n\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());

    // lowercase and uppercase x are different
    queryStr = "prog_line   a01tT1z, bcv1, x, B\n, cx1, X, \t z; Select B";
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT_EQUAL(7, (int)entTable.size());
    endIt = entTable.end();
    s = "a01tT1z";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "bcv1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "x";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "B";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "cx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "X";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "z";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != endIt);
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "ALIVE\nDECLARATIONS\n  prog_line a01tT1z\n";
    s += "  prog_line bcv1\n  prog_line x\n";
    s += "  prog_line B\n  prog_line cx1\n  prog_line X\n  prog_line z\n";
    s += "SELECT TUPLE\n  prog_line B\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_mult_decl()
{
    string queryStr = "\n\nassign Ccxx1, bd1; \n";
    queryStr += "procedure pl123, \n\nxvcxv1, ggs1g;";
    queryStr += "call call123, x, nbc;\n\t\n";
    queryStr += "stmtLst ssbdv1, g2cx1#, X, mmmio;";
    queryStr += "\t\n  variable   \n\t vvvv1, nbv1; ";
    queryStr += "stmt Ty123; assign x56v231,\t\nUU12;";
    queryStr += "while www123, \n\t  HJ13s, rr75#1g;";
    queryStr += "constant hbdg1, FFA72h, bcsdf1hf1;";
    queryStr += "if\n\tiii,\tpc21sa1,\nnotPassword;";
    queryStr += "\t\tprog_line Plvx1, bbnb1g#g;";
    queryStr += "stmt a,b\n;  Select nbv1";
    PQLParser parser;
    string s;
    map<string, DesignEnt> entTable;
    QueryInfo *qinfo;
    map<string, DesignEnt>::iterator it, endIt;
    parser.parse(queryStr);
    entTable = parser.get_ent_table();
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    CPPUNIT_ASSERT(30 == (int)entTable.size());
    s = "Ccxx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "bd1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "pl123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "xvcxv1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "ggs1g";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROC);
    s = "call123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "x";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "nbc";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CALL);
    s = "ssbdv1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "g2cx1#";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "X";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "mmmio";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMTLST);
    s = "vvvv1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "nbv1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_VAR);
    s = "Ty123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "x56v231";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "UU12";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_ASSIGN);
    s = "www123";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "HJ13s";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "rr75#1g";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_WHILE);
    s = "hbdg1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "FFA72h";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "bcsdf1hf1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_CONST);
    s = "iii";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "pc21sa1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "notPassword";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_IF);
    s = "Plvx1";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "bbnb1g#g";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_PROGLINE);
    s = "a";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);
    s = "b";
    it = entTable.find(s);
    CPPUNIT_ASSERT(it != entTable.end());
    CPPUNIT_ASSERT_EQUAL(it->first, s);
    CPPUNIT_ASSERT_EQUAL(it->second, ENT_STMT);

    s = "ALIVE\nDECLARATIONS\n  assign Ccxx1\n  assign bd1\n";
    s += "  procedure pl123\n";
    s += "  procedure xvcxv1\n  procedure ggs1g\n  call call123\n  call x\n";
    s += "  call nbc\n  stmtLst ssbdv1\n  stmtLst g2cx1#\n  stmtLst X\n";
    s += "  stmtLst mmmio\n  variable vvvv1\n  variable nbv1\n  stmt Ty123\n";
    s += "  assign x56v231\n  assign UU12\n  while www123\n  while HJ13s\n";
    s += "  while rr75#1g\n  constant hbdg1\n  constant FFA72h\n";
    s += "  constant bcsdf1hf1\n  if iii\n  if pc21sa1\n  if notPassword\n";
    s += "  prog_line Plvx1\n  prog_line bbnb1g#g\n  stmt a\n  stmt b\n";
    s += "SELECT TUPLE\n  variable nbv1\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_select_bool()
{
    string queryStr = "assign bb1; prog_line X1g; Select BOOLEAN";
    PQLParser parser;
    string s;
    QueryInfo *qinfo;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    s = "ALIVE\nDECLARATIONS\n  assign bb1\n  prog_line X1g\n";
    s += "SELECT BOOLEAN\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_select_tuple()
{
    string queryStr = "assign bcv1; prog_line bvcb1, GS1; ";
    queryStr += "stmt SS123;  Select <bcv1, GS1>";
    PQLParser parser;
    QueryInfo *qinfo;
    string output;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  assign bcv1\n  prog_line bvcb1\n";
    output += "  prog_line GS1\n  stmt SS123\nSELECT TUPLE\n  assign bcv1\n";
    output += "  prog_line GS1\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "stmtLst   QQwe1, hg1; prog_line x, bv13hs#1; ";
    queryStr += "call vvbx1; while X; variable VBCV1, KJj12; constant bnbn;";
    queryStr += "  assign BBVB123jh;  variable thd15;";
    queryStr += "Select\n\t<\n\n VBCV1  \n\t\t  , x  \n\t, \n\t bnbn , \n ";
    queryStr += "   \t  X \n\t ,   QQwe1  \n\t>";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  stmtLst QQwe1\n  stmtLst hg1\n";
    output += "  prog_line x\n";
    output += "  prog_line bv13hs#1\n  call vvbx1\n  while X\n";
    output += "  variable VBCV1\n  variable KJj12\n  constant bnbn\n";
    output += "  assign BBVB123jh\n  variable thd15\n";
    output += "SELECT TUPLE\n  variable VBCV1\n  prog_line x\n";
    output += "  constant bnbn\n  while X\n  stmtLst QQwe1\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_select_attrRef()
{
    string queryStr = "procedure p1; Select p1.procName";
    PQLParser parser;
    QueryInfo *qinfo;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    string output;
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  procedure p1\nSELECT TUPLE\n";
    output += "  procedure p1 procName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "assign a12; Select a12.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  assign a12\n";
    output += "SELECT TUPLE\n  assign a12 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "stmtLst sl43#; Select sl43#.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  stmtLst sl43#\n";
    output += "SELECT TUPLE\n  stmtLst sl43# stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "stmt gbv#c; Select gbv#c.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  stmt gbv#c\n";
    output += "SELECT TUPLE\n  stmt gbv#c stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "call nba1; Select nba1.procName";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  call nba1\n";
    output += "SELECT TUPLE\n  call nba1 procName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "call Tnbvc1; Select Tnbvc1.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  call Tnbvc1\n";
    output += "SELECT TUPLE\n  call Tnbvc1 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "while pklf9; Select pklf9.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  while pklf9\n";
    output += "SELECT TUPLE\n  while pklf9 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "if HHbvc1; Select HHbvc1.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  if HHbvc1\n";
    output += "SELECT TUPLE\n  if HHbvc1 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "variable uvdg#; Select uvdg#.varName";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  variable uvdg#\n";
    output += "SELECT TUPLE\n  variable uvdg# varName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "constant dfb1; Select dfb1.value";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  constant dfb1\n";
    output += "SELECT TUPLE\n  constant dfb1 value\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "prog_line pofd1; Select pofd1.prog_line#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  prog_line pofd1\n";
    output += "SELECT TUPLE\n  prog_line pofd1 prog_line#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "procedure proc1, proc2; stmtLst ST1, ST2;";
    queryStr += " stmt s1, s2, s3; ";
    queryStr += "assign a1, a2, a3; call c1, c2, c3; while w1, w2, w3; ";
    queryStr += "if i1, i2, i3; variable v1, v2, v3;";
    queryStr += "constant const1, const2, const3; prog_line pl1, pl2, pl3;";
    queryStr += " Select <ST1, ST2.stmt#, s1.stmt#, s1, ST2, a1.stmt#, c2, ";
    queryStr += " c3.procName, w1.stmt#, w1, w3, i1, i3.stmt#, v1, ";
    queryStr += " v1.varName, const1, const1.value, pl2.prog_line#, ";
    queryStr += " pl2, pl3 >";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "ALIVE\nDECLARATIONS\n  procedure proc1\n";
    output += "  procedure proc2\n";
    output += "  stmtLst ST1\n  stmtLst ST2\n  stmt s1\n  stmt s2\n  stmt s3\n";
    output += "  assign a1\n  assign a2\n  assign a3\n  call c1\n  call c2\n";
    output += "  call c3\n  while w1\n  while w2\n  while w3\n  if i1\n";
    output += "  if i2\n  if i3\n  variable v1\n  variable v2\n";
    output += "  variable v3\n  constant const1\n  constant const2\n";
    output += "  constant const3\n  prog_line pl1\n  prog_line pl2\n";
    output += "  prog_line pl3\n";
    output += "SELECT TUPLE\n  stmtLst ST1\n  stmtLst ST2 stmt#\n";
    output += "  stmt s1 stmt#\n  stmt s1\n  stmtLst ST2\n  assign a1 stmt#\n";
    output += "  call c2\n  call c3 procName\n  while w1 stmt#\n  while w1\n";
    output += "  while w3\n  if i1\n  if i3 stmt#\n  variable v1\n";
    output += "  variable v1 varName\n  constant const1\n";
    output += "  constant const1 value\n  prog_line pl2 prog_line#\n";
    output += "  prog_line pl2\n  prog_line pl3\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_modifies()
{
    // Modifies(assign,var)
    string queryStr = "assign ad; variable vhd; ";
    queryStr += "Select ad such that Modifies(ad,vhd)";
    string out;
    PQLParser parser;
    QueryInfo *qinfo;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign ad\n  variable vhd\n";
    out += "SELECT TUPLE\n";
    out += "  assign ad\nModifies(ad,vhd)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces
    queryStr = "assign fh1; variable gdfg1, hgf1udA; ";
    queryStr += " Select hgf1udA such that ";
    queryStr += "  \n Modifies (\t\n  fh1  , \t gdfg1 \t)  ";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign fh1\n  variable gdfg1\n";
    out += "  variable hgf1udA\n";
    out += "SELECT TUPLE\n  variable hgf1udA\nModifies(fh1,gdfg1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(proc,var)
    queryStr = "procedure plf1; variable gbdg1; ";
    queryStr += "Select plf1 such that Modifies(plf1, gbdg1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  procedure plf1\n  variable gbdg1\n";
    out += "SELECT TUPLE\n  procedure plf1\nModifies(plf1,gbdg1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(if,var)
    queryStr = "variable mmvd1; if nfI1g; Select nfI1g such that ";
    queryStr += "Modifies(nfI1g, mmvd1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable mmvd1\n  if nfI1g\n";
    out += "SELECT TUPLE\n";
    out += "  if nfI1g\nModifies(nfI1g,mmvd1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(while,var)
    queryStr = " while bcv1; variable TQWEx1; Select TQWEx1 such that ";
    queryStr += "Modifies(bcv1, TQWEx1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while bcv1\n  variable TQWEx1\n";
    out += "SELECT TUPLE\n";
    out += "  variable TQWEx1\nModifies(bcv1,TQWEx1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(call,var)
    queryStr = "  variable qecxv1#; call Kmmbc1; Select Kmmbc1 such that ";
    queryStr += "Modifies(Kmmbc1, qecxv1#)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable qecxv1#\n  call Kmmbc1\n";
    out += "SELECT TUPLE\n";
    out += "  call Kmmbc1\nModifies(Kmmbc1,qecxv1#)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(stmt,var)
    queryStr = "  stmt Iuvc1; variable lljgbf1; Select Iuvc1 such that ";
    queryStr += "Modifies(Iuvc1, lljgbf1)\n";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  stmt Iuvc1\n  variable lljgbf1\n";
    out += "SELECT TUPLE\n";
    out += "  stmt Iuvc1\nModifies(Iuvc1,lljgbf1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(prog_line,var)
    queryStr = " variable hjf1#xa; prog_line poiote; Select poiote ";
    queryStr += "such that Modifies(poiote, hjf1#xa )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable hjf1#xa\n";
    out += "  prog_line poiote\n";
    out += "SELECT TUPLE\n  prog_line poiote\nModifies(poiote,hjf1#xa)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(synonym,string)
    queryStr = "  stmt fvb1; Select fvb1 such that  ";
    queryStr += " Modifies  (  \t fvb1,  \"abvxc\"  \n \t)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  stmt fvb1\nSELECT TUPLE\n";
    out += "  stmt fvb1\n";
    out += "Modifies(fvb1,\"abvxc\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(synonym,_)
    queryStr = "  while df1; stmt BBx1;  Select <df1,BBx1> ";
    queryStr += " such that Modifies(df1,   \t  _  \t ) \n";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while df1\n  stmt BBx1\n";
    out += "SELECT TUPLE\n  while df1\n  stmt BBx1\nModifies(df1,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,var)
    queryStr = " variable hcb, m2df1; Select m2df1 such that  ";
    queryStr += "Modifies(5, m2df1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable hcb\n  variable m2df1\n";
    out += "SELECT TUPLE\n";
    out += "  variable m2df1\nModifies(5,m2df1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,string)
    queryStr = "  variable BLEh; Select BLEh such that Modifies(13,  \"Ex1\")";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable BLEh\n";
    out += "SELECT TUPLE\n  variable BLEh\n";
    out += "Modifies(13,\"Ex1\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,_)
    queryStr = " Select BOOLEAN such that Modifies(235, _)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\nModifies(235,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,_), int is negative
    queryStr = " Select BOOLEAN such that Modifies(-23615, _)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\nModifies(-23615,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,var)
    queryStr = " variable utq; Select utq such that ";
    queryStr += "   Modifies  \t (  \t \"proc1\"  \t ,utq)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable utq\nSELECT TUPLE\n";
    out += "  variable utq\n";
    out += "Modifies(\"proc1\",utq)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,string)
    queryStr = " while xfgvb1; Select xfgvb1 such that ";
    queryStr += "Modifies  (  \"fvProc\" \t , \t \n \"bcb14\"  \t \n)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while xfgvb1\nSELECT TUPLE\n";
    out += "  while xfgvb1\n";
    out += "Modifies(\"fvProc\",\"bcb14\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,_)
    queryStr = " stmtLst sf; Select sf such that Modifies(\"qbcvb1\",_)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  stmtLst sf\nSELECT TUPLE\n";
    out += "  stmtLst sf\n";
    out += "Modifies(\"qbcvb1\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,var)
    queryStr = "  variable gvbcvb; Select gvbcvb such that  ";
    queryStr += "Modifies(_,gvbcvb)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable gvbcvb\nSELECT TUPLE\n";
    out += "  variable gvbcvb\n";
    out += "Modifies(_,gvbcvb)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,string)
    queryStr = " assign a; Select a such that Modifies(_,  \"bmcvkb\" )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a\nSELECT TUPLE\n  assign a\n";
    out += "Modifies(_,\"bmcvkb\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,_)
    queryStr = "  variable sdfv1; Select sdfv1 such that Modifies(  _  , _ )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable sdfv1\nSELECT TUPLE\n";
    out += "  variable sdfv1\n";
    out += "Modifies(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(assign,var) and Modifies(proc,var)
    queryStr = "assign Asd1; variable bv1; procedure eh1ty; ";
    queryStr += "Select bv1 such that Modifies(Asd1,bv1) and Modifies(eh1ty,bv1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign Asd1\n  variable bv1\n";
    out += "  procedure eh1ty\n";
    out += "SELECT TUPLE\n  variable bv1\nModifies(Asd1,bv1)\n";
    out += "Modifies(eh1ty,bv1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(while,var) and Modifies(if,var) and Modifies(_,"string")
    queryStr = "variable nfbg1; while dxfg1; if bv1hda; Select <bv1hda,dxfg1>";
    queryStr += " such that Modifies(dxfg1,nfbg1)  \t  and \n\t  ";
    queryStr += "Modifies(bv1hda,nfbg1)\n  and \n \t Modifies(_, \"hjs1\")";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable nfbg1\n  while dxfg1\n";
    out += "  if bv1hda\n";
    out += "SELECT TUPLE\n  if bv1hda\n  while dxfg1\nModifies(dxfg1,nfbg1)\n";
    out += "Modifies(bv1hda,nfbg1)\nModifies(_,\"hjs1\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    //////////////////////////////////////////////////////////////////
    // Repeated Modifies clause (ie. equivalent clauses)
    //////////////////////////////////////////////////////////////////
    queryStr = " while w1, w2; assign a1, a2; procedure proc1, proc2; ";
    queryStr += " stmt stmt1, stmt2; call call1, call2; if if1, if2; ";
    queryStr += " variable var1, var2, var3; prog_line pl1, pl2, pl3 ; ";
    queryStr += " Select   <w1,var2,pl1> such that Modifies(w1, var1) and ";
    queryStr += " Modifies(a1, var1) and Modifies(w1, var2) and ";
    queryStr += " Modifies(w1,var1)  and "; // R w1,var
    queryStr += " Modifies(call1, var1) and Modifies (proc1, var2) and ";
    queryStr += " Modifies(call1, var1)  and  "; // R call,var
    queryStr += " Modifies(stmt1, var2) and Modifies(if2, var3) and";
    queryStr += " Modifies(a1,var1) and "; // R assign,var
    queryStr += " Modifies(a2, var3) and Modifies(pl3, var2) and ";
    queryStr += " Modifies(stmt2, var2) and ";
    queryStr += " Modifies(proc1,var2) and "; // R proc,var
    queryStr += " Modifies(a1, \"strvar1\") and ";
    queryStr += " Modifies(pl3,var2) and "; // R prog_line,var
    queryStr += " Modifies(if2, var3) and "; // R if,var
    queryStr += " Modifies(if1, \"strvar2\") and ";
    queryStr += " Modifies(stmt2, var2) and ";  // R stmt,var
    queryStr += " Modifies(a2, \"strvar1\") and ";
    queryStr += " Modifies(a1, \"strvar1\") and "; // R syn,str
    queryStr += " Modifies(call1, _) and Modifies(\"myproc\", var1) and ";
    queryStr += " Modifies(stmt2, _) and Modifies(\"proc3\", var2) and ";
    queryStr += " Modifies(stmt2, _) and "; // R syn,_
    queryStr += " Modifies(\"myproc\", var1) and "; // R string,var
    queryStr += " Modifies(61, var1) and Modifies(735, _) and ";
    queryStr += " Modifies(\"doSmth\", \"avar\") and ";
    queryStr += " Modifies(\"f\",\"v\") and Modifies(17, \"ch\") and ";
    queryStr += " Modifies(61, var1) and "; // R int,var
    queryStr += " Modifies(\"doSmth\",\"avar\") and "; // R string,string
    queryStr += " Modifies(735,_) and "; // R int,_
    queryStr += " Modifies(9, \"str\") and Modifies(\"pp1\", _) and ";
    queryStr += " Modifies(23, \"blargh\") and Modifies(_, var2) and ";
    queryStr += " Modifies(\"pp1\",_) and "; // R string,_
    queryStr += " Modifies(23, \"blargh\") and "; // R int,string
    queryStr += " Modifies(_, var3) and Modifies(_, \"ch\") and ";
    queryStr += " Modifies(_, _) and Modifies(_, \"bleh\") and ";
    queryStr += " Modifies(_,\"blargh\") and ";
    queryStr += " Modifies(_,\"ch\") and "; // R _,string
    queryStr += " Modifies(_,var3) and Modifies(_, _) "; // R _,syn; R _,_
    // Dont show warnings
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while w1\n  while w2\n  assign a1\n";
    out += "  assign a2\n";
    out += "  procedure proc1\n  procedure proc2\n  stmt stmt1\n";
    out += "  stmt stmt2\n  call call1\n  call call2\n  if if1\n  if if2\n";
    out += "  variable var1\n  variable var2\n  variable var3\n";
    out += "  prog_line pl1\n  prog_line pl2\n  prog_line pl3\nSELECT TUPLE\n";
    out += "  while w1\n  variable var2\n  prog_line pl1\nModifies(w1,var1)\n";
    out += "Modifies(a1,var1)\nModifies(w1,var2)\nModifies(call1,var1)\n";
    out += "Modifies(proc1,var2)\nModifies(stmt1,var2)\nModifies(if2,var3)\n";
    out += "Modifies(a2,var3)\nModifies(pl3,var2)\nModifies(stmt2,var2)\n";
    out += "Modifies(a1,\"strvar1\")\nModifies(if1,\"strvar2\")\n";
    out += "Modifies(a2,\"strvar1\")\nModifies(call1,_)\n";
    out += "Modifies(\"myproc\",var1)\nModifies(stmt2,_)\n";
    out += "Modifies(\"proc3\",var2)\nModifies(61,var1)\nModifies(735,_)\n";
    out += "Modifies(\"doSmth\",\"avar\")\nModifies(\"f\",\"v\")\n";
    out += "Modifies(17,\"ch\")\nModifies(9,\"str\")\nModifies(\"pp1\",_)\n";
    out += "Modifies(23,\"blargh\")\nModifies(_,var2)\nModifies(_,var3)\n";
    out += "Modifies(_,\"ch\")\nModifies(_,_)\nModifies(_,\"bleh\")\n";
    out += "Modifies(_,\"blargh\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_err_parse_decl_empty_syn()
{
    string queryStr = "assign ";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_EMPTY_SYN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
        PARSE_DECL_EMPTY_SYN_STR, entity_type_to_string(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "procedure p1, p2; stmt s1; call ; Select s1  ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_EMPTY_SYN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
        PARSE_DECL_EMPTY_SYN_STR, entity_type_to_string(ENT_CALL));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_parse_decl_repeated_syn()
{
    string queryStr = "assign g; stmt s; call g; Select s";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_REPEATED_SYN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_DECL_REPEATED_SYN_STR,
        "g", entity_type_to_string(ENT_CALL),
        entity_type_to_string(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_parse_decl_invalid_syn()
{
    string queryStr = "assign a; stmt 1dkm14; Select a";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_INVALID_SYN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_DECL_INVALID_SYN_STR,
        "1dkm14");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_parse_decl_ent_syn_invalid_sep()
{
    string queryStr = "assign a; stmt*blt; Select a";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_ENT_SYN_INVALID_SEP,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_DECL_ENT_SYN_INVALID_SEP_STR,
        "*blt;");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_parse_decl_no_terminator()
{
    string queryStr = "stmt b1; prog_line pl1, pl2, pl3; call p Select b1";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_DECL_NO_TERMINATOR, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_DECL_NO_TERMINATOR_STR,
        ENT_CALL_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_parse_no_select_after_decl()
{
    string queryStr = "stmt s; assign a; bleh";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_NO_SELECT_AFTER_DECL,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_NO_SELECT_AFTER_DECL_STR,
        "bleh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_undeclared()
{
    string queryStr = "stmt s; Select a";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_SELECT_UNDECLARED, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_SELECT_UNDECLARED_STR, "a");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_undef_attrname()
{
    string queryStr = "stmt s; Select s.myName";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_UNDEF_ATTRNAME,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_ATTRREF_UNDEF_ATTRNAME_STR,
        "myName", "s");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "assign a; variable v; stmt g; Select <a, v.nonEx>";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_UNDEF_ATTRNAME,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_ATTRREF_UNDEF_ATTRNAME_STR,
        "nonEx", "v");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_undeclared_attrRef()
{
    string queryStr = "assign a; Select s.stmt#";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_UNDECLARED,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
        PARSE_ATTRREF_UNDECLARED_STR, "s",
        AttrRef("s", ENT_INVALID, ATTR_STMTNO).toPeriodString().c_str());
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_attrRef_syn_attrName_type_error()
{
    // assign.varName
    string queryStr = "assign a; Select a.varName";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
        parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
        PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
        AttrRef("a", ENT_ASSIGN, ATTR_VARNAME).toPeriodString().c_str(),
        "varName", ENT_ASSIGN_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // assign.procName
    queryStr = "assign bdb; Select bdb.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("bdb", ENT_ASSIGN, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_ASSIGN_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // assign.prog_line#
    queryStr = "assign hmjhmAS; Select hmjhmAS.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("hmjhmAS", ENT_ASSIGN, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_ASSIGN_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // assign.value
    queryStr = "assign xKcd; Select xKcd.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("xKcd", ENT_ASSIGN, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_ASSIGN_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // call.varName
    queryStr = "call bAd; Select bAd.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("bAd", ENT_CALL, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_CALL_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // call.prog_line#
    queryStr = "call Tefb1; Select Tefb1.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("Tefb1", ENT_CALL, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_CALL_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // call.value
    queryStr = "call md1#; Select md1#.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("md1#", ENT_CALL, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_CALL_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // if.varName
    queryStr = "if kM1; Select kM1.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("kM1", ENT_IF, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_IF_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // if.procName
    queryStr = "if Mms6; Select Mms6.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("Mms6", ENT_IF, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_IF_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // if.prog_line#
    queryStr = "if yjfjha; Select yjfjha.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("yjfjha", ENT_IF, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_IF_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // if.value
    queryStr = "if bb; Select bb.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("bb", ENT_IF, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_IF_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // while.varName
    queryStr = "while dbn; Select dbn.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("dbn", ENT_WHILE, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_WHILE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // while.procName
    queryStr = "while sxb; Select sxb.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("sxb", ENT_WHILE, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_WHILE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // while.prog_line#
    queryStr = "while Aa; Select Aa.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("Aa", ENT_WHILE, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_WHILE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // while.value
    queryStr = "while N; Select N.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("N", ENT_WHILE, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_WHILE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // stmt.varName
    queryStr = "stmt hmm; Select hmm.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("hmm", ENT_STMT, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_STMT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmt.procName
    queryStr = "stmt xb; Select xb.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("xb", ENT_STMT, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_STMT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmt.prog_line#
    queryStr = "stmt Tmb; Select Tmb.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("Tmb", ENT_STMT, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_STMT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmt.value
    queryStr = "stmt mgm; Select mgm.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("mgm", ENT_STMT, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_STMT_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // prog_line.varName
    queryStr = "prog_line bn; Select bn.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("bn", ENT_PROGLINE, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_PROGLINE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // prog_line.procName
    queryStr = "prog_line nmmn; Select nmmn.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("nmmn", ENT_PROGLINE, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_PROGLINE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // prog_line.stmt#
    queryStr = "prog_line gBa; Select gBa.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("gBa", ENT_PROGLINE, ATTR_STMTNO).toPeriodString()
                    .c_str(),
            ATTR_STMTNO_STR, ENT_PROGLINE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // prog_line.value
    queryStr = "prog_line yuu; Select yuu.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("yuu", ENT_PROGLINE, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_PROGLINE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // constant.varName
    queryStr = "constant c1; Select c1.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("c1", ENT_CONST, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_CONST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // constant.procName
    queryStr = "constant jhm; Select jhm.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("jhm", ENT_CONST, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_CONST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // constant.stmt#
    queryStr = "constant bn#h; Select bn#h.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("bn#h", ENT_CONST, ATTR_STMTNO).toPeriodString()
                    .c_str(),
            ATTR_STMTNO_STR, ENT_CONST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // constant.prog_line#
    queryStr = "constant ksd; Select ksd.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("ksd", ENT_CONST, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_CONST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // stmtLst.varName
    queryStr = "stmtLst sl1; Select sl1.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("sl1", ENT_STMTLST, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_STMTLST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmtLst.procName
    queryStr = "stmtLst hh; Select hh.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("hh", ENT_STMTLST, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_STMTLST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmtLst.prog_line#
    queryStr = "stmtLst gmma; Select gmma.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("gmma", ENT_STMTLST, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_STMTLST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // stmtLst.value
    queryStr = "stmtLst tmna; Select tmna.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("tmna", ENT_STMTLST, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_STMTLST_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // procedure.varName
    queryStr = "procedure p1; Select p1.varName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("p1", ENT_PROC, ATTR_VARNAME).toPeriodString()
                    .c_str(),
            ATTR_VARNAME_STR, ENT_PROC_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // procedure.stmt#
    queryStr = "procedure proc; Select proc.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("proc", ENT_PROC, ATTR_STMTNO).toPeriodString()
                    .c_str(),
            ATTR_STMTNO_STR, ENT_PROC_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // procedure.prog_line#
    queryStr = "procedure pBH; Select pBH.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("pBH", ENT_PROC, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_PROC_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // procedure.value
    queryStr = "procedure pnka; Select pnka.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("pnka", ENT_PROC, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_PROC_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // variable.procName
    queryStr = "variable v1; Select v1.procName";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("v1", ENT_VAR, ATTR_PROCNAME).toPeriodString()
                    .c_str(),
            ATTR_PROCNAME_STR, ENT_VAR_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // variable.stmt#
    queryStr = "variable var; Select var.stmt#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("var", ENT_VAR, ATTR_STMTNO).toPeriodString()
                    .c_str(),
            ATTR_STMTNO_STR, ENT_VAR_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // variable.prog_line#
    queryStr = "variable voo; Select voo.prog_line#";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("voo", ENT_VAR, ATTR_PROGLINE).toPeriodString()
                    .c_str(),
            ATTR_PROGLINE_STR, ENT_VAR_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    // variable.value
    queryStr = "variable voodoo; Select voodoo.value";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, this->BUFLEN, this->BUFLEN,
            PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR,
            AttrRef("voodoo", ENT_VAR, ATTR_VALUE).toPeriodString()
                    .c_str(),
            ATTR_VALUE_STR, ENT_VAR_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_invalid_attrRef()
{
    string queryStr = "stmt s; Select <s, 123za>";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_SELECT_INVALID_ATTRREF,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_SELECT_INVALID_ATTRREF_STR,
            "123za");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_tuple_no_close()
{
    string queryStr = "stmt s; assign a; Select <s,a  ";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_SELECT_TUPLE_NO_CLOSE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_SELECT_TUPLE_NO_CLOSE_STR);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_select_nothing()
{
    string queryStr = "stmt s; Select 13t";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_SELECT_NOTHING, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_SELECT_NOTHING_STR,
            "13t");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_argone()
{
    string queryStr = "stmt s; Select s such that Modifies(^5123,s)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
            relRefType_to_string(REL_MODIFIES), "^5123");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_no_comma()
{
    string queryStr = "assign a;variable v;Select a such that Modifies(a v)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_NO_COMMA, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_NO_COMMA_STR,
            relRefType_to_string(REL_MODIFIES));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_argtwo()
{
    string queryStr = "assign a; Select a such that Modifies(a,#53)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
            relRefType_to_string(REL_MODIFIES), "#53");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_arg_int_invalid()
{
    // TODO: Replace with stringbuffer
    char *tmpBuf = new char[500];
    long long tmpLL;

    string queryStr = "variable v; ";
    queryStr += "Select BOOLEAN such that Modifies(551234567890, v)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "551234567890",
            S_TO_INT_TOO_LONG);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Overflow
    queryStr = "stmt s; Select s such that Modifies(3234567890, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    tmpLL = 3234567890L;
    _snprintf(tmpBuf, 500, S_TO_INT_OVERFLOW, tmpLL);
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "3234567890",
            tmpBuf);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Overflow by 1
    queryStr = "stmt s; Select s such that Modifies(2147483648, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    tmpLL = 2147483648L;
    _snprintf(tmpBuf, 500, S_TO_INT_OVERFLOW, tmpLL);
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "2147483648",
            tmpBuf);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Underflow by 1
    queryStr = "stmt s; Select s such that Modifies(-2147483649, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    tmpLL = 2147483649L;
    _snprintf(tmpBuf, 500, S_TO_INT_UNDERFLOW, tmpLL);
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "-2147483649",
            tmpBuf);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Underflow by > 1
    queryStr = "stmt s; Select s such that Modifies(-5734567890, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    tmpLL = 5734567890L;
    _snprintf(tmpBuf, 500, S_TO_INT_UNDERFLOW, tmpLL);
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "-5734567890",
            tmpBuf);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    delete tmpBuf;
}

void Test_20_PQLParser::test_err_rel_argone_undeclared()
{
    string queryStr = "variable v; Select v such that Modifies(a,v)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_UNDECLARED_STR,
            relRefType_to_string(REL_MODIFIES), "a");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_argone_type_error()
{
    string queryStr = "variable v, v2; Select v such that Modifies(v,v2)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
            TYPE_ERROR_MODIFIES[0]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_argtwo_undeclared()
{
    string queryStr = "assign a; Select a such that Modifies(a,someVar)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_UNDECLARED_STR,
            relRefType_to_string(REL_MODIFIES), "someVar");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_argtwo_type_error()
{
    string queryStr = "assign a; stmt s; Select s such that Modifies(a,s)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_MODIFIES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_rel_no_rparen()
{
    string queryStr = "assign a; variable v; Select a such that Modifies(a,v";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_NO_RPAREN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_NO_RPAREN_STR,
            relRefType_to_string(REL_MODIFIES), "Modifies(a,v)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_relcond_and_nosep()
{
    string queryStr = "assign a1, a2; variable v1, v2;";
    queryStr += " Select a1 such that Modifies(a1,v1) and# Modifies(a2,v2)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_RELCOND_AND_NOSEP, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_RELCOND_AND_NOSEP_STR,
            "Modifies(a1,v1)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_relcond_invalid_relRef()
{
    string queryStr = "stmt g1, g2; ";
    queryStr += "Select g1 such that Modifies(g1,_) and Nonsense(s1,s2)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_RELCOND_INVALID_RELREF,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_RELCOND_INVALID_RELREF_STR,
            "Nonsense(s1,s2)", "Modifies(g1,_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_end_of_query_error()
{
    string queryStr = "procedure p1, p2; variable v1, v2; ";
    queryStr += "Select p1 such that Modifies(p1,v1) and Modifies(p2,v2) sdf1";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_END_OF_QUERY_ERROR, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_END_OF_QUERY_ERROR_STR,
            "sdf1");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_uses()
{
    // Uses(assign,var)
    string queryStr = "assign a; variable v; Select a such that Uses(a,v)";
    string out;
    PQLParser parser;
    QueryInfo *qinfo;
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a\n  variable v\n";
    out += "SELECT TUPLE\n";
    out += "  assign a\nUses(a,v)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(if,var)
    queryStr = "if ivb1; variable sdf1; ";
    queryStr += "Select sdf1 such that Uses(ivb1,sdf1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  if ivb1\n  variable sdf1\n";
    out += "SELECT TUPLE\n";
    out += "  variable sdf1\nUses(ivb1,sdf1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(while,var)
    queryStr = "while fdg1; variable hd1bd#; ";
    queryStr += "Select fdg1 such that Uses(fdg1, hd1bd#)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  while fdg1\n  variable hd1bd#\n";
    out += "SELECT TUPLE\n";
    out += "  while fdg1\nUses(fdg1,hd1bd#)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(procedure,var)
    queryStr = " variable mmmsdf1; procedure pfdgy; ";
    queryStr += "Select mmmsdf1 such that Uses(pfdgy, mmmsdf1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  variable mmmsdf1\n  procedure pfdgy\n";
    out += "SELECT TUPLE\n  variable mmmsdf1\nUses(pfdgy,mmmsdf1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(call,var)
    queryStr = " call cvfh; variable tr14531; ";
    queryStr += " Select cvfh such that Uses(cvfh, tr14531)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  call cvfh\n  variable tr14531\n";
    out += "SELECT TUPLE\n";
    out += "  call cvfh\nUses(cvfh,tr14531)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(stmt,var)
    queryStr = " stmt sfsdf1; variable mbv; ";
    queryStr += "Select mbv such that Uses(sfsdf1,  mbv)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  stmt sfsdf1\n  variable mbv\n";
    out += "SELECT TUPLE\n";
    out += "  variable mbv\nUses(sfsdf1,mbv)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(prog_line,var)
    queryStr = " variable ywert1; prog_line pldg1; ";
    queryStr += "Select pldg1 such that Uses(pldg1, ywert1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  variable ywert1\n  prog_line pldg1\n";
    out += "SELECT TUPLE\n  prog_line pldg1\nUses(pldg1,ywert1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(synonym,"string")
    queryStr = " stmt fg1; Select fg1 such that Uses(fg1, \"bleh\")";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  stmt fg1\nSELECT TUPLE\n  stmt fg1\n";
    out += "Uses(fg1,\"bleh\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(synonym,_)
    queryStr = " procedure qwey1b; Select BOOLEAN such that Uses(qwey1b,_)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  procedure qwey1b\nSELECT BOOLEAN\n";
    out += "Uses(qwey1b,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses("string",var)
    queryStr = "variable v1, v2; Select v1 such that Uses(\"proc\",v1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  variable v1\n  variable v2\n";
    out += "SELECT TUPLE\n";
    out += "  variable v1\nUses(\"proc\",v1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses("string","string")
    queryStr = " assign db1; Select db1 such that Uses(\"bxcv1\",\"mmn1\")";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign db1\nSELECT TUPLE\n";
    out += "  assign db1\n";
    out += "Uses(\"bxcv1\",\"mmn1\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses("string",_)
    queryStr = " while sfg1; Select sfg1 such that Uses(\"uydr\",_)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  while sfg1\nSELECT TUPLE\n";
    out += "  while sfg1\n";
    out += "Uses(\"uydr\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(int,var)
    queryStr = " while sd;variable bm1; Select sd such that Uses(634, bm1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  while sd\n  variable bm1\n";
    out += "SELECT TUPLE\n";
    out += "  while sd\nUses(634,bm1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(int,var), int is negative
    queryStr = " while sd;variable bm1; Select sd such that ";
    queryStr += " Uses(  -71231, bm1)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  while sd\n  variable bm1\n";
    out += "SELECT TUPLE\n";
    out += "  while sd\nUses(-71231,bm1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(int,"string")
    queryStr = " prog_line pl1; Select pl1 such that Uses(83, \"warf\")";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  prog_line pl1\nSELECT TUPLE\n";
    out += "  prog_line pl1\n";
    out += "Uses(83,\"warf\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(int,_)
    queryStr = "Select BOOLEAN such that Uses(58542,_)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\nSELECT BOOLEAN\nUses(58542,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(_,var)
    queryStr = " call cl13; variable x; Select cl13 such that Uses(_, x)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  call cl13\n  variable x\n";
    out += "SELECT TUPLE\n";
    out += "  call cl13\nUses(_,x)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(_,"string")
    queryStr = " constant m2; Select m2 such that Uses(_, \"hohoho\")";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  constant m2\nSELECT TUPLE\n";
    out += "  constant m2\n";
    out += "Uses(_,\"hohoho\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Uses(_,_)
    queryStr = " assign a3; variable sdf1; Select <a3,sdf1> such that ";
    queryStr += " Uses(_,_)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a3\n  variable sdf1\n";
    out += "SELECT TUPLE\n";
    out += "  assign a3\n  variable sdf1\nUses(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Multiple Uses
    queryStr = " assign a; variable v, v2; procedure p; ";
    queryStr += "Select <a,p> such that Uses(a,v) and Uses(p,v2)";
    parser.parse(queryStr, false, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a\n  variable v\n";
    out += "  variable v2\n";
    out += "  procedure p\nSELECT TUPLE\n  assign a\n  procedure p\n";
    out += "Uses(a,v)\nUses(p,v2)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Repeated Uses
    queryStr = "assign a1, a2, a3; if i1, i2, i3; while w1, w2, w3; ";
    queryStr += "procedure p1, p2, p3; call c1, c2, c3; stmt s1, s2, s3; ";
    queryStr += "prog_line pl1, pl2, pl3; variable v1, v2, v3; ";
    queryStr += "Select <a1,a1.stmt#,i1,i1.stmt#,w1,w1.stmt#,p2,p2.procName,";
    queryStr += "c1,c2.procName,s1,s1.stmt#,pl1> such that ";
    queryStr += " Uses(a1,v1) and Uses(i1, v2) and Uses(w1, v1) and ";
    queryStr += " Uses(p1, v1) and Uses(c1, v2) and Uses(s2, v2) and ";
    queryStr += " Uses(pl1, v3) and ";
    // Repeated Uses(synonym,var)
    queryStr += " Uses(a1,v1) and Uses(i1,v2) and Uses(w1,v1) and ";
    queryStr += " Uses(p1,v1) and Uses(c1,v2) and Uses(s2,v2) and ";
    queryStr += " Uses(pl1,v3) and ";
    // Uses(syn,"string"), Uses(syn,_)
    queryStr += " Uses(c2, \"avar\") and Uses(i3,_) and ";
    // Repeated Uses(syn,"string") and Uses(syn,_)
    queryStr += " Uses(c2, \"avar\") and Uses(i3,_) and ";
    // Uses(string,*)
    queryStr += " Uses(\"proc1\",v3) and Uses(\"someProc\", \"x\") and ";
    queryStr += " Uses(\"vsd\", _) and ";
    // Repeated Uses(string,*)
    queryStr += " Uses(\"proc1\", v3) and Uses(\"someProc\",\"x\") and ";
    queryStr += " Uses(\"vsd\",_) and ";
    // Uses(int, *)
    queryStr += " Uses(51, v2) and Uses(7351, \"bvar\") and ";
    queryStr += " Uses(26434, _) and ";
    // Repeated Uses(int, *)
    queryStr += " Uses(51, v2) and Uses(7351, \"bvar\") and ";
    queryStr += " Uses(26434, _) and ";
    // Uses(_,*)
    queryStr += " Uses(_, v1) and Uses(_, \"hsfg\") and Uses(_,_) and ";
    // Repeated Uses(_,*)
    queryStr += " Uses(_,v1) and Uses(_,\"hsfg\") and Uses(_,_)";
    parser.parse(queryStr, true, false);
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    qinfo = parser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n  assign a3\n";
    out += "  if i1\n  if i2\n  if i3\n  while w1\n  while w2\n  while w3\n";
    out += "  procedure p1\n  procedure p2\n  procedure p3\n  call c1\n";
    out += "  call c2\n  call c3\n  stmt s1\n  stmt s2\n  stmt s3\n";
    out += "  prog_line pl1\n  prog_line pl2\n  prog_line pl3\n";
    out += "  variable v1\n  variable v2\n  variable v3\n";
    out += "SELECT TUPLE\n  assign a1\n  assign a1 stmt#\n  if i1\n";
    out += "  if i1 stmt#\n  while w1\n  while w1 stmt#\n  procedure p2\n";
    out += "  procedure p2 procName\n  call c1\n  call c2 procName\n";
    out += "  stmt s1\n  stmt s1 stmt#\n  prog_line pl1\n";
    out += "Uses(a1,v1)\nUses(i1,v2)\nUses(w1,v1)\nUses(p1,v1)\n";
    out += "Uses(c1,v2)\nUses(s2,v2)\nUses(pl1,v3)\nUses(c2,\"avar\")\n";
    out += "Uses(i3,_)\nUses(\"proc1\",v3)\nUses(\"someProc\",\"x\")\n";
    out += "Uses(\"vsd\",_)\nUses(51,v2)\nUses(7351,\"bvar\")\n";
    out += "Uses(26434,_)\nUses(_,v1)\nUses(_,\"hsfg\")\nUses(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_err_uses_argtypes()
{
    string queryStr = " stmtLst vf; variable g; ";
    queryStr += " Select vf such that Uses(vf,g)";
    string out;
    PQLParser parser;
    ostringstream *os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
            TYPE_ERROR_USES[0]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " variable v1, v2; Select v1 such that Uses(v1, v2)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
            TYPE_ERROR_USES[0]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " variable bdf; constant c1; ";
    queryStr += " Select c1 such that Uses(c1, bdf)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
            TYPE_ERROR_USES[0]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // arg two
    queryStr = "  procedure p1; Select p1 such that Uses(_,p1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " stmtLst s1; Select s1 such that Uses(_,s1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "stmt sdf1; Select BOOLEAN such that Uses(_,sdf1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "assign bdf1; Select bdf1 such that Uses(_, bdf1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "call fb1; Select fb1 such that Uses(_, fb1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "while w123; Select w123 such that Uses(_, w123)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "if iy35; Select iy35 such that Uses(_,iy35)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "constant mbd1; Select mbd1 such that Uses(_,mbd1)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "prog_line pl67; Select pl67 such that Uses(_,pl67)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
            TYPE_ERROR_USES[1]);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // arg two int
    queryStr = "stmt dfg1; Select dfg1 such that Uses(_,3452)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
            relRefType_to_string(REL_USES), "3452");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_calls_and_star()
{
    set<const char*> S;
    S.insert(CALLS_STR);
    S.insert(CALLS_STAR_STR);
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    ostringstream *os;
    QueryInfo *qinfo;

    for (set<const char*>::const_iterator it = S.begin(); it != S.end();
            it++) {
        // Calls(proc,proc)
        sb.clear();
        sb.substitutef(" procedure p1, p2; Select p1 such that %s(p1,p2)",
                *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  procedure p1\n");
        sb.append("  procedure p2\n");
        sb.append("SELECT TUPLE\n  procedure p1\n");
        sb.substitutef("%s(p1,p2)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls(proc,"string")
        sb.clear();
        sb.substitutef(
            "procedure fv1; Select fv1 such that %s(fv1, \"proc2\")", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append(
            "ALIVE\nDECLARATIONS\n  procedure fv1\nSELECT TUPLE\n");
        sb.append("  procedure fv1\n");
        sb.substitutef("%s(fv1,\"proc2\")\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls(proc,_)
        sb.clear();
        sb.append("procedure bfg1; assign a123; ");
        sb.substitutef(" Select a123 such that %s(bfg1,_)", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append(
            "ALIVE\nDECLARATIONS\n  procedure bfg1\n  assign a123\n");
        sb.append("SELECT TUPLE\n");
        sb.substitutef("  assign a123\n%s(bfg1,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls("string",proc)
        sb.clear();
        sb.substitutef(
            "procedure s1; Select s1 such that %s(\"myProc\",s1)", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append(
            "ALIVE\nDECLARATIONS\n  procedure s1\nSELECT TUPLE\n");
        sb.append("  procedure s1\n");
        sb.substitutef("%s(\"myProc\",s1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls("string","string")
        sb.clear();
        sb.substitutef(
            "procedure f; Select f such that %s(\"a1\",\"b2s\")", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append(
            "ALIVE\nDECLARATIONS\n  procedure f\nSELECT TUPLE\n");
        sb.append("  procedure f\n");
        sb.substitutef("%s(\"a1\",\"b2s\")\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls("string",_)
        sb.clear();
        sb.substitutef(" assign sd1; Select sd1 such that %s(\"blah\",_)",
                *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign sd1\nSELECT TUPLE\n");
        sb.append("  assign sd1\n");
        sb.substitutef("%s(\"blah\",_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls(_,proc)
        sb.clear();
        sb.append("while w1; procedure s; Select <w1, s> such that ");
        sb.substitutef("%s(_,s)", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  while w1\n  procedure s\n");
        sb.append("SELECT TUPLE\n");
        sb.substitutef("  while w1\n  procedure s\n%s(_,s)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls(_,"string")
        sb.clear();
        sb.substitutef("stmt s1; Select s1 such that %s(_,\"df1\")", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s1\nSELECT TUPLE\n");
        sb.append("  stmt s1\n");
        sb.substitutef("%s(_,\"df1\")\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Calls(_,_)
        sb.clear();
        sb.substitutef("assign asb; Select asb such that %s(_,_)", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign asb\nSELECT TUPLE\n");
        sb.append("  assign asb\n");
        sb.substitutef("%s(_,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Multiple calls
        sb.clear();
        sb.append("procedure p1, p2; ");
        sb.substitutef(" Select p1 such that %s(p1,p2) and %s(p2, \"tig\")",
                *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  procedure p1\n");
        sb.append("  procedure p2\n");
        sb.substitutef(
            "SELECT TUPLE\n  procedure p1\n%s(p1,p2)\n%s(p2,\"tig\")\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Repeated clauses
        sb.clear();
        sb.append("procedure p1, p2, p3, p4, p5; while w1; assign a2; ");
        sb.append("Select <p1.procName, p1, a2, w1, p2.procName> such that ");
        sb.substitutef(" %s(p1,p2) and %s(p3,\"aproc\") and %s(p4,_) and ",
                *it);
        // Repeated Calls(proc,*)
        sb.substitutef(" %s(p1,p2) and %s(p3,\"aproc\") and %s(p4,_) and ",
                *it);
        // Calls("string",*)
        sb.substitutef(" %s(\"a\",p3) and %s(\"bs\",\"sdf\") and ", *it);
        sb.substitutef(" %s(\"jfgh\", _) and ", *it);
        // Repeated Calls("string",*)
        sb.substitutef(" %s(\"a\",p3) and %s(\"bs\",\"sdf\") and ", *it);
        sb.substitutef(" %s(\"jfgh\", _) and ", *it);
        // Calls(_,*)
        sb.substitutef(" %s(_,p4) and %s(_,\"someProc\") and %s(_,_) and ",
                *it);
        // Repeated Calls(_,*)
        sb.substitutef(" %s(_,p4) and %s(_,\"someProc\") and %s(_,_) ", *it);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  procedure p1\n");
        sb.append("  procedure p2\n");
        sb.append("  procedure p3\n  procedure p4\n  procedure p5\n");
        sb.append("  while w1\n  assign a2\n");
        sb.append("SELECT TUPLE\n  procedure p1 procName\n  procedure p1\n");
        sb.append("  assign a2\n  while w1\n  procedure p2 procName\n");
        sb.substitutef("%s(p1,p2)\n%s(p3,\"aproc\")\n%s(p4,_)\n", *it);
        sb.substitutef("%s(\"a\",p3)\n%s(\"bs\",\"sdf\")\n%s(\"jfgh\",_)\n",
                *it);
        sb.substitutef("%s(_,p4)\n%s(_,\"someProc\")\n%s(_,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    }
}

void Test_20_PQLParser::test_err_calls_and_star_argtypes()
{
    set<pair<const char*, const char **> > S;
    S.insert(pair<const char *, const char**>(CALLS_STR, TYPE_ERROR_CALLS));
    S.insert(pair<const char *, const char **>
                (CALLS_STAR_STR, TYPE_ERROR_CALLS_STAR));
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    ostringstream *os;

    for (set<pair<const char*, const char **> >::const_iterator
            it = S.begin(); it != S.end(); it++) {
        // Calls(stmtLst,_)
        sb.clear();
        sb.substitutef("stmtLst s; Select s such that %s(s,_)", it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(stmt,_)
        sb.clear();
        sb.substitutef("stmt s; Select s such that %s(s,_)", it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(assign,_)
        sb.clear();
        sb.substitutef("assign a; Select a such that %s(a,_)", it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(call,_)
        sb.clear();
        sb.substitutef("call df; Select df such that %s(df,_)", it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(while,_)
        sb.clear();
        sb.substitutef("while fsdf; Select fsdf such that %s(fsdf,_)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(if,_)
        sb.clear();
        sb.substitutef(" if bda; Select bda such that %s(bda,_)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(variable,_)
        sb.clear();
        sb.substitutef("variable fgdf; Select fgdf such that %s(fgdf,_)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(constant,_)
        sb.clear();
        sb.substitutef("constant As1; Select As1 such that %s(As1,_)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(prog_line,_)
        sb.clear();
        sb.substitutef("prog_line bs; Select bs such that %s(bs,_)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_TYPE_ERROR_STR,
                it->second[0]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,stmtLst)
        sb.clear();
        sb.substitutef("stmtLst gs123; Select gs123 such that %s(_,gs123)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,stmt)
        sb.clear();
        sb.substitutef("stmt mfw; Select mfw such that %s(_,mfw)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,assign)
        sb.clear();
        sb.substitutef("assign sdg1; Select sdg1 such that %s(_,sdg1)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,call)
        sb.clear();
        sb.substitutef("call bdf1; Select bdf1 such that %s(_,bdf1)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,while)
        sb.clear();
        sb.substitutef("while Kdf1; Select Kdf1 such that %s(_,Kdf1)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,if)
        sb.clear();
        sb.substitutef("if jms1; Select jms1 such that %s(_,jms1)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,variable)
        sb.clear();
        sb.substitutef("variable yof; Select yof such that %s(_,yof)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,constant)
        sb.clear();
        sb.substitutef("constant g2d; Select g2d such that %s(_,g2d)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Calls(_,prog_line)
        sb.clear();
        sb.substitutef("prog_line mbn8; Select mbn8 such that %s(_,mbn8)",
                it->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_TYPE_ERROR_STR,
                it->second[1]);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }

    // Calls(Int,_)
    queryStr = "constant ng1; Select ng1 such that Calls(52,_)",
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
            relRefType_to_string(REL_CALLS), "52");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Calls(_,Int)
    queryStr = "assign iupc; Select iupc such that Calls(_,731)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
            relRefType_to_string(REL_CALLS), "731");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Calls*(Int,_)
    queryStr = "constant ng1; Select ng1 such that Calls*(52,_)",
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
            relRefType_to_string(REL_CALLS_STAR), "52");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // Calls*(_,Int)
    queryStr = "assign iupc; Select iupc such that Calls*(_,731)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
            relRefType_to_string(REL_CALLS_STAR), "731");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_parent_and_star()
{
    set<const char *> S;
    S.insert(PARENT_STR);
    S.insert(PARENT_STAR_STR);
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    QueryInfo *qinfo;

    for (set<const char *>::const_iterator it = S.begin(); it != S.end();
            it++) {
        // Parent(stmt,stmt)
        sb.clear();
        sb.substitutef("stmt sg, jdg1; Select sg such that %s(sg, jdg1)",
                *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt sg\n  stmt jdg1\n"
                "SELECT TUPLE\n");
        sb.substitutef("  stmt sg\n%s(sg,jdg1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(while,stmt)
        sb.clear();
        sb.append("stmt bndf; while sdf; Select sdf such that ");
        sb.substitutef("%s(sdf,bndf)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt bndf\n  while sdf\n"
                "SELECT TUPLE\n");
        sb.substitutef("  while sdf\n%s(sdf,bndf)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(if,stmt)
        sb.clear();
        sb.append(" if mkh1; stmt nf1; Select mkh1 such that ");
        sb.substitutef("%s(mkh1, nf1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  if mkh1\n  stmt nf1\n"
                "SELECT TUPLE\n");
        sb.substitutef("  if mkh1\n%s(mkh1,nf1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(prog_line,stmt)
        sb.clear();
        sb.append("stmt b1; prog_line ply1; Select ply1 such that ");
        sb.substitutef("%s(ply1,b1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt b1\n  prog_line ply1\n"
                "SELECT TUPLE\n");
        sb.substitutef("  prog_line ply1\n%s(ply1,b1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym, assign)
        sb.clear();
        sb.append("assign qw1; stmt jf; Select jf such that ");
        sb.substitutef("%s(jf,qw1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign qw1\n  stmt jf\n"
                "SELECT TUPLE\n");
        sb.substitutef("  stmt jf\n%s(jf,qw1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym,call)
        sb.clear();
        sb.append(" stmt jhd; call cy; Select <jhd,cy> such that ");
        sb.substitutef("%s(jhd,cy)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt jhd\n  call cy\n"
                "SELECT TUPLE\n");
        sb.substitutef("  stmt jhd\n  call cy\n%s(jhd,cy)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym,while)
        sb.clear();
        sb.append("while hb1; stmt ksdfg; Select hb1 such that ");
        sb.substitutef("%s(ksdfg,hb1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  while hb1\n  stmt ksdfg\n"
                "SELECT TUPLE\n");
        sb.substitutef("  while hb1\n%s(ksdfg,hb1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym,if)
        sb.clear();
        sb.append(" if kh1; stmt s123; Select kh1 such that ");
        sb.substitutef("%s(s123,kh1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  if kh1\n  stmt s123\n"
                "SELECT TUPLE\n");
        sb.substitutef("  if kh1\n%s(s123,kh1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym, prog_line)
        sb.clear();
        sb.append(" stmt yrq; prog_line plb1; Select plb1 such that ");
        sb.substitutef("%s(yrq,plb1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt yrq\n  prog_line plb1\n");
        sb.append("SELECT TUPLE\n  prog_line plb1\n");
        sb.substitutef("%s(yrq,plb1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym,Int)
        sb.clear();
        sb.append("while g1; Select g1 such that ");
        sb.substitutef("%s(g1,6724)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  while g1\nSELECT TUPLE\n"
                "  while g1\n");
        sb.substitutef("%s(g1,6724)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(synonym,_)
        sb.clear();
        sb.append("assign bd1; stmt uy7; Select bd1 such that ");
        sb.substitutef("%s(uy7, _)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign bd1\n  stmt uy7\n"
                "SELECT TUPLE\n");
        sb.substitutef("  assign bd1\n%s(uy7,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(Int,synonym)
        sb.clear();
        sb.append("stmt bhn1; Select bhn1 such that ");
        sb.substitutef("%s(32, bhn1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt bhn1\nSELECT TUPLE\n"
                "  stmt bhn1\n");
        sb.substitutef("%s(32,bhn1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(Int,synonym), Int is negative
        sb.clear();
        sb.append("stmt bhn1; Select bhn1 such that ");
        sb.substitutef("%s(-124, bhn1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt bhn1\nSELECT TUPLE\n"
                "  stmt bhn1\n");
        sb.substitutef("%s(-124,bhn1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(Int,Int)
        sb.clear();
        sb.append("while ht1; Select ht1 such that ");
        sb.substitutef("%s( 72, 3362)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  while ht1\nSELECT TUPLE\n"
                "  while ht1\n");
        sb.substitutef("%s(72,3362)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(Int,Int), both Int are negative
        sb.clear();
        sb.append("while ht1; Select ht1 such that ");
        sb.substitutef("%s( -1578, -2147483648)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  while ht1\nSELECT TUPLE\n"
                "  while ht1\n");
        sb.substitutef("%s(-1578,-2147483648)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(Int,_)
        sb.clear();
        sb.append("constant vb1; Select vb1 such that ");
        sb.substitutef("%s(4,_)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  constant vb1\nSELECT TUPLE\n");
        sb.substitutef("  constant vb1\n%s(4,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(_,synonym)
        sb.clear();
        sb.append("stmt khs; Select khs such that ");
        sb.substitutef("%s(_,khs)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt khs\nSELECT TUPLE\n"
                "  stmt khs\n");
        sb.substitutef("%s(_,khs)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(_,Int)
        sb.clear();
        sb.append(" variable v; Select v such that ");
        sb.substitutef("%s(_, 51)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  variable v\nSELECT TUPLE\n");
        sb.substitutef("  variable v\n%s(_,51)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Parent(_,_)
        sb.clear();
        sb.append(" stmt s; Select s such that ");
        sb.substitutef("%s(_,_)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s\nSELECT TUPLE\n"
                "  stmt s\n");
        sb.substitutef("%s(_,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Multiple Parent
        sb.clear();
        sb.append(" stmt s1; while w1; if i1; assign a1; Select <s1,w1> ");
        sb.substitutef("such that %s(s1,i1) and %s(w1,a1)", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s1\n  while w1\n"
                "  if i1\n");
        sb.append("  assign a1\nSELECT TUPLE\n  stmt s1\n  while w1\n");
        sb.substitutef("%s(s1,i1)\n%s(w1,a1)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Repeated clauses
        sb.clear();
        sb.append(" stmt s1, s2, s3; assign a1, a2, a3; call c1, c2, c3; ");
        sb.append("while w1, w2, w3; if i1, i2, i3; variable v1, v2, v3;");
        sb.append("constant const1, const2; prog_line pl1, pl2, pl3; ");
        sb.append("Select <s1,s1.stmt#,s2,a1,a1.stmt#, c1, c1.procName,");
        sb.append(" w1,w1.stmt#, w2, i1.stmt#, i2.stmt#, v1, v1.varName, ");
        sb.append(" const1, const1.value, const2, pl1> such that ");
        // Parent(syn,syn)
        sb.substitutef("%s(s1,s3) and %s(w1, s3) and %s(i1, s3) and ", *it);
        sb.substitutef("%s(pl1,s3) and %s(w1, a1) and %s(w1, c1) and ", *it);
        sb.substitutef("%s(w1,w3) and %s(w2,i2) and %s(w2, pl3) and ", *it);
        // Repeated Parent(syn,syn)
        sb.substitutef("%s(s1,s3) and %s(w1, s3) and %s(i1, s3) and ", *it);
        sb.substitutef("%s(pl1,s3) and %s(w1, a1) and %s(w1, c1) and ", *it);
        sb.substitutef("%s(w1,w3) and %s(w2,i2) and %s(w2, pl3) and ", *it);
        // Parent(syn,Int), Parent(syn,_)
        sb.substitutef("%s(i1, 62) and %s(i1,_) and ", *it);
        // Repeated Parent(syn,Int), Parent(syn,_)
        sb.substitutef("%s(i1, 62) and %s(i1,_)  and ", *it);
        // Parent(Int,*)
        sb.substitutef("%s(84,pl2) and %s(1,9752) and %s(73515,_) and ", *it);
        // Repeated Parent(Int,*)
        sb.substitutef("%s(84,pl2) and %s(1,9752) and %s(73515,_) and ", *it);
        // Parent(_,*)
        sb.substitutef("%s(_,a2) and %s(_,723) and %s(_,_) and ", *it);
        // Repeated Parent(_,*)
        sb.substitutef("%s(_,a2) and %s(_,723) and %s(_,_) ", *it);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        qinfo = parser.get_queryinfo();
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s1\n  stmt s2\n"
                "  stmt s3\n");
        sb.append("  assign a1\n  assign a2\n  assign a3\n  call c1\n");
        sb.append("  call c2\n  call c3\n  while w1\n  while w2\n");
        sb.append("  while w3\n  if i1\n  if i2\n  if i3\n  variable v1\n");
        sb.append("  variable v2\n  variable v3\n  constant const1\n");
        sb.append("  constant const2\n  prog_line pl1\n  prog_line pl2\n");
        sb.append("  prog_line pl3\nSELECT TUPLE\n  stmt s1\n");
        sb.append("  stmt s1 stmt#\n  stmt s2\n  assign a1\n");
        sb.append("  assign a1 stmt#\n  call c1\n  call c1 procName\n");
        sb.append("  while w1\n  while w1 stmt#\n  while w2\n  if i1 stmt#\n");
        sb.append("  if i2 stmt#\n  variable v1\n  variable v1 varName\n");
        sb.append("  constant const1\n  constant const1 value\n");
        sb.append("  constant const2\n  prog_line pl1\n");
        sb.substitutef("%s(s1,s3)\n%s(w1,s3)\n%s(i1,s3)\n", *it);
        sb.substitutef("%s(pl1,s3)\n%s(w1,a1)\n%s(w1,c1)\n", *it);
        sb.substitutef("%s(w1,w3)\n%s(w2,i2)\n%s(w2,pl3)\n", *it);
        sb.substitutef("%s(i1,62)\n%s(i1,_)\n", *it);
        sb.substitutef("%s(84,pl2)\n%s(1,9752)\n%s(73515,_)\n", *it);
        sb.substitutef("%s(_,a2)\n%s(_,723)\n%s(_,_)\n", *it);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    }
}

void Test_20_PQLParser::test_err_parent_and_star_argtypes()
{
    set<pair<const char *, const char **> > RS;
    RS.insert(pair<const char *, const char **>
                (PARENT_STR, TYPE_ERROR_PARENT));
    RS.insert(pair<const char *, const char **>
                (PARENT_STAR_STR, TYPE_ERROR_PARENT_STAR));
    StringBuffer sb;
    string queryStr;
    string out;
    PQLParser parser;
    ostringstream *os;

    // invalid synonym types for arg 1
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_PROC_STR, "p"));
    ESONE.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "nd"));
    ESONE.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "a"));
    ESONE.insert(pair<const char *, const char *>(ENT_CALL_STR, "c"));
    ESONE.insert(pair<const char *, const char *>(ENT_VAR_STR, "v"));
    ESONE.insert(pair<const char *, const char *>(ENT_CONST_STR, "c1"));
    // invalid synonym types for arg 2
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_PROC_STR, "p"));
    ESTWO.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "mn"));
    ESTWO.insert(pair<const char *, const char *>(ENT_VAR_STR, "v"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CONST_STR, "c"));

    for (set<pair<const char *, const char **> >::const_iterator
            relIt = RS.begin(); relIt != RS.end(); relIt++) {
        // arg one synonym errors
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(%s,_)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGONE_TYPE_ERROR_STR,
                    relIt->second[0]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }

        // Parent("string",_)
        sb.clear();
        sb.sprintf("Select BOOLEAN such that %s(\"awhile\",_)",
                relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
                relIt->first, "\"awhile\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // arg two synonym errors
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(_,%s)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGTWO_TYPE_ERROR_STR, relIt->second[1]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }

        // Parent(_,"string")
        sb.clear();
        sb.sprintf("Select BOOLEAN such that %s(_, \"line2\")",
                relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
                relIt->first, "\"line2\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }
}

void Test_20_PQLParser::test_follows_and_star()
{
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    QueryInfo *qinfo;

    set<const char *> RS;
    RS.insert(FOLLOWS_STR);
    RS.insert(FOLLOWS_STAR_STR);
    // ok synonym types for arg 1
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_STMT_STR, "s"));
    ESONE.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "a"));
    ESONE.insert(pair<const char *, const char *>(ENT_CALL_STR, "ch"));
    ESONE.insert(pair<const char *, const char *>(ENT_WHILE_STR, "w"));
    ESONE.insert(pair<const char *, const char *>(ENT_IF_STR, "ihs"));
    ESONE.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "bnd"));
    // ok synonym types for arg 2
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_STMT_STR, "ut"));
    ESTWO.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "nc"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CALL_STR, "c"));
    ESTWO.insert(pair<const char *, const char *>(ENT_WHILE_STR, "b"));
    ESTWO.insert(pair<const char *, const char *>(ENT_IF_STR, "i"));
    ESTWO.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "pln"));

    for (set<const char *>::const_iterator relIt = RS.begin();
            relIt != RS.end(); relIt++) {
        // Arg One
        // Parent(syn*,stmt)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.append("stmt jfd; ");
            sb.sprintf("%s %s; Select %s such that %s(%s,jfd)",
                    entIt->first, entIt->second, entIt->second,
                    *relIt, entIt->second);
            queryStr = sb.toString();
            parser.parse(queryStr, false, false);
            qinfo = parser.get_queryinfo();
            CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
            sb.clear();
            sb.append("ALIVE\nDECLARATIONS\n  stmt jfd\n");
            sb.sprintf("  %s %s\nSELECT TUPLE\n  %s %s\n%s(%s,jfd)\n",
                    entIt->first, entIt->second, entIt->first, entIt->second,
                    *relIt, entIt->second);
            out = sb.toString();
            CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        }
        // Parent(Int,stmt)
        sb.clear();
        sb.append("stmt Qer1; Select Qer1 such that ");
        sb.substitutef("%s(627, Qer1)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt Qer1\nSELECT TUPLE\n"
                "  stmt Qer1\n");
        sb.substitutef("%s(627,Qer1)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Parent(Int,stmt), Int is negative
        sb.clear();
        sb.append("stmt Qer1; Select Qer1 such that ");
        sb.substitutef("%s(-2147483648, Qer1)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt Qer1\nSELECT TUPLE\n"
                "  stmt Qer1\n");
        sb.substitutef("%s(-2147483648,Qer1)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Parent(_,stmt)
        sb.clear();
        sb.append("stmt df1; Select df1 such that ");
        sb.substitutef("%s(_,df1)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt df1\nSELECT TUPLE\n"
                "  stmt df1\n");
        sb.substitutef("%s(_,df1)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Arg Two
        // Parent(_,syn*)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(_,%s)",
                    entIt->first, entIt->second, entIt->second,
                    *relIt, entIt->second);
            queryStr = sb.toString();
            parser.parse(queryStr, false, false);
            qinfo = parser.get_queryinfo();
            CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
            sb.clear();
            sb.append("ALIVE\nDECLARATIONS\n");
            sb.sprintf("  %s %s\nSELECT TUPLE\n  %s %s\n%s(_,%s)\n",
                    entIt->first, entIt->second, entIt->first, entIt->second,
                    *relIt, entIt->second);
            out = sb.toString();
            CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        }
        // Parent(_,Int)
        sb.clear();
        sb.append("assign nd; Select nd such that ");
        sb.substitutef("%s(_,41)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign nd\nSELECT TUPLE\n");
        sb.append("  assign nd\n");
        sb.substitutef("%s(_,41)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Parent(_,_)
        sb.clear();
        sb.append("stmt ummf; Select ummf such that ");
        sb.substitutef("%s(_,_)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt ummf\nSELECT TUPLE\n"
                "  stmt ummf\n");
        sb.substitutef("%s(_,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Multiple clauses
        sb.clear();
        sb.append("stmt s1, s2; assign a1, a2; call c3; Select <s2, a1> ");
        sb.append("such that ");
        sb.substitutef("%s(s1,a1) and %s(c3, a2)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, true, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s1\n  stmt s2\n"
                "  assign a1\n");
        sb.append("  assign a2\n  call c3\nSELECT TUPLE\n  stmt s2\n");
        sb.append("  assign a1\n");
        sb.substitutef("%s(s1,a1)\n%s(c3,a2)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Repeated clauses
        sb.clear();
        sb.append("procedure p; stmt s1, s2, s3; assign a1, a2, a3;");
        sb.append("call c1, c2, c3; while w1, w2, w3; if i1, i2, i3;");
        sb.append("prog_line pl1, pl2, pl3; Select <s1, s1.stmt#, p, a1,");
        sb.append("a1.stmt#, a3, c1, c2.procName, w1, w1.stmt#, i1, i2, ");
        sb.append("i1.stmt#, pl1, pl3> such that ");
        // Follows(syn,syn)
        sb.substitutef(" %s(s1, s3) and %s(a1, s3) and %s(c1, s3) and ",
                *relIt);
        sb.substitutef(" %s(w1, s3) and %s(i1, s3) and %s(pl1, s3) and ",
                *relIt);
        sb.substitutef(" %s(s2, a3) and %s(s2, c2) and %s(s2, w3) and ",
                *relIt);
        sb.substitutef(" %s(s1, i2) and %s(s2, pl2) and ", *relIt);
        // Repeated Follows(Syn,Syn)
        sb.substitutef(" %s(s1, s3) and %s(a1, s3) and %s(c1, s3) and ",
                *relIt);
        sb.substitutef(" %s(w1, s3) and %s(i1, s3) and %s(pl1, s3) and ",
                *relIt);
        sb.substitutef(" %s(s2, a3) and %s(s2, c2) and %s(s2, w3) and ",
                *relIt);
        sb.substitutef(" %s(s1, i2) and %s(s2, pl2) and ", *relIt);
        // Follows(syn,Int), Follows(syn,_)
        sb.substitutef(" %s(s2,731) and %s(w1, _) and ", *relIt);
        // Repeated Follows(syn,Int), Follows(syn,_)
        sb.substitutef(" %s(s2,731) and %s(w1, _) and ", *relIt);
        // Follows(Int,*)
        sb.substitutef(" %s(11, c2) and %s(72, 1373) and %s(78375, _) and ",
                *relIt);
        // Repeated Follows(Int,*)
        sb.substitutef(" %s(11, c2) and %s(72, 1373) and %s(78375, _) and ",
                *relIt);
        // Follows(_,*)
        sb.substitutef(" %s(_,pl2) and %s(_,913114) and %s(_,_) and ",
                *relIt);
        // Repeated Follows(_,*)
        sb.substitutef(" %s(_,pl2) and %s(_,913114) and %s(_,_) ", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  procedure p\n  stmt s1\n"
                "  stmt s2\n");
        sb.append("  stmt s3\n  assign a1\n  assign a2\n  assign a3\n");
        sb.append("  call c1\n  call c2\n  call c3\n  while w1\n");
        sb.append("  while w2\n  while w3\n  if i1\n  if i2\n  if i3\n");
        sb.append("  prog_line pl1\n  prog_line pl2\n  prog_line pl3\n");
        sb.append("SELECT TUPLE\n  stmt s1\n  stmt s1 stmt#\n");
        sb.append("  procedure p\n  assign a1\n  assign a1 stmt#\n");
        sb.append("  assign a3\n  call c1\n  call c2 procName\n  while w1\n");
        sb.append("  while w1 stmt#\n  if i1\n  if i2\n  if i1 stmt#\n");
        sb.append("  prog_line pl1\n  prog_line pl3\n");
        sb.substitutef("%s(s1,s3)\n%s(a1,s3)\n%s(c1,s3)\n", *relIt);
        sb.substitutef("%s(w1,s3)\n%s(i1,s3)\n%s(pl1,s3)\n", *relIt);
        sb.substitutef("%s(s2,a3)\n%s(s2,c2)\n%s(s2,w3)\n", *relIt);
        sb.substitutef("%s(s1,i2)\n%s(s2,pl2)\n", *relIt);
        sb.substitutef("%s(s2,731)\n%s(w1,_)\n", *relIt);
        sb.substitutef("%s(11,c2)\n%s(72,1373)\n%s(78375,_)\n", *relIt);
        sb.substitutef("%s(_,pl2)\n%s(_,913114)\n%s(_,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    }
}

void Test_20_PQLParser::test_err_follows_and_star_argtypes()
{
    StringBuffer sb;
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    set<pair<const char *, const char **> > RS;
    RS.insert(pair<const char *, const char **>
                (FOLLOWS_STR, TYPE_ERROR_FOLLOWS));
    RS.insert(pair<const char *, const char **>
                (FOLLOWS_STAR_STR, TYPE_ERROR_FOLLOWS_STAR));

    // invalid arg one synonym types
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_PROC_STR, "p"));
    ESONE.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "sl"));
    ESONE.insert(pair<const char *, const char *>(ENT_VAR_STR, "v"));
    ESONE.insert(pair<const char *, const char *>(ENT_CONST_STR, "Cg"));
    // invalid arg two synonym types
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_PROC_STR, "b"));
    ESTWO.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "h"));
    ESTWO.insert(pair<const char *, const char *>(ENT_VAR_STR, "aasf"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CONST_STR, "qq"));
    for (set<pair<const char *, const char **> >::const_iterator
            relIt = RS.begin(); relIt != RS.end(); relIt++) {
        // Parent(syn,_)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(%s,_)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGONE_TYPE_ERROR_STR, relIt->second[0]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Parent("string",_)
        sb.clear();
        sb.append("while dd; Select dd such that ");
        sb.substitutef("%s(\"t32\",_)", relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
                relIt->first, "\"t32\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        // Parent(_,syn)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(_,%s)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGTWO_TYPE_ERROR_STR, relIt->second[1]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Parent(_,"string")
        sb.clear();
        sb.append(" constant ch; Select ch such that ");
        sb.substitutef("%s(_, \"bsf\")", relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
                relIt->first, "\"bsf\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }
}

void Test_20_PQLParser::test_next_and_star_and_bip()
{
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    QueryInfo *qinfo;

    set<const char *> RS;
    RS.insert(NEXT_STR);
    RS.insert(NEXT_STAR_STR);
    RS.insert(NEXTBIP_STR);
    RS.insert(NEXTBIP_STAR_STR);
    // ok arg one synonym types
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_STMT_STR, "st"));
    ESONE.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "a"));
    ESONE.insert(pair<const char *, const char *>(ENT_CALL_STR, "c"));
    ESONE.insert(pair<const char *, const char *>(ENT_WHILE_STR, "w"));
    ESONE.insert(pair<const char *, const char *>(ENT_IF_STR, "i"));
    ESONE.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "pl"));
    // ok arg two synonym types
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_STMT_STR, "b"));
    ESTWO.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "x"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CALL_STR, "sd"));
    ESTWO.insert(pair<const char *, const char *>(ENT_WHILE_STR, "q"));
    ESTWO.insert(pair<const char *, const char *>(ENT_IF_STR, "n"));
    ESTWO.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "j"));

    for (set<const char *>::const_iterator
            relIt = RS.begin(); relIt != RS.end(); relIt++) {
        // Arg one
        // Next(syn,prog_line)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.append("prog_line qnda; ");
            sb.sprintf("%s %s; Select %s such that %s(%s,qnda)",
                    entIt->first, entIt->second, entIt->second, *relIt,
                    entIt->second);
            queryStr = sb.toString();
            parser.parse(queryStr, false, false);
            qinfo = parser.get_queryinfo();
            CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
            sb.clear();
            sb.append("ALIVE\nDECLARATIONS\n  prog_line qnda\n");
            sb.sprintf("  %s %s\nSELECT TUPLE\n  %s %s\n%s(%s,qnda)\n",
                    entIt->first, entIt->second, entIt->first, entIt->second,
                    *relIt, entIt->second);
            out = sb.toString();
            CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        }
        // Next(Int,prog_line)
        sb.clear();
        sb.append("prog_line kmfgd; Select kmfgd such that ");
        sb.substitutef("%s(782, kmfgd)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line kmfgd\n"
                "SELECT TUPLE\n");
        sb.append("  prog_line kmfgd\n");
        sb.substitutef("%s(782,kmfgd)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Next(Int,prog_line), Int is negative
        sb.clear();
        sb.append("prog_line kmfgd; Select kmfgd such that ");
        sb.substitutef("%s(-5136, kmfgd)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line kmfgd\n"
                "SELECT TUPLE\n");
        sb.append("  prog_line kmfgd\n");
        sb.substitutef("%s(-5136,kmfgd)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Next(_,prog_line)
        sb.clear();
        sb.append("prog_line mb; Select mb such that ");
        sb.substitutef("%s(_,mb)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line mb\n"
                "SELECT TUPLE\n");
        sb.append("  prog_line mb\n");
        sb.substitutef("%s(_,mb)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Arg two
        // Next(prog_line,syn)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; prog_line ksndgb#; Select %s such that ",
                    entIt->first, entIt->second, entIt->second);
            sb.sprintf("%s(ksndgb#, %s)", *relIt, entIt->second);
            queryStr = sb.toString();
            parser.parse(queryStr, false, false);
            qinfo = parser.get_queryinfo();
            CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
            sb.clear();
            sb.append("ALIVE\nDECLARATIONS\n");
            sb.sprintf("  %s %s\n  prog_line ksndgb#\nSELECT TUPLE\n",
                    entIt->first, entIt->second);
            sb.sprintf("  %s %s\n%s(ksndgb#,%s)\n", entIt->first,
                    entIt->second, *relIt, entIt->second);
            out = sb.toString();
            CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        }
        // Next(prog_line,Int)
        sb.clear();
        sb.append("prog_line bs; Select bs such that ");
        sb.substitutef("%s(bs,1235)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line bs\nSELECT TUPLE\n");
        sb.append("  prog_line bs\n");
        sb.substitutef("%s(bs,1235)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Next(prog_line,_)
        sb.clear();
        sb.append("prog_line hsef; Select hsef such that ");
        sb.substitutef("%s(hsef,_)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line hsef\n"
                "SELECT TUPLE\n");
        sb.append("  prog_line hsef\n");
        sb.substitutef("%s(hsef,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Multiple Next
        sb.clear();
        sb.append("prog_line pl1, pl6; assign a1, a2; Select <a1,pl1> ");
        sb.append(" such that ");
        sb.substitutef(" %s(pl1,a1) and %s(a2,pl6)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  prog_line pl1\n"
                "  prog_line pl6\n");
        sb.append("  assign a1\n  assign a2\nSELECT TUPLE\n");
        sb.append("  assign a1\n  prog_line pl1\n");
        sb.substitutef("%s(pl1,a1)\n%s(a2,pl6)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Repeated Next
        sb.clear();
        sb.append(" procedure p1, p2, p3; stmtLst sl1, sl2, sl3; ");
        sb.append(" stmt s1, s2, s3; assign a1, a2, a3; call c1, c2, c3; ");
        sb.append(" while w1, w2, w3; if i1, i2, i3; variable v1, v2, v3; ");
        sb.append(" constant const1, const2, const3; ");
        sb.append(" prog_line pl1, pl2, pl3; ");
        sb.append(" Select <p1, sl1, s2, p2.procName, a1, a1.stmt#, c2, ");
        sb.append(" w1, w1.stmt#, w3, i1, v1, v2.varName, const1, pl3> ");
        sb.append(" such that ");
        // Next(syn,prog_line)
        sb.substitutef(" %s(s1,pl1) and %s(a1, pl1) and %s(c2, pl2) and ",
                *relIt);
        sb.substitutef(" %s(w1, pl1) and %s(i1, pl1) and %s(pl3, pl1) and ",
                *relIt);
        // Repeated Next(syn,prog_line)
        sb.substitutef(" %s(s1,pl1) and %s(a1, pl1) and %s(c2, pl2) and ",
                *relIt);
        sb.substitutef(" %s(w1, pl1) and %s(i1, pl1) and %s(pl3, pl1) and  ",
                *relIt);
        // Next(prog_line,syn)
        sb.substitutef(" %s(pl2, s3) and %s(pl2, a3) and %s(pl2, c2) and ",
                *relIt);
        sb.substitutef(" %s(pl2, w2) and %s(pl2, i3) and %s(pl2, pl3) and ",
                *relIt);
        // Repeated Next(prog_line,syn)
        sb.substitutef(" %s(pl2, s3) and %s(pl2, a3) and %s(pl2, c2) and ",
                *relIt);
        sb.substitutef(" %s(pl2, w2) and %s(pl2, i3) and %s(pl2, pl3) and ",
                *relIt);
        // Next(syn,Int), Next(syn,_)
        sb.substitutef(" %s(pl3,351) and %s(pl2,_) and ", *relIt);
        // Repeated Next(syn,Int), Next(syn,_)
        sb.substitutef(" %s(pl3,351) and %s(pl2,_) and ", *relIt);
        // Next(Int,*)
        sb.substitutef(" %s(25, a3) and %s(7, 62) and %s(3472,_) and ",
                *relIt);
        // Repeated Next(Int,*)
        sb.substitutef(" %s(25, a3) and %s(7, 62) and %s(3472,_) and ",
                *relIt);
        // Next(_,*)
        sb.substitutef(" %s(_,s2) and %s(_, 62171) and %s(_,_) and ", *relIt);
        // Repeated Next(_,*)
        sb.substitutef(" %s(_,s2) and %s(_, 62171) and %s(_,_) ", *relIt);

        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  procedure p1\n"
                "  procedure p2\n");
        sb.append("  procedure p3\n  stmtLst sl1\n  stmtLst sl2\n");
        sb.append("  stmtLst sl3\n  stmt s1\n  stmt s2\n  stmt s3\n");
        sb.append("  assign a1\n  assign a2\n  assign a3\n  call c1\n");
        sb.append("  call c2\n  call c3\n  while w1\n  while w2\n");
        sb.append("  while w3\n  if i1\n  if i2\n  if i3\n  variable v1\n");
        sb.append("  variable v2\n  variable v3\n  constant const1\n");
        sb.append("  constant const2\n  constant const3\n  prog_line pl1\n");
        sb.append("  prog_line pl2\n  prog_line pl3\nSELECT TUPLE\n");
        sb.append("  procedure p1\n  stmtLst sl1\n  stmt s2\n");
        sb.append("  procedure p2 procName\n  assign a1\n  assign a1 stmt#\n");
        sb.append("  call c2\n  while w1\n  while w1 stmt#\n  while w3\n");
        sb.append("  if i1\n  variable v1\n  variable v2 varName\n");
        sb.append("  constant const1\n  prog_line pl3\n");
        sb.substitutef("%s(s1,pl1)\n%s(a1,pl1)\n%s(c2,pl2)\n", *relIt);
        sb.substitutef("%s(w1,pl1)\n%s(i1,pl1)\n%s(pl3,pl1)\n", *relIt);
        sb.substitutef("%s(pl2,s3)\n%s(pl2,a3)\n%s(pl2,c2)\n", *relIt);
        sb.substitutef("%s(pl2,w2)\n%s(pl2,i3)\n%s(pl2,pl3)\n", *relIt);
        sb.substitutef("%s(pl3,351)\n%s(pl2,_)\n", *relIt);
        sb.substitutef("%s(25,a3)\n%s(7,62)\n%s(3472,_)\n", *relIt);
        sb.substitutef("%s(_,s2)\n%s(_,62171)\n%s(_,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    }
}

void Test_20_PQLParser::test_err_next_and_star_and_bip_argtypes()
{
    StringBuffer sb;
    string queryStr, out;
    PQLParser parser;
    ostringstream *os;

    set<pair<const char *, const char **> > RS;
    RS.insert(pair<const char *, const char **>
                (NEXT_STR, TYPE_ERROR_NEXT));
    RS.insert(pair<const char *, const char **>
                (NEXT_STAR_STR, TYPE_ERROR_NEXT_STAR));
    RS.insert(pair<const char *, const char **>
                (NEXTBIP_STR, TYPE_ERROR_NEXTBIP));
    RS.insert(pair<const char *, const char **>
                (NEXTBIP_STAR_STR, TYPE_ERROR_NEXTBIP_STAR));
    // invalid types for arg one
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_PROC_STR, "p"));
    ESONE.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "sl"));
    ESONE.insert(pair<const char *, const char *>(ENT_VAR_STR, "v"));
    ESONE.insert(pair<const char *, const char *>(ENT_CONST_STR, "co"));
    // invalid types for arg two
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_PROC_STR, "ba"));
    ESTWO.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "yw"));
    ESTWO.insert(pair<const char *, const char *>(ENT_VAR_STR, "y"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CONST_STR, "j"));

    for (set<pair<const char *, const char **> > ::const_iterator
            relIt = RS.begin(); relIt != RS.end(); relIt++) {
        // Arg one
        // Next(syn,_)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(%s,_)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGONE_TYPE_ERROR_STR, relIt->second[0]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Next("string",_)
        sb.clear();
        sb.substitutef("Select BOOLEAN such that %s(\"hah\",_)",
                relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
                relIt->first, "\"hah\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Arg two
        // Next(_,syn)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(_,%s)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGTWO_TYPE_ERROR_STR, relIt->second[1]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Next(_,"string")
        sb.clear();
        sb.substitutef("assign a; Select a such that %s(_, \"mn\")",
                relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
                relIt->first, "\"mn\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }
}

void Test_20_PQLParser::test_affects_and_star_and_bip()
{
    StringBuffer sb;
    string queryStr, out;
    QueryInfo *qinfo;
    PQLParser parser;

    set<const char *> RS;
    RS.insert(AFFECTS_STR);
    RS.insert(AFFECTS_STAR_STR);
    RS.insert(AFFECTSBIP_STR);
    RS.insert(AFFECTSBIP_STAR_STR);

    // valid types for arg one synonym
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "ab"));
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_ASSIGN_STR, "asdf"));

    for (set<const char *>::const_iterator relIt = RS.begin();
            relIt != RS.end(); relIt++) {
        // Arg One
        // Affects(syn,assign)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.append("assign t; ");
            sb.sprintf("%s %s; Select %s such that %s(%s,t)",
                    entIt->first, entIt->second, entIt->second, *relIt,
                    entIt->second);
            queryStr = sb.toString();
            parser.parse(queryStr, false, false);
            qinfo = parser.get_queryinfo();
            CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
            sb.clear();
            sb.append("ALIVE\nDECLARATIONS\n  assign t\n");
            sb.sprintf("  %s %s\nSELECT TUPLE\n  %s %s\n%s(%s,t)\n",
                    entIt->first, entIt->second, entIt->first, entIt->second,
                    *relIt, entIt->second);
            out = sb.toString();
            CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        }
        // Affects(Int,assign)
        sb.clear();
        sb.append(" assign bs; Select bs such that ");
        sb.substitutef(" %s(612, bs)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign bs\nSELECT TUPLE\n"
                "  assign bs\n");
        sb.substitutef("%s(612,bs)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Affects(Int,assign), Int is negative
        sb.clear();
        sb.append(" assign bs; Select bs such that ");
        sb.substitutef(" %s( -678056, bs)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign bs\nSELECT TUPLE\n"
                "  assign bs\n");
        sb.substitutef("%s(-678056,bs)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Affects(_,assign)
        sb.clear();
        sb.append(" assign bds; Select bds such that ");
        sb.substitutef(" %s(_, bds)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign bds\nSELECT TUPLE\n"
                "  assign bds\n");
        sb.substitutef("%s(_,bds)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Arg Two
        // Affects(_,Int)
        sb.clear();
        sb.substitutef("Select BOOLEAN such that %s(_, 735146)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\nSELECT BOOLEAN\n");
        sb.substitutef("%s(_,735146)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
        // Affects(_,_)
        sb.clear();
        sb.substitutef("stmt s; Select s such that %s(_,_)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmt s\nSELECT TUPLE\n"
                "  stmt s\n");
        sb.substitutef("%s(_,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Multiple Affects
        sb.clear();
        sb.append("assign a1, a2; Select <a1,a2.stmt#> such that ");
        sb.substitutef(" %s(a1,561) and %s(a2,a1)", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n"
                "SELECT TUPLE\n");
        sb.append("  assign a1\n  assign a2 stmt#\n");
        sb.substitutef("%s(a1,561)\n%s(a2,a1)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

        // Repeated Affects
        sb.clear();
        sb.append("stmtLst sl1, sl2, sl3; procedure p1, p2, p3; ");
        sb.append("stmt s1, s2, s3; call c1, c2, c3; assign a1, a2, a3; ");
        sb.append("if i1, i2, i3; while w1, w2, w3; variable v1, v2; ");
        sb.append("constant const1, const2; prog_line pl1, pl2, pl3; ");
        sb.append("Select <w1, w2.stmt#, a1, c1, p1.procName, p2, p1, s1, ");
        sb.append("a1.stmt#, a2, i1, v2, const2, pl3> such that ");
        // Affects(syn,syn)
        sb.substitutef(" %s(a1, a3) and ", *relIt);
        // Repeated Affects(syn,syn)
        sb.substitutef(" %s(a1,a3) and ", *relIt);
        // Affects(syn,Int), Affects(syn,_)
        sb.substitutef(" %s(a2, 641) and %s(a3, _)  and ", *relIt);
        // Repeated Affects(syn,Int), Affects(syn,_)
        sb.substitutef(" %s(a2, 641) and %s(a3, _) and ", *relIt);
        // Affects(Int,*)
        sb.substitutef(" %s(163, a2) and %s(672, 2) and %s(7411,_) and ",
                *relIt);
        // Repeated Affects(Int,*)
        sb.substitutef(" %s(163, a2) and %s(672, 2) and %s(7411,_) and ",
                *relIt);
        // Affects(_,*)
        sb.substitutef(" %s(_,a1) and %s(_,61357) and %s(_,_) and ", *relIt);
        // Repeated Affects(_,*)
        sb.substitutef(" %s(_,a1) and %s(_,61357) and %s(_,_) ", *relIt);
        queryStr = sb.toString();
        parser.parse(queryStr, false, false);
        qinfo = parser.get_queryinfo();
        CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
        sb.clear();
        sb.append("ALIVE\nDECLARATIONS\n  stmtLst sl1\n  stmtLst sl2\n");
        sb.append("  stmtLst sl3\n  procedure p1\n  procedure p2\n");
        sb.append("  procedure p3\n  stmt s1\n  stmt s2\n  stmt s3\n");
        sb.append("  call c1\n  call c2\n  call c3\n  assign a1\n");
        sb.append("  assign a2\n  assign a3\n  if i1\n  if i2\n  if i3\n");
        sb.append("  while w1\n  while w2\n  while w3\n  variable v1\n");
        sb.append("  variable v2\n  constant const1\n  constant const2\n");
        sb.append("  prog_line pl1\n  prog_line pl2\n  prog_line pl3\n");
        sb.append("SELECT TUPLE\n  while w1\n  while w2 stmt#\n  assign a1\n");
        sb.append("  call c1\n  procedure p1 procName\n  procedure p2\n");
        sb.append("  procedure p1\n  stmt s1\n  assign a1 stmt#\n");
        sb.append("  assign a2\n  if i1\n  variable v2\n  constant const2\n");
        sb.append("  prog_line pl3\n");
        sb.substitutef("%s(a1,a3)\n", *relIt);
        sb.substitutef("%s(a2,641)\n%s(a3,_)\n", *relIt);
        sb.substitutef("%s(163,a2)\n%s(672,2)\n%s(7411,_)\n", *relIt);
        sb.substitutef("%s(_,a1)\n%s(_,61357)\n%s(_,_)\n", *relIt);
        out = sb.toString();
        CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    }
}

void Test_20_PQLParser::test_err_affects_and_star_and_bip_argtypes()
{
    StringBuffer sb;
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    set<pair<const char *, const char **> > RS;
    RS.insert(pair<const char *, const char **>
                (AFFECTS_STR, TYPE_ERROR_AFFECTS));
    RS.insert(pair<const char *, const char **>
                (AFFECTS_STAR_STR, TYPE_ERROR_AFFECTS_STAR));
    RS.insert(pair<const char *, const char **>
                (AFFECTSBIP_STR, TYPE_ERROR_AFFECTSBIP));
    RS.insert(pair<const char *, const char **>
                (AFFECTSBIP_STAR_STR, TYPE_ERROR_AFFECTSBIP_STAR));

    // invalid types for arg one synonym
    set<pair<const char *, const char *> > ESONE;
    ESONE.insert(pair<const char *, const char *>(ENT_PROC_STR, "p"));
    ESONE.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "sl"));
    ESONE.insert(pair<const char *, const char *>(ENT_STMT_STR, "s"));
    ESONE.insert(pair<const char *, const char *>(ENT_CALL_STR, "c"));
    ESONE.insert(pair<const char *, const char *>(ENT_WHILE_STR, "w"));
    ESONE.insert(pair<const char *, const char *>(ENT_IF_STR, "i"));
    ESONE.insert(pair<const char *, const char *>(ENT_VAR_STR, "v"));
    ESONE.insert(pair<const char *, const char *>(ENT_CONST_STR, "co"));
    ESONE.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "pl"));

    // invalid types for arg two synonym
    set<pair<const char *, const char *> > ESTWO;
    ESTWO.insert(pair<const char *, const char *>(ENT_PROC_STR, "bsf"));
    ESTWO.insert(pair<const char *, const char *>(ENT_STMTLST_STR, "sq"));
    ESTWO.insert(pair<const char *, const char *>(ENT_STMT_STR, "bb"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CALL_STR, "ye"));
    ESTWO.insert(pair<const char *, const char *>(ENT_WHILE_STR, "y"));
    ESTWO.insert(pair<const char *, const char *>(ENT_IF_STR, "d"));
    ESTWO.insert(pair<const char *, const char *>(ENT_VAR_STR, "q"));
    ESTWO.insert(pair<const char *, const char *>(ENT_CONST_STR, "j"));
    ESTWO.insert(pair<const char *, const char *>(ENT_PROGLINE_STR, "rq"));

    for (set<pair<const char *, const char **> >::const_iterator
            relIt = RS.begin(); relIt != RS.end(); relIt++) {
        // Arg one
        // Affects(syn,_)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESONE.begin(); entIt != ESONE.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(%s,_)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGONE_TYPE_ERROR_STR, relIt->second[0]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Affects("string",_)
        sb.clear();
        sb.append(" stmt s; Select s such that ");
        sb.substitutef(" %s(\"bdfg\",_)", relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGONE, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGONE_STR,
                relIt->first, "\"bdfg\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

        // Arg two
        // Affects(_,syn)
        for (set<pair<const char *, const char *> >::const_iterator
                entIt = ESTWO.begin(); entIt != ESTWO.end(); entIt++) {
            sb.clear();
            sb.sprintf("%s %s; Select %s such that %s(_,%s)",
                    entIt->first, entIt->second, entIt->second,
                    relIt->first, entIt->second);
            queryStr = sb.toString();
            os = new ostringstream;
            parser.parse(os, queryStr, true, false);
            out = os->str();
            CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO_TYPE_ERROR,
                    parser.get_parse_result());
            _snprintf_s(this->buf, BUFLEN, BUFLEN,
                    PARSE_REL_ARGTWO_TYPE_ERROR_STR, relIt->second[1]);
            CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
        }
        // Affects(_,"string")
        sb.clear();
        sb.append(" call c; Select c such that ");
        sb.substitutef(" %s(_,\"ksfdga\")", relIt->first);
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARGTWO, parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARGTWO_STR,
                relIt->first, "\"ksfdga\"");
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }
}

void Test_20_PQLParser::test_pattern()
{
    StringBuffer sb;
    string queryStr, out;
    QueryInfo *qinfo;
    PQLParser parser;

    // pattern assign(var,_)
    queryStr = "assign a; variable v; ";
    queryStr += " Select a pattern a(v,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a\n  variable v\n"
            "SELECT TUPLE\n";
    out += "  assign a\nassign pattern a(v,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign(var,"expr")
    queryStr = "assign nbd; variable vdfa; ";
    queryStr += "Select vdfa pattern nbd(vdfa,\"2 *  5\")";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign nbd\n  variable vdfa\n";
    out += "SELECT TUPLE\n  variable vdfa\n";
    out += "assign pattern nbd(vdfa,\"2*5\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign(var,_"expr"_)
    queryStr = "assign kkq; variable hfh; ";
    queryStr += " Select kkq pattern kkq(hfh,_\"  6 + 5 * a \"_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign kkq\n  variable hfh\n";
    out += "SELECT TUPLE\n  assign kkq\n";
    out += "assign pattern kkq(hfh,_\"6+5*a\"_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign("string",_)
    queryStr = "  assign bfb; Select bfb pattern bfb(\"someVar\",_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign bfb\nSELECT TUPLE\n"
            "  assign bfb\n";
    out += "assign pattern bfb(\"someVar\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign("string","expr")
    queryStr = " assign ja; Select ja pattern ja(\"bvv\", \"  a + b - 3\")";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign ja\nSELECT TUPLE\n"
            "  assign ja\n";
    out += "assign pattern ja(\"bvv\",\"a+b-3\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign("string",_"expr"_)
    queryStr = " assign lkka; Select lkka pattern lkka(\"ca\", _\"v\"_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign lkka\nSELECT TUPLE\n"
            "  assign lkka\n";
    out += "assign pattern lkka(\"ca\",_\"v\"_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign(_,_)
    queryStr = " assign x; Select x pattern x(_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign x\nSELECT TUPLE\n  assign x\n";
    out += "assign pattern x(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign(_,"expr")
    queryStr = " assign g; Select g pattern g(_, \" 3 * aba + 4 - ca1g\")";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign g\nSELECT TUPLE\n  assign g\n";
    out += "assign pattern g(_,\"3*aba+4-ca1g\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern assign(_,_"expr"_)
    queryStr = "assign nna; Select nna pattern nna(_, _\"  df + 1 - 4 \"_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign nna\nSELECT TUPLE\n"
            "  assign nna\n";
    out += "assign pattern nna(_,_\"df+1-4\"_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces - pattern assign(var,_)
    queryStr = "assign qq; variable ngd; ";
    queryStr += " Select <qq,ngd> pattern qq  \t (  \t ngd  , _  \n )";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign qq\n  variable ngd\n"
            "SELECT TUPLE\n";
    out += "  assign qq\n  variable ngd\nassign pattern qq(ngd,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces - pattern assign(var, _"expr"_)
    queryStr = " assign nbs; variable qhgs#1; Select nbs ";
    queryStr += " pattern nbs  \n\t  \t ( \t \n qhgs#1   \n \t , ";
    queryStr += "  _\"    1251 + 51 * cba - hsf \"_  \n \t \n ) ";
    parser.parse(queryStr, true, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign nbs\n  variable qhgs#1\n"
            "SELECT TUPLE\n";
    out += "  assign nbs\nassign pattern nbs(qhgs#1,_\"1251+51*cba-hsf\"_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern if(var,_,_)
    queryStr = "if isdf; variable sa; Select isdf ";
    queryStr += " pattern isdf(sa,_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  if isdf\n  variable sa\n"
            "SELECT TUPLE\n";
    out += "  if isdf\nif pattern isdf(sa,_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern if("string",_,_)
    queryStr = " if bba; Select bba pattern bba(\"vv\",_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  if bba\nSELECT TUPLE\n  if bba\n";
    out += "if pattern bba(\"vv\",_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern if(_,_,_)
    queryStr = "  if ajaq; Select ajaq pattern ajaq(_,_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  if ajaq\nSELECT TUPLE\n  if ajaq\n";
    out += "if pattern ajaq(_,_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces - pattern if(var,_,_)
    queryStr = " variable bvbsa; if fvaf; Select <fvaf, bvbsa> ";
    queryStr += " pattern \n \t  fvaf  \n \t ( \t \n bvbsa \n \t , \t \n";
    queryStr += " _ \t\n , \t\n\t _ \n\t\n )\t\n  ";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  variable bvbsa\n  if fvaf\n"
            "SELECT TUPLE\n";
    out += "  if fvaf\n  variable bvbsa\n";
    out += "if pattern fvaf(bvbsa,_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern while(var,_)
    queryStr = " while aa ; variable ppq; Select aa ";
    queryStr += " pattern aa(ppq,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while aa\n  variable ppq\n"
            "SELECT TUPLE\n";
    out += "  while aa\nwhile pattern aa(ppq,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern while("string",_)
    queryStr = " while bba; Select bba pattern bba(\"nafg\",_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while bba\nSELECT TUPLE\n"
            "  while bba\n";
    out += "while pattern bba(\"nafg\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // pattern while(_,_)
    queryStr = " while ghaq; Select ghaq pattern ghaq(_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while ghaq\nSELECT TUPLE\n"
            "  while ghaq\n";
    out += "while pattern ghaq(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces - while("string",_)
    queryStr = " while basdfa; Select BOOLEAN pattern basdfa  \n \t ";
    queryStr += "  ( \n\t \"avar\"\n\t  \n , \t \n _ \t\t\t\n  ) ";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  while basdfa\nSELECT BOOLEAN\n";
    out += "while pattern basdfa(\"avar\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Multiple pattern
    queryStr = " assign aadf; while wgn2#; if iisdfa; ";
    queryStr += " variable vbba, v3y, vj1; ";
    queryStr += " Select <aadf, vbba, wgn2#, iisdfa> ";
    queryStr += " pattern aadf(vbba, _\"63 - sfv * 721\"_) and ";
    queryStr += "  wgn2#(v3y, _) and iisdfa(vj1,_,_)";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign aadf\n  while wgn2#\n"
            "  if iisdfa\n";
    out += "  variable vbba\n  variable v3y\n  variable vj1\nSELECT TUPLE\n";
    out += "  assign aadf\n  variable vbba\n  while wgn2#\n  if iisdfa\n";
    out += "assign pattern aadf(vbba,_\"63-sfv*721\"_)\n";
    out += "while pattern wgn2#(v3y,_)\nif pattern iisdfa(vj1,_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Repeated pattern
    queryStr = " assign a1, a2, a3; while w1, w2, w3; if i1, i2, i3; ";
    queryStr += " procedure p1, p2, p3; stmtLst sl1, sl2, sl3; ";
    queryStr += " stmt s1, s2, s3; call c1, c2, c3; variable v1, v2, v3; ";
    queryStr += " constant const1, const2, const3; prog_line pl1, pl2, pl3;";
    queryStr += " variable v4, v5, v6; ";
    queryStr += " Select <a1.stmt#, a2, a1, w1.stmt#, w2, i1.stmt#, p1, ";
    queryStr += " p1.procName, p2, sl1, s1, s2.stmt#, c2, v1, v2.varName, ";
    queryStr += " const1, const2.value, pl1, v5.varName> ";
    // Pattern assign(var,*)
    queryStr += " pattern a1(v1,_) and ";
    queryStr += " a2(v3, \" 2 * y72 - 625\") and ";
    queryStr += " a3 ( v6 , _\" 761 * sd + nasaA - 832  \"_) and ";
    // Repeated Pattern assign(var,*)
    queryStr += " a1(v1,_) and ";
    queryStr += " a2(v3, \" 2 * y72 - 625\") and ";
    queryStr += " a3(v6, _\" 761 * sd + nasaA - 832 \"_) and ";
    // Pattern assign("string",*)
    queryStr += " a2(\"ret\", _) and a3( \"val\", \"yu + mva - 252\") and ";
    queryStr += " a1(\"toSwitch\", _\" s + aba - 123 - ffa * 1\"_) and ";
    // Repeated Pattern assign("string",*)
    queryStr += " a2(\"ret\", _) and a3( \"val\", \"yu + mva - 252\") and ";
    queryStr += " a1(\"toSwitch\", _\" s + aba - 123 - ffa * 1\"_) and ";
    // Pattern assign(_,*)
    queryStr += " a3( _, _ ) and a2(_,\"62 - 15 * nah\") and ";
    queryStr += " a1(_, _\"hh + a1yh - Ba1 * 61 + 576\"_) and ";
    // Repeated Pattern assign(_,*)
    queryStr += " a3( _, _ ) and a2(_,\"62 - 15 * nah\") and ";
    queryStr += " a1(_, _\"hh + a1yh - Ba1 * 61 + 576\"_) and ";
    // Pattern if(*,_,_)
    queryStr += " i1(v2, _, _) and  i2 ( \"con\" , _, _ ) and ";
    queryStr += " i3 (_, _, _) and ";
    // Repeated Pattern if(*,_,_)
    queryStr += " i1(v2, _, _) and  i2 ( \"con\" , _, _ ) and ";
    queryStr += " i3 (_, _, _)  and ";
    // Pattern while(*,_)
    queryStr += " w1(v6, _ ) and w3 ( \"one\", _) and w3 (_, _) and ";
    // Repeated Pattern while(*,_)
    queryStr += " w1(v6, _ ) and w3 ( \"one\", _) and w3 (_, _)  ";
    parser.parse(queryStr, false, false);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "ALIVE\nDECLARATIONS\n  assign a1\n  assign a2\n  assign a3\n";
    out += "  while w1\n  while w2\n  while w3\n  if i1\n  if i2\n";
    out += "  if i3\n  procedure p1\n  procedure p2\n  procedure p3\n";
    out += "  stmtLst sl1\n  stmtLst sl2\n  stmtLst sl3\n  stmt s1\n";
    out += "  stmt s2\n  stmt s3\n  call c1\n  call c2\n  call c3\n";
    out += "  variable v1\n  variable v2\n  variable v3\n";
    out += "  constant const1\n  constant const2\n  constant const3\n";
    out += "  prog_line pl1\n  prog_line pl2\n  prog_line pl3\n";
    out += "  variable v4\n  variable v5\n  variable v6\n";
    out += "SELECT TUPLE\n  assign a1 stmt#\n  assign a2\n  assign a1\n";
    out += "  while w1 stmt#\n  while w2\n  if i1 stmt#\n  procedure p1\n";
    out += "  procedure p1 procName\n  procedure p2\n  stmtLst sl1\n";
    out += "  stmt s1\n  stmt s2 stmt#\n  call c2\n  variable v1\n";
    out += "  variable v2 varName\n  constant const1\n";
    out += "  constant const2 value\n  prog_line pl1\n";
    out += "  variable v5 varName\n";
    out += "assign pattern a1(v1,_)\n";
    out += "assign pattern a2(v3,\"2*y72-625\")\n";
    out += "assign pattern a3(v6,_\"761*sd+nasaA-832\"_)\n";
    out += "assign pattern a2(\"ret\",_)\n";
    out += "assign pattern a3(\"val\",\"yu+mva-252\")\n";
    out += "assign pattern a1(\"toSwitch\",_\"s+aba-123-ffa*1\"_)\n";
    out += "assign pattern a3(_,_)\nassign pattern a2(_,\"62-15*nah\")\n";
    out += "assign pattern a1(_,_\"hh+a1yh-Ba1*61+576\"_)\n";
    out += "if pattern i1(v2,_,_)\nif pattern i2(\"con\",_,_)\n";
    out += "if pattern i3(_,_,_)\n";
    out += "while pattern w1(v6,_)\nwhile pattern w3(\"one\",_)\n";
    out += "while pattern w3(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}

void Test_20_PQLParser::test_err_patcl_varref_invalid()
{
    string queryStr;
    string out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign a1g; Select a1g pattern a1g(  \t 61213, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_INVALID_STR,
            "61213");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // spaces after varRef
    queryStr = " assign a661; Select a661 ";
    queryStr += " pattern a661(6Agb15 \t\n, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_INVALID_STR,
            "6Agb15");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " if iba; Select iba pattern iba(72, _,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_INVALID_STR,
            "72");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " if buaq; Select buaq pattern buaq ( ^jmsdf$6 \t , _ , _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_INVALID_STR,
            "^jmsdf$6");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " while w; Select w pattern w( 7341 , _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_INVALID_STR,
            "7341");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_varref_undeclared()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign a; Select a pattern a(v1,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_UNDECLARED_STR,
            "v1");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " while w2; Select w2 pattern w2( naf,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_UNDECLARED_STR,
            "naf");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " if i15; Select i15 pattern i15( gfa5,_,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_UNDECLARED_STR,
            "gfa5");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_varref_notvar()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign a1, v1; Select a1 pattern a1(v1,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_NOTVAR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_NOTVAR_STR,
            "v1", entity_type_to_string(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " if idb; constant c1; Select c1 pattern idb( c1,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_NOTVAR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_NOTVAR_STR,
            "c1", entity_type_to_string(ENT_CONST));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " while w3; stmt conVar; Select w3 pattern w3(conVar,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_VARREF_NOTVAR,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_VARREF_NOTVAR_STR,
            "conVar", entity_type_to_string(ENT_STMT));
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_argone_nocomma()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = "assign a; variable va; Select a pattern a(va$1,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "a(va");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "assign ba; Select ba pattern ba( \"hasf\"#15,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "ba(\"hasf\"");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "assign yw; Select yw pattern yw(_adh,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "yw(_");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "if ida1; variable hh; Select ida1 pattern ida1(hh  674,_,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "ida1(hh");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "if hs; Select hs pattern hs( \"gaq56\"  731,_,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "hs(\"gaq56\"");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " if uwa; Select uwa pattern uwa(_bnba,_,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "uwa(_");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "while w; variable c; Select w pattern w(c$1,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "w(c");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "while rh; Select rh pattern rh(\"aag\"  !63,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "rh(\"aag\"");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "while oga; Select oga pattern oga(_ mg3,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ARGONE_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_ARGONE_NOCOMMA_STR,
            "oga(_");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_assign_expr_nodquote()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign ba1; Select ba1 pattern ba1(_, \"3 *  5)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ASSIGN_EXPR_NODQUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_ASSIGN_EXPR_NODQUOTE_STR,
            "ba1(_,\"3 *  5)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "  assign khka; Select khka pattern khka(_, _\"a + b -3  )";
    queryStr += "  pattern khka(_, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ASSIGN_EXPR_NODQUOTE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_ASSIGN_EXPR_NODQUOTE_STR,
            "khka(_,_\"a + b -3  )  pattern khka(_, _)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_assign_expr_wildcard_no_underscore()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = "assign alpha; Select alpha ";
    queryStr += " pattern alpha(_, _\"ha + 62  * ta \"  )";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE_STR,
            "alpha(_,_\"ha + 62  * ta \"");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_assign_expr_invalid()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign bua; Select bua ";
    queryStr += " pattern bua(_, invalidExpr)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ASSIGN_EXPR_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_ASSIGN_EXPR_INVALID_STR,
            "bua(_,", "invalidExpr");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = " assign ewaasg; variable nvba; Select ewaasg ";
    queryStr += " pattern ewaasg(  nvba  ,  #1415 )";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_ASSIGN_EXPR_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_ASSIGN_EXPR_INVALID_STR,
            "ewaasg(nvba,", "#1415");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_if_argtwo_not_underscore()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // no space after 'adf'
    queryStr = " if iisa; Select iisa ";
    queryStr += " pattern  iisa(  \"var\" \t, adf, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE_STR,
            "iisa(\"var\",", "adf");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // spaces after nonsense
    queryStr = " if abba; Select abba ";
    queryStr += " pattern  abba(  _ \t, nonsense \t , _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE_STR,
            "abba(_,", "nonsense");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_if_argtwo_nocomma()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " if kda; Select kda pattern ";
    queryStr += " kda(_,_asdf,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_IF_ARGTWO_NOCOMMA,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_IF_ARGTWO_NOCOMMA_STR,
            "kda(_,_");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_if_argthree_not_underscore()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // no spaces after 'varaf'
    queryStr = " if kaQ; Select kaQ pattern ";
    queryStr += " kaQ(_,_, varaf)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE_STR,
            "kaQ(_,_,", "varaf");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // spaces after '#y211'
    queryStr = " if nnQ2   ; Select nnQ2 pattern ";
    queryStr += " nnQ2( \"hasd\" ,_, \t #y211 \t \n )";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE_STR,
            "nnQ2(\"hasd\",_,", "#y211");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_while_argtwo_not_underscore()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // no spaces after 'adasdf'
    queryStr = " while w1g; Select w1g pattern ";
    queryStr += " w1g(_, adasdf)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE_STR,
            "w1g(_,", "adasdf");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // spaces after '^1gva'
    queryStr = " while vvba; Select vvba pattern ";
    queryStr += " vvba( \"baff\" ,  ^1gva  \t \n )";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN,
            PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE_STR,
            "vvba(\"baff\",", "^1gva");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_norparen()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // pattern assign
    queryStr = " assign as; variable var; Select as pattern ";
    queryStr += " as(var,_\"a + b\"_  ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_NORPAREN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_NORPAREN_STR,
            "pattern as(var,_\"a+b\"_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // pattern if
    queryStr = " if ita; Select ita pattern ";
    queryStr += " ita( \"vba\" ,_ ,_ sdfg ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_NORPAREN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_NORPAREN_STR,
            "pattern ita(\"vba\",_,_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // pattern while
    queryStr = "  while wenb; variable ba; Select wenb pattern ";
    queryStr += " wenb( ba ,_  y35af ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_NORPAREN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_NORPAREN_STR,
            "pattern wenb(ba,_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcond_and_nosep()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign a; while w; Select <a,w> pattern ";
    queryStr += " a(_,_) and#41 pattern(w,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCOND_AND_NOSEP,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCOND_AND_NOSEP_STR,
            "#41");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_syn_undeclared()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign a; variable v; Select a pattern a(v,_) and ";
    queryStr += " a2ba(_,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_SYN_UNDECLARED,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_SYN_UNDECLARED_STR,
            "a2ba");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_nolparen()
{
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    queryStr = " assign bn,fs; Select bn pattern bn(_,_) and ";
    queryStr += " fs ^^yha";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_NOLPAREN, parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCL_NOLPAREN_STR, "fs");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void Test_20_PQLParser::test_err_patcl_syn_type_error()
{
    StringBuffer sb;
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // synonym is not while, if, assign
    set<const char *> S;
    S.insert(ENT_PROC_STR);
    S.insert(ENT_STMTLST_STR);
    S.insert(ENT_STMT_STR);
    S.insert(ENT_CALL_STR);
    S.insert(ENT_VAR_STR);
    S.insert(ENT_CONST_STR);
    S.insert(ENT_PROGLINE_STR);
    for (set<const char *>::const_iterator it = S.begin();
            it != S.end(); it++) {
        sb.clear();
        sb.sprintf(" while ww; %s someSyn; Select ww pattern ww(_,_) and ",
                *it);
        sb.append(" someSyn(_,_)");
        queryStr = sb.toString();
        os = new ostringstream;
        parser.parse(os, queryStr, true, false);
        out = os->str();
        CPPUNIT_ASSERT_EQUAL(PARSE_PATCL_SYN_TYPE_ERROR,
                parser.get_parse_result());
        _snprintf_s(this->buf, BUFLEN, BUFLEN,
                PARSE_PATCL_SYN_TYPE_ERROR_STR, "someSyn", *it);
        CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
    }
}

void Test_20_PQLParser::test_err_patcond_invalid_patcl()
{
    StringBuffer sb;
    string queryStr, out;
    ostringstream *os;
    PQLParser parser;

    // not synonym
    queryStr = " assign a; Select a pattern a(_,_) and ";
    queryStr += " #51(_ ,_)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCOND_INVALID_PATCL,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCOND_INVALID_PATCL_STR,
            "#51(_ ,_)", "pattern a(_,_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    // not synonym, no rparen
    queryStr = " assign bab; Select bab pattern bab(_,_) and ";
    queryStr += "   bab(\"cca\" , _)  and 661  ";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_PATCOND_INVALID_PATCL,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_PATCOND_INVALID_PATCL_STR,
            "661  ", "pattern bab(\"cca\",_)");
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}