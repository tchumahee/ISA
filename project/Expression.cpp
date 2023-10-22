#include "Expression.h"
#include <iostream>

using namespace std;

void Expression::printExpression() {
	cout << "Operation: " << operation << " First operand: " << firstOperand.getValue() << " Second operand: " << secondOperand.getValue() << endl;
}