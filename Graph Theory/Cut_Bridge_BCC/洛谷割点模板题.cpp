#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<cstring>
#include <iostream>
using namespace std;
#define MAXN 200011
struct Edge{
    int u,v;
    bool operator < (const Edge& lhs) const
    {return u < lhs.u || (u == lhs.u && v < lhs.v);}
};
vector<int>G[MAXN],bcc[MAXN];
vector<Edge>bridge;
int low[MAXN],pre[MAXN],dfs_clock=0,
iscut[MAXN],bccno[MAXN],bcc_cnt=0;
//bccno是每个点在哪块 bcc是第i块有哪些点
//点编号0~n-1
stack<Edge>s;//保存在当前bcc中的边,割顶的bccno无意义,因为存在于多个bcc中
void dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    int child=0;
    for (auto v : G[u]) {
        Edge e = {u,v};
        if (!pre[v]) {
        //not visited yet
            s.push(e); //store cut edge
            dfs(v,u); //注意v,u的顺序
            child++;
            low[u] = min(low[u], low[v]);
            if (low[v] >= pre[u]) {
            //if cut, bcc find
                if (low[v] > pre[u])
                    bridge.push_back((Edge){min(u,v),max(u,v)});
                iscut[u] = 1;
                bcc[++bcc_cnt].clear();
                while(1) {
                    Edge x = s.top(); s.pop();
                    if(bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if(bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if (x.u==u && x.v==v) break;
                }
            }
        }
        else if( pre[u] > pre[v] && v!=fa ) {
        //early than father
            s.push(e);
            low[u] = min(low[u],pre[v]);
        }
    }
    if(child <= 1 && fa < 0)
        iscut[u] = 0;
}

int n, m;


int main() {
    {
        int i,a,b;
        char ch;
        cin >> n >> m;
        memset(pre, 0, sizeof(pre));
        for (int i=1; i<=m; i++) {
            cin >> a >> b;
            // a--; b--;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        for (i = 1; i <= n; i++)
            if (!pre[i])
                dfs(i,-1);
        int cnt_cut = 0;
        for (int i=1; i <=n; i++)
            cnt_cut += (iscut[i] == 1);
        cout << cnt_cut << endl;
        for (int i = 1; i <= n; i++) {
            if (iscut[i])
                printf("%d ", i);
        }
    }
    return 0;
}