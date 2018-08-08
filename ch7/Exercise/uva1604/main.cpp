#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef int State[9];
const int maxstate = 100000;
int empty_x,empty_y;
State st[maxstate];
int dis[maxstate];
int goal[9]; //-1->E 0 -> W 1->R 2-> B

//定义状态
//状态1   W R B  上下 前后 左右
//   2   W B R
//   3   R B W
//   4   R W B
//   5   B W R
//   6   B R W
const int left[7] = {0,6,3,2,5,1};
const int right[7] = {0,6,3,2,5,1};
const int forward[7] = {0,4,5,6,1,2,3};
const int back[7] = {0,4,5,6,1,2,3};
const int next[4][7] = {{0,6,3,2,5,1},{0,6,3,2,5,1},{0,4,5,6,1,2,3},{0,4,5,6,1,2,3}};
const int dr[4] = {0,0,-1,1};
const int dc[4] = {-1,1,0,0};

bool in(){
    cin >> empty_x >> empty_y;
    if(empty_x == 0 && empty_y == 0) return false;
    char ch;
    for(int i=0;i < 9;++i){
        cin >> ch;
        if(ch == 'E')
            goal[i] = -1;
        else if(ch == 'W')
            goal[i] = 0;
        else if(ch == 'R')
            goal[i] = 1;
        else
            goal[i] = 2;
    }
    //init
    for(int i=0;i < 9;++i)
        st[0][i] = 1;
    st[0][3*empty_y+empty_x-4] = 0;
    dis[0] = 0;
    return true;
}

void init_search_table();
bool try_to_inseart(State t);

bool judge(State s){
    for(int i=0;i < 9;++i){
        if(goal[i] == 0 && s[i] != 0){return false;}
        else if(goal[i] != (s[i] + 1) / 2 ) return false;
    }
    return true;
}

int bfs(){
    init_search_table();
    int front = 0,rear = 1;
    for(;front  < rear;front++){
        if(judge(st[front])) return 1;
        // search empty block
        int i, r, c, nr, nc;
        for(i=0;i < 9;++i){if(st[front][i] == 0) break;}
        r = i / 3;  c = i % 3;
        for(i=0;i < 4;++i){
            nr = r + dr[i];
            nc = c + dc[i];
            if(nr < 0 || nr > 3 || nc < 0 || nc > 3) continue;
            State t;
            memcpy(t,st[front], sizeof(State));
            t[3*r+c] = 0;
            t[3*nr+nc] = next[i][t[3*nr+nc]];
            if(try_to_inseart(t)) ++rear;
        }
    }
    return 0;
}

int main() {
    while(in()){
        int ans = bfs();
        if(ans >= 0)
            printf("%d\n",ans);
        else
            printf("-1");
    }
    return 0;
}