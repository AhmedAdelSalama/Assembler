/*
 * ObjectTable.h
 *
 *  Created on: May 26, 2020
 *      Author: Ahmed Waleed
 */

#include <map>
#include <string>
using namespace std;

enum mnemonic {
	LDA = 0x0,
	LDX = 0x4,
	LDL = 0x8,
	STX = 0x10,
	STL = 0x14,
	ADD = 0x18,
	MUL = 0x20,
	DIV = 0x24,
	COMP = 0x28,
	JEQ = 0x30,
	JGT = 0x34,
	JLT = 0x38,
	AND = 0x40,
	OR = 0x44,
	LDCH = 0x50,
	STCH = 0x54,
	ADDF = 0x58,
	MULF = 0x60,
	DIVF = 0x64,
	LDB = 0x68,
	LDF = 0x70,
	LDT = 0x74,
	STB = 0x78,
	STF = 0x80,
	STT = 0x84,
	COMPF = 0x88,
	ADDR = 0x90,
	SUBR = 0x94,
	MULR = 0x98,
	STA = 0x0C,
	SUB = 0x1C,
	TIX = 0x2C,
	J = 0x3C,
	JSUB = 0x4B,
	RSUB = 0x4C,
	SUBF = 0x5C,
	LDS = 0x6C,
	STS = 0x7C,
	DIVR = 0x9C,
	COMPR = 0xA0,
	SHIFTL = 0xA4,
	SHIFTR = 0xA8,
	RMO = 0xAC,
	SVC = 0xB0,
	CLEAR = 0xB4,
	TIXR = 0xB8,
	FLOAT = 0xC0,
	FIX = 0xC4,
	NORM = 0xC8,
	LPS = 0xD0,
	STI = 0xD4,
	RD = 0xD8,
	WD = 0xDC,
	TD = 0xE0,
	STSW = 0xE8,
	SSK = 0xEC,
	SIO = 0xF0,
	HIO = 0xF4,
	TIO = 0xF8,
};

#ifndef OBJECTTABLE_H_
#define OBJECTTABLE_H_

class ObjectTable {
public:
	ObjectTable() {
		buildTable();
	}

	int doesItExist(string mnemonic);
	int getOpCode(string mnemonic);
	int getFormat(string mnemonic);
private:
	map<string, int> mnemonicNames;

	// https://stackoverflow.com/questions/42842698/c-name-from-enum-displayed-as-string
	void buildTable() {
		mnemonicNames["ADD"] = ADD;
		mnemonicNames["ADDF"] = ADDF;
		mnemonicNames["ADDR"] = ADDR;
		mnemonicNames["AND"] = AND;
		mnemonicNames["CLEAR"] = CLEAR;
		mnemonicNames["COMP"] = COMP;
		mnemonicNames["COMPF"] = COMPF;
		mnemonicNames["COMPR"] = COMPR;
		mnemonicNames["DIV"] = DIV;
		mnemonicNames["DIVF"] = DIVF;
		mnemonicNames["DIVR"] = DIVR;
		mnemonicNames["FIX"] = FIX;
		mnemonicNames["FLOAT"] = FLOAT;
		mnemonicNames["HIO"] = HIO;
		mnemonicNames["J"] = J;
		mnemonicNames["JEQ"] = JEQ;
		mnemonicNames["JGT"] = JGT;
		mnemonicNames["JLT"] = JLT;
		mnemonicNames["JSUB"] = JSUB;
		mnemonicNames["LDA"] = LDA;
		mnemonicNames["LDB"] = LDB;
		mnemonicNames["LDCH"] = LDCH;
		mnemonicNames["LDF"] = LDF;
		mnemonicNames["LDL"] = LDL;
		mnemonicNames["LDS"] = LDS;
		mnemonicNames["LDT"] = LDT;
		mnemonicNames["LDX"] = LDX;
		mnemonicNames["LPS"] = LPS;
		mnemonicNames["MUL"] = MUL;
		mnemonicNames["MULF"] = MULF;
		mnemonicNames["MULR"] = MULR;
		mnemonicNames["NORM"] = NORM;
		mnemonicNames["OR"] = OR;
		mnemonicNames["RD"] = RD;
		mnemonicNames["RMO"] = RMO;
		mnemonicNames["RSUB"] = RSUB;
		mnemonicNames["SHIFTL"] = SHIFTL;
		mnemonicNames["SHIFTR"] = SHIFTR;
		mnemonicNames["SIO"] = SIO;
		mnemonicNames["SSK"] = SSK;
		mnemonicNames["STA"] = STA;
		mnemonicNames["STB"] = STB;
		mnemonicNames["STCH"] = STCH;
		mnemonicNames["STF"] = STF;
		mnemonicNames["STI"] = STI;
		mnemonicNames["STL"] = STL;
		mnemonicNames["STS"] = STS;
		mnemonicNames["STSW"] = STSW;
		mnemonicNames["STT"] = STT;
		mnemonicNames["STX"] = STX;
		mnemonicNames["SUB"] = SUB;
		mnemonicNames["SUBF"] = SUBF;
		mnemonicNames["SUBR"] = SUBR;
		mnemonicNames["SVC"] = SVC;
		mnemonicNames["TD"] = TD;
		mnemonicNames["TIO"] = TIO;
		mnemonicNames["TIX"] = TIX;
		mnemonicNames["TIXR"] = TIXR;
		mnemonicNames["WD"] = WD;
	}
};

#endif /* OBJECTTABLE_H_ */
