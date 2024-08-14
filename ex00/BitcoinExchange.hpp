#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define db "data.csv"

# include <iostream>
# include <map>

class BitcoinExchange
{
	private:
		std::map<time_t, float> _exchangeRates;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		BitcoinExchange(std::string &dbFile);
		float getExchangeRate(time_t &date);
		void showLastResult(std::string &inputFile);
		time_t getDate(std::string &date);
		float getRate(std::string &rate);
		time_t& getClosestDate(struct tm &time, time_t &date);
	
		class InvalidArgument : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: could not open file.";
				}
		};
	
		class DataBaseError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: could not open file data.csv";
				}
		};
	
		class RateNegativeError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: not a positive number.";
				}
		};
	
		class RateOverError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: too large a number.";
				}
		};
	
		class InputFileError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: could not open file inputfile.";
				}
		};
	
		class DateError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: date not found.";
				}
		};
	
		class InputHeaderError : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: could not find header.";
				}
		};
};

#endif