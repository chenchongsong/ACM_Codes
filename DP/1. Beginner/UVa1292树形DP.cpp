//坑爹刘汝佳 题意都搞不清楚
//按训练指南p96的题意 一个点可以覆盖与之相邻的点 求把所有点都覆盖的最小代价
//有些边是不用被覆盖的
//然而UVaOJ愿意为：一个点个可以覆盖与之相邻的边 求把所有边都覆盖的最小代价
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define maxn 1600
using namespace std;
int dp[maxn][2];
//[0] 该点不放士兵
//[1] 该点放士兵
bool vis[maxn];
vector <int> ed[maxn];
void Clear() {
	memset(dp, 0, sizeof(dp));
	memset(vis, 0, sizeof(vis));
	for (int i=0; i<=1550; i++) {
		ed[i].clear();
	}
}
void dfs(int u) {
	vis[u] = 1;
	dp[u][0] = 0;
	dp[u][1] = 1;
	for (int i=0; i<ed[u].size(); i++) {
		int v = ed[u][i];
		if (vis[v]) continue;
		dfs(v);
		dp[u][1] += min(dp[v][0], dp[v][1]);
		dp[u][0] += dp[v][1];
	}
}

int main() {
	int n;
	while (cin>>n) {
		Clear();
		for (int i=1; i<=n; i++) {
			int u, v, num;
			scanf("%d", &u);
			getchar(); getchar();
			scanf("%d", &num); getchar();
			for (int j=1; j<=num; j++) {
				scanf("%d", &v);
				ed[u].push_back(v);
				ed[v].push_back(u);
			}
		}
		dfs(0);
		cout << min(dp[0][0], dp[0][1]) << endl;
	}
}
/*

6
0:(1) 1
1:(1) 2
2:(1) 3
3:(1) 4
4:(1) 5
5:(0)

*/