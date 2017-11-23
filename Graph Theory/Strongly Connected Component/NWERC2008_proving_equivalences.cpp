#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define MaxN 50005
#define INF 0x3f3f3f3f
using namespace std;

// 强连通分量
int dfs_clock = 0, pre[MaxN],low[MaxN];
int scc_cnt, sccno[MaxN];
stack<int> S;
vector<int> G[MaxN];

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
       // int original_size = S.size();
       int tmp = 0;
       do {
              tmp = S.top();   S.pop();
              sccno[tmp] = scc_cnt;
       } while (tmp != u);
       // size[scc_cnt] = original_size - S.size();
}
} // end of dfs

int indeg[MaxN], outdeg[MaxN];
void Clear() {
       dfs_clock = 0;
       memset(pre, 0, sizeof(pre));
       memset(low, 0, sizeof(low));
       scc_cnt = 0;
       memset(sccno, 0, sizeof(sccno));
       while (!S.empty()) S.pop();
       for (int i=0; i<MaxN; i++)
              G[i].clear();
       memset(indeg, 0, sizeof(indeg));
       memset(outdeg, 0, sizeof(outdeg));
}
int main() {
       int T, N, M, a, b;
       cin >> T;
       // printf("%d\n", T);
       while (T--) {
              Clear();
              cin >> N >> M;
              for (int i=1; i<=M; i++) {
                     cin >> a >> b;
                     Add(a, b);
              }
              for (int i=1; i<=N; i++)
                     if (!pre[i])
                            dfs(i);
              for (int i=1; i<=N; i++) {
                     for (int j=0; j<G[i].size(); j++) {
                            int to = G[i][j];
                            if (sccno[i] != sccno[to])
                                   indeg[sccno[to]]++,
                                   outdeg[sccno[i]]++;
                     }
              }
              int cnt_start = 0;
              int cnt_end = 0;
              int cnt_single = 0;

              for (int i=1; i<=scc_cnt; i++) {
                     if (!indeg[i]) cnt_start++;
                     if (!outdeg[i]) cnt_end++;
                     if (!indeg[i] && !outdeg[i]) cnt_single++;
              }
              cnt_start -= cnt_single;
              cnt_end -= cnt_single;

              // printf("========== %d -- %d -- %d\n", cnt_start, cnt_end, cnt_single);
              
              if (scc_cnt == 1) {puts("0");continue;}
              if (cnt_single == scc_cnt) {printf("%d\n",scc_cnt);continue;}
              printf("%d\n", max(cnt_start, cnt_end) + cnt_single);
       }
       return 0;
}

/*
1
5 5
1 3
3 4
4 1
2 3
1 2

5


*/

