#ifndef T11_PQLPARSER_H
#define T11_PQLPARSER_H

#include <cstdarg>
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

#define S_TO_UINT_MAX 2147483647L
#define S_TO_UINT_EMPTY_STRING "string_to_uint - String is empty"
#define S_TO_UINT_WHITESPACE "string_to_uint - String consists of whitespace"
#define S_TO_UINT_TOO_LONG  "string_to_uint - String is too long (max 10 char)"
#define S_TO_UINT_OVERFLOW "string_to_uint - integer overflow. Max 2147483647"

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

enum RelRefType {
    REL_MODIFIES, REL_USES, REL_CALLS, REL_CALLS_STAR,
    REL_PARENT, REL_PARENT_STAR, REL_FOLLOWS, REL_FOLLOWS_STAR,
    REL_NEXT, REL_NEXT_STAR, REL_AFFECTS, REL_AFFECTS_STAR,
    REL_INVALID
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

enum ClauseType {
    SUCHTHAT_CLAUSE, WITH_CLAUSE, PATTERN_CLAUSE
};

enum RelRefArgType {
    RELARG_SYN, RELARG_STRING, REL_INT, REL_WILDCARD,
    RELARG_INVALID
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

    RelRef(): relType(REL_INVALID), argOneType(RELARG_INVALID),
                argOneSyn(ENT_INVALID), argOneString(), argOneInt(0),
                argTwoType(RELARG_INVALID), argTwoSyn(ENT_INVALID),
                argTwoString(), argTwoInt(0) {}

    RelRef(const RelRef &o) {
        if (this != &o) {
            this->relType = o.relType;
            this->argOneType = o.argOneType;
            switch (this->argOneType) {
            case RELARG_SYN:
                this->argOneSyn = o.argOneSyn;
                // fall through
            case RELARG_STRING:
                this->argOneString = o.argOneString;
                break;
            case REL_INT:
                this->argOneInt = o.argOneInt;
                break;
            }
            this->argTwoType = o.argTwoType;
            switch (this->argTwoType) {
            case RELARG_SYN:
                this->argTwoSyn = o.argTwoSyn;
                // fall through
            case RELARG_STRING:
                this->argTwoString = o.argTwoString;
                break;
            case REL_INT:
                this->argTwoInt = o.argTwoInt;
                break;
            }
        }
    }

    RelRef &operator=(const RelRef &o) {
        if (this != &o) {
            this->relType = o.relType;
            this->argOneType = o.argOneType;
            switch (this->argOneType) {
            case RELARG_SYN:
                this->argOneSyn = o.argOneSyn;
                // fall through
            case RELARG_STRING:
                this->argOneString = o.argOneString;
                break;
            case REL_INT:
                this->argOneInt = o.argOneInt;
                break;
            }
            this->argTwoType = o.argTwoType;
            switch (this->argTwoType) {
            case RELARG_SYN:
                this->argTwoSyn = o.argTwoSyn;
                // fall through
            case RELARG_STRING:
                this->argTwoString = o.argTwoString;
                break;
            case REL_INT:
                this->argTwoInt = o.argTwoInt;
                break;
            }
        }
        return *this;
    }

    ~RelRef() {}

    bool set_arg_one(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg) {
        return this->set_arg(1, argType, sb, errorMsg);
    }

    bool set_arg_two(RelRefArgType argType, StringBuffer &sb,
            char **errorMsg) {
        return this->set_arg(2, argType, sb, errorMsg);
    }

    bool set_arg(int which, RelRefArgType argType, StringBuffer &sb,
            char **errorMsg) {
        bool ret = true;
        switch (argType) {
        case RELARG_SYN:
            if (which == 1) {
                this->argOneSyn = ENT_INVALID;
            } else {
                this->argTwoSyn = ENT_INVALID;
            }
            // fall through
        case RELARG_STRING:
            if (which == 1) {
                this->argOneString = sb.toString();
            } else {
                this->argTwoString = sb.toString();
            }
            break;
        case REL_INT:
            if (which == 1) {
                if (!string_to_uint(sb.toString(), &argOneInt, errorMsg)) {
                    ret = false;
                }
            } else {
                if (!string_to_uint(sb.toString(), &argTwoInt, errorMsg)) {
                    ret = false;
                }
            }
            break;
        case REL_WILDCARD:
            if (which == 1) {
                this->argOneType = REL_WILDCARD;
            } else {
                this->argTwoType = REL_WILDCARD;
            }
            break;
        case REL_INVALID:
            ret = false;
            if (errorMsg) {
                if (which == 1) {
                    *errorMsg = strdup(SET_ARG_ONE_INVALID);
                } else {
                    *errorMsg = strdup(SET_ARG_TWO_INVALID);
                }
            }
            break;
        }
        if (ret) {
            if (which == 1) {
                this->argOneType = argType;
            } else {
                this->argTwoType = argType;
            }
        }
        return ret;
    }

    std::string dump(void) const {
        StringBuffer sb;
        sb.append(relRefType_to_string(this->relType));
        sb.append('(');
        switch (this->argOneType) {
        case RELARG_SYN:
            sb.append(this->argOneString);
            break;
        case RELARG_STRING:
            sb.append('"');
            sb.append(this->argOneString);
            sb.append('"');
            break;
        case REL_INT:
            sb.append_int(this->argOneInt);
            break;
        case REL_WILDCARD:
            sb.append('_');
            break;
        }
        sb.append(',');
        switch (this->argTwoType) {
        case RELARG_SYN:
            sb.append(this->argTwoString);
            break;
        case RELARG_STRING:
            sb.append('"');
            sb.append(this->argTwoString);
            sb.append('"');
            break;
        case REL_INT:
            sb.append_int(this->argTwoInt);
            break;
        case REL_WILDCARD:
            sb.append('_');
            break;
        }
        sb.append(')');
        return sb.toString();
    }

    static bool valid(const struct RelRef &r) {
        return r.relType != REL_INVALID;
    }
    static const char *SET_ARG_ONE_INVALID;
    static const char *SET_ARG_TWO_INVALID;
};

// For comparing RelRef so that we will not insert repeated relref
struct RelRefCmp {
    bool operator()(const RelRef &a, const RelRef &b) const {
        #define RELREF_ARGTWO_CMP() do {\
            if (a.argTwoType == RELARG_SYN) {\
                if (a.argTwoSyn != b.argTwoSyn) {\
                    return a.argTwoSyn < b.argTwoSyn;\
                }\
                return a.argTwoString < b.argTwoString;\
            } else if (a.argTwoType == RELARG_STRING) {\
                return a.argTwoString < b.argTwoString;\
            } else if (a.argTwoType == REL_INT) {\
                return a.argTwoInt < b.argTwoInt;\
            } else {\
                return false;\
            }\
        } while(0)

        int cmp;
        if (a.relType != b.relType) {
            return a.relType < b.relType;
        } else if (a.argOneType != b.argOneType) {
            return a.argOneType < b.argOneType;
        } else if (a.argTwoType != b.argTwoType) {
            return a.argTwoType < b.argTwoType;
        } else if (a.argOneType == RELARG_SYN) {
            if (a.argOneSyn != b.argOneSyn) {
                return a.argOneSyn < b.argOneSyn;
            }
            cmp = a.argOneString.compare(b.argOneString);
            if (cmp != 0) {
                return (cmp < 0);
            }
            RELREF_ARGTWO_CMP();

        } else if (a.argOneType == RELARG_STRING) {
            cmp = a.argOneString.compare(b.argOneString);
            if (cmp != 0) {
                return (cmp < 0);
            }
            RELREF_ARGTWO_CMP();
        } else if (a.argOneType == REL_INT) {
            if (a.argOneInt != b.argOneInt) {
                return a.argOneInt < b.argOneInt;
            }
            RELREF_ARGTWO_CMP();
        } else if (a.argOneType == REL_WILDCARD) {
            RELREF_ARGTWO_CMP();
        }

        #undef RELREF_ARGTWO_CMP
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
    bool eat_lparen();
    bool eat_rparen();
    bool eat_underscore();
    bool eat_dquote();
    void eat_till_ws(StringBuffer &sb);
    bool eat_synonym(StringBuffer &sb);
    AttrRef eat_attrRef(StringBuffer &sb);
    bool eat_attrName(StringBuffer &sb);
    void eat_alpha(StringBuffer &sb);
    bool eat_alpha_string(StringBuffer &sb, const char *s);
    bool eat_alpha_strings(StringBuffer &sb, int nrStrs, ...);
    void eat_alpha_star(StringBuffer &sb);
    bool eat_alpha_star_string(StringBuffer &sb, const char *s);
    void eat_ident(StringBuffer &sb);
    bool eat_ident_string(StringBuffer &sb, const char *s);
    bool eat_string_till_ws(StringBuffer &sb, const char *s);
    int eat_int(StringBuffer &sb);
    bool eat_select(StringBuffer &sb);
    bool eat_select_tuple(StringBuffer &sb);
    AttrRef eat_select_tuple_elem(StringBuffer &sb);
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
    bool relRef_finalize(RelRef &relRef, char **errorMsg);
    RelRef eat_relRef_modifies(StringBuffer &sb);
    RelRef eat_relRef_uses(StringBuffer &sb);
    RelRef eat_relRef_calls(StringBuffer &sb);
    RelRef eat_relRef_calls_star(StringBuffer &sb);
    RelRef eat_relRef_parent(StringBuffer &sb);
    RelRef eat_relRef_parent_star(StringBuffer &sb);
    RelRef eat_relRef_follows(StringBuffer &sb);
    RelRef eat_relRef_follows_star(StringBuffer &sb);
    RelRef eat_relRef_next(StringBuffer &sb);
    RelRef eat_relRef_next_star(StringBuffer &sb);
    RelRef eat_relRef_affects(StringBuffer &sb);
    RelRef eat_relRef_affects_star(StringBuffer &sb);
    RelRef eat_relRef(StringBuffer &sb);
    bool eat_relCond(StringBuffer &sb);
    void eat_select_stwithpat(StringBuffer &sb);
    bool insert_syn(DesignEnt ent, const std::string &s);
    DesignEnt retrieve_syn_type(const std::string& s) const;
    DesignEnt string_to_entity(const std::string &s);
    AttrType string_to_attrType(const std::string &s) const;
    void error(const char *s, ...);
    void warning(const char *s, ...) const;
    void valist_print(const char *pfx, const char *fmt, va_list ap) const;

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
    bool add_relRef(RelRef& relRef, char **errorMsg);
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
    bool add_modifies_relRef(RelRef &relRef, char **errorMsg);
    bool add_uses_relRef(RelRef &relRef, char **errorMsg);
    bool add_calls_relRef(RelRef &relRef, char **errorMsg);
    bool add_parent_relRef(RelRef &relRef, char **errorMsg);
    bool add_follows_relRef(RelRef &relRef, char **errorMsg);
    bool add_next_relRef(RelRef &relRef, char **errorMsg);
    bool add_affects_relRef(RelRef &relRef, char **errorMsg);
};

#endif