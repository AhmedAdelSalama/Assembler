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

const int NO_RESULT = -1;

string toUpper(string s);

// returns -1 -> !found
// returns  1 -> found
// return   4 -> found && Format 4
int ObjectTable::doesItExist(string mnemonic) {
	mnemonic = toUpper(mnemonic);

	//check Format 4
	bool isFormat4 = mnemonic.at(0) == '+';
	if (isFormat4) {
		//https://www.tutorialspoint.com/substring-in-cplusplus
		mnemonic = mnemonic.substr(1, mnemonic.length());
	}

	// http://www.cplusplus.com/reference/map/map/find/
	std::map<string, int>::iterator check;
	check = mnemonicNames.find(mnemonic);
	if (check != mnemonicNames.end()) {
		if (isFormat4)
			return 4;
		return 1;
	}
	return 0;
}

bool Format4Flag = false;

// returns -1 -> !found
// otherwise: returns the correct operation code.
int ObjectTable::getOpCode(string mnemonic) {
	int exists = doesItExist(mnemonic);
	if (exists) {
		if(exists == 4){
			Format4Flag = true;
			mnemonic = mnemonic.substr(1, mnemonic.length());
		}
		mnemonic = toUpper(mnemonic);
		return mnemonicNames[mnemonic];
	} else
		return NO_RESULT;
}

// returns -1 -> !found
// otherwise: returns the correct format.
int ObjectTable::getFormat(string mnemonic) {
	Format4Flag = false;
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
	case NO_RESULT:
		return NO_RESULT;
	default:
		if(Format4Flag)
			return 4;
		return 3;
	}
}

string toUpper(string s) {
	// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}
