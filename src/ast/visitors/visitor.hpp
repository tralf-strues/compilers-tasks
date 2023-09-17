#pragma once

//////////////////////////////////////////////////////////////////////

/* Statements */
class Statement;
class ExprStatement;
class AssignmentStatement;

//////////////////////////////////////////////////////////////////////

/* Declarations */
class VarDeclStatement;
class FunDeclStatement;

//////////////////////////////////////////////////////////////////////

/* Expressions */
class Expression;
class ComparisonExpression;
class BinaryExpression;
class UnaryExpression;
class DereferenceExpression;
class AddressofExpression;
class IfExpression;
class MatchExpression;
class NewExpression;
class BlockExpression;
class FnCallExpression;
class IntrinsicCall;
class CompoundInitializerExpr;
class FieldAccessExpression;
class LiteralExpression;
class VarAccessExpression;
class TypecastExpression;
class YieldExpression;
class ReturnExpression;

//////////////////////////////////////////////////////////////////////

class Visitor {
 public:
  virtual ~Visitor() = default;

  /* Statements */
  virtual void VisitExprStatement(ExprStatement* node) = 0;
  virtual void VisitAssignment(AssignmentStatement* node) = 0;

  /* Declarations */
  virtual void VisitVarDecl(VarDeclStatement* node) = 0;
  virtual void VisitFunDecl(FunDeclStatement* node) = 0;

  /* Expressions */
  virtual void VisitComparison(ComparisonExpression* node) = 0;
  virtual void VisitBinary(BinaryExpression* node) = 0;
  virtual void VisitUnary(UnaryExpression* node) = 0;
  virtual void VisitFnCall(FnCallExpression* node) = 0;
  virtual void VisitBlock(BlockExpression* node) = 0;
  virtual void VisitIf(IfExpression* node) = 0;
  virtual void VisitLiteral(LiteralExpression* node) = 0;
  virtual void VisitVarAccess(VarAccessExpression* node) = 0;
  virtual void VisitReturn(ReturnExpression* node) = 0;
};

//////////////////////////////////////////////////////////////////////
