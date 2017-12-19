#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#define MaxNode 510
#define MaxEdge 200010
#define MaxQue 2000010
using namespace std;

// ==========  DINIC() ==========
// O(n^2*m)
// all con[]==1 O(min(n^(2/3),m(1/2))*m)
// 二分图匹配 O(n^(0.5) * m)
#include <cstring>
#define INF 0x3f3f3f3f
struct Edge {int from, to, cap;};
vector<Edge> edges;
vector<int> G[MaxNode];
int S, T;
int dis[MaxNode],cur[MaxNode];
bool vis[MaxNode];
void Clear() {
    edges.clear();
    for (int i=0; i<MaxNode; i++) G[i].clear();
}
void Add(int from, int to, int cap) {
    edges.push_back((Edge){from,to,cap});
    edges.push_back((Edge){to,from,0});
    int m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}
int bfs() {
    memset(vis,0,sizeof(vis));
    queue<int> Q;
    Q.push(S); dis[S]=0; vis[S]=1;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i=0; i<G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if(!vis[e.to] && e.cap) {
                vis[e.to]=1;
                dis[e.to]=dis[u]+1;
                Q.push(e.to);
            }
        }
    }
    return vis[T];
}
int dfs(int u,int lim) {
    if (u==T || !lim) return lim;
    int flow=0, f;
    for (int& i=cur[u]; i<G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (dis[e.to]>dis[u] && e.cap)
            if ((f=dfs(e.to,min(lim-flow,e.cap))) > 0){
            flow+=f;
            e.cap-=f;
            edges[G[u][i]^1].cap+=f;
            if (flow==lim) break;
        }
    }
    return flow;
}
int DINIC() {
    int flow=0;
    while(bfs()) {
        memset(cur, 0, sizeof(cur));
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
    for (int i = 1; i < edges.size(); i += 2)
        if (edges[i].cap) Ans_M++;
    
    printf("%d %d %d\n", N, Ans_Flow, Ans_M);

    for (int i = 1; i < edges.size(); i += 2) { // 所有反向边
        Edge& e = edges[i];
        if (e.cap) {
            printf("%d %d %d\n", e.to, e.from, e.cap);
        }
    }

}

