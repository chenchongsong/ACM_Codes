struct State {
	int u, d;
	State (int u = 0, int d = 0): u(u), d(d){}
	bool operator < (const State& another) const { return d > another.d; }
};
void dijkstra (int s) {
	memset(vis, 0, sizeof(int) * n);
	memset(dis, inf, sizeof(int) * n);
	dis[s] = 0;
	priority_queue<State> que;
	que.push(State(s, dis[s]));
	while (!que.empty()) {
		int u = que.top().u; que.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = 0; i < G[u].size(); i++)
		{
			Edge& edge = edges[G[u][i]];
			int v = edge.v, w = edge.w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				que.push(State(v, dis[v]));
			}
		}
	}
}
