#pragma once

#include "Lexer.h"
#include "Expression.h"
#include "Values.h"
#include <list>

class Parser
{
private:
	Lexer lexer;
	pair<int, int> token;

	void next();
	Operand secondOperand();
	Operand firstOperand();

public:
	inline Parser() = default;
	Parser(Lexer);

	bool endOfFile();
	Expression nextExpression();

};

