#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

struct BLOCK{
    BLOCK(int a, int b){x = a; y = b;}
    int x,y;
};

//ENSW四个方向的位移
const int dx[4] = {1, 0, 0, -1};
const int dy[4] = {0, 1, -1, 0};
const char dirs[] = "ensw";
const int N = 250;

int kase, n, ncnt, cnt;
vector<struct BLOCK> blocks;
vector<int> re;
int visited[N][N];

bool come_to_block(int x, int y){
    for(int i=0; i < blocks.size();++i)
        if(x == blocks[i].x && y == blocks[i].y)
            return true;
    return false;
}

//当block时返回false,否则返回true
bool judge(int x, int y, int next_x, int next_y, int di){
    if(di == 0){
        for(int i=0;i < blocks.size();++i){
            if(blocks[i].y == y && blocks[i].x >= x && blocks[i].x <= next_x)
                return false;
        }
    }
    else if(di == 1){
        for(int i=0;i < blocks.size();++i){
            if(blocks[i].x == x && blocks[i].y >= y && blocks[i].y <= next_y)
                return false;
        }
    }
    else if(di == 2){
        for(int i=0;i < blocks.size();++i){
            if(blocks[i].x == x && blocks[i].y <= y && blocks[i].y >= next_y)
                return false;
        }
    }
    else if(di == 3){
        for(int i=0;i < blocks.size();++i)
            if(blocks[i].y == y && blocks[i].x <= x && blocks[i].x >= next_x)
                return false;
    }

    return true;
}

void step(int x, int y, int di, int steps){

    if(steps == n){
        if(x == 0 && y == 0){
            for(int i=0;i < re.size();++i)
                cout << dirs[re[i]];
            cnt++;
            cout << endl;
        }
        return;
    }

    //当剩余的步数不够回到终点时候剪枝
    int left_steps = 0;
    for(int i = steps + 1;i <= n;++i)
        left_steps += i;
    if(abs(x) + abs(y) > left_steps)
        return ;

    int next_di[2];
    if(di == 0 || di == 3){
        //如果当前当像是E||W,转头之后方向就是N||S
        next_di[0] = 1;
        next_di[1] = 2;
    }
    else{
        next_di[0] = 0;
        next_di[1] = 3;
    }

    for(int i = 0;i < 2;++i){
        int next_x = x + dx[next_di[i]] * (steps+1), next_y = y + dy[next_di[i]] * (steps+1);
        if(!judge(x,y,next_x,next_y,next_di[i]) || visited[next_x+N/2][next_y+N/2])
            continue;
        re.push_back(next_di[i]);
        visited[next_x+N/2][next_y+N/2] = 1;
        step(next_x, next_y, next_di[i], steps+1);
        visited[next_x+N/2][next_y+N/2] = 0;
        re.pop_back();
    }
}

int main() {
    cin >> kase;
    while(kase--){
        blocks.clear();
        memset(visited,0, sizeof(visited));
        cnt = 0;
        cin >> n >> ncnt;
        int x,y;
        while(ncnt--){
            cin >> x >> y;
            blocks.push_back(BLOCK(x,y));
        }
        x = y = 0;
        for(int i = 0;i < 4;++i){
            if(come_to_block(dx[i],dy[i]))
                continue;
            re.push_back(i);
            visited[dx[i]+N/2][dy[i]+N/2] = 1;
            step(dx[i],dy[i],i,1);
            visited[dx[i]+N/2][dy[i]+N/2] = 0;
            re.pop_back();
        }
        printf("Found %d golygon(s).\n\n",cnt);
    }
    return 0;
}