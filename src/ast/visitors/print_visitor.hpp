#pragma once

#include <ast/visitors/visitor.hpp>
#include <ast/expressions.hpp>
#include <ast/declarations.hpp>
#include <ast/statements.hpp>

//////////////////////////////////////////////////////////////////////

class PrintVisitor : public Visitor {
 public:
  PrintVisitor(std::ostream& os) : os_(os) {}

  /* Statements */
  void VisitExprStatement(ExprStatement* node) override {
    node->expr->Accept(this);
    os_ << ";" << std::endl;
  }

  void VisitAssignment(AssignmentStatement* node) override {
    node->lhs->Accept(this);
    os_ << " = ";
    node->rhs->Accept(this);
  }

  /* Declarations */
  void VisitVarDecl(VarDeclStatement* node) override {
    os_ << "var " << node->GetName() << " = ";
    node->rhs->Accept(this);
    os_ << ";" << std::endl;
  }

  void VisitFunDecl(FunDeclStatement* node) override {
    os_ << "fun " << node->GetName() << " ";
    for (const auto& param : node->params) {
      os_ << param.value.identifier << " ";
    }

    os_ << " = ";
    node->body->Accept(this);
  }

  /* Expressions */
  void VisitComparison(ComparisonExpression* node) override {
    node->lhs->Accept(this);
    os_ << " " << lex::FormatTokenType(node->cmp_operator.type) << " ";
    node->rhs->Accept(this);
  }

  void VisitBinary(BinaryExpression* node) override {
    node->lhs->Accept(this);
    os_ << " " << lex::FormatTokenType(node->binary_operator.type) << " ";
    node->rhs->Accept(this);
  }

  void VisitUnary(UnaryExpression* node) override {
    os_ << lex::FormatTokenType(node->unary_operator.type);
    node->operand->Accept(this);
  }

  void VisitFnCall(FnCallExpression* node) override {
    os_ << node->name.value.identifier << "(";
    for (const auto& arg : node->args) {
      arg->Accept(this);
      os_ << ", ";
    }
    os_ << node->name.value.identifier << ")";
  }

  void VisitBlock(BlockExpression* node) override {
    os_ << "{" << std::endl;
    for (const auto& statement : node->statements) {
      statement->Accept(this);
    }
    os_ << "}" << std::endl;
  }

  void VisitIf(IfExpression* node) override {
    os_ << "if (";
    node->condition_expr->Accept(this);
    os_ << ") { ";
    node->true_expr->Accept(this);
    os_ << " } else { ";
    node->false_expr->Accept(this);
    os_ << " }";
  }

  void VisitLiteral(LiteralExpression* node) override {
    switch (node->literal.type) {
      case lex::TokenType::kNumber: {
        os_ << node->literal.value.number;
        break;
      }

      case lex::TokenType::kString: {
        os_ << "\"" << node->literal.value.string << "\"";
        break;
      }

      default: {
        FMT_ASSERT(false, "Invalid literal");
      }
    }
  }

  void VisitVarAccess(VarAccessExpression* node) override {
    os_ << node->variable.value.identifier;
  }

  void VisitReturn(ReturnExpression* node) override {
    os_ << "return ";
    node->expression->Accept(this);
  }

 private:
  std::ostream& os_;
};

//////////////////////////////////////////////////////////////////////
