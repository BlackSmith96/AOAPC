/*
 * 参考https://wcr1996.com/2015/07/25/uva-690-pipeline-scheduling/,并且做了详细的注释
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 25;
//dt存储了可能的步长
int n, a[5], dt[maxn], ans, cnt;

//p是当前unit状态，k是间隔
bool ok(int *p, int k) {
    for(int i = 0; i < 5; ++i)
        if(a[i] << k & p[i]) return false;
    return true;
}

//sum是当前总的间隔,d是当前处理到的taskID,p是现在unit的状态,dt[]记录了
void dfs(int *p, int d, int sum) {
    if(sum + dt[0] * (10 - d) >= ans) return;
    if(d == 10) {ans = min(ans, sum); return; }
    for(int i = 0; i < cnt; ++i) {
        if(ok(p, dt[i])) {
            int p2[5];
            for(int j = 0; j < 5; ++j)
                p2[j] =(p[j] >> dt[i]) | a[j];
            dfs(p2, d+1, sum + dt[i]);
        }
    }
    return;
}
int main() {
    while(~scanf("%d", &n) && n) {
        memset(a, 0, sizeof(a));
        memset(dt, 0, sizeof(dt));
        for(int i = 0; i < 5; ++i) {
            char s[maxn]; scanf("%s", s);
            for(int j = 0; j < n; ++j)
                if(s[j] == 'X') a[i] |=(1 << j);
        }
        cnt = 0;
        for(int i = 1; i <= n; ++i)
            if(ok(a, i)) dt[cnt++]=i;
        ans = 10 * n;
        //因为第一个任务完成是在n时刻，后面的任务相当于把结束的时间拖长
        dfs(a, 1, n);
        printf("%d\n", ans);
    }
    return 0;
}