#include "RPN.hpp"
#include <cstdlib>
#include <iostream>

int main(int ac, char *av[])
{
  if (ac != 2) {
    std::cerr << "Error: in main: RPN must have 1 and only argument\n";
    return EXIT_FAILURE;
  }
  try {
    RPN rpn;
    rpn.RPNisation(av[1]);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
