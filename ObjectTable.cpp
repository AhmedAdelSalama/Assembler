/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Waleed
 */

#include "ObjectTable.h"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

string toUpper(string s);

// returns 0 (false) if not found
bool ObjectTable::doesItExist(string mnemonic) {
	mnemonic = toUpper(mnemonic);
	// http://www.cplusplus.com/reference/map/map/find/
	std::map<string, int>::iterator check;
	check = mnemonicNames.find(mnemonic);
	if (check != mnemonicNames.end())
		return true;
	return false;
}

// returns -1 if not found
int ObjectTable::getOpCode(string mnemonic) {
	if (doesItExist(mnemonic)) {
		mnemonic = toUpper(mnemonic);
		return mnemonicNames[mnemonic];
	} else
		return -1;
}

// returns -1 if not found
int ObjectTable::getFormat(string mnemonic) {
	switch (getOpCode(mnemonic)) {
	case FIX:
	case FLOAT:
	case HIO:
	case NORM:
	case SIO:
	case TIO:
		return 1;
	case ADDR:
	case CLEAR:
	case COMPR:
	case DIVR:
	case MULR:
	case RMO:
	case SHIFTL:
	case SHIFTR:
	case SUBR:
	case SVC:
	case TIXR:
		return 2;
	case -1:
		return -1;
	default:
		return 3;
	}
}

string toUpper(string s) {
	// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}
