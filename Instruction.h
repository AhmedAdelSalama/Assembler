/*
 * Instruction.cpp
 *
 *  Created on: May 27, 2020
 *      Author: Bahaa, Islam Ahmden
 */

#include <string>
#include "Expression.h"
#include "SymbolTable.h"

using namespace std;

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

class Instruction {
public:
	string label;
	string operation;
	string operator1;
	string operand1;
	string operand2;
	int instructionLenght;
	SymbolTable sym;
	//Expression operand;   // e.g. for most Format 3 instructions it will be the TA,
	// So you are required to calculate the disp.

	// These should be 0's and 1's (instantiated as chars "just for readability")
	//bool flags[] = { 'n', 'i', 'x', 'b', 'p', 'e' };

	int LOCCTR;
//	Instruction(string _label, string _operation, Expression _operand, int _LOCCTR);
	Instruction(string _label, string _operation, string _operand1,
			string _operator1, string _operand2, int _LOCCTR, SymbolTable _sym);
	int getInstructionLength();
	int expression();
	int evaluateExp(string p1, string op, string p2, int flag);
	string perform();

};

#endif /* INSTRUCTION_H_ */
