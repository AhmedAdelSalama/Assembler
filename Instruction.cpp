/*
 * Instruction.cpp
 *
 *  Created on: May 27, 2020
 *      Author: Bahaa, Islam Ahmden
 */

#include "Instruction.h"
#include "ObjectTable.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include<sstream>
#include<vector>
#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;
// Have Fun ... ^_^


 Instruction::Instruction(string _label, string _operation, string _operand1,string _operator1,string _operand2,int _LOCCTR,SymbolTable _sym){
   label=_label;
   operation=_operation;
   operand1=_operand1;
   operand2=_operand2;
   operator1=_operator1;

   LOCCTR=_LOCCTR;
   sym=_sym;

}
string Upper(string s);
bool isRegister (string r);
string convertDecimalToBinary(int n,int bits);
bool isNumber(const std::string &s);
// evaluation
int evaluateExp(string p1,string op,string p2,int flag);
void checkAndConvert(string p1,vector<char> &oper,vector<int> &num);
int evl(vector<char> oper,vector<int> num);
int switches(char op,int p1,int p2);
//
int Instruction::getInstructionLength(){
return instructionLenght;
}


string Instruction::perform(){
    ObjectTable ops;
     if(ops.doesItExist(operation)!=0){
            int n=0,i=0,x=0,p=0,b=0,e=0;
            int m = ops.getOpCode(operation);
            int format=ops.getFormat(operation);
            std::stringstream stream;
            stream << std::hex << m;
            std::stringstream HLOCCTR;
            HLOCCTR << std::hex << LOCCTR;


            if(format ==1){
                string ans;
                instructionLenght=1;
                ans=HLOCCTR.str()+" "+stream.str()+" 1";
                return ans;
           }else if(format ==2){
               string ans;
               if(operand1=="")return "ERROR";
                instructionLenght=2;
                bool rtn = isRegister(operand1);
                if(!rtn)return "ERROR";
                 ans=HLOCCTR.str()+" "+stream.str()+to_string(sym.getSymbolValue(operand1));
                if(operand2=="") ans+="0";
                else {
                    rtn = isRegister(operand2);
                    if(!rtn)return "ERROR";
                     ans+=to_string(sym.getSymbolValue(operand2));
                }
                ans+=" 2";
                return ans;
           }else if(format ==3||format ==4){
               int address1,address2;
               bool imediteNumber=false;

                if((operand1[0]== '#' ||operand1[0]== '@')&&(operand2!=""))return "ERROR";
                if(operand1[0]== '#'){
                    i=1;n=0;
                    operand1=operand1.substr(1, operand1.length());
                    if(isNumber(operand1)){
                        address1 = stoi(operand1);
                        if((format==3 && address1>4095)||(format==4 && address1>1048575)){
                                return "ERROR";
                        }
                        if(address1<0)return "ERROR: illegal operand";
                        imediteNumber=true;
                    }else{
                        address1=sym.getSymbolValue(operand1);
                    }
                }else if(operand1[0]== '@'){
                    i=0;n=1;
                    operand1=operand1.substr(1, operand1.length());
                    address1=sym.getSymbolValue(operand1);
                }else{
                    n=1;i=1;
                    address1=sym.getSymbolValue(operand1);
                }

                if(operand2!="" && Upper(operand2)!= "X"){
                        if((operand2[0]== '#' ||operand2[0]== '@'))return "ERROR";
                        if(isNumber(operand1)&&isNumber(operand2)){
                            address1=expression();
                            if(address1=-4)return "Error wrong operand";
                            imediteNumber=true;i=1;
                        }else if(isNumber(operand1)||isNumber(operand2))return "ERROR can't perform this expression";
                        else{
                            address1=expression();
                            if(address1=-4)return "Error wrong operand";
                        }


                }

                string binary_o_c=convertDecimalToBinary(m,8);
                binary_o_c.pop_back();
                binary_o_c.pop_back();
                binary_o_c+=to_string(n)+to_string(i);
                if(Upper(operand2)=="X")binary_o_c+=to_string(1);
                else  binary_o_c+=to_string(0);


                if(format==3){
                    e=0;
                    string ans=HLOCCTR.str()+" ";
                    instructionLenght=3;
                            int disp;
                        if(imediteNumber){
                            disp=address1;p=0;b=0;
                        }else{
                            int pc = LOCCTR + 0x3 ;
                            if(address1==-1){
                                    disp=0;
                                    string key=operand1;
                                    list<int> l;
                                    l.push_back( LOCCTR+1 );
                                    sym.forwardRef.insert( make_pair (key, l));
                            }else{
                                disp = address1 - pc ;
                                if(disp> -0x800 && disp < 0x7FF){p = 1; b = 0;}
                                else{
                                        return "ERROR displacement out of range";

                                }
                           }
                        }
                        binary_o_c+=to_string(b)+to_string(p)+to_string(e);
                        std::stringstream dsp_to_hex;
                        dsp_to_hex << std::hex << disp;
                        string Hdis=dsp_to_hex.str();
                        if(disp<0x0){
                            Hdis=Hdis.substr(Hdis.length()-3, Hdis.length());
                        }
                        else{
                            while(Hdis.size() < 3){
                                 Hdis=to_string(0)+Hdis;
                            }
                        }
                        int dec = std::stoi(binary_o_c, nullptr, 2);
                        std::stringstream to_hex;
                        to_hex << std::hex << dec;
                        Hdis=to_hex.str()+Hdis;
                        ans+=Hdis+" 3";

                        return ans;


                }else{  //format 4
                    e=1;p=0;b=0;
                    string ans=HLOCCTR.str()+" ";
                    instructionLenght=4;

                    if(address1==-1){
                            string key=operand1;
                            list<int> l;
                            l.push_back( LOCCTR+1 );
                            sym.forwardRef.insert( make_pair (key, l));
                            address1=0;
                    }
                    binary_o_c+=to_string(b)+to_string(p)+to_string(e);

                        int dec = std::stoi(binary_o_c, nullptr, 2);
                        std::stringstream part1;
                        part1 << std::hex << dec;
                        std::stringstream part2;
                        part2 << std::hex << address1;
                        string l=part2.str();
                        while(l.size()<5){
                            l=to_string(0)+l;
                        }
                        ans+=part1.str()+l+" 4";

                        return ans;

                }
           }

   }else{
       if(operand1=="")return "Error operand is missing";
       string ans="";
       int result;
    /*   std::map<string, list<int>>::iterator itr;
        itr = sym.forwardRef.find(label);
        if (itr != sym.forwardRef.end()) {

        }*/

       if(operand2!=""){
            result=expression();
            if(result==-4)return "Error wrong operand";
       }
       else{
        if(isNumber(operand1)){
            result=stoi(operand1);
        }else{
             result=sym.getSymbolValue(operand1);

        }
       }
       if(operation=="RESW"){
            // * 3 >> hex
            if(result==-1)return "Error operand isnot exist";
            if(result<0)return "Error operand is wrong";
            instructionLenght=3*result;
            return ans;
       }else if(operation=="RESB"){
           // * 1 >> hex
           if(result==-1)return "Error operand isnot exist";
            if(result<0)return "Error operand is wrong";
            instructionLenght=result;
            return ans;
       }else if(operation=="WORD"){
            // + 3
            // label , rkm
            if(operand2==""){
                if(isNumber(operand1)||sym.getSymbolValue(operand1)!=-1){
                    instructionLenght=3;
                    return ans;
                }else return "Error operand is wrong";
            }else return "Error operand is wrong";
       }else if(operation=="BYTE"){
           // + charcter length
           if(operand2!="")return "Error operand is wrong";
            if(operand1[0]=='X'&&operand1[1]=='\''&&operand1[operand1.length()-1]=='\''){

                instructionLenght=1;
                return ans;
            }else if(operand1[0]=='C'&&operand1[1]=='\''&&operand1[operand1.length()-1]=='\''){
                operand1=operand1.substr(2,operand1.length()-1);
                instructionLenght=operand1.length();
                return ans;
            }else return "Error wrong operand";
       }else{return "ERROR Not Valid Operation";}

   }

}

//to convert a string to upper case
string Upper(string s) {
	// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}
//to check if an operand is a regester
bool isRegister (string r){
    string registers[]={"A","X","L","B", "S", "T", "F", "PC","SW"};
    int size = *(&registers + 1) - registers;
    for(int i=0;i<size;i++){
        if(r==registers[i])return true;
    }
    return false;
}

int Instruction::expression(){
        int address1;int address2;
        string ops="+-*/";
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(operand1.find(ops[i])!= std::string::npos && operand2.find(ops[j])!= std::string::npos){
                    int add=evaluateExp(operand1,operator1,operand2,2);
                    if(add==-1)return -3;
                    else return add;
                }
            }
            }
             for(int i=0;i<4;i++){
                if(operand1.find(ops[i])!= std::string::npos ){
                    int add=evaluateExp(operand1,operator1,operand2,0);
                    if(add==-1)return -3;
                    else return add;
                }else if( operand2.find(ops[i])!= std::string::npos ){
                   int add= evaluateExp(operand1,operator1,operand2,1);
                   if(add==-1)return -3;
                    else return add;

                }
        }

        if(isNumber(operand1)&&isNumber(operand2)){
                address1=stoi(operand1);address2=stoi(operand2);
        }else if(isNumber(operand1)||isNumber(operand2)){
            if(isNumber(operand1)){
                 address1=stoi(operand1);address2=sym.getSymbolValue(operand2);
                 if(address2==-1)return -4;
            }else{
                address1=sym.getSymbolValue(operand1);address2=stoi(operand2);
                if(address1==-1)return -4;
            }

        }
        else{
            address1=sym.getSymbolValue(operand1);
            address2=sym.getSymbolValue(operand2);
            if(address1==-1||address2==-1)return -4;
        }

      int p1=address1;int p2=address2;
      int r;
            switch(operator1[0]){
                case '+': r = p1 + p2; break;
                case '-': r = p1 - p2; break;
                case '*': r = p1 * p2; break;
                case '/': r = p1 / p2; break;
            }
    return r;
}

//to convert decimal to binary string
string convertDecimalToBinary(int n,int bits)
{
    string binaryNumber = "";
    int remainder, i = 0, step = 1;

    while (n!=0 || i<bits)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber = to_string(remainder)+binaryNumber;
        i ++;
    }
    return binaryNumber;
}
int Instruction::evaluateExp(string p1,string op,string p2,int flag){
    if(flag==0){
        vector<int>num;
        vector<char>oper;
        if(p1[0]=='-') return -1;
        checkAndConvert(p1,oper,num);
        int sum=evl(oper,num);
        int address=sym.getSymbolValue(p2);
        int disp = switches(op[0],sum,address);
        return disp;

    }else if(flag==1){
        vector<int>num2;
        vector<char>oper2;
        if(p2[0]=='-') return -1;
        checkAndConvert(p2,oper2,num2);
        int sum=evl(oper2,num2);
        int address=sym.getSymbolValue(p1);
        int disp = switches(op[0],address,sum);
        return disp;

    }else{
        vector<int>num1;
        vector<char>oper1;
        vector<int>num2;
        vector<char>oper2;
       if(p1[0]=='-') return -1;
       if(p2[0]=='-') return -1;
        checkAndConvert(p1,oper1,num1);
        int sum1=evl(oper1,num1);
        checkAndConvert(p2,oper2,num2);
        int sum2=evl(oper2,num2);
        int disp = switches(op[0],sum1,sum2);
        return disp;
    }

}
int switches(char op,int p1,int p2){
    int r;
            switch(op){
                case '+': r = p1 + p2; break;
                case '-': r = p1 - p2; break;
                case '*': r = p1 * p2; break;
                case '/': r = p1 / p2; break;
            }
            return r;
}
int evl(vector<char> oper,vector<int> num){
    int sum=0;
    for(int i=0;i<oper.size();i++){
            if(i==0){
                sum+=switches(oper[i],num[i],num[i+1]);
            }else
       sum=switches(oper[i],sum,num[i+1]);
    }
    return sum;
   // cout<<sum;
}
void checkAndConvert(string p1,vector<char> &oper,vector<int> &num){
        for(int i=0;i<p1.length();i++){
            if(p1[i]=='+' || p1[i]=='-'||p1[i]=='*'||p1[i]=='/'){
                oper.push_back(p1[i]);
            }
        }
        int n = p1.length();
        char char_array[n + 1];
        strcpy(char_array, p1.c_str());
        char *token = strtok(char_array, "[+-*/]");
        while (token != NULL)
        {
            int y = atoi(token);
            num.push_back(y);
            token = strtok(NULL, "[+-*/]");
        }
}
//to check if a string is a number
bool isNumber(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
