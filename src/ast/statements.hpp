#pragma once

#include <ast/syntax_tree.hpp>
#include <ast/expressions.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Statement : public TreeNode {
 public:
};

//////////////////////////////////////////////////////////////////////

class ExprStatement : public Statement {
 public:
  ExprStatement(Expression* expr) : expr{expr} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitExprStatement(this);
  }

  virtual lex::Location GetLocation() override {
    return expr->GetLocation();
  }

  Expression* expr;
};

//////////////////////////////////////////////////////////////////////

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement(lex::Token assign_token, UnaryExpression* lhs, Expression* rhs)
      : assign_token(assign_token), lhs(lhs), rhs(rhs) {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitAssignment(this);
  }

  virtual lex::Location GetLocation() override {
    return assign_token.location;
  }

  lex::Token assign_token;
  UnaryExpression* lhs;
  Expression* rhs;
};

//////////////////////////////////////////////////////////////////////
