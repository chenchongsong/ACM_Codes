#include <cstdio>
#include <cstring>
using namespace std;
int dp[100010];
int a[100010];
int main() {
	int n, p;
	scanf("%d%d", &n, &p);
	for (int i=1; i<=n; i++) scanf("%d", &a[i]), a[i]-=p;
	int ans = 0;
	int cnt = 0;
	for (int i=1; i<=n; i++) {
		if (cnt < 0) cnt = 0;
		cnt += a[i];
		if (cnt > ans) ans = cnt;
	}
	printf("%d\n", ans);
	return 0;
}