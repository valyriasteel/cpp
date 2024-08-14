#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, char **av)
{
	try
	{
		if (ac < 3)
			throw PmergeMe::InvalidArgument();
		PmergeMe pmerge(av);
		pmerge.sorting();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}