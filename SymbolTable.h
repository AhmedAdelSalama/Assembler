/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Salama
 */

#include <climits>
#include <string>
#include <utility>
#include <map>
#include <string>
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
	void add(string symbol , int value);
	void updateValue(string symbol , int value);
    // returns -1, in case of Forward Reference.
	int getSymbolValue(string symbol);
    int findRegisterValue(regMnemonic reg);
private:
	map<string,int> symbolsNames;
	void preloadRegisters() {
        symbolsNames["A"] = A;
        symbolsNames["X"] = X;
        symbolsNames["L"] = L;
        symbolsNames["B"] = B;
        symbolsNames["S"] = S;
        symbolsNames["T"] = T;
        symbolsNames["F"] = F;
        symbolsNames["PC"] = PC;
        symbolsNames["SW"] = SW;
	}

	int findSymbolValue(string key);

};
#endif /* SYMBOLTABLE_H_ */
