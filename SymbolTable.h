/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Salama
 */

#include <climits>
#include <string>
#include "Registers.h"
using namespace std;

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

// CONSIDER: EQU only, ignore ORG
//int UNKNOWN_YET = INT_MIN;

class SymbolTable {
public:
	SymbolTable();

	// returns INT_MIN (UNKNOWN_YET), in case of Forward Reference.
	int findSymbolValue(string key);

	// Just give a way to access them, you are not required to assembly the
	// Format 2 instructions, just create a place holders ...
	int findRegisterValue(regMnemonic reg);
	bool changeRegisterValue(regMnemonic reg, int value);
};

class Symbol {
public:
	string key;
	int value;
	bool flag;

	Symbol(string _key, int _value);
};

#endif /* SYMBOLTABLE_H_ */
