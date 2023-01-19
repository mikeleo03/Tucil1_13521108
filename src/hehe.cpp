#include <iostream>
#include "solver.hpp"
#include <cstdlib>
#include <time.h>
using namespace std;

int main() {
    int i=11;  
    float f=12.3;  
    string str= to_string(i);  
    string result = "((" + str + "+" + str + ")" + "*" + str + ")";
    cout<<"string value of integer i is :"<< str <<"\n";
    cout << result;
}