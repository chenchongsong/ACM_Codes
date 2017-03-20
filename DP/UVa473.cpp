// dp[disk][j] 前disk张唱片 前j首歌
// 每次枚举一个i 意思是把第i~j首歌写进 第disk张唱片
// dp[disk][j] = max{ dp[disk-1][i-1]+seg[i][j]}
// O(n^2*(t+m))
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn 900
#define maxm 120
#define maxt 120
int dp[maxm][maxn];
int seg[maxn][maxn]; //seg[i][j] 记区间[i,j]内的歌最多能塞几首到一张光盘里
int bag[maxt];
int n, t, m;
int ti[maxn];

void Clear() {
	memset(ti, 0, sizeof(ti));
	memset(dp, 0, sizeof(dp));
	memset(seg, 0, sizeof(seg));
}
void Init() {
	Clear();
	scanf("%d%d%d", &n, &t, &m);
	scanf("%d", &ti[1]);
	for (int i=2; i<=n; i++)
		scanf(", %d", &ti[i]);

	for (int i=1; i<=n; i++) {
		memset(bag, 0, sizeof(bag));
		int ans = 0;
		for (int j=i; j<=n; j++) {
			for (int v=t; v>0; v--) {
				if (v>=ti[j]) {
					bag[v] = max(bag[v], bag[v-ti[j]]+1);
					ans = max(ans, bag[v]);
				}
			}
			seg[i][j] = ans;
			//printf("i--%d j--%d: %d\n",i,j,seg[i][j]);
		}
	}
}
void DP() {
	for (int disk=1; disk<=m; disk++)
		for (int j=1; j<=n; j++)
			for (int i=1; i<=j; i++)
				dp[disk][j] = max(dp[disk][j], dp[disk-1][i-1]+seg[i][j]);			
}

int main() {
	int T; cin >> T;
	for (int kase = 1; kase <= T; kase++) {
		Init();
		DP();
		if (kase != 1) puts("");
		printf("%d\n", dp[m][n]);
	}
	return 0;	
}
