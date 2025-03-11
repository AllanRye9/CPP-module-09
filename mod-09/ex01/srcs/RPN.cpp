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

static int isOperator(char c)
{
    if (c == '-' || c == '+' || c == '*' || c == '/')
        return 1;
    return 0;
}

int RPN::readInput(const std::string &s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        _data.push_back(std::string(1, s[i]));
    }
    if (isInvalidNumber(s))
        return 0;
    return (_data.size() > 1 ? 1 : 0);
}

void RPN::checkData()
{
    for (std::list<std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
    {
        if (!isOperator(*it->c_str()) && !isdigit(*it->c_str()) && !isspace(*it->c_str()))
            throw WrongDataException();
        // throw GreaterThanException();
    }
}

bool RPN::isInvalidNumber(const std::string& str) {
    for (size_t i = 0; i + 1 < str.size(); ++i) {
        if (str[i] == '-' && std::isdigit(str[i + 1]))
            return true;
    }
    return false;
}


void RPN::rpnMath(const std::string &s)
{
    if (!readInput(s))
        throw WrongDataException();
    checkData();
    for (std::list<std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
    {
        if (*it != "+" && *it != "-" && *it != "/" && *it != "*")
        {
            int x = std::atoi((*it).c_str());
            if (x != 0)
                _st.push(x);
        }
        else
        {
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
