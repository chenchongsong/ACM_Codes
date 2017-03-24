#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxn 60
int dp[maxn][maxn];
int cut[maxn];
int sum[maxn];
int main() {
	int n, l;
	while (scanf("%d", &l)!=EOF && l) {
		scanf("%d", &n);
		for (int i=1; i<=n; i++) {
			scanf("%d", &cut[i]);
		}
		cut[0] = 0;
		sort(cut+1, cut+n+1);
		sum[0] = 0;
		for (int i=1; i<=n; i++) {
			sum[i] = sum[i-1] + cut[i]-cut[i-1];

		}
		//n++;
		sum[++n] = l;
		
		memset(dp, 63, sizeof(dp));
		for (int i=n; i>=1; i--) {
			dp[i][i] = 0;
			for (int j=i+1; j<=n; j++) {
				for (int k=i; k<j; k++) {
					dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]);
				}
				dp[i][j] += sum[j]-sum[i-1];
			}
		}
		printf("The minimum cutting is %d.\n", dp[1][n]);
	}
	return 0;
}