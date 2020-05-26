/*
 * Instruction.h
 *
 *  Created on: May 27, 2020
 *      Author: ---
 */

#include <string>
#include "Expression.h"
using namespace std;

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

class Instruction {
public:
	string label;
	int OPCODE;
	int operandValue;   // e.g. for most Format 3 instructions it will be the TA,
						// So you are required to calculate the disp.

	// These should be 0's and 1's (instantiated as chars "just for readability")
	bool flags[] = { 'n', 'i', 'x', 'b', 'p', 'e' };

	int LOCCTR;

	Instruction() = 0;
	long getObjectCode() = 0;
};

class StorageInstruction: Instruction {
	//It needs special treatment I guess.
};

class AssemblyInstruction: Instruction {
public:
	int format;
};

#endif /* INSTRUCTION_H_ */
