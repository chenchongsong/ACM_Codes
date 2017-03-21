#include <cstdio>
#include <cstring>
//#include <algorithm>
#define maxn 210
int dp[maxn][maxn];
int a[maxn], id[maxn];
int N;
int max(int a, int b){return a>b?a:b;}

int main() {
	int T;
	scanf("%d", &T);
	for (int kase=1; kase<=T; kase++) {
		scanf("%d", &N);
		int cnt = 0, tmp;
		for (int i=1; i<=N; i++) {
			scanf("%d", &tmp);
			if (tmp != id[cnt]) {
				a[++cnt] = 1;
				id[cnt] = tmp;
			}
			else
				a[cnt]++;
		}
		for (int i=cnt; i>=1; i--) {
			dp[i][i] = a[i]*a[i];

			for (int j=i+1; j<=cnt; j++) {
				if (id[i]==id[j]) {
					dp[i][j] = dp[i+1][j-1]+(a[i]+a[j])*(a[i]+a[j]);
				}
				else {
					dp[i][j] = 0;
				}
				for (int k=i; k<j; k++) {
					dp[i][j] = max(dp[i][j], dp[i][k]+dp[k+1][j]);
				}
				//printf("%d--%d: %d\n", i,j , dp[i][j]);
			}
		}
		printf("Case %d: %d\n", kase, dp[1][cnt]);
	}
	return 0;
}