#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define maxn 1000005
#define maxlog 23

vector<int> G[maxn];
int size[maxn];
int dep[maxn];
int f[maxn][maxlog];

void dfs(int u) {
    for (int i=1;i<maxlog;i++) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto& v : G[u]) {
        if (!dep[v]) {
            f[v][0]=u;
            dep[v] = dep[u] + 1;
            dfs(v);
            size[u] += size[v];
        }
    }
}

int lca(int a,int b) {
    if (dep[a] > dep[b]) swap(a,b); 

    for (int i=maxlog-1;i>=0;i--)
        if (dep[f[b][i]]>=dep[a])
            b=f[b][i];
    if (a==b) return a;
    for (int i=maxlog-1;i>=0;i--)
        if (f[a][i]!=f[b][i])
            a=f[a][i], b=f[b][i];
    return f[a][0];
}
int low_lca(int a,int b) {
    if (dep[a] > dep[b]) swap(a,b);
    for (int i=maxlog-1;i>=0;i--)
        if (dep[f[b][i]]>=dep[a]+1)
            b=f[b][i];
    return b;
    for (int i=maxlog-1;i>=0;i--)
        if (f[a][i]!=f[b][i])
            a=f[a][i], b=f[b][i];
    return f[a][0];
}

int n, m;
int tonode(int i, int j) {
    return i * m + j + 1;
}
void addedge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int dx[10] = {1, 0};
int dy[10] = {0, 1};
int q, i0, j0, i1, j1, i2, j2; 

int main() {
    cin >> n >> m;
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            scanf("%d", &size[tonode(i,j)]);
    for (int i=0; i<n; i++)
        for (int j = 0; j < m; j++) {
            if (size[tonode(i,j)] == 0) continue;
            for (int dir=0; dir < 2; dir++) {
                int tx = i+dx[dir];
                int ty = j+dy[dir];
                if (tx < 0 || tx>=n || ty<0 || ty>=m)
                    continue;
                if (size[tonode(tx,ty)] == 0)
                    continue;
                addedge(tonode(i,j),tonode(tx,ty));
            }
        }
    int R = 0;
    for (int i=1; i<=n*m; i++) {
        if (!dep[i] && size[i]) {
            R = i;
            dep[i] = 1;
            dfs(i);
        }
    }

    cin >> q;
    while (q--) {
        scanf("%d%d%d%d%d%d", &i0,&j0,&i1,&j1,&i2,&j2);
        i0--;i1--;i2--;
        j0--;j1--;j2--;
        int s = tonode(i0,j0);
        int e1 = tonode(i1,j1);
        int e2 = tonode(i2,j2);
        if (size[s] == 0) {
            puts("0"); continue;
        }
        if (size[e1]==0 && size[e2]==0) {
            printf("%d\n",size[R]);continue;
        }
        if ((size[e1]==0) ^ (size[e2]==0)) {
            int ans = 0;
            if (size[e1] == 0) e1 = e2;
            int tmp = lca(e1, s);
            if (tmp == s) ans = size[R] - size[e1];
            else {
                if (tmp == e1) ans = size[low_lca(e1,s)];
                else ans = size[R] - size[e1];
            }
            printf("%d\n", ans);continue;
        }
        int ans = 0, low = 0;
        if (lca(s,e1)==e1) {
            if (lca(s,e2)==e2) {
                low = e1+e2-lca(e1,e2);
                low = low_lca(low,s);
            }
            else {
                low = e1;
                low = low_lca(low,s);
            }
        }
        else {
            if (lca(s,e2)==e2) {
                low = e2;
                low = low_lca(low,s);
            }
            else low = R;
        }
        ans = size[low];
        if (lca(low,e1)==low) {
            if (lca(low,e2)==low) {
                if (lca(e1,e2)==e1 || lca(e1,e2)==e2)
                    ans -= size[lca(e1,e2)];
                else ans -= (size[e1]+size[e2]);
            }
            else ans -= size[e1];
        }
        else {
            if (lca(low,e2)==low)
                ans -= size[e2];
        }
        printf("%d\n", ans);
    }
    return 0;
}