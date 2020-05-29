/*
 * ObjectCodeHandler.h
 *
 *  Created on: May 27, 2020
 *      Author: Eslam Ahmed
 */

#include <string>
#include <fstream>
#include <map>
 using namespace std;

#ifndef OBJECTCODEHANDLER_H_
#define OBJECTCODEHANDLER_H_

//Didn't provide any further details in order to give you the freedom to chose anyway you like to achieve the result
//Since no one else is depending on your part. (بلاش هبد عنيف ^_^)

class ObjectCodeHandler {
public:
    string instruct;
    string operand;
    string label;
	ObjectCodeHandler(string _instruction,string _operand,string _label);

	void record();


};

#endif /* OBJECTCODEHANDLER_H_ */
