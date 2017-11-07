#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#define maxn 5010
#define maxk 5010
#define maxs 5010
using namespace std;
int dp[maxk][maxs]; // dp[i][j]: 前i组 sum为j 最小修改数
int N, K, S;
map<int, int> cnt[maxk]; // cnt[i][j]: 第i组中一共有多少个数值为j的
int tot_cost[maxk]; // 说明第i组一共 tot_cost[i] 个数
int a[maxn];
int main () {
	cin >> N >> K >> S;
	for (int i=1; i <= N; i++) {
		scanf("%d", &a[i]);
	}
	for (int i=1; i <= N; i++) {
		int pos = (i-1) % K + 1; // 分成 1 ~ K 一共 K 组
		cnt[pos][a[i]] = cnt[pos][a[i]] + 1;
		tot_cost[pos]++;
	}
	memset(dp, 63, sizeof(dp));
	dp[0][0] = 0;
	for (int i=1; i<=K; i++) {
		int min_prev = dp[i-1][0];
		for (int j=0; j<=S; j++) {
			min_prev = min(min_prev, dp[i-1][j]);
			dp[i][j] = min_prev + tot_cost[i]; // 用cnt[i]里面不存在的数
			
			for (map<int, int>::iterator it=cnt[i].begin();it!=cnt[i].end();++it) {
				if (j - it->first < 0) break;
				dp[i][j] = min(dp[i][j], dp[i-1][j - it->first] + tot_cost[i]-it->second);
			}
		}
	}
	// for (int i=1; i<=K; i++) {
	// 	for (int j=0; j<=S; j++) {
	// 		printf("cnt[%d] == %d\n", j, cnt[i][j]);
	// 	}
	// 	for (int j=0; j<=S; j++) {
	// 		printf("i %d  j%d : %d\n", i,j,dp[i][j]);
	// 	}
	// }
	printf("%d\n", dp[K][S]);
	return 0;
}

// Notes
// 关于为什么不会T的一点猜想
// 看起来是O(K * S * (N/K))
// 所以是O(N * S) 可以过