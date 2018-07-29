#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

int n, cnt, kase, visited[21], edges[21][21], valid_nodes[21];
vector<int> re;

void init(){
    cnt = 0;
    memset(visited,0,sizeof(visited));
    memset(edges,0, sizeof(edges));
    memset(valid_nodes,0, sizeof(valid_nodes));
    re.clear();
}

void DFS(int node){
    if(!valid_nodes[node])
        return;
    if(node == n){
        //Find the path
        for(int i=0;i < re.size();++i)
            printf("%d ",re[i]);
        printf("%d\n",node);
        ++cnt;
        return;
    }
    visited[node] = 1;
    re.push_back(node);
    for(int v = 1;v <= 20;++v){
        if(edges[node][v] && !visited[v]){
            DFS(v);
        }
    }
    re.pop_back();
    visited[node] = 0;
}

void RDFS(int v){
    valid_nodes[v] = 1;
    for(int i=1;i <= 20;++i){
        if(edges[v][i] && !valid_nodes[i])
            RDFS(i);
    }
}

int main() {
    while(init(), cin >> n){
        int x, y;
        while(cin >> x >> y, x || y)
            edges[x][y] = edges[y][x] = 1;
        printf("CASE %d:\n", ++kase);
        RDFS(n);
        DFS(1);
        printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, n);
    }
    return 0;
}