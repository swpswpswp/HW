#include "StringToInt.h"
#include <string>
#include <iostream>
using namespace std;

int StringToInt::convert(const string& s) const{
    try{
        if(s.empty()){
            throw 0;
        }
        for(int i = 0; i < s.length(); i++){
            if(i == 0 && s[i] == '-'){
                continue;
            }
            if(i == 0 && s[i] == '+'){
                continue;
            }
            if((s[i] < '0' || s[i] > '9') && s[i] != '.'){
                throw 1;
            }
            if(s[i] == '.' && i != s.length() - 1){
                throw 4;
            }
        }
        if((s[0] == '-' || s[0] == '+') && s.length() == 1){
            throw 3;
        }
        int result = 0;
        if(s[0] == '-'){
            return -convert(s.substr(1, s.length() - 1));
        }
        if(s[0] == '+'){
            return convert(s.substr(1, s.length() - 1));
        }
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '.'){
                continue;
            }
            result = result * 10 + (s[i] - '0');
            if(result < 0){
                throw 2;
            }
        }
        return result;
    }catch(int e){
        if(e == 0){
            cerr << "String is empty" << endl;
        }
        if(e == 1){
            cerr << "String contains non-digit characters" << endl;
        }
        if(e == 2){
            cerr << "Integer overflow" << endl;
        }
        if(e == 3){
            cerr << "String has only one sign" << endl;
        }
        if(e == 4){
            cerr << "String has a dot in the middle" << endl;
        }
    }
}