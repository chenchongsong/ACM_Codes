#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#define MaxN 50010
#define MaxM 100010
using namespace std;

// int top, cnt, tmp, stack[MaxN];
int dfs_clock = 0, pre[MaxN],low[MaxN];
int scc_cnt, sccno[MaxN], size[MaxN];
stack<int> S;
vector<int> G[MaxN], G2[MaxN];

int size_enemy[MaxN];
bool is_enemy[MaxN];
bool is_safe[MaxN];

void Add(int a,int b) {G[a].push_back(b);}
void Add2(int a, int b) {G2[a].push_back(b);}

void dfs(int u) {
	pre[u] = low[u] = ++dfs_clock;
	S.push(u);
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]); 
		}
		else if (!sccno[v]) 
			low[u] = min(low[u],pre[v]);
	}
	if (low[u] == pre[u]) {
		scc_cnt++;
		int original_size = S.size(), tmp = 0;
		do {
			tmp = S.top();
			S.pop();
			sccno[tmp] = scc_cnt;
		} while (tmp != u);
		size[scc_cnt] = original_size - S.size();
	}
}

int main() {
	int n, m, e;
	scanf("%d%d%d",&n, &e, &m);
	for (int i=1;i<=m;i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		Add(a,b);
	}
	for (int i=1; i<=e; i++) {
		int tmp_enemy;
		scanf("%d", &tmp_enemy);
		is_enemy[tmp_enemy] = true;
	}

	// build scc
	// node indexed from 0 ~ n-1
	for (int i=0; i<n; i++)
		if (!pre[i])
			dfs(i);

	for (int i=0; i<n; i++) {
		if (is_enemy[i])
			size_enemy[sccno[i]]++;
		// printf(" node%d belongs to %d\n",i,sccno[i]);
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<G[i].size(); j++) { // for each original edge
			int to = G[i][j];
			if (sccno[i] != sccno[to])
				Add2(sccno[to], sccno[i]); // Add edge reversely to create a new graph
		}
	}

	queue<int> Q;
	memset(is_safe, 1, sizeof(is_safe));

	// Q initialisation
	for (int i=1; i<=scc_cnt; i++) {
		if (size_enemy[i] > 0) {
			is_safe[i] = false;
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int Qhead = Q.front();
		Q.pop();
		for (int i=0; i<G2[Qhead].size(); i++) {
			int to = G2[Qhead][i];
			if (is_safe[to]) {
				is_safe[to] = false;
				Q.push(to);
			}
		}
	}

	int Ans = 0;
	for (int i=1; i<=scc_cnt; i++) {
		if (is_safe[i]) {
			bool no_safe_out = true;
			// whether this scc can directly reach other "safe" scc
			for (int j=0; j<G2[i].size(); j++) {
				if (is_safe[G2[i][j]]) {
					no_safe_out = false;
					break;
				}
			}
			Ans += no_safe_out;
		}
		else
			Ans += size[i]-size_enemy[i];
			// inform each non-enemy spy in this scc using private message
	}

	printf("%d\n",Ans);
	return 0;
}
