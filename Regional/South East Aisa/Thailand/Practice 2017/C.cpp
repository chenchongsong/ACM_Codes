#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define maxn 200005
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
int n, t, val[maxn];
int fa[maxn][5];
int fc[maxn][5];
int sc[maxn][5];
vector<int> G[maxn];
bool vis[maxn];
int ans;

void Clear() {
	memset(val, 0, sizeof(val));
	val[0] = -INF;
	for (int i=0; i<maxn; i++)
		G[i].clear();
	memset(vis, 0, sizeof(vis));
	memset(fa, 0, sizeof(fa));
	memset(fc, 0, sizeof(fc));
	memset(sc, 0, sizeof(sc));
	for (int i=1; i<=n; i++)
		fa[i][0] = fc[i][0] = sc[i][0] = i;

}
void dfs1(int u) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int i=0; i<G[u].size(); i++) {
		int v = G[u][i];
		if (!vis[v]) {
			dfs1(v);
			fa[v][1] = u;
		}
	}
}

void cal(int c1, int c2) {
	if (fa[c1][2] == c2 || fa[c2][2] == c1) return;
	ans = max(ans, val[c1] + val[c2]);
}
void update(int& c1, int& c2, int newc) {
	if (val[newc] >= val[c1]) {
		c2 = c1;
		c1 = newc;
		return;
	}
	if (val[newc] >= val[c2]) {
		c2 = newc;
	}
}
void dfs2(int u) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int i=0; i<G[u].size(); i++) {
		int v = G[u][i]; // for each son
		if (vis[v]) continue;
		dfs2(v);
		for (int k=1; k<=4; k++) {
			update(fc[u][k], sc[u][k], fc[v][k-1]);
		}
	}
	cal(fc[u][2], sc[u][2]); // 2 : 2

	cal(fc[u][3], fc[u][1]);
	cal(fc[u][3], sc[u][1]);
	cal(sc[u][3], fc[u][1]);
	cal(sc[u][3], sc[u][1]);
}

int main() {
	// freopen("Desktop/input-draft0.txt", "r", stdin);
	cin >> t;
	while (t--) {
		cin >> n;
		Clear();
		for (int i=1; i<=n; i++)
			scanf("%d", &val[i]);
		for (int i=1; i<n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		memset(vis, 0, sizeof(vis));
		dfs1(1);

		for (int k = 2; k <= 4; k++)
			for (int i=1; i<=n; i++)
				fa[i][k] = fa[ fa[i][k-1] ][1];

		ans = -1;
		for (int i=1; i<=n; i++) {
			if (fa[i][4] != 0) {
				ans = max(ans, val[i]+val[fa[i][4]]);
			}
		}
		memset(vis, 0, sizeof(vis));
		dfs2(1);

		cout << ans << endl;

	}
}

/*

2
8
110 100 10 110 7 100 15 30
1 2
2 5
5 3
5 4
4 7
7 6
7 8

1
7
1 2 5 4 4 6 7
1 2
1 3
2 4
2 5
3 6
4 7


*/
