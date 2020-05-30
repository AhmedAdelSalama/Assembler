#ifndef SPLITLINE_H
#define SPLITLINE_H
#include <iostream>
#include <regex>
using namespace std;

// A class to get information needed from each validated line.
// It consists of  label, instruction, operand/s and operator if exists.
//=================================================================================================================================

class SplitLine
{
    public:
        string      label,
                   instruction,
                 operand1,
                _operator,
                 operand2;
        bool    isComment;

        SplitLine(bool isComment, string label, string instruction, string operand1, string _operator, string operand2);
};

#endif // SPLITLINE_H
