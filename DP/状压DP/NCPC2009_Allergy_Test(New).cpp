// 这题卡常数啊QAQ
// 不能用递归
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[1<<20][8];
bool vis[1<<20][8];
// dp[S][t] 表示排下的allergy集合为S, 最后t天内只有某一个allergy还active
// 完成S的最少时间
int K, D[20];

// int DP(int S, int t) {
// 	if (S == 0 && t == 0) return 0;
// 	if (S == 0 || t == 0) return INF;
// 	if (vis[S][t]) return dp[S][t]; // visited
// 	vis[S][t] = true;
	
// 	int& res = dp[S][t];

// 	for (int i=0; i<K; i++) {
// 		if (S & (1<<i)) {
// 			if (D[i] < t) continue;
// 			if (D[i] == t) {
// 				for (int old_t = 0; old_t<=7; old_t++)
// 					res = min(res, DP(S-(1<<i), old_t) + t);
// 				continue;
// 			}
// 			for (int old_t = 7; old_t>=0; old_t--) {
// 				if (old_t + t - 1 >= D[i])
// 					res = min(res, DP(S-(1<<i),old_t) + t);
// 				else
// 					break;
// 			}
// 		}
// 	}
// 	// printf("S== %d t == %d dp[][] == %d\n",S,t,dp[S][t]);
// 	return res;
// }

int main() {
	cin >> K;
	for (int i=0; i<K; i++) cin >> D[i];
	memset(dp, 63, sizeof(dp));

	dp[0][0] = 0;
	for (int S = 1; S < (1<<K); S++)
	for (int t = 1; t <= 7; t++)
		for (int i=0; i<K; i++) {
			if (S & (1<<i)) {
				if (D[i] < t) continue;
				if (D[i] == t) {
					for (int old_t = 0; old_t<=7; old_t++)
						dp[S][t] = min(dp[S][t], dp[S-(1<<i)][old_t] + t);
					continue;
				}
				for (int old_t = 7; old_t>=0; old_t--) {
					if (old_t + t - 1 >= D[i])
						dp[S][t] = min(dp[S][t], dp[S-(1<<i)][old_t] + t);
					else
						break;
				}
			}
		}

	int Ans = INF;
	for (int t = 1; t <= 7; t++)
		Ans = min(Ans, dp[(1<<K)-1][t]);
	
	cout << Ans << endl;
	return 0;
}
