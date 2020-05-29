/*
 * InstructionHandler.h
 *
 *  Created on: May 27, 2020
 *      Author: EvilS
 */

#include "Instruction.h"
#include "ObjectCodeHandler.h"

#ifndef INSTRUCTIONHANDLER_H_
#define INSTRUCTIONHANDLER_H_

class InstructionHandler {
public:
	InstructionHandler();

	//returns false when the instruction is not correct
	//It will pass the address and object code of the instruction
	//to the ObjectCodeHandler to do this job (Eslam Ahmed)
	bool handle(Instruction inst) {
		string result;
		//should be formated like this:
		//result = "1000 141033"
		//"<Adress><one space><Object Code>"
		result = evaluateInstruction(inst); // (Bahaa + Islam)

		// re
		if (result.compare("Error"))
			return false;
		// return false -> bad instruction

		interpreter.record();	// (Eslam Ahmed)

		return true;
	}

private:
	ObjectCodeHandler interpreter;

	//return "Error" in case of bad instruction
	//should be formated like this : result = "1000 141033"
	string evaluateInstruction(Instruction inst);
};

#endif /* INSTRUCTIONHANDLER_H_ */
