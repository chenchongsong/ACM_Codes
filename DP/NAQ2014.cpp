#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
int n, k;
int v[400][2];
int dp[400][400][3];
// [0]: close first room
// [1]: close second room
// [2]: close neither

int main() {
	scanf("%d%d", &n, &k);
	for (int i=1; i<=n+1; i++) {
		scanf("%d%d", &v[i][0], &v[i][1]);
	}
	
	memset(dp, 128, sizeof(dp)); // -INF
	dp[0][0][2] = 0;
	
	for (int i=1; i<=n; i++) { // 前i行
		// special case: j == 0
		dp[i][0][2] = dp[i-1][0][2] + v[i][0] + v[i][1];
		
		for (int j=1; j <= min(i, k); j++) { // 关掉j间
			dp[i][j][0] = max(dp[i-1][j-1][0], dp[i-1][j-1][2]) + v[i][1];
			dp[i][j][1] = max(dp[i-1][j-1][1], dp[i-1][j-1][2]) + v[i][0];

			dp[i][j][2] = max(dp[i-1][j][0], dp[i-1][j][1]) + v[i][0] + v[i][1];
			dp[i][j][2] = max(dp[i][j][2], dp[i-1][j][2] + v[i][0] + v[i][1]);
		}
	}

	// for (int i=1; i<=n; i++) {
	// 	for (int j=0; j<=k; j++) {
	// 		printf("i%d j%d : dp %d %d %d\n",i,j,dp[i][j][0],dp[i][j][1],dp[i][j][2]);
	// 	}
	// }

	int ans = 0;
	ans = max(dp[n][k][0], dp[n][k][1]);
	ans = max(ans, dp[n][k][2]);
	printf("%d\n", ans);
	return 0;
}