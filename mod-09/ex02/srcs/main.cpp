#include "../include/PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2)
        return ( std::cerr << "Wrong Input format <./PmergeMe> <N.1, N.2, ...>" << std::endl, 0);
    PmergeMe inPut;
    try {
        inPut.PmergeMeMath(av[1]);
    } 
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}