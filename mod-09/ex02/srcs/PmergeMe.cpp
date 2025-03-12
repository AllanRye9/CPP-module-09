#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }
PmergeMe::PmergeMe(int ac, char **av) {
    if (isNegative(*av))
        throw NegativeException();
    srand(time(0));
    for (int i = 0; i < ac; i++){
        int value = std::atoi(av[i]);
        if (value <= 0)
            throw WrongDataException();
        _sData.insert(value);
        _dData.push_back(value);
    }
    if (_sData.size() != 0 && _dData.size() != 0)
    {
        std::cout << "Before: ";
        display(_dData);
    }
    
    
}
PmergeMe::~PmergeMe() {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other){ 
    if (this == &other)
        return (*this);
    this->_dData = other._dData;
    this->_sData = other._sData;
    return *this;
}

bool PmergeMe::isNegative(const std::string &str)
{
    size_t i = 0;

    while (i < str.size())
    {
        if (str[i] == '-' && i + 1 < str.size() && isdigit(str[i + 1]))
            return true;
        else
            i++;
    }
    return false;
}

const char *PmergeMe::WrongDataException ::what() const throw() { return "Wrong Input Format"; }

const char *PmergeMe::NegativeException ::what() const throw() { return "Number is negative"; }
