/*
 * ObjectCodeHandler.cpp
 *
 *  Created on: May 27, 2020
 *      Author: Eslam Ahmed
 */
#include "ObjectCodeHandler.h"
#include <string>
#include <fstream>
#include <map>
using namespace std;

    string infile="";
    string textrecord="";
    string address="";
    string objcode="";
    string format="";
    int textlength=0;
    int proglength=0;
	ObjectCodeHandler::ObjectCodeHandler(string _instruction,string _operand,string _label){
            instruct=_instruction;
            operand=_operand;
            label=_label;
	};
   void splitstr(string str) {
   string word = "";
   int m=0;
   for (auto x : str)
   {
       if (x == ' ')
       {
           if(m==0)
                address+=word;
           else
                objcode+=word;

           word = "";
           m++;
       }
       else
       {
           word = word + x;
       }
   }
   format+=word;
   word="";
   m=0;
}



        //instruction(objectcode,address,format)
	void ObjectCodeHandler::record(){
	    int firsttextaddres;
	     string textaddres;
        int textaddressnow=0;


	    //if objectcode is empty
	    if(instruct==""){
                if(textrecord!=""){
                infile="";
                int lasttextaddress = std::stoi(address, 0, 16);
                lasttextaddress-=firsttextaddres;
                char hexString[20];
                itoa(lasttextaddress, hexString, 16);
                infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                ofstream myfile;
                myfile.open ("objcode.txt",ios::app);
                myfile << infile;
                myfile.close();
                infile="";
                textrecord="";
                }

        }
        else{ //in the beginneng of text record
                if(textrecord==""){
                     textaddres=address;
                     firsttextaddres= std::stoi(address, 0, 16);

                     }

        splitstr(instruct);
        map<string, string> update;
        if(update.size()>0){
	    std::map<string, string>::iterator complabel;
        complabel = update.find(label);
            //if we found forward label
        if (complabel != update.end()) {
                int lasttextaddress = std::stoi(address, 0, 16);
                lasttextaddress-=firsttextaddres;
                char hexString[20];
                itoa(lasttextaddress, hexString, 16);
                infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                ofstream myfile;
                myfile.open ("objcode.txt",ios::app);
                myfile << infile;

                infile="";
                infile=infile+"T "+complabel->second+" 02 "+address;
                myfile << infile;
                myfile.close();
                infile="";
                textrecord="";
                                }

            textaddressnow = std::stoi(address, 0, 16);
            //if coloumns >59
        }else if((textaddressnow-firsttextaddres)>59){
                infile="";
                int lasttextaddress = std::stoi(address, 0, 16);
                lasttextaddress-=firsttextaddres;
                char hexString[20];
                itoa(lasttextaddress, hexString, 16);
                infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                ofstream myfile;
                myfile.open ("objcode.txt",ios::app);
                myfile << infile;
                myfile.close();
                infile="";
                textrecord="";
        }
        else{
	    if(format=="4"){
            string check = objcode.substr(objcode.length()-5, objcode.length());
            if(check=="00000"&&operand[0]!='#'){
                update.insert(pair<string, string>(operand,address));
            }
	    }
	    else if(format=="3"){
            string check = objcode.substr(objcode.length()-3, objcode.length());
            if(check=="000"&&operand[0]!='#'){
                update.insert(pair<string, string>(operand,address));
            }
	    }
	    textrecord+=objcode;
        }
            }





	}

