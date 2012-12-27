#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include "TestPQLParser.h"
#include "../SPA/PQLParser.h"

using std::string;
using std::map;
using std::ostringstream;

void TestPQLParser::setUp()
{
    this->buf = new char[TestPQLParser::BUFLEN+5];
}

void TestPQLParser::tearDown()
{
    delete[] this->buf;
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestPQLParser);

void TestPQLParser::test_one_decl_one()
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
    s = "DECLARATIONS\n  assign al3t\nSELECT TUPLE\n  assign al3t\n";
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
    s = "DECLARATIONS\n  procedure bnvb#\nSELECT TUPLE\n  procedure bnvb#\n";
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
    s = "DECLARATIONS\n  stmtLst H1bvg\nSELECT TUPLE\n  stmtLst H1bvg\n";
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
    s = "DECLARATIONS\n  stmt s7772a\nSELECT TUPLE\n  stmt s7772a\n";
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
    s = "DECLARATIONS\n  call Gbcv1\nSELECT TUPLE\n  call Gbcv1\n";
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
    s = "DECLARATIONS\n  while KMB2vx\nSELECT TUPLE\n  while KMB2vx\n";
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
    s = "DECLARATIONS\n  if u\nSELECT TUPLE\n  if u\n";
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
    s = "DECLARATIONS\n  variable x\nSELECT TUPLE\n  variable x\n";
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
    s = "DECLARATIONS\n  constant c2\nSELECT TUPLE\n  constant c2\n";
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
    s = "DECLARATIONS\n  prog_line plbc\nSELECT TUPLE\n  prog_line plbc\n";
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
    s = "DECLARATIONS\n  assign nbnesdf1#bvsAA\nSELECT TUPLE\n";
    s += "  assign nbnesdf1#bvsAA\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void TestPQLParser::test_one_decl()
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
    s = "DECLARATIONS\n  assign afC\n  assign bca\n  assign ncvb1\n";
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
    s = "DECLARATIONS\n  procedure pl123\n  procedure ABsx1\n";
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
    s = "DECLARATIONS\n  stmtLst bhvx1\n  stmtLst CVS1\n  stmtLst MBMcb1\n";
    s += "  stmtLst HH123\n  stmtLst YFS1cvx\n";
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
    s = "DECLARATIONS\n  stmt a\n  stmt b\n  stmt f#1sdc\n";
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
    s = "DECLARATIONS\n  call gbd1\n  call ccAS123\n";
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
    s = "DECLARATIONS\n  while W123v\n  while qfdf1t5\n  while bv11bv\n";
    s += "  while x\n  while nbnx1\nSELECT TUPLE\n  while bv11bv\n";
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
    s = "DECLARATIONS\n  if nmb1\n  if xgcx1\nSELECT TUPLE\n  if xgcx1\n";
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
    s = "DECLARATIONS\n  variable Bb1\n  variable cvx1\n";
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
    s = "DECLARATIONS\n  constant Cb#zsd1\n  constant Jvd11a\n";
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
    s = "DECLARATIONS\n  prog_line a01tT1z\n  prog_line bcv1\n  prog_line x\n";
    s += "  prog_line B\n  prog_line cx1\n  prog_line X\n  prog_line z\n";
    s += "SELECT TUPLE\n  prog_line B\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void TestPQLParser::test_mult_decl()
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
    CPPUNIT_ASSERT(30, (int)entTable.size());
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

    s = "DECLARATIONS\n  assign Ccxx1\n  assign bd1\n  procedure pl123\n";
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

void TestPQLParser::test_select_bool()
{
    string queryStr = "assign bb1; prog_line X1g; Select BOOLEAN";
    PQLParser parser;
    string s;
    QueryInfo *qinfo;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    s = "DECLARATIONS\n  assign bb1\n  prog_line X1g\nSELECT BOOLEAN\n";
    CPPUNIT_ASSERT_EQUAL(s, qinfo->dump_to_string());
}

void TestPQLParser::test_select_tuple()
{
    string queryStr = "assign bcv1; prog_line bvcb1, GS1; ";
    queryStr += "stmt SS123;  Select <bcv1, GS1>";
    PQLParser parser;
    QueryInfo *qinfo;
    string output;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  assign bcv1\n  prog_line bvcb1\n";
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
    output = "DECLARATIONS\n  stmtLst QQwe1\n  stmtLst hg1\n  prog_line x\n";
    output += "  prog_line bv13hs#1\n  call vvbx1\n  while X\n";
    output += "  variable VBCV1\n  variable KJj12\n  constant bnbn\n";
    output += "  assign BBVB123jh\n  variable thd15\n";
    output += "SELECT TUPLE\n  variable VBCV1\n  prog_line x\n";
    output += "  constant bnbn\n  while X\n  stmtLst QQwe1\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());
}

void TestPQLParser::test_select_attrRef()
{
    string queryStr = "procedure p1; Select p1.procName";
    PQLParser parser;
    QueryInfo *qinfo;
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    string output;
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  procedure p1\nSELECT TUPLE\n";
    output += "  procedure p1 procName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "assign a12; Select a12.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  assign a12\nSELECT TUPLE\n  assign a12 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "stmtLst sl43#; Select sl43#.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  stmtLst sl43#\n";
    output += "SELECT TUPLE\n  stmtLst sl43# stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "stmt gbv#c; Select gbv#c.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  stmt gbv#c\n";
    output += "SELECT TUPLE\n  stmt gbv#c stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "call nba1; Select nba1.procName";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  call nba1\n";
    output += "SELECT TUPLE\n  call nba1 procName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "call Tnbvc1; Select Tnbvc1.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  call Tnbvc1\n";
    output += "SELECT TUPLE\n  call Tnbvc1 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "while pklf9; Select pklf9.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  while pklf9\n";
    output += "SELECT TUPLE\n  while pklf9 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "if HHbvc1; Select HHbvc1.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  if HHbvc1\n";
    output += "SELECT TUPLE\n  if HHbvc1 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "variable uvdg#; Select uvdg#.varName";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  variable uvdg#\n";
    output += "SELECT TUPLE\n  variable uvdg# varName\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "constant dfb1; Select dfb1.value";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  constant dfb1\n";
    output += "SELECT TUPLE\n  constant dfb1 value\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "prog_line pofd1; Select pofd1.stmt#";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  prog_line pofd1\n";
    output += "SELECT TUPLE\n  prog_line pofd1 stmt#\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());

    queryStr = "procedure proc1, proc2; stmtLst ST1, ST2;";
    queryStr += " stmt s1, s2, s3; ";
    queryStr += "assign a1, a2, a3; call c1, c2, c3; while w1, w2, w3; ";
    queryStr += "if i1, i2, i3; variable v1, v2, v3;";
    queryStr += "constant const1, const2, const3; prog_line pl1, pl2, pl3;";
    queryStr += " Select <ST1, ST2.stmt#, s1.stmt#, s1, ST2, a1.stmt#, c2, ";
    queryStr += " c3.procName, w1.stmt#, w1, w3, i1, i3.stmt#, v1, ";
    queryStr += " v1.varName, const1, const1.value, pl2.stmt#, pl2, pl3 >";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    output = "DECLARATIONS\n  procedure proc1\n  procedure proc2\n";
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
    output += "  constant const1 value\n  prog_line pl2 stmt#\n";
    output += "  prog_line pl2\n  prog_line pl3\n";
    CPPUNIT_ASSERT_EQUAL(output, qinfo->dump_to_string());
}

void TestPQLParser::test_modifies()
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
    out = "DECLARATIONS\n  assign ad\n  variable vhd\nSELECT TUPLE\n";
    out += "  assign ad\nModifies(ad,vhd)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // spaces
    queryStr = "assign fh1; variable gdfg1, hgf1udA; ";
    queryStr += " Select hgf1udA such that ";
    queryStr += "  \n Modifies (\t\n  fh1  , \t gdfg1 \t)  ";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  assign fh1\n  variable gdfg1\n  variable hgf1udA\n";
    out += "SELECT TUPLE\n  variable hgf1udA\nModifies(fh1,gdfg1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(proc,var)
    queryStr = "procedure plf1; variable gbdg1; ";
    queryStr += "Select plf1 such that Modifies(plf1, gbdg1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  procedure plf1\n  variable gbdg1\n";
    out += "SELECT TUPLE\n  procedure plf1\nModifies(plf1,gbdg1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(if,var)
    queryStr = "variable mmvd1; if nfI1g; Select nfI1g such that ";
    queryStr += "Modifies(nfI1g, mmvd1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable mmvd1\n  if nfI1g\nSELECT TUPLE\n";
    out += "  if nfI1g\nModifies(nfI1g,mmvd1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(while,var)
    queryStr = " while bcv1; variable TQWEx1; Select TQWEx1 such that ";
    queryStr += "Modifies(bcv1, TQWEx1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  while bcv1\n  variable TQWEx1\nSELECT TUPLE\n";
    out += "  variable TQWEx1\nModifies(bcv1,TQWEx1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(call,var)
    queryStr = "  variable qecxv1#; call Kmmbc1; Select Kmmbc1 such that ";
    queryStr += "Modifies(Kmmbc1, qecxv1#)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable qecxv1#\n  call Kmmbc1\nSELECT TUPLE\n";
    out += "  call Kmmbc1\nModifies(Kmmbc1,qecxv1#)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(stmt,var)
    queryStr = "  stmt Iuvc1; variable lljgbf1; Select Iuvc1 such that ";
    queryStr += "Modifies(Iuvc1, lljgbf1)\n";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  stmt Iuvc1\n  variable lljgbf1\nSELECT TUPLE\n";
    out += "  stmt Iuvc1\nModifies(Iuvc1,lljgbf1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(prog_line,var)
    queryStr = " variable hjf1#xa; prog_line poiote; Select poiote ";
    queryStr += "such that Modifies(poiote, hjf1#xa )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable hjf1#xa\n  prog_line poiote\n";
    out += "SELECT TUPLE\n  prog_line poiote\nModifies(poiote,hjf1#xa)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(synonym,string)
    queryStr = "  stmt fvb1; Select fvb1 such that  ";
    queryStr += " Modifies  (  \t fvb1,  \"abvxc\"  \n \t)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  stmt fvb1\nSELECT TUPLE\n  stmt fvb1\n";
    out += "Modifies(fvb1,\"abvxc\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(synonym,_)
    queryStr = "  while df1; stmt BBx1;  Select <df1,BBx1> ";
    queryStr += " such that Modifies(df1,   \t  _  \t ) \n";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  while df1\n  stmt BBx1\n";
    out += "SELECT TUPLE\n  while df1\n  stmt BBx1\nModifies(df1,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,var)
    queryStr = " variable hcb, m2df1; Select m2df1 such that  ";
    queryStr += "Modifies(5, m2df1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable hcb\n  variable m2df1\nSELECT TUPLE\n";
    out += "  variable m2df1\nModifies(5,m2df1)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,string)
    queryStr = "  variable BLEh; Select BLEh such that Modifies(13,  \"Ex1\")";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable BLEh\nSELECT TUPLE\n  variable BLEh\n";
    out += "Modifies(13,\"Ex1\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(int,_)
    queryStr = " Select BOOLEAN such that Modifies(235, _)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\nSELECT BOOLEAN\nModifies(235,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,var)
    queryStr = " variable utq; Select utq such that ";
    queryStr += "   Modifies  \t (  \t \"proc1\"  \t ,utq)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable utq\nSELECT TUPLE\n  variable utq\n";
    out += "Modifies(\"proc1\",utq)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,string)
    queryStr = " while xfgvb1; Select xfgvb1 such that ";
    queryStr += "Modifies  (  \"fvProc\" \t , \t \n \"bcb14\"  \t \n)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  while xfgvb1\nSELECT TUPLE\n  while xfgvb1\n";
    out += "Modifies(\"fvProc\",\"bcb14\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(string,_)
    queryStr = " stmtLst sf; Select sf such that Modifies(\"qbcvb1\",_)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  stmtLst sf\nSELECT TUPLE\n  stmtLst sf\n";
    out += "Modifies(\"qbcvb1\",_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,var)
    queryStr = "  variable gvbcvb; Select gvbcvb such that  ";
    queryStr += "Modifies(_,gvbcvb)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable gvbcvb\nSELECT TUPLE\n  variable gvbcvb\n";
    out += "Modifies(_,gvbcvb)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,string)
    queryStr = " assign a; Select a such that Modifies(_,  \"bmcvkb\" )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  assign a\nSELECT TUPLE\n  assign a\n";
    out += "Modifies(_,\"bmcvkb\")\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(_,_)
    queryStr = "  variable sdfv1; Select sdfv1 such that Modifies(  _  , _ )";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  variable sdfv1\nSELECT TUPLE\n  variable sdfv1\n";
    out += "Modifies(_,_)\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());

    // Modifies(assign,var) and Modifies(proc,var)
    queryStr = "assign Asd1; variable bv1; procedure eh1ty; ";
    queryStr += "Select bv1 such that Modifies(Asd1,bv1) and Modifies(eh1ty,bv1)";
    parser.parse(queryStr);
    qinfo = parser.get_queryinfo();
    CPPUNIT_ASSERT_EQUAL(PARSE_OK, parser.get_parse_result());
    out = "DECLARATIONS\n  assign Asd1\n  variable bv1\n  procedure eh1ty\n";
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
    out = "DECLARATIONS\n  variable nfbg1\n  while dxfg1\n  if bv1hda\n";
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
    out = "DECLARATIONS\n  while w1\n  while w2\n  assign a1\n  assign a2\n";
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

void TestPQLParser::test_err_parse_decl_empty_syn()
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

void TestPQLParser::test_err_parse_decl_repeated_syn()
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

void TestPQLParser::test_err_parse_decl_invalid_syn()
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

void TestPQLParser::test_err_parse_decl_ent_syn_invalid_sep()
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

void TestPQLParser::test_err_parse_decl_no_terminator()
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

void TestPQLParser::test_err_parse_no_select_after_decl()
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

void TestPQLParser::test_err_select_undeclared()
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

void TestPQLParser::test_err_select_undef_attrname()
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

void TestPQLParser::test_err_select_undeclared_attrRef()
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

void TestPQLParser::test_err_select_attrRef_syn_attrName_type_error()
{
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
}

void TestPQLParser::test_err_select_invalid_attrRef()
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

void TestPQLParser::test_err_select_tuple_no_close()
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

void TestPQLParser::test_err_select_nothing()
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

void TestPQLParser::test_err_rel_argone()
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

void TestPQLParser::test_err_rel_no_comma()
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

void TestPQLParser::test_err_rel_argtwo()
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

void TestPQLParser::test_err_rel_arg_int_invalid()
{
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
            S_TO_UINT_TOO_LONG);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);

    queryStr = "stmt s; Select s such that Modifies(3234567890, _)";
    os = new ostringstream;
    parser.parse(os, queryStr, true, false);
    out = os->str();
    CPPUNIT_ASSERT_EQUAL(PARSE_REL_ARG_INT_INVALID,
            parser.get_parse_result());
    _snprintf_s(this->buf, BUFLEN, BUFLEN, PARSE_REL_ARG_INT_INVALID_STR,
            relRefType_to_string(REL_MODIFIES), "one", "3234567890",
            S_TO_UINT_OVERFLOW);
    CPPUNIT_ASSERT_EQUAL(string(this->buf), out);
}

void TestPQLParser::test_err_rel_argone_undeclared()
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

void TestPQLParser::test_err_rel_argone_type_error()
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

void TestPQLParser::test_err_rel_argtwo_undeclared()
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