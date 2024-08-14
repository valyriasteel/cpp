#include "RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw RPN::InvalidArgument();
		std::string input = av[1];
		RPN rpn(input);
		std::cout << rpn.getResult() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}