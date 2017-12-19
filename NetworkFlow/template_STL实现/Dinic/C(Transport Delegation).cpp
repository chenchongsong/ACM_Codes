#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <queue>
#define MaxNode 5000
#define MaxEdge 5000000
#define MaxQue 2000000
using namespace std;
int N, M, A, B, Ans, Total;

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
int Min(int a,int b){return a<b?a:b;}
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

int getID(unordered_map<string, int> &id, string str) {
    if (id.count(str))
        return id[str];
    int newID = id.size();
    return id[str] = newID;
}

int main() {
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
