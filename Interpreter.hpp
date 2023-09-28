#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Ast.hpp"
#include <exception>

class Interpreter
{
public:
    int Evaluate(const Expr& expr)
    {
        return expr.Visit<int>(*this);
    }

    struct ZeroDivisionException : public std::exception
    {
        const char* what() const noexcept override
        {
            return "zero division";
        }
    };

    int operator()(const Integer& expr)
    {
        return expr.num;
    }

    int operator()(const UnaryOperation& unary)
    {
        int expr = Evaluate(*unary.expr);

        switch (unary.type)
        {
        case UnaryOpType::Negate:
            return -expr;
            break;
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
            break;
        case BinOpType::Substract:
            return left - right;
            break;
        case BinOpType::Multiply:
            return left * right;
            break;
        case BinOpType::Divide:
            return left / right;
            break;
	default:
	    // Unreachable.
	    break;
        }
    }
}; // class Interpreter

#endif // INTERPRETER_HPP
