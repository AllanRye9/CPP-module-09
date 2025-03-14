#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }
PmergeMe::PmergeMe(int ac, char **av)
{
    if (isNegative(ac, av))
        throw NegativeException();
    srand(time(0));
    if (splitContainer(ac, av))
        throw std::runtime_error("Unexpected error.\n");
    if (_left.size() == 0 && _right.size() != 0)
        throw WrongDataException();
    std::cout << "Before: ";
    displayStr(ac, av);
    clock_t start1 = clock();
    sortDeque();
    clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;

    clock_t start2 = clock();
    sortQueue();
    clock_t end2 = clock();
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;

    std::cout << "After: ";
    display(_final);
    std::cout << "Time to process a range of " << _final.size() << " elements with std::[..] : " << time1 << std::endl;
    std::cout << "Time to process a range of " << _final.size() << " elements with std::[..] : " << time2 << std::endl;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::displayStr(int ac, char **av){
    for (int x = 1; x < ac - 1; x++){
        std::string buff(av[x]);
        for (size_t i = 0; i < buff.size(); i++)
            std::cout << buff[i]; 
        std::cout << " ";
        }
        std::cout << std::endl;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this == &other)
        return (*this);
    this->_left = other._left;
    this->_right = other._right;
    return *this;
}

int PmergeMe::splitContainer(int ac, char **av)
{
    int i = 0;
    int n = ac / 2;
    if (n != 0)
    {
        if (ac > 1)
        {
            int n = atoi(av[ac - 1]);
            if (n < 0)
                throw NegativeException();
            _final.insert(n);
            n -= 1;
        }
    }
    while (++i < n)
        _left.push_back(atoi(av[i]));
    while (i < (ac - n))
    {
        _right.push(atoi(av[i]));
        i++;
    }
    sortQueue();
    sortDeque();
    mergefinal();
    return 0;
}
void PmergeMe::sortQueue()
{
    std::deque<int> arr;
    while (!_right.empty())
    {
        arr.push_back(_right.front());
        _right.pop();
    }

    std::sort(arr.begin(), arr.end());
    for (std::deque<int>::iterator it = arr.begin(); it != arr.end(); it++)
        _right.push(*it);
}

void PmergeMe::sortDeque()
{
    std::sort(_left.begin(), _left.end());
}

void PmergeMe::mergefinal()
{
    std::deque<int> tem;
    while (!_right.empty())
    {
        tem.push_back(_right.front());
        _right.pop();
    }
    for (std::deque<int>::iterator it = tem.begin(); it != tem.end(); it++)
    {
        std::pair<std::set<int>::iterator, bool> result = _final.insert(*it);
        if (!result.second)
            throw std::runtime_error("Duplicate encountered.\n");
    }
    for (std::deque<int>::iterator it = _left.begin(); it != _left.end(); it++)
    {
        std::pair<std::set<int>::iterator, bool> result = _final.insert(*it);
        if (!result.second)
            throw std::runtime_error("Duplicate encountered.\n");
    }
}

bool PmergeMe::isNegative(int ac, char **av)
{
    for (int i = 0; i < ac - 1; i++)
    {
        std::string str(av[i]);
        for (size_t x = 0; x < str.size(); x++)
        {
            if (-1 == atoi(str.c_str()))
                throw WrongDataException();
            if (str[x] == '-' && x + 1 < str.size() && isdigit(str[x + 1]))
                return true;
            x++;
        }
    }
    return false;
}

const char *PmergeMe::WrongDataException ::what() const throw() { return "Wrong Input Format"; }

const char *PmergeMe::NegativeException ::what() const throw() { return "Number is negative"; }
