#include <iostream>
#include <regex>
#include "SplitLine.h"

using namespace std;

//A function to extract label, opcode , operands and operator without any additional characters "except the ones
//indicating different addressing modes".
//the boolean parameter to know the operator + from the external format +
int extract(string splitLine, string &word , bool isOperator){
    int i =0;
    stringstream str;
    while(splitLine[i]!='\n'){
        //if statement made for the _operator which takes only one character of : + - * / ,
        // to ensure that it's nothing to do with different addressing modes
        if(splitLine[i]==','||splitLine[i]=='-'||splitLine[i]=='+'||splitLine[i]=='*'||splitLine[i]=='/'){
            if(isOperator){
                word+=splitLine[i];
                i++;
            }
            break;
        }
        if(splitLine[i]==' '||splitLine[i]=='\t'){
            if(word.size()!=0){
                break;
            }
        }else{
            word+=splitLine[i];
        }
        i++;
    }
    return i;
}
//A parser function to validate each line and
//extract label, opcode and operands.
//This function validates the line only. To validate the operands corresponding to each opcode,
//opcode must be checked first in OPTAB then the operands according to their opcode.
SplitLine parseLine(string line){
    try{
        regex comment ("[\\s|\\t]*\\..*");
        regex lineWithNoOperand_labelled ("[\\s|\\t]*[\\w]{1,6}[\\s|\\t]+[+]*[a-zA-z]{1,6}[\\s|\\t]*");
        regex lineWithNoOperand_unlabelled ("[\\s|\\t]*[+]*[a-zA-z]{1,6}[\\s|\\t]*");
        regex lineWithOneOperand_labelled ("[\\s|\\t]*[\\w]{1,6}[\\s|\\t]+[+]*[a-zA-z]{1,6}[\\s|\\t]+[@|#|X'|C']*[\\w]{1,6}[']*[\\s|\\t]*");
        regex lineWithOneOperand_unlabelled ("[\\s|\\t]*[+]*[a-zA-z]{1,6}[\\s|\\t]+[@|#|X'|C']*[\\w]{1,6}[']*[\\s|\\t]*");
        regex lineWithTwoOperands_labelled ("[\\s|\\t]*[\\w]{1,6}[\\s|\\t]+[+]*[a-zA-z]{1,6}[\\s|\\t]+[@|#]*[\\w]{1,6}[\\s|\\t]*[,-/*+]?[\\s|\\t]*[@|#]*[\\w]{1,6}[\\s|\\t]*");
        regex lineWithTwoOperands_unlabelled ("[\\s|\\t]*[+]*[a-zA-z]{1,6}[\\s|\\t]+[@|#]*[\\w]{1,6}[\\s|\\t]*[,-/*+]?[\\s|\\t]*[@|#]*[\\w]{1,6}[\\s|\\t]*");
        /*
        NOTES:lineWithNoOperand_labelled deals with storage directives but you still need to validate the operators
                according to the OPTAB "operation table".
        */
        string  label,opCode,operand1 ,_operator, operand2;
        if(regex_match(line,comment)){
            return SplitLine(true ,label,opCode,operand1 , _operator , operand2);
        }
        int i=0;
        if(regex_match(line , lineWithNoOperand_labelled)){
            i =extract(line,label , false);
            i+= extract(line.substr(i),opCode, false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        if(regex_match(line , lineWithNoOperand_unlabelled)){
            i =extract(line,opCode , false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithOneOperand_labelled)){
            i = extract(line , label , false);
            i+= extract(line.substr(i),opCode, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithOneOperand_unlabelled)){
            i = extract(line,opCode, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithTwoOperands_labelled)){
            i = extract(line , label, false);
            i+= extract(line.substr(i),opCode, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithTwoOperands_unlabelled)){
            i = extract(line,opCode, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,opCode,operand1 ,_operator, operand2);
        }
        cerr << "Syntax Error.." << endl;
    }catch(regex_error& e){
        cerr << "Error! parsing a line went wrong.." << endl;
    }
    return SplitLine(true ,"","","","","");
}

int main()
{
    SplitLine spl = parseLine("EOF BYTE C'EOF'\n");
    string x = spl.label+" " + spl.opCode + " " + spl.operand1+" " + spl._operator+" " + spl.operand2;
    cout << x << endl;
    return 0;
}
