#include "../include/RPN.hpp"

int main(int ac, char **av) {
    if (ac < 2)
        return ( std::cerr << "Wrong Input format <./RPN> <N.1, N.2, ...>" << std::endl, 0);
    RPN inPut;
    try {
        inPut.rpnMath(av[1]);
    } 
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}