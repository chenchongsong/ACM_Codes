#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <cstring>
#define INF 0x3f3f3f3f
#define MaxNode 500000
#define MaxEdge 2000000
#define MaxQue 2000000

using namespace std;
int R, C, m0=1, Ans, Total, S, T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],NEXT[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];

int Min(int a,int b){return a<b?a:b;}
int IN(int x, int y) { return (x * C + y); }
int OUT(int x, int y) { return (IN(x, y) + R * C); }

void Clear() {
    memset(head, 0, sizeof(head));
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(NEXT, 0, sizeof(NEXT));
    memset(con, 0, sizeof(con));
    memset(Q, 0, sizeof(Q));
    memset(cur, 0, sizeof(cur));
}

void Add(int a,int b,int c)
{
    // printf("%d %d: %d\n",a,b,c);
    v[++m0]=b;NEXT[m0]=head[a];head[a]=m0;con[m0]=c;
    v[++m0]=a;NEXT[m0]=head[b];head[b]=m0;con[m0]=0;
}

int bfs()
{
    int Qhead=0,Qtail=0;
    memset(vis,0,sizeof(vis));
    memset(dis,127,sizeof(dis));
    dis[S]=0;vis[S]=1;Q[++Qtail]=S;
    while(Qhead<Qtail)
    {
        ++Qhead;
        for(int i=head[Q[Qhead]];i;i=NEXT[i])
            if(!vis[v[i]] && con[i])
            {
                vis[v[i]]=1;
                dis[v[i]]=dis[Q[Qhead]]+1;
                Q[++Qtail]=v[i];
            }
    }
    return vis[T];
}

int dfs(int now,int lim)
{
    if (now==T || !lim) return lim;
    int flow=0, f;
    for (int& i=cur[now];i;i=NEXT[i])
    {
        if (dis[v[i]]>dis[now] && con[i])
            if ((f = dfs(v[i],Min(lim-flow,con[i]))) > 0) {
            flow+=f;
            con[i]-=f;
            con[i^1]+=f;
            if (flow==lim) break;
        }
    }
    return flow;
}

int DINIC()
{
    int flow=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(head));
        flow+=dfs(S,INF);
    }
    return flow;
}

int soldier[610][610];



int main()
{
    Clear();
    cin >> R >> C;
    S = 2 * R * C + 10;
    T = S + 1;

    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            // printf("i == %d j == %d\n",i,j);
            cin >> soldier[i][j];
            Add(IN(i,j), OUT(i,j), soldier[i][j]);

            if (i==0 || i==R-1 || j==0 || j==C-1)
                Add(S, IN(i,j), INF);
            if (i > 0) Add(OUT(i,j), IN(i-1,j), INF);
            if (i < R-1) Add(OUT(i,j), IN(i+1,j), INF);
            if (j > 0) Add(OUT(i,j), IN(i,j-1), INF);
            if (j < C-1) Add(OUT(i,j), IN(i,j+1), INF);
        }
    }

    int kingC, kingR;
    cin >> kingC >> kingR;
    Add(OUT(kingC, kingR), T, INF);
    
    Ans=DINIC();
    printf("%d\n",Ans);
    return 0;
}

/*

7 8
42 42  0  0  0  0  0 16
42 11 14 42 42 42 10 16
42  0 42 42 42 42  0 16
42  0 42 42 42 42  0 42
42  0 42 42 42 42  0 42
42 11 42 42 42  5  5 42
42 42  0  0  0 42 42 42
3 4

3 3
1 1 1
1 3 1
1 1 1
1 1

*/