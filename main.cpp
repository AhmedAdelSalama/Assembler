//============================================================================
// Name        : Assembler.cpp
// Author      : https://youtu.be/AhCLgRVcKMg
// Version     : 0.0v
// Copyright   : Your copyright notice
// Description : Hello World
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <algorithm>
#include <string>
#include "SplitLine.h"
#include "Parser.h"
#include "Registers.h"
#include "ObjectTable.h"
#include "Instruction.h"
#include "InstructionHandler.h"
#include "ObjectCodeHandler.h"

using namespace std;

int main(int argc, char *argv[]) {

	/* Should be modified to
	 * TODO LOCCTR = program start position.
	 * be careful with it, since it will be passed to every
	 * instruction and will be incremented as follows:
	 * LOCCTR += <some instruction>.length();
	 */

	// Ahmed Salama will fill out the Symbol Table,
	// and will be responsible for:
	// -> START (Store the program name and Initial LOCCTR)
	// -> EQU (Just treat it like any other entity in the symbol table) Directive as well. (END is just a flag)
	//---------------------------------------------------------------- *
	//SymbolTable SymTable;
	//InstructionHandler assembler;
	//General Algorithm
	/**
	 * read a line
	 * Identify it using regex
	 * detect labels, store its address or put a * if not defined yet
	 * pass the instruction to the Instruction Handler
	 * repeat
	 */
	int LOCCTR = 0, lineNumber = 0;
	SymbolTable symTable;
	string line;
	ifstream file(argv[1]);
	ofstream outfile;
	ofstream ofs;
	ofs.open("report.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofs.open("objcod.txt", ios::out | ios::trunc);
	ofs.close();
	outfile.open("report.txt", ios::app);
	while (getline(file, line)) {
		lineNumber++;
		transform(line.begin(), line.end(), line.begin(), ::toupper);
		line.append("\n");
		SplitLine spl = parseLine(lineNumber, line);
		string x = spl.label + " " + spl.instruction + " " + spl.operand1 + " "
				+ spl._operator + " " + spl.operand2;
		cout << x << endl;
		// cout <<lineNumber<<": label: " <<spl.label<<" operation: " <<spl.instruction<<" operand1: " <<spl.operand1<<" operator: " <<spl._operator<<" operand2: " <<spl.operand2 <<endl;
		if (!spl.isComment) {
			Instruction inst(spl.label, spl.instruction, spl.operand1,
					spl._operator, spl.operand2, LOCCTR, symTable);
			if (spl.instruction == "START") {
				if (spl.operand1.length() > 0) {
					LOCCTR = stoi(spl.operand1, 0, 16);
					ObjectCodeHandler objectCodeHandler("", spl.operand1,
							spl.label, "");
					objectCodeHandler.record();
				}
				if (spl.label.length() > 0) {
					symTable.add(spl.label, LOCCTR);
				}
				//eslam
				//GENERATE HEADER RECORD
			} else if (spl.instruction == "END") {
				//eslam
				//GENERATE END RECORD
			} else if (spl.instruction == "EQU") {
				int value = inst.expression();
				symTable.updateValue(spl.label, value);
				cout << value << endl;
			} else {
				//build SYMTAB
				if (spl.label.length() > 0) {
					symTable.add(spl.label, LOCCTR);
				}
				string result = inst.perform();
				int length = result.length();
				if (result[0] == 'E') {
					//ERROR
					outfile << "line " << lineNumber << ":" << result << endl;
					exit(1);
				} else if (result == "") {
					char hexString[20];
					itoa(LOCCTR, hexString, 16);

					ObjectCodeHandler objectCodeHandler(result, spl.operand1,
							spl.label, hexString);
					objectCodeHandler.record();
				}

				else {
					ObjectCodeHandler objectCodeHandler(result, spl.operand1,
							spl.label, "");
					objectCodeHandler.record();
				}
				LOCCTR += inst.getInstructionLength();
			}

		}

	}
	file.close();
	outfile.close();

	return 0;
}

