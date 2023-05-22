#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <vector>
#include <deque>
#include <iostream>

enum e_time {BEFORE_SORT, AFTER_SORT, DEBUG};

class PmergeMe { 
	public:
	 PmergeMe();
	 ~PmergeMe();
	 PmergeMe(const PmergeMe& other);
	 PmergeMe& operator=(const PmergeMe& other);
	 std::vector<int>& getVector();
	 std::deque<int>& getDeque();
	 void fillContainers(char**);

	 // Allow to get container type without what type is inside + specify a type
	 template <template<typename, typename>class TContainer, typename type, typename T>
	 void sortContainer(TContainer<type, T>& container) 
	 {
	 	 TContainer<std::pair<type, type>, T> pairContainer;
	 	 emptyInitialContainer(container, pairContainer);
	 	 TContainer<std::pair<type, type>, T> pendingElements;
		 sortByFirstIndice(container, pairContainer, pendingElements);
		 insertSecondIndice(container, pendingElements);
	 }

	 template <typename T>
	 void printContainer(T& container, int time) const
	 {
	 	 typename T::const_iterator it = container.begin();
	 	 typename T::const_iterator ite = container.end();
	 	 if (time == BEFORE_SORT)
	 	 	 std::cout << "Before:\t";
	 	 else if (time == AFTER_SORT) 
	 	 	 std::cout << "After:\t";
	 	 else {
	 	 	 static int i;
	 	 	 std::cout << i++ << "DEBUG:\t";
	 	 }
	 	 while (it != ite) {
			 std::cout << *it << " ";
	 	 	 it++;
	 	 }
		 std::cout << '\n';
	 }

	private:
	 std::vector<int> _vector;
	 std::deque<int> _deque;

	private:
	 // Empty the initial container into a container of the same type which
	 // holds pairs of int instead of raw ints
	 // Also swaps values of said pairs in ascending order
	 template <template<typename, typename>class TContainer, typename type, typename T>
	 void emptyInitialContainer(TContainer<type, T>& container, TContainer<std::pair<type, type>, T>& pairContainer)
	 {
	 	 if (container.size() >= 2) {
	 	 	 type tmp = container.front();
	 	 	 container.erase(container.begin());
	 	 	 type tmp2 = container.front();
	 	 	 container.erase(container.begin());
	 	 	 if (tmp > tmp2) {
	 	 	 	 type swap = tmp;
	 	 	 	 tmp = tmp2;
	 	 	 	 tmp2 = swap;
	 	 	 }
	 	 	 pairContainer.push_back(std::make_pair(tmp, tmp2));
	 	 	 emptyInitialContainer(container, pairContainer);
	 	 }
	 	 else if (container.size() == 1) {
	 	 	 pairContainer.push_back(std::make_pair(-1, container.front()));
	 	 	 container.erase(container.begin());
	 	 }
	 }

	 template <template<typename, typename>class TContainer, typename type, typename T>
	 void sortByFirstIndice(TContainer<type, T>& container, TContainer<std::pair<type, type>, T>& pairContainer, TContainer<std::pair<type, type>, T>& pendingElements)
	 {
	 	 if (!pairContainer.empty()) {
			 type firstIndiceValue = pairContainer.begin()->first;
			 // Means number of values to sort is odd
			 if (firstIndiceValue == -1) {
			 	 pendingElements.push_back(std::make_pair(-1, pairContainer.begin()->second));
			 	 pairContainer.erase(pairContainer.begin());
			 	 return;
			 }

			 // Insert back 'a' value of [a,b] in original container, keep b in a separate container with the index 'a' was put in
			 typename TContainer<type, T>::iterator it = container.begin();
			 size_t containerSize = container.size();
			 int index = 0;
			 for ( ; static_cast<size_t>(index) < containerSize ; index++, it++) {
			 	 if (firstIndiceValue <= container[index])
			 	 	 break;
			 }
			 container.insert(it, firstIndiceValue);
			 pendingElements.push_back(std::make_pair(index, pairContainer.begin()->second));
			 pairContainer.erase(pairContainer.begin());
			 sortByFirstIndice(container, pairContainer, pendingElements);
	 	 }
	 }

	 template <template<typename, typename>class TContainer, typename type, typename T>
	 void insertSecondIndice(TContainer<type, T>& container, TContainer<std::pair<type, type>, T>& pendingElements)
	 {
	 	 if (!pendingElements.empty()) {
	 	 	 int index = pendingElements.begin()->first;
	 	 	 if (index == -1)
	 	 	 	 index = 0;
			 type secondIndiceValue = pendingElements.begin()->second;
			 size_t containerSize = container.size();
			 typename TContainer<type, T>::iterator it = container.begin() + index;
			 for ( ; static_cast<size_t>(index) < containerSize ; index++, it++) {
			 	 if (secondIndiceValue <= container[index])
			 	 	 break;
			 }
			 container.insert(it, secondIndiceValue);
			 pendingElements.erase(pendingElements.begin());
			 insertSecondIndice(container, pendingElements);
	 	 }
	 }

	 template <template<typename, typename>class TContainer, typename type, typename T>
	 void printPairContainer(TContainer<std::pair<type, type>, T >& pairContainer) const
	 {
	 	 typename TContainer<std::pair<type, type>, T>::const_iterator it = pairContainer.begin();
	 	 typename TContainer<std::pair<type, type>, T>::const_iterator ite = pairContainer.end();
		 std::cout << "Pair Container:";
	 	 while (it != ite) {
			 std::cout << " {" << it->first << ',' << it->second << '}';
	 	 	 it++;
	 	 }
		 std::cout << '\n';
	 }

 } ;


#endif // PMERGEME_HPP_
