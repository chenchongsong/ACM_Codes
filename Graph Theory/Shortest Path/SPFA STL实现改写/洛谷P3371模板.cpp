// directed
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define maxn 2000010
#define INF 0x3f3f3f3f
using namespace std;

// ========= NEW SPFA =========
struct Edge {int u, v, w;};
vector<Edge> edges; // need clearance
vector<int> G[maxn]; // need clearance
int dis[maxn];
bool vis[maxn];
queue<int> que;
void AddEdge(int a, int b, int c) {
	edges.push_back((Edge){a,b,c});
	G[a].push_back(edges.size()-1);
}
void Spfa(int Source) {
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	que.push(Source); dis[Source] = 0;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i=0; i<G[u].size(); i++) {
			Edge& e = edges[G[u][i]];
			int v = e.v, w = e.w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					vis[v] = 1;
					que.push(v);
				}
			}
		}
		vis[u] = 0;
	}
}
void Clear() {
	edges.clear();
	for (int i=0; i<maxn; i++)
		G[i].clear();
}
// ========= END OF TEMPLATE =========

int main() {
	int N, M, S;
	cin >> N >> M >> S;
	for (int i=1; i<=M; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c); // directed
	}
	Spfa(S);
	for (int i=1; i<=N; i++) {
		printf("%d ", dis[i] == INF ? 2147483647 : dis[i]);
	}
	return 0;
}