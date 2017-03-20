// f[i][j][k] 前i张唱片 前j首歌 第i张已经用了"<=k分钟" (不是恰好k分钟)
// 三种决策 1.不选j这首歌 2.把第j首歌是第i个光盘的第一首 3.j不是光盘i的第一首
// f[i][j][k] = max(f[i][j-1][k], f[i-1][j-1][t]+1, f[i][j-1][k-ti[j]]+1);
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn 900
#define maxm 120
#define maxt 120
int dp[maxm][maxn][maxt];
int n, t, m, ans;
int ti[maxn];

void Clear() {
	memset(ti, 0, sizeof(ti));
	memset(dp, 0, sizeof(dp));
}

int main() {
	int T; cin >> T;
	for (int kase = 1; kase <= T; kase++) {
		Clear();
		scanf("%d%d%d", &n, &t, &m);
		scanf("%d", &ti[1]);
		for (int i=2; i<=n; i++)
			scanf(", %d", &ti[i]);
		for (int i=1; i<=m; i++)
			for (int j=1; j<=n; j++)
				for (int k=0; k<=t; k++) {
					dp[i][j][k] = dp[i][j-1][k];
					if (ti[j] <= k) {
						dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k-ti[j]]+1);
						dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][t]+1);
					}
					//printf("i--%d j--%d k--%d : %d ans== %d\n", i,j,k,dp[i][j][k],ans);
				}
		if (kase != 1) puts("");
		printf("%d\n", dp[m][n][t]);
	}
	return 0;	
}
