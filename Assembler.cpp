//============================================================================
// Name        : Assembler.cpp
// Author      : https://youtu.be/AhCLgRVcKMg
// Version     : 0.0v
// Copyright   : Your copyright notice
// Description : Hello World
//============================================================================

#include <iostream>
#include <regex>
#include <fstream>
#include <algorithm>
#include "SplitLine.h"
#include "Parser.h"
#include "Registers.h"
#include "ObjectTable.h"
#include "Instruction.h"
#include "InstructionHandler.h"

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


	// Ahmed Salama will fill out the Symbol Table,
	// and will be responsible for:
	// -> START (Store the program name and Initial LOCCTR)
	// -> EQU (Just treat it like any other entity in the symbol table) Directive as well. (END is just a flag)

	//---------------------------------------------------------------- *

	//SymbolTable SymTable;
	//InstructionHandler assembler;

	//General Algorithm

	/**
	 * read a line
	 * Identify it using regex
	 * detect labels, store its address or put a * if not defined yet
	 * pass the instruction to the Instruction Handler
	 * repeat
	 */
     int LOCCTR = 0 , lineNumber=0;
     string line;
     ifstream file("srcfile.txt");
     while(getline(file,line)){
        lineNumber++;
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        line.append("\n");
        SplitLine spl = parseLine(lineNumber,line);
       // string x = spl.label+" " + spl.instruction + " " + spl.operand1+" " + spl._operator+" " + spl.operand2;
        if(!spl.isComment){
            Instruction inst(spl.label,spl.instruction,spl.operand1,spl._operator,spl.operand2);
            if(spl.instruction.compare("START")){
                //GENERATE HEADER RECORD
            }else if(spl.instruction.compare("END")){
                //GENERATE END RECORD
            }else{
                //build SYMTAB
                //GET DISPLACEMENT
                //GENERATE TEXT RECORD
            }
            LOCCTR += inst.getInstructionLength();
        }

     }
     file.close();

	//Example

	//If you found a label, do your magic and insert it into the Symtable
	//Don't forget to consider a place for the registers @see SymbolTable.h

	//هبد غرضه التوضيح و ملوش علاقة بالواقع
	//string line[3] = filterLine(readLine());

	//dummy variables
	//string label;		//line[0]
	//string operation;	//line[1]
	//string operands;	//line[2]
	//Expression exp(operands, SymTable);

	//real code
	//Instruction inst(label, operation, exp, LOCCTR);
	//bool isValid = assembler.handle(inst);

	//if(isValid){
		//continue
	//}
	//else{
		//شوف الي يريحك عاوز تقفل البرنامج في وشه خالص معنديش مانع ، عاوز تعلم على السطور و تعرفه غلطته في الآخر مش وحش برضو
	//}

	//update LOCCTR
	//LOCCTR += inst.getInstructionLength();

	//and loop until END is met.

	return 0;
}

//	Ctrl + B before running !!
