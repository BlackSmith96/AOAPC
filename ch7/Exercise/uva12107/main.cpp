#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char a1[3],b1[3],c1[3],a2[3],b2[3],c2[3],s1;
int a,b,c;

bool in(){
    cin >> a1;
    if(a1[0] == '0') return false;
    cin >> b1 >> c1 >> a2 >> b2 >> c2;
    return true;
}

bool equal(int num1, int num2, char * snum ){
    char str[5];
    sprintf(str,"%d",num1 * num2);
    if(strlen(str) != strlen(snum)) return false;
    for(int i=0;snum[i] != '\0';++i)
        if(snum[i] != str[i] && snum[i] != '*')
            return false;
    return true;
}

//sta = 1代表a,sta = 2代表b，sta = 3代表c
bool iter(char * s,int i, int sta){
    if(sta == 3)
        return equal(a, b, s+i);
    if(s[i] == ' ')
        return iter(s,i+1,sta+1);
    if(s[i] == '*'){
        int ok = 0,k;
        if(i != 0 && s[i-1] != ' ') k = 0;
        for(;k < 10;++k){
            if(sta == 1)
                a = a * 10 + k;
            else
                b = b * 10 + k;
            if(iter(s,i+1,sta)){
                ok = 1;
                break;
            }
        }
        if(ok)  return true;
    }
    else{
        if(sta == 1){
            a = a * 10 + s[i] - '0';
        }
        else{
            b = b * 10 + s[i] - '0';
        }
        return iter(s,i+1,sta);
    }
}

int main() {
    while(in()){
        //Your code
        cout << a1 << b1 << endl;
    }
    return 0;
}