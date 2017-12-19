#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <cstring>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f
#define MaxNode 500000
#define MaxEdge 2000000
#define MaxQue 2000000

using namespace std;
int R, C, Ans;

int IN(int x, int y) { return (x * C + y); }
int OUT(int x, int y) { return (IN(x, y) + R * C); }

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