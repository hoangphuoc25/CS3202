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
    CPPUNIT_ASSERT_EQUAL(string(NEXTBIP_STR),
            string(relRefType_to_string(REL_NEXTBIP)));
    CPPUNIT_ASSERT_EQUAL(string(NEXTBIP_STAR_STR),
            string(relRefType_to_string(REL_NEXTBIP_STAR)));
    CPPUNIT_ASSERT_EQUAL(string(AFFECTSBIP_STR),
            string(relRefType_to_string(REL_AFFECTSBIP)));
    CPPUNIT_ASSERT_EQUAL(string(AFFECTSBIP_STAR_STR),
            string(relRefType_to_string(REL_AFFECTSBIP_STAR)));
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
    CPPUNIT_ASSERT_EQUAL(BASETYPE_INT,
            refSynType_to_BaseType(REFSYN_PROGLINE_PROGLINE_NO));
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
    // assign.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_ASSIGN,
            attrRef_to_RefSynType(attrRef));
    // invalid: assign without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, assign.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // call.stmt#
    attrRef.entType = ENT_CALL;
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CALL,
            attrRef_to_RefSynType(attrRef));
    // call.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CALL_PROCNAME,
            attrRef_to_RefSynType(attrRef));
    // invalid: call without any attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, call.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // if.stmt#
    attrRef.entType = ENT_IF;
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_IF,
            attrRef_to_RefSynType(attrRef));
    // invalid: if without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, if.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // while.stmt#
    attrRef.entType = ENT_WHILE;
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_WHILE,
            attrRef_to_RefSynType(attrRef));
    // invalid: while without attrname
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, while.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // stmt.stmt#
    attrRef.entType = ENT_STMT;
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMT,
            attrRef_to_RefSynType(attrRef));
    // invalid: stmt without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
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
    // prog_line.prog_line#
    attrRef.attr = ATTR_PROGLINE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROGLINE_PROGLINE_NO,
            attrRef_to_RefSynType(attrRef));
    // invalid, assign.varName
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // stmtLst.stmt#
    attrRef.entType = ENT_STMTLST;
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_STMTLST,
            attrRef_to_RefSynType(attrRef));
    // invalid: stmtLst without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, stmtLst.procName
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // const.value
    attrRef.entType = ENT_CONST;
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_CONST,
            attrRef_to_RefSynType(attrRef));
    // invalid: const without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, const.stmt#
    attrRef.attr = ATTR_STMTNO;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // proc.procName
    attrRef.entType = ENT_PROC;
    attrRef.attr = ATTR_PROCNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_PROC,
            attrRef_to_RefSynType(attrRef));
    // invalid: procedure without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // invalid, procedure.value
    attrRef.attr = ATTR_VALUE;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
            attrRef_to_RefSynType(attrRef));
    // var.varName
    attrRef.entType = ENT_VAR;
    attrRef.attr = ATTR_VARNAME;
    CPPUNIT_ASSERT_EQUAL(REFSYN_VAR,
            attrRef_to_RefSynType(attrRef));
    // invalid: variable without attrName
    attrRef.attr = ATTR_DEFAULT;
    CPPUNIT_ASSERT_EQUAL(REFSYN_INVALID,
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

void Test_03_PQL::test_withClause_normalize()
{
    using std::swap;
    WithClause withCl;

    // concrete arguments do not get swapped
    withCl.leftRef.refType = REF_INT;
    withCl.leftRef.refIntVal = 367;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 1;
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("367 = 1"), withCl.toString());
    withCl.leftRef.refType = REF_STRING;
    withCl.leftRef.refStringVal = "zvg";
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("\"zvg\" = 1"), withCl.toString());
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "ab";
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("\"zvg\" = \"ab\""), withCl.toString());

    // 1 synonym, 1 concrete argument
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "a";
    withCl.leftRef.refSynType = REFSYN_ASSIGN;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 35;
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("a.stmt# = 35"), withCl.toString());
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("35 = a.stmt#"), withCl.toString());
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("a.stmt# = 35"), withCl.toString());
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "jax";
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("a.stmt# = \"jax\""), withCl.toString());
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("\"jax\" = a.stmt#"), withCl.toString());
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("a.stmt# = \"jax\""), withCl.toString());

    // 2 synonym of different type
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "hja";
    withCl.leftRef.refSynType = REFSYN_STMT;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "bad";
    withCl.rightRef.refSynType = REFSYN_VAR;
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("hja.stmt# = bad.varName"),
            withCl.toString());
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("bad.varName = hja.stmt#"),
            withCl.toString());
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("hja.stmt# = bad.varName"),
            withCl.toString());
    // 2 synonym of same type
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "joke";
    withCl.leftRef.refSynType = REFSYN_WHILE;
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "maker";
    withCl.rightRef.refSynType = REFSYN_WHILE;
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("joke.stmt# = maker.stmt#"),
            withCl.toString());
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("maker.stmt# = joke.stmt#"),
            withCl.toString());
    withCl.normalize();
    CPPUNIT_ASSERT_EQUAL(string("joke.stmt# = maker.stmt#"),
            withCl.toString());
}

void Test_03_PQL::test_withClause_is_contradiction()
{
    using std::swap;
    WithClause withCl;
    // type mismatch (int,string) and hence contradiction
    withCl.leftRef.refType = REF_INT;
    withCl.leftRef.refIntVal = 35;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "abc";
    CPPUNIT_ASSERT_EQUAL(string("35 = \"abc\""), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // type mismatch (string,int) and hence contradiction
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("\"abc\" = 35"), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // same type (string,string) but different value, contradiction
    withCl.leftRef.refType = REF_STRING;
    withCl.leftRef.refStringVal = "zack";
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "dan";
    CPPUNIT_ASSERT_EQUAL(string("\"zack\" = \"dan\""),
            withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // same type (string,string) and same value, no contradiction
    withCl.rightRef.refStringVal = "zack";
    CPPUNIT_ASSERT_EQUAL(string("\"zack\" = \"zack\""),
            withCl.toString());
    CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
    // same type (int,int) but different value, contradiction
    withCl.leftRef.refType = REF_INT;
    withCl.leftRef.refIntVal = 756;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 3288;
    CPPUNIT_ASSERT_EQUAL(string("756 = 3288"), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // same type (int,int) and same value, no contradiction
    withCl.rightRef.refIntVal = 756;
    CPPUNIT_ASSERT_EQUAL(string("756 = 756"), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
    // different type (string syn, int), hence contradiction
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "agh";
    withCl.leftRef.refSynType = REFSYN_PROC;
    withCl.rightRef.refType = REF_INT;
    withCl.rightRef.refIntVal = 32;
    CPPUNIT_ASSERT_EQUAL(string("agh.procName = 32"), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // different type (int, string syn), hence contradiction
    swap(withCl.leftRef, withCl.rightRef);
    CPPUNIT_ASSERT_EQUAL(string("32 = agh.procName"), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // same type (string syn, string), no contradiction
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "yodawg";
    withCl.leftRef.refSynType = REFSYN_CALL_PROCNAME;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "who";
    CPPUNIT_ASSERT_EQUAL(string("yodawg.procName = \"who\""),
            withCl.toString());
    CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
    // same type (string, string syn), no contradiction
    swap(withCl.leftRef, withCl.rightRef);
    withCl.rightRef.refStringVal = "vvv";
    withCl.rightRef.refSynType = REFSYN_VAR;
    CPPUNIT_ASSERT_EQUAL(string("\"who\" = vvv.varName"),
            withCl.toString());
    CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
    // different type (int syn, string), hence contradiction
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "nn";
    withCl.leftRef.refSynType = REFSYN_PROGLINE;
    withCl.rightRef.refType = REF_STRING;
    withCl.rightRef.refStringVal = "bob";
    CPPUNIT_ASSERT_EQUAL(string("nn = \"bob\""), withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // different type (string, int syn), hence contradiction
    withCl.leftRef.refType = REF_STRING;
    withCl.leftRef.refStringVal = "haha";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "bonfire";
    withCl.rightRef.refSynType = REFSYN_WHILE;
    CPPUNIT_ASSERT_EQUAL(string("\"haha\" = bonfire.stmt#"),
            withCl.toString());
    CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
    // 2 ref of same RefSynType, no contradiction
    set<RefSynType> intRefs;
    intRefs.insert(REFSYN_STMTLST); intRefs.insert(REFSYN_STMT);
    intRefs.insert(REFSYN_ASSIGN); intRefs.insert(REFSYN_CALL);
    intRefs.insert(REFSYN_WHILE); intRefs.insert(REFSYN_IF);
    intRefs.insert(REFSYN_CONST); intRefs.insert(REFSYN_PROGLINE);
    intRefs.insert(REFSYN_PROGLINE_PROGLINE_NO);
    set<RefSynType> stringRefs;
    stringRefs.insert(REFSYN_PROC);
    stringRefs.insert(REFSYN_CALL_PROCNAME);
    stringRefs.insert(REFSYN_VAR);
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "refOne";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "refTwo";
    for (set<RefSynType>::const_iterator it = intRefs.begin();
            it != intRefs.end(); it++) {
        RefSynType refSynType = *it;
        withCl.leftRef.refSynType = refSynType;
        withCl.rightRef.refSynType = refSynType;
        CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
    }

    // 2 different RefSynType, one string, one int, contradiction
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "refOne";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "refTwo";
    for (set<RefSynType>::const_iterator intRefIt = intRefs.begin();
            intRefIt != intRefs.end(); intRefIt++) {
        withCl.leftRef.refSynType = *intRefIt;
        for (set<RefSynType>::const_iterator stringRefIt =
                stringRefs.begin(); stringRefIt != stringRefs.end();
                stringRefIt++) {
            withCl.rightRef.refSynType = *stringRefIt;
            CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
        }
    }
    for (set<RefSynType>::const_iterator stringRefIt =
                stringRefs.begin(); stringRefIt != stringRefs.end();
                stringRefIt++) {
        withCl.leftRef.refSynType = *stringRefIt;
        for (set<RefSynType>::const_iterator intRefIt = intRefs.begin();
            intRefIt != intRefs.end(); intRefIt++) {
            withCl.rightRef.refSynType = *intRefIt;
            CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
        }
    }

    // 2 different int RefSynType, but left ref is one of
    // stmt, prog_line, prog_line.prog_line#, const.value, stmtLst.stmt#
    // so no contradiction
    set<RefSynType> okRefSynSet;
    okRefSynSet.insert(REFSYN_STMT); okRefSynSet.insert(REFSYN_PROGLINE);
    okRefSynSet.insert(REFSYN_PROGLINE_PROGLINE_NO);
    okRefSynSet.insert(REFSYN_CONST); okRefSynSet.insert(REFSYN_STMTLST);
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "refOne";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "refTwo";
    for (set<RefSynType>::const_iterator okIt = okRefSynSet.begin();
            okIt != okRefSynSet.end(); okIt++) {
        withCl.leftRef.refSynType = *okIt;
        for (set<RefSynType>::const_iterator intRefIt = intRefs.begin();
                intRefIt != intRefs.end(); intRefIt++) {
            withCl.rightRef.refSynType = *intRefIt;
            CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
        }
    }
    // 2 different int RefSynType, but right ref is one of
    // stmt, prog_line, prog_line.prog_line#, const.value, stmtLst.stmt#
    // so no contradiction
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "refOne";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "refTwo";
    for (set<RefSynType>::const_iterator intRefIt = intRefs.begin();
                intRefIt != intRefs.end(); intRefIt++) {
        withCl.leftRef.refSynType = *intRefIt;
        for (set<RefSynType>::const_iterator okIt = okRefSynSet.begin();
            okIt != okRefSynSet.end(); okIt++) {
            withCl.rightRef.refSynType = *okIt;
            CPPUNIT_ASSERT_EQUAL(false, withCl.is_contradiction());
        }
    }


    // 2 different int RefSynType, and none of them is
    // stmt, prog_line, prog_line.prog_line#, const.value, stmtLst.stmt#
    // hence contradiction
    set<RefSynType> notOkIntRefs;
    notOkIntRefs.insert(REFSYN_ASSIGN); notOkIntRefs.insert(REFSYN_CALL);
    notOkIntRefs.insert(REFSYN_WHILE); notOkIntRefs.insert(REFSYN_IF);
    withCl.leftRef.refType = REF_ATTRREF;
    withCl.leftRef.refStringVal = "refOne";
    withCl.rightRef.refType = REF_ATTRREF;
    withCl.rightRef.refStringVal = "refTwo";
    for (set<RefSynType>::const_iterator it = notOkIntRefs.begin();
            it != notOkIntRefs.end(); it++) {
        withCl.leftRef.refSynType = *it;
        for (set<RefSynType>::const_iterator kt = notOkIntRefs.begin();
                kt != notOkIntRefs.end(); kt++) {
            if (*it != *kt) {
                withCl.rightRef.refSynType = *kt;
                CPPUNIT_ASSERT_EQUAL(true, withCl.is_contradiction());
            }
        }
    }
}