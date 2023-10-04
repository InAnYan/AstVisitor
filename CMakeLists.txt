cmake_minimum_required(VERSION 3.26)
project(AstVisitor)

set(CMAKE_CXX_STANDARD 20)

add_executable(AstVisitor main.cpp ClassicalApproach.hpp OurApproach.hpp)
