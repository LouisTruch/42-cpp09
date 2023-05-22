#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN& other)
{
	_stack = other._stack;
}

RPN& RPN::operator=(const RPN& other)
{
	if (&other == this)
		return *this;
	_stack = other._stack;
	return *this;
}

void RPN::RPNisation(const std::string& input)
{
	if (input.empty())
		throw std::invalid_argument ("Error: in RPN::parseInput: Input is empty");
	for(size_t i = 0 ; input[i] ; i++) {
		if (i % 2 == 0) {
			if (isdigit(input[i]))
				_stack.push(static_cast<double>(input[i] - '0'));
			else if (isoperator(input[i])) {
				try {
					computeOperator(input[i]);
				} catch (const std::exception& e) {
					std::cerr << e.what() << '\n';
					return;
				}
			}
			else
				throw std::invalid_argument ("Error: in RPN::parseInput: Bad input expected digit or operator");
		}
		else {
			if (input[i] != ' ')
				throw std::invalid_argument ("Error: in RPN::parseInput: Bad input expected space");
		}
	}
	if (_stack.size() > 1)
		throw std::invalid_argument ("Error: in RPN::parseInput: 2 or more numbers still present in stack");
	std::cout << _stack.top() << '\n';
}

void RPN::computeOperator(int operation)
{
	if (_stack.size() < 2)
		throw std::invalid_argument ("Error: in RPN::computeOperator: stack size was inferior to 2, can't compute");
	double tmp = _stack.top();
	_stack.pop();
	double tmp2 = _stack.top();
	_stack.pop();
	switch (operation) {
		case '+' :
			_stack.push(tmp2 + tmp);
			break;
		case '-' :
			_stack.push(tmp2 - tmp);
			break;
		case '*' :
			_stack.push(tmp2 * tmp);
			break;
		case '/' :
			if (tmp == 0)
				throw std::invalid_argument ("Error: in RPN::computeOperator: Can't divide by 0");
			_stack.push(tmp2 / tmp);
			break;
	}
}

bool RPN::isoperator(int c) const
{
  if (c == '+' || c == '-' || c == '*' || c == '/')
    return true;
  return false;
}
