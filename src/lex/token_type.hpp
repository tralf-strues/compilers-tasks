#pragma once

#include <cstdlib>

namespace lex {

//////////////////////////////////////////////////////////////////////

enum class TokenType : uint32_t {
  /* One-two character tokens */
  kPlus,
  kMinus,
  kStar,
  kDiv,
  kAssign,
  kEquals,
  kNotEq,
  kNot,
  kLess,
  kGreater,
  kLeftParen,
  kRightParen,
  kLeftCBrace,
  kRightCBrace,
  kComma,
  kColon,

  /* Keywords */
  kTrue,
  kFalse,
  kFun,
  kVar,
  kIf,
  kThen,
  kElse,
  kReturn,

  /* Literals */
  kNumber,
  kString,
  kIdentifier,

  /* Other */
  kEOF
};

////////////////////////////////////////////////////////////////

inline const char* FormatTokenType(TokenType type) {
  switch (type) {
    case TokenType::kPlus:        { return "+"; }
    case TokenType::kMinus:       { return "-"; }
    case TokenType::kStar:        { return "*"; }
    case TokenType::kDiv:         { return "/"; }
    case TokenType::kAssign:      { return "="; }
    case TokenType::kEquals:      { return "=="; }
    case TokenType::kNotEq:       { return "!="; }
    case TokenType::kNot:         { return "!"; }
    case TokenType::kLess:        { return "<"; }
    case TokenType::kGreater:     { return ">"; }
    case TokenType::kLeftParen:   { return "("; }
    case TokenType::kRightParen:  { return ")"; }
    case TokenType::kLeftCBrace:  { return "{"; }
    case TokenType::kRightCBrace: { return "}"; }
    case TokenType::kComma:       { return ","; }
    case TokenType::kColon:       { return ";"; }
    case TokenType::kTrue:        { return "true"; }
    case TokenType::kFalse:       { return "false"; }
    case TokenType::kFun:         { return "fun"; }
    case TokenType::kVar:         { return "var"; }
    case TokenType::kIf:          { return "if"; }
    case TokenType::kThen:        { return "then"; }
    case TokenType::kElse:        { return "else"; }
    case TokenType::kReturn:      { return "return"; }

    default: { return ""; }
  }

  return "";
}

////////////////////////////////////////////////////////////////

}  // namespace lex
