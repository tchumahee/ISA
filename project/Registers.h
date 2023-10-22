#pragma once
#include <fstream>
#include "Values.h"

using namespace std;

class Registers
{
private:
	friend class Processor;
	friend class Parser;

	pair<int, const int> registers[4] = { {1, RAX}, {2, RBX}, {3, RCX}, {4, RDX} }; 

	const string registersFile = "sadrzaj_registara.txt";

	inline Registers() = default;
};

