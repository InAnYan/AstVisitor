#ifndef AST_HPP
#define AST_HPP

#include <variant>
#include <memory>

// Forward declaration.
struct Expr;

enum class BinOpType
{
    Add,
    Subtract,
    Multiply,
    Divide
};

struct BinaryOperation
{
    BinaryOperation(std::unique_ptr<Expr> left, BinOpType type, std::unique_ptr<Expr> right)
        : left(std::move(left)), type(type), right(std::move(right))
    { }

    std::unique_ptr<Expr> left;
    BinOpType type;
    std::unique_ptr<Expr> right;
};

enum class UnaryOpType
{
    Negate
};

struct UnaryOperation
{
    UnaryOperation(UnaryOpType type, std::unique_ptr<Expr> expr)
        : type(type), expr(std::move(expr))
    { }

    UnaryOpType type;
    std::unique_ptr<Expr> expr;
};

struct Integer
{
    Integer(int num)
        : num(num)
    { }

    int num;
};

using ExprVariant = std::variant<Integer, UnaryOperation, BinaryOperation>;

// By creating a class type that derives from std::variant
// we make it a distinct type and support forward declaration.
struct Expr : public ExprVariant
{
    // Allowing constructors of std::variant to be constructors of Expr.
    using ExprVariant::ExprVariant;

    // Making std::visit a member method.
    template <typename R, typename Visitor>
    R Visit(Visitor&& vis)
    {
        return std::visit<R>(vis, *this);
    }

    // And a const version.
    template <typename R, typename Visitor>
    R Visit(Visitor&& vis) const
    {
        return std::visit<R>(vis, *this);
    }
};

#endif // AST_HPP
