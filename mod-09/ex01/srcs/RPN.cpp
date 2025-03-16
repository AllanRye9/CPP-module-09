#include "../include/RPN.hpp"

RPN::RPN(const RPN &other) { *this = other; }
RPN::RPN() {}
RPN::~RPN() {}
RPN &RPN::operator=(const RPN &other)
{
    if (this == &other)
        return (*this);
    this->_data = other._data;
    this->_st = other._st;
    return (*this);
}

bool RPN::isNegative(const std::string &str)
{
    size_t i = 0;

    while (i < str.size())
    {
        if (str[i] == '-' && i + 1 < str.size() && isdigit(str[i + 1])){
            return true;
        }

        if (isdigit(str[i]))
        {
            size_t num = 0;
            while (i < str.size() && isdigit(str[i]))
            {
                num = num * 10 + (str[i] - '0');
                if (num > 9)
                    throw GreaterThanException();
                i++;
            }
        }
        else
            i++;
    }
    return false;
}

int RPN::readInput(const std::string &s)
{
    if (isNegative(s)) 
        throw NegativeException();

    size_t i = 0;
    while (i < s.size())
    {
        if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        {
            i++;
            continue;
        }
        if (isdigit(s[i]))
        {
            std::string number;
            while (i < s.size() && isdigit(s[i]))
            {
                number += s[i];
                i++;
            }
            _data.push_back(number);
            continue;
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
        {
            _data.push_back(std::string(1, s[i]));
            i++;
            continue;
        }
        return 0;
    }
    return (_data.size() > 1 ? 1 : 0);
}


void RPN::rpnMath(const std::string &s)
{
    if (!readInput(s))
        throw WrongDataException();
    for (std::list<std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
    {
        if (*it != "+" && *it != "-" && *it != "/" && *it != "*")
            _st.push(std::atoi((*it).c_str()));
        else
        {
            if (_st.size() < 2)
                throw std::runtime_error("Error: Not enough operands for operation");
            int b = _st.top();
            _st.pop();
            int a = _st.top();
            _st.pop();
            if (*it == "+")
                _st.push(a + b);
            else if (*it == "-")
                _st.push(a - b);
            else if (*it == "*")
                _st.push(a * b);
            else if (*it == "/")
                _st.push(a / b);
            else
                throw std::exception();
        }
    }
    if (!_st.empty())
        std::cout << _st.top() << std::endl;
    else
        std::cerr << "Error: stack is Empty" << std::endl;
}

const char *RPN::WrongDataException ::what() const throw() { return "Wrong Input Format"; }

const char *RPN::GreaterThanException ::what() const throw() { return "Value is Greater than 10"; }

const char *RPN::NegativeException ::what() const throw() { return "Number is negative"; }
