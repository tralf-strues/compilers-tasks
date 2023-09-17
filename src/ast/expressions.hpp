#pragma once

#include <ast/syntax_tree.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Expression : public TreeNode {
 public:
  virtual void Accept(Visitor*) = 0;

  // Later

  // virtual types::Type* GetType() = 0;
};

//////////////////////////////////////////////////////////////////////

// Assignable entity

class LvalueExpression : public Expression {};

//////////////////////////////////////////////////////////////////////

class ComparisonExpression : public Expression {
 public:
  ComparisonExpression(lex::Token cmp_operator, Expression* lhs, Expression* rhs)
      : cmp_operator(cmp_operator), lhs(lhs), rhs(rhs) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitComparison(this);
  }

  virtual lex::Location GetLocation() override {
    return cmp_operator.location;
  }

  lex::Token cmp_operator;
  Expression* lhs;
  Expression* rhs;
};

//////////////////////////////////////////////////////////////////////

// Binary arithmetic: + - / *

class BinaryExpression : public Expression {
 public:
  BinaryExpression(lex::Token binary_operator, Expression* lhs, Expression* rhs)
      : binary_operator(binary_operator), lhs(lhs), rhs(rhs) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBinary(this);
  }

  virtual lex::Location GetLocation() override {
    return binary_operator.location;
  }

  lex::Token binary_operator;
  Expression* lhs;
  Expression* rhs;
};

//////////////////////////////////////////////////////////////////////

class UnaryExpression : public Expression {
 public:
  UnaryExpression(lex::Token unary_operator, Expression* operand) : unary_operator(unary_operator), operand(operand) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitUnary(this);
  }

  virtual lex::Location GetLocation() override {
    return unary_operator.location;
  }

  lex::Token unary_operator;
  Expression* operand;
};

//////////////////////////////////////////////////////////////////////

class FnCallExpression : public Expression {
 public:
  FnCallExpression(lex::Token name, std::vector<Expression*> args) : name(name), args(args) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitFnCall(this);
  }

  virtual lex::Location GetLocation() override {
    return name.location;
  }

  lex::Token name;
  std::vector<Expression*> args;
};

//////////////////////////////////////////////////////////////////////

class BlockExpression : public Expression {
 public:
  BlockExpression(lex::Token open_brace, std::vector<Statement*> statements)
      : open_brace(open_brace), statements(statements) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBlock(this);
  }

  virtual lex::Location GetLocation() override {
    return open_brace.location;
  }

  lex::Token open_brace;
  std::vector<Statement*> statements;
};

//////////////////////////////////////////////////////////////////////

class IfExpression : public Expression {
 public:
  IfExpression(lex::Token if_token, Expression* condition_expr, Expression* true_expr, Expression* false_expr)
      : if_token(if_token), condition_expr(condition_expr), true_expr(true_expr), false_expr(false_expr) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitIf(this);
  }

  virtual lex::Location GetLocation() override {
    return if_token.location;
  }

  lex::Token if_token;
  Expression* condition_expr;
  Expression* true_expr;
  Expression* false_expr;
};

//////////////////////////////////////////////////////////////////////

class LiteralExpression : public Expression {
 public:
  LiteralExpression(lex::Token literal) : literal(literal) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitLiteral(this);
  }

  virtual lex::Location GetLocation() override {
    return literal.location;
  }

  lex::Token literal;
};

//////////////////////////////////////////////////////////////////////

class VarAccessExpression : public LvalueExpression {
 public:
  VarAccessExpression(lex::Token variable) : variable(variable) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarAccess(this);
  }

  virtual lex::Location GetLocation() override {
    return variable.location;
  }

  lex::Token variable;
};

//////////////////////////////////////////////////////////////////////

class ReturnExpression : public Expression {
 public:
  ReturnExpression(lex::Token return_token, Expression* expression)
      : return_token(return_token), expression(expression) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitReturn(this);
  }

  virtual lex::Location GetLocation() override {
    return return_token.location;
  }

  lex::Token return_token;
  Expression* expression;
};

//////////////////////////////////////////////////////////////////////
