#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef int State[9];
const int maxstate = 100000;
const int hashsize = 1000003;
int myhead[hashsize], mynext[hashsize];
int empty_x,empty_y;
State st[maxstate];
int dist[maxstate];
int goal[9]; //-1->E 0 -> W 1->R 2-> B

//定义状态
//状态1   W R B  上下 前后 左右
//   2   W B R
//   3   R B W
//   4   R W B
//   5   B W R
//   6   B R W
const int left[7] = {0,6,3,2,5,1};  //往左滚
const int right[7] = {0,6,3,2,5,1};
const int forward[7] = {0,4,5,6,1,2,3};
const int back[7] = {0,4,5,6,1,2,3};
const int next_state[4][7] = {{0,6,3,2,5,1},{0,6,3,2,5,1},{0,4,5,6,1,2,3},{0,4,5,6,1,2,3}};
const int dr[4] = {0,0,1,-1};
const int dc[4] = {1,-1,0,0};

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
        st[1][i] = 1;
    st[1][3*empty_y+empty_x-4] = 0;
    dist[1] = 0;
    return true;
}

int myhash(State & s){
    int v = 0;
    for(int i=0;i < 9;++i) v = v * 10 + s[i];
    return v % hashsize;
}

void init_search_table(){
    memset(myhead, 0, sizeof(myhead));
}

bool try_to_inseart(int s){
    int h = myhash(st[s]);
    int u = myhead[h];
    while(u){
        if(memcmp(st[u],st[s], sizeof(st[s])) == 0) return 0;
        u = mynext[u];
    }
    mynext[s] = myhead[h];
    myhead[h] = s;
    return 1;
}

bool judge(State s){
    for(int i=0;i < 9;++i){
        if(goal[i] == 0 && s[i] != 0){return false;}
        else if(goal[i] != (s[i] + 1) / 2 ) return false;
    }
    return true;
}

void debug(State s);
int bfs(){
    init_search_table();
    int front = 1,rear = 2;
    for(;front  < rear;front++){
        State& s = st[front];
        if(judge(s)) return front;
        // search empty block
        int z, r, c, nr, nc,nz;
        for(z=0;z < 9;++z){if(s[z] == 0) break;}
        r = z / 3;  c = z % 3;
        for(int d=0;d < 4;++d){
            nr = r + dr[d];
            nc = c + dc[d];
            nz = 3 * nr + nc;
            if(nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
            State& t = st[rear];
            memcpy(&t,st[front], sizeof(State));
            t[z] = next_state[d][s[nz]];
            t[nz] = 0;
            dist[rear] = dist[front] + 1;
            //debug(t);
            if(try_to_inseart(rear)) ++rear;
        }
    }
    return 0;
}

void debug(State s){
    cout << "****";
    for(int i=0;i < 9;++i){
        if(i % 3 == 0) cout << endl;
        if(s[i] == 1 || s[i] == 2) cout << "W ";
        if(s[i] == 3 || s[i] == 4) cout << "R ";
        if(s[i] == 5 || s[i] == 6) cout << "B ";
        if(s[i] == 0) cout << "E ";
    }
    cout << endl << "****" << endl;
}

int main() {
    while(in()){
        int ans = bfs();
        if(ans >= 0)
            printf("%d\n",dist[ans]);
        else
            printf("-1");
    }
    return 0;
}