#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <iostream>

int main(int ac, char **av)
{
  if (ac != 2) {
    std::cerr << "Error: Correct format is ./btc file.txt\n";
    return EXIT_FAILURE;
  }
  BitcoinExchange BitcoinExchange;
  try {
    BitcoinExchange.parseDataFile();
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << '\n';
    return EXIT_FAILURE;
  }
  BitcoinExchange.readInputFile(av[1]);
  return EXIT_SUCCESS;
}
