// ========== 费用流 ==========
// O(SPFA_const * M * MAXFLOW)
// random Graph: n=250 m=5000 con[i]<=10000: 0.85s
struct Edge {int from, to, cap, cost;};
vector<Edge> edges;
vector<int> G[maxn];
int S, T, ansflow;
ll anscost;
int dis[maxn], path[maxn];
bool vis[maxn];

void Add(int from, int to, int cap, int cost) {
	edges.push_back((Edge){from,to,cap,cost});
    edges.push_back((Edge){to,from,0,-cost});
    int m0 = edges.size();
    G[from].push_back(m0-2);
    G[to].push_back(m0-1);
}
bool spfa() {
	memset(dis, 63, sizeof(dis));
	memset(vis, 0,sizeof(vis));
	queue<int> q;
	q.push(S); dis[S]=0; vis[S]=1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i=0; i<G[u].size(); i++) {
			Edge& e = edges[G[u][i]];
			int v = e.to;
			if(e.cap && dis[v] > dis[u]+e.cost) {
				dis[v] = dis[u]+e.cost;
				path[v] = G[u][i];
				if(!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			} 
		} 
		vis[u] = 0;
	}
	return dis[T]<INF; //0x3f3f3f3f
}
void CostFlow() {
	ansflow = anscost = 0;
	memset(path, 0, sizeof(path));
	while (spfa()) {
		int f=INF;
		for(int x=T;x!=S;x=edges[path[x]].from)
			f = min(f,edges[path[x]].cap);
		for(int x=T;x!=S;x=edges[path[x]].from) {
			edges[path[x]].cap -= f;
			edges[path[x]^1].cap += f;
		}
		anscost += (ll)dis[T]*(ll)f;
		ansflow += f;
	}
}
// cin>>S>>T; CostFlow();
// printf("%d %lld\n",ansflow,anscost);
