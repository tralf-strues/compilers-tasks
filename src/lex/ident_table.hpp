#pragma once

#include <lex/token_type.hpp>

#include <string>
#include <map>

#include <fmt/core.h>

namespace lex {

class IdentTable {
 public:
  IdentTable() {
    Populate();
  }

  // Use-of-string-view-for-map-lookup
  // https://stackoverflow.com/questions/35525777

  std::optional<TokenType> LookupWord(const std::string_view word) {
    auto it = map_.find(word);
    return (it != map_.end()) ? std::optional(it->second) : std::nullopt;
  }

 private:
  void Populate() {
    /* One-two character tokens */
    // map_.emplace("+",  TokenType::kPlus);
    // map_.emplace("-",  TokenType::kMinus);
    // map_.emplace("*",  TokenType::kStar);
    // map_.emplace("/",  TokenType::kDiv);
    // map_.emplace("=",  TokenType::kAssign);
    // map_.emplace("==", TokenType::kEquals);
    // map_.emplace("!=", TokenType::kNotEq);
    // map_.emplace("!",  TokenType::kNot);
    // map_.emplace("<",  TokenType::kLess);
    // map_.emplace(">",  TokenType::kGreater);
    // map_.emplace("(",  TokenType::kLeftParen);
    // map_.emplace(")",  TokenType::kRightParen);
    // map_.emplace("{",  TokenType::kLeftCBrace);
    // map_.emplace("}",  TokenType::kRightCBrace);
    // map_.emplace(",",  TokenType::kComma);
    // map_.emplace(";",  TokenType::kColon);

    /* Keywords */
    map_.emplace("true",    TokenType::kTrue);
    map_.emplace("false",   TokenType::kFalse);
    map_.emplace("fun",     TokenType::kFun);
    map_.emplace("var",     TokenType::kVar);
    map_.emplace("if",      TokenType::kIf);
    map_.emplace("then",    TokenType::kThen);
    map_.emplace("else",    TokenType::kElse);
    map_.emplace("return",  TokenType::kReturn);
  }

 private:
  // What-are-transparent-comparators
  // https://stackoverflow.com/questions/20317413

  std::map<std::string, TokenType, std::less<>> map_;
};

}  // namespace lex
