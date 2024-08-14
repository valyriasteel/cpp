#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange()
{
	
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	_exchangeRates = copy._exchangeRates;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this == &copy)
		return *this;
	_exchangeRates = copy._exchangeRates;
	return *this;
}

BitcoinExchange::BitcoinExchange(std::string &dbFile)
{
	std::ifstream file(dbFile);
	if (!file.is_open())
		throw BitcoinExchange::DataBaseError();
	std::stringstream line;
	line << file.rdbuf();
	std::string firstline;
	std::getline(line, firstline);
	std::string date;
	std::string rate;
	float frate;
	time_t ldate;
	while (std::getline(line, firstline))
	{
		std::stringstream database(firstline);
		std::getline(database, date, ',');
		std::getline(database, rate, '\n');
		ldate = getDate(date);
		frate = getRate(rate);
		_exchangeRates.insert(std::pair<time_t, float>(ldate, frate));
	}
	file.close();
}

time_t BitcoinExchange::getDate(std::string &date)
{
	std::stringstream ss;
	ss << date;
	std::string ldate;
	std::getline(ss, ldate, '-');

	struct tm tm;
	bzero(&tm, sizeof(tm));
	std::string str_year = ldate;
	int num_year = std::atoi(ldate.c_str());
	tm.tm_year = num_year - 1900;

	std::getline(ss, ldate, '-');
	std::string str_month = ldate;
	int num_month = std::atoi(ldate.c_str());
	tm.tm_mon = num_month - 1;

	std::getline(ss, ldate, '-');
	std::string str_day = ldate;
	int num_day = std::atoi(ldate.c_str());
	tm.tm_mday = num_day;

	struct tm copy;
	bzero(&copy, sizeof(copy));
	copy.tm_year = tm.tm_year;
	copy.tm_mon = tm.tm_mon;
	copy.tm_mday = tm.tm_mday;
	time_t t = mktime(&tm);
	if (t == -1 || copy.tm_year != tm.tm_year || copy.tm_mon != tm.tm_mon || copy.tm_mday != tm.tm_mday)
		throw(std::invalid_argument(std::string("Error: bad input => " + str_year + "-" + str_month + "-" + str_day)));
	return t;
}

float BitcoinExchange::getRate(std::string &rate)
{
	double convert;
	std::stringstream ss(rate);
	ss >> convert;

	if (convert < 0)
		throw BitcoinExchange::RateNegativeError();
	if (convert > std::numeric_limits<int>::max())
		throw BitcoinExchange::RateOverError();
	return convert;
}

void BitcoinExchange::showLastResult(std::string &inputFile)
{
	std::ifstream file(inputFile);
	if (!file.is_open())
		throw BitcoinExchange::InputFileError();
	std::stringstream line;
	line << file.rdbuf();
	std::string start;
	std::string date;
	std::string rate;
	float frate;
	time_t ldate;
	bool found = false;
	while (std::getline(line, start))
	{
		if (!found && !start.compare("date | value"))
			found = true;
		else if (found)
		{
			std::stringstream database(start);
			std::getline(database, date, '|');
			std::getline(database, rate, '\n');
			try
			{
				ldate = getDate(date);
				frate = getRate(rate);
				std::cout << date << "=> " << frate << " = " << frate * getExchangeRate(ldate) << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
			throw BitcoinExchange::InputHeaderError();
	}
}

float BitcoinExchange::getExchangeRate(time_t &date)
{
	struct tm *ptm = NULL;
	ptm = localtime(&date);
	struct tm tm;
	bzero(&tm, sizeof(tm));
	tm.tm_year = ptm->tm_year;
	tm.tm_mon = ptm->tm_mon;
	tm.tm_mday = ptm->tm_mday;
	while (_exchangeRates.find(date) == _exchangeRates.end())
	{
		if (tm.tm_mday > 1)
			--tm.tm_mday;
		else if (tm.tm_mon > 0)
		{
			tm.tm_mday = 31;
			--tm.tm_mon;
		}
		else
		{
			tm.tm_mday = 31;
			tm.tm_mon = 11;
			--tm.tm_year;
		}
		if (tm.tm_year < 0)
			throw BitcoinExchange::DateError();
		date = BitcoinExchange::getClosestDate(tm, date);
	}
	return _exchangeRates[date];
}

time_t& BitcoinExchange::getClosestDate(struct tm &tm, time_t &date)
{
	struct tm copy;
	bzero(&copy, sizeof(copy));
	copy.tm_year = tm.tm_year;
	copy.tm_mon = tm.tm_mon;
	copy.tm_mday = tm.tm_mday;
	date = mktime(&tm);
	while (date == -1 || copy.tm_year != tm.tm_year || copy.tm_mon != tm.tm_mon || copy.tm_mday != tm.tm_mday)
	{
		tm.tm_year = copy.tm_year;
		tm.tm_mon = copy.tm_mon;
		tm.tm_mday = copy.tm_mday - 1;
		copy.tm_mday = tm.tm_mday;
		date = mktime(&tm);
	}
	return date;
}