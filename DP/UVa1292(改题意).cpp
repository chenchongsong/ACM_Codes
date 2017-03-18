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
int dp[maxn][3];
//[0] 自己和所有儿子都不放士兵 (father一定要放士兵)
//[1] 自己不放士兵 至少一个儿子有士兵
//[2] 自己有士兵
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
	//printf("now== %d\n", u);
	vis[u] = 1;
	dp[u][0] = 0;
	dp[u][1] = 0;
	dp[u][2] = 1;
	int flag = 0, delta = maxn; //INF
	for (int i=0; i<ed[u].size(); i++) {
		int v = ed[u][i];
		if (vis[v]) continue;
		dfs(v);
		//2
		dp[u][2] += min(min(dp[v][0], dp[v][1]), dp[v][2]);
		//0
		dp[u][0] += dp[v][1];
		//1
		if (dp[v][2] <= dp[v][1]) {
			flag = 1;
			dp[u][1] +=dp[v][2];
		}
		else {
			dp[u][1] += dp[v][1];
			delta = min(delta, dp[v][2]-dp[v][1]);
		}
	}
	if (!flag) dp[u][1] +=delta;
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
		for (int i=0; i<n; i++)
		{
			printf("%d--0:%d 1:%d 2:%d\n", i,dp[i][0],dp[i][1],dp[i][2]);
		}
		cout << min(dp[0][1], dp[0][2]) << endl;
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