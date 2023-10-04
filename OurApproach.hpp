#ifndef OUR_APPROACH_HPP
#define OUR_APPROACH_HPP

#include <variant>
#include <memory>

// Step 1: forward declare the abstract AST node.
struct Expr;

// Step 2: define all AST nodes however you want. No restrictions or obligations.

struct Integer
{
    int num;
};

enum class UnaryOpType
{
    Negate
};

struct UnaryOperation
{
    UnaryOpType type;
    std::unique_ptr<Expr> expr;
};

enum class BinOpType
{
    Add,
    Subtract,
    Multiply,
    Divide
};

struct BinaryOperation
{
    std::unique_ptr<Expr> left;
    BinOpType type;
    std::unique_ptr<Expr> right;
};

// Step 3: define the expression.

// This step is a bit ugly, but it is not so complex.
// Firstly, we should implement Expr as a class, because we cannot forward declare `using`.

// By creating this using we just eliminate code duplication.
using ExprVariant = std::variant<Integer, UnaryOperation, BinaryOperation>;

// By creating a class type that derives from std::variant
// we make it a distinct type and support forward declaration.
struct Expr : public ExprVariant
{
    // Allowing constructors of std::variant to be constructors of Expr.
    using ExprVariant::ExprVariant;
};

// Step 4: encapsulate the desired functionality over AST in a class.
// Each method on an AST node is implemented as call operator overload with corresponding AST node type. 
// In our example we evaluate the result of an expression.
class Interpreter
{
public:
    int Evaluate(const Expr& expr)
    {
        // The heart of our approach.
        // std::visit implements the dispatch and also supports different return types.
        return std::visit<int>(*this, expr);
    }

    int operator()(const Integer& expr)
    {
        return expr.num;
    }

    // In fact, we don't have to implement the dispatched method as call overload.
    // Disadvantage of this approach is that the call operator has to be public.
    // But if we had an overloaded method called Execute and then we pass a lambda
    // that calls this method, the Execute method could be private!

    int operator()(const UnaryOperation& unary)
    {
        int expr = Evaluate(*unary.expr);

        switch (unary.type)
        {
        case UnaryOpType::Negate:
            return -expr;
        default:
            // Unreachable.
            break;
        }
    }

    int operator()(const BinaryOperation& binary)
    {
        int left = Evaluate(*binary.left);
        int right = Evaluate(*binary.right);

        switch (binary.type)
        {
        case BinOpType::Add:
            return left + right;
        case BinOpType::Subtract:
            return left - right;
        case BinOpType::Multiply:
            return left * right;
        case BinOpType::Divide:
            return left / right;
        default:
            // Unreachable.
            break;
        }
    }
}; // class Interpreter

#endif // OUR_APPROACH_HPP
