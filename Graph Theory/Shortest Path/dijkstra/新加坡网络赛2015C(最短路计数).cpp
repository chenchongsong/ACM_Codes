#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 20005;
const int maxm = 400005;
const int inf = 0x3f3f3f3f;

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
	int cnt[maxn];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int w) {
		edges.push_back(Edge(u, v, w));
		m = edges.size();
		G[u].push_back(m-1);
	}

	int dijkstra (int s, int e) {
		memset(vis, 0, sizeof(int) * n);
		memset(dis, inf, sizeof(int) * n);
		dis[s] = 0;
		cnt[s] = 1;

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
					cnt[v] = cnt[u];
					que.push(State(v, dis[v]));
				}
				else if (dis[v] == dis[u] + w)
					cnt[v] += cnt[u];
			}
		}
		return dis[e];
	}
}solver;

int N, M, totNode;


void init () {
	totNode = 1;

	solver.init(N + 1);

	for (int i=1; i<=M; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		solver.addEdge(a, b, c);
	}
	int S, T;
	cin >> S >> T;
	solver.dijkstra(S, T);

	cout << solver.cnt[T] << endl;

}

int main () {
	scanf("%d%d", &N, &M);
	init();

	return 0;
}