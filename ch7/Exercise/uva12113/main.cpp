/*
 * 参考了网络上的解法：
 * 因为只是4*4的方格，所以用暴力枚举的办法，一共有C96种情况，所以枚举即可
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int vis[9]; //一共9个位子可以选
char mp[5][15], begin_map[5][15];

bool judge(char temp[5][15]){
    for(int i=0;i < 5;++i)
        for(int j=0;j < 9;++j)
            if(mp[i][j] != temp[i][j])
                return false;
    return true;
}

void debug(char t[9][15]){
    printf("********\n");
    for(int i=0;i < 5;++i){
        for(int j=0;j < 9;++j)
            printf("%c",t[i][j]);
        printf("\n");
    }
    printf("********\n");
}

bool in(){
    for(int i=0;i < 5;++i){
        gets(mp[i]);
        if(mp[i][0] == '0')
            return false;
    }
    return true;
}

bool iter(int step,char m[5][15]){
    if(judge(m))
        return true;
    if(step >= 6)
        return false;

    int x,y;
    for(int se = 0;se < 9;++se){
        if(vis[se])
            continue;

        x = se % 3;
        y = se / 3 + 1;

        char t[5][15];
        for(int i=0;i < 5;++i)
            for(int j=0;j < 9;++j)
                t[i][j] = m[i][j];

        vis[se] = 1;
        t[y-1][2 * x + 1] = t[y-1][2 * x + 3] = t[y+1][2 * x + 1] = t[y+1][2 * x + 3] = '_';
        t[y+1][2 * x] = t[y][2 * x] = t[y][2 * x + 4] = t[y+1][2 * x + 4] = '|';
        t[y][2 * x + 1] = t[y][2 * x + 2] = t[y][2 * x + 3] = t[y+1][2 * x + 2] = ' ';
        //if(step == 3 && vis[0] == 1 && vis)
        //    debug(t);

        if(iter(step+1,t))
            return true;
        vis[se] = 0;

    }
    return false;
}

void init(){
    for(int i=0;i < 5;++i)
        for(int j=0;j < 9;++j)
            begin_map[i][j] = ' ';
    memset(vis,0, sizeof(vis));
}

int main() {
    int kase = 0;
    bool ans;
    while(true){
        if(!in())
            break;
        init();
        ans = iter(0, begin_map);
        printf("Case %d: ",++kase);
        if(ans)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}