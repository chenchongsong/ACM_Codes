#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 110
using namespace std;
int dp[maxn];
struct gangster {
	int t, p, s;
	bool operator < (const gangster& next) const {
		return t < next.t;
	}
} a[maxn];
int Abs(int x) {return x>0?x:-x;}
int main() {
	int Case, n, k, totTime;
	scanf("%d", &Case);
	for (int kase = 1; kase <= Case; kase++) {
		scanf("%d%d%d", &n, &k, &totTime);
		for (int i=1; i<=n; i++) scanf("%d", &a[i].t);
		for (int i=1; i<=n; i++) scanf("%d", &a[i].p);
		for (int i=1; i<=n; i++) scanf("%d", &a[i].s);
		sort(a+1, a+n+1);

		memset(dp, 128+63, sizeof(dp));//fill (dp, dp+maxn, -999999999);
		dp[0] = 0;
		a[0].s = a[0].t = 0;
		int ans = 0;
		for (int i=1; i<=n; i++) {
			for (int j=0; j<i; j++) {
				//notice: if a[i].t==a[j].t && a[i].s==a[j].s
				//then both are acceptable
				if (Abs(a[i].s-a[j].s) <= Abs(a[i].t-a[j].t))
					dp[i] = max(dp[i], dp[j]+a[i].p);
			}
			ans = max(ans, dp[i]);
		}
		if (kase != 1) puts("");
		printf("%d\n", ans);

	}
	return 0;
}