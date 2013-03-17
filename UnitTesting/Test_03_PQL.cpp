#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include "Test_03_PQL.h"
#include "../SPA/PQLParser.h"

using std::string;
using std::map;
using std::ostringstream;
using std::set;
using std::pair;

void Test_03_PQL::setUp() {}

void Test_03_PQL::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_03_PQL);

void Test_03_PQL::test_relRefType_to_string()
{
    CPPUNIT_ASSERT_EQUAL(string(MODIFIES_STR),
            string(relRefType_to_string(REL_MODIFIES)));
    CPPUNIT_ASSERT_EQUAL(string(USES_STR),
            string(relRefType_to_string(REL_USES)));
    CPPUNIT_ASSERT_EQUAL(string(CALLS_STR),
            string(relRefType_to_string(REL_CALLS)));
    CPPUNIT_ASSERT_EQUAL(string(CALLS_STAR_STR),
            string(relRefType_to_string(REL_CALLS_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(PARENT_STR),
            string(relRefType_to_string(REL_PARENT)));
    CPPUNIT_ASSERT_EQUAL(string(PARENT_STAR_STR),
            string(relRefType_to_string(REL_PARENT_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(FOLLOWS_STR),
            string(relRefType_to_string(REL_FOLLOWS)));
    CPPUNIT_ASSERT_EQUAL(string(FOLLOWS_STAR_STR),
            string(relRefType_to_string(REL_FOLLOWS_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(NEXT_STR),
            string(relRefType_to_string(REL_NEXT)));
    CPPUNIT_ASSERT_EQUAL(string(NEXT_STAR_STR),
            string(relRefType_to_string(REL_NEXT_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(AFFECTS_STR),
            string(relRefType_to_string(REL_AFFECTS)));
    CPPUNIT_ASSERT_EQUAL(string(AFFECTS_STAR_STR),
            string(relRefType_to_string(REL_AFFECTS_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(INVALID_STR),
            string(relRefType_to_string(REL_INVALID)));
}

void Test_03_PQL::test_entity_type_to_string()
{
    CPPUNIT_ASSERT_EQUAL(string(ENT_PROC_STR),
            string(entity_type_to_string(ENT_PROC)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_STMTLST_STR),
            string(entity_type_to_string(ENT_STMTLST)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_STMT_STR),
            string(entity_type_to_string(ENT_STMT)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_ASSIGN_STR),
            string(entity_type_to_string(ENT_ASSIGN)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_CALL_STR),
            string(entity_type_to_string(ENT_CALL)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_WHILE_STR),
            string(entity_type_to_string(ENT_WHILE)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_IF_STR),
            string(entity_type_to_string(ENT_IF)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_VAR_STR),
            string(entity_type_to_string(ENT_VAR)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_CONST_STR),
            string(entity_type_to_string(ENT_CONST)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_PROGLINE_STR),
            string(entity_type_to_string(ENT_PROGLINE)));
    CPPUNIT_ASSERT_EQUAL(string(ENT_INVALID_STR),
            string(entity_type_to_string(ENT_INVALID)));
}

void Test_03_PQL::test_attrType_to_string()
{
    CPPUNIT_ASSERT_EQUAL(string(ATTR_PROCNAME_STR),
            string(attrType_to_string(ATTR_PROCNAME)));
    CPPUNIT_ASSERT_EQUAL(string(ATTR_VARNAME_STR),
            string(attrType_to_string(ATTR_VARNAME)));
    CPPUNIT_ASSERT_EQUAL(string(ATTR_VALUE_STR),
            string(attrType_to_string(ATTR_VALUE)));
    CPPUNIT_ASSERT_EQUAL(string(ATTR_STMTNO_STR),
            string(attrType_to_string(ATTR_STMTNO)));
    CPPUNIT_ASSERT_EQUAL(string(ATTR_DEFAULT_STR),
            string(attrType_to_string(ATTR_DEFAULT)));
    CPPUNIT_ASSERT_EQUAL(string(ATTR_INVALID_STR),
            string(attrType_to_string(ATTR_INVALID)));
}

void Test_03_PQL::test_designEnt_to_relRefArgType()
{
    CPPUNIT_ASSERT_EQUAL(RELARG_STRING,
                designEnt_to_relRefArgType(ENT_PROC));
    CPPUNIT_ASSERT_EQUAL(RELARG_STRING,
                designEnt_to_relRefArgType(ENT_VAR));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_STMTLST));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_STMT));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_CALL));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_WHILE));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_IF));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_CONST));
    CPPUNIT_ASSERT_EQUAL(RELARG_INT,
                designEnt_to_relRefArgType(ENT_PROGLINE));
    CPPUNIT_ASSERT_EQUAL(RELARG_INVALID,
                designEnt_to_relRefArgType(ENT_INVALID));
}

void Test_03_PQL::test_refSynType_to_BaseType()
{
    CPPUNIT_ASSERT_EQUAL(BASETYPE_STRING,
            refSynType_to_BaseType(REFSYN_PROC));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_STRING,
            refSynType_to_BaseType(REFSYN_CALL_PROCNAME));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_STRING,
            refSynType_to_BaseType(REFSYN_VAR));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_STMTLST));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_STMT));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_CALL));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_WHILE));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_IF));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_CONST));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_PROGLINE));
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INVALID,
            refSynType_to_BaseType(REFSYN_INVALID));
}

void Test_03_PQL::test_baseType_to_string()
{
    CPPUNIT_ASSERT_EQUAL(string(BASETYPE_STRING_STR),
            string(baseType_to_string(BASETYPE_STRING)));
    CPPUNIT_ASSERT_EQUAL(string(BASETYPE_INT_STR),
            string(baseType_to_string(BASETYPE_INT)));
    CPPUNIT_ASSERT_EQUAL(string(INVALID_STR),
            string(baseType_to_string(BASETYPE_INVALID)));
}

void Test_03_PQL::test_attrRef_to_RefSynType()
{
    AttrRef attrRef;
    attrRef.syn = "asyn";
    attrRef.entType = ENT_ASSIGN;
    attrRef.attr = ATTR_DEFAULT;
    // assign
    CPPUNIT_ASSERT_EQUAL(REFSYN_ASSIGN,
            attrRef_to_RefSynType(attrRef));
    // assign.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_ASSIGN,
            attrRef_to_RefSynType(attrRef));
    // invalid, assign.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // call
    attrRef.entType = ENT_CALL;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CALL,
            attrRef_to_RefSynType(attrRef));
    // call.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CALL,
            attrRef_to_RefSynType(attrRef));
    // call.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CALL_PROCNAME,
            attrRef_to_RefSynType(attrRef));
    // invalid, call.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // if
    attrRef.entType = ENT_IF;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_IF,
            attrRef_to_RefSynType(attrRef));
    // if.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_IF,
            attrRef_to_RefSynType(attrRef));
    // invalid, if.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // while
    attrRef.entType = ENT_WHILE;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_WHILE,
            attrRef_to_RefSynType(attrRef));
    // while.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_WHILE,
            attrRef_to_RefSynType(attrRef));
    // invalid, while.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // stmt
    attrRef.entType = ENT_STMT;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMT,
            attrRef_to_RefSynType(attrRef));
    // stmt.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMT,
            attrRef_to_RefSynType(attrRef));
    // invalid, stmt.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // prog_line
    attrRef.entType = ENT_PROGLINE;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROGLINE,
            attrRef_to_RefSynType(attrRef));
    // prog_line.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROGLINE,
            attrRef_to_RefSynType(attrRef));
    // invalid, assign.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // stmtLst
    attrRef.entType = ENT_STMTLST;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMTLST,
            attrRef_to_RefSynType(attrRef));
    // stmtLst.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMTLST,
            attrRef_to_RefSynType(attrRef));
    // invalid, stmtLst.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // const
    attrRef.entType = ENT_CONST;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CONST,
            attrRef_to_RefSynType(attrRef));
    // const.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CONST,
            attrRef_to_RefSynType(attrRef));
    // invalid, const.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // proc
    attrRef.entType = ENT_PROC;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROC,
            attrRef_to_RefSynType(attrRef));
    // proc.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROC,
            attrRef_to_RefSynType(attrRef));
    // invalid, assign.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // var
    attrRef.entType = ENT_VAR;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_VAR,
            attrRef_to_RefSynType(attrRef));
    // var.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_VAR,
            attrRef_to_RefSynType(attrRef));
    // invalid, var.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // ent invalid
    attrRef.entType = ENT_INVALID;
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
}