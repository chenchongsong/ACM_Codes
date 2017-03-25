#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 4020
#define INF 0x3f3f3f3f
using namespace std;
int dp[maxn];
int a[maxn], g[maxn];
int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		memset(dp, 0, sizeof(dp));
		scanf("%d", &n);
		for (int i=n+1; i<=2*n; i++)
			scanf("%d", &a[i]);
		for (int i=1; i<=n; i++)
			a[i] = a[n*2-i+1];
		n *= 2;

		for (int i=2;i<=n+1;i++) g[i]=INF;
		int Ans = 0;
		for (int i=1;i<=n;i++)
		{
			int k=lower_bound(g+2, g+n+2, a[i]) - g;
			dp[i] = k-1; //  以A[i]结尾的LIS长度
			Ans = max(Ans, dp[i]);
			g[k] = a[i];
		}
		printf("%d\n", Ans);
	}
	return 0;
}