#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#define MaxQue 2000000
using namespace std;
const int MaxNode=5000;
const int MaxEdge=5000000;
int N, M, W[123], L[123];

vector<int> ans[MaxNode];

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

void dfsans(int now, int id) {
	if (vis[now] || now == S || now == T) return;
	vis[now] = 1;
	ans[id].push_back(now);
	for (int i=0; i < G[now].size(); i++) {
		Edge& e = edges[G[now][i]];
		if (N < now && now <=N+N) {
			// printf("now %d to %d\n", now, now-N);
			// printf("now %d to %d\n", now, now-N);
			dfsans(now-N, id);
			break;
		}
		// printf("now %d to %d\n", now, v[i]);
		if (e.cap == 0) continue;
		if (vis[e.to]) continue;
		if (e.to > N+N) continue;
		// if (N < now && now <=N+N && )
		// printf("now %d to %d\n", now, v[i]);
		dfsans(e.to, id);
	}
}

int main(){
	Clear();
	cin>>N;
	S=0;
	for(int i=1; i<=N; i++){
		cin>>W[i]>>L[i];
		if(!W[i]) Add(S, i, 1);
		Add(i, i+N, 1);
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			if(i==j) continue;
			if(L[i]>=W[j]) Add(i+N, j, 1);
		}
	}
	cin>>M;
	T=N+N+M+1;
	for(int i=1; i<=M; i++){
		int tmp;
		cin>>tmp;
		Add(N+N+i, T, 1);
		for(int j=1; j<=N; j++)
			if(L[j]>=tmp) Add(N+j, 2*N+i, 1);
	}
	if(DINIC()!=M){
		cout<<"impossible"<<endl;
		return 0;
	}

	memset(vis, 0, sizeof(vis));
	vis[T] = 1;

	for (int i=1; i<=M; i++) {
		dfsans(N+N+i, i);
	}
	for (int i=1; i<=M; i++) {
		for (int j=ans[i].size()-1; j>=0; j--) {
			if (1<=ans[i][j] && ans[i][j]<=N) {
				cout << ans[i][j] << " ";
			}
		}
		puts("");
	}
	
	return 0;
}


/*

5
0 1
1 2
2 3
3 4
0 2
2
4 2


7
0 1
1 4
0 3
0 1
2 5
2 5
1 2
3
5 4 5

2
0 1
5 3
2
2 1
*/