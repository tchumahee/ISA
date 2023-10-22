#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer lexer) : lexer(lexer) {
	next();
}

void Parser::next() {
	pair<int, int> temp = lexer.next();
	std::cout << "Next token: " << temp.first << " " << temp.second << endl; 
	token = temp;
}

Operand Parser::secondOperand() {
	try {
		if (token.first == BR_OP) {
			next();
			if (token.first == NUM) {
				pair<int, int> reg = token;
				next();
				if (token.first == BR_CL)
					return Operand(reg.second, false, true); // 2. true za indirektno referenciranje
				else throw new std::exception();
			}
			else if (token.first == REG) {
				pair<int, int> reg = token;
				next();
				if (token.first == BR_CL)
					return Operand(reg.second, true, true); // 1. true za registar; 2. true za indirektno referenciranje
				else throw new std::exception();
			}
		}
		else if (token.first == NUM)
			return Operand(token.second, false, false);
		else if (token.first == REG)
			return Operand(token.second, true, false);
		else
			throw std::exception();
	}
	catch (std::exception ex) {
		throw new std::exception("Invalid operand value.");
	}
}

Operand Parser::firstOperand() {
	Operand operand = secondOperand();
	if (operand.getIndirectRef() == false && operand.getIsRegister() == false)
		throw std::exception("First operand must be a register name or memory address.");
	return operand;
}

bool Parser::endOfFile() {
	if (lexer.endOfFile())
		return true;
	return false;
}

Expression Parser::nextExpression() {
	if (!endOfFile())
	{
		try {
			if (token.first != OP)
			{
				throw std::exception("Invalid operation.");
			}

			int operation = token.second;

			next();
			if (token.first != BR_OP && token.first != REG && token.first != NUM)
				throw std::exception("Invalid first operand.");
			Operand op1 = firstOperand();
			next();
			if (token.first != COMMA)
				throw std::exception("Operands must be separated by ','.");
			next();
			if (token.first != BR_OP && token.first != REG && token.first != NUM)
				throw std::exception("Invalid first operand.");
			Operand op2 = secondOperand();
			next();

			if (token.first != DELIM)
				throw std::exception("';' expected at end of command.");
			next();
			return Expression(operation, op1, op2);
		}
		catch (std::exception ex) {
			std::cout << "Invalid command: ";
			std::cout << ex.what();
			throw ex;
		}
	}
}