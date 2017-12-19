#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define MaxNode 5000
#define MaxEdge 500000
#define MaxQue 2000000
using  namespace std;
int N, M, A, B, Ans;

char map[1000];
int Node(int i,int j){return i*M+j;} // i=0~N-1 j=0~M-1

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
