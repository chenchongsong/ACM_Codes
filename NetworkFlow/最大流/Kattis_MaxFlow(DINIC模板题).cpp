#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define MaxNode 510
#define MaxEdge 200010
#define MaxQue 2000010
using namespace std;

// ==========  DINIC() ==========
// O(n^2*m)
// all con[]==1 O(min(n^(2/3),m(1/2))*m)
// 二分图匹配 O(n^(0.5) * m)
#define INF 0x3f3f3f3f
int m0 = 1, S, T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],NEXT[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];
int Min(int a,int b){return a<b?a:b;}
void Clear() {
    // include <cstring>
    // memset(head u v NEXT con Q cur) to zero;
}
void Add(int a,int b,int c) {
v[++m0]=b;u[m0]=a;NEXT[m0]=head[a];head[a]=m0;con[m0]=c;
v[++m0]=a;u[m0]=b;NEXT[m0]=head[b];head[b]=m0;con[m0]=0;
}
int bfs() {
    int Qhead=0,Qtail=0;
    memset(vis,0,sizeof(vis));
    memset(dis,127,sizeof(dis));
    dis[S]=0;vis[S]=1;Q[++Qtail]=S;
    while(Qhead<Qtail) {
        ++Qhead;
        for(int i=head[Q[Qhead]];i;i=NEXT[i])
            if(!vis[v[i]] && con[i]) {
                vis[v[i]]=1;
                dis[v[i]]=dis[Q[Qhead]]+1;
                Q[++Qtail]=v[i];
            }
    }
    return vis[T];
}
int dfs(int now,int lim) {
    if (now==T || !lim) return lim;
    int flow=0, f;
    for (int& i=cur[now];i;i=NEXT[i]) {
        if (dis[v[i]]>dis[now] && con[i])
            if ((f=dfs(v[i],Min(lim-flow,con[i]))) > 0){
            flow+=f;
            con[i]-=f;
            con[i^1]+=f;
            if (flow==lim) break;
        }
    }
    return flow;
}
int DINIC() {
    int flow=0;
    while(bfs()) {
        memcpy(cur,head,sizeof(head));
        flow+=dfs(S,INF);
    }
    return flow;
}

int main() {
    int N, M, a, b, c;
    cin >> N >> M >> S >> T;
    for (int i=1; i<=M; i++) {
        cin >> a >> b >> c;
        Add(a, b, c);
    }
    
    int Ans_Flow = DINIC();
    
    int Ans_M = 0;
    for (int i = 3; i <= m0; i += 2)
        if (con[i]) Ans_M++;
    
    printf("%d %d %d\n", N, Ans_Flow, Ans_M);

    for (int i = 3; i <= m0; i += 2) {
        if (con[i]) {
            printf("%d %d %d\n", v[i], u[i], con[i]);
        }
    }

}

