/*
 * Instruction.cpp
 *
 *  Created on: May 27, 2020
 *      Author: Bahaa, Islam Ahmden
 */

#include "SymbolTable.h"
#include <string>
using namespace std;

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

//IMPORTANT NOTE: try to make the Expression simple
//Let is just calculate math steps using SymTable values if needed,
//and let the Instruction class do the rest based on addressing flags.

/* Expressions consist of
 * Operator [+, -, *, /] (division is usually defined to produce an  integer result)
 * Individual terms [Constants, User-defined symbols]
 */

class Expression {
public:
	string expression;
	SymbolTable SymTable;
	int calculateValue();
	Expression(string _expression, SymbolTable _SymTable);
};

#endif /* EXPRESSION_H_ */
