#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <cassert>
#include <string>
#include <map>
#include <utility>
#include <memory>
#include <fstream>
#include "PQLParser.h"
#include "StringBuffer.h"

using std::string;
using std::map;
using std::vector;
using std::set;
using std::pair;
using std::make_pair;
using std::auto_ptr;
using std::ostream;
using std::ofstream;
using std::ios_base;

//////////////////////////////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////////////////////////////

bool string_is_synonym(const std::string &s)
{
    int len = s.size();
    if (len <= 0) {
        return false;
    }
    if (!isalpha(s[0])) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isalnum(s[i]) && s[i] != '#') {
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////
// PQLParseErrorStream
//////////////////////////////////////////////////////////////////////

PQLParseErrorStream::PQLParseErrorStream():
            useStderr(true), os(NULL)
{
}

PQLParseErrorStream::PQLParseErrorStream(ostream *os_):
        useStderr(false), os(os_) {}

PQLParseErrorStream::PQLParseErrorStream(PQLParseErrorStream &other)
{
    if (this != &other) {
        this->useStderr = other.useStderr;
        this->os = other.os;
    }
}

void PQLParseErrorStream::swap(PQLParseErrorStream &other) throw()
{
    bool tmpUseStderr = this->useStderr;
    this->useStderr = other.useStderr;
    other.useStderr = tmpUseStderr;
    auto_ptr<ostream> tmpOs = this->os;
    this->os = other.os;
    other.os = tmpOs;
}

PQLParseErrorStream& PQLParseErrorStream::operator=
        (PQLParseErrorStream &other)
{
    PQLParseErrorStream tmpStream(other);
    this->swap(tmpStream);
    return *this;
}

PQLParseErrorStream::~PQLParseErrorStream() {}

void PQLParseErrorStream::print(const char *s)
{
    if (this->useStderr) {
        fprintf(stderr, "%s", s);
    } else {
        (*(this->os)) << s;
    }
}

//////////////////////////////////////////////////////////////////////
// PQL Parser
//////////////////////////////////////////////////////////////////////

#define RESTORE_AND_RET(retVal, savePtr) do {\
    this->bufIdx = savePtr;\
    return retVal;\
} while(0)

PQLParser::PQLParser():
        parseErr(PARSE_OK), showWarnings(true), showErrors(true),
        parseErrorStream()
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
    strToAttrType[ATTR_PROGLINE_STR] = ATTR_PROGLINE;
    qinfo = new QueryInfo();
}

PQLParser::~PQLParser()
{
    if (qinfo) {
        delete qinfo;
    }
}

ParseError PQLParser::get_parse_result() const
{
    return this->parseErr;
}

map<string, DesignEnt> PQLParser::get_ent_table() const
{
    return this->entTable;
}

QueryInfo *PQLParser::get_queryinfo() const
{
    // kill queryinfo if PARSE_OK != parseErr
    if (PARSE_OK != this->parseErr) {
        this->qinfo->kill();
    }
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
        throw(ParseError)
{
    if (s.size() <= 0) {
        this->error(PARSE_DECL_EMPTY_SYN, entity_type_to_string(entType));
    }
    map<string, DesignEnt>::iterator it = this->entTable.find(s);
    if (it != this->entTable.end()) {
        const char *tmpS = s.c_str();
        this->error(PARSE_DECL_REPEATED_SYN, tmpS,
            entity_type_to_string(entType),
            entity_type_to_string(it->second));
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

void PQLParser::error(ParseError parseErr_, ...) throw(ParseError)
{
    this->parseErr = parseErr_;
    va_list ap;
    va_start(ap, parseErr_);
    if (this->showErrors) {
        this->print_error(ap);
    }
    va_end(ap);
    throw this->parseErr;
}

void PQLParser::warning(const char *s, ...) const
{
    if (this->showWarnings) {
        va_list ap;
        va_start(ap, s);
        this->valist_print("Warning: ", s, ap);
        va_end(ap);
    }
}

void PQLParser::valist_print(const char *pfx, const char *fmt,
        va_list ap) const throw()
{
    fprintf(stderr, "%s", pfx);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

void PQLParser::print_error(va_list ap)
{
    StringBuffer sb;
    switch (this->parseErr) {
    case PARSE_DECL_EMPTY_SYN:
        sb.vsprintf(PARSE_DECL_EMPTY_SYN_STR, ap);
        break;
    case PARSE_DECL_REPEATED_SYN:
        sb.vsprintf(PARSE_DECL_REPEATED_SYN_STR, ap);
        break;
    case PARSE_DECL_INVALID_SYN:
        sb.vsprintf(PARSE_DECL_INVALID_SYN_STR, ap);
        break;
    case PARSE_DECL_ENT_SYN_INVALID_SEP:
        sb.vsprintf(PARSE_DECL_ENT_SYN_INVALID_SEP_STR, ap);
        break;
    case PARSE_DECL_NO_TERMINATOR:
        sb.vsprintf(PARSE_DECL_NO_TERMINATOR_STR, ap);
        break;
    case PARSE_NO_SELECT_AFTER_DECL:
        sb.vsprintf(PARSE_NO_SELECT_AFTER_DECL_STR, ap);
        break;
    case PARSE_SELECT_UNDECLARED:
        sb.vsprintf(PARSE_SELECT_UNDECLARED_STR, ap);
        break;
    case PARSE_ATTRREF_UNDECLARED:
        sb.vsprintf(PARSE_ATTRREF_UNDECLARED_STR, ap);
        break;
    case PARSE_SELECT_INVALID_ATTRREF:
        sb.vsprintf(PARSE_SELECT_INVALID_ATTRREF_STR, ap);
        break;
    case PARSE_SELECT_TUPLE_NO_CLOSE:
        sb.vsprintf(PARSE_SELECT_TUPLE_NO_CLOSE_STR, ap);
        break;
    case PARSE_SELECT_NOTHING:
        sb.vsprintf(PARSE_SELECT_NOTHING_STR, ap);
        break;
    case PARSE_ATTRREF_UNDEF_ATTRNAME:
        sb.vsprintf(PARSE_ATTRREF_UNDEF_ATTRNAME_STR, ap);
        break;
    case PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR:
        sb.vsprintf(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR_STR, ap);
        break;
    case PARSE_REL_ARGONE:
        sb.vsprintf(PARSE_REL_ARGONE_STR, ap);
        break;
    case PARSE_REL_ARGTWO:
        sb.vsprintf(PARSE_REL_ARGTWO_STR, ap);
        break;
    case PARSE_REL_ARG_INT_INVALID:
        sb.vsprintf(PARSE_REL_ARG_INT_INVALID_STR, ap);
        break;
    case PARSE_REL_ARGONE_UNDECLARED:
        sb.vsprintf(PARSE_REL_ARGONE_UNDECLARED_STR, ap);
        break;
    case PARSE_REL_ARGONE_TYPE_ERROR:
        sb.vsprintf(PARSE_REL_ARGONE_TYPE_ERROR_STR, ap);
        break;
    case PARSE_REL_ARGTWO_UNDECLARED:
        sb.vsprintf(PARSE_REL_ARGTWO_UNDECLARED_STR, ap);
        break;
    case PARSE_REL_ARGTWO_TYPE_ERROR:
        sb.vsprintf(PARSE_REL_ARGTWO_TYPE_ERROR_STR, ap);
        break;
    case PARSE_REL_NO_COMMA:
        sb.vsprintf(PARSE_REL_NO_COMMA_STR, ap);
        break;
    case PARSE_REL_NO_RPAREN:
        sb.vsprintf(PARSE_REL_NO_RPAREN_STR, ap);
        break;
    case PARSE_RELCOND_AND_NOSEP:
        sb.vsprintf(PARSE_RELCOND_AND_NOSEP_STR, ap);
        break;
    case PARSE_RELCOND_INVALID_RELREF:
        sb.vsprintf(PARSE_RELCOND_INVALID_RELREF_STR, ap);
        break;
    case PARSE_PATCL_VARREF_INVALID:
        sb.vsprintf(PARSE_PATCL_VARREF_INVALID_STR, ap);
        break;
    case PARSE_PATCL_VARREF_UNDECLARED:
        sb.vsprintf(PARSE_PATCL_VARREF_UNDECLARED_STR, ap);
        break;
    case PARSE_PATCL_VARREF_NOTVAR:
        sb.vsprintf(PARSE_PATCL_VARREF_NOTVAR_STR, ap);
        break;
    case PARSE_PATCL_ARGONE_NOCOMMA:
        sb.vsprintf(PARSE_PATCL_ARGONE_NOCOMMA_STR, ap);
        break;
    case PARSE_PATCL_ASSIGN_EXPR_NODQUOTE:
        sb.vsprintf(PARSE_PATCL_ASSIGN_EXPR_NODQUOTE_STR, ap);
        break;
    case PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE:
        sb.vsprintf(PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE_STR, ap);
        break;
    case PARSE_PATCL_ASSIGN_EXPR_INVALID:
        sb.vsprintf(PARSE_PATCL_ASSIGN_EXPR_INVALID_STR, ap);
        break;
    case PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE:
        sb.vsprintf(PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE_STR, ap);
        break;
    case PARSE_PATCL_IF_ARGTWO_NOCOMMA:
        sb.vsprintf(PARSE_PATCL_IF_ARGTWO_NOCOMMA_STR, ap);
        break;
    case PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE:
        sb.vsprintf(PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE_STR, ap);
        break;
    case PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE:
        sb.vsprintf(PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE_STR, ap);
        break;
    case PARSE_PATCL_NORPAREN:
        sb.vsprintf(PARSE_PATCL_NORPAREN_STR, ap);
        break;
    case PARSE_PATCL_SYN_UNDECLARED:
        sb.vsprintf(PARSE_PATCL_SYN_UNDECLARED_STR, ap);
        break;
    case PARSE_PATCL_NOLPAREN:
        sb.vsprintf(PARSE_PATCL_NOLPAREN_STR, ap);
        break;
    case PARSE_PATCL_SYN_TYPE_ERROR:
        sb.vsprintf(PARSE_PATCL_SYN_TYPE_ERROR_STR, ap);
        break;
    case PARSE_PATCOND_AND_NOSEP:
        sb.vsprintf(PARSE_PATCOND_AND_NOSEP_STR, ap);
        break;
    case PARSE_PATCOND_INVALID_PATCL:
        sb.vsprintf(PARSE_PATCOND_INVALID_PATCL_STR, ap);
        break;
    case PARSE_QINFO_INSERT_INVALID_RELREF:
        sb.vsprintf(PARSE_QINFO_INSERT_INVALID_RELREF_STR, ap);
        break;
    case PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED:
        sb.vsprintf(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED_STR, ap);
        break;
    case PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE:
        sb.vsprintf(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE_STR, ap);
        break;
    case PARSE_WITHCLAUSE_REFS_INVALID:
        sb.vsprintf(PARSE_WITHCLAUSE_REFS_INVALID_STR, ap);
        break;
    case PARSE_WITHCLAUSE_TYPE_MISMATCH:
        sb.vsprintf(PARSE_WITHCLAUSE_TYPE_MISMATCH_STR, ap);
        break;
    case PARSE_WITHCLAUSE_AND_NOSEP:
        sb.vsprintf(PARSE_WITHCLAUSE_AND_NOSEP_STR, ap);
        break;
    case PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS:
        sb.vsprintf(PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS_STR, ap);
        break;
    case PARSE_WITHCLAUSE_EXPECT_WITH:
        sb.vsprintf(PARSE_WITHCLAUSE_EXPECT_WITH_STR, ap);
        break;
    case PARSE_REF_INTEGER_ERROR:
        sb.vsprintf(PARSE_REF_INTEGER_ERROR_STR, ap);
        break;
    case PARSE_REF_ATTRREF_ERROR:
        sb.vsprintf(PARSE_REF_ATTRREF_ERROR_STR, ap);
        break;
    case PARSE_DQUOTED_IDENT_INVALID:
        sb.vsprintf(PARSE_DQUOTED_IDENT_INVALID_STR, ap);
        break;
    case PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE:
        sb.vsprintf(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE_STR, ap);
        break;
    case PARSE_END_OF_QUERY_ERROR:
        sb.vsprintf(PARSE_END_OF_QUERY_ERROR_STR, ap);
        break;
    case PARSE_UNKNOWN:
        sb.vsprintf(PARSE_UNKNOWN_STR, ap);
        break;
    default:
        break;
    }
    this->parseErrorStream.print(sb.c_str());
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

//////////////////////////////////////////////////////////////////////
// functions for eat_while<bool (*fn)(char ch)> specialization
//////////////////////////////////////////////////////////////////////

bool not_comma_space(char ch)
{
    return (!isspace(ch) && ch != ',');
}

bool not_comma_space_gt(char ch)
{
    return (!isspace(ch) && ch != ',' && ch != '>');
}

bool not_comma_space_rparen(char ch)
{
    return (!isspace(ch) && ch != ',' && ch != ')');
}

bool not_comma_space_semicolon(char ch)
{
    return (!isspace(ch) && ch != ',' && ch != ';');
}

bool not_space(char ch)
{
    return !isspace(ch);
}

bool not_space_lparen(char ch)
{
    return (!isspace(ch) && ch != '(');
}

bool not_space_rparen(char ch)
{
    return (!isspace(ch) && ch != ')');
}

bool not_rparen(char ch)
{
    return ch != ')';
}

bool not_dquote(char ch)
{
    return ch != '"';
}

bool is_alpha(char ch)
{
    return isalpha(ch);
}

bool is_alpha_star(char ch)
{
    return (isalpha(ch) || ch == '*');
}

bool is_alpha_underscore(char ch)
{
    return (isalpha(ch) || ch == '_');
}

bool is_alpha_underscore_sharp(char ch)
{
    return (isalpha(ch) || '_' == ch || '#' == ch);
}

bool is_ident(char ch)
{
    return (isalnum(ch) || ch == '#');
}

bool is_space(char ch)
{
    return isspace(ch);
}

template<bool (*fn)(char ch)>
int PQLParser::eat_while(StringBuffer &sb)
{
    int ate = 0;
    while (this->bufIdx < this->bufLen && fn(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        ate++;
    }
    return ate;
}

bool PQLParser::eat_string_till_ws(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_while<not_space>(sb);
    if (!sb.strcmp(str)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

bool PQLParser::eat_alpha_string(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_while<is_alpha>(sb);
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

bool PQLParser::eat_alpha_star_string(StringBuffer &sb, const char *s)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_while<is_alpha_star>(sb);
    if (!sb.strcmp(s)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

bool PQLParser::eat_alpha_underscore_string(StringBuffer &sb, const char *s)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_while<is_alpha_underscore>(sb);
    if (!sb.strcmp(s)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

bool PQLParser::eat_design_entity(StringBuffer &sb)
{
    return (this->eat_alpha_string(sb, ENT_ASSIGN_STR) ||
            this->eat_alpha_string(sb, ENT_STMT_STR) ||
            this->eat_alpha_string(sb, ENT_VAR_STR) ||
            this->eat_alpha_string(sb, ENT_IF_STR) ||
            this->eat_alpha_string(sb, ENT_WHILE_STR) ||
            this->eat_alpha_string(sb, ENT_PROC_STR) ||
            this->eat_alpha_string(sb, ENT_CALL_STR) ||
            this->eat_alpha_string(sb, ENT_CONST_STR) ||
            this->eat_alpha_underscore_string(sb, ENT_PROGLINE_STR) ||
            this->eat_alpha_string(sb, ENT_STMTLST_STR) ||
            false);
}

bool PQLParser::eat_ident_string(StringBuffer &sb, const char *str)
{
    int saveIdx = this->bufIdx;
    sb.clear();
    this->eat_while<is_ident>(sb);
    if (!sb.strcmp(str)) {
        return true;
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
}

bool PQLParser::eat_dquoted_ident(StringBuffer &sb)
{
    int saveIdx = this->bufIdx;
    if (!this->eat_dquote()) {
        RESTORE_AND_RET(false, saveIdx);
    }
    sb.clear();
    if (this->bufIdx < this->bufLen &&
            is_alpha(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    } else {
        // invalid identifier string
        this->eat_while<not_dquote>(sb);
        this->error(PARSE_DQUOTED_IDENT_INVALID, sb.c_str());
    }
    this->eat_while<is_ident>(sb);
    if (!this->eat_dquote()) {
        this->error(PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE, sb.c_str());
    }
    return true;
}

int PQLParser::eat_int(StringBuffer &sb)
{
    bool neg = false;
    int charsConsumed = 0;
    if (this->bufIdx < this->bufLen) {
        if (this->buf[this->bufIdx] == '-') {
            sb.append(this->buf[this->bufIdx++]);
            neg = true;
            charsConsumed++;
        }
    } else {
        return 0;
    }
    // must be digit from now on
    if (this->bufIdx < this->bufLen &&
            isdigit(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        charsConsumed++;
    } else {
        if (neg) {
            // consumed 1 '-', move back
            this->bufIdx--;
        }
        return 0;
    }
    while (this->bufIdx < this->bufLen &&
            isdigit(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
        charsConsumed++;
    }
    return charsConsumed;
}

void PQLParser::eat_till_end(StringBuffer& sb)
{
    sb.clear();
    while (this->bufIdx < this->bufLen) {
        sb.append(this->buf[this->bufIdx++]);
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

bool PQLParser::eat_equal()
{
    return this->eat_one_char('=');
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
    if (this->bufIdx < this->bufLen &&
            islower(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    } else {
        RESTORE_AND_RET(false, saveIdx);
    }
    this->eat_while<is_alpha_underscore_sharp>(sb);
    if (!sb.strcmp(ATTR_PROCNAME_STR) ||
            !sb.strcmp(ATTR_VARNAME_STR) ||
            !sb.strcmp(ATTR_VALUE_STR) ||
            !sb.strcmp(ATTR_STMTNO_STR) ||
            !sb.strcmp(ATTR_PROGLINE_STR)) {
        return true;
    }
    RESTORE_AND_RET(false, saveIdx);
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
        // synonym and period ate, ok to error out
        if (!this->eat_attrName(sb)) {
            sb.clear();
            this->eat_while<is_ident>(sb);
            this->error(PARSE_ATTRREF_UNDEF_ATTRNAME, sb.c_str(),
                    syn.c_str());
        }
        attr = sb.toString();
        AttrType attrType = this->string_to_attrType(attr);
        AttrRef attrRef = AttrRef(syn, ENT_INVALID, attrType);
        // "type check"
        DesignEnt entType = this->retrieve_syn_type(syn);
        if (entType == ENT_INVALID) {
            this->error(PARSE_ATTRREF_UNDECLARED,
                syn.c_str(), attrRef.toPeriodString().c_str());
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
                    entType == ENT_ASSIGN || entType == ENT_CALL ||
                    entType == ENT_WHILE || entType == ENT_IF);
            break;
        case ATTR_PROGLINE:
            ok = (ENT_PROGLINE == entType);
            break;
        }
        if (ok) {
            return AttrRef(syn, entType, attrType);
        } else {
            this->error(PARSE_ATTRREF_SYN_ATTRNAME_TYPE_ERROR,
                attrRef.toPeriodString().c_str(), attr.c_str(),
                entity_type_to_string(entType));
        }
    } else {
        RESTORE_AND_RET(AttrRef(), saveIdx);
    }
}

bool PQLParser::eat_decl_one() throw(ParseError)
{
    #define EAT_SYN() do {\
        if (!this->eat_synonym(sb)) {\
            sb.clear();\
            if (this->eat_while<not_comma_space_semicolon>(sb) <= 0) {\
                this->error(PARSE_DECL_EMPTY_SYN, entStr.c_str());\
            } else {\
                this->error(PARSE_DECL_INVALID_SYN, sb.c_str());\
            }\
        } else {\
            this->insert_syn(entType, sb.toString());\
        }\
    } while(0)

    StringBuffer sb;
    string s;
    bool ret;
    int saveIdx;
    this->eat_space();
    saveIdx = this->bufIdx;
    if (!this->eat_design_entity(sb)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    string entStr = sb.toString();
    DesignEnt entType = string_to_entity(entStr);
    if (this->eat_space() <= 0) {
        sb.clear();
        this->eat_while<not_space>(sb);
        this->error(PARSE_DECL_ENT_SYN_INVALID_SEP, sb.c_str());
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
        this->error(PARSE_DECL_NO_TERMINATOR, entStr.c_str());
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

AttrRef PQLParser::eat_select_tuple_elem(StringBuffer &sb) throw(ParseError)
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
        } else {
            this->error(PARSE_SELECT_UNDECLARED, syn.c_str());
        }
    }
    RESTORE_AND_RET(AttrRef(), saveIdx);
}

bool PQLParser::eat_select_tuple(StringBuffer &sb) throw(ParseError)
{
    this->eat_space();
    int saveIdx = this->bufIdx;
    ParseError ret;
    sb.clear();
    // 1 element
    AttrRef attrRef = this->eat_select_tuple_elem(sb);
    if (attrRef.attr != ATTR_INVALID) {
        this->qinfo->set_select_tuple();
        ret = this->qinfo->add_select_tuple(attrRef);
        if (ret != PARSE_OK) {
            this->error_add_select_tuple(ret, attrRef);
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
        // "Select <" - Must be selecting tuple. OK to call error() here
        sb.clear();
        this->eat_while<not_comma_space_gt>(sb);
        this->error(PARSE_SELECT_INVALID_ATTRREF, sb.c_str());
    }
    this->qinfo->set_select_tuple();
    ret = this->qinfo->add_select_tuple(attrRef);
    if (ret != PARSE_OK) {
        this->error_add_select_tuple(ret, attrRef);
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
            sb.clear();
            this->eat_while<not_comma_space_gt>(sb);
            this->error(PARSE_SELECT_INVALID_ATTRREF, sb.c_str());
        }
        ret = this->qinfo->add_select_tuple(attrRef);
        if (ret != PARSE_OK) {
            this->error_add_select_tuple(ret, attrRef);
        }
    }
    this->eat_space();
    if (!this->eat_gt()) {
        this->error(PARSE_SELECT_TUPLE_NO_CLOSE);
    }
    return true;
}

void PQLParser::error_add_select_tuple(ParseError parseErr_,
        const AttrRef &attrRef) throw(ParseError)
{
    StringBuffer sb;
    switch (parseErr_) {
    case PARSE_SELECT_UNDECLARED:
        this->error(parseErr_, attrRef.syn.c_str());
        break;
    }
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
    return this->eat_alpha_string(sb, CALLS_STR);
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

bool PQLParser::eat_nextBip(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, NEXTBIP_STR);
}

bool PQLParser::eat_nextBip_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, NEXTBIP_STAR_STR);
}

bool PQLParser::eat_affectsBip(StringBuffer &sb)
{
    return this->eat_alpha_string(sb, AFFECTSBIP_STR);
}

bool PQLParser::eat_affectsBip_star(StringBuffer &sb)
{
    return this->eat_alpha_star_string(sb, AFFECTSBIP_STAR_STR);
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
        if (this->eat_while<is_ident>(sb) > 0 && this->eat_dquote()) {
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
        // TODO: Change this to use this->eat_dquoted_ident
        sb.clear();
        if (this->eat_while<is_ident>(sb) > 0 && this->eat_dquote()) {
            return RELARG_STRING;
        }
    }
    RESTORE_AND_RET(RELARG_INVALID, saveIdx);
}

RelRefArgType PQLParser::eat_callRef(StringBuffer &sb)
{
    return this->eat_varRef(sb);
}

void PQLParser::eat_XRef_YRef(
        RelRefArgType (PQLParser::*eat_XRef)(StringBuffer &sb),
        RelRefArgType (PQLParser::*eat_YRef)(StringBuffer &sb),
        RelRef &relRef, StringBuffer &sb, char **errorMsg) throw(ParseError)
{
    int saveIdx = this->bufIdx;
    RelRefArgType argType;
    ParseError ret;
    this->eat_space();
    argType = (this->*eat_XRef)(sb);
    if (argType == RELARG_INVALID) {
        sb.clear();
        this->eat_while<not_comma_space>(sb);
        this->error(PARSE_REL_ARGONE, relRefType_to_string(relRef.relType),
            sb.c_str());
    }
    ret = relRef.set_arg_one(argType, sb, errorMsg);
    if (ret != PARSE_OK) {
        this->error_set_relRef_arg(ret, relRef, "one", sb, errorMsg);
    }
    this->eat_space();
    if (!this->eat_comma()) {
        this->error(PARSE_REL_NO_COMMA, relRefType_to_string(relRef.relType));
    }
    this->eat_space();
    sb.clear();
    errorMsg = NULL;
    argType = (this->*eat_YRef)(sb);
    if (argType == RELARG_INVALID) {
        sb.clear();
        this->eat_while<not_comma_space_rparen>(sb);
        this->error(PARSE_REL_ARGTWO, relRefType_to_string(relRef.relType),
            sb.c_str());
    }
    ret = relRef.set_arg_two(argType, sb, errorMsg);
    if (ret != PARSE_OK) {
        this->error_set_relRef_arg(ret, relRef, "two", sb, errorMsg);
    }
}

void PQLParser::error_set_relRef_arg(ParseError parseErr_,
        const RelRef& relRef, const char *which, const StringBuffer &sb,
        char **errorMsg) throw(ParseError)
{
    StringBuffer errBuf;
    switch (parseErr_) {
    case PARSE_REL_ARG_INT_INVALID:
        if (errorMsg && *errorMsg) {
            errBuf.append((const char *)*errorMsg);
            free(*errorMsg);
            *errorMsg = NULL;
        }
        this->error(parseErr_, relRefType_to_string(relRef.relType),
                which, sb.c_str(), errBuf.c_str());
        break;
    }
}

void PQLParser::eat_entRef_varRef(RelRef &relRef, StringBuffer &sb,
        char **errorMsg) throw(ParseError)
{
    this->eat_XRef_YRef(&PQLParser::eat_entRef,
            &PQLParser::eat_varRef, relRef, sb, errorMsg);
}

void PQLParser::eat_callRef_callRef(RelRef &relRef, StringBuffer &sb,
        char **errorMsg) throw(ParseError)
{
    this->eat_XRef_YRef(&PQLParser::eat_callRef, &PQLParser::eat_callRef,
                relRef, sb, errorMsg);
}

void PQLParser::eat_stmtRef_stmtRef(RelRef &relRef, StringBuffer &sb,
        char **errorMsg) throw(ParseError)
{
    this->eat_XRef_YRef(&PQLParser::eat_stmtRef, &PQLParser::eat_stmtRef,
                relRef, sb, errorMsg);
}

void PQLParser::eat_lineRef_lineRef(RelRef &relRef, StringBuffer &sb,
        char **errorMsg) throw(ParseError)
{
    this->eat_XRef_YRef(&PQLParser::eat_lineRef, &PQLParser::eat_lineRef,
                relRef, sb, errorMsg);
}

bool PQLParser::eat_relRef_generic(RelRef &relRef, StringBuffer &sb,
        bool (PQLParser::*eat_relRef_string_M) (StringBuffer &sb),
        RelRefType relRefType,
        void (PQLParser::*eat_arg_M)
            (RelRef &relRef, StringBuffer &sb, char **errorMsg))
{
    int saveIdx = this->bufIdx;
    char *errorMsg = NULL;
    ParseError ret;
    if ((this->*eat_relRef_string_M)(sb)) {
        relRef.relType = relRefType;
        this->eat_space();
        if (this->eat_lparen()) {
            // point of no return. Definitely SomeRel(arg1,arg2)
            (this->*eat_arg_M)(relRef, sb, &errorMsg);
            this->eat_space();
            if (!this->eat_rparen()) {
                this->error(PARSE_REL_NO_RPAREN,
                    relRefType_to_string(relRef.relType),
                    relRef.dump().c_str());
            }
            assert(RelRef::valid(relRef));
            errorMsg = NULL;
            ret = this->qinfo->add_relRef(relRef, &errorMsg);
            if (ret != PARSE_OK) {
                this->error_add_relRef(ret, relRef, errorMsg);
            } else if (errorMsg) {
                this->warning(errorMsg);
                free(errorMsg);
                errorMsg = NULL;
            }
            return true;
        }
    }
    return false;
}

void PQLParser::error_add_relRef(ParseError parseErr_, const RelRef &relRef,
        char *errorMsg) throw(ParseError)
{
    StringBuffer errBuf;
    if (errorMsg) {
        errBuf.append(errorMsg);
        free(errorMsg);
    }
    const char *relRefStr = relRefType_to_string(relRef.relType);
    const char **typeErrorArray = TYPE_ERROR_EMPTY;
    switch (relRef.relType) {
    case REL_MODIFIES:
        typeErrorArray = TYPE_ERROR_MODIFIES;
        break;
    case REL_USES:
        typeErrorArray = TYPE_ERROR_USES;
        break;
    case REL_CALLS:
        typeErrorArray = TYPE_ERROR_CALLS;
        break;
    case REL_CALLS_STAR:
        typeErrorArray = TYPE_ERROR_CALLS_STAR;
        break;
    case REL_PARENT:
        typeErrorArray = TYPE_ERROR_PARENT;
        break;
    case REL_PARENT_STAR:
        typeErrorArray = TYPE_ERROR_PARENT_STAR;
        break;
    case REL_FOLLOWS:
        typeErrorArray = TYPE_ERROR_FOLLOWS;
        break;
    case REL_FOLLOWS_STAR:
        typeErrorArray = TYPE_ERROR_FOLLOWS_STAR;
        break;
    case REL_NEXT:
        typeErrorArray = TYPE_ERROR_NEXT;
        break;
    case REL_NEXT_STAR:
        typeErrorArray = TYPE_ERROR_NEXT_STAR;
        break;
    case REL_AFFECTS:
        typeErrorArray = TYPE_ERROR_AFFECTS;
        break;
    case REL_AFFECTS_STAR:
        typeErrorArray = TYPE_ERROR_AFFECTS_STAR;
        break;
    case REL_NEXTBIP:
        typeErrorArray = TYPE_ERROR_NEXTBIP;
        break;
    case REL_NEXTBIP_STAR:
        typeErrorArray = TYPE_ERROR_NEXTBIP_STAR;
        break;
    case REL_AFFECTSBIP:
        typeErrorArray = TYPE_ERROR_AFFECTSBIP;
        break;
    case REL_AFFECTSBIP_STAR:
        typeErrorArray = TYPE_ERROR_AFFECTSBIP_STAR;
        break;
    }
    switch (parseErr_) {
    case PARSE_REL_ARGONE_UNDECLARED:
        this->error(parseErr_, relRefStr, relRef.argOneString.c_str());
        break;
    case PARSE_REL_ARGONE_TYPE_ERROR:
        this->error(parseErr_, typeErrorArray[0]);
        break;
    case PARSE_REL_ARGTWO_UNDECLARED:
        this->error(parseErr_, relRefStr, relRef.argTwoString.c_str());
        break;
    case PARSE_REL_ARGTWO_TYPE_ERROR:
        this->error(parseErr_, typeErrorArray[1]);
        break;
    }
}

bool PQLParser::eat_relRef_modifies(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_modifies,
                REL_MODIFIES, &PQLParser::eat_entRef_varRef);
}

bool PQLParser::eat_relRef_uses(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_uses,
            REL_USES, &PQLParser::eat_entRef_varRef);
}

bool PQLParser::eat_relRef_calls(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_calls,
                   REL_CALLS, &PQLParser::eat_callRef_callRef);
}

bool PQLParser::eat_relRef_calls_star(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_calls_star,
                   REL_CALLS_STAR, &PQLParser::eat_callRef_callRef);
}

bool PQLParser::eat_relRef_parent(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_parent,
                   REL_PARENT, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_parent_star(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_parent_star,
                   REL_PARENT_STAR, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_follows(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_follows,
                   REL_FOLLOWS, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_follows_star(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_follows_star,
                   REL_FOLLOWS_STAR, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_next(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_next,
                   REL_NEXT, &PQLParser::eat_lineRef_lineRef);
}

bool PQLParser::eat_relRef_next_star(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_next_star,
                   REL_NEXT_STAR, &PQLParser::eat_lineRef_lineRef);
}

bool PQLParser::eat_relRef_affects(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_affects,
                   REL_AFFECTS, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_affects_star(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb, &PQLParser::eat_affects_star,
                   REL_AFFECTS_STAR, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_nextBip(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb,
                   &PQLParser::eat_nextBip,
                   REL_NEXTBIP, &PQLParser::eat_lineRef_lineRef);
}

bool PQLParser::eat_relRef_nextBip_star(RelRef &relRef,
        StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb,
                   &PQLParser::eat_nextBip_star,
                   REL_NEXTBIP_STAR, &PQLParser::eat_lineRef_lineRef);
}

bool PQLParser::eat_relRef_affectsBip(RelRef &relRef, StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb,
                   &PQLParser::eat_affectsBip,
                   REL_AFFECTSBIP, &PQLParser::eat_stmtRef_stmtRef);
}

bool PQLParser::eat_relRef_affectsBip_star(RelRef &relRef,
        StringBuffer &sb)
{
    return this->eat_relRef_generic(relRef, sb,
                   &PQLParser::eat_affectsBip_star,
                   REL_AFFECTSBIP_STAR, &PQLParser::eat_stmtRef_stmtRef);
}

RelRef PQLParser::eat_relRef(StringBuffer &sb)
{
    RelRef relRef;
    if (this->eat_relRef_modifies(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_uses(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_calls_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_calls(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_parent_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_parent(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_follows_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_follows(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_next_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_next(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_affects_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_affects(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_nextBip_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_nextBip(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_affectsBip_star(relRef, sb)) {
        return relRef;
    } else if (this->eat_relRef_affectsBip(relRef, sb)) {
        return relRef;
    } else {
        return RelRef();
    }
}

bool PQLParser::eat_relCond(StringBuffer &sb) throw(ParseError)
{
    int saveIdx = this->bufIdx;
    RelRef relRef, prevRelRef;
    if (this->eat_space() <= 0) {
        RESTORE_AND_RET(false, saveIdx);
    }
    relRef = this->eat_relRef(sb);
    if (!RelRef::valid(relRef)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    prevRelRef = relRef;
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
            sb.clear();
            this->eat_while<not_space>(sb);
            this->error(PARSE_RELCOND_AND_NOSEP, prevRelRef.dump().c_str());
        }
        relRef = this->eat_relRef(sb);
        if (!RelRef::valid(relRef)) {
            sb.clear();
            this->eat_while<not_rparen>(sb);
            sb.append(')');
            this->error(PARSE_RELCOND_INVALID_RELREF, sb.c_str(),
                    prevRelRef.dump().c_str());
        }
        prevRelRef = relRef;
    }
    return true;
}

PatCl PQLParser::eat_patternClause(StringBuffer &sb) throw (ParseError)
{
    int saveIdx = this->bufIdx;
    bool ret;
    RelRefArgType rtype;
    PatCl patCl;
    PatClType patClType = PATCL_INVALID;
    PatClVarRefType varRefType = PATVARREF_INVALID;
    PatClExprType exprType = PATEXPR_INVALID;
    string syn, varRefString, exprString;
    DesignEnt entType;
    StringBuffer errorSb;
    sb.clear();
    this->eat_space();
    // synonym
    if (!this->eat_synonym(sb)) {
        RESTORE_AND_RET(PatCl(), saveIdx);
    }
    syn = sb.toString();
    entType = this->retrieve_syn_type(syn);
    if (entType != ENT_ASSIGN && entType != ENT_IF &&
            entType != ENT_WHILE) {
        RESTORE_AND_RET(PatCl(), saveIdx);
    }
    switch (entType) {
    case ENT_ASSIGN:
        patClType = PATCL_ASSIGN;
        break;
    case ENT_IF:
        patClType = PATCL_IF;
        break;
    case ENT_WHILE:
        patClType = PATCL_WHILE;
        break;
    }
    this->eat_space();
    if (!this->eat_lparen()) {
        RESTORE_AND_RET(PatCl(), saveIdx);
    }
    // point of no return, ok to error out from now since we ate '('
    this->eat_space();
    saveIdx = this->bufIdx;
    // 1st argument - eat varRef
    rtype = this->eat_varRef(sb);
    if (rtype == RELARG_INVALID) {
        this->bufIdx = saveIdx;
        sb.clear();
        this->eat_while<not_comma_space>(sb);
        this->error(PARSE_PATCL_VARREF_INVALID, sb.c_str());
    }
    assert(rtype == RELARG_SYN || rtype == RELARG_STRING ||
            rtype == RELARG_WILDCARD);
    varRefString = sb.toString();
    if (rtype == RELARG_SYN) {
        // type check, make sure it's of type var
        entType = this->retrieve_syn_type(varRefString);
        if (entType == ENT_INVALID) {
            this->error(PARSE_PATCL_VARREF_UNDECLARED,
                    varRefString.c_str());
        } else if (entType != ENT_VAR) {
            this->error(PARSE_PATCL_VARREF_NOTVAR, varRefString.c_str(),
                    entity_type_to_string(entType));
        }
        varRefType = PATVARREF_SYN;
    } else if (rtype == RELARG_STRING) {
        varRefType = PATVARREF_STRING;
    } else if (rtype == RELARG_WILDCARD) {
        varRefType = PATVARREF_WILDCARD;
        varRefString = "_";
    }
    this->eat_space();
    saveIdx = this->bufIdx;

    #define ARGONE_ERROR(someErr) do { \
        errorSb.clear(); \
        errorSb.sprintf("%s(%s%s%s", syn.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : ""), \
                    varRefString.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : "")); \
        this->error(someErr, errorSb.c_str()); \
    } while (0)

    #define ARGONE_ERROR_SB(someErr) do { \
        errorSb.clear(); \
        errorSb.sprintf("%s(%s%s%s", syn.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : ""), \
                    varRefString.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : "")); \
        this->error(someErr, errorSb.c_str(), sb.c_str()); \
    } while (0)

    #define ARGTWO_ERROR(argtwostr, someErr) do { \
        errorSb.clear(); \
        errorSb.sprintf("%s(%s%s%s,"argtwostr, syn.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : ""), \
                    varRefString.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : ""), \
                    sb.c_str()); \
        this->error(someErr, errorSb.c_str()); \
    } while(0)

    #define ARGTWO_ERROR_SB_ERR(someErr) do { \
        errorSb.clear(); \
        errorSb.sprintf("%s(%s%s%s,", syn.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : ""), \
                    varRefString.c_str(), \
                    ((varRefType == PATVARREF_STRING) ? "\"" : "")); \
        this->error(someErr, errorSb.c_str(), sb.c_str()); \
    } while(0)

    // comma after first arg
    if (!this->eat_comma()) {
        ARGONE_ERROR(PARSE_PATCL_ARGONE_NOCOMMA);
    }
    this->eat_space();
    saveIdx = this->bufIdx;
    // second arg
    if (patClType == PATCL_ASSIGN) {
        if (this->eat_dquote()) {
            exprType = PATEXPR_EXPR;
            sb.clear();
            this->eat_while<not_dquote>(sb);
            if (!this->eat_dquote()) {
                ARGTWO_ERROR("\"%s", PARSE_PATCL_ASSIGN_EXPR_NODQUOTE);
            }
            exprString = sb.toString();
        } else if (this->eat_underscore()) {
            if (this->eat_dquote()) {
                exprType = PATEXPR_EXPR_WILDCARD;
                sb.clear();
                this->eat_while<not_dquote>(sb);
                if (!this->eat_dquote()) {
                    ARGTWO_ERROR("_\"%s",
                            PARSE_PATCL_ASSIGN_EXPR_NODQUOTE);
                }
                if (!this->eat_underscore()) {
                    ARGTWO_ERROR("_\"%s\"",
                            PARSE_PATCL_ASSIGN_EXPR_WILDCARD_NO_UNDERSCORE);
                }
                exprString = sb.toString();
            } else {
                exprType = PATEXPR_WILDCARD;
            }
        } else {
            // error, invalid expr
            sb.clear();
            this->eat_while<not_space_rparen>(sb);
            ARGTWO_ERROR_SB_ERR(PARSE_PATCL_ASSIGN_EXPR_INVALID);
        }
    } else if (patClType == PATCL_IF) {
        if (!this->eat_underscore()) {
            sb.clear();
            this->eat_while<not_comma_space>(sb);
            ARGTWO_ERROR_SB_ERR(PARSE_PATCL_IF_ARGTWO_NOT_UNDERSCORE);
        }
        this->eat_space();
        if (!this->eat_comma()) {
            errorSb.clear();
            errorSb.sprintf("%s(%s%s%s,_", syn.c_str(),
                        ((varRefType == PATVARREF_STRING) ? "\"" : ""),
                        varRefString.c_str(),
                        ((varRefType == PATVARREF_STRING) ? "\"" : ""));
            this->error(PARSE_PATCL_IF_ARGTWO_NOCOMMA, errorSb.c_str());
        }
        this->eat_space();
        if (!this->eat_underscore()) {
            sb.clear();
            this->eat_while<not_space_rparen>(sb);
            errorSb.clear();
            errorSb.sprintf("%s(%s%s%s,_,", syn.c_str(),
                        ((varRefType == PATVARREF_STRING) ? "\"" : ""),
                        varRefString.c_str(),
                        ((varRefType == PATVARREF_STRING) ? "\"" : ""));
            this->error(PARSE_PATCL_IF_ARGTHREE_NOT_UNDERSCORE,
                    errorSb.c_str(), sb.c_str());
        }
    } else if (patClType == PATCL_WHILE) {
        if (!this->eat_underscore()) {
            sb.clear();
            this->eat_while<not_space_rparen>(sb);
            ARGTWO_ERROR_SB_ERR(PARSE_PATCL_WHILE_ARGTWO_NOT_UNDERSCORE);
        }
    }
    this->eat_space();
    // set PatCl parameters
    switch (patClType) {
    case PATCL_ASSIGN:
        patCl.set_pat_assign(syn, varRefType, varRefString, exprType,
                exprString);
        break;
    case PATCL_IF:
        patCl.set_pat_if(syn, varRefType, varRefString);
        break;
    case PATCL_WHILE:
        patCl.set_pat_while(syn, varRefType, varRefString);
        break;
    }
    if (!this->eat_rparen()) {
        this->error(PARSE_PATCL_NORPAREN, patCl.toString().c_str());
    }
    return patCl;

    #undef ARGONE_ERROR
    #undef ARGONE_ERROR_SB
    #undef ARGTWOERROR
    #undef ARGTWO_ERROR_SB
}

bool PQLParser::eat_patternCond(StringBuffer &sb) throw(ParseError)
{
    int saveIdx = this->bufIdx;
    PatCl patcl, prevPatcl;
    char *errorMsg = NULL;
    if (this->eat_space() <= 0) {
        RESTORE_AND_RET(false, saveIdx);
    }
    patcl = this->eat_patternClause(sb);
    if (!PatCl::valid(patcl)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    this->qinfo->add_patCl(patcl, &errorMsg);
    if (errorMsg) {
        this->warning(errorMsg);
        errorMsg = NULL;
    }

    while (1) {
        saveIdx = this->bufIdx;
        if (this->eat_space() <= 0) {
            break;
        }
        if (!this->eat_and(sb)) {
            this->bufIdx = saveIdx;
            break;
        }
        if (this->eat_space() <= 0) {
            sb.clear();
            this->eat_while<not_space>(sb);
            this->error(PARSE_PATCOND_AND_NOSEP, sb.c_str());
        }
        prevPatcl = patcl;
        patcl = this->eat_patternClause(sb);
        if (!PatCl::valid(patcl)) {
            sb.clear();
            saveIdx = this->bufIdx;
            this->eat_while<not_space_lparen>(sb);
            string s = sb.toString();
            if (string_is_synonym(s)) {
                DesignEnt entType = this->retrieve_syn_type(s);
                switch (entType) {
                case ENT_INVALID:
                    this->error(PARSE_PATCL_SYN_UNDECLARED, s.c_str());
                    break;
                case ENT_ASSIGN: case ENT_IF: case ENT_WHILE:
                    // next char is not '('
                    this->error(PARSE_PATCL_NOLPAREN, s.c_str());
                    break;
                default:
                    // invalid synonym type
                    this->error(PARSE_PATCL_SYN_TYPE_ERROR, s.c_str(),
                            entity_type_to_string(entType));
                    break;
                }
            } else {
                sb.clear();
                this->bufIdx = saveIdx;
                this->eat_while<not_rparen>(sb);
                if (this->bufIdx < this->bufLen &&
                        this->buf[this->bufIdx] == ')') {
                    sb.append(')');
                }
                this->error(PARSE_PATCOND_INVALID_PATCL, sb.c_str(),
                        prevPatcl.toString().c_str());
            }
        }
        this->qinfo->add_patCl(patcl, &errorMsg);
        if (errorMsg) {
            this->warning(errorMsg);
            errorMsg = NULL;
        }
    }
    return true;
}

bool PQLParser::eat_ref(StringBuffer& sb, Ref& refOut,
        bool triggerError, Ref *lhsRef)
{
    this->eat_while<is_space>(sb);
    bool ret = false;
    int saveIdx = this->bufIdx;
    sb.clear();
    if (this->eat_dquoted_ident(sb)) {
        refOut.refType = REF_STRING;
        refOut.refStringVal = sb.toString();
        ret = true;
    } else {
        this->bufIdx = saveIdx;
        sb.clear();
        if (this->eat_int(sb) > 0) {
            int intVal = 0;
            char *errorMsg = NULL;
            string intString = sb.toString();
            if (string_to_int(intString, &intVal, &errorMsg)) {
                refOut.refType = REF_INT;
                refOut.refIntVal = intVal;
                ret = true;
            } else {
                // integer conversion error
                string errorMsgStr;
                if (errorMsg) {
                    errorMsgStr = string(errorMsg);
                    free(errorMsg);
                } else {
                    errorMsgStr = "";
                }
                if (triggerError) {
                    this->error(PARSE_REF_INTEGER_ERROR,
                            intString.c_str(), errorMsgStr.c_str());
                } else {
                    this->warning(PARSE_REF_INTEGER_ERROR_STR,
                            intString.c_str(), errorMsgStr.c_str());
                }
            }
        } else {
            // try eating AttrRef
            this->bufIdx = saveIdx;
            AttrRef attrRef = this->eat_attrRef(sb);
            if (ATTR_INVALID != attrRef.attr) {
                // TODO: Are the checks in this block necessary
                RefSynType refSynType = attrRef_to_RefSynType(attrRef);
                if (REFSYN_INVALID != refSynType) {
                    refOut.refType = REF_ATTRREF;
                    refOut.refStringVal = attrRef.syn;
                    refOut.refSynType = refSynType;
                    ret = true;
                } else {
                    // invalid AttrRef
                    if (triggerError) {
                        this->error(PARSE_REF_ATTRREF_ERROR,
                                sb.c_str());
                    } else {
                        this->warning(PARSE_REF_ATTRREF_ERROR_STR,
                                sb.c_str());
                    }
                }
            } else {
                this->bufIdx = saveIdx;
                // parse synonym
                if (this->eat_synonym(sb)) {
                    string synName = sb.toString();
                    DesignEnt entType =
                            this->retrieve_syn_type(synName);
                    if (ENT_INVALID == entType) {
                        this->error(PARSE_WITHCLAUSE_REF_SYNONYM_UNDECLARED,
                                synName.c_str());
                    }
                    if (ENT_PROGLINE != entType) {
                        this->error(PARSE_WITHCLAUSE_REF_SYNONYM_NOT_PROGLINE,
                                synName.c_str(),
                                entity_type_to_string(entType));
                    }
                    refOut.refType = REF_ATTRREF;
                    refOut.refStringVal = synName;
                    refOut.refSynType = REFSYN_PROGLINE;
                    ret = true;
                } else {
                    // parsing of ref has failed at this stage
                    this->bufIdx = saveIdx;
                    if (triggerError) {
                        this->eat_while<is_space>(sb);
                        sb.clear();
                        this->eat_while<not_space>(sb);
                        assert(NULL != lhsRef);
                        this->error(PARSE_WITHCLAUSE_EXPECT_REF_ON_RHS,
                                lhsRef->toString().c_str(),
                                sb.c_str());
                    }
                }
            }
        }
    }
    return ret;
}

bool PQLParser::eat_withClause_one(StringBuffer &sb,
        WithClause& withClause, ParseError *qinfoAddError)
{
    assert(NULL != qinfoAddError);
    int saveIdx = this->bufIdx;
    char *errorMsg = NULL;
    Ref leftRef, rightRef;
    AttrRef attrRef;
    bool parsedSynonym;
    sb.clear();
    if (!this->eat_ref(sb, leftRef, false, NULL)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    // eat space
    this->eat_while<is_space>(sb);
    // eat '=' sign
    if (!this->eat_equal()) {
        RESTORE_AND_RET(false, saveIdx);
    }
    // eat space after '='
    this->eat_while<is_space>(sb);
    // seen left ref and '=', must be a WithClause
    // just error out from now on
    attrRef = AttrRef();
    this->eat_ref(sb, rightRef, true, &leftRef);
    // set left and right ref
    withClause.leftRef = leftRef;
    withClause.rightRef = rightRef;
    // With Clause with invalid ref(s), shouldnt happen
    if (!WithClause::valid_refs(withClause)) {
        sb.clear();
        sb.append(withClause.toString());
        this->error(PARSE_WITHCLAUSE_REFS_INVALID, sb.c_str());
    }
    // type mismatch between left and right Ref
    if (!WithClause::valid_type(withClause)) {
        BaseType leftRefType = Ref::get_BaseType(withClause.leftRef);
        BaseType rightRefType = Ref::get_BaseType(withClause.rightRef);
        sb.clear();
        sb.append(withClause.toString());
        this->error(PARSE_WITHCLAUSE_TYPE_MISMATCH, sb.c_str(),
                baseType_to_string(leftRefType),
                baseType_to_string(rightRefType));
    }
    *qinfoAddError = this->qinfo->add_withClause(withClause, &errorMsg);
    if (errorMsg) {
        this->warning(errorMsg);
        free(errorMsg);
    }
    return true;
}

bool PQLParser::eat_withClause(StringBuffer& sb) throw(ParseError)
{
    int saveIdx = this->bufIdx;
    WithClause withClause, prevWithClause;
    ParseError qinfoAddError;
    char *errorMsg;
    if (this->eat_space() <= 0) {
        RESTORE_AND_RET(false, saveIdx);
    }
    if (!this->eat_withClause_one(sb, withClause, &qinfoAddError)) {
        RESTORE_AND_RET(false, saveIdx);
    }
    if (PARSE_OK != qinfoAddError) {
        this->parseErr = qinfoAddError;
    }
    // carry on passing despite the query being false to help
    // the user catch more errors
    while (1) {
        saveIdx = this->bufIdx;
        if (this->eat_space() <= 0) {
            break;
        }
        if (!this->eat_and(sb)) {
            this->bufIdx = saveIdx;
            break;
        }
        if (this->eat_space() <= 0) {
            sb.clear();
            this->eat_while<not_space>(sb);
            this->error(PARSE_WITHCLAUSE_AND_NOSEP, sb.c_str());
        }
        prevWithClause = withClause;
        withClause = WithClause();
        if (!this->eat_withClause_one(sb, withClause, &qinfoAddError)) {
            // Read 'and', so we naturally expect a with clause
            this->eat_till_end(sb);
            this->error(PARSE_WITHCLAUSE_EXPECT_WITH, sb.c_str(),
                    prevWithClause.toString().c_str());
        }
        if (PARSE_OK != qinfoAddError) {
            this->parseErr = qinfoAddError;
        }
        // carry on passing despite the query being false to help
        // the user catch more errors
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
        } else if (this->eat_with(sb) && this->eat_withClause(sb)) {
            // nothing
        } else if (this->eat_pattern(sb) && this->eat_patternCond(sb)) {
            // nothing
        } else {
            break;
        }
    }
}

void PQLParser::parse(const string &s, bool showErrors_, bool showWarnings_)
{
    this->_parse(s, showErrors_, showWarnings_);
}

void PQLParser::parse(ostream *os, const string &s, bool showErrors_,
        bool showWarnings_)
{
    this->parseErrorStream = PQLParseErrorStream(os);
    this->_parse(s, showErrors_, showWarnings_);
}

void PQLParser::_parse(const string &s, bool showErrors_, bool showWarnings_)
{
    StringBuffer sb;
    int saveIdx;
    this->bufIdx = 0;
    this->buf = s;
    this->bufLen = this->buf.size();
    this->showErrors = showErrors_;
    this->showWarnings = showWarnings_;
    this->entTable.clear();
    this->entVec.clear();
    this->parseErr = PARSE_OK;
    try {
        this->eat_decls();
        qinfo->reset(this->entTable, this->entVec);
        if (!this->eat_select(sb)) {
            this->error(PARSE_NO_SELECT_AFTER_DECL, sb.c_str());
            return;
        }
        if (this->eat_space() <= 0) {
            this->error(PARSE_NO_SEP_AFTER_SELECT, false,
                "Expected whitespace after Select");
            return;
        }
        saveIdx = this->bufIdx;
        if (this->eat_select_boolean(sb)) {
            this->qinfo->set_select_boolean();
        } else if (this->eat_select_tuple(sb)) {
            // nothing
        } else {
            sb.clear();
            this->eat_while<not_comma_space>(sb);
            this->error(PARSE_SELECT_NOTHING, sb.c_str());
        }

        this->eat_select_stwithpat(sb);
        this->eat_space();
        if (this->bufIdx != this->bufLen) {
            this->error(PARSE_END_OF_QUERY_ERROR,
                this->buf.c_str() + this->bufIdx);
        }
    } catch (ParseError err_) {
        // kill qinfo upon encountering parse error
        this->parseErr = err_;
        this->qinfo->kill();
    }
}

#undef RESTORE_AND_RET