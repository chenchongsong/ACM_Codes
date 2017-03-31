#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 510
using namespace std;
int dp[maxn][maxn];
int main() {
	int T, n, delta;
	scanf("%d", &T);
	for (int kase=1; kase<=T; kase++) {
		scanf("%d%d", &n, &delta);
		for (int i=n; i>=1; i--) {
			dp[i][i] = 0;
			for (int j=i+1; j<=n; j++) {
				dp[i][j] = min(dp[i+1][j]+(i+delta)*(j-i+1), dp[i][j-1]+(j+delta)*(j-i+1));
				// min(吃第i个, 吃第j个)
				for (int k=i+1; k<j; k++)
				dp[i][j] = min(dp[i][j],
					dp[i][k-1]+dp[k+1][j]+(k+delta)*(j-i+1));
			}
		}
		printf("Case %d: %d\n", kase, dp[1][n]);
	}
	return 0;
}
