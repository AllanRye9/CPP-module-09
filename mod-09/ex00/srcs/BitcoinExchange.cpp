#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }

BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this == &other)
        return (*this);
    this->_data = other._data;
    this->_inPut = other._inPut;
    this->_outPut = other._outPut;
    return (*this);
}

void BitcoinExchange::printResults(std::vector<std::string> &result)
{
    for (std::vector<std::string>::iterator it = result.begin(); it != result.end(); ++it)
        std::cout << *it << std::endl;
}

void BitcoinExchange::printOutResults() { printResults(_outPut); }

int BitcoinExchange::checkFormats(std::string &line, char s)
{
    size_t size = line.size();
    size_t i = 0;

    for (; i < size && (line[i] == ' ' || line[i] == '\t'); ++i)
        ;

    if (i < size && !std::isdigit(line[i]))
        return (1);

    for (; i < size; ++i)
        if (!std::isdigit(line[i]) && line[i] != '-')
            break;

    for (; i < size && (line[i] == ' ' || line[i] == '\t'); ++i)
        ;

    if (line[i] != s)
        return (1);

    ++i;

    for (; i < size && (line[i] == ' ' || line[i] == '\t'); ++i)
        ;

    if (i < size && (line[i] == '+' || line[i] == '-'))
        ++i;

    if (line[i] == '.')
        return (1);

    for (; i < size; ++i)
        if (!std::isdigit(line[i]) && line[i] != '.')
            break;

    for (; i < size; ++i)
        if (line[i] != ' ' && line[i] != '\t')
            return (1);

    return 0;
}

static bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    return false;
}

static int isInvalidDate(std::string &inputDate)
{
    if (inputDate.length() != 10)
        return 1;

    if (inputDate[4] != '-' || inputDate[7] != '-')
        return 1;

    std::string year = inputDate.substr(0, 4);
    if (year.find_first_not_of("0123456789") != std::string::npos)
        return 1;

    int intYear = std::atoi(year.c_str());

    std::string month = inputDate.substr(5, 2);
    if (month.find_first_not_of("0123456789") != std::string::npos || std::atoi(month.c_str()) < 1 || std::atoi(month.c_str()) > 12)
        return 1;

    std::string day = inputDate.substr(8);
    if (day.find_first_not_of("0123456789") != std::string::npos || std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 31)
        return 1;

    // Check for months with 30 days: April, June, September, November
    if (month == "04" || month == "06" || month == "09" || month == "11")
        if (std::atoi(day.c_str()) > 30)
            return 1;

    // Check for February (month == "02")
    if (month == "02")
    {
        if (std::atoi(day.c_str()) > 29)
            return 1; // February can have max 29 days
        if (std::atoi(day.c_str()) == 29 && !isLeapYear(intYear))
            return 1; // February 29 is valid only in a leap year
    }

    return 0; // Return 0 if all checks pass
}

static int findDots(std::string &inputDat, const char c)
{
    size_t i = inputDat.find(c);
    if (i == std::string::npos)
        return 0;
    i++;
    if (inputDat.substr(i).find(c) != std::string::npos)
        return 1;
    return 0;
}

static int isInvalidValue(std::string &inputDate, double *p)
{
    if (inputDate[0] == '+' && inputDate.find_first_not_of("0123456789.") == std::string::npos)
        inputDate = inputDate.substr(1);

    if (inputDate[0] == '-' || inputDate.find_first_not_of("0123456789.") != std::string::npos)
        return (*p = NOT_POSITIVE, 1);
    if (findDots(inputDate, '.'))
        return (*p = MULTIPLE_DOTS, 1);
    try
    {
        *p = std::atof(inputDate.c_str());
    }
    catch (const std::exception &e)
    {
        return (*p = TOO_LARGE, 1);
    }
    return 0;
}

static void parseDateValue(std::string &liner, const char *c, int *date, double *value)
{
    size_t i = liner.find(c[0]);
    if (liner.length() < 12 || i != 10 || i == std::string::npos || liner.find_first_not_of(c) != std::string::npos)
    {
        *date = BAD_INPUT;
        return;
    }
    std::string inputDate;
    inputDate = liner.substr(0, i);
    if (isInvalidDate(inputDate))
    {
        *date = INVALID_DATE;
        return;
    }
    std::string pDate = inputDate.substr(0, 4) + inputDate.substr(5, 2) + inputDate.substr(8, 2);
    *date = std::atoi(pDate.c_str());
    std::string valueData = liner.substr(i + 1);
    if (isInvalidValue(valueData, value))
        return;
}

void BitcoinExchange::fillVector(std::vector<std::pair<std::string, std::pair<int, double> > > &data, std::ifstream &input, const char *c)
{
    std::string line;
    std::string liner;
    int date = -1;
    int flag;
    double value = -1;
    if (getline(input, line))
    {
        if (line != "date,exchange_rate" && line != "date | value")
            value = MISSING_HEADER;
        else
            value = 0; // valid header indicator
        liner = line;
    }
    else
        throw std::runtime_error("Empty file");
    if (value == MISSING_HEADER)
        data.push_back(std::make_pair(liner, std::make_pair(value, MISSING_HEADER)));
    while (getline(input, line))
    {
        flag = checkFormats(line, c[0]);
        std::istringstream word(line);
        std::ostringstream oss;
        std::copy(std::istream_iterator<std::string>(word), std::istream_iterator<std::string>(), std::ostream_iterator<std::string>(oss));
        liner = oss.str();

        parseDateValue(liner, c, &date, &value);
        if (!flag)
            data.push_back(std::make_pair(liner, std::make_pair(date, value)));
        else
            data.push_back(std::make_pair(liner, std::make_pair(date, FORMAT_ERROR)));
    }
}

static bool compareInts(const std::pair<std::string, std::pair<int, double> > &x, const std::pair<std::string, std::pair<int, double> > &y)
{
    return x.second.first < y.second.first;
}

void BitcoinExchange::populateOutPut()
{
    std::string line;
    int date;
    double value;
    double result;

    for (std::vector<std::pair<std::string, std::pair<int, double> > >::iterator it = _inPut.begin(); it != _inPut.end(); ++it)
    {
        line = it->first;
        date = it->second.first;
        value = it->second.second;
        result = 0;

        if (value == MISSING_HEADER)
        {
            _outPut.push_back("Error: Missing or Invalid Header => " + line);
            continue;
        }
        if (date == BAD_INPUT)
        {
            _outPut.push_back("Error: bad input => " + line);
            continue;
        }
        if (date == INVALID_DATE)
        {
            _outPut.push_back("Error: invalid Date => " + line.substr(0, 10));
            continue;
        }
        if (value == NOT_POSITIVE)
        {
            _outPut.push_back("Error: not a positive number.");
            continue;
        }
        if (value == MULTIPLE_DOTS)
        {
            _outPut.push_back("Error: multiple dots => " + line.substr(11));
            continue;
        }
        if (value > 1000 || value == TOO_LARGE)
        {
            _outPut.push_back("Error: too large a number.");
            continue;
        }
        if (value == FORMAT_ERROR || date == FORMAT_ERROR)
        {
            _outPut.push_back("Error: bad input => " + line);
            continue;
        }
        for (std::vector<std::pair<std::string, std::pair<int, double> > >::iterator itd = _data.begin(); itd != _data.end(); ++itd)
        {
            if (itd->second.first < 0 || itd->second.second < 0)
                continue;
            if (itd->second.first > date)
                break;
            result = value * itd->second.second;
        }
        std::ostringstream oss;
        oss << result;
        _outPut.push_back(line.substr(0, 10) + " => " + line.substr(11) + " = " + oss.str());
    }
}

BitcoinExchange::BitcoinExchange(std::string &dataSource, std::string &dataInput)
{
    std::ifstream data(dataSource.c_str());
    std::ifstream src(dataInput.c_str());

    if (!src.is_open() || !data.is_open())
    {
        if (data.is_open())
            data.close();
        throw FileOpenException();
    }
    fillVector(_data, data, ",-.0123456789");
    fillVector(_inPut, src, "|+-.0123456789");
    std::sort(_data.begin(), _data.end(), compareInts);
    data.close();
    src.close();
    populateOutPut();
}

const char *BitcoinExchange::FileOpenException::what() const throw()
{
    return "could not open file.";
}
