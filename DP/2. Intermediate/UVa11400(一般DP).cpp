#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1010
using namespace std;
struct light {
	int v, k, c, l;
	bool operator < (const light& b) const {
		return v > b.v;
	}
} a[maxn];
int dp[maxn], dpHas[maxn], sum[maxn];
int main() {
	int n;
	while (scanf("%d",&n) && n) {
		for (int i=1; i<=n; i++)
			scanf("%d%d%d%d",&a[i].v,&a[i].k,&a[i].c,&a[i].l);
		sort(a+1, a+n+1);

		sum[0] = 0;
		for (int i=1; i<=n; i++)
			sum[i] = sum[i-1] + a[i].l;
		memset(dp, 63, sizeof(dp));
		dp[0] = 0;

		for (int i=1; i<=n; i++) {
			dpHas[i] = dp[i-1] + a[i].c*a[i].l + a[i].k;
			dp[i] = dpHas[i];
			
			for (int j=1; j<i; j++)
				dp[i] = min(dp[i], dpHas[j]+a[j].c * (sum[i]-sum[j]));
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}