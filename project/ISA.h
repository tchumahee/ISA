#pragma once
#include "Expression.h"
#include "Lexer.h"
#include "Parser.h"
#include "Processor.h"

class ISA
{
private:
	Lexer lexer;
	Parser parser;
	Expression currentExpression; 
	Processor processor = Processor();

	void evaluateNextExpression();

public:
	ISA(Processor);

	void readCode(string);
	void evaluateCode();
};

