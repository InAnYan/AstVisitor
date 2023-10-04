#ifndef CLASSICAL_APPROACH_HPP
#define CLASSICAL_APPROACH_HPP

#include <memory>

// Step 1: forward declare all AST nodes.
class BinaryOperation;
class UnaryOperation;
class Integer;

// Step 2: create Visitor class and specify all methods over AST nodes.
struct Visitor
{
    virtual ~Visitor() = default;

    virtual void VisitBinaryOperation(const BinaryOperation& expr) = 0;
    virtual void VisitUnaryOperation(const UnaryOperation& expr) = 0;
    virtual void VisitInteger(const Integer& expr) = 0;
};

// Step 3: create the root AST node
struct Expr
{
    virtual ~Expr() = default;
    virtual void Accept(Visitor& vis) const = 0;

    // Yes, if we need to change the node, we have to define a NEW method with const qualifier.
};

// Step 4: define all AST nodes.
// They should derive from Expr and implement the Accept method.

struct Integer : Expr
{
    int num;

    void Accept(Visitor& vis) const override
    {
        vis.VisitInteger(*this);
    }
};

enum class UnaryOpType
{
    Negate
};

struct UnaryOperation : Expr
{
    UnaryOpType type;
    std::unique_ptr<Expr> expr;

    void Accept(Visitor& vis) const override
    {
        vis.VisitUnaryOperation(*this);
    }
};

enum class BinOpType
{
    Add,
    Subtract,
    Multiply,
    Divide
};

struct BinaryOperation : Expr
{
    std::unique_ptr<Expr> left;
    BinOpType type;
    std::unique_ptr<Expr> right;

    void Accept(Visitor& vis) const override
    {
        vis.VisitBinaryOperation(*this);
    }
};

// Step 5: create a class that performs some function over an AST node.
// The class should inherit from Visitor and implement all pure virtual methods.
// In our example we evalute the result of an expression.
struct Interpreter : Visitor
{
    int Evaluate(const Expr& expr)
    {
        expr.Accept(*this);
        return stored;
    }

    void VisitInteger(const Integer& expr) override
    {
        stored = expr.num;
    }

    void VisitUnaryOperation(const UnaryOperation& unary) override
    {
        int expr = Evaluate(*unary.expr);

        switch (unary.type)
        {
        case UnaryOpType::Negate:
            // Because virtual methods cannot be templated, we store the result in a field.
            stored = -expr;
            break;
        default:
            // Unreachable.
            break;
        }
    }

    void VisitBinaryOperation(const BinaryOperation& binary) override
    {
        int left = Evaluate(*binary.left);
        int right = Evaluate(*binary.right);

        switch (binary.type)
        {
        case BinOpType::Add:
            stored = left + right;
            break;
        case BinOpType::Subtract:
            stored = left - right;
            break;
        case BinOpType::Multiply:
            stored = left * right;
            break;
        case BinOpType::Divide:
            stored = left / right;
            break;
        default:
            // Unreachable.
            break;
        }
    }

private:
    int stored;
}; // class Interpreter

#endif // CLASSICAL_APPROACH_HPP
