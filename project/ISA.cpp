#include "ISA.h"
#include <iostream>

ISA::ISA(Processor procesor) {
	processor = procesor;
}

void ISA::readCode(string sourceCode) {
	ifstream fSource(sourceCode);
	string source = "";
	string line;

	while (getline(fSource, line))
		source += (line + " ");

	lexer = Lexer(source);
	parser = Parser(lexer);
}

void ISA::evaluateCode() {
	while (!parser.endOfFile()) {
		try {
			evaluateNextExpression();
		}
		catch (std::exception ex) {
			return;
		}
	}
}

void ISA::evaluateNextExpression() {
	int destReg = 0;
	bool destIsAdr = false;
	int op1 = 0, op2 = 0;

	try {
		Expression temp = parser.nextExpression();
		currentExpression = temp;
	}
	catch (std::exception ex) {
		throw ex;
	}

	std::cout << "EXPRESSION: ";
	currentExpression.printExpression();

	if (currentExpression.getFirstOperand().getIndirectRef()) {
		if (currentExpression.getFirstOperand().getIsRegister()) {
			op1 = processor.getRegValById(processor.getRegValById(currentExpression.getFirstOperand().getValue())); // vrijednost na adresi na koju pokazuje sadrzaj datog registra
			destReg = processor.getRegValById(currentExpression.getFirstOperand().getValue());
		}
		else {
			op1 = processor.getRegValById(currentExpression.getFirstOperand().getValue());
			destReg = currentExpression.getFirstOperand().getValue();
			destIsAdr = true;
		}
	}
	else {
		op1 = processor.getRegValById(currentExpression.getFirstOperand().getValue());
		destReg = currentExpression.getFirstOperand().getValue();
	}

	if (currentExpression.getSecondOperand().getIndirectRef()) {
		if (currentExpression.getSecondOperand().getIsRegister())
			op2 = processor.getRegValById(processor.getRegValById(currentExpression.getSecondOperand().getValue()));
		else
			op2 = processor.getRegValById(currentExpression.getSecondOperand().getValue());
	}
	else {
		if (currentExpression.getSecondOperand().getIsRegister())
			op2 = processor.getRegValById(currentExpression.getSecondOperand().getValue());
		else
			op2 = currentExpression.getSecondOperand().getValue();
	}

	switch (currentExpression.getOperation()) {
	case ADD:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 + op2) : processor.setRegValById(destReg, op1 + op2);
		break;
	case SUB:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 - op2) : processor.setRegValById(destReg, op1 - op2);
		break;
	case MUL:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 * op2) : processor.setRegValById(destReg, op1 * op2);
		break;
	case DIV:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 / op2) : processor.setRegValById(destReg, op1 / op2);
		break;
	case MOV:
		destIsAdr ? processor.setRegValByAdr(destReg, op2) : processor.setRegValById(destReg, op2);
		break;
	case AND:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 & op2) : processor.setRegValById(destReg, op1 & op2);
		break;
	case OR:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 | op2) : processor.setRegValById(destReg, op1 | op2);
		break;
	case XOR:
		destIsAdr ? processor.setRegValByAdr(destReg, op1 ^ op2) : processor.setRegValById(destReg, op1 ^ op2);
		break;
	}
}
