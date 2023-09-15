#include <lex/lexer.hpp>

namespace lex {

Lexer::Lexer(std::istream& source) : scanner_(source) {
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetNextToken() {
  SkipWhitespace();

  SkipComments();

  if (auto op = MatchOperators()) {
    return *op;
  }

  if (auto lit = MatchLiterls()) {
    return *lit;
  }

  if (auto word = MatchWords()) {
    return *word;
  }

  FMT_ASSERT(false, "Could not match any token\n");
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetPreviousToken() {
  return prev_;
}

////////////////////////////////////////////////////////////////////

void Lexer::Advance() {
  prev_ = peek_;

  if (advanced_) {
    advanced_ = false;
  } else {
    advanced_ = true;
    peek_ = GetNextToken();
  }
}

////////////////////////////////////////////////////////////////////

bool Lexer::Matches(lex::TokenType type) {
  if (Peek().type != type) {
    return false;
  }

  Advance();
  return true;
}

////////////////////////////////////////////////////////////////////

Token Lexer::Peek() {
  if (!advanced_) {
    Advance();
  }

  return peek_;
}

////////////////////////////////////////////////////////////////////

bool IsWhitespace(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void Lexer::SkipWhitespace() {
  while (IsWhitespace(scanner_.CurrentSymbol())) {
    scanner_.MoveRight();
  }
}

////////////////////////////////////////////////////////////////////

void Lexer::SkipComments() {
  while (scanner_.CurrentSymbol() == '#') {
    scanner_.MoveNextLine();
    SkipWhitespace();
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchOperators() {
  auto token_type = MatchOperator();
  if (!token_type) {
    return std::nullopt;
  }

  Token token{};
  token.type     = token_type.value();
  token.location = scanner_.CurrentLocation();

  return token;
}

////////////////////////////////////////////////////////////////////

std::optional<TokenType> Lexer::MatchOperator() {
  #define CASE_SINGLE(symbol, token_type) \
    case symbol: {                        \
      scanner_.MoveRight();               \
      return token_type;                  \
    }

  #define CASE_DOUBLE(symbols, type_single, type_double) \
    case symbols[0]: {                                   \
      scanner_.MoveRight();                              \
      if (scanner_.CurrentSymbol() == symbols[1]) {      \
        scanner_.MoveRight();                            \
        return type_double;                              \
      } else {                                           \
        return type_single;                              \
      }                                                  \
    }

  switch (scanner_.CurrentSymbol()) {
    CASE_SINGLE('+', TokenType::kPlus);
    CASE_SINGLE('-', TokenType::kMinus);
    CASE_SINGLE('*', TokenType::kStar);
    CASE_SINGLE('/', TokenType::kDiv);
    CASE_DOUBLE("==", TokenType::kAssign, TokenType::kEquals);
    CASE_DOUBLE("!=", TokenType::kNot, TokenType::kNotEq);
    CASE_SINGLE('<', TokenType::kLess);
    CASE_SINGLE('>', TokenType::kGreater);
    CASE_SINGLE('(', TokenType::kLeftParen);
    CASE_SINGLE(')', TokenType::kRightParen);
    CASE_SINGLE('{', TokenType::kLeftCBrace);
    CASE_SINGLE('}', TokenType::kRightCBrace);
    CASE_SINGLE(',', TokenType::kComma);
    CASE_SINGLE(';', TokenType::kColon);
  };

  #undef CASE_SINGLE
  #undef CASE_DOUBLE

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchLiterls() {
  if (auto num_token = MatchNumericLiteral()) {
    return num_token;
  }

  if (auto string_token = MatchStringLiteral()) {
    return string_token;
  }

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<int32_t> CharToDigit(char ch) {
  return (ch >= '0' && ch <= '9') ? std::optional<int32_t>(ch - '0') : std::nullopt;
}
 
std::optional<Token> Lexer::MatchNumericLiteral() {
  Location location = scanner_.CurrentLocation();

  int32_t number{0};
  bool valid{false};

  while (auto digit = CharToDigit(scanner_.CurrentSymbol())) {
    number *= 10;
    number += *digit;

    valid = true;

    scanner_.MoveRight();
  }

  if (!valid) {
    return std::nullopt;
  }

  Token token{};
  token.type = TokenType::kNumber;
  token.value.number = number;
  token.location = location;

  return token;
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchStringLiteral() {
  if (scanner_.CurrentSymbol() != '\"') {
    return std::nullopt;
  }

  Location location = scanner_.CurrentLocation();

  scanner_.MoveRight();  // skip opening '\"'
  size_t start = scanner_.CurrentOffset();
  size_t length = 0;
  while (scanner_.CurrentSymbol() != '\"') {
    scanner_.MoveRight();
    ++length;
  }
  scanner_.MoveRight();  // skip closing '\"'

  Token token{};
  token.type = TokenType::kString;
  token.location = location;
  token.value.string = scanner_.SubString(start, length);

  return token;
}

////////////////////////////////////////////////////////////////////

bool IsWordSymbol(char symbol) {
  return std::isalnum(symbol) || symbol == '_';
}

std::optional<Token> Lexer::MatchWords() {
  Location location = scanner_.CurrentLocation();

  size_t start = scanner_.CurrentOffset();
  size_t length = 0;
  while (IsWordSymbol(scanner_.CurrentSymbol())) {
    scanner_.MoveRight();
    ++length;
  }

  if (length == 0) {
    return std::nullopt;
  }

  Token token{};
  token.location = location;

  auto word = scanner_.SubString(start, length);

  auto keyword_type = table_.LookupWord(word);
  if (keyword_type) {
    token.type = keyword_type.value();
  } else {
    token.type = TokenType::kIdentifier;
    token.value.identifier = word;
  }

  return token;
}

}  // namespace lex
