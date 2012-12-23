#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <string>
#include <map>
#include <utility>
#include "PQLParser.h"
#include "StringBuffer.h"

using std::string;
using std::map;
using std::vector;
using std::set;
using std::pair;
using std::make_pair;

//////////////////////////////////////////////////////////////////////
// AttrRef
//////////////////////////////////////////////////////////////////////

AttrRef::AttrRef(): syn(""), entType(ENT_INVALID), attr(ATTR_INVALID) {}

AttrRef::AttrRef(string s, DesignEnt et, AttrType a)
    : syn(s), entType(et), attr(a) {}

void AttrRef::dump_to_sb(StringBuffer &sb) const
{
    sb.append(entity_type_to_string(entType));
    sb.append(' ');
    sb.append(syn);
    if (attr != ATTR_DEFAULT) {
        sb.append(' ');
        sb.append(attrType_to_string(attr));
    }
}

bool AttrRefCmp::operator()(const AttrRef &a, const AttrRef &b) const
{
    if (a.syn != b.syn) {
        return a.syn < b.syn;
    } else if (a.entType != b.entType) {
        return a.entType < b.entType;
    } else {
        return a.attr < b.attr;
    }
}

//////////////////////////////////////////////////////////////////////
// RelRef
//////////////////////////////////////////////////////////////////////

const char *RelRef::SET_ARG_ONE_INVALID =
    "RelRef::set_arg_one - arg one has invalid type";
const char *RelRef::SET_ARG_TWO_INVALID =
    "RelRef::set_arg_two - arg two has invalid type";

bool RelRef::valid(const struct RelRef &r) {
    return r.relType != REL_INVALID;
}

RelRef::RelRef(): relType(REL_INVALID), argOneType(RELARG_INVALID),
    argOneSyn(ENT_INVALID), argOneString(), argOneInt(0),
    argTwoType(RELARG_INVALID), argTwoSyn(ENT_INVALID),
    argTwoString(), argTwoInt(0) {}

RelRef::RelRef(const RelRef &o)
{
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
        case RELARG_INT:
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
        case RELARG_INT:
            this->argTwoInt = o.argTwoInt;
            break;
        }
    }
}

RelRef& RelRef::operator=(const RelRef &o)
{
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
        case RELARG_INT:
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
        case RELARG_INT:
            this->argTwoInt = o.argTwoInt;
            break;
        }
    }
    return *this;
}

RelRef::~RelRef() {}

bool RelRef::set_arg_one(RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
    return this->set_arg(1, argType, sb, errorMsg);
}

bool RelRef::set_arg_two(RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
    return this->set_arg(2, argType, sb, errorMsg);
}

bool RelRef::set_arg(int which, RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
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
    case RELARG_INT:
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
    case RELARG_WILDCARD:
        if (which == 1) {
            this->argOneType = RELARG_WILDCARD;
        } else {
            this->argTwoType = RELARG_WILDCARD;
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

string RelRef::dump(void) const
{
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
    case RELARG_INT:
        sb.append_int(this->argOneInt);
        break;
    case RELARG_WILDCARD:
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
    case RELARG_INT:
        sb.append_int(this->argTwoInt);
        break;
    case RELARG_WILDCARD:
        sb.append('_');
        break;
    }
    sb.append(')');
    return sb.toString();
}

bool RelRefCmp::operator()(const RelRef &a, const RelRef &b) const
{
    #define RELREF_ARGTWO_CMP() do {\
        if (a.argTwoType == RELARG_SYN) {\
            if (a.argTwoSyn != b.argTwoSyn) {\
                return a.argTwoSyn < b.argTwoSyn;\
            }\
            return a.argTwoString < b.argTwoString;\
        } else if (a.argTwoType == RELARG_STRING) {\
            return a.argTwoString < b.argTwoString;\
        } else if (a.argTwoType == RELARG_INT) {\
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
    } else if (a.argOneType == RELARG_INT) {
        if (a.argOneInt != b.argOneInt) {
            return a.argOneInt < b.argOneInt;
        }
        RELREF_ARGTWO_CMP();
    } else if (a.argOneType == RELARG_WILDCARD) {
        RELREF_ARGTWO_CMP();
    }

    #undef RELREF_ARGTWO_CMP
}

//////////////////////////////////////////////////////////////////////
// PQL Parser
//////////////////////////////////////////////////////////////////////

#define RESTORE_AND_RET(retVal, savePtr) do {\
    this->bufIdx = savePtr;\
    return retVal;\
} while(0)

PQLParser::PQLParser(): parseErrors(0)
{
    strToEnt[ENT_PROC_STR] = ENT_PROC;
    strToEnt[ENT_STMTLST_STR] = ENT_STMTLST;
    strToEnt[ENT_STMT_STR] = ENT_STMT;
    strToEnt[ENT_ASSIGN_STR] = ENT_ASSIGN;
    strToEnt[ENT_CALL_STR] = ENT_CALL;
    strToEnt[ENT_WHILE_STR] = ENT_WHILE;
    strToEnt[ENT_IF_STR] = ENT_IF;
    strToEnt[ENT_VAR_STR] = ENT_VAR;
    strToEnt[ENT_CONST_STR] = ENT_CONST;
    strToEnt[ENT_PROGLINE_STR] = ENT_PROGLINE;

    strToAttrType[ATTR_PROCNAME_STR] = ATTR_PROCNAME;
    strToAttrType[ATTR_VARNAME_STR] = ATTR_VARNAME;
    strToAttrType[ATTR_VALUE_STR] = ATTR_VALUE;
    strToAttrType[ATTR_STMTNO_STR] = ATTR_STMTNO;
    qinfo = new QueryInfo();
}

PQLParser::~PQLParser()
{
    if (qinfo) {
        delete qinfo;
    }
}

int PQLParser::get_parse_errors() const
{
    return this->parseErrors;
}

map<string, DesignEnt> PQLParser::get_ent_table() const
{
    return this->entTable;
}

QueryInfo *PQLParser::get_queryinfo() const
{
    return this->qinfo;
}

DesignEnt PQLParser::string_to_entity(const string &s)
{
    if (strToEnt.find(s) != strToEnt.end()) {
        return strToEnt[s];
    } else {
        return ENT_INVALID;
    }
}

AttrType PQLParser::string_to_attrType(const string &s) const
{
    map<string, AttrType>::const_iterator it = this->strToAttrType.find(s);
    if (it == this->strToAttrType.end()) {
        return ATTR_INVALID;
    } else {
        return it->second;
    }
}

bool PQLParser::insert_syn(DesignEnt entType, const std::string &s)
{
    if (s.size() <= 0) {
        this->error("Zero length entity of type %s",
            entity_type_to_string(entType));
        return false;
    }
    map<string, DesignEnt>::iterator it = this->entTable.find(s);
    if (it != this->entTable.end()) {
        const char *tmpS = s.c_str();
        this->error("design entity \"%s\" of type \"%s\" was"
            "previously declared (%s %s)",
            entity_type_to_string(entType),
            tmpS, entity_type_to_string(it->second), tmpS);
        return false;
    } else {
        this->entTable[s] = entType;
        this->entVec.push_back(pair<DesignEnt, string>(entType, s));
        return true;
    }
}

DesignEnt PQLParser::retrieve_syn_type(const string &s) const
{
    map<string, DesignEnt>::const_iterator it = this->entTable.find(s);
    if (it == this->entTable.end()) {
        return ENT_INVALID;
    } else {
        return it->second;
    }
}

const char *relRefType_to_string(RelRefType relType)
{
    switch (relType) {
    case REL_MODIFIES:
        return MODIFIES_STR;
    case REL_USES:
        return USES_STR;
    case REL_CALLS:
        return CALLS_STR;
    case REL_CALLS_STAR:
        return CALLS_STAR_STR;
    case REL_PARENT:
        return PARENT_STR;
    case REL_PARENT_STAR:
        return PARENT_STAR_STR;
    case REL_FOLLOWS:
        return FOLLOWS_STR;
    case REL_FOLLOWS_STAR:
        return FOLLOWS_STAR_STR;
    case REL_NEXT:
        return NEXT_STR;
    case REL_NEXT_STAR:
        return NEXT_STAR_STR;
    case REL_AFFECTS:
        return AFFECTS_STR;
    case REL_AFFECTS_STAR:
        return AFFECTS_STAR_STR;
    default:
        return INVALID_STR;
    }
}

const char *entity_type_to_string(DesignEnt entType)
{
    switch (entType) {
    case ENT_PROC:
        return ENT_PROC_STR;
    case ENT_STMTLST:
        return ENT_STMTLST_STR;
    case ENT_STMT:
        return ENT_STMT_STR;
    case ENT_ASSIGN:
        return ENT_ASSIGN_STR;
    case ENT_CALL:
        return ENT_CALL_STR;
    case ENT_WHILE:
        return ENT_WHILE_STR;
    case ENT_IF:
        return ENT_IF_STR;
    case ENT_VAR:
        return ENT_VAR_STR;
    case ENT_CONST:
        return ENT_CONST_STR;
    case ENT_PROGLINE:
        return ENT_PROGLINE_STR;
    case ENT_INVALID:
        return ENT_INVALID_STR;
    }
}

const char *attrType_to_string(AttrType attrType)
{
    switch (attrType) {
    case ATTR_PROCNAME:
        return ATTR_PROCNAME_STR;
    case ATTR_VARNAME:
        return ATTR_VARNAME_STR;
    case ATTR_VALUE:
        return ATTR_VALUE_STR;
    case ATTR_STMTNO:
        return ATTR_STMTNO_STR;
    case ATTR_DEFAULT:
        return ATTR_DEFAULT_STR;
    default:
        return ATTR_INVALID_STR;
    }
}

bool string_to_uint(const string& s, int *res, char **errorMsg)
{
    int len = s.size();
    if (len <= 0) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_EMPTY_STRING);
        }
        return false;
    }
    int idx = 0;
    while (idx < len && isspace(s[idx])) {
        idx++;
    }
    if (idx >= len) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_WHITESPACE);
        }
        return false;
    }
    if (len - idx > 10) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_TOO_LONG);
        }
    }
    long long tmp = 0;
    while (idx < len && isdigit(s[idx])) {
        tmp = tmp * 10 + (s[idx++] - '0');
    }
    if (tmp > S_TO_UINT_MAX) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_OVERFLOW);
        }
        return false;
    }
    if (res) {
        *res = (int)tmp;
    }
    return true;
}

void PQLParser::error(const char *s, ...)
{
    this->parseErrors++;
    va_list ap;
    va_start(ap, s);
    this->valist_print("Error: ", s, ap);
    va_end(ap);
}

void PQLParser::warning(const char *s, ...) const
{
    va_list ap;
    va_start(ap, s);
    this->valist_print("Warning: ", s, ap);
    va_end(ap);
}

void PQLParser::valist_print(const char *pfx, const char *fmt,
        va_list ap) const
{
    fprintf(stderr, "%s", pfx);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

int PQLParser::eat_space()
{
    int spaces = 0;
    while (this->bufIdx < this->bufLen &&
            isspace(this->buf[this->bufIdx])) {
        this->bufIdx++;
        spaces++;
    }
    return spaces;
}

bool PQLParser::eat_one_char(char ch)
{
    int saveIdx = this->bufIdx;
    if (this->bufIdx < this->bufLen &&
            this->buf[this->bufIdx] == ch) {
        this->bufIdx++;
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

int PQLParser::eat_nonws_token(StringBuffer &sb)
{
    sb.clear();
    int ate = 0;
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

int PQLParser::eat_till_ws(StringBuffer &sb)
{
    int ate = 0;
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

bool PQLParser::eat_string_till_ws(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_till_ws(sb);
    if (!sb.strcmp(str)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

int PQLParser::eat_alpha(StringBuffer &sb)
{
    int ate = 0;
    while (this->bufIdx < this->bufLen &&
            isalpha(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

bool PQLParser::eat_alpha_string(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_alpha(sb);
    if (!sb.strcmp(str)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

bool PQLParser::eat_alpha_strings(StringBuffer &sb, int nrStrs, ...)
{
    if (nrStrs <= 0) {
        return true;
    }
    int saveIdx = this->bufIdx;
    const char *s;
    va_list ap;
    va_start(ap, nrStrs);
    s = va_arg(ap, const char *);
    this->eat_space();
    if (!this->eat_alpha_string(sb, s)) {
        va_end(ap);
        RESTORE_AND_RET(false, saveIdx);
    }
    for (int i = 1; i < nrStrs; i++) {
        s = va_arg(ap, const char *);
        if (this->eat_space() <= 0) {
            va_end(ap);
            RESTORE_AND_RET(false, saveIdx);
        }
        if (!this->eat_alpha_string(sb, s)) {
            va_end(ap);
            RESTORE_AND_RET(false, saveIdx);
        }
    }
    va_end(ap);
    return true;
}

int PQLParser::eat_alpha_star(StringBuffer &sb)
{
    int ate = 0;
    while (this->bufIdx < this->bufLen &&
            (isalpha(this->buf[this->bufIdx]) ||
             this->buf[this->bufIdx] == '*')) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

bool PQLParser::eat_alpha_star_string(StringBuffer &sb, const char *s)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_alpha_star(sb);
    if (!sb.strcmp(s)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

int PQLParser::eat_ident(StringBuffer &sb)
{
    int ate = 0;
    while (this->bufIdx < this->bufLen &&
            (isalnum(this->buf[this->bufIdx]) ||
             this->buf[this->bufIdx] == '#')) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

bool PQLParser::eat_ident_string(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_ident(sb);
    if (!sb.strcmp(str)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

int PQLParser::eat_int(StringBuffer &sb)
{
    if (this->bufIdx < this->bufLen &&
            isdigit(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    } else {
        return 0;
    }
    int cnt = 1;
    while (this->bufIdx < this->bufLen &&
            isdigit(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        cnt++;
    }
    return cnt;
}

bool PQLParser::eat_select(StringBuffer &sb)
{
    return this->eat_string_till_ws(sb, SELECT_STR);
}

bool PQLParser::eat_comma()
{
    return this->eat_one_char(',');
}

bool PQLParser::eat_semicolon()
{
    return this->eat_one_char(';');
}

bool PQLParser::eat_period()
{
    return this->eat_one_char('.');
}

bool PQLParser::eat_lt()
{
    return this->eat_one_char('<');
}

bool PQLParser::eat_gt()
{
    return this->eat_one_char('>');
}

bool PQLParser::eat_lparen()
{
    return this->eat_one_char('(');
}

bool PQLParser::eat_rparen()
{
    return this->eat_one_char(')');
}

bool PQLParser::eat_underscore()
{
    return this->eat_one_char('_');
}

bool PQLParser::eat_dquote()
{
    return this->eat_one_char('"');
}

bool PQLParser::eat_synonym(StringBuffer &sb)
{
    sb.clear();
    if (this->bufIdx < this->bufLen &&
            isalpha(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    } else {
        return false;
    }
    while (this->bufIdx < this->bufLen &&
            (isalnum(this->buf[this->bufIdx]) ||
                        this->buf[this->bufIdx] == '#')) {
        sb.append(this->buf[this->bufIdx++]);
    }
    return true;
}

bool PQLParser::eat_attrName(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    return ((this->eat_ident_string(sb, ATTR_PROCNAME_STR))
            ||
            (this->bufIdx = saveIdx,
             this->eat_ident_string(sb, ATTR_VARNAME_STR))
            ||
            (this->bufIdx = saveIdx,
             this->eat_ident_string(sb, ATTR_VALUE_STR))
            ||
            (this->bufIdx = saveIdx,
             this->eat_ident_string(sb, ATTR_STMTNO_STR))
            ||
            (this->bufIdx = saveIdx, false));
}

AttrRef PQLParser::eat_attrRef(StringBuffer &sb)
{
    sb.clear();
    int saveIdx = this->bufIdx;
    string syn, attr;
    bool ok;
    if (this->eat_synonym(sb)) {
        syn = sb.toString();
        if (!this->eat_period()) {
            RESTORE_AND_RET(AttrRef(), saveIdx);
        }
        sb.clear();
        if (!this->eat_attrName(sb)) {
            RESTORE_AND_RET(AttrRef(), saveIdx);
        }
        attr = sb.toString();
        // "type check"
        DesignEnt entType = this->retrieve_syn_type(syn);
        if (entType == ENT_INVALID) {
            RESTORE_AND_RET(AttrRef(), saveIdx);;
        }
        AttrType attrType = this->string_to_attrType(attr);
        if (attrType == ATTR_INVALID) {
            RESTORE_AND_RET(AttrRef(), saveIdx);
        }
        ok = false;
        switch (attrType) {
        case ATTR_PROCNAME:
            ok = (entType == ENT_PROC || entType == ENT_CALL);
            break;
        case ATTR_VARNAME:
            ok = (entType == ENT_VAR);
            break;
        case ATTR_VALUE:
            ok = (entType == ENT_CONST);
            break;
        case ATTR_STMTNO:
            ok = (entType == ENT_STMT || entType == ENT_STMTLST ||
                    entType == ENT_ASSIGN || entType == ENT_CALL |
                    entType == ENT_WHILE || entType == ENT_IF ||
                    entType == ENT_PROGLINE);
            break;
        }
        if (ok) {
            return AttrRef(syn, entType, attrType);
        } else {
            RESTORE_AND_RET(AttrRef(), saveIdx);
        }
    } else {
        RESTORE_AND_RET(AttrRef(), saveIdx);
    }
}

bool PQLParser::eat_decl_one()
{
    #define EAT_SYN() do {\
        ret = this->eat_synonym(sb);\
        s = sb.toString();\
        if (!ret) {\
            if (s.size() == 0) {\
                this->error("Missing design entity for \"%s\"",\
                    entStr.c_str());\
            } else {\
                this->eat_till_ws(sb);\
                this->error("Expected synonym, got \"%s\"",\
                    sb.toString().c_str());\
            }\
            RESTORE_AND_RET(false, saveIdx);\
        }\
        if (!this->insert_syn(entType, s)) {\
            RESTORE_AND_RET(false, saveIdx);\
        }\
    } while(0)

    StringBuffer sb;
    string s;
    bool ret;
    int saveIdx;
    this->eat_space();
    saveIdx = this->bufIdx;
    this->eat_nonws_token(sb);
    string entStr = sb.toString();
    DesignEnt entType = string_to_entity(entStr);
    if (entType == ENT_INVALID) {
        RESTORE_AND_RET(false, saveIdx);
    }
    if (this->eat_space() <= 0) {
        this->error("Expected whitespace between design entity and synonym");
        RESTORE_AND_RET(false, saveIdx);
    }
    EAT_SYN();
    while (1) {
        this->eat_space();
        if (!this->eat_comma()) {
            break;
        }
        this->eat_space();
        EAT_SYN();
    }
    this->eat_space();
    if (!this->eat_semicolon()) {
        this->error("Missing terminator ';'");
        RESTORE_AND_RET(false, saveIdx);
    }
    return true;

    #undef EAT_SYN
}

void PQLParser::eat_decls()
{
    while (this->eat_decl_one()) {
        // nothing
    }
}

bool PQLParser::eat_select_boolean(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    if (this->eat_string_till_ws(sb, BOOLEAN_STR)) {
        return true;
    }
    RESTORE_AND_RET(false, saveIdx);
}

AttrRef PQLParser::eat_select_tuple_elem(StringBuffer &sb)
{
    this->eat_space();
    int saveIdx = this->bufIdx;
    sb.clear();
    AttrRef attrRef = this->eat_attrRef(sb);
    if (attrRef.attr != ATTR_INVALID) {
        return attrRef;
    }
    sb.clear();
    this->bufIdx = saveIdx;
    if (this->eat_synonym(sb)) {
        string syn = sb.toString();
        DesignEnt entType = this->retrieve_syn_type(syn);
        if (entType != ENT_INVALID) {
            return AttrRef(syn, entType, ATTR_DEFAULT);
        }
    }
    RESTORE_AND_RET(AttrRef(), saveIdx);
}

bool PQLParser::eat_select_tuple(StringBuffer &sb)
{
    this->eat_space();
    int saveIdx = this->bufIdx;
    char *errorMsg = NULL;
    sb.clear();
    // 1 element
    AttrRef attrRef = this->eat_select_tuple_elem(sb);
    if (attrRef.attr != ATTR_INVALID) {
        this->qinfo->set_select_tuple();
        if (!this->qinfo->add_select_tuple(attrRef, &errorMsg)) {
            this->error(errorMsg);
            free(errorMsg);
            RESTORE_AND_RET(false, saveIdx);
        }
        return true;
    }
    // multiple elements
    this->bufIdx = saveIdx;
    if (!this->eat_lt()) {
        RESTORE_AND_RET(false, saveIdx);
    }
    this->eat_space();
    attrRef = this->eat_select_tuple_elem(sb);
    if (attrRef.attr == ATTR_INVALID) {
        RESTORE_AND_RET(false, saveIdx);
    }
    this->qinfo->set_select_tuple();
    if (!this->qinfo->add_select_tuple(attrRef, &errorMsg)) {
        this->error(errorMsg);
        free(errorMsg);
        RESTORE_AND_RET(false, saveIdx);
    }
    while (1) {
        this->eat_space();
        if (!this->eat_comma()) {
            break;
        }
        this->eat_space();
        sb.clear();
        attrRef = this->eat_select_tuple_elem(sb);
        if (attrRef.attr == ATTR_INVALID) {
            RESTORE_AND_RET(false, saveIdx);
        }
        errorMsg = NULL;
        if (!this->qinfo->add_select_tuple(attrRef, &errorMsg)) {
            this->error(errorMsg);
            free(errorMsg);
            RESTORE_AND_RET(false, saveIdx);
        }
    }
    this->eat_space();
    if (!this->eat_gt()) {
        printf("cur buf = %s\n", this->buf.c_str() + this->bufIdx);
        RESTORE_AND_RET(false, saveIdx);
    }
    return true;
}

bool PQLParser::eat_such_that(StringBuffer &sb)
{
    return this->eat_alpha_strings(sb, 2, SUCH_STR, THAT_STR);
}

bool PQLParser::eat_with(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, WITH_STR);
}

bool PQLParser::eat_pattern(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, PATTERN_STR);
}

bool PQLParser::eat_and(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, AND_STR);
}

bool PQLParser::eat_modifies(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, MODIFIES_STR);
}

bool PQLParser::eat_uses(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, USES_STR);
}

bool PQLParser::eat_calls(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, CALLS_STAR_STR);
}

bool PQLParser::eat_calls_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, CALLS_STAR_STR);
}

bool PQLParser::eat_parent(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, PARENT_STR);
}

bool PQLParser::eat_parent_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, PARENT_STAR_STR);
}

bool PQLParser::eat_follows(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, FOLLOWS_STR);
}

bool PQLParser::eat_follows_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, FOLLOWS_STAR_STR);
}

bool PQLParser::eat_next(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, NEXT_STR);
}

bool PQLParser::eat_next_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, NEXT_STAR_STR);
}

bool PQLParser::eat_affects(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, AFFECTS_STR);
}

bool PQLParser::eat_affects_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, AFFECTS_STAR_STR);
}

RelRefArgType PQLParser::eat_entRef(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    if (this->eat_synonym(sb)) {
        return RELARG_SYN;
    } else if (this->eat_underscore()) {
        return RELARG_WILDCARD;
    } else if (this->eat_dquote()) {
        sb.clear();
        if (this->eat_ident(sb) > 0 && this->eat_dquote()) {
            return RELARG_STRING;
        }
    }
    sb.clear();
    this->bufIdx = saveIdx;
    if (this->eat_int(sb) > 0) {
        return RELARG_INT;
    }
    RESTORE_AND_RET(RELARG_INVALID, saveIdx);
}

RelRefArgType PQLParser::eat_stmtRef(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    if (this->eat_synonym(sb)) {
        return RELARG_SYN;
    } else if (this->eat_underscore()) {
        return RELARG_WILDCARD;
    } else if (this->eat_int(sb)) {
        return RELARG_INT;
    }
    RESTORE_AND_RET(RELARG_INVALID, saveIdx);
}

RelRefArgType PQLParser::eat_lineRef(StringBuffer &sb)
{
    return this->eat_stmtRef(sb);
}

RelRefArgType PQLParser::eat_varRef(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    if (this->eat_synonym(sb)) {
        return RELARG_SYN;
    } else if (this->eat_underscore()) {
        return RELARG_WILDCARD;
    } else if (this->eat_dquote()) {
        sb.clear();
        if (this->eat_ident(sb) > 0 && this->eat_dquote()) {
            return RELARG_STRING;
        }
    }
    RESTORE_AND_RET(RELARG_INVALID, saveIdx);
}

RelRef PQLParser::eat_relRef_modifies(StringBuffer &sb)
{
    RelRef relRef;
    RelRefArgType argType;
    char *errorMsg = NULL;
    int saveIdx = this->bufIdx;
    sb.clear();
    if (!this->eat_modifies(sb)) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    relRef.relType = REL_MODIFIES;
    this->eat_space();
    if (!this->eat_lparen()) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    this->eat_space();
    argType = this->eat_entRef(sb);
    if (argType == RELARG_INVALID) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    if (!relRef.set_arg_one(argType, sb, &errorMsg)) {
        if (errorMsg) {
            this->error(errorMsg);
            free(errorMsg);
            errorMsg = NULL;
        }
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    this->eat_space();
    if (!this->eat_comma()) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    this->eat_space();
    sb.clear();
    errorMsg = NULL;
    argType = this->eat_varRef(sb);
    if (argType == RELARG_INVALID) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    if (!relRef.set_arg_two(argType, sb, &errorMsg)) {
        if (errorMsg) {
            this->error(errorMsg);
            free(errorMsg);
            errorMsg = NULL;
        }
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    this->eat_space();
    if (!this->eat_rparen()) {
        RESTORE_AND_RET(RelRef(), saveIdx);
    }
    return relRef;
}

RelRef PQLParser::eat_relRef_uses(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_calls(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_calls_star(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_parent(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_parent_star(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_follows(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_follows_star(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_next(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_next_star(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_affects(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef_affects_star(StringBuffer &sb)
{
    // TODO: Fill in
    return RelRef();
}

RelRef PQLParser::eat_relRef(StringBuffer &sb)
{
    #define EAT_RELREF_METHOD(method) do {\
        this->bufIdx = saveIdx;\
        relRef = this->method(sb);\
        if (RelRef::valid(relRef)) {\
            errorMsg = NULL;\
            if (!this->qinfo->add_relRef(relRef, &errorMsg)) {\
                this->error(errorMsg);\
                free(errorMsg);\
                RESTORE_AND_RET(RelRef(), saveIdx);\
            } else {\
                if (errorMsg) {\
                    this->warning(errorMsg);\
                    free(errorMsg);\
                }\
            }\
            return relRef;\
        }\
    } while(0)

    int saveIdx = this->bufIdx;
    RelRef relRef;
    char *errorMsg;
    EAT_RELREF_METHOD(eat_relRef_modifies);
    EAT_RELREF_METHOD(eat_relRef_uses);
    EAT_RELREF_METHOD(eat_relRef_calls_star);
    EAT_RELREF_METHOD(eat_relRef_calls);
    EAT_RELREF_METHOD(eat_relRef_parent_star);
    EAT_RELREF_METHOD(eat_relRef_parent);
    EAT_RELREF_METHOD(eat_relRef_follows_star);
    EAT_RELREF_METHOD(eat_relRef_follows);
    EAT_RELREF_METHOD(eat_relRef_next_star);
    EAT_RELREF_METHOD(eat_relRef_next);
    EAT_RELREF_METHOD(eat_relRef_affects_star);
    EAT_RELREF_METHOD(eat_relRef_affects);
    return RelRef();

    #undef EAT_RELREF_METHOD
}

bool PQLParser::eat_relCond(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    RelRef relRef;
    if (this->eat_space() <= 0) {
        RESTORE_AND_RET(false, saveIdx);
    }
    relRef = this->eat_relRef(sb);
    if (!RelRef::valid(relRef)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    while (1) {
        saveIdx = this->bufIdx;
        if (this->eat_space() <= 0) {
            this->bufIdx = saveIdx;
            break;
        }
        if (!this->eat_and(sb)) {
            this->bufIdx = saveIdx;
            break;
        }
        if (this->eat_space() <= 0) {
            this->bufIdx = saveIdx;
            break;
        }
        relRef = this->eat_relRef(sb);
        if (!RelRef::valid(relRef)) {
            this->bufIdx = saveIdx;
            break;
        }
    }
    return true;
}

void PQLParser::eat_select_stwithpat(StringBuffer &sb)
{
    if (this->bufIdx >= this->bufLen) {
        return;
    }
    int saveIdx = this->bufIdx;
    while (1) {
        if (this->eat_space() <= 0) {
            break;
        }
        if (this->eat_such_that(sb) && this->eat_relCond(sb)) {
            // nothing
        } else if (this->eat_with(sb)) {
            // TODO: Fill in
        } else if (this->eat_pattern(sb)) {
            // TODO: Fill in
        } else {
            break;
        }
    }
}

void PQLParser::parse(const string &s)
{
    StringBuffer sb;
    int saveIdx;
    this->bufIdx = 0;
    this->buf = s;
    this->bufLen = this->buf.size();
    this->entTable.clear();
    this->entVec.clear();
    this->parseErrors = 0;
    this->eat_decls();
    if (this->parseErrors > 0) {
        return;
    }
    qinfo->reset(this->entTable, this->entVec);
    if (!this->eat_select(sb)) {
        this->error("Expected \"Select\", got \"%s\"",
            sb.toString().c_str());
        return;
    }
    if (this->eat_space() <= 0) {
        this->error("Expected whitespace after Select");
        return;
    }
    saveIdx = this->bufIdx;
    if (this->eat_select_tuple(sb)) {
        // nothing
    } else {
        this->bufIdx = saveIdx;
        if (this->eat_select_boolean(sb)) {
            this->qinfo->set_select_boolean();
        } else {
            this->error("Select clause: Expected tuple or BOOLEAN, got "
                "\"%s\"", sb.toString().c_str());
            return;
        }
    }

    this->eat_select_stwithpat(sb);
    this->eat_space();
    if (this->bufIdx != this->bufLen) {
        this->error("Expected end of query, got \"%s\"",
            this->buf.c_str() + this->bufIdx);
    }
}

#undef RESTORE_AND_RET

/* class QueryInfo */

QueryInfo::QueryInfo() {}

QueryInfo::QueryInfo(const map<string, DesignEnt>& etab,
        const vector<pair<DesignEnt, string> > &eVec)
{
    this->reset(etab, eVec);
}

void QueryInfo::reset(const map<string, DesignEnt>& etab,
        const vector<pair<DesignEnt, string> > &eVec)
{
    this->entTable.clear();
    for (map<string, DesignEnt>::const_iterator it = etab.begin();
            it != etab.end(); it++) {
        this->entTable[it->first] = it->second;
    }
    this->entVec.clear();
    for (vector<pair<DesignEnt, string> >::const_iterator it = eVec.begin();
            it != eVec.end(); it++) {
        this->entVec.push_back(*it);
    }
    this->evalOrder.clear();
    this->relRefs.clear();
    this->relRefsSet.clear();
}

void QueryInfo::set_select_boolean()
{
    this->selectType = SEL_BOOLEAN;
}

void QueryInfo::set_select_tuple()
{
    this->selectType = SEL_TUPLE;
    this->selectTuple.clear();
    this->selectTable.clear();
}

bool QueryInfo::add_select_tuple(AttrRef attrRef, char **errorMsg)
{
    const std::string& syn = attrRef.syn;
    if (this->entTable.find(syn) == this->entTable.end()) {
        if (errorMsg) {
            _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                "Unknown entity \"%s\"", syn.c_str());
            *errorMsg = _strdup(this->errorBuf);
        }
        return false;
    }
    if (this->selectTable.find(attrRef) != this->selectTable.end()) {
        StringBuffer sb;
        string s;
        if (errorMsg) {
            attrRef.dump_to_sb(sb);
            s = sb.toString();
            _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                "Select element \"%s\" already exists", s.c_str());
            *errorMsg = _strdup(this->errorBuf);
        }
        return false;
    } else {
        this->selectTable.insert(attrRef);
        this->selectTuple.push_back(attrRef);
        return true;
    }
}

DesignEnt QueryInfo::retrieve_syn_type(const string &s) const
{
    map<string, DesignEnt>::const_iterator it = this->entTable.find(s);
    if (it != this->entTable.end()) {
        return it->second;
    } else {
        return ENT_INVALID;
    }
}

void QueryInfo::insert_relRef(const RelRef &relRef, char **errorMsg)
{
    if (this->relRefsSet.find(relRef) == this->relRefsSet.end()) {
        this->evalOrder.push_back(
            make_pair(SUCHTHAT_CLAUSE, this->relRefs.size()));
        this->relRefsSet.insert(relRef);
        this->relRefs.push_back(relRef);
    } else {
        // else duplicate relRef, dont insert
        if (errorMsg) {
            _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                "Repeated relRef \"%s\"", relRef.dump().c_str());
            *errorMsg = strdup(this->errorBuf);
        }
    }
}

bool QueryInfo::add_modifies_relRef(RelRef &relRef, char **errorMsg)
{
    DesignEnt entType;
    if (relRef.argOneType == RELARG_SYN) {
        entType = this->retrieve_syn_type(relRef.argOneString);
        switch (entType) {
        case ENT_ASSIGN: case ENT_STMT: case ENT_IF:
        case ENT_WHILE: case ENT_PROC: case ENT_CALL:
        case ENT_PROGLINE:
            relRef.argOneSyn = entType;
            break;
        case ENT_INVALID:
            if (errorMsg) {
                _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                    "Modifies - arg one is an undeclared synonym \"%s\"",
                    relRef.argOneString.c_str());
                *errorMsg = strdup(this->errorBuf);
            }
            return false;
        default:
            // all other types fail
            if (errorMsg) {
                _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                    "Modifies - arg one must be a synonym of type assign, "
                    "stmt, if, while, procedure, call, prog_line"
                    "; or the name of a procedure enclosed in double quotes"
                    "; or an underscore");
                *errorMsg = strdup(this->errorBuf);
            }
            return false;
        }
    }
    if (relRef.argTwoType == RELARG_SYN) {
        entType = this->retrieve_syn_type(relRef.argTwoString);
        switch (entType) {
        case ENT_VAR:
            relRef.argTwoSyn = entType;
            break;
        case ENT_INVALID:
            if (errorMsg) {
                _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                    "Modifies - arg two is an undeclared synonym \"%s\"",
                    relRef.argTwoString.c_str());
                *errorMsg = strdup(this->errorBuf);
            }
            return false;
        default:
            if (errorMsg) {
                _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                    "Modifies - arg two must be a synonym of type variable"
                    "; or the name of a variable enclosed in double quotes"
                    "; or an underscore");
                *errorMsg = strdup(this->errorBuf);
            }
            return false;
        }
    }
    this->insert_relRef(relRef, errorMsg);
    return true;
}

bool QueryInfo::add_uses_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_calls_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_parent_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_follows_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_next_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_affects_relRef(RelRef &relRef, char **errorMsg)
{
    // TODO: fill in
    return false;
}

bool QueryInfo::add_relRef(RelRef &relRef, char **errorMsg)
{
    switch (relRef.relType) {
    case REL_MODIFIES:
        return this->add_modifies_relRef(relRef, errorMsg);
    case REL_USES:
        return this->add_uses_relRef(relRef, errorMsg);
    case REL_CALLS:
    case REL_CALLS_STAR:
        return this->add_calls_relRef(relRef, errorMsg);
    case REL_PARENT:
    case REL_PARENT_STAR:
        return this->add_parent_relRef(relRef, errorMsg);
    case REL_FOLLOWS:
    case REL_FOLLOWS_STAR:
        return this->add_follows_relRef(relRef, errorMsg);
    case REL_NEXT:
    case REL_NEXT_STAR:
        return this->add_next_relRef(relRef, errorMsg);
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
        return this->add_affects_relRef(relRef, errorMsg);
    default:
        if (errorMsg) {
            *errorMsg = strdup("add_relRef - trying to add invalid rel ref");
        }
        return false;
    }
}

void QueryInfo::dump(void) const
{
    this->dump(stdout);
}

void QueryInfo::dump(FILE *f) const
{
    fprintf(f, "%s", this->dump_to_string().c_str());
}

std::string QueryInfo::dump_to_string() const
{
    StringBuffer sb;
    sb.append("DECLARATIONS\n");
    for (vector<pair<DesignEnt, string> >::const_iterator it =
            this->entVec.begin(); it != this->entVec.end(); it++) {
        sb.append("  ");
        sb.append(entity_type_to_string(it->first));
        sb.append(' ');
        sb.append(it->second.c_str());
        sb.append('\n');
    }
    sb.append("SELECT ");
    if (this->selectType == SEL_TUPLE) {
        sb.append("TUPLE\n");
        for (vector<AttrRef>::const_iterator kt =
                this->selectTuple.begin(); kt != this->selectTuple.end();
                kt++) {
            const AttrRef& attrRef = *kt;
            sb.append("  ");
            attrRef.dump_to_sb(sb);
            sb.append('\n');
        }
    } else {
        sb.append("BOOLEAN\n");
    }
    for (vector<pair<ClauseType, int> >::const_iterator it =
            this->evalOrder.begin(); it != this->evalOrder.end(); it++) {
        switch (it->first) {
        case SUCHTHAT_CLAUSE:
            sb.append(this->relRefs[it->second].dump());
            sb.append('\n');
            break;
        }
    }
    return sb.toString();
}