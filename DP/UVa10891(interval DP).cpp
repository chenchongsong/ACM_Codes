#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[110];
int sum[110];
int dp[110][110];
int n;
int main() {
	while (scanf("%d", &n)!=EOF && n) {
		sum[0] = 0;
		for (int i=1; i<=n; i++) {
			cin >> a[i];
			dp[i][i] = a[i];
			sum[i] = sum[i-1] + a[i];
		}
		for (int len = 2; len<=n; len++) {
			for (int i=1; i<=n; i++) {
				int j = i + len - 1;
				if (j > n) break;
				dp[i][j] = sum[j]-sum[i-1];
				for (int k = i+1; k<=j; k++) {
					dp[i][j] = max(dp[i][j], sum[k-1]-sum[i-1]-dp[k][j]);
				}
				for (int k = i; k<j; k++) {
					dp[i][j] = max(dp[i][j], sum[j]-sum[k]-dp[i][k]);
				}
			}
		}
		cout << dp[1][n] << endl;
	}
	return 0;
}