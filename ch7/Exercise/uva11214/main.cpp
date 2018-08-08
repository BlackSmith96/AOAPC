#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, kase = 0;
int vis[4][30];     //行、列，主对角线、副对角线
int map[10][10];

bool in(){
    cin >> n;
    if(n == 0) return false;
    cin >> m;
    char ch;
    memset(map,0, sizeof(map));
    for(int i=0;i < n;++i)
        for(int j=0;j < m;++j){
            cin >> ch;
            if(ch == 'X')
                map[i][j] = 1;
        }
    return true;
}

bool judge(){
    for(int i=0;i < n;++i){
        for(int j=0;j < m;++j){
            if(map[i][j] == 1 && !vis[0][i] && !vis[1][j] && !vis[2][i+j] && !vis[3][n+j-i]){
                return false;
            }
        }
    }
    return true;
}

bool DFS(int d, int cur, int maxd){
    if(d == maxd){
        return judge();
    }
    int ok = 0;
    for(;cur < n *m;++cur){
        int r = cur / m, c = cur % m;
        int ta = vis[0][r], tb = vis[1][c], tc = vis[2][r+c], td = vis[3][n+c-r];
        vis[0][r] = 1; vis[1][c] = 1; vis[2][r+c] = 1; vis[3][n+c-r] = 1;
        if(DFS(d+1,cur,maxd)){ok = 1;break;}
        vis[0][r] = ta; vis[1][c] = tb; vis[2][r+c] = tc; vis[3][n+c-r] = td;
    }
    return ok;
}

int main() {
    while(in()){
        for(int maxd=0;;++maxd){
            memset(vis,0,sizeof(vis));
            if(DFS(0,0,maxd)){
                printf("Case %d: %d\n",++kase,maxd);
                break;
            }
        }
    }
    return 0;
}