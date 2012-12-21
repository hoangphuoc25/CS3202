#ifndef T11_PQLPARSER_H
#define T11_PQLPARSER_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <set>
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

enum DesignEnt {
    ENT_PROC, ENT_STMTLST, ENT_STMT, ENT_ASSIGN, ENT_CALL,
    ENT_WHILE, ENT_IF, ENT_VAR, ENT_CONST, ENT_PROGLINE,
    ENT_INVALID
};

enum SelectType {
    SEL_TUPLE, SEL_BOOLEAN
};

#define ATTR_PROCNAME_STR "procName"
#define ATTR_VARNAME_STR  "varName"
#define ATTR_VALUE_STR    "value"
#define ATTR_STMTNO_STR   "stmt#"
#define ATTR_DEFAULT_STR  "default"
#define ATTR_INVALID_STR  "invalid"

enum AttrType {
    ATTR_PROCNAME, ATTR_VARNAME, ATTR_VALUE, ATTR_STMTNO,
    ATTR_INVALID, ATTR_DEFAULT
};

// Helper functions
const char *entity_type_to_string(DesignEnt entType);
const char *attrType_to_string(AttrType attrType);

struct AttrRef {
    std::string syn;
    DesignEnt entType;
    AttrType attr;
    AttrRef(): syn(""), entType(ENT_INVALID), attr(ATTR_INVALID) {}
    AttrRef(std::string s, DesignEnt et, AttrType a)
        : syn(s), entType(et), attr(a) {}
    void dump_to_sb(StringBuffer &sb) const {
        sb.append(entity_type_to_string(entType));
        sb.append(' ');
        sb.append(syn);
        if (attr != ATTR_DEFAULT) {
            sb.append(' ');
            sb.append(attrType_to_string(attr));
        }
    }
};

struct AttrRefCmp {
    bool operator()(const AttrRef &a, const AttrRef &b) const {
        if (a.syn != b.syn) {
            return a.syn < b.syn;
        } else if (a.entType != b.entType) {
            return a.entType < b.entType;
        } else {
            return a.attr < b.attr;
        }
    }
};

// forward declaration
class QueryInfo;

class PQLParser {
public:
    PQLParser();
    ~PQLParser();
    void parse(const std::string &s);

    QueryInfo *get_queryinfo() const;

    // For testing purposes
    int get_parse_errors() const;
    std::map<std::string, DesignEnt> get_ent_table() const;

private:
    PQLParser(const PQLParser &o);
    PQLParser& operator=(const PQLParser &o);

    void eat_decls();
    bool eat_decl_one();
    int eat_space();
    void eat_nonws_token(StringBuffer &sb);
    bool eat_one_char(char ch);
    bool eat_comma();
    bool eat_semicolon();
    bool eat_period();
    bool eat_lt();
    bool eat_gt();
    void eat_till_ws(StringBuffer &sb);
    bool eat_synonym(StringBuffer &sb);
    AttrRef eat_attrRef(StringBuffer &sb);
    bool eat_attrName(StringBuffer &sb);
    void eat_alpha(StringBuffer &sb);
    bool eat_alpha_string(StringBuffer &sb, const char *s);
    bool eat_alpha_strings(StringBuffer &sb, int nrStrs, ...);
    void eat_ident(StringBuffer &sb);
    bool eat_ident_string(StringBuffer &sb, const char *s);
    bool eat_string_till_ws(StringBuffer &sb, const char *s);
    bool eat_select(StringBuffer &sb);
    bool eat_select_tuple(StringBuffer &sb);
    AttrRef eat_select_tuple_elem(StringBuffer &sb);
    bool eat_select_boolean(StringBuffer &sb);
    bool eat_such_that(StringBuffer &sb);
    bool eat_with(StringBuffer &sb);
    bool eat_pattern(StringBuffer &sb);
    void eat_select_stwithpat(StringBuffer &sb);
    bool insert_syn(DesignEnt ent, const std::string &s);
    DesignEnt retrieve_syn_type(const std::string& s) const;
    DesignEnt string_to_entity(const std::string &s);
    AttrType string_to_attrType(const std::string &s) const;
    void error(const char *s, ...);

    int bufIdx;
    int bufLen;
    std::string buf;
    std::map<std::string, DesignEnt> entTable;
    std::vector<std::pair<DesignEnt, std::string> > entVec;
    int parseErrors;
    QueryInfo *qinfo;

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
    bool add_select_tuple(AttrRef attrRef, char **errorMsg);
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

    char errorBuf[QINFO_ERROR_LEN+5];
};

#endif