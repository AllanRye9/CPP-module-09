#include "../include/BitcoinExchange.hpp"

int main(int ac, char **av) {
    if (ac < 2)
        return ( std::cerr << "File Openning failed. format <./btc> <inputFile>" << std::endl, 0);
    if (ac != 2)
        return (std::cerr << "Invalid Input. format <./btc> <inputFile>" << std::endl, 0);
    std::string dataBase = DATA_FILE;
    std::string inputFile = av[1];
    try {
        BitcoinExchange exchange(dataBase, inputFile);
        exchange.printOutResults();
    } 
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}