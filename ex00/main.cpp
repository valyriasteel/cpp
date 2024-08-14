#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw BitcoinExchange::InvalidArgument();
		std::string dbFile = db;
		BitcoinExchange exchange(dbFile);
		std::string input = av[1];
		exchange.showLastResult(input);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}