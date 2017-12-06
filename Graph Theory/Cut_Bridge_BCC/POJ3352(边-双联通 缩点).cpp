// 先求出边-双连通分量（low[i]值相同的点属于同一个边双连通分量.)
// 然后把边双连通分量缩点，得到一个无向连通图
// 那么这时最少加几条边才能构成边双连通图呢？
// 有个结论：对于一棵无向树,我们要使得其变成边双连通图
// 需要添加的边数 == (树中度数为1的点的个数+1)/2

// 实现：如何求边双联通分量？
// 找到所有的桥 打上标记
// 然后再对全图进行dfs（不走桥
// 每一次dfs都意味着有一个新的边－双联通分量

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
#define MAXN 100011
#define ms(x) memset(x, 0, sizeof(x))

struct Edge{
	int from, to, isbridge;
	Edge(int a, int b, int c){from=a;to=b;isbridge=c;}
};

vector<int> G[MAXN];
vector<Edge> edges;

int low[MAXN], pre[MAXN], dfs_clock=0;
int bccno[MAXN], bcc_cnt=0;

int deg[MAXN];
bool vis[MAXN];

void AddEdge(int a, int b) {
	edges.push_back(Edge(a, b, false));
	G[a].push_back(edges.size()-1);
	edges.push_back(Edge(b, a, false));
	G[b].push_back(edges.size()-1);
}

void dfs(int u, int fa) {
	low[u] = pre[u] = ++dfs_clock;
	for (int i=0; i<G[u].size(); i++) {
		Edge& e = edges[G[u][i]];
		int v = e.to;
		if (!pre[v]) {
			dfs(v,u);
			low[u] = min(low[u], low[v]);
			if (low[v] > pre[u]) {
				e.isbridge = true;
				edges[G[u][i] ^ 1].isbridge = true;
			}
		}
		else if( pre[u] > pre[v] && v!=fa ) {
			low[u] = min(low[u],pre[v]);
		}
	}
}

void dfs2(int u) {
	vis[u] = true;
	bccno[u] = bcc_cnt;
	for (int i=0; i<G[u].size(); i++) {
		Edge& e = edges[G[u][i]];
		int v = e.to;
		if (vis[v]) continue;
		if (e.isbridge) continue;
		dfs2(v);
	}
}
inline void read(int &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = getchar());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = getchar());
}
int main() {
	int n, m;
	read(n); read(m);

	int a, b;
	for (int i=1; i<=m; i++) {
		read(a); read(b);
		AddEdge(a, b);
	}
		
	for(int i = 1; i <= n; i++)
		if(!pre[i])
			dfs(i, -1);

	for (int i=1; i<=n; i++) {
		if (!vis[i]) {
			bcc_cnt++;
			dfs2(i);
		}
	}

	for (int i=1; i<=n; i++) {
		for (int j=0; j<G[i].size(); j++) {
			int to = edges[G[i][j]].to;
			if (bccno[i] != bccno[to]) // bridge: i -- to
				deg[bccno[to]]++;
			// 由于是双向边
			// 每次deg只改一个端点
			// 另一个端点的deg之后总会被+1
		}
	}

	int cnt1 = 0;
	for (int i=1; i<=bcc_cnt; i++)
		cnt1 += (deg[i] == 1);

	cout << (cnt1 + 1) / 2 << endl;

	return 0;
}