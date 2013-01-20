#ifndef T11_PQL_H
#define T11_PQL_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "StringBuffer.h"

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
#define ATTR_DEFAULT_STR  "default"
#define ATTR_INVALID_STR  "invalid"

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

enum DesignEnt {
    ENT_PROC, ENT_STMTLST, ENT_STMT, ENT_ASSIGN, ENT_CALL,
    ENT_WHILE, ENT_IF, ENT_VAR, ENT_CONST, ENT_PROGLINE,
    ENT_INVALID
};

enum SelectType {
    SEL_TUPLE, SEL_BOOLEAN
};

enum AttrType {
    ATTR_PROCNAME, ATTR_VARNAME, ATTR_VALUE, ATTR_STMTNO,
    ATTR_INVALID, ATTR_DEFAULT
};

enum RelRefType {
    REL_MODIFIES, REL_USES, REL_CALLS, REL_CALLS_STAR,
    REL_PARENT, REL_PARENT_STAR, REL_FOLLOWS, REL_FOLLOWS_STAR,
    REL_NEXT, REL_NEXT_STAR, REL_AFFECTS, REL_AFFECTS_STAR,
    REL_INVALID
};

enum ClauseType {
    SUCHTHAT_CLAUSE, WITH_CLAUSE, PATTERN_CLAUSE, INVALID_CLAUSE
};

enum RelRefArgType {
    RELARG_SYN, RELARG_STRING, RELARG_INT, RELARG_WILDCARD,
    RELARG_INVALID
};

enum PatClType {
    PATCL_ASSIGN, PATCL_IF, PATCL_WHILE, PATCL_INVALID
};

enum PatClVarRefType {
    PATVARREF_SYN, PATVARREF_WILDCARD, PATVARREF_STRING, PATVARREF_INVALID
};

enum PatClExprType {
    PATEXPR_EXPR, PATEXPR_EXPR_WILDCARD, PATEXPR_WILDCARD,
    PATEXPR_INVALID
};

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
    PARSE_END_OF_QUERY_ERROR,
    PARSE_UNKNOWN
};

enum PQLOptimization {
    PQL_OPTIMIZE_NONE
};

// Helper functions
const char *relRefType_to_string(RelRefType relType);
const char *entity_type_to_string(DesignEnt entType);
const char *attrType_to_string(AttrType attrType);

struct AttrRef {
    std::string syn;
    DesignEnt entType;
    AttrType attr;
    AttrRef();
    AttrRef(std::string s, DesignEnt et, AttrType a);
    void dump_to_sb(StringBuffer &sb) const;
    std::string toPeriodString() const;
};

struct AttrRefCmp {
    bool operator()(const AttrRef &a, const AttrRef &b) const;
};

struct RelRef {
    RelRefType relType;
    RelRefArgType argOneType;
    DesignEnt argOneSyn;
    std::string argOneString;
    int argOneInt;
    RelRefArgType argTwoType;
    DesignEnt argTwoSyn;
    std::string argTwoString;
    int argTwoInt;

    RelRef();
    RelRef(const RelRef &o);
    RelRef &operator=(const RelRef &o);
    ~RelRef();
    ParseError set_arg_one(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    ParseError set_arg_two(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    ParseError set_arg(int which, RelRefArgType argType, StringBuffer &sb,
            char **errorMsg);
    std::string dump(void) const;
    static bool valid(const struct RelRef &r);
};

// For comparing RelRef so that we will not insert repeated relref
struct RelRefCmp {
    bool operator()(const RelRef &a, const RelRef &b) const;
};

// Pattern clauses
struct PatCl {
    enum PatClType type;
    std::string syn;
    enum PatClVarRefType varRefType;
    std::string varRefString;
    enum PatClExprType exprType;
    std::string exprString;

    PatCl();
    void set_pat_assign(const std::string &s, enum PatClVarRefType vrType,
            const std::string& vr, enum PatClExprType exType,
            const std::string& ex);
    void set_pat_if(const std::string& s, enum PatClVarRefType vrType,
            const std::string& vr);
    void set_pat_while(const std::string& s, enum PatClVarRefType vrType,
            const std::string& vr);
    std::string toString(bool showType=false) const;
    static bool valid(const PatCl &p);
};

struct PatClCmp {
    bool operator()(const PatCl &a, const PatCl &b) const;
};

// class QueryInfo

#define QINFO_ERROR_LEN 1000

class QueryInfo {
public:
    QueryInfo();
    QueryInfo(const std::map<std::string, DesignEnt>& etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    void optimize(enum PQLOptimization method=PQL_OPTIMIZE_NONE);
    void reset(const std::map<std::string, DesignEnt> &etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    void set_select_boolean();
    void set_select_tuple();
    ParseError add_select_tuple(AttrRef attrRef);
    ParseError add_relRef(RelRef& relRef, char **errorMsg);
    ParseError add_patCl(const PatCl &p, char **errorMsg);
    void dump(void) const;
    void dump(FILE *f) const;
    std::string dump_to_string() const;
    std::string dump_optimized_to_string() const;
    ClauseType get_nth_clause(int n, void **r);
    int get_nr_clauses() const;
    SelectType get_selectType() const;
    const std::vector<AttrRef>& get_selectTuple() const;

private:
    // entity declarations
    std::map<std::string, DesignEnt> entTable;
    std::vector<std::pair<DesignEnt, std::string> > entVec;
    SelectType selectType;
    std::vector<AttrRef> selectTuple;
    std::set<AttrRef, AttrRefCmp> selectTable;
    std::vector<std::pair<ClauseType, int> > insertOrder;
    std::vector<std::pair<ClauseType, int> > evalOrder;
    std::vector<RelRef> relRefs;
    std::set<RelRef, RelRefCmp> relRefsSet;
    std::vector<PatCl> patCls;
    std::set<PatCl, PatClCmp> patClSet;

    char errorBuf[QINFO_ERROR_LEN+5];

    void insert_relRef(const RelRef &relRef, char **errorMsg);
    DesignEnt retrieve_syn_type(const std::string &s) const;
    ParseError add_X_relRef(const std::set<DesignEnt> &argOneTypes,
            const std::set<DesignEnt> &argTwoTypes,
            RelRef &relRef, char **errorMsg);
    ParseError add_modifies_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_uses_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_calls_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_parent_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_follows_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_next_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_affects_relRef(RelRef &relRef, char **errorMsg);
    void dump_decl_select(StringBuffer &sb) const;
    void dump_clauses(StringBuffer &sb, bool dumpOptimized=false) const;

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
    static std::set<DesignEnt> MODIFIES_ARGONE_TYPES;
    static std::set<DesignEnt> MODIFIES_ARGTWO_TYPES;
    static std::set<DesignEnt> USES_ARGONE_TYPES;
    static std::set<DesignEnt> USES_ARGTWO_TYPES;
    static std::set<DesignEnt> CALLS_ARGONE_TYPES;
    static std::set<DesignEnt> CALLS_ARGTWO_TYPES;
    static std::set<DesignEnt> PARENT_ARGONE_TYPES;
    static std::set<DesignEnt> PARENT_ARGTWO_TYPES;
    static std::set<DesignEnt> FOLLOWS_ARGONE_TYPES;
    static std::set<DesignEnt> FOLLOWS_ARGTWO_TYPES;
    static std::set<DesignEnt> NEXT_ARGONE_TYPES;
    static std::set<DesignEnt> NEXT_ARGTWO_TYPES;
    static std::set<DesignEnt> AFFECTS_ARGONE_TYPES;
    static std::set<DesignEnt> AFFECTS_ARGTWO_TYPES;
};

#endif