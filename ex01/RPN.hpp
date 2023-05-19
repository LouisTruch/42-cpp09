#ifndef RPN_HPP_
#define RPN_HPP_

#include <stack>
#include <string>

class RPN { 
	public:
	 RPN();
	 ~RPN();
	 RPN(const RPN& other);
	 RPN& operator=(const RPN& other);

	 void RPNisation(const std::string&);
	 void computeOperator(int);

	private:
	 std::stack<double> _stack;
 } ;

bool isoperator(int c);

#endif // RPN_HPP_
