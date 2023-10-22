#pragma once

enum TokenType {
	OP = 21, REG = 22, NUM = 23,
	COMMA = 24, DELIM = 25, BR_OP = 26, BR_CL = 27, END = 28
};

enum Operation {
	ADD = 10, SUB = 11, MUL = 12, DIV = 13,
	AND = 14, OR = 15, NOT = 16, XOR = 17,
	MOV = 18
};

enum RegisterNames {
	RAX = 1, RBX = 2, RCX = 3, RDX = 4
};