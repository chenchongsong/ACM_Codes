#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#define MaxN 2000011
#define MaxM 2000011
using namespace std;
typedef long long ll;
int n,m,tot,top,dfs_clock,scc_num,cnt,tmp,Ans;

int dfn[MaxN],low[MaxN],stack[MaxN];
int sccno[MaxN],out[MaxN],size[MaxN];
int head[MaxN],u[MaxM],v[MaxM],w[MaxM],NEXT[MaxM];
bool in[MaxN];

void Add(int a, int b, int c)
{u[++tot]=a;v[tot]=b;w[tot]=c;NEXT[tot]=head[a];head[a]=tot;}

void dfs(int now)
{
       dfn[now]=low[now]=++dfs_clock;
       stack[++top]=now;
       for (int i=head[now];i;i=NEXT[i])
       {
              if (!dfn[v[i]])
              {
                     dfs(v[i]);
                     low[now]=min(low[now],low[v[i]]); 
              }
              else if (!sccno[v[i]]) 
                     low[now]=min(low[now],dfn[v[i]]);
       }
       if (low[now]==dfn[now])
       {
              scc_num++;
              cnt=top;
              do{
                     tmp=stack[top--];
                     sccno[tmp]=scc_num;
              }while (tmp!=now);
              size[scc_num]=cnt-top;
       }
}

struct Edge { ll u,v,w; };
vector<Edge> edges;
vector<int> G[MaxN];
ll val[MaxN];
ll dp[MaxN];

void Add2(ll u, ll v, ll w) {
       // cout << u << " " << v << " " << w << endl;
       edges.push_back((Edge){u,v,w});
       G[u].push_back(edges.size()-1);
}

void Cal(int scc, ll w) {
       ll l = 0, r = 20000, mid=0;
       while (l+1 < r) {
              mid = (l+r)>>1;
              if ((mid*(mid+1))>>1 > w)
                     r = mid;
              else l = mid;
       }
       val[scc] += w * (l+1);
       val[scc] -= ( (l*(l+1))/2 + l*(l+1)*(2*l+1)/6 ) /2; // sigma(1~l)(i+i^2)
       // cout << "val == " << val[scc] << endl;
}

ll DP(int u) {
       if (dp[u]) return dp[u];
       for (auto& e : G[u]) {
              ll v = edges[e].v;
              dp[u] = max(dp[u], DP(v)+edges[e].w);
       }
       dp[u] += val[u];
       return dp[u];
}

int main()
{
       scanf("%d%d",&n,&m);
       int a,b,c;
       for (int i=1;i<=m;i++)
       {
              scanf("%d%d%d",&a,&b,&c);
              Add(a,b,c);
       }
       for (int i=1;i<=n;i++)
              if (!dfn[i])
                     dfs(i);

       for (int i=1;i<=m;i++) {
              int sv = sccno[v[i]];
              int su = sccno[u[i]];
              if (su == sv) {
                     Cal(su, w[i]);
              }
              else Add2(su, sv, w[i]);
       }
       int s;
       scanf("%d", &s);

       cout << DP(sccno[s]) << endl;
       return 0;
}

