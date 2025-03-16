#include "../include/PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        return std::cerr << "Wrong Input format: <./PmergeMe> <N1 N2 ...>" << std::endl, 1;
    try{
        PmergeMe inPut(ac, av);
    }
    catch (const std::exception &e){
        return (std::cerr << e.what() << std::endl, 1);
    }
    catch (...){
        return (std::cerr << "Unexpected Error" << std::endl, 1);
    }
    return 0;
}
