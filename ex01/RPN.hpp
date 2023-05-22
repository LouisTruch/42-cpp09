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

	private:
	 std::stack<double> _stack;

	private:
	 void computeOperator(int);
	 bool isoperator(int) const;
 } ;

#endif // RPN_HPP_
