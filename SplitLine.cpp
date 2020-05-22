#include <iostream>
#include <regex>
#include "SplitLine.h"

using namespace std;

SplitLine::SplitLine(bool isComment, string label, string opCode, string operand1, string _operator, string operand2)
{
            this->isComment = isComment;
            this->label = label;
            this->opCode = opCode;
            this->operand1 = operand1;
            this->_operator = _operator;
            this->operand2 = operand2;
}
