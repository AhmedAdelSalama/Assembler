#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <iostream>
#include <regex>
using namespace std;
//A function to extract label, instruction , operands and operator without any additional characters "except the ones
//indicating different addressing modes".
//the boolean parameter to know the operator + from the external format +
int extract(string splitLine, string &word , bool isOperator);
//A parser function to validate each line and
//extract label, instruction and operands.
//This function validates the line only. To validate the operands corresponding to each instruction,
//instruction must be checked first in OPTAB then the operands according to their instruction.

SplitLine parseLine(string line);

#endif // PARSER_H_INCLUDED
