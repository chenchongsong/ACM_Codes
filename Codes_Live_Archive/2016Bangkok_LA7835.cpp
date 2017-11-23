#include<cstdio>
#include<algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#define maxn 500010
#define maxlog 19
#define INF 0x3f3f3f3f
using namespace std;

vector<int> G[maxn];
int dep[maxn]; //在dfs树上的深度
int f[maxn][maxlog];
int size[maxn];
int below_lca;

void dfs(int u) {
	size[u] = 1;
	for (int i=1;i<maxlog;i++)
		f[u][i] = f[f[u][i-1]][i-1];

	for (int v : G[u]) {
		if (!dep[v]) {
			f[v][0]=u;
			dep[v] = dep[u] + 1;
			dfs(v);
			size[u] += size[v];
		}
	}
}

int LCA(int a,int b) { 
	if (dep[a]>dep[b]) swap(a,b); //保证b更深

	int bb = b; // a copy of b
	for (int i=maxlog-1;i>=0;i--)
		if (dep[f[bb][i]]>=dep[a]+1) {
			bb=f[bb][i];
		}
	// 将bb移动至深度dep[a]+1
	below_lca = bb;

	for (int i=maxlog-1;i>=0;i--)
		if (dep[f[b][i]]>=dep[a]) {
			b=f[b][i];
		}
	//将b移动至与a同一深度
	
	if (a==b) return a; //LCA=a=b
	
	for (int i=maxlog-1;i>=0;i--)
		if (f[a][i]!=f[b][i]) {
			a=f[a][i];
			b=f[b][i];
		}
	//向上找到LCA

	return f[a][0]; //LCA=f[a][0]-f[b][0]
}

void Clear() {
	for (int i=0; i<maxn; i++)
		G[i].clear();
	memset(dep, 0, sizeof(dep));
	memset(f, 0, sizeof(f));
	memset(size, 0, sizeof(size));
}

int main() {

	int tc, N, Q, root;
	cin >> tc;
	for (int kase=1; kase <= tc; kase++) {
		Clear();
		cin >> N >> Q >> root;
		for (int i=1; i<=N-1; i++) {
			int u, v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);		
		}
		// 单棵树
		if (!dep[root]) {
			dep[root] = 1; // 不能改为0
			dfs(root);
		}
		printf("Case #%d:\n", kase);
		for (int i=1; i<=Q; i++) {
			int opt, U;
			cin >> opt >> U;
			if (!opt) {
				root = U;
				continue;
			}
			// opt == 1
			if (U == root) {
				printf("%d\n", N);
				continue;
			}
			int tmp_lca = LCA(root, U);
			if (tmp_lca == root) {
				printf("%d\n", size[U]);
				continue;
			}
			if (tmp_lca == U) {
				printf("%d\n", N - size[below_lca]);
				continue;
			}
			// U -> tmp_lca -> root
			printf("%d\n", size[U]);
		}
	}
	return 0;
}