#include "Processor.h"
#include <string>
#include <iostream>

Processor& Processor::operator=(const Processor& p) {
	return *this;
}

 int Processor::getRegValByAdr(int regAdr) {
	 ifstream fRegisters(registers.registersFile);
	 string registersStream;

	 if (fRegisters.is_open()) {
		 while (fRegisters.good()) {
			 fRegisters >> registersStream;

			 int pointer = 0;

			 while (pointer < registersStream.length()) {
				 if (registersStream[pointer] == '[') {
					 if ((int(registersStream[++pointer]) - 48) == regAdr) {
						 fRegisters >> registersStream;
						 fRegisters.close();
						 return stoi(registersStream);
					 }
					 else
						 fRegisters >> registersStream;
				 }
			 }
		 }
		 fRegisters.close();
		 return -1;
	 }
 }

 void Processor::setRegValByAdr(int regAdr, int value) {
	 ifstream fRegisters(registers.registersFile);
	 ofstream fTemp("temp.txt");
	 string registersStream;
	 int numOfLines = 0;

	 if (fRegisters.is_open()) {
		 while (fRegisters.good()) {
			 fRegisters >> registersStream;
			 numOfLines++;
			 int pointer = 0;

			 while (pointer < registersStream.length()) {
				 if (registersStream[pointer] == '[') {
					 if ((int(registersStream[++pointer]) - 48) == regAdr) {
						 if (fTemp.is_open()) {
							 fTemp << (registersStream + " ");
							 fTemp << value;
							 fTemp << "\n";
						 }
						 else {
							 fRegisters.close();
							 return;
						 }
						 fRegisters >> registersStream;
					 }
					 else
					 {
						 if (fTemp.is_open()) {
							 fTemp << (registersStream + " ");
							 fRegisters >> registersStream;
							 fTemp << (registersStream + "\n");
						 }
						 else {
							 fRegisters.close();
							 return;
						 }
					 }
				 }
				 else
					 break;
			 }
		 }
		 fRegisters.close();
		 fTemp.close();

		 string line;
		 ofstream fRegistersOut(registers.registersFile);
		 ifstream fTempIn("temp.txt");
		 if (fRegistersOut.is_open() && fTempIn.is_open()) {
			 for (int i = 1; i < numOfLines; i++) {
				 getline(fTempIn, line);
				 fRegistersOut << (line + "\n");
			 }
			 getline(fTempIn, line);
			 fRegistersOut << line;
		 }
		 fRegistersOut.close();
		 fTempIn.close();
		 remove("temp.txt");
		 return;
	 }
 }

 int Processor::getRegValById(int regId) {
	 for (pair<int, int> reg : registers.registers) {
		 if (reg.second == regId)
			 return getRegValByAdr(reg.first);
	 }
 }

 void Processor::setRegValById(int regId, int value) {
	 for (pair<int, int> reg : registers.registers) {
		 if (reg.second == regId)
			 setRegValByAdr(reg.first, value);
	 }
 }
