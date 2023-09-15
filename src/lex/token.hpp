#pragma once

#include <lex/scanner.hpp>

#include <variant>
#include <cstddef>

namespace lex {

//////////////////////////////////////////////////////////////////////

struct Token {
  TokenType type;

  union {
    int32_t number;
    std::string_view string;
    std::string_view identifier;
  } value;
  
  Location location;
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
