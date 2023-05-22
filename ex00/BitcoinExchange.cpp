#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_btcValues = other._btcValues;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (&other == this)
		return *this;
	_btcValues = other._btcValues;
	return *this;
}

void printMap(std::map<std::string, double> _map)
{
	std::map<std::string, double>::iterator it = _map.begin();
	for ( ; it != _map.end() ; it++) {
		std::cout << it->first << "," << it->second << '\n';
	}
}

void BitcoinExchange::parseDataFile(void)
{
	std::ifstream dataFile;
	dataFile.open("data.csv", std::ios::in);
	if (!dataFile)
		throw std::invalid_argument("Error: Could not open data.csv");
	std::string buffer;
	getline(dataFile, buffer);
	if (buffer != "date,exchange_rate")
		throw std::invalid_argument("Error: in data.csv: Formatting is incorrect");
	size_t commaNb, commaPos;
	struct tm tm;
	std::string date, exchangeRate;
	double btcValue;
	char *endptr;
	while (getline(dataFile, buffer)) {
		commaNb = count(buffer.begin(), buffer.end(), ',');
		if (commaNb != 1) 
			throw std::invalid_argument("Error: in data.csv: Formatting is incorrect");
		commaPos = buffer.find(',');
		date = buffer.substr(0, commaPos);
		if (!strptime(date.c_str(), "%Y-%m-%d", &tm) || date.size() != 10 ||!isValidDate(date))
			throw std::invalid_argument("Error: in data.csv: Formatting is incorrect");
		exchangeRate = buffer.substr(commaPos + 1, buffer.size() - commaPos - 1);
		errno = 0;
		btcValue = strtod(exchangeRate.c_str(), &endptr);
		if (errno == ERANGE || endptr[0] != '\0')
			throw std::invalid_argument("Error: in data.csv: Formatting is incorrect");
		if (btcValue < 0)
			throw std::invalid_argument("Error: in data.csv : BTC value can't be negative");
		_btcValues.insert(std::make_pair(date, btcValue));
	}
	// printMap(_btcValues);
	dataFile.close();
}


void BitcoinExchange::readInputFile(std::string input) const
{
	std::ifstream inputFile;
	inputFile.open(input.c_str(), std::ios::in);
	if (!inputFile) {
		std::cerr << "Error: in input file: Could not open input file\n";
		return ;
	}
	std::string buffer;
	getline(inputFile, buffer);
	if (buffer != "date | value") {
		std::cerr << "Error: in input file: Formatting is incorrect\n";
		return ;
	}
	struct tm tm;
	std::string date, btc;
	float btcNb = -1;
	char *endptr;
	int error;
	while (getline(inputFile, buffer)) {
		error = NO_ERROR;
		std::string::difference_type nbPipe = std::count(buffer.begin(), buffer.end(), '|');
		std::string::difference_type nbSpace = std::count(buffer.begin(), buffer.end(), ' ');
		if (buffer.size() < 14)
			error = BAD_INPUT;
		else if (buffer.substr(10, 3) != " | ")
			error = BAD_INPUT;
		else if (nbPipe != 1 || nbSpace != 2)
			error = BAD_INPUT;
		if (error == NO_ERROR)
			date = buffer.substr(0, buffer.find_first_of(' '));
		if (!strptime(date.c_str(), "%Y-%m-%d", &tm) || date.size() != 10 ||!isValidDate(date))
			error = BAD_INPUT;
		btc = buffer.substr(buffer.find_last_of(' ') + 1, buffer.size());
		errno = 0;
		btcNb = std::strtof(btc.c_str(), &endptr);
		if (endptr[0] != '\0')
			error = BAD_INPUT;
		else if (errno == ERANGE || btcNb > 1000)
			error = TOOLARGE_NB;
		else if (btcNb < 0)
			error = NEGATIVE_NB;
		printLine(buffer, date, btcNb, error);
	}
	inputFile.close();
}

void BitcoinExchange::printLine(std::string& buffer, std::string& date, float btcNb, int error) const
{
	switch (error) {
		case BAD_INPUT:
			std::cerr << "Error: bad input => " << buffer << '\n';
			break;
		case TOOLARGE_NB:
			std::cerr << "Error: too large a number.\n";
			break;
		case NEGATIVE_NB:
			std::cerr << "Error: not a positive number.\n";
			break;
		default:
			std::map<std::string, double>::const_iterator it;
			it = _btcValues.lower_bound(date);
			if (it == _btcValues.end())
				it--;
			std::cout << date << " => " << btcNb << " = " << it->second * btcNb <<'\n';
	}
}

bool BitcoinExchange::isValidDate(std::string& date) const
{
	static const int maxYear = 2050;
	static const int minYear = 2008;

	char *endptr;
	long year = strtol(date.c_str(), &endptr, 10);
	long month = strtol(endptr + 1, &endptr, 10);
	long day = strtol(endptr + 1, NULL, 10);

	bool isLeap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
	if (year == 2009 && month == 01 && day < 2)
		return false;
	if (year > maxYear || year < minYear)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (month == 2) {
		if (isLeap)
			return day <= 29;
		else
			return day <= 28;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return day <= 30;
	return true;
}
