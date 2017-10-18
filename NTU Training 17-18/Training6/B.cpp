#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define maxn 300010
using namespace std;
int n, m;
int deg[maxn];
int belong[maxn]; // which group ith soldier in
vector<int> G[maxn];
queue<int> Q;

bool conflict(int x) {
	int count = 0; // count enermy in the same group
	for (int j=0; j<G[x].size(); j++)
		count += (belong[x]==belong[G[x][j]]?1:0);
	return count > 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i=1; i<=m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u == v) continue;
		bool hasRep = false;
		for (int j=0; j<G[u].size(); j++) {
			if (G[u][j] == v)
				hasRep = true;
		}
		if (hasRep) continue;
		deg[u]++;
		deg[v]++;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bool canOneGroup = true;
	for (int i=1; i<=n; i++) {
		if (deg[i] > 1) {
			canOneGroup = false;
			break;
		}
	}
	if (canOneGroup) {
		printf("1\n");
		for (int i=1; i<=n; i++)
			printf("%d ", i);
		return 0;
	}

	// otherwise, can be divied into 2 groups (0/1)
	// initially all soldiers in group 0
	memset(belong, 0, sizeof(belong));

	for (int i=1; i<=n; i++)
		if (conflict(i))
			Q.push(i);

	while (!Q.empty()) {
		int Qhead = Q.front();
		Q.pop();
		if (!conflict(Qhead)) continue;
		belong[Qhead] ^= 1; // change to the other group
		for (int j=0; j<G[Qhead].size(); j++) {
			int next = G[Qhead][j];
			if (conflict(next))
				Q.push(next);
		}
	}
	puts("2");
	for (int i=1; i<=n; i++) {
		if (!belong[i])
			printf("%d ", i);
	}
	puts("");
	for (int i=1; i<=n; i++) {
		if (belong[i])
			printf("%d ", i);
	}
	return 0;
}
