#pragma once

#include <lex/token_type.hpp>
#include <lex/location.hpp>

#include <fmt/core.h>

#include <string_view>
#include <filesystem>
#include <iostream>
#include <istream>
#include <vector>
#include <span>

namespace lex {

//////////////////////////////////////////////////////////////////////

class Scanner {
 public:
  Scanner(std::istream& source);

  const Location& CurrentLocation() const;

  char CurrentSymbol() const;
  char NextSymbol() const;

  void MoveRight();
  void MoveNextLine();

  size_t CurrentOffset() const;
  std::string_view SubString(size_t start, size_t length) const;

 private:
  std::string buffer_;

  size_t cur_offset_{0};
  Location current_location_{};
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
