#pragma once

#include <ast/statements.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Declaration : public Statement {
 public:
  virtual std::string_view GetName() = 0;
};

//////////////////////////////////////////////////////////////////////

class VarDeclStatement : public Declaration {
 public:
  VarDeclStatement(lex::Token name, Expression* rhs)
      : name(name), rhs(rhs) {
  }

  void Accept(Visitor* visitor) override {
    visitor->VisitVarDecl(this);
  }

  lex::Location GetLocation() override {
    return name.location;
  }

  std::string_view GetName() override {
    return name.value.identifier;
  }

  lex::Token name;
  Expression* rhs;
};

//////////////////////////////////////////////////////////////////////

class FunDeclStatement : public Declaration {
 public:
  FunDeclStatement(lex::Token name, std::vector<lex::Token> params, BlockExpression* body)
      : name(name), params(params), body(body) {
  }

  void Accept(Visitor* visitor) override {
    visitor->VisitFunDecl(this);
  }

  lex::Location GetLocation() override {
    return name.location;
  }

  std::string_view GetName() override {
    return name.value.identifier;
  }

  lex::Token name;
  std::vector<lex::Token> params;
  BlockExpression* body;
};

//////////////////////////////////////////////////////////////////////
