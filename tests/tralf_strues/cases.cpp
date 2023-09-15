#include <lex/lexer.hpp>

// Finally,
#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <sstream>

//////////////////////////////////////////////////////////////////////

TEST_CASE("Lexer: Just works", "[lex]") {
  std::stringstream source("1 + 2");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 1);
  CHECK(l.Matches(lex::TokenType::kPlus));
  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 2);
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Braces", "[lex]") {
  std::stringstream source("1 + (1)");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 1);
  CHECK(l.Matches(lex::TokenType::kPlus));
  CHECK(l.Matches(lex::TokenType::kLeftParen));
  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 1);
  CHECK(l.Matches(lex::TokenType::kRightParen));
}

///////////////////////////////////////////////////////////////////

TEST_CASE("Keywords", "[lex]") {
  std::stringstream source(
      "var   fun   if else "
      "return   true false  ");
  lex::Lexer l{source};
  CHECK(l.Matches(lex::TokenType::kVar));
  CHECK(l.Matches(lex::TokenType::kFun));
  CHECK(l.Matches(lex::TokenType::kIf));
  CHECK(l.Matches(lex::TokenType::kElse));
  CHECK(l.Matches(lex::TokenType::kReturn));
  CHECK(l.Matches(lex::TokenType::kTrue));
  CHECK(l.Matches(lex::TokenType::kFalse));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Consequent", "[lex]") {
  std::stringstream source("!true");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kNot));
  CHECK(l.Matches(lex::TokenType::kTrue));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Comments", "[lex]") {
  std::stringstream source(
      "# Comment if var a = 1; \n"
      "# One more comment \n"
      "1 # Token then comment \n"  // <--- Token
      "# Comment with no newline");
  lex::Lexer l{source};

  // parses to just `1`
  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 1);
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Statement", "[lex]") {
  std::stringstream source("var abc = 0;");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kVar));
  CHECK(l.Matches(lex::TokenType::kIdentifier));
  CHECK(l.GetPreviousToken().value.identifier == "abc");
  CHECK(l.Matches(lex::TokenType::kAssign));
  CHECK(l.Matches(lex::TokenType::kNumber));
  CHECK(l.GetPreviousToken().value.number == 0);
  CHECK(l.Matches(lex::TokenType::kColon));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("String literal", "[lex]") {
  std::stringstream source("\"Hello world\"");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kString));
  CHECK(l.GetPreviousToken().value.string == "Hello world");
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Funtion declaration args", "[lex]") {
  std::stringstream source("(a1, a2)");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kLeftParen));
  CHECK(l.Matches(lex::TokenType::kIdentifier));
  CHECK(l.GetPreviousToken().value.identifier == "a1");
  CHECK(l.Matches(lex::TokenType::kComma));
  CHECK(l.Matches(lex::TokenType::kIdentifier));
  CHECK(l.GetPreviousToken().value.identifier == "a2");
  CHECK(l.Matches(lex::TokenType::kRightParen));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Curly", "[lex]") {
  std::stringstream source("{ }");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kLeftCBrace));
  CHECK(l.Matches(lex::TokenType::kRightCBrace));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Assign vs Equals", "[lex]") {
  std::stringstream source("== = ==");
  lex::Lexer l{source};

  CHECK(l.Matches(lex::TokenType::kEquals));
  CHECK(l.Matches(lex::TokenType::kAssign));
  CHECK(l.Matches(lex::TokenType::kEquals));
}

//////////////////////////////////////////////////////////////////////

// TEST_CASE("Lex types", "[lex]") {
//   std::stringstream source(": Int Bool String Unit");
//   lex::Lexer l{source};

//   CHECK(l.Matches(lex::TokenType::COLUMN));

//   CHECK(l.Matches(lex::TokenType::TY_INT));
//   CHECK(l.Matches(lex::TokenType::TY_BOOL));
//   CHECK(l.Matches(lex::TokenType::TY_STRING));
//   CHECK(l.Matches(lex::TokenType::TY_UNIT));
// }

//////////////////////////////////////////////////////////////////////
