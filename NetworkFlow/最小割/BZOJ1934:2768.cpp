#include <cstdio>
#include <cstring>
#define INF 0x7fffffff
#define MaxNode 500
#define MaxEdge 500000
#define MaxQue 2000000
int M,N,m0=1,Ans,Total,S,T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],next[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];

int thought[MaxNode];

int Min(int a,int b){return a<b?a:b;}

void Add(int a,int b,int c)
{
    //printf("%d -- %d : %d\n",a,b,c);
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
    //memset(con, 0, sizeof(con));
    //memset(thought, 0, sizeof(thought));
    scanf("%d%d",&N,&M);
    S = N + 1;
    T = N + 2;
    for (int i=1; i<=N; i++) {
        scanf("%d", &thought[i]);
        if (thought[i])
            Add(S, i, 1);
        else
            Add(i, T, 1);
    }

    for (int i=1; i<=M; i++) {
        int person1, person2;
        scanf("%d%d", &person1, &person2);
        if (thought[person1] && !thought[person2])
            Add(person1, person2, 1);
        if (!thought[person1] && thought[person2])
            Add(person2, person1, 1);
    }
    
    Ans=DINIC();
    printf("%d\n",Ans);
    return 0;
}
