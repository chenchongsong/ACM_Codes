#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 260
using namespace std;
int dp[maxn][maxn], fre[maxn], sum[maxn];
int main() {
	int n;
	while (scanf("%d", &n)==1) {
		sum[0]=0;
		for (int i=1; i<=n ;i++) {
			scanf("%d", &fre[i]);
			sum[i] = sum[i-1] + fre[i];
		}
		memset(dp, 63, sizeof(dp));
		for (int i=n; i>=1; i--) {
			dp[i][i]=0;
			for (int j=i+1; j<=n; j++) {
				dp[i][j]=min(dp[i+1][j]+sum[j]-sum[i], dp[i][j-1]+sum[j-1]-sum[i-1]);
				// init: min(node i has no left subtree/ no right subtree)
				for (int k=i+1; k<j; k++)
					dp[i][j]=min(dp[i][j], dp[i][k-1]+dp[k+1][j]+(sum[j]-sum[i-1]-fre[k]));
			}
		}
		printf("%d\n", dp[1][n]);
	}
	return 0;
}