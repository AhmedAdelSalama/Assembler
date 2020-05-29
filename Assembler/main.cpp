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
#include <string>
#include "SplitLine.h"
#include "Parser.h"
#include "Registers.h"
#include "ObjectTable.h"
#include "Instruction.h"
#include "InstructionHandler.h"

using namespace std;

int main() {


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
     SymbolTable symTable;
     string line;
     ifstream file("srcfile.txt");
     while(getline(file,line)){
        lineNumber++;
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        line.append("\n");
        SplitLine spl = parseLine(lineNumber,line);
        //string x = spl.label+" " + spl.instruction + " " + spl.operand1+" " + spl._operator+" " + spl.operand2;
        //cout << x <<endl;
       // cout <<lineNumber<<": label: " <<spl.label<<" operation: " <<spl.instruction<<" operand1: " <<spl.operand1<<" operator: " <<spl._operator<<" operand2: " <<spl.operand2 <<endl;
        if(!spl.isComment){
           // Instruction inst(spl.label,spl.instruction,spl.operand1,spl._operator,spl.operand2);
            if(spl.instruction == "START"){
                if(spl.operand1.length()>0){
                    LOCCTR = stoi(spl.operand1);
                }
                if(spl.label.length()>0){
                    symTable.add(spl.label,LOCCTR);
                }
                //eslam
                //GENERATE HEADER RECORD
            }
            else if(spl.instruction.compare("END")==0){
                //eslam
                //GENERATE END RECORD
            }
            else{
                //build SYMTAB
                if(spl.label.length()>0){
                    symTable.add(spl.label,LOCCTR);
                }
                //pass arguments to Bhaa and islam
                //GENERATE TEXT RECORD

                //Ahmed Salama is waiting for Bahaa and islam instruction implementation
                // LOCCTR += inst.getInstructionLength();
            }

        }

     }
     file.close();

	//Example

	//If you found a label, do your magic and insert it into the Symtable
	//Don't forget to consider a place for the registers @see SymbolTable.h

	//Â»œ €—÷Â «· Ê÷ÌÕ Ê „·Ê‘ ⁄·«ﬁ… »«·Ê«ﬁ⁄
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
		//‘Ê› «·Ì Ì—ÌÕﬂ ⁄«Ê“  ﬁ›· «·»—‰«„Ã ›Ì Ê‘Â Œ«·’ „⁄‰œÌ‘ „«‰⁄ ° ⁄«Ê“  ⁄·„ ⁄·Ï «·”ÿÊ— Ê  ⁄—›Â €·ÿ Â ›Ì «·¬Œ— „‘ ÊÕ‘ »—÷Ê
	//}

	//update LOCCTR
	//LOCCTR += inst.getInstructionLength();

	//and loop until END is met.

	return 0;
}

//	Ctrl + B before running !!
