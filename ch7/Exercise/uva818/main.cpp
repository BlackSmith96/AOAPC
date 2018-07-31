#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, edges[16][16], min_times, k, kase=0, vis[16], l;
bool loop_flag;

void init(){
    memset(edges, 0, sizeof(edges));
    min_times = 200;
}

bool in(){
    cin >> n;
    if(n == 0)
        return false;

    int a, b;
    cin >> a >> b;
    while(a != -1 || b != -1){
        ++edges[a-1][b-1];
        ++edges[b-1][a-1];
        cin >> a >> b;
    }
    return true;
}

//判断有没有节点的度大于2
bool judge_degree(){
    for(int i=0;i < n;++i){
        //确保i不是被拿下来的珠子
        if(k & 1 << i) continue;
        int d = 0;
        for(int j=0;j < n;++j){
            if(i == j) continue;
            if(k & 1 << j) continue;
            if(edges[i][j])
                d += edges[i][j];
        }
        if(d > 2)
            return false;
    }

    return true;
}

bool DFS(int i, int fa){
    vis[i] = 1;
    for(int v=0;v < n;++v){
        if(edges[i][v]){
            if(v == fa || (k & (1 << v))) continue;
            if(vis[v]) return true;
            if(DFS(v,i)) return true;
        }
    }
    return false;
}


int main() {
    while(true){
        init();
        if(!in())
            break;

        for(k=0;k < (1 << n);++k){
            l = 0;
            if(!judge_degree())
                continue;
            //判断是否成环
            memset(vis, 0, sizeof(vis));
            loop_flag = false;
            for(int i=0;i < n ;++i){
                if(k & 1 << i) continue;
                if(vis[i]) continue;
                ++l;
                if(DFS(i,-1)){
                    loop_flag = true;
                    break;
                }
            }
            if(loop_flag) continue;
            int total = 0;
            for(int i=0;i < n ;++i)
                if(k & (1 << i))
                    ++total;
            if(total + 1 < l)
                continue;
            if(total < min_times)
                min_times = total;
        }
        printf("Set %d: Minimum links to open is %d\n", ++kase, min_times);
    }
    return 0;
}