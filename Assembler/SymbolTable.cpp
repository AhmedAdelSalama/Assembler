/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Salama
 */

#include "SymbolTable.h"
#include <string>
using namespace std;

void SymbolTable::add(string symbol , int value){
    std::map<string, int>::iterator itr;
	itr = symbolsNames.find(symbol);
    if (itr == symbolsNames.end()) {
		symbolsNames[symbol] = value;
	}
}
//returns -1 if symbol is not found
//returns the value otherwise "forward reference"
int SymbolTable::getSymbolValue(string symbol){
    std::map<string, int>::iterator itr;
	itr = symbolsNames.find(symbol);
	if (itr != symbolsNames.end()) {
		return itr->second;
	}
	return -1;
}
//returns -1 for invalid arguments
//returns register value otherwise
int SymbolTable::findRegisterValue(regMnemonic reg){
    string registers[10] = {"A","X","L","B","S","T","F","PC","SW"};
    return symbolsNames.find(registers[reg])->second;
}
