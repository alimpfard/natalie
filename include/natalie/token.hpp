#pragma once

#include "natalie.hpp"

namespace Natalie {

struct Token : public gc {
    enum class Type {
        AliasKeyword,
        And,
        AndKeyword,
        Arrow,
        BareName,
        BeginKeyword,
        BEGINKeyword,
        BitwiseAnd,
        BinaryOnesComplement,
        BitwiseOr,
        BitwiseXor,
        BreakKeyword,
        CaseKeyword,
        ClassKeyword,
        ClassVariable,
        Comma,
        Comment,
        Comparison,
        Constant,
        ConstantResolution,
        DefinedKeyword,
        DefKeyword,
        Divide,
        DivideEqual,
        DoKeyword,
        Dot,
        DotDot,
        DotDotDot,
        ElseKeyword,
        ElsifKeyword,
        ENCODINGKeyword,
        EndKeyword,
        ENDKeyword,
        EnsureKeyword,
        Eof,
        Eol,
        Equal,
        EqualEqual,
        EqualEqualEqual,
        EvaluateToStringBegin,
        EvaluateToStringEnd,
        Exponent,
        ExponentEqual,
        FalseKeyword,
        FILEKeyword,
        Float,
        ForKeyword,
        GlobalVariable,
        GreaterThan,
        GreaterThanOrEqual,
        HashRocket,
        IfKeyword,
        InKeyword,
        InstanceVariable,
        Integer,
        InterpolatedStringBegin,
        InterpolatedStringEnd,
        Invalid,
        LCurlyBrace,
        LBracket,
        LeftShift,
        LessThan,
        LessThanOrEqual,
        LINEKeyword,
        LParen,
        Match,
        Minus,
        MinusEqual,
        ModuleKeyword,
        Modulus,
        ModulusEqual,
        Multiply,
        MultiplyEqual,
        NextKeyword,
        NilKeyword,
        Not,
        NotEqual,
        NotKeyword,
        NotMatch,
        Or,
        OrKeyword,
        PercentLowerI,
        PercentLowerW,
        PercentUpperI,
        PercentUpperW,
        Plus,
        PlusEqual,
        RCurlyBrace,
        RBracket,
        RedoKeyword,
        Regexp,
        RescueKeyword,
        RetryKeyword,
        ReturnKeyword,
        RightShift,
        RParen,
        SafeNavigation,
        SelfKeyword,
        Semicolon,
        String,
        SuperKeyword,
        Symbol,
        SymbolKey,
        TernaryColon,
        TernaryQuestion,
        ThenKeyword,
        TrueKeyword,
        UndefKeyword,
        UnlessKeyword,
        UnterminatedRegexp,
        UnterminatedString,
        UntilKeyword,
        WhenKeyword,
        WhileKeyword,
        YieldKeyword,
    };

    Token() { }

    Token(Type type, const char *file, size_t line, size_t column)
        : m_type { type }
        , m_file { file }
        , m_line { line }
        , m_column { column } { }

    Token(Type type, const char *literal, const char *file, size_t line, size_t column)
        : m_type { type }
        , m_literal { literal }
        , m_file { file }
        , m_line { line }
        , m_column { column } {
        assert(m_literal);
    }

    Token(Type type, char literal, const char *file, size_t line, size_t column)
        : m_type { type }
        , m_file { file }
        , m_line { line }
        , m_column { column } {
        char buf[2] = { literal, 0 };
        m_literal = GC_STRDUP(buf);
    }

    Token(Type type, nat_int_t integer, const char *file, size_t line, size_t column)
        : m_type { type }
        , m_integer { integer }
        , m_file { file }
        , m_line { line }
        , m_column { column } { }

    Token(Type type, double dbl, const char *file, size_t line, size_t column)
        : m_type { type }
        , m_double { dbl }
        , m_file { file }
        , m_line { line }
        , m_column { column } { }

    static Token invalid() { return Token { Token::Type::Invalid, nullptr, 0, 0 }; }

    Type type() { return m_type; }
    void set_type(Token::Type type) { m_type = type; }

    const char *literal() { return m_literal; }
    void set_literal(const char *literal) { m_literal = literal; }
    void set_literal(std::string literal) { m_literal = GC_STRDUP(literal.c_str()); }

    nat_int_t get_integer() { return m_integer; }
    double get_double() { return m_double; }

    const char *type_value(Env *env) {
        switch (m_type) {
        case Type::AliasKeyword:
            return "alias";
        case Type::AndKeyword:
            return "and";
        case Type::And:
            return "&&";
        case Type::Arrow:
            return "->";
        case Type::BareName:
            return "name";
        case Type::BeginKeyword:
            return "begin";
        case Type::BEGINKeyword:
            return "BEGIN";
        case Type::BitwiseAnd:
            return "&";
        case Type::BinaryOnesComplement:
            return "~";
        case Type::BitwiseOr:
            return "|";
        case Type::BitwiseXor:
            return "^";
        case Type::BreakKeyword:
            return "break";
        case Type::CaseKeyword:
            return "case";
        case Type::ClassKeyword:
            return "class";
        case Type::ClassVariable:
            return "cvar";
        case Type::Comma:
            return ",";
        case Type::Comment:
            return "comment";
        case Type::Comparison:
            return "<=>";
        case Type::ConstantResolution:
            return "::";
        case Type::Constant:
            return "constant";
        case Type::DefinedKeyword:
            return "defined?";
        case Type::DefKeyword:
            return "def";
        case Type::DivideEqual:
            return "/=";
        case Type::Divide:
            return "/";
        case Type::DoKeyword:
            return "do";
        case Type::DotDotDot:
            return "...";
        case Type::DotDot:
            return "..";
        case Type::Dot:
            return ".";
        case Type::ElseKeyword:
            return "else";
        case Type::ElsifKeyword:
            return "elsif";
        case Type::ENCODINGKeyword:
            return "__ENCODING__";
        case Type::EndKeyword:
            return "end";
        case Type::ENDKeyword:
            return "END";
        case Type::EnsureKeyword:
            return "ensure";
        case Type::Eof:
            return "EOF";
        case Type::Eol:
            return "\n";
        case Type::EqualEqualEqual:
            return "===";
        case Type::EqualEqual:
            return "==";
        case Type::Equal:
            return "=";
        case Type::EvaluateToStringBegin:
            return "evstr";
        case Type::EvaluateToStringEnd:
            return "evstrend";
        case Type::Exponent:
            return "**";
        case Type::ExponentEqual:
            return "**=";
        case Type::FalseKeyword:
            return "false";
        case Type::FILEKeyword:
            return "__FILE__";
        case Type::Float:
            return "float";
        case Type::ForKeyword:
            return "for";
        case Type::GlobalVariable:
            return "gvar";
        case Type::GreaterThanOrEqual:
            return ">=";
        case Type::GreaterThan:
            return ">";
        case Type::HashRocket:
            return "=>";
        case Type::IfKeyword:
            return "if";
        case Type::InKeyword:
            return "in";
        case Type::InstanceVariable:
            return "ivar";
        case Type::Integer:
            return "integer";
        case Type::InterpolatedStringBegin:
            return "dstr";
        case Type::InterpolatedStringEnd:
            return "dstrend";
        case Type::Invalid:
            env->raise("SyntaxError", "%d: syntax error, unexpected '%s'", m_line + 1, m_literal);
        case Type::LCurlyBrace:
            return "{";
        case Type::LBracket:
            return "[";
        case Type::LeftShift:
            return "<<";
        case Type::LessThanOrEqual:
            return "<=";
        case Type::LessThan:
            return "<";
        case Type::LINEKeyword:
            return "__LINE__";
        case Type::LParen:
            return "(";
        case Type::Match:
            return "=~";
        case Type::MinusEqual:
            return "-=";
        case Type::Minus:
            return "-";
        case Type::ModuleKeyword:
            return "module";
        case Type::ModulusEqual:
            return "%=";
        case Type::Modulus:
            return "%";
        case Type::MultiplyEqual:
            return "*=";
        case Type::Multiply:
            return "*";
        case Type::NextKeyword:
            return "next";
        case Type::NilKeyword:
            return "nil";
        case Type::NotEqual:
            return "!=";
        case Type::NotKeyword:
            return "not";
        case Type::NotMatch:
            return "!~";
        case Type::Not:
            return "!";
        case Type::OrKeyword:
            return "or";
        case Type::Or:
            return "||";
        case Type::PercentLowerI:
            return "%i";
        case Type::PercentLowerW:
            return "%w";
        case Type::PercentUpperI:
            return "%I";
        case Type::PercentUpperW:
            return "%W";
        case Type::PlusEqual:
            return "+=";
        case Type::Plus:
            return "+";
        case Type::RCurlyBrace:
            return "}";
        case Type::RBracket:
            return "]";
        case Type::RedoKeyword:
            return "redo";
        case Type::Regexp:
            return "regexp";
        case Type::RescueKeyword:
            return "rescue";
        case Type::RetryKeyword:
            return "retry";
        case Type::ReturnKeyword:
            return "return";
        case Type::RightShift:
            return ">>";
        case Type::RParen:
            return ")";
        case Type::SafeNavigation:
            return "&.";
        case Type::SelfKeyword:
            return "self";
        case Type::Semicolon:
            return ";";
        case Type::String:
            return "string";
        case Type::SuperKeyword:
            return "super";
        case Type::SymbolKey:
            return "symbol_key";
        case Type::Symbol:
            return "symbol";
        case Type::TernaryColon:
            return ":";
        case Type::TernaryQuestion:
            return "?";
        case Type::ThenKeyword:
            return "then";
        case Type::TrueKeyword:
            return "true";
        case Type::UndefKeyword:
            return "undef";
        case Type::UnlessKeyword:
            return "unless";
        case Type::UnterminatedRegexp:
            env->raise("SyntaxError", "unterminated regexp meets end of file");
        case Type::UnterminatedString:
            env->raise("SyntaxError", "unterminated string meets end of file at line %i and column %i: %s", m_line, m_column, m_literal);
        case Type::UntilKeyword:
            return "until";
        case Type::WhenKeyword:
            return "when";
        case Type::WhileKeyword:
            return "while";
        case Type::YieldKeyword:
            return "yield";
        }
        NAT_UNREACHABLE();
    }

    Value *to_ruby(Env *env, bool with_line_and_column_numbers = false) {
        if (m_type == Type::Eof)
            return env->nil_obj();
        const char *type = type_value(env);
        auto hash = new HashValue { env };
        hash->put(env, SymbolValue::intern(env, "type"), SymbolValue::intern(env, type));
        switch (m_type) {
        case Type::PercentLowerI:
        case Type::PercentUpperI:
        case Type::PercentLowerW:
        case Type::PercentUpperW:
        case Type::Regexp:
        case Type::String:
            hash->put(env, SymbolValue::intern(env, "literal"), new StringValue { env, m_literal });
            break;
        case Type::BareName:
        case Type::ClassVariable:
        case Type::Constant:
        case Type::GlobalVariable:
        case Type::InstanceVariable:
        case Type::Symbol:
        case Type::SymbolKey:
            hash->put(env, SymbolValue::intern(env, "literal"), SymbolValue::intern(env, m_literal));
            break;
        case Type::Float:
            hash->put(env, SymbolValue::intern(env, "literal"), new FloatValue { env, m_double });
            break;
        case Type::Integer:
            hash->put(env, SymbolValue::intern(env, "literal"), new IntegerValue { env, m_integer });
            break;
        default:
            void();
        }
        if (with_line_and_column_numbers) {
            hash->put(env, SymbolValue::intern(env, "line"), new IntegerValue { env, static_cast<nat_int_t>(m_line) });
            hash->put(env, SymbolValue::intern(env, "column"), new IntegerValue { env, static_cast<nat_int_t>(m_column) });
        }
        return hash;
    }

    bool is_bare_name() { return m_type == Type::BareName; }
    bool is_closing_token() { return m_type == Type::RBracket || m_type == Type::RCurlyBrace || m_type == Type::RParen; }
    bool is_comma() { return m_type == Type::Comma; }
    bool is_comment() { return m_type == Type::Comment; }
    bool is_double_quoted_string() { return m_type == Type::String && m_double_quoted; }
    bool is_else_keyword() { return m_type == Type::ElseKeyword; }
    bool is_elsif_keyword() { return m_type == Type::ElsifKeyword; }
    bool is_end_keyword() { return m_type == Type::EndKeyword; }
    bool is_end_of_expression() { return m_type == Type::Eol || m_type == Type::Eof || is_expression_modifier(); }
    bool is_eof() { return m_type == Type::Eof; }
    bool is_eol() { return m_type == Type::Eol; }
    bool is_expression_modifier() { return m_type == Type::IfKeyword || m_type == Type::UnlessKeyword || m_type == Type::WhileKeyword || m_type == Type::UntilKeyword; }
    bool is_lparen() { return m_type == Type::LParen; }
    bool is_newline() { return m_type == Type::Eol; }
    bool is_rparen() { return m_type == Type::RParen; }
    bool is_semicolon() { return m_type == Type::Semicolon; }
    bool is_valid() { return m_type != Type::Invalid; }
    bool is_when_keyword() { return m_type == Type::WhenKeyword; }

    void validate(Env *env) {
        if (!is_valid()) {
            type_value(env);
            NAT_UNREACHABLE();
        }
    }

    bool can_precede_method_name() {
        return m_type == Token::Type::Dot || m_type == Token::Type::ConstantResolution || m_type == Token::Type::DefKeyword;
    }

    bool can_follow_collapsible_newline() {
        return m_type == Token::Type::RCurlyBrace
            || m_type == Token::Type::RBracket
            || m_type == Token::Type::RParen
            || m_type == Token::Type::TernaryColon;
    }

    bool can_precede_collapsible_newline() {
        return m_type == Token::Type::And
            || m_type == Token::Type::AndKeyword
            || m_type == Token::Type::Arrow
            || m_type == Token::Type::BitwiseAnd
            || m_type == Token::Type::BinaryOnesComplement
            || m_type == Token::Type::BitwiseOr
            || m_type == Token::Type::BitwiseXor
            || m_type == Token::Type::Comma
            || m_type == Token::Type::Comparison
            || m_type == Token::Type::ConstantResolution
            || m_type == Token::Type::Divide
            || m_type == Token::Type::DivideEqual
            || m_type == Token::Type::Dot
            || m_type == Token::Type::DotDot
            || m_type == Token::Type::Equal
            || m_type == Token::Type::EqualEqual
            || m_type == Token::Type::EqualEqualEqual
            || m_type == Token::Type::Exponent
            || m_type == Token::Type::ExponentEqual
            || m_type == Token::Type::GreaterThan
            || m_type == Token::Type::GreaterThanOrEqual
            || m_type == Token::Type::HashRocket
            || m_type == Token::Type::InKeyword
            || m_type == Token::Type::LCurlyBrace
            || m_type == Token::Type::LBracket
            || m_type == Token::Type::LeftShift
            || m_type == Token::Type::LessThan
            || m_type == Token::Type::LessThanOrEqual
            || m_type == Token::Type::LParen
            || m_type == Token::Type::Match
            || m_type == Token::Type::Minus
            || m_type == Token::Type::MinusEqual
            || m_type == Token::Type::Modulus
            || m_type == Token::Type::ModulusEqual
            || m_type == Token::Type::Multiply
            || m_type == Token::Type::MultiplyEqual
            || m_type == Token::Type::Not
            || m_type == Token::Type::NotEqual
            || m_type == Token::Type::NotMatch
            || m_type == Token::Type::Or
            || m_type == Token::Type::OrKeyword
            || m_type == Token::Type::Plus
            || m_type == Token::Type::PlusEqual
            || m_type == Token::Type::RightShift
            || m_type == Token::Type::SafeNavigation
            || m_type == Token::Type::TernaryColon
            || m_type == Token::Type::TernaryQuestion;
    }

    bool has_sign() { return m_has_sign; }
    void set_has_sign(bool has_sign) { m_has_sign = has_sign; }

    const char *file() { return m_file; }
    size_t line() { return m_line; }
    size_t column() { return m_column; }

    bool whitespace_precedes() { return m_whitespace_precedes; }
    void set_whitespace_precedes(bool whitespace_precedes) { m_whitespace_precedes = whitespace_precedes; }

    bool double_quoted() { return m_double_quoted; }
    void set_double_quoted(bool double_quoted) { m_double_quoted = double_quoted; }

private:
    Type m_type { Type::Invalid };
    const char *m_literal { nullptr };
    nat_int_t m_integer { 0 };
    double m_double { 0 };
    bool m_has_sign { false };
    const char *m_file { nullptr };
    size_t m_line { 0 };
    size_t m_column { 0 };
    bool m_whitespace_precedes { false };
    bool m_double_quoted { false };
};
}
