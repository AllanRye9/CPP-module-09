#pragma once

#include <cerrno>
#include <climits>
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <deque>
#include <iterator>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <cctype>
#include <vector>
#include <sstream>
#include <cstring>

class PmergeMe
{
private:
    std::deque<int> _left;
    std::queue<int> _right;
    std::set<int> _final;
public:
    PmergeMe(int ac, char **av);
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    template <typename T>
    void display(const T &container)
    {
        for (typename T::const_iterator it = container.begin(); it != container.end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;
    }
    bool isValidInteger(const std::string &s);
    void displayStr(int ac, char **av);
    void sortQueue();
    void sortDeque();
    void splitContainer(int ac, char **av);
    bool integerOverflow(int ac, char **av);
    void mergefinal();
    class WrongDataException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
    class NegativeException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};