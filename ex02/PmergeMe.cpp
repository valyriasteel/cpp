#include "PmergeMe.hpp"
#include <sstream>
#include <iomanip>

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	_vector = copy._vector;
	_deque = copy._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &copy)
{
	if (this == &copy)
		return *this;
	_vector.clear();
	_deque.clear();
	_vector = copy._vector;
	_deque = copy._deque;
	return *this;
}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(char **av)
{
	int token;
	char *end;
	for (int i = 1; av[i]; i++)
	{
		token = std::strtol(av[i], &end, 10);
		if (*end || token < 0)
			throw InvalidExpression();
		_vector.push_back(token);
		_deque.push_back(token);
	}
}

void PmergeMe::sorting()
{
	clock_t startVec, endVec, startDeq, endDeq;
	print("Before");
	startVec = clock();
	mergeInsertionSort(_vector, 0, _vector.size() - 1);
	endVec = clock();
	startDeq = clock();
	mergeInsertionSort(_deque, 0, _deque.size() - 1);
	endDeq = clock();
	print("After");
	double elapsedVec = double(endVec - startVec) / CLOCKS_PER_SEC;
	double elapsedDeq = double(endDeq - startDeq) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << elapsedVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: " << std::fixed << std::setprecision(6) << elapsedDeq << " us" << std::endl;
}

void PmergeMe::print(std::string str)
{
	std::cout << str << ": ";
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}