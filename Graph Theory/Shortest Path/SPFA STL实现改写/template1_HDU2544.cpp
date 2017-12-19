#include <cstdio>
#include <cstring>
#include <iostream>
#define maxn 110
using namespace std;
#include <vector>
#include <queue>

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
	int N, M;
	while (cin >> N >> M && N && M) {
		Clear();
		for (int i=1; i<=M; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			AddEdge(a, b, c);
			AddEdge(b, a, c);
		}
		Spfa(1);
		printf("%d\n", dis[N]);
	}
	return 0;
}
