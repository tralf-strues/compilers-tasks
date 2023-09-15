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

const char* FormatTokenType(TokenType type);

////////////////////////////////////////////////////////////////

}  // namespace lex
