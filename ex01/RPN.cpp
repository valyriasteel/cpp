#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN &copy)
{
	_stack = copy._stack;
}

RPN& RPN::operator=(const RPN &copy)
{
	if (this == &copy)
		return *this;
	_stack = copy._stack;
	return *this;
}

RPN::RPN(std::string &input)
{
	int i = -1;
	const char *cstr;

	while (input.c_str()[++i])
		if (input.c_str()[i] == ' ')
			input.erase(i, 1);
	cstr = input.c_str();
	i = -1;
	while (cstr[++i])
	{
		if (isdigit(cstr[i]))
			_stack.push(cstr[i] - '0');
		else if (cstr[i] == '+' || cstr[i] == '-' || cstr[i] == '*' || cstr[i] == '/')
		{
			if (_stack.size() < 2)
				throw RPN::StackToSmall();
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			switch (cstr[i])
			{
			case '+':
				_stack.push(a + b);
				break;
			case '-':
				_stack.push(a - b);
				break;
			case '*':
				_stack.push(a * b);
				break;
			case '/':
				if (b == 0)
					throw RPN::DivisionByZero();
				_stack.push(a / b);
				break;
			}
		}
		else
			throw RPN::UnknownOperator();
	}
	if (_stack.size() != 1)
		throw RPN::MissingOperators();
}

int RPN::getResult()
{
	return _stack.top();
}