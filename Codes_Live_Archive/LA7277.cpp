#include <cstdio>
#include <cstring>
#define INF 0x7fffffff
#define MaxNode 5000
#define MaxEdge 500000
#define MaxQue 2000000
int N,M,A,B,m0=1,Ans,Total,S,T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],next[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];

char map[1000];

int Min(int a,int b){return a<b?a:b;}
int Node(int i,int j){return i*M+j;} // i=0~N-1 j=0~M-1

void Clear() {
    memset(head, 0, sizeof(head));
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(next, 0, sizeof(next));
    memset(con, 0, sizeof(con));
    memset(Q, 0, sizeof(Q));
    memset(cur, 0, sizeof(cur));
}

void Add(int a,int b,int c)
{
    // printf("%d %d: %d\n",a,b,c);
    v[++m0]=b;next[m0]=head[a];head[a]=m0;con[m0]=c;
    v[++m0]=a;next[m0]=head[b];head[b]=m0;con[m0]=0;
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
        for(int i=head[Q[Qhead]];i;i=next[i])
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
    int flow=0,f;
    for (int& i=cur[now];i;i=next[i])
    {
        if (dis[v[i]]>dis[now] && con[i])
        if (f=dfs(v[i],Min(lim-flow,con[i])))
        {
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

int main()
{
    Clear();
    scanf("%d%d%d%d",&N,&M,&A,&B);
    S = N * M + 1;
    T = N * M + 2;
    for (int i=0; i<N; i++) {
        scanf("%s", map);
        for (int j=0; j<strlen(map); j++) {
            if (map[j] == '.')
                Add(S, Node(i,j), B);
            else // '#'
                Add(Node(i,j), T, B);
            if (i > 0) Add(Node(i,j), Node(i-1,j), A);
            if (i < N-1) Add(Node(i,j), Node(i+1,j), A);
            if (j > 0) Add(Node(i,j), Node(i,j-1), A);
            if (j < M-1) Add(Node(i,j), Node(i,j+1), A);
        }
    }
    
    Ans=DINIC();
    printf("%d\n",Ans);
    return 0;
}
