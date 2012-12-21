#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <string>
#include <map>
#include "PQLParser.h"
#include "StringBuffer.h"

using std::string;
using std::map;
using std::vector;
using std::set;
using std::pair;

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

void PQLParser::error(const char *s, ...)
{
    this->parseErrors++;
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    va_end(ap);
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

void PQLParser::eat_nonws_token(StringBuffer &sb)
{
    sb.clear();
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    }
}

void PQLParser::eat_till_ws(StringBuffer &sb)
{
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    }
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

void PQLParser::eat_alpha(StringBuffer &sb)
{
    while (this->bufIdx < this->bufLen &&
            isalpha(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    }
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

void PQLParser::eat_ident(StringBuffer &sb)
{
    while (this->bufIdx < this->bufLen &&
            (isalnum(this->buf[this->bufIdx]) ||
             this->buf[this->bufIdx] == '#')) {
        sb.append(this->buf[this->bufIdx++]);
    }
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

void PQLParser::eat_select_stwithpat(StringBuffer &sb)
{
    if (this->bufIdx >= this->bufLen) {
        return;
    }
    while (1) {
        if (this->eat_space() <= 0) {
            break;
        }
        if (this->eat_with(sb)) {
        } else {
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
    return sb.toString();
}