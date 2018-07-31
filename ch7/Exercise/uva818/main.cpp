#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, edges[16][16], min_times, k, kase=0, vis[16];
bool loop_flag;

void init(){
    memset(edges, 0, sizeof(edges));
    min_times = INT_MAX;
}

bool in(){
    cin >> n;
    if(n == 0)
        return false;

    int a, b;
    for(int i=0;i < n;++i){
        cin >> a >> b;
        edges[a][b] = edges[b][a] = 1;
    }
    return true;
}

//判断有没有节点的度大于2
bool judge_degree(){
    for(int i=1;i <= n;++i){
        int d = 0;
        for(int j=1;j <= n;++j){
            if(i == j) continue;
            if(k & 1 << j) continue;
            if(edges[i][j])
                ++d;
        }
        if(d > 2)
            return false;
    }
}

bool DFS(int i, int target){
    for(int j=1;j != )
}

bool judge_loop(int i){

}

int main() {
    while(true){
        ++kase;
        init();
        if(!in())
            break;

        for(int k=0;k < (1 << n);++k){
            if(!judge_degree())
                continue;
            //判断是否成环
            loop_flag = false;
            for(int i=1;i <= n ;++i){
                memset(vis, 0, sizeof(vis));
                if(!judge_loop(i)){
                    loop_flag = true;
                    break;
                }
            }
            if(loop_flag) continue;
            int total = 0;
            for(int i=0;i < n ;++i)
                if(k & (1 << i))
                    ++total;
            if(total < min_times)
                min_times = total;
        }
        printf("Set %d: Minimum links to open is %d\n", kase++, min_times);
    }
    return 0;
}