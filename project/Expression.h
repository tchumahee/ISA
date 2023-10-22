#pragma once

#include "Operand.h"
#include "Values.h"
#include <string>

using namespace std;

class Expression
{
private:
	int operation;
	Operand firstOperand;
	Operand secondOperand;

public:
	Expression() = default;
	inline Expression(int operation, Operand firstOperand, Operand secondOperand) : operation(operation), firstOperand(firstOperand), secondOperand(secondOperand) {}; 

	int getOperation() { return operation; }
	Operand getFirstOperand() { return firstOperand; }
	Operand getSecondOperand() { return secondOperand; }

	void printExpression();
};

