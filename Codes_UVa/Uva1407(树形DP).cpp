#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define maxn 510
using namespace std;
int dp[maxn][maxn][2], n;
// dp[u][j][0]: 遍历子树u的j个节点 然后回到u点 最少要走的距离
// dp[u][j][1]: 不用回到u点
// 模型：树形DP 每个节点u相当于一个背包问题 j相当于背包容量 最少要走的距离相当于val总和
vector<int> ed[maxn], cost_ed[maxn];
bool vis[maxn];
int size[maxn]; //size[i] 表示以i为节点的子树大小
void Clear() {
	memset(dp, 63, sizeof(dp));
	memset(vis, 0, sizeof(vis));
	memset(size, 0, sizeof(size));
	for (int i=0; i<n; i++) {
		ed[i].clear();
		cost_ed[i].clear();
	}
}

void dfs(int u) {
	size[u] = 1;
	dp[u][1][0] = dp[u][1][1] = 0;

	for (int i=0; i<(int)ed[u].size(); i++) {
		int v = ed[u][i];
		int w = cost_ed[u][i];
		dfs(v);
		size[u] += size[v];

		for (int j=size[u]; j>=2; j--) //只能取一次 0/1背包 故j倒过来枚举
			for (int k=1; k<=min(j,size[v]); k++) {
				dp[u][j][0]=min(dp[u][j][0], dp[v][k][0]+dp[u][j-k][0]+w*2);
				dp[u][j][1]=min(dp[u][j][1], dp[v][k][0]+dp[u][j-k][1]+w*2);
				dp[u][j][1]=min(dp[u][j][1], dp[v][k][1]+dp[u][j-k][0]+w);
			}
	}
}
//dfs复杂度 O(n^2状态 * 转移n(枚举k)) = O(n^3)
//枚举儿子节点v=ed[u][i] 均摊下来这一维O(1) 所以不算数

int main() {
	int kase = 0;
	while (scanf("%d", &n)!=EOF && n) {
		Clear();
		int u, v, val;
		for (int i=1; i<n; i++) {
			scanf("%d%d%d", &u, &v, &val);
			ed[v].push_back(u);
			cost_ed[v].push_back(val);
		}
		dfs(0);

		printf("Case %d:\n", ++kase);
		int Q, x;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d", &x);
			for (int ans=n; ans; ans--)
				if (dp[0][ans][1] <= x) {
					printf("%d\n", ans);
					break;
				}
		}
	}
	return 0;
}