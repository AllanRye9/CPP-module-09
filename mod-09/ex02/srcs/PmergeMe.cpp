#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

bool PmergeMe::integerOverflow(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::istringstream iss(av[i]);
        std::string token;
        while (iss >> token)
        {
            errno = 0;
            char *endptr;
            if (!isValidInteger(token))
                throw std::runtime_error("Error: Input Not Integer.");
            long num = std::strtol(token.c_str(), &endptr, 10);
            if (token.c_str() == endptr || *endptr != '\0')
                return true;
            if (errno == ERANGE || num > INT_MAX || num < INT_MIN)
                return true;
        }
    }
    return false;
}

PmergeMe::PmergeMe(int ac, char **av)
{
    splitContainer(ac, av);

    clock_t start1 = clock();
    sortDeque();
    clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;

    clock_t start2 = clock();
    sortQueue();
    clock_t end2 = clock();
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;

    mergefinal();
    std::cout << "Before: ";
    displayStr(ac, av);
    std::cout << "After : ";
    display(_final);
    std::cout << "Time to process a range of " << _final.size()
              << " elements with std::deque : " << time1 << " ms" << std::endl;
    std::cout << "Time to process a range of " << _final.size()
              << " elements with std::queue : " << time2 << " ms" << std::endl;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::displayStr(int ac, char **av)
{
    for (int x = 1; x < ac; x++){
        std::string buff(av[x]);
        std::cout << buff << " ";
    }
    std::cout << std::endl;
}

bool PmergeMe::isValidInteger(const std::string &s)
{
    if (s.empty())
        return false;
    size_t i = 0;
    if (s[i] == '-' || s[i] == '+')
        i++;
    if (i == s.size())
        return false;
    for (; i < s.size(); i++){
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

const char *PmergeMe::WrongDataException::what() const throw()
{
    return "Wrong Input Format";
}

const char *PmergeMe::NegativeException::what() const throw()
{
    return "Number is negative";
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this == &other)
        return (*this);
    this->_left = other._left;
    this->_right = other._right;
    this->_final = other._final;
    return *this;
}

void PmergeMe::splitContainer(int ac, char **av)
{
    if (integerOverflow(ac, av))
        throw std::runtime_error("Int Overflow detected.");
    std::vector<int> numbers;
    for (int i = 1; i < ac; i++)
    {
        std::string token(av[i]);
        int value = std::atoi(av[i]);
        if (value < 0)
            throw NegativeException();
        numbers.push_back(value);
    }
    if (numbers.size() % 2 == 1)
    {
        _final.insert(numbers.back());
        numbers.pop_back();
    }
    size_t mid = numbers.size() / 2;
    _left.assign(numbers.begin(), numbers.begin() + mid);
    for (size_t j = mid; j < numbers.size(); j++)
        _right.push(numbers[j]);
}

void PmergeMe::sortDeque()
{
    std::deque<int> tempLeft;
    while (_left.size() > 1)
    {
        int a = _left.front();
        _left.pop_front();
        int b = _left.front();
        _left.pop_front();
        if (a > b)
            std::swap(a, b);
        tempLeft.push_back(a);
        tempLeft.push_back(b);
    }
    if (!_left.empty())
        tempLeft.push_back(_left.front());
    _left = tempLeft;
}

void PmergeMe::sortQueue()
{
    std::deque<int> unsorted;
    while (!_right.empty())
    {
        unsorted.push_back(_right.front());
        _right.pop();
    }

    std::deque<int> sorted;
    while (unsorted.size() > 1)
    {
        int a = unsorted.front();
        unsorted.pop_front();
        int b = unsorted.front();
        unsorted.pop_front();
        if (a > b)
            std::swap(a, b);
        sorted.push_back(a);
        sorted.push_back(b);
    }
    if (!unsorted.empty())
        sorted.push_back(unsorted.front());

    while (!sorted.empty())
    {
        _right.push(sorted.front());
        sorted.pop_front();
    }
}

void PmergeMe::mergefinal()
{
    std::deque<int> merged;

    while (!_left.empty())
    {
        merged.push_back(_left.front());
        _left.pop_front();
    }
    while (!_right.empty())
    {
        merged.push_back(_right.front());
        _right.pop();
    }

    std::set<int>::iterator result;
    for (std::deque<int>::iterator it = merged.begin(); it != merged.end(); it++)
    {
        std::pair<std::set<int>::iterator, bool> result = _final.insert(*it);
        if (!result.second)
            throw std::runtime_error("Duplicate Encountered or Wrong Input");
    }
}
