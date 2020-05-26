//============================================================================
// Name        : Assembler.cpp
// Author      : https://youtu.be/AhCLgRVcKMg
// Version     : 0.0v
// Copyright   : Your copyright notice
// Description : Hello World
//============================================================================

#include <iostream>
#include "Registers.h"
#include "ObjectTable.h"
#include "Instruction.h"
using namespace std;

int main() {

	ObjectTable opTable;

	cout << opTable.doesItExist("ADD") << endl;
	cout << opTable.doesItExist("+aDd") << endl;
	cout << opTable.doesItExist("He5o?") << endl;

	cout << opTable.getOpCode("ADD") << endl;
	cout << opTable.getOpCode("+aDd") << endl;
	cout << opTable.getOpCode("He5o?") << endl;

	cout << opTable.getFormat("ADD") << endl;
	cout << opTable.getFormat("+aDd") << endl;
	cout << opTable.getFormat("He5o?") << endl;

	/* Should be modified to
	 * TODO LOCCTR = program start position.
	 * be careful with it, since it will be passed to every
	 * instruction and will be incremented as follows:
	 * LOCCTR += <some instruction>.length();
	 */
	int LOCCTR = 0;

	// Ahmed Salama will fill out the Symbol Table,
	// and will be responsible for START / EQU / END Directives as well.



	return 0;
}

//	Ctrl + B before running !!
