#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

void printAndLaunchSorting(PmergeMe& pmerge, const std::string& containerType, int nbElements)
{
  const clock_t start = clock();
  if (containerType == "vector"){
    pmerge.printContainer(pmerge.getVector(), BEFORE_SORT);
    pmerge.sortContainer(pmerge.getVector());
    pmerge.printContainer(pmerge.getVector(), AFTER_SORT);
  }
  else if (containerType == "deque")
    pmerge.sortContainer(pmerge.getDeque());
  std::cout << "Time to process a range of " << nbElements << " with std::" << containerType << " : "
    << std::fixed << float(clock() - start) / CLOCKS_PER_SEC << " s\n";
}

int main(int ac, char *av[])
{
  if (ac == 1) {
    std::cerr << "Error: in main: PmergeMe must have at least 1 argument\n";
    return EXIT_FAILURE;
  }
  PmergeMe pmerge;
  try {
    pmerge.fillContainers(av);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  printAndLaunchSorting(pmerge, "vector", ac - 1);
  printAndLaunchSorting(pmerge, "deque", ac - 1);
  return EXIT_SUCCESS;
}
