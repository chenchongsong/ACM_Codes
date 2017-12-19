#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#define maxn 40000
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

int button[maxn];

int main() {
	int TC, N, tar;
	cin >> TC;
	while (TC--) {
		Clear();
		cin >> N >> tar;
		for (int i=1; i<=N; i++) {
			cin >> button[i];
			for (int t = 0; t <= 3600; t++) {
				int to = t + button[i];
				if (to < 0) to = 0;
				if (to > 3600) to = 3600;
				AddEdge(t, to, 1);
			}
		}
		Spfa(0);
		for (int t=tar; t<=3600; t++) {
			if (dis[t] < INF) {
				printf("%d %d\n", dis[t], t-tar);
				break;
			} 
		}
	}
	return 0;
}