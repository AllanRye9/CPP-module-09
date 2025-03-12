#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <iterator>
#include <exception>
#include <algorithm>
#include <cstdlib>

class PmergeMe
{
private:
    std::deque <int> _dData;
    std::set <int> _sData;
public:
    PmergeMe(int ac, char **av);
    ~PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    template <typename T>
    void display(const T & container){
        for (T::const_iterator it = container.begin(); it != container.end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;
    }
    bool isNegative(const std::string &str);
    class WrongDataException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
    class NegativeException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
};
