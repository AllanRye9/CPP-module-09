#pragma once

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <iterator>
#include <exception>
#include <algorithm>
#include <cstdlib>

class PmergeMe
{
private:
    std::stack<int> _st;
    std::list<std::string> _data;
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    int readInput(const std::string &s);
    bool isNegative(const std::string &str);
    void PmergeMeMath(const std::string &s);
    class WrongDataException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
    class GreaterThanException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
    class NegativeException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
};
