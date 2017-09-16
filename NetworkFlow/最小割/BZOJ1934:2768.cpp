// http://www.cnblogs.com/iwtwiioi/p/3934305.html

// 首先也是二分图，将s连到1的点，点为0连到t，容量均为1（1的点集我设x，0的点集我设为y）
// 然后连兄弟边，容量均为1（双向）
// 然后求最小割就是答案
// 为什么呢。。

// 因为我们设s就代表了1，t代表了0，而一个割C(s, t)就代表了一个解决冲突的方案，
// 如果某个x集里的点a现在被割分到了t，那么它与s的边一定断掉（代表他自己违背自己），
// 与x集或y集的其它分到s的点的边也一定断掉（代表了它解决冲突的方案）

// 所以最小割就代表了最优方案。


// http://pepcy.cf/BZOJ-1934-SHOI-2007-%E5%96%84%E6%84%8F%E7%9A%84%E6%8A%95%E7%A5%A8Vote/

// 建最小割跑最大流即为答案。

// 从源点向意愿赞同／反对的小朋友连一条容量为 1 的边
// 从意愿反对／赞同的小朋友向汇点连一条容量为 1 的边，以上两组边若被割断，则表示投票与意愿相反；

// 每对朋友互连一条容量为 1 的边，割断表示朋友间投票不同，
// 但实际有用的边只有从赞同／反对的人连向反对／赞同的边。


// CCS:
// 一种割法的边权和 == 一种表决方案的冲突总数
// 为了使表决方案冲突总数最小 我们要找到最小的割

// 一种表决方案 ---对应---> 一种割
// 因为 若不是割 则存在一条通路 S->A->B->T 说明两个朋友A&B的观点不同 所以不是一种表决方案


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
