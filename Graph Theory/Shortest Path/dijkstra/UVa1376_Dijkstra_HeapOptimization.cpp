#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1010;
const int maxm = 3 * 1e6 + 10;
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

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int w) {
		edges.push_back(Edge(u, v, w));
		m = edges.size();
		G[u].push_back(m-1);
		edges.push_back(Edge(v, u, w));
		m = edges.size();
		G[v].push_back(m-1);
	}

	int dijkstra (int s, int e) {
		memset(vis, 0, sizeof(int) * n);
		memset(dis, inf, sizeof(int) * n);
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
		return dis[e];
	}
}solver;

int N, M, totNode, id[maxn * 2][maxn];

inline int ID (int x, int y) {
	if (y < 0 || x >= 2 * N - 2) return 0; // starting point
	if (x < 0 || y >= M - 1) return 1; // ending point
	int& t = id[x][y];
	if (t == 0) t = ++totNode;
	return t;
}

void init () {
	totNode = 1;
	memset(id, 0, sizeof(id));
	int w;

	solver.init(2 * (N-1)*(M-1) + 2);
	// here, we treat each triangle blank space as a Node
	// 0th row:     (0 0)   (0 1)
	// 0th row: (1 0)   (1 1)
	// 1th row:     (2 0)   (2 1)
	// 1th row: (3 0)   (3 1)

	// horizontal
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-1; j++) {
			scanf("%d", &w);
			int u = ID(2*i-1, j), v = ID(2*i, j);
			solver.addEdge(u, v, w);
		}
	}

	// vertical
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &w);
			int u = ID(2*i+1, j), v = ID(2*i, j-1);
			solver.addEdge(u, v, w);
		}
	}

	// diagonal
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < M-1; j++) {
			scanf("%d", &w);
			int u = ID(2*i, j), v = ID(2*i+1, j);
			solver.addEdge(u, v, w);
		}
	}
}

int main () {
	int kase = 0;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("Case %d: Minimum = %d\n", ++kase, solver.dijkstra(0, 1));
	}
	return 0;
}