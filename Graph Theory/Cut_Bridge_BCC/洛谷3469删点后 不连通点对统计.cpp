#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 200011
#define ll long long
int n, m;
ll ans[MAXN];
ll size[MAXN];

// 点-双联通:点对存在两条(点不重复)的路径
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

void dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    size[u] = 1;
    ll tmp = 0; // 记录到目前为止易被分离的子节点v的size总和
    for (auto v : G[u]) {
        Edge e = {u,v};
        
        if (!pre[v]) {
            
            dfs(v,u); //注意v,u的顺序
            size[u] += size[v];
            
            low[u] = min(low[u], low[v]);
            if (low[v] >= pre[u]) { // 若删掉u v会被分离
                ans[u] += (size[v] * tmp); // 统计易被分离的子树之间的点对数目
                tmp += size[v];
            }
        }
        else if( pre[u] > pre[v] && v!=fa )
            low[u] = min(low[u],pre[v]);
    }
    ans[u] += tmp * (n - tmp - 1);
    // 统计已被分离的子树 与 不易被分离的其他点之间的点对数目
}
// end of template
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main() {
    n = read(); m = read();
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        if (!pre[i])
            dfs(i,-1);
    for (int i=1; i<=n; i++)
        printf("%lld\n", (ans[i]+(n-1)) * 2);

    return 0;
}
