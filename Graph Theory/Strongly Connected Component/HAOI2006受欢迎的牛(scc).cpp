#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#define MaxN 10010
using namespace std;

// 强连通分量
int dfs_clock = 0, pre[MaxN],low[MaxN];
int scc_cnt, sccno[MaxN], size[MaxN];
stack<int> S; vector<int> G[MaxN];

void Add(int a,int b) {G[a].push_back(b);}

void dfs(int u) {
pre[u] = low[u] = ++dfs_clock;
S.push(u);
for (int i = 0; i < G[u].size(); i++) {
       int v = G[u][i];
       if (!pre[v]) {
              dfs(v);
              low[u] = min(low[u], low[v]); 
}
else if (!sccno[v]) 
	 low[u] = min(low[u],pre[v]);
}
if (low[u] == pre[u]) {
       scc_cnt++;
       int original_size = S.size(), tmp = 0;
       do {
              tmp = S.top();   S.pop();
              sccno[tmp] = scc_cnt;
       } while (tmp != u);
       size[scc_cnt] = original_size - S.size();
} } // end of dfs

vector<int> G2[MaxN];
int main() {
       int n, m;
       scanf("%d%d", &n, &m);
       for (int i=1; i<=m; i++) {
              int a, b;
              scanf("%d%d", &a, &b);
              Add(a, b);
       }
       for (int i=1; i<=n; i++)
              if (!pre[i])
                     dfs(i);
       for (int i=1; i<=n; i++) {
              for (int j=0; j<G[i].size(); j++) {
                     int to = G[i][j];
                     if (sccno[i] != sccno[to]) {
                            G2[sccno[i]].push_back(sccno[to]);
                     }
              }
       }
       int ans = 0;
       bool flag = 0;
       for (int i=1; i<=scc_cnt; i++) {
              if (G2[i].size() == 0) {
                     if (flag) {
                            ans = 0;
                            break;
                     }
                     flag = 1;
                     ans = size[i];
              }
       }
       printf("%d\n", ans);
       return 0;
}
