#ifndef T11_PQL_H
#define T11_PQL_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "StringBuffer.h"

#define INVALID_STR "invalid"

#define ENT_PROC_STR     "procedure"
#define ENT_STMTLST_STR  "stmtLst"
#define ENT_STMT_STR     "stmt"
#define ENT_ASSIGN_STR   "assign"
#define ENT_CALL_STR     "call"
#define ENT_WHILE_STR    "while"
#define ENT_IF_STR       "if"
#define ENT_VAR_STR      "variable"
#define ENT_CONST_STR    "constant"
#define ENT_PROGLINE_STR "prog_line"
#define ENT_INVALID_STR  "invalid"

#define BOOLEAN_STR "BOOLEAN"
#define WITH_STR    "with"
#define PATTERN_STR "pattern"
#define AND_STR     "and"
#define SELECT_STR  "Select"
#define SUCH_STR    "such"
#define THAT_STR    "that"
#define INVALID_STR "invalid"
#define MODIFIES_STR     "Modifies"
#define USES_STR         "Uses"
#define CALLS_STAR_STR   "Calls*"
#define CALLS_STR        "Calls"
#define PARENT_STR       "Parent"
#define PARENT_STAR_STR  "Parent*"
#define FOLLOWS_STR      "Follows"
#define FOLLOWS_STAR_STR "Follows*"
#define NEXT_STR         "Next"
#define NEXT_STAR_STR    "Next*"
#define AFFECTS_STR      "Affects"
#define AFFECTS_STAR_STR "Affects*"

#define ATTR_PROCNAME_STR "procName"
#define ATTR_VARNAME_STR  "varName"
#define ATTR_VALUE_STR    "value"
#define ATTR_STMTNO_STR   "stmt#"
#define ATTR_PROGLINE_STR "prog_line#"
#define ATTR_DEFAULT_STR  "default"
#define ATTR_INVALID_STR  "invalid"

#define BASETYPE_INT_STR    "int"
#define BASETYPE_STRING_STR "string"

// arg: synonym type
#define PARSE_DECL_EMPTY_SYN_STR \
    "Missing synonym of type \"%s\""
// args: synonym, new type, previous type
#define PARSE_DECL_REPEATED_SYN_STR \
    "synonym \"%s\" of type \"%s\" was previously declared as \"%s\""
// arg: PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_DECL_INVALID_SYN_STR \
    "Expected synonym, got \"%s\""
// arg: PQLParser::eat_while<is_space>(sb) --> sb.c_str()
#define PARSE_DECL_ENT_SYN_INVALID_SEP_STR \
    "Expected whitespace between design entity and synonym, got \"%s\""
// arg: entity type
#define PARSE_DECL_NO_TERMINATOR_STR \
    "Missing terminator ';' for entity type \"%s\""
// arg: StringBuffer contents
#define PARSE_NO_SELECT_AFTER_DECL_STR \
    "Expected \"Select\", got \"%s\""
// arg: undeclared synonym
#define PARSE_SELECT_UNDECLARED_STR \
    "Selecting undeclared entity \"%s\""
#define PARSE_SELECT_INVALID_ATTRREF_STR \
    "Select: invalid attrRef \"%s\""
#define PARSE_SELECT_TUPLE_NO_CLOSE_STR \
    "Missing '>' for Select tuple"
// arg: eat_while<not_comma_space>(sb) ---> sb.c_str()
#define PARSE_SELECT_NOTHING_STR \
    "Select clause: Expected tuple or BOOLEAN, got \"%s\""
// args: attrName, synonym
#define PARSE_ATTRREF_UNDEF_ATTRNAME_STR \
    "AttrRef: undefined attrName \"%s\" for synonym \"%s\""
// args: synonym, attrRef.c_str(false)
#define PARSE_ATTRREF_UNDECLARED_STR \
    "Select: undefined synonym \"%s\" for attrRef \"%s\""
// args: attrRef.toPeriodString().c_str(), attrName, design entity
#define PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR \
    "AttrRef \"%s\": attrName \"%s\" is not defined for synonyms of type %s"
// args: relRef string rep, relRef arg one
#define PARSE_REL_ARGONE_STR \
    "%s: invalid arg one \"%s\""
// args: relRef string rep, relRef arg two
#define PARSE_REL_ARGTWO_STR \
    "%s: invalid arg two \"%s\""
// args: relRef string rep, "one" / "two", synonym name, other error msg
#define PARSE_REL_ARG_INT_INVALID_STR \
    "%s: Invalid integer arg %s \"%s\" [%s]"
// args: relRef string rep, synonym
#define PARSE_REL_ARGONE_UNDECLARED_STR \
    "%s: arg one is an undeclared synonym \"%s\""
// arg: generated error string
#define PARSE_REL_ARGONE_TYPE_ERROR_STR "%s"
// args: relRef string rep, synonym
#define PARSE_REL_ARGTWO_UNDECLARED_STR \
     "%s: arg two is an undeclared synonym \"%s\""
// arg: generated error string
#define PARSE_REL_ARGTWO_TYPE_ERROR_STR "%s"
// arg: relRef string rep
#define PARSE_REL_NO_COMMA_STR "%s: Expected comma between arguments"
// args: relRef string rep, relRef.dump()
#define PARSE_REL_NO_RPAREN_STR \
    "%s: Expected ')' [%s]"
// arg: relRef.dump().c_str()
#define PARSE_RELCOND_AND_NOSEP_STR \
    "relCond: expect whitespace after \"and\" [after %s]"
// args: PQLParser::eat_while<not_rparen>(sb) --> sb.c_str(),
//       prevRelRef.dump().c_str()
#define PARSE_RELCOND_INVALID_RELREF_STR \
    "Expected RelRef, got \"%s\" [after %s]"
// arg: PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_PATCL_VARREF_INVALID_STR \
    "patCl: expected varRef, got \"%s\""
// arg: varRef
#define PARSE_PATCL_VARREF_UNDECLARED_STR \
    "patCl: undeclared varRef \"%s\""
// args: varRef, relRefType_to_string(someType)
#define PARSE_PATCL_VARREF_NOTVAR_STR \
    "patCl: varRef \"%s\" is not of type variable [type \"%s\"]"
// arg: patcl string so far
#define PARSE_PATCL_ARGONE_NOCOMMA_STR \
    "patCl: expected comma after \"%s\""
// arg: patcl string so far
#define PARSE_PATCL_ASSIGN_EXPR_NODQUOTE_STR \
    "assign pattern: missing double quote for %s"
// arg: patcl string so far
#define PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE_STR \
    "assign pattern: missing underscore after %s"
// args: patcl string so far,
//       PQLParser::eat_while<not_rparen>(sb) --> sb.c_str()
#define PARSE_PATCL_ASSIGN_EXPR_INVALID_STR \
    "assign pattern: expected expr after %s ; got \"%s\""
// args: patcl string so far,
//       PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE_STR \
    "if pattern: expected underscore after %s ; got \"%s\""
// arg: patcl string so far
#define PARSE_PATCL_IF_ARGTWO_NOCOMMA_STR \
    "if pattern: expected comma after %s"
// args: patcl string so far,
//       PQLParser::eat_while<not_rparen_space>(sb) --> sb.c_str()
#define PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE_STR \
    "if pattern: expected underscore after %s ; got \"%s\""
// args: patcl string so far,
//       PQLParser::eat_while<not_rparen_space>(sb) --> sb.c_str()
#define PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE_STR \
    "while pattern: expected underscore after %s ; got \"%s\""
// arg: patcl.toString().c_str()
#define PARSE_PATCL_NORPAREN_STR \
    "patCl: Missing rparen for \"%s\""
// arg: syn
#define PARSE_PATCL_SYN_UNDECLARED_STR \
    "patCl: undeclared synonym \"%s\""
// arg: syn
#define PARSE_PATCL_NOLPAREN_STR \
    "patCl: Missing lparen for \"%s\""
// args: syn, entity_type_to_string(syn)
#define PARSE_PATCL_SYN_TYPE_ERROR_STR \
    "patCl: synonym \"%s\" is of type \"%s\", valid types: assign, while, if"
// arg: PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_PATCOND_AND_NOSEP_STR \
    "patCond: expect whitespace after \"and\" [got %s]"
// args: PQLParser::eat_while<not_rparen>(sb) --> sb.c_str(),
//       prevPatCl.toString().c_str()
#define PARSE_PATCOND_INVALID_PATCL_STR \
    "Expected patCl, got \"%s\" [after %s]"
#define PARSE_QINFO_INSERT_INVALID_RELREF_STR \
    "QueryInfo::add_relRef - Trying to insert invalid relRef"
// arg: sb.c_str()
#define PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR \
    "Ref in WithClause: undefined synonym \"%s\""
// args: synName.c_str(), entity_type_to_string(entType)
#define PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR \
    "Ref in WithClause: synonym \"%s\" of type \"%s\" " \
    "has no attrName, only prog_line can have no attrName"
// arg: withClause.toString()
#define PARSE_WITHCLAUSE_REFS_INVALID_STR \
    "WithClause: Invalid Ref in ' %s '"
// args: withClause, left ref BaseType, rightRef BaseType
#define PARSE_WITHCLAUSE_TYPE_MISMATCH_STR \
    "WithClause: type mismatch for %s [%s vs. %s]"
// arg: PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_WITHCLAUSE_AND_NOSEP_STR \
    "WithClause: expect whitespace after \"and\" [got %s]"
// args: left_side_ref.toString().c_str(),
//       PQLParser::eat_while<not_space>(sb) --> sb.c_str()
#define PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS_STR \
    "WithClause: expect ref on right hand side of \"%s = \", " \
    "got \"%s\""
// args: PQLParser::eat_till_end(sb) --> sb._str(),
//       prevWithClause.toString().c_str()
#define PARSE_WITHCLAUSE_EXPECT_WITH_STR \
    "WithClause: expect with after 'and', got \"%s\" [after %s]"
// args: integer string, errorMsg
#define PARSE_REF_INTEGER_ERROR_STR \
    "Ref: integer conversion error for \"%s\" [%s]"
// arg: sb.c_str()
#define PARSE_REF_ATTRREF_ERROR_STR \
    "Ref: expected AttrRef, got \"%s\""
// arg: PQLParser::eat_while<not_dquote>(sb) --> sb.c_str()
#define PARSE_DQUOTED_IDENT_INVALID_STR \
    "Quoted identifier: expected identifier string, got \"%s\""
// arg: sb.c_str()
#define PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR \
    "Quoted identifier: expect close quote for \"%s\""
// arg: StringBuffer contents
#define PARSE_END_OF_QUERY_ERROR_STR \
    "Expected end of query, got \"%s\""
#define PARSE_UNKNOWN_STR "Unknown error"
// type error stuff
#define TYPE_ERROR_ARRAY_SZ 2

extern const char *TYPE_ERROR_EMPTY[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_MODIFIES[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_USES[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_CALLS[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_CALLS_STAR[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_PARENT[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_PARENT_STAR[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_FOLLOWS[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_FOLLOWS_STAR[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_NEXT[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_NEXT_STAR[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_AFFECTS[TYPE_ERROR_ARRAY_SZ];
extern const char *TYPE_ERROR_AFFECTS_STAR[TYPE_ERROR_ARRAY_SZ];

/// Used to represent the various design entities in PQL
enum DesignEnt {
    ENT_PROC,     ///< type for procedure
    ENT_STMTLST,  ///< type for stmtLst
    ENT_STMT,     ///< type for stmt
    ENT_ASSIGN,   ///< type for assign
    ENT_CALL,     ///< type for call
    ENT_WHILE,    ///< type for while
    ENT_IF,       ///< type for if
    ENT_VAR,      ///< type for variable
    ENT_CONST,    ///< type for constant
    ENT_PROGLINE, ///< type for prog_line
    ENT_INVALID   ///< Invalid type, indicates an error
};

/// Type of the select clause
enum SelectType {
    SEL_TUPLE,  ///< Select tuple
    SEL_BOOLEAN ///< Select boolean
};

/// Type of a 'ref' in the PQL grammar
enum RefType {
    REF_STRING,  ///< a string
    REF_INT,     ///< an integer
    REF_ATTRREF, ///< an attrRef
    REF_INVALID
};

/// Representation of a 'ref' which is a synonym
enum RefSynType {
    REFSYN_PROC,                 ///< procedure.procName
    REFSYN_STMTLST,              ///< stmtLst.stmt#
    REFSYN_STMT,                 ///< stmt.stmt#
    REFSYN_ASSIGN,               ///< assign.stmt#
    REFSYN_CALL,                 ///< call.stmt#
    REFSYN_CALL_PROCNAME,        ///< call.procName
    REFSYN_WHILE,                ///< while.stmt#
    REFSYN_IF,                   ///< if.stmt#
    REFSYN_VAR,                  ///< variable.varName
    REFSYN_CONST,                ///< constant.value
    REFSYN_PROGLINE,             ///< prog_line
    REFSYN_PROGLINE_PROGLINE_NO, ///< prog_line.prog_line#
    REFSYN_INVALID               ///< invalid type
};

/// Type of an attrName in the PQL grammar
enum AttrType {
    ATTR_PROCNAME, ///< .procName, for procedure
    ATTR_VARNAME,  ///< .varName, for variable
    ATTR_VALUE,    ///< .value, for constant
    ATTR_STMTNO,   ///< .stmt#, for statement types
    ATTR_PROGLINE, ///< .prog_line#, for prog_line
    ATTR_INVALID,  ///< Invalid type, indicates an error
    ATTR_DEFAULT   ///< same type as synonym
};

/// Type of Relation, eg. Modifies, Calls, Parent
enum RelRefType {
    REL_MODIFIES,     ///< Modifies
    REL_USES,         ///< Uses
    REL_CALLS,        ///< Calls
    REL_CALLS_STAR,   ///< Calls*
    REL_PARENT,       ///< Parent
    REL_PARENT_STAR,  ///< Parent*
    REL_FOLLOWS,      ///< Follows
    REL_FOLLOWS_STAR, ///< Follows*
    REL_NEXT,         ///< Next
    REL_NEXT_STAR,    ///< Next*
    REL_AFFECTS,      ///< Affects
    REL_AFFECTS_STAR, ///< Affects*
    REL_INVALID       ///< Invalid Relation, indicates an error
};

/// Type of a clause in PQL query, eg. Relation, Pattern, With
enum ClauseType {
    SUCHTHAT_CLAUSE, ///< Relation clauses, eg. Modifies, Parent
    WITH_CLAUSE,     ///< with clause
    PATTERN_CLAUSE,  ///< pattern clause
    INVALID_CLAUSE   ///< Invalid type, indicates an error
};

/// Indicates the argument type in a Relation clause
enum RelRefArgType {
    RELARG_SYN,      ///< Synonym
    RELARG_STRING,   ///< String
    RELARG_INT,      ///< Integer
    RELARG_WILDCARD, ///< Wildcard, or '_'
    RELARG_INVALID   ///< Invalid type, indicates an error
};

/// Type of pattern clause
enum PatClType {
    PATCL_ASSIGN, ///< pattern assignSyn(...)
    PATCL_IF,     ///< pattern ifSyn(...)
    PATCL_WHILE,  ///< pattern whileSyn(...)
    PATCL_INVALID ///< Invalid type, indicates an error
};

/// Type of variable for pattern clause
enum PatClVarRefType {
    PATVARREF_SYN,      ///< Synonym
    PATVARREF_WILDCARD, ///< Wildcard, or '_'
    PATVARREF_STRING,   ///< String
    PATVARREF_INVALID   ///< Invalid type, indicates an error
};

/// Type of first expression for pattern clause
/// Note that we do not store the second expression for pattern if,
/// since it is always a wildcard
enum PatClExprType {
    PATEXPR_EXPR,          ///< Expression
    PATEXPR_EXPR_WILDCARD, ///< Expression with wildcard on both sides
    PATEXPR_WILDCARD,      ///< Wildcard, or '_'
    PATEXPR_INVALID        ///< Invalid type, indicates an error
};

/// General Type, read explanation for more details
/// For instance,
/// ENT_ASSIGN -> BASETYPE_INT
/// ENT_PROC   -> BASETYPE_STRING
/// REFSYN_CALL -> BASETYPE_INT
/// REFSYN_CALL_PROCNAME -> BASETYPE_STRING
enum BaseType {
    BASETYPE_INT,    ///< int type
    BASETYPE_STRING, ///< string type
    BASETYPE_INVALID ///< invalid type
};

/// PQLParser error types
enum ParseError {
    PARSE_OK,
    PARSE_DECL_EMPTY_SYN, PARSE_DECL_REPEATED_SYN, PARSE_DECL_INVALID_SYN,
    PARSE_DECL_ENT_SYN_INVALID_SEP, PARSE_DECL_NO_TERMINATOR,
    PARSE_NO_SELECT_AFTER_DECL, PARSE_NO_SEP_AFTER_SELECT,
    PARSE_SELECT_UNDECLARED,
    PARSE_SELECT_INVALID_ATTRREF,
    PARSE_SELECT_TUPLE_NO_CLOSE, PARSE_SELECT_NOTHING,
    PARSE_ATTRREF_UNDEF_ATTRNAME, PARSE_ATTRREF_UNDECLARED,
    PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
    PARSE_REL_ARGONE, PARSE_REL_ARGTWO, PARSE_REL_ARG_INT_INVALID,
    PARSE_REL_ARGONE_UNDECLARED, PARSE_REL_ARGONE_TYPE_ERROR,
    PARSE_REL_ARGTWO_UNDECLARED, PARSE_REL_ARGTWO_TYPE_ERROR,
    PARSE_REL_NO_COMMA, PARSE_REL_NO_RPAREN,
    PARSE_RELCOND_AND_NOSEP, PARSE_RELCOND_INVALID_RELREF,
    PARSE_PATCL_VARREF_INVALID, PARSE_PATCL_VARREF_UNDECLARED,
    PARSE_PATCL_VARREF_NOTVAR, PARSE_PATCL_ARGONE_NOCOMMA,
    PARSE_PATCL_ASSIGN_EXPR_NODQUOTE,
    PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE,
    PARSE_PATCL_ASSIGN_EXPR_INVALID,
    PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE,
    PARSE_PATCL_IF_ARGTWO_NOCOMMA, PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE,
    PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE,
    PARSE_PATCL_NORPAREN, PARSE_PATCL_SYN_UNDECLARED,
    PARSE_PATCL_NOLPAREN, PARSE_PATCL_SYN_TYPE_ERROR,
    PARSE_PATCOND_AND_NOSEP, PARSE_PATCOND_INVALID_PATCL,
    PARSE_QINFO_INSERT_INVALID_RELREF,
    /// Triggered when a ref is a synonym and the
    /// synonym is undeclared
    PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
    /// Triggered when a ref in with clause is a synonym
    /// but not a prog_line
    PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
    PARSE_WITHCLAUSE_REFS_INVALID,
    /// Triggered when ref on both sides of a with clause have differing
    /// BaseType, eg.
    /// 3 = "somestring"
    /// call1.procName = a1.stmt#
    PARSE_WITHCLAUSE_TYPE_MISMATCH,
    /// Triggered for concrete with clause whose values dont match
    /// eg. "astring" = "bstring", 35 = 1024
    /// This should not be handled by PQLParser::error
    PARSE_WITHCLAUSE_VALUE_MISMATCH,
    PARSE_WITHCLAUSE_AND_NOSEP,
    /// Triggered when we have parsed leftRef and '=' but right hand
    /// side of '=' is not a valid Ref
    PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS,
    /// In a consecutive chain of with clause, this is triggered when
    /// we have ate the 'and' token, but failed to parse leftRef or
    /// failed to parse '='
    PARSE_WITHCLAUSE_EXPECT_WITH,
    /// Triggered when a syntactically and semantically valid
    /// with clause can NEVER be true.
    /// This is meant to skip query evaluation if triggered and
    /// should not be handled by PQLParser::error
    PARSE_WITHCLAUSE_CONTRADICTION,
    PARSE_REF_INTEGER_ERROR, PARSE_REF_ATTRREF_ERROR,
    PARSE_DQUOTED_IDENT_INVALID,
    PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE,
    PARSE_END_OF_QUERY_ERROR,
    PARSE_UNKNOWN
};

// Forward declaration
struct AttrRef;

/// Returns a string equivalent of a given RelRefType
/// @param relType relation type eg. REL_MODIFIES, REL_USES
/// @return a string constant of the equivalent RelRefType,
///         or an error string if REL_INVALID was supplied
const char *relRefType_to_string(RelRefType relType);
/// Returns a string equivalent of a DesignEnt
/// @param entType the design entity
/// @return a string constant of the equivalent DesignEnt,
///         or an error string if ENT_INVALID was supplied
const char *entity_type_to_string(DesignEnt entType);
/// Returns a string equivalent of an AttrType
/// @param attrType the AttrType
/// @return a string constant of the equivalent AttrType,
///         or an error string if ATTR_INVALID was supplied
const char *attrType_to_string(AttrType attrType);
/// Returns an appropriate RelRefArgType the DesignEnt can
/// store. This can only be RELARG_STRING or RELARG_INT
/// @param ent the design entity
/// @return a RelRefArgType indicating the type of the DesignEnt,
///         or RELARG_INVALID if ENT_INVALID was supplied
RelRefArgType designEnt_to_relRefArgType(DesignEnt ent);
/// Converts a RefSynType to a BaseType
/// @param refSynType the input RefSynType to convert
/// @return a BaseType corresponding to the given RefSynType
BaseType refSynType_to_BaseType(RefSynType refSynType);
/// Converts a BaseType to a string
/// @param baseType the BaseType to convert
/// @return a string representation of the BaseType
const char *baseType_to_string(BaseType baseType);
/// Converts an AttrRef to a RefSynType
/// @param attrRef the AttrRef to convert
/// @return a RefSynType equivalent to the AttrRef
RefSynType attrRef_to_RefSynType(const AttrRef& attrRef);

/// Interface inherited by RelRef, PatCl
/// This allows us to use a single type to store RelRef and PatCl
struct GenericRef {
public:
    /// dummy method, just implement this with empty body in subclasses
    virtual void dummy();
};

/// Data structure for an attrRef in the PQL grammar.
/// An example of an AttrRef:
/// <pre><code>
///     assign a;
///     a.stmt#
/// </code></pre>
struct AttrRef {
public:
    /// synonym portion of the attrRef
    std::string syn;
    /// DesignEnt representing the type of the AttrRef::syn
    DesignEnt entType;
    /// AttrType of the AttrRef
    AttrType attr;

    /// Constructor
    AttrRef();
    /// Copy constructor
    /// @param o AttrRef to copy
    AttrRef(const AttrRef& o);
    /// Copy assignment operator
    /// @param o AttrRef to copy
    /// @return reference to this AttrRef. This is a C++ convention
    AttrRef& operator=(const AttrRef &o);
    /// Destructor
    ~AttrRef();
    /// Constructor with values supplied
    /// @param s string representing the synonym part of the AttrRef
    /// @param et DesignEnt of the synonym s
    /// @param a AttrType of the AttrRef
    AttrRef(std::string s, DesignEnt et, AttrType a);
    /// Compares this AttrRef with another AttrRef for equality
    /// @param o the AttrRef to compare with
    /// @return true if this AttrRef is equal to the other AttrRef,
    ///         false otherwise
    bool operator==(const AttrRef& o) const;
    /// dumps a string representation of the AttrRef into the
    /// StringBuffer
    /// @param sb StringBuffer to dump the string representation of
    ///           the AttrRef to
    void dump_to_sb(StringBuffer &sb) const;
    /// Returns a "syn.attrName" representation of the AttrRef
    /// @return string in "syn.attrName" format of the AttrRef
    std::string toPeriodString() const;
    /// Used to swap two AttrRef
    /// @param one the first AttrRef
    /// @param two the second AttrRef
    friend void swap(AttrRef& one, AttrRef& two) {
        using std::swap;
        swap(one.syn, two.syn);
        swap(one.entType, two.entType);
        swap(one.attr, two.attr);
    }
};

/// Used for comparing AttrRef objects
struct AttrRefCmp {
    /// Comparison operator for AttrRef objects
    /// @param a the first AttrRef
    /// @param b the second AttrRef
    /// @return true if a < b, false otherwise
    bool operator()(const AttrRef &a, const AttrRef &b) const;
};

/// Data structure for Relation clauses, eg. Modifies, Uses
struct RelRef: public GenericRef {
public:
    /// Relation type, eg. Modifies, Uses, Parent
    RelRefType relType;
    /// Type of the first argument to the Relation.
    /// For Modifies(a,v), this will refer to the synonym "a"
    RelRefArgType argOneType;
    /// If first argument of the Relation is of type RELARG_SYN,
    /// then this field indicates its type in terms of DesignEnt.
    /// Otherwise, the value of this field should not be trusted.
    DesignEnt argOneSyn;
    /// String of the first argument in the Relation.
    /// Case 1: RelRef::argOneType is RELARG_SYN. This field indicates
    ///         the name of the synonym.
    ///
    /// Case 2: RelRef::argOneType is RELARG_STRING. This field
    ///         indicates the actual string.
    ///
    /// Otherwise: the value of this field should not be trusted.
    std::string argOneString;
    /// If the first argument of the Relation is of type RELARG_INT,
    /// then this field indicates its value.
    ///
    /// Otherwise, the value of this field should not be trusted.
    int argOneInt;
    /// Type of the second argument to the Relation.
    /// For Modifies(a,v), this will refer to the synonym "b"
    RelRefArgType argTwoType;
    /// If the first argument of the Relation is of type RELARG_SYN,
    /// then this field indicates its type in terms of DesignEnt.
    /// Otherwise, the value of this field should not be trusted.
    DesignEnt argTwoSyn;
    /// String of the second argument in the Relation.
    /// Case 1: RelRef::argTwoType is RELARG_SYN. This field indicates
    ///         the name of the synonym.
    ///
    /// Case 2: RelRef::argTwoType is RELARG_STRING. This field
    ///         indicates the actual string.
    ///
    /// Otherwise: the value of this field should not be trusted.
    std::string argTwoString;
    /// If the second argument of the Relation is of type RELARG_INT,
    /// then this field indicates its value.
    ///
    /// Otherwise, the value of this field should not be trusted.
    int argTwoInt;

    /// Constructor
    RelRef();
    /// Copy constructor
    /// @param o the RelRef to copy
    RelRef(const RelRef &o);
    /// Copy assignment operator
    /// @param o the RelRef to copy
    /// @return a reference to this RelRef. This is a C++ convention
    RelRef &operator=(const RelRef &o);
    /// Destructor
    ~RelRef();
    /// Sets the first argument of the RelRef
    /// @param argType the argument type of the RelRef
    /// @param sb StringBuffer containing the string of the first
    ///           argument
    /// @param errorMsg a pointer to a char* for error messages.
    ///                 The char* should point to NULL if supplied,
    ///                 and if not supplied, this field should be set
    ///                 to NULL.
    ///                 If anything other than PARSE_OK was returned
    ///                 by this method and *errorMsg != NULL, then
    ///                 an error string may possibly be allocated.
    ///                 It is the user's responsibility to call the
    ///                 "free" function on this string.
    /// @return a ParseError signalling whether this call was
    ///         sucessful / unsuccessful
    ParseError set_arg_one(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    /// Sets the second argument of the RelRef
    /// @param argType the argument type of the RelRef
    /// @param sb StringBuffer containing the string of the second
    ///           argument
    /// @param errorMsg a pointer to a char* for error messages.
    ///                 The char* should point to NULL if supplied,
    ///                 and if not supplied, this field should be set
    ///                 to NULL.
    ///                 If anything other than PARSE_OK was returned
    ///                 by this method and *errorMsg != NULL, then
    ///                 an error string may possibly be allocated.
    ///                 It is the user's responsibility to call the
    ///                 "free" function on this string.
    /// @return a ParseError signalling whether this call was
    ///         sucessful / unsuccessful
    ParseError set_arg_two(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    /// Sets the first or second argument of the RelRef
    /// @param which Either 1 (for first argument) or
    //               2 (for second argument)
    /// @param argType the argument type of the RelRef
    /// @param sb StringBuffer containing the string argument
    /// @param errorMsg a pointer to a char* for error messages.
    ///                 The char* should point to NULL if supplied,
    ///                 and if not supplied, this field should be set
    ///                 to NULL.
    ///                 If anything other than PARSE_OK was returned
    ///                 by this method and *errorMsg != NULL, then
    ///                 an error string may possibly be allocated.
    ///                 It is the user's responsibility to call the
    ///                 "free" function on this string.
    /// @return a ParseError signalling whether this call was
    ///         sucessful / unsuccessful
    ParseError set_arg(int which, RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    /// Returns a string representation of the RelRef
    /// @return a string representation of the RelRef
    std::string dump(void) const;
    /// Checks if the RelRef is valid, ie. it has valid relation
    /// type and valid argument types
    /// @param r the RelRef to check
    /// @return true if the RelRef is valid, false otherwise
    static bool valid(const struct RelRef &r);
    /// dummy method inherited from GenericRef
    void dummy();
    /// swaps two RelRef
    /// @param one the first RelRef
    /// @param two the second RelRef
    friend void swap(RelRef& one, RelRef& two) {
        using std::swap;
        swap(one.relType, two.relType);
        swap(one.argOneType, two.argOneType);
        swap(one.argOneSyn, two.argOneSyn);
        swap(one.argOneString, two.argOneString);
        swap(one.argOneInt, two.argOneInt);
        swap(one.argTwoType, two.argTwoType);
        swap(one.argTwoSyn, two.argTwoSyn);
        swap(one.argTwoString, two.argTwoString);
        swap(one.argTwoInt, two.argTwoInt);
    }
};

/// For comparing RelRef so that we will not insert repeated RelRef
struct RelRefCmp {
    /// Comparison operator for RelRef
    /// @param a first RelRef
    /// @param b second RelRef
    /// @return true if a < b, false otherwise
    bool operator()(const RelRef &a, const RelRef &b) const;
};

/// Data structure for representing pattern clause
struct PatCl: public GenericRef {
public:
    /// type of the pattern clause, one of assign, if, while
    enum PatClType type;
    /// synonym of the pattern clause
    ///
    /// For pattern assignSyn(...), this refers to assignSyn
    ///
    /// For pattern ifSyn(...), this refers to ifSyn
    ///
    /// For pattern whileSyn(...), this refers to whileSyn
    std::string syn;
    /// indicates the type of the variable in the pattern clause
    enum PatClVarRefType varRefType;
    /// string of the variable in the pattern clause
    ///
    /// Case 1: varRefType == PATVARREF_SYN. Then this field refers
    ///         to the name of the synonym for the variable
    ///
    /// Case 2: varRefType == PATVARREF_STRING. Then this field
    ///         refers to the actual string argument
    ///
    /// Otherwise, the value of this field cannot be trusted
    std::string varRefString;
    /// Indicates the type of the expression (the 2nd argument)
    /// of the pattern clause
    ///
    /// Case 1: PatCl::type == PATCL_ASSIGN. Then this field can
    ///         be PATEXPR_EXPR, PATEXPR_EXPR_WILDCARD or
    ///         PATEXPR_WILDCARD
    ///
    /// Otherwise, you can safely ignore the value of this field,
    /// since the remaining argument(s) for pattern if and
    /// pattern while can only be wildcard
    enum PatClExprType exprType;
    /// Indicates the expression string of the second argument
    /// in a pattern assign clause.
    ///
    /// This field is only valid if all the below are valid:
    ///
    /// 1. PatCl::type == PATCL_ASSIGN
    /// 2. PatCl::exprType == PATEXPR_EXPR ||
    ///    PatCl::exprType == PATEXPR_EXPR_WILDCARD
    std::string exprString;

    /// Constructor
    PatCl();
    /// Copy constructor
    /// @param o the PatCl to copy
    PatCl(const PatCl& o);
    /// Copy assignment operator
    /// @param o the PatCl to copy
    /// @return a reference to this PatCl. This is a C++ convention
    PatCl& operator=(const PatCl& o);
    /// Destructor
    ~PatCl();
    /// Sets the pattern assign clause
    /// @param s the assign synonym
    /// @param vrType the variable type
    /// @param vr the string of the variable
    /// @param exType the expression type
    /// @param ex the string of the expression
    void set_pat_assign(const std::string &s, enum PatClVarRefType vrType,
            const std::string& vr, enum PatClExprType exType,
            const std::string& ex);
    /// Sets the pattern if clause
    /// @param s the if synonym
    /// @param vrType the variable type
    /// @param vr the string of the variable
    void set_pat_if(const std::string& s, enum PatClVarRefType vrType,
            const std::string& vr);
    /// Sets the pattern while clause
    /// @param s the while synonym
    /// @param vrType the variable type
    /// @param vr the string of the variable
    void set_pat_while(const std::string& s, enum PatClVarRefType vrType,
            const std::string& vr);
    // Returns a string representation of the pattern clause
    /// @param showType shows the type of the clause, eg. assign, if
    /// @return a string representation of the pattern clause
    std::string toString(bool showType=false) const;
    /// Checks if a pattern clause is valid
    /// @param p the pattern clause to check
    /// @return true if p is valid, false otherwise
    static bool valid(const PatCl &p);
    /// dummy method inherited from GenericRef
    void dummy();
    /// swaps two PatCl
    /// @param one the first PatCl
    /// @param two the second PatCl
    friend void swap(PatCl &one, PatCl &two) {
        using std::swap;
        swap(one.type, two.type);
        swap(one.syn, two.syn);
        swap(one.varRefType, two.varRefType);
        swap(one.varRefString, two.varRefString);
        swap(one.exprType, two.exprType);
        swap(one.exprString, two.exprString);
    }
};

/// Used to compare two PatCl
struct PatClCmp {
    /// Comparison function for PatCl
    /// @param a the first PatCl
    /// @param b the second PatCl
    /// @return true if a < b, false otherwise
    bool operator()(const PatCl &a, const PatCl &b) const;
};

/// Ref data structure
struct Ref {
    /// type of Ref
    RefType refType;
    /// if refType == REF_STRING, this holds the literal string value
    /// if refType == REF_ATTRREF, this holds the synonym
    std::string refStringVal;
    /// if refType == REF_INT, this holds the literal integer value
    int refIntVal;
    /// if refType == REF_ATTRREF, this holds the type of AttrRef
    /// eg. REFSYN_ASSIGN, REFSYN_CALL, REFSYN_CALL_PROCNAME
    RefSynType refSynType;
    /// Constructor
    Ref();
    /// Copy constructor
    Ref(const Ref& o);
    /// Copy assignment operator
    /// @param o the Ref to copy
    /// @return a reference to this Ref
    Ref& operator=(const Ref& o);
    /// Compare with another Ref for equality
    /// @param o the Ref to compare against
    /// @return true if this Ref is equal to the other Ref
    bool operator==(const Ref& o) const;
    /// Converts the Ref to a string
    /// @return a string representation of the Ref
    std::string toString() const;
    /// Swaps two Ref
    /// @param x the first Ref
    /// @param y the second Ref
    friend void swap(Ref& x, Ref& y) {
        using std::swap;
        swap(x.refType, y.refType);
        swap(x.refStringVal, y.refStringVal);
        swap(x.refIntVal, y.refIntVal);
        swap(x.refSynType, y.refSynType);
    }
    /// Checks if a Ref is valid
    /// @param ref the Ref to check validity
    /// @return true if the Ref is valid, false otherwise
    static bool valid(const Ref& ref);
    /// Gets the BaseType of a Ref
    /// @return the BaseType of the Ref
    static BaseType get_BaseType(const Ref& ref);
};

/// Comparator for Ref
struct RefCmp {
    /// Compares two Ref using < relationship
    /// @param x the first Ref
    /// @param y the second Ref
    /// @return true if x < y, false otherwise
    bool operator()(const Ref& x, const Ref& y) const;
};

/// Data structure for WithClause
struct WithClause: public GenericRef {
    /// ref on left hand side of '='
    Ref leftRef;
    /// ref on right hand side of '='
    Ref rightRef;

    /// Default constructor
    WithClause();
    /// Copy constructor
    /// @param o the WithClause to copy
    WithClause(const WithClause& o);
    /// Copy assignment operator
    /// @param o the WithClause to copy
    /// @return a reference to this WithClause
    WithClause& operator=(const WithClause& o);
    /// Converts the WithClause to a string
    /// @return a string representation of the WithClause
    std::string toString() const;
    /// Normalizes the representation of a WithClause.
    /// WithClause with both arguments being concrete values
    /// will not be affected.
    ///
    /// For WithClause with 1 concrete argument and 1 synonym
    /// argument, the synonym argument will always be on the LHS.
    ///
    /// For WithClause with 2 synonym arguments, we reorder
    /// according to the following criteria:
    /// If the 2 Refs are of the same RefSynType, we order them
    /// according to their synonyms (lexicographical ordering).
    /// Otherwise, we order according to their appearance
    /// in the RefSynType enum definition.
    void normalize();
    /// dummy method
    void dummy();
    /// Checks if a WithClause can never evaluate to true
    /// @return true if a WithClause is a contradiction, false otherwise
    bool is_contradiction() const;
    /// Swaps two WithClause
    /// @param x the first WithClause
    /// @param y the second WithClause
    friend void swap(WithClause& x, WithClause& y) {
        using std::swap;
        swap(x.leftRef, y.leftRef);
        swap(x.rightRef, y.rightRef);
    }
    /// Checks if a WithClause's left and right refs are valid
    /// @return true if a WithClause's refs are valid, false otherwise
    static bool valid_refs(const WithClause& withClause);
    /// Checks for type validity of WithClause
    /// @return true if a WithClause's leftRef type matches its rightRef
    ///         type, false otherwise
    static bool valid_type(const WithClause& withClause);
};

/// Comparator for WithClause
struct WithClauseCmp {
    /// Compares two WithClause using '<' relation
    /// @param x the first WithClause
    /// @param y the second WithClause
    /// @return true if x < y, false otherwise
    bool operator()(const WithClause& x, const WithClause& y) const;
};

#define QINFO_ERROR_LEN 1000

/// Data structure representing a PQL query
class QueryInfo {
public:
    /// Constructor
    QueryInfo();
    /// Constructor taking in a symbol table
    /// @param etab symbol table containing string to DesignEnt mapping
    /// @param eVec vector representation of the symbol table; it is
    ///             here as a linear representation of the symbol table
    QueryInfo(const std::map<std::string, DesignEnt>& etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    /// Destructor
    ~QueryInfo();
    /// Clears the QueryInfo data structure and inserts information
    /// from the symbol table.
    /// @param etab the symbol table containing string to DesignEnt
    ///             mapping
    /// @param eVec vector representation of the symbol table; it is
    ///             here as a linear representation of the symbol table
    void reset(const std::map<std::string, DesignEnt> &etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    /// Set the Select clause to select boolean
    void set_select_boolean();
    /// Set the Select clause to select tuple
    void set_select_tuple();
    /// Adds a tuple to be selected
    /// @param attrRef an additional tuple to be selected
    /// @return a ParseError enum indicating PARSE_OK on success
    ///         or an appropriate error otherwise.
    ParseError add_select_tuple(AttrRef attrRef);
    /// Adds a new Relation clause
    /// @param relRef the new Relation clause to be added
    /// @param errorMsg pointer to a char*. If supplied, the char*
    ///                 should point to NULL. Otherwise, this field
    ///                 should be set to NULL.
    ///                 If supplied, this field allows an appropriate
    ///                 error message to be returned to the user.
    ///                 The user should check this field and call "free"
    ///                 on the string (if an error string is allocated)
    /// @return a ParseError enum indicating PARSE_OK on success
    ///         or an apporpriate error otherwise.
    ParseError add_relRef(RelRef& relRef, char **errorMsg);
    /// Adds a new pattern clause
    /// @param PatCl the new pattern clause to be added
    /// @param errorMsg pointer to a char*. If supplied, the char*
    ///                 should point to NULL. Otherwise, this field
    ///                 should be set to NULL.
    ///                 If supplied, this field allows an appropriate
    ///                 error message to be returned to the user.
    ///                 The user should check this field and call "free"
    ///                 on the string (if an error string is allocated)
    /// @return a ParseError enum indicating PARSE_OK on success
    ///         or an apporpriate error otherwise.
    ParseError add_patCl(const PatCl &p, char **errorMsg);
    /// Adds a new WithClause
    /// @param withClause the WithClause to add
    /// @param errorMsg pointer to char*. If supplied, the char *
    ///                 should contain the value NULL. Otherwise, this
    ///                 field should be set to NULL.
    ///                 If supplied, this field allows an appropriate
    ///                 error message to be returned to the user.
    ///                 The user should check this field and call the
    ///                 free function on the string if *errorMsg != NULL
    /// @return PARSE_OK on success, or an appropriate error otherwise
    ParseError add_withClause(const WithClause &withClause,
            char **errorMsg);
    /// Dumps a representation of the QueryInfo data structure to stdout
    void dump(void) const;
    /// Dumps a representation of the QueryInfo data structure to
    /// a FILE*
    void dump(FILE *f) const;
    /// Returns a string representation of the QueryInfo data structure
    std::string dump_to_string() const;
    /// Retrieves the nth clause and its type
    /// @param n 0-indexed integer of the clause we wish to retrieve
    /// @param clauseType a pointer to ClauseType. If this is not NULL,
    ///                   it will be set to the ClauseType of the nth
    ///                   clause if it exists and set to INVALID_CLAUSE
    ///                   if the nth clause does not exist.
    /// @return a const GenericRef* of the clause we wish to retrieve, or
    ///         the NULL pointer if n is out of bounds.
    ///         The user should use a dynamic_cast to cast the
    ///         GenericRef* to an appropriate pointer. The clause's
    ///         actual type can be deduced by the return value of
    ///         QueryInfo::get_nth_clause_type
    const GenericRef *get_nth_clause(int n, ClauseType *clauseType) const;
    /// Returns the number of clauses in the PQL query
    /// @return the number of clauses in the PQL query
    int get_nr_clauses() const;
    /// Retrieves the type of the object the PQL query is selecting
    /// @return the type of the object the PQL query is selecting
    SelectType get_selectType() const;
    /// Retrieves all the objects the PQL query is selecting
    /// @return a reference to const vector of AttrRef representing
    ///         the objects the PQL query is selecting
    ///         The contents of the vector should only be trusted
    ///         if QueryInfo::get_selectType == SEL_TUPLE
    const std::vector<AttrRef>& get_selectTuple() const;
    /// Checks if the current query is alive
    /// @return true if the current query is alive, false otherwise
    bool is_alive() const;
    /// Kills the current query so that the QueryEvaluator will not
    /// process it
    void kill();

    /// Checks if synonyms of a certain DesignEnt is an acceptable
    /// type for the first argument of a Relation
    /// @param relType the Relation type
    /// @param entType the DesignEnt of the first argument to the
    ///                Relation
    /// @return true if the Relation accepts synonyms of the
    ///         DesignEnt as a first argument, false otherwise
    static bool is_valid_argOne_syn_type(RelRefType relType,
            DesignEnt entType);
    /// Checks if synonyms of a certain DesignEnt is an acceptable
    /// type for the second argument of a Relation
    /// @param relType the Relation type
    /// @param entType the DesignEnt of the second argument to the
    ///                Relation
    /// @return true if the Relation accepts synonyms of the
    ///         DesignEnt as a second argument, false otherwise
    static bool is_valid_argTwo_syn_type(RelRefType relType,
            DesignEnt entType);

private:
    /// Symbol table for design entity declarations
    std::map<std::string, DesignEnt> entTable;
    /// Linear representation of QueryInfo::entTable
    std::vector<std::pair<DesignEnt, std::string> > entVec;
    /// type of object the PQL Query is selecting
    SelectType selectType;
    /// If QueryInfo::selectType == SEL_TUPLE, then this stores
    /// the various objects selected
    std::vector<AttrRef> selectTuple;
    /// Set of the AttrRef we are selecting
    std::set<AttrRef, AttrRefCmp> selectTable;
    /// textual order of various clauses.
    ///
    /// This is used for identifying the ClauseType for an entry
    /// in QueryInfo::clauses and also for creating a string
    /// representation of the QueryInfo data structure.
    ///
    /// For each pair object, the ClauseType indicates the
    /// appropriate clause type, whereas the integer refers to
    /// the index into the appropriate vector.
    ///
    /// Eg. if ClauseType == SUCHTHAT_CLAUSE and int == 5,
    /// this refers to the 5th entry (0-indexed) of QueryInfo::relRefs
    std::vector<std::pair<ClauseType, int> > insertOrder;
    /// vector of Relation clauses (in textual order)
    std::vector<RelRef> relRefs;
    /// Set of Relation clauses. This allows us to avoid adding
    /// duplicated Relation clauses as an optimization.
    std::set<RelRef, RelRefCmp> relRefsSet;
    /// vector of Pattern clauses (in textual order)
    std::vector<PatCl> patCls;
    /// Set of Pattern clauses. This allows us to avoid adding
    /// duplicated Pattern clauses as an optimization.
    std::set<PatCl, PatClCmp> patClSet;
    /// vector of WithClause (in textual order)
    std::vector<WithClause> withClauseVec;
    /// Set of WithClause. This allows us to avoid adding duplicated
    /// WithClause as an optimization
    std::set<WithClause, WithClauseCmp> withClauseSet;
    /// vector of all the clauses (in textual order)
    std::vector<GenericRef *> clauses;
    /// if this is true, the QueryEvaluator will continue to
    /// process the query. Otherwise, the query evaluator will
    /// not process the query.
    bool alive;

    /// character buffer used to store error messages
    char errorBuf[QINFO_ERROR_LEN+5];

    /// Inserts a Relation clause
    /// @relRef the Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    void insert_relRef(const RelRef &relRef, char **errorMsg);
    /// Retrieves the type of a synonym declared in the PQL query
    /// @param s the name of the synonym
    /// @return a DesignEnt representing the type of the synonym in
    ///         the PQL query (if it was declared in the query),
    ///         ENT_INVALID otherwise.
    DesignEnt retrieve_syn_type(const std::string &s) const;
    ParseError add_X_relRef(const std::set<DesignEnt> &argOneTypes,
            const std::set<DesignEnt> &argTwoTypes,
            RelRef &relRef, char **errorMsg);
    /// Inserts a Modifies Relation clause
    /// @relRef the Modifies Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_modifies_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts a Uses Relation clause
    /// @relRef the Uses Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_uses_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts a Calls / Calls* Relation clause
    /// @relRef the Calls / Calls* Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_calls_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts a Parent / Parent* Relation clause
    /// @relRef the Parent / Parent* Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_parent_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts a Follows / Follows* Relation clause
    /// @relRef the Follows / Follows* Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_follows_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts a Next / Next* Relation clause
    /// @relRef the Next / Next* Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_next_relRef(RelRef &relRef, char **errorMsg);
    /// Inserts an Affects / Affects* Relation clause
    /// @relRef the Affects / Affects* Relation clause to insert
    /// @errorMsg pointer to char*. If this field is supplied, the
    ///           char* should have value NULL. The user should
    ///           check whether an error message was returned, by
    ///           checking the char* against NULL. If an error message
    ///           was returned, the user is responsible for freeing
    ///           the string using the "free" function.
    ///           If this field is not supplied, NULL can be used
    ///           in place of it.
    /// @return PARSE_OK on success, an appropriate error otherwise
    ParseError add_affects_relRef(RelRef &relRef, char **errorMsg);
    /// Dumps the declarations section of the PQL query to a
    /// StringBuffer
    /// @param sb the StringBuffer to dump the declarations to
    void dump_decl_select(StringBuffer &sb) const;
    /// Dumps all the clauses of the PQL query (in textual order)
    /// to a StringBuffer
    /// @param sb the StringBuffer to dump the clauses to
    void dump_clauses(StringBuffer &sb) const;

    #define MODIFIES_ARGONE_TYPES_ARR_SZ 7
    #define MODIFIES_ARGTWO_TYPES_ARR_SZ 1
    #define USES_ARGONE_TYPES_ARR_SZ 7
    #define USES_ARGTWO_TYPES_ARR_SZ 1
    #define CALLS_ARGONE_TYPES_ARR_SZ 1
    #define CALLS_ARGTWO_TYPES_ARR_SZ 1
    #define PARENT_ARGONE_TYPES_ARR_SZ 4
    #define PARENT_ARGTWO_TYPES_ARR_SZ 6
    #define FOLLOWS_ARGONE_TYPES_ARR_SZ 6
    #define FOLLOWS_ARGTWO_TYPES_ARR_SZ 6
    #define NEXT_ARGONE_TYPES_ARR_SZ 6
    #define NEXT_ARGTWO_TYPES_ARR_SZ 6
    #define AFFECTS_ARGONE_TYPES_ARR_SZ 1
    #define AFFECTS_ARGTWO_TYPES_ARR_SZ 1

    static DesignEnt MODIFIES_ARGONE_TYPES_ARR[MODIFIES_ARGONE_TYPES_ARR_SZ];
    static DesignEnt MODIFIES_ARGTWO_TYPES_ARR[MODIFIES_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt USES_ARGONE_TYPES_ARR[USES_ARGONE_TYPES_ARR_SZ];
    static DesignEnt USES_ARGTWO_TYPES_ARR[USES_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt CALLS_ARGONE_TYPES_ARR[CALLS_ARGONE_TYPES_ARR_SZ];
    static DesignEnt CALLS_ARGTWO_TYPES_ARR[CALLS_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt PARENT_ARGONE_TYPES_ARR[PARENT_ARGONE_TYPES_ARR_SZ];
    static DesignEnt PARENT_ARGTWO_TYPES_ARR[PARENT_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt FOLLOWS_ARGONE_TYPES_ARR[FOLLOWS_ARGONE_TYPES_ARR_SZ];
    static DesignEnt FOLLOWS_ARGTWO_TYPES_ARR[FOLLOWS_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt NEXT_ARGONE_TYPES_ARR[NEXT_ARGONE_TYPES_ARR_SZ];
    static DesignEnt NEXT_ARGTWO_TYPES_ARR[NEXT_ARGTWO_TYPES_ARR_SZ];
    static DesignEnt AFFECTS_ARGONE_TYPES_ARR[AFFECTS_ARGONE_TYPES_ARR_SZ];
    static DesignEnt AFFECTS_ARGTWO_TYPES_ARR[AFFECTS_ARGTWO_TYPES_ARR_SZ];
    static const std::set<DesignEnt> MODIFIES_ARGONE_TYPES;
    static const std::set<DesignEnt> MODIFIES_ARGTWO_TYPES;
    static const std::set<DesignEnt> USES_ARGONE_TYPES;
    static const std::set<DesignEnt> USES_ARGTWO_TYPES;
    static const std::set<DesignEnt> CALLS_ARGONE_TYPES;
    static const std::set<DesignEnt> CALLS_ARGTWO_TYPES;
    static const std::set<DesignEnt> PARENT_ARGONE_TYPES;
    static const std::set<DesignEnt> PARENT_ARGTWO_TYPES;
    static const std::set<DesignEnt> FOLLOWS_ARGONE_TYPES;
    static const std::set<DesignEnt> FOLLOWS_ARGTWO_TYPES;
    static const std::set<DesignEnt> NEXT_ARGONE_TYPES;
    static const std::set<DesignEnt> NEXT_ARGTWO_TYPES;
    static const std::set<DesignEnt> AFFECTS_ARGONE_TYPES;
    static const std::set<DesignEnt> AFFECTS_ARGTWO_TYPES;
};

// Globals

/// Global AttrRefCmp, defined in PQL.cpp
extern struct AttrRefCmp glob__AttrRefCmp;

/// Global RefCmp, defined in PQL.cpp
extern struct RefCmp glob__RefCmp;

#endif