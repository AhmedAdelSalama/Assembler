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
#include <iostream>
using namespace std;

    string infile;
    string textrecord;
    string address;
    string objcode;
    string format;
    string textaddres;
    string header;
    string firstadd;

    string update[2][100];
    int begining=0;
    int i=0;
    int textlength=0;
    int proglength=0;

	ObjectCodeHandler::ObjectCodeHandler(string _instruction,string _operand,string _label,string _loctr){
            instruct=_instruction;
            operand=_operand;
            label=_label;
            loctr=_loctr;
	};
   void splitstr(string str) {
   string word = "";
   int m=0;
   for (auto x : str)
   {
       if (x == ' ')
       {
           if(m==0)
                address=word;
           else
                objcode=word;

           word = "";
           m++;
       }
       else
       {
           word = word + x;
       }
   }
   format=word;
   word="";
   m=0;
}
string searcharray(string label){
        for(int y=0;y<=i;y++){
                if (update[0][y]==label){
                    return update[1][y];
                }
        }

return "no";
}

void endob(){

fstream myfile("objcod.txt",ios::in | ios::out | ios::app);

                    myfile<<"E 1000"<<endl;

}



    	void ObjectCodeHandler::record(){

    	int firsttextaddres;
        int lasttextaddress;

       // in the begining of progrm

        if(begining==0){
                      header="";
                     textaddres=operand;
                     firstadd=operand;
                     firsttextaddres= std::stoi(textaddres, 0, 16);
                     begining++;
                     header=header+"H "+label+" "+operand+"            ";
                    fstream myfile("objcod.txt",ios::in | ios::out | ios::trunc);
                    myfile<<header<<endl;
                     return;

                     }


          if(instruct=="END"){

                        lasttextaddress = std::stoi(address, 0, 16);
                        firsttextaddres=std::stoi(firstadd, 0, 16);
                        lasttextaddress-=firsttextaddres;
                        char hexString[20];
                        itoa(lasttextaddress, hexString, 16);
                        fstream file("objcod.txt", std::ios::in | std::ios::out);
                        file.seekp(14);
                        file <<hexString ;
                        endob();
          }

            //if objectcode is empty create new text

        if(instruct=="" && textrecord!="" ){
                infile="";
                firsttextaddres=std::stoi(textaddres, 0, 16);
                 lasttextaddress = std::stoi(address, 0, 16);
                lasttextaddress-=firsttextaddres;
                char hexString[20];
                itoa(lasttextaddress, hexString, 16);
                infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                fstream myfile("objcod.txt",ios::in | ios::out | ios::app);
                myfile<<infile<<endl;
                infile="";
                textrecord="";
                textaddres="";

                }


            //if we found forward label
            if(i>0 && searcharray(label)!="no" && label != "" ){
                //if there is no objcode
            if(instruct == "" && textrecord==""){

                infile=infile+"T "+searcharray(label)+" 02 "+loctr;
                fstream myfile("objcod.txt",ios::in | ios::out | ios::app);
                myfile<<infile<<endl;
                infile="";
            }

                //if there is  objcode
                else if(instruct != "") {
                splitstr(instruct);
                infile="";
                lasttextaddress = std::stoi(address, 0, 16);
                firsttextaddres=std::stoi(textaddres, 0, 16);
                lasttextaddress-=firsttextaddres;
                char hexString[20];
                itoa(lasttextaddress, hexString, 16);
                infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                fstream myfile("objcod.txt",ios::in | ios::out | ios::app);
                myfile<<infile<<endl;
                infile="";
                textrecord="";
                textaddres="";
                //the new print

                infile=infile+"T "+searcharray(label)+" 02 "+address;
               // fstream myfile("objcod.txt",ios::in | ios::out | ios::app);
                myfile<<infile<<endl;
                infile="";
                textaddres=address;
                firsttextaddres= std::stoi(textaddres, 0, 16);
        }


            }


            if(textrecord.length()>59){
                    if(instruct!="")
                        splitstr(instruct);
                    else
                        address=loctr;
                    infile="";
                    if(address.length()>0)
                    lasttextaddress = std::stoi(address, 0, 16);
                    firsttextaddres=std::stoi(textaddres, 0, 16);
                    lasttextaddress-=firsttextaddres;
                    char hexString[20];
                    itoa(lasttextaddress, hexString, 16);
                    infile=infile+"T "+textaddres+" "+hexString+" "+textrecord;
                    fstream myfile("objcod.txt",ios::in | ios::out | ios::app);
                    myfile<<infile<<endl;
                    infile="";
                    textrecord="";
                    textaddres="";
        }
        if(instruct!=""){
        splitstr(instruct);
        if(textaddres==""){
            textaddres=address;
        }
	    if(format=="4"){
            string check = objcode.substr(objcode.length()-5, objcode.length());
            if(check=="00000"&&operand[0]!='#'){
                update[0][i]=operand;
                update[1][i]=address;
                        i++;
            }
	    }
	    else if(format=="3"){
            string check = objcode.substr(objcode.length()-3, objcode.length());
            if(check=="000"&&operand[0]!='#'){
                update[0][i]=operand;
                update[1][i]=address;
                 i++;            }
	    }

	    textrecord=textrecord+" "+objcode;
        }

    	}

















