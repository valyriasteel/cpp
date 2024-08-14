#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>

class RPN
{
	private:
		std::stack<int> _stack;
	public:
		RPN();
		~RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &copy);
		RPN(std::string &input);
		int getResult();

		class InvalidArgument : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: invalid argument use: ./RPN \"<expression>\"";
				}
		};

		class StackToSmall : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: stack too small";
				}
		};

		class DivisionByZero : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: division by zero";
				}
		};

		class UnknownOperator : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error";
				}
		};

		class MissingOperators : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: missing operators";
				}
		};
};

#endif