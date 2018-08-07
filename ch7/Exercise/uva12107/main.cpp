#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const char chs[11] = {'*','0','1','2','3','4','5','6','7','8','9'};
char expression[15];
int maxd,l,cnt,kase = 0;

bool in(){
    gets(expression);
    if(expression[0] == '0') {return false;}
    return true;
}

bool smaller(char a , char b){
    if(a == '*') return true;
    if(b == '*') return false;
    return (b-a);
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
void iter(char * s,int i, int sta, int n1, int n2){
    if(cnt >= 2)
        return ;
    if(sta == 3){
        if(equal(n1, n2, s+i))
            ++cnt;
        return;
    }
    if(s[i] == ' ')
        return iter(s,i+1,sta+1,n1,n2);
    if(s[i] == '*'){
        int k,a,b;
        if(i != 0 && s[i-1] != ' ') k = 0;
        else k = 1;
        for(;k < 10 && cnt < 2;++k){
            a = n1; b= n2;
            if(sta == 1)
                a = a * 10 + k;
            else
                b = b * 10 + k;
            iter(s,i+1,sta,a,b);
        }
    }
    else{
        if(sta == 1){
            n1 = n1 * 10 + s[i] - '0';
        }
        else{
            n2 = n2 * 10 + s[i] - '0';
        }
        iter(s,i+1,sta,n1,n2);
    }
}

bool changedigit(char exp[15], int i, int nums){
    if(nums == 0){
        cnt = 0;
        iter(exp,0,1,0,0);
        if(cnt != 1)
            return false;
        else{
            printf("Case %d: %s\n",++kase,exp);
            return true;
        }
    }
    if((l-i) < nums) return false;
    if(exp[i] == ' ') return changedigit(exp,i+1,nums);
    int ok = 0;
    char s[15];
    int j;
    for(j = 0;j < 11 && smaller(chs[j],exp[i]);++j){
        if(i > 0 && chs[j] == '0' && exp[i-1] == ' ') continue;
        strcpy(s,exp);
        if(chs[j] == exp[i]) continue;
        s[i] = chs[j];
        if(changedigit(s,i+1,nums-1)){
            return true;
        }
    }
    if(changedigit(exp,i+1,nums))
        return true;
    for(;j < 11;++j){
        if(chs[j] == exp[i]) continue;
        strcpy(s,exp);
        s[i] = chs[j];
        if(changedigit(s,i+1,nums-1))
            return true;
    }
    return false;
}

int main() {
    while(in()){
        //Your code
        l = strlen(expression);
        int ok = 0;
        for(maxd=0;;++maxd){
            if(changedigit(expression,0,maxd))
                break;
        }
    }
    return 0;
}