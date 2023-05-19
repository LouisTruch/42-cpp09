#ifndef BITCOINEXCHANGE_HPP_
#define BITCOINEXCHANGE_HPP_

#include <string>
#include <map>

class BitcoinExchange { 
	public:
	 BitcoinExchange();
	 ~BitcoinExchange();
	 BitcoinExchange(const BitcoinExchange& other);
	 BitcoinExchange& operator=(const BitcoinExchange& other);

	 void parseDataFile(void);
	 void readInputFile(std::string input) const;
	 void printLine(std::string buffer, std::string date, float btcNb, int error) const;
	 static bool isValidDate(std::string);

	 typedef enum e_error {NO_ERROR, BAD_INPUT, TOOLARGE_NB, NEGATIVE_NB} t_error;

	private:
	 std::map<std::string, double> _map;
 } ;

#endif // BITCOINEXCHANGE_HPP_
