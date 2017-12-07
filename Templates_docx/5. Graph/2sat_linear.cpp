
// node indexed from 0~n-1
#include <cstring>
int n, dfs_clock=0, scc_cnt=0;
int pre[MAXN*2],low[MAXN*2];
int sccno[MAXN*2];
stack<int> S;
vector<int> G[MAXN*2];
void Clear() {
    for (int i = 0; i < n*2; i++)
        G[i].clear();
    dfs_clock = scc_cnt = 0;
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(sccno, 0, sizeof(sccno));
}
void add_constrain(int x,int xval,int y,int yval) {
    //x=xval or y = yval
    x=2*x+xval;
    y=2*y+yval;
    G[x^1].push_back(y); //!x->y
    G[y^1].push_back(x); //!y->x
}
void dfs(int u) { // scc
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
        int tmp = 0;
        do {
            tmp = S.top(); S.pop();
            sccno[tmp] = scc_cnt;
        } while (tmp != u);
    }
} // end of dfs
bool twosat() {
    for (int i=0; i<n*2; i++)
        if (!pre[i])
            dfs(i);
    for (int i=0; i<n; i++)
        if (sccno[i*2] == sccno[i*2+1])
            return false;
    return true;
}