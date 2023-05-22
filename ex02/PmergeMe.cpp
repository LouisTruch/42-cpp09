#include "PmergeMe.hpp"
#include <stdexcept>
#include <string>
#include <climits>
#include <cstdlib>
#include <cerrno>
#include <iostream>

#define DECIMAL_BASE 10

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_vector = other._vector;
	_deque = other._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (&other == this)
		return *this;
	_vector = other._vector;
	_deque = other._deque;
	return *this;
}

std::vector<int>& PmergeMe::getVector() {return _vector;}

std::deque<int>& PmergeMe::getDeque() {return _deque;}

void PmergeMe::fillContainers(char *av[])
{
  long int nb;
  for (size_t i = 1 ; av[i] ; i++) {
    errno = 0;
    std::string avStr(av[i]);
    if (avStr.empty())
    	throw std::invalid_argument ("Error: in PmergeMe::fillContainers: Empty argument");
    for (size_t j = 0 ; avStr[j]; j++) {
      if (!isdigit(avStr[j]))
    		throw std::invalid_argument ("Error: in PmergeMe::fillContainers: Invalid argument");
    }
    nb = strtol(avStr.c_str(), NULL, DECIMAL_BASE);
    if (nb > INT_MAX || errno == ERANGE)
    	throw std::invalid_argument ("Error: in PmergeMe::fillContainers: Overflow from one argument");
    _vector.push_back(static_cast<int>(nb));
    _deque.push_back(static_cast<int>(nb));
  }
}
