#include "StringToInt.h"
#include <iostream>
using namespace std;

int main(){
    StringToInt si;
    string s;
    cin >> s;
    cout << si.convert(s) << endl;
    return 0;
}