/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Salama
 */

#include <climits>
#include <string>
#include <utility>
#include "Registers.h"
using namespace std;

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

// CONSIDER: EQU only, ignore ORG
//int UNKNOWN_YET = INT_MIN;

class SymbolTable {
public:
	SymbolTable() {
		preloadRegisters();
	}
	int insert(string symbol);
	int search(string symbol);
	int remove(string symbol);
private:
	map<string, pair<int,vector<int>>> symbolsNames;

	void preloadRegisters() {
	    vector<int> emptyVector;
	    pair<int,vector<int>> regValue;
	    regValue.second =emptyVector;
	    regValue.first =A;
        symbolsNames["A"] = regValue;
        regValue.first =X;
        symbolsNames["X"] = regValue;
        regValue.first =L;
        symbolsNames["L"] = regValue;
        regValue.first =B;
        symbolsNames["B"] = regValue;
        regValue.first =S;
        symbolsNames["S"] = regValue;
        regValue.first =T;
        symbolsNames["T"] = regValue;
        regValue.first =F;
        symbolsNames["F"] = regValue;
        regValue.first =PC;
        symbolsNames["PC"] = regValue;
        regValue.first =SW;
        symbolsNames["SW"] = regValue;
	}

	// returns INT_MIN (UNKNOWN_YET), in case of Forward Reference.
	int findSymbolValue(string key);

	// Just give a way to access them, you are not required to assembly the
	// Format 2 instructions, just create a place holders ...
	int findRegisterValue(regMnemonic reg);
	bool changeRegisterValue(regMnemonic reg, int value);
};
#endif /* SYMBOLTABLE_H_ */
