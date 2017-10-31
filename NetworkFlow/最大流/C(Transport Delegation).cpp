#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <cstring>
#define INF 0x7fffffff
#define MaxNode 5000
#define MaxEdge 5000000
#define MaxQue 2000000
using namespace std;
int N,M,A,B,m0=1,Ans,Total,S,T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],NEXT[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];

int Min(int a,int b){return a<b?a:b;}
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

int getID(unordered_map<string, int> &id, string str) {
    if (id.count(str))
        return id[str];
    int newID = id.size();
    return id[str] = newID;
}

int main()
{
    Clear();
    int s, r, f, t;
    unordered_map<string, int> id;
    cin >> s >> r >> f >> t;
    S = getID(id, "$Source");
    T = getID(id, "$Sink");

    string tmp;
    for (int i=1; i<=r; i++) {
        cin >> tmp;
        int curID = getID(id, tmp);
        Add(S, curID, 1);
    }

    for (int i=1; i<=f; i++) {
        cin >> tmp;
        int curID = getID(id, tmp);
        Add(curID, T, 1);
    }

    for (int i=1; i<=t; i++) { // addEdge for each transport company
        string in_str = "$in" + to_string(i);
        string out_str = "$out" + to_string(i);
        int inID = getID(id, in_str);
        int outID = getID(id, out_str);
        Add(inID, outID, 1); // 每个运输公司的点容量为1
        int num;
        cin >> num;
        for (int j=1; j<=num; j++) {
            cin >> tmp;
            Add(getID(id, tmp), inID, 1);
            Add(outID, getID(id, tmp), 1);
        }
    }
    
    Ans=DINIC();
    printf("%d\n",Ans);
    return 0;
}
