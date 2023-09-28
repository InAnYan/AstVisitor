#include <iostream>
#include <memory>

#include "Ast.hpp"
#include "Interpreter.hpp"

int main()
{
    Interpreter interpreter;

    std::cout << "1. Evaluating 2 + 3." << std::endl;

    Expr first(BinaryOperation(std::make_unique<Expr>(Integer(2)),
                               BinOpType::Add,
                               std::make_unique<Expr>(Integer(3))));

    std::cout << "   Expected: 5." << std::endl;
    std::cout << "   Result: " << interpreter.Evaluate(first) << std::endl;

    std::cout << "2. Evaluating (2 + 3) * 4." << std::endl;

    Expr second(BinaryOperation(std::make_unique<Expr>(std::move(first)),
                               BinOpType::Multiply,
                               std::make_unique<Expr>(Integer(4))));

    std::cout << "   Expected: 20." << std::endl;
    std::cout << "   Result: " << interpreter.Evaluate(second) << std::endl;

    return 0;
}
