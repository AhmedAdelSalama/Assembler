/*
 * Instruction.cpp
 *
 *  Created on: May 27, 2020
 *      Author: Bahaa, Islam Ahmden
 */

#include <string>
#include "Expression.h"
using namespace std;

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

class Instruction {
public:
	string label;
	string operation;
	Expression operand;   // e.g. for most Format 3 instructions it will be the TA,
						// So you are required to calculate the disp.

	// These should be 0's and 1's (instantiated as chars "just for readability")
	bool flags[] = { 'n', 'i', 'x', 'b', 'p', 'e' };

	int LOCCTR;

	Instruction(string _label, string _operation, Expression _operand, int _LOCCTR);
	int getInstructionLength();
};

class StorageInstruction: Instruction {
	//It needs special treatment I guess.
};

class AssemblyInstruction: Instruction {
public:
	int format;
};

#endif /* INSTRUCTION_H_ */
