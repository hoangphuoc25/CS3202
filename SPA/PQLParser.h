#ifndef T11_PQLPARSER_H
#define T11_PQLPARSER_H

#include <cstdarg>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <memory>
#include <fstream>
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

#define S_TO_UINT_MAX 2147483647L
#define S_TO_UINT_EMPTY_STRING "string_to_uint - String is empty"
#define S_TO_UINT_WHITESPACE "string_to_uint - String consists of whitespace"
#define S_TO_UINT_TOO_LONG  "string_to_uint - String is too long (max 10 char)"
#define S_TO_UINT_OVERFLOW "string_to_uint - integer overflow. Max 2147483647"

// arg: synonym type
#define PARSE_DECL_EMPTY_SYN_STR \
    "Missing synonym of type \"%s\""
// args: synonym, new type, previous type
#define PARSE_DECL_REPEATED_SYN_STR \
    "synonym \"%s\" of type \"%s\" was previously declared as \"%s\""
// arg: PQLParser::eat_till_ws(sb) --> sb.c_str()
#define PARSE_DECL_INVALID_SYN_STR \
    "Expected synonym, got \"%s\""
#define PARSE_DECL_ENT_SYN_NOSEP_STR \
    "Expected whitespace between design entity and synonym"
#define PARSE_DECL_NO_TERMINATOR_STR \
    "Missing terminator ';'"
// arg: StringBuffer contents
#define PARSE_NO_SELECT_AFTER_DECL_STR \
    "Expected \"Select\", got \"%s\""
// arg: undeclared synonym
#define PARSE_SELECT_UNKNOWN_STR \
    "Unknown entity \"%s\""
// arg: repeated synonym
#define PARSE_SELECT_REPEATED_STR \
    "Select element \"%s\" already exists"
// arg: PQLParser::eat_till_comma_space_gt(sb) --> sb.c_str()
#define PARSE_SELECT_INVALID_ATTR_STR \
    "Invalid select attribute \"%s\""
#define PARSE_SELECT_TUPLE_NO_CLOSE_STR \
    "Missing '>' for Select tuple"
// arg: StringBuffer contents
#define PARSE_SELECT_NOTHING_STR \
    "Select clause: Expected tuple or BOOLEAN, got \"%s\""
// args: relRef string rep, relRef arg one
#define PARSE_REL_ARGONE_STR \
    "%s: invalid arg one \"%s\""
// args: relRef string rep, relRef arg two
#define PARSE_REL_ARGTWO_STR \
    "%s: invalid arg two \"%s\""
// args: relRef string rep, "one" / "two", synonym name, other error msg
#define PARSE_REL_ARG_INT_INVALID_STR \
    "%s: Invalid integer arg %s \"%s\" [%s]"
// args: relRef string rep, "one" / "two"
#define PARSE_REL_ARG_INVALID_STR \
    "%s: setting arg %s to arg of invalid type"
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
// arg: relRef.dump()
#define PARSE_RELREF_INVALID_STR \
    "Invalid RelRef \"%s\""
#define PARSE_RELCOND_AND_NOSEP_STR \
    "relCond: expect whitespace after \"and\""
// arg: PQLParser::eat_till_rparen(sb) --> sb.c_str()
#define PARSE_RELCOND_INVALID_RELREF_STR \
    "Expected RelRef, got \"%s\""
#define PARSE_QINFO_INSERT_INVALID_RELREF_STR \
    "QueryInfo::add_relRef - Trying to insert invalid relRef"
// arg: StringBuffer contents
#define PARSE_END_OF_QUERY_ERROR_STR \
    "Expected end of query, got \"%s\""
#define PARSE_UNKNOWN_STR "Unknown error"

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
    SUCHTHAT_CLAUSE, WITH_CLAUSE, PATTERN_CLAUSE
};

enum RelRefArgType {
    RELARG_SYN, RELARG_STRING, RELARG_INT, RELARG_WILDCARD,
    RELARG_INVALID
};

enum ParseError {
    PARSE_OK,
    PARSE_DECL_EMPTY_SYN, PARSE_DECL_REPEATED_SYN, PARSE_DECL_INVALID_SYN,
    PARSE_DECL_ENT_SYN_NOSEP, PARSE_DECL_NO_TERMINATOR,
    PARSE_NO_SELECT_AFTER_DECL, PARSE_NO_SEP_AFTER_SELECT,
    PARSE_SELECT_UNKNOWN, PARSE_SELECT_REPEATED, PARSE_SELECT_INVALID_ATTR,
    PARSE_SELECT_TUPLE_NO_CLOSE, PARSE_SELECT_NOTHING,
    PARSE_REL_ARGONE, PARSE_REL_ARGTWO, PARSE_REL_ARG_INT_INVALID,
    PARSE_REL_ARG_INVALID,
    PARSE_REL_ARGONE_UNDECLARED, PARSE_REL_ARGONE_TYPE_ERROR,
    PARSE_REL_ARGTWO_UNDECLARED, PARSE_REL_ARGTWO_TYPE_ERROR,
    PARSE_REL_NO_COMMA, PARSE_REL_NO_RPAREN,
    PARSE_RELREF_INVALID,
    PARSE_RELCOND_AND_NOSEP, PARSE_RELCOND_INVALID_RELREF,
    PARSE_QINFO_INSERT_INVALID_RELREF,
    PARSE_END_OF_QUERY_ERROR,
    PARSE_UNKNOWN
};

// Helper functions
const char *relRefType_to_string(RelRefType relType);
const char *entity_type_to_string(DesignEnt entType);
const char *attrType_to_string(AttrType attrType);
bool string_to_uint(const std::string& s, int *res, char **errorMsg);

struct AttrRef {
    std::string syn;
    DesignEnt entType;
    AttrType attr;
    AttrRef();
    AttrRef(std::string s, DesignEnt et, AttrType a);
    void dump_to_sb(StringBuffer &sb) const;
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

// For printing out parse error
class PQLParseErrorStream {
public:
    PQLParseErrorStream();
    PQLParseErrorStream(std::ostream *os_);
    PQLParseErrorStream(PQLParseErrorStream &o);
    void swap(PQLParseErrorStream &o) throw();
    PQLParseErrorStream& operator=(PQLParseErrorStream &o);
    ~PQLParseErrorStream();
    void print(const char *s);

private:
    bool useStderr;
    std::auto_ptr<std::ostream> os;
};

// forward declaration
class QueryInfo;

class PQLParser {
public:
    PQLParser();
    ~PQLParser();
    void parse(const std::string &s, bool showErrors_=true,
            bool showWarnings_=true);
    void parse(std::ostream *os, const std::string &s,
            bool showErrors_=true, bool showWarnings_=true);

    QueryInfo *get_queryinfo() const;

    // For testing purposes
    ParseError get_parse_result() const;
    std::map<std::string, DesignEnt> get_ent_table() const;

private:
    PQLParser(const PQLParser &o);
    PQLParser& operator=(const PQLParser &o);

    void _parse(const std::string &s, bool showErrors_=true,
            bool showWarnings_=true);
    void eat_decls();
    bool eat_decl_one() throw(ParseError);
    int eat_space();
    bool eat_one_char(char ch);
    bool eat_comma();
    bool eat_semicolon();
    bool eat_period();
    bool eat_lt();
    bool eat_gt();
    bool eat_lparen();
    bool eat_rparen();
    bool eat_underscore();
    bool eat_dquote();
    int eat_till_ws(StringBuffer &sb);
    int eat_till_rparen(StringBuffer &sb);
    int eat_till_comma_space(StringBuffer &sb);
    int eat_till_comma_space_gt(StringBuffer &sb);
    int eat_till_comma_space_rparen(StringBuffer &sb);
    int eat_till_comma_space_semicolon(StringBuffer &sb);
    bool eat_synonym(StringBuffer &sb);
    AttrRef eat_attrRef(StringBuffer &sb);
    bool eat_attrName(StringBuffer &sb);
    int eat_alpha(StringBuffer &sb);
    bool eat_alpha_string(StringBuffer &sb, const char *s);
    bool eat_alpha_strings(StringBuffer &sb, int nrStrs, ...);
    int eat_alpha_star(StringBuffer &sb);
    bool eat_alpha_star_string(StringBuffer &sb, const char *s);
    int eat_alpha_underscore(StringBuffer &sb);
    bool eat_alpha_underscore_string(StringBuffer &sb, const char *s);
    bool eat_design_entity(StringBuffer &sb);
    int eat_ident(StringBuffer &sb);
    bool eat_ident_string(StringBuffer &sb, const char *s);
    bool eat_dquoted_ident(StringBuffer &sb);
    bool eat_string_till_ws(StringBuffer &sb, const char *s);
    int eat_int(StringBuffer &sb);
    bool eat_select(StringBuffer &sb);
    bool eat_select_tuple(StringBuffer &sb);
    AttrRef eat_select_tuple_elem(StringBuffer &sb);
    void error_add_select_tuple(ParseError parseErr_, const AttrRef &attrRef)
        throw(ParseError);
    bool eat_select_boolean(StringBuffer &sb);
    bool eat_such_that(StringBuffer &sb);
    bool eat_with(StringBuffer &sb);
    bool eat_pattern(StringBuffer &sb);
    bool eat_and(StringBuffer &sb);
    bool eat_modifies(StringBuffer &sb);
    bool eat_uses(StringBuffer &sb);
    bool eat_calls(StringBuffer &sb);
    bool eat_calls_star(StringBuffer &sb);
    bool eat_parent(StringBuffer &sb);
    bool eat_parent_star(StringBuffer &sb);
    bool eat_follows(StringBuffer &sb);
    bool eat_follows_star(StringBuffer &sb);
    bool eat_next(StringBuffer &sb);
    bool eat_next_star(StringBuffer &sb);
    bool eat_affects(StringBuffer &sb);
    bool eat_affects_star(StringBuffer &sb);
    RelRefArgType eat_entRef(StringBuffer &sb);
    RelRefArgType eat_stmtRef(StringBuffer &sb);
    RelRefArgType eat_lineRef(StringBuffer &sb);
    RelRefArgType eat_varRef(StringBuffer &sb);
    void eat_entRef_varRef(RelRef &relRef, StringBuffer &sb,
            char **errorMsg) throw(ParseError);
    void error_set_relRef_arg(ParseError parseErr_, const RelRef &relRef,
            const char *which, const StringBuffer &sb, char **errorMsg)
                throw(ParseError);
    bool relRef_finalize(RelRef &relRef, char **errorMsg);
    bool eat_relRef_generic(RelRef &relRef, StringBuffer &sb,
        bool (PQLParser::*eat_relRef_string_M) (StringBuffer &sb),
        RelRefType relRefType,
        void (PQLParser::*eat_arg_M)
            (RelRef &relRef, StringBuffer &sb, char **errorMsg));
    void error_add_relRef(ParseError parseErr_, const RelRef &relRef,
            const StringBuffer &sb, char *errorMsg) throw(ParseError);
    bool eat_relRef_modifies(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_uses(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_calls(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_calls_star(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_parent(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_parent_star(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_follows(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_follows_star(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_next(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_next_star(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_affects(RelRef &relRef, StringBuffer &sb);
    bool eat_relRef_affects_star(RelRef &relRef, StringBuffer &sb);
    RelRef eat_relRef(StringBuffer &sb);
    bool eat_relCond(StringBuffer &sb) throw(ParseError);
    void eat_select_stwithpat(StringBuffer &sb);
    bool insert_syn(DesignEnt ent, const std::string &s) throw(ParseError);
    DesignEnt retrieve_syn_type(const std::string& s) const;
    DesignEnt string_to_entity(const std::string &s);
    AttrType string_to_attrType(const std::string &s) const;
    void error(ParseError parseErr_, ...) throw(ParseError);
    void warning(const char *s, ...) const;
    void valist_print(const char *pfx, const char *fmt, va_list ap)
            const throw();
    void print_error(va_list ap);

    int bufIdx;
    int bufLen;
    std::string buf;
    std::map<std::string, DesignEnt> entTable;
    std::vector<std::pair<DesignEnt, std::string> > entVec;
    ParseError parseErr;
    QueryInfo *qinfo;
    bool showWarnings;
    bool showErrors;
    PQLParseErrorStream parseErrorStream;

    std::map<std::string, DesignEnt> strToEnt;
    std::map<std::string, AttrType> strToAttrType;
};

// class QueryInfo

#define QINFO_ERROR_LEN 1000

class QueryInfo {
public:
    QueryInfo();
    QueryInfo(const std::map<std::string, DesignEnt>& etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    void reset(const std::map<std::string, DesignEnt> &etab,
        const std::vector<std::pair<DesignEnt, std::string> >& eVec);
    void set_select_boolean();
    void set_select_tuple();
    ParseError add_select_tuple(AttrRef attrRef);
    ParseError add_relRef(RelRef& relRef, char **errorMsg);
    void dump(void) const;
    void dump(FILE *f) const;
    std::string dump_to_string() const;

private:
    // entity declarations
    std::map<std::string, DesignEnt> entTable;
    std::vector<std::pair<DesignEnt, std::string> > entVec;
    SelectType selectType;
    std::vector<AttrRef> selectTuple;
    std::set<AttrRef, AttrRefCmp> selectTable;
    std::vector<std::pair<ClauseType, int> > evalOrder;
    std::vector<RelRef> relRefs;
    std::set<RelRef, RelRefCmp> relRefsSet;

    char errorBuf[QINFO_ERROR_LEN+5];

    void insert_relRef(const RelRef &relRef, char **errorMsg);
    DesignEnt retrieve_syn_type(const std::string &s) const;
    ParseError add_modifies_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_uses_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_calls_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_parent_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_follows_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_next_relRef(RelRef &relRef, char **errorMsg);
    ParseError add_affects_relRef(RelRef &relRef, char **errorMsg);
};

#endif