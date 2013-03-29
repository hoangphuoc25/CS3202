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
#include "PQL.h"
#include "StringBuffer.h"
#include "SPAUtils.h"

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
    bool eat_equal();
    template<bool (*fn)(char ch)>
        int eat_while(StringBuffer &sb);
    bool eat_synonym(StringBuffer &sb);
    AttrRef eat_attrRef(StringBuffer &sb);
    bool eat_attrName(StringBuffer &sb);
    bool eat_alpha_string(StringBuffer &sb, const char *s);
    bool eat_alpha_strings(StringBuffer &sb, int nrStrs, ...);
    bool eat_alpha_star_string(StringBuffer &sb, const char *s);
    bool eat_alpha_underscore_string(StringBuffer &sb, const char *s);
    bool eat_design_entity(StringBuffer &sb);
    bool eat_ident_string(StringBuffer &sb, const char *s);
    /// Triggers parsing error on:
    /// 1. invalid identity string (PARSE_DQUOTED_IDENT_INVALID)
    /// 2. missing closing quote (PARSE_DQUOTED_IDENT_MISSING_CLOSE_QUOTE)
    bool eat_dquoted_ident(StringBuffer &sb);
    bool eat_string_till_ws(StringBuffer &sb, const char *s);
    int eat_int(StringBuffer &sb);
    /// Eats the entire PQL Query from this->bufIdx
    /// @param sb the StringBuffer to store the characters eaten
    void eat_till_end(StringBuffer& sb);
    bool eat_select(StringBuffer &sb);
    bool eat_select_tuple(StringBuffer &sb) throw(ParseError);
    AttrRef eat_select_tuple_elem(StringBuffer &sb) throw(ParseError);
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
    RelRefArgType eat_callRef(StringBuffer &sb);
    void eat_XRef_YRef(RelRefArgType (PQLParser::*eat_XRef)(StringBuffer &sb),
            RelRefArgType (PQLParser::*eat_YRef)(StringBuffer &sb),
            RelRef &relRef, StringBuffer &sb, char **errorMsg)
                throw(ParseError);
    void error_set_relRef_arg(ParseError parseErr_, const RelRef &relRef,
            const char *which, const StringBuffer &sb, char **errorMsg)
                throw(ParseError);
    void eat_entRef_varRef(RelRef &relRef, StringBuffer &sb, char **errorMsg)
            throw(ParseError);
    void eat_callRef_callRef(RelRef &relRef, StringBuffer &sb,
            char **errorMsg) throw(ParseError);
    void eat_stmtRef_stmtRef(RelRef &relRef, StringBuffer &sb,
            char **errorMsg) throw(ParseError);
    void eat_lineRef_lineRef(RelRef &relRef, StringBuffer &sb,
            char **errorMsg) throw(ParseError);
    bool relRef_finalize(RelRef &relRef, char **errorMsg);
    bool eat_relRef_generic(RelRef &relRef, StringBuffer &sb,
        bool (PQLParser::*eat_relRef_string_M) (StringBuffer &sb),
        RelRefType relRefType,
        void (PQLParser::*eat_arg_M)
            (RelRef &relRef, StringBuffer &sb, char **errorMsg));
    void error_add_relRef(ParseError parseErr_, const RelRef &relRef,
            char *errorMsg) throw(ParseError);
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
    PatCl eat_patternClause(StringBuffer &sb) throw(ParseError);
    bool eat_patternCond(StringBuffer &sb) throw(ParseError);
    /// Eats a ref.
    /// There are a few points where an error can occur
    /// 1. When parsing a double quoted identity string, the
    ///    PQLParser::eat_dquoted_ident method may result in an error
    /// 2. If PQLParser::eat_int successfully eats an integer but
    ///    the string_to_int function fails and the triggerError param
    ///    is set to true
    /// 3. PQLParser::eat_attrRef returns a valid AttrRef which somehow
    ///    fails to convert to a RefSynType. This should NEVER happen
    /// 4. We parse a synonym and it is either (a). not declared or
    ///    (b). not of type prog_line
    /// 5. Parsing of "IDENT", integer, AttrRef and ref all fail and the
    ///    triggerError param is set to true. This will mean we are
    ///    trying to parse the right hand side ref of a WithClause.
    ///    Since we have seen the '=', an error should be raised when
    ///    parsing of the right hand side ref fails.
    /// @param sb StringBuffer for parsing purposes
    /// @param refOut the Ref to modify upon successful parse
    /// @param triggerError whether to trigger an error if parsing
    ///                     fails at some point. This should only be
    ///                     set to true if we are parsing the right side
    ///                     of a WithClause
    /// @param lhsRef pointer to a Ref. This field should point to
    ///               a valid Ref if triggerError is true, otherwise
    ///               it should contain NULL.
    /// @return true if parsing a Ref succeeds, false otherwise
    bool eat_ref(StringBuffer &sb, Ref& refOut, bool triggerError,
            Ref *lhsRef);
    bool eat_withClause_one(StringBuffer &sb, WithClause& WithClause,
            ParseError *qinfoAddError);
    bool eat_withClause(StringBuffer& sb) throw(ParseError);
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

#endif