// directed graph
// STL
// 624ms
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 2000010;
const int maxm = 2000010;
const int INF = 0x3f3f3f3f;

struct Dijkstra {
	struct Edge {
		int u, v, w;
		Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	};

	struct State {
		int u, d;
		State (int u = 0, int d = 0): u(u), d(d) {}
		bool operator < (const State& another) const { return d > another.d; }
	};

	int n, m, dis[maxm], vis[maxm];
	vector<Edge> edges;
	vector<int> G[maxm];

	void init (int n) {
		n += 3; // make sure correctness
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int w) { // directed
		edges.push_back(Edge(u, v, w));
		m = edges.size();
		G[u].push_back(m-1);
	}

	void dijkstra (int s) {
		memset(vis, 0, sizeof(int) * n);
		memset(dis, INF, sizeof(int) * n);
		dis[s] = 0;

		priority_queue<State> que;
		que.push(State(s, dis[s]));

		while (!que.empty()) {
			int u = que.top().u;
			que.pop();

			if (vis[u]) continue;
			vis[u] = 1;

			for (int i = 0; i < G[u].size(); i++) {
				Edge& edge = edges[G[u][i]];
				int v = edge.v, w = edge.w;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					que.push(State(v, dis[v]));
				}
			}
		}
	}
}solver;

int N, M, S;

int main () {
	cin >> N >> M >> S;
	solver.init(N+1); // 0 ~ N
	for (int i=1; i<=M; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		solver.addEdge(a, b, c);
	}
	solver.dijkstra(S);

	for (int i=1; i<=N; i++) {
		printf("%d ", solver.dis[i] == INF ? 2147483647 : solver.dis[i]);
	}

	return 0;
}