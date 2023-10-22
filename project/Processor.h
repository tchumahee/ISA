#pragma once
#include "Registers.h"

class Processor
{
private:
	Registers registers = Registers();

public:
	Processor() = default;

	Processor& operator=(const Processor&);

	int getRegValByAdr(int);
	void setRegValByAdr(int, int);
	int getRegValById(int);
	void setRegValById(int, int);
};

