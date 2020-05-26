//============================================================================
// Name        : Assembler.cpp
// Author      : https://youtu.be/AhCLgRVcKMg
// Version     : 0.0v
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ObjectTable.h"
using namespace std;

int main() {
	ObjectTable opTable;

	cout << opTable.doesItExist("ADD") << endl;
	cout << opTable.doesItExist("aDd") << endl;
	cout << opTable.doesItExist("He5o?") << endl;

	cout << opTable.getOpCode("ADD") << endl;
	cout << opTable.getOpCode("aDd") << endl;
	cout << opTable.getOpCode("He5o?") << endl;

	cout << opTable.getFormat("ADD") << endl;
	cout << opTable.getFormat("aDd") << endl;
	cout << opTable.getFormat("He5o?") << endl;

	return 0;
}

//	Ctrl + B before running !!
