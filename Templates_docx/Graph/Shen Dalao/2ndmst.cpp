#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 1000 //n
#define MAXM 2000 //m
int n,m,fa[MAXN],maxcost[MAXN][MAXN],pre[MAXN];
bool vis[MAXN];
struct Edge
{
    int u,v,w,inMST;
    Edge(int u=0,int v=0,int dist=0):u(u),v(v),w(dist){inMST=0;}
} edge[MAXM];
vector<Edge> vec[MAXN];//MST

bool cmp(const Edge& a,const Edge& b){
    return a.w<b.w;
}

int root(int x){
    return fa[x]==x?x:fa[x]=root(fa[x]);
}

void kruskal()
{
    sort(edge,edge+m,cmp);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    int cnt=0;

    for(int i=0;i<m;i++){
        int x=root(edge[i].u),y=root(edge[i].v);
        if(x!=y){
            fa[y]=x;
            vec[edge[i].u].push_back(Edge(edge[i].u, edge[i].v, edge[i].w));
            vec[edge[i].v].push_back(Edge(edge[i].v, edge[i].u, edge[i].w));
            edge[i].inMST=1;
            if(++cnt==n-1)
                break;
        }
    }
}

void dfs(int u)
{
    vis[u]=1;
    for(int i=0;i<vec[u].size();i++)
    {
        int v=vec[u][i].v;
        if(!vis[v]) //access a new node
        {   //u是v的父亲 在有根树中
            for(int j=1;j<=n;j++)
                if(vis[j])//relax from all node visited
                {
                    //j->v = max(j->u,u->v)
                    maxcost[j][v] = maxcost[v][j] = max(maxcost[j][u], vec[u][i].w);
                }
            dfs(v);
        }
    }
}

int nextMST()
{
    int i,ans=0x3f3f3f3f;
    for(i=0;i<m;i++)
    {
        Edge e = edge[i];
        if(!e.inMST)
            ans = min(ans,e.w-maxcost[e.u][e.v]);
            //ans是边权增大了多少
    }
    return ans;
}