#pragma once
#include <string>
#include "Values.h"

using namespace std;

class Lexer
{

private:
	string sourceCode;
	int pointer;

public:
	Lexer();
	Lexer(string);
	pair<int, int> next();
	bool endOfFile();
};

