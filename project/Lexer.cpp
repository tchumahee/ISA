#include "Lexer.h"
#include <iostream>

Lexer::Lexer() {
	pointer = 0;
}

Lexer::Lexer(string s) {
	sourceCode = s;
	pointer = 0;
}

pair<int, int> Lexer::next() {
	string temp;

	while (pointer < sourceCode.length() && isspace(sourceCode[pointer])) {
		pointer++;
	}

	if (pointer < sourceCode.length() && isdigit(sourceCode[pointer]))
	{
		do {
			temp += sourceCode[pointer++];
		}
		while (pointer < sourceCode.length() && isdigit(sourceCode[pointer]));
		return { NUM, stoi(temp) };
	}

	if (pointer < sourceCode.length() && isalpha(sourceCode[pointer]))
	{
		do {
			temp += sourceCode[pointer++];
		} while (pointer < sourceCode.length() && isalpha(sourceCode[pointer]));

		if (temp == "ADD" || temp == "add")
			return { OP, ADD };
		if (temp == "SUB" || temp == "sub")
			return { OP, SUB };
		if (temp == "MUL" || temp == "mul")
			return { OP, MUL };
		if (temp == "DIV" || temp == "div")
			return { OP, DIV};
		if (temp == "AND" || temp == "and")
			return { OP, AND };
		if (temp == "OR" || temp == "or")
			return { OP, OR};
		if (temp == "NOT" || temp == "not")
			return { OP, NOT};
		if (temp == "XOR" || temp == "xor")
			return { OP, XOR };
		if (temp == "MOV" || temp == "mov")
			return { OP, MOV };

		if (temp == "RAX" || temp == "rax")
			return { REG, RAX};
		if (temp == "RBX" || temp == "rbx")
			return { REG, RBX };
		if (temp == "RCX" || temp == "rcx")
			return { REG, RCX };
		if (temp == "RDX" || temp == "rdx")
			return { REG, RDX };
	}

	pair<int, int> retVal;

	if (pointer < sourceCode.length())
	{
		switch (sourceCode[pointer]) {
		case ',':
			retVal = { COMMA, 0 };
			pointer++;
			break;
		case ';':
			retVal = { DELIM, 0 };
			pointer++;
			break;
		case '[':
			retVal = { BR_OP, 0 };
			pointer++;
			break;
		case ']':
			retVal = { BR_CL, 0 };
			pointer++;
			break;
		default:
			throw std::exception();
		}

		return retVal;
	}
}

bool Lexer::endOfFile() {
	if (pointer >= sourceCode.length())
		return true;
	return false;
}
