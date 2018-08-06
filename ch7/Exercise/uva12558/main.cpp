#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 10000;

set<long long> s;
int d;
long long ans[maxn], v[maxn];

long long gcd(long long a, long long b){
    return b?gcd(b,a%b):a;
}

bool better(int cd){
    for(int i=0;i < cd;++i)
        return
}

bool dfs(int depth,int begin,long long a,long long b){
    if(depth == maxn){
        if(b * begin == a && ){
        }
    }
}

int main() {
    int kase, times = 0;
    cin >> kase;
    while(kase--){
        long long a,b,t;
        int k;

        cin >> a >> b >> k;
        while(k--) {cin >> t; s.insert(t);}
        for(d = 0;;++d){
            memset(ans,-1, sizeof(ans));
            if(dfs(0,b/a+1,a,b)) break;
        }
        printf("Case %d: %lld/%lld=",++times,a,b);
        for(int i=0;i<=d;++i){
            if(i) printf("+");
            printf("1/%lld",ans[i]);
        }
        printf("\n");
    }
    return 0;
}