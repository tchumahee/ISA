#pragma once
#include <string>

using namespace std;

class Operand
{
private:
	int value;
	bool indirectRef;
	bool isRegister;

public:
	Operand() = default;
	Operand(int value, bool isRegister, bool indirectRef) : value(value), isRegister(isRegister), indirectRef(indirectRef) {};

	bool getIndirectRef() { return indirectRef; }
	bool getIsRegister() { return isRegister; }
	int getValue() { return value; }
};
