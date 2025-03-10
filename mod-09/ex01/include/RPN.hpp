#pragma once

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <iterator>
#include <exception>
#include <algorithm>
#include <cstdlib>

class RPN
{
private:
    std::stack<int> _st;
    std::list<std::string> _data;
public:
    RPN();
    ~RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    int readInput(const std::string &s);
    void checkData();
    void rpnMath(const std::string &s);
    class WrongDataException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
};
