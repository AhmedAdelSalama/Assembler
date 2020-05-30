#include <iostream>
#include <regex>
#include <fstream>
#include "SplitLine.h"

using namespace std;
//A function to extract label, instruction , operands and operator without any additional characters "except the ones
//indicating different addressing modes".
//the boolean parameter to know the operator + from the external format +
int extract(string splitLine, string &word , bool isOperator){
    int i =0;
    stringstream str;
    while(splitLine[i]!='\n'&&splitLine[i]!='.'){
        //if statement made for the _operator which takes only one character of : + - * / ,
        // to ensure that it's nothing to do with different addressing modes
        if(splitLine[i]==','||splitLine[i]=='-'||splitLine[i]=='+'||splitLine[i]=='*'||splitLine[i]=='/'){
            //current pc value
            if(!isOperator&&word.length()==0&&splitLine[i]=='*'){
                word+=splitLine[i];
                i++;
                break;
            }
            //end of operand
            if(!isOperator&&word.length()>0){
                break;
            }
            word+=splitLine[i];
            if(isOperator){
                i++;
                break;
            }
        }
        else if(splitLine[i]==' '||splitLine[i]=='\t'){
            if(word.size()!=0){
                break;
            }
        }
        //if the operand between ()
        else if(splitLine[i]=='('){
            if(word.size()!=0){
                    break;
            }
            else{
                i++;
                while(splitLine[i]!=')'){
                    if(splitLine[i]=='\n'||splitLine[i]=='\.'){
                        throw "ERORR! \")\" is missing!";
                    }
                    word+=splitLine[i];
                    i++;
                }
                i++;
                break;
            }
        }
        else{
            word+=splitLine[i];
        }
        i++;
    }
    return i;
}
//A parser function to validate each line and
//extract label, instruction and operands.
//This function validates the line only. To validate the operands corresponding to each instruction,
//instruction must be checked first in OPTAB then the operands according to their instruction.
SplitLine parseLine(int lineNumber, string line){
    try{
        regex comment ("[\\s|\\t]*\\..*\n");
        regex lineWithNoOperand_labelled ("[\\s|\\t]*[\\w]+[\\s|\\t]+[+]?[a-zA-z]{1,6}[\\s|\\t]*");
        regex lineWithNoOperand_unlabelled ("[\\s|\\t]*[+]?[a-zA-z]{1,6}[\\s|\\t]*");
        regex lineWithOneOperand_labelled ("[\\s|\\t]*[\\w]+[\\s|\\t]+[+]?[a-zA-z]{1,6}[\\s|\\t]+[@|#]?[\\*\\w]+?[\\s|\\t]*");
        regex lineWithOneOperand_unlabelled ("[\\s|\\t]*[+]?[a-zA-z]{1,6}[\\s|\\t]+[@|#]?[\\*\\w]*[\\s|\\t]*");
        regex lineWithTwoOperands_labelled ("[\\s|\\t]*[\\w]+[\\s|\\t]+[+]?[a-zA-z]{1,6}[\\s|\\t]+[@|#]?[\\*\\w]+[\\s|\\t]*[,-/*+]+[\\s|\\t]*[@|#]?[\\*\\w]+[\\s|\\t]*");
        regex lineWithTwoOperands_unlabelled ("[\\s|\\t]*[+]?[a-zA-z]{1,6}[\\s|\\t]+[@|#]?[\\*\\w]+[\\s|\\t]*[,-/*+]+[\\s|\\t]*[@|#]?[\\*\\w]+[\\s|\\t]*");
        //regex for BYTE - WORD
        regex storageDirectiveBYTE ("[\\s|\\t]*[\\w]*[\\s|\\t]+BYTE[\\s|\\t]+[X|C]'[\\w]+'[\\s|\\t]*");
        //\\d or \\w or both?
        regex storageDirectiveWORD ("[\\s|\\t]*[\\w]*[\\s|\\t]+WORD[\\s|\\t]+[-]*[\\d]+[\\s|\\t]*");
        regex storageDirectiveRES ("[\\s|\\t]*[\\w]*[\\s|\\t]+RES[W|B]{1}[\\s|\\t]+[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*[-/*+]*[\\s|\\t]*[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*");
        regex lineWithEQU2operands_labelled ("[\\s|\\t]*[\\w]*[\\s|\\t]+EQU[\\s|\\t]+[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*[-/*+]*[\\s|\\t]*[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*");
        regex lineWithEQU2operands_unlabelled ("[\\s|\\t]*EQU[\\s|\\t]+[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*[-/*+]*[\\s|\\t]*[(]?[-/*+\\d\\w]*[)]?[\\s|\\t]*");
        /*
        NOTES:lineWithNoOperand_labelled deals with storage directives but you still need to validate the operators
                according to the OPTAB "operation table".
        */
        string  label,instruction,operand1 ,_operator, operand2;
        if(regex_match(line,comment)){
            return SplitLine(true ,label,instruction,operand1 , _operator , operand2);
        }
        int i=0;
        if(regex_match(line , storageDirectiveBYTE)){
            i = extract(line , label , false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line , storageDirectiveWORD)){
            i = extract(line , label , false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line , lineWithNoOperand_unlabelled)){
            i =extract(line,instruction , false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithOneOperand_unlabelled)){
            i = extract(line,instruction, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithTwoOperands_unlabelled)){
            i = extract(line,instruction, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }

        if(regex_match(line , lineWithNoOperand_labelled)){
            i =extract(line,label , false);
            i+= extract(line.substr(i),instruction, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithTwoOperands_labelled)){
            i = extract(line , label, false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithOneOperand_labelled)){
            i = extract(line , label , false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }

        if(regex_match(line,storageDirectiveRES)){
            i = extract(line , label, false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithEQU2operands_unlabelled)){
            i = extract(line , instruction, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        if(regex_match(line,lineWithEQU2operands_labelled)){
            i = extract(line , label, false);
            i+= extract(line.substr(i),instruction, false);
            i+= extract(line.substr(i),operand1, false);
            i+= extract(line.substr(i),_operator, true);
            i+= extract(line.substr(i),operand2, false);
            return SplitLine(false ,label,instruction,operand1 ,_operator, operand2);
        }
        ofstream outfile;
        outfile.open("report.txt",ios::app);
        outfile <<"line "<<lineNumber<<":" << "Syntax Error!" << endl;
        outfile.close();
    }catch(regex_error& e){
        cerr << "Error! parsing a line went wrong.." << endl;
    }
    return SplitLine(true ,"","","","","");
}
