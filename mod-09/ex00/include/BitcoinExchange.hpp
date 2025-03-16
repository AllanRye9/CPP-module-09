#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <cstring>

#define DATA_FILE "data.csv"

enum ErrorCode{
    BAD_INPUT = -1,
    INVALID_DATE = -2,
    NOT_POSITIVE = -3,
    MULTIPLE_DOTS = -4,
    TOO_LARGE = -5,
    FORMAT_ERROR = -6,
    MISSING_HEADER = -7
};

class BitcoinExchange
{
private:
    std::vector<std::string> _outPut;
    std::vector<std::pair<std::string, std::pair<int, double> > > _inPut;
    std::vector<std::pair<std::string, std::pair<int, double> > > _data;

public:
    BitcoinExchange(std::string &dataSource, std::string &dataInput);
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    void printResults(std::vector<std::string> &result);
    void fillVector(std::vector<std::pair<std::string, std::pair<int, double> > > &data, std::ifstream &input, const char *c);
    int checkFormats(std::string &line, char s);
    void printOutResults();
    void populateOutPut();
    class FileOpenException : public std::exception{
        public:
            virtual const char *what() const throw();
    };
};
