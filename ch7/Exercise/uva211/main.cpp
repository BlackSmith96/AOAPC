#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int rips[7][8], map[7][8], bone_number[7][7], visited[29];
int bone[7][8][4]; //分别对应上下左右四个方向上的可能块号,0则为不可能
int cnt, cases = 0;
//上下左右四个方向依次位移,i是行坐标，j是列坐标
const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

void init(){
    cnt = 0;
    memset(bone, 0, sizeof(bone));
    memset(visited, 0, sizeof(visited));
    memset(map, 0, sizeof(map));
}

void calc_bone_number(){
    int total = 0;
    for(int pip1 = 0;pip1 <= 6;++pip1){
        for(int pip2 = pip1;pip2 <= 6;++pip2){
            bone_number[pip1][pip2] = ++total;
        }
    }
}

void calc_bone(){
    int ni, nj;
    for(int i=0;i < 7;++i)
        for(int j=0;j < 8;++j)
            for(int d=0;d < 4;++d){
                ni = i + di[d];
                nj = j + dj[d];
                if(ni < 0 || ni > 6 || nj < 0 || nj > 7)
                    continue;
                if(rips[i][j] < rips[ni][nj])
                    bone[i][j][d] = bone_number[rips[i][j]][rips[ni][nj]];
                else
                    bone[i][j][d] = bone_number[rips[ni][nj]][rips[i][j]];
            }
}

void iter_visit(int i, int j){

    if(i == 7){
        printf("\n");
        for(int x=0;x < 7;++x){
            for(int y=0;y<8;++y)
                printf("%4d",map[x][y]);
            printf("\n");
        }
        ++cnt;
        return;
    }

    int ni, nj;
    if(j == 7){
        ni = i + 1;
        nj = 0;
    }
    else{
        ni = i;
        nj = j + 1;
    }

    if(map[i][j] > 0){
        iter_visit(ni, nj);
    }

    for(int d=3;d >=0 ;--d){
        if(bone[i][j][d] == 0)
            continue;
        if(map[i][j] == 0 && map[i+di[d]][j+dj[d]] == 0 && !visited[bone[i][j][d]]){
            map[i][j] = map[i+di[d]][j+dj[d]] = bone[i][j][d];
            visited[bone[i][j][d]] = 1;
            iter_visit(ni,nj);
            visited[bone[i][j][d]] = 0;
            map[i][j] = map[i+di[d]][j+dj[d]] = 0;
        }
    }
}

bool in(){
    ++cases;
    for(int i=0;i < 7;++i)
        for(int j=0;j < 8;++j)
            if(!(cin >> rips[i][j]))
                return false;

    if(cases >= 2)printf("\n\n\n");
    printf("Layout #%d:\n\n",cases);
    for(int i=0;i < 7;++i){
        for(int j=0;j < 8;++j)
            printf("%4d",rips[i][j]);
        printf("\n");
    }
    printf("\nMaps resulting from layout #%d are:\n\n",cases);
    return true;
}



int main() {
    calc_bone_number();
    while(true){
        init();
        if(!in())
            break;

        calc_bone();
        iter_visit(0,0);

        printf("\nThere are %d solution(s) for layout #%d.\n",cnt,cases);
    }
    return 0;
}