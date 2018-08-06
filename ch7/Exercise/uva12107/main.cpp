#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char a1[3],b1[3],c1[3],a2[3],b2[3],c2[3];

bool in(){
    cin >> a1;
    if(a1[0] == '0') return false;
    cin >> b1 >> c1 >> a2 >> b2 >> c2;
    return true;
}

int main() {
    while(in()){
        //Your code
        cout << a1 << b1 << endl;
    }
    return 0;
}