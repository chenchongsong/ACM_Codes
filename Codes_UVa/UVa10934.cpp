/*
思路：类似于树形背包那题 发现楼层数很大 不可作为状态
f[i][j]: given i balls, try j times
how many floors can be determined

假设现在有i球和j次机会 第一次在mid层扔球 若球破了
则 向下可确定f[i-1][j-1]层(剩下i-1球 j-1次机会)

若球没破 向上可确定f[i][j-1]层
故而 f[i][j] = f[i-1][j-1]+ 1(mid层) +f[i][j-1];
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxball 110
#define maxtry 70
using namespace std;
long long dp[maxball][maxtry];
int main() {
	memset(dp, 0, sizeof(dp));
	for (int i=1; i<=105; i++)
		for (int j=1; j<=65; j++)
			dp[i][j] = dp[i-1][j-1]+ 1LL + dp[i][j-1];

	int k; long long n;
	while(scanf("%d%lld",&k,&n) && k) {
		int ans = 1;
		for (; ans<=63; ans++)
			if (dp[k][ans] >= n) {
				printf("%d\n", ans);
				break;
			}
		if (ans == 64) puts("More than 63 trials needed.");
	}
	return 0;
}