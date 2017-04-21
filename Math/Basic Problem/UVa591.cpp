#include <cstdio>
int h[100], ave, sum, ans, kase = 0, n;
int main() {
	while (scanf("%d", &n) && n) {
		sum = ans = 0;
		for (int i=1; i<=n; i++) {
			scanf("%d", &h[i]);
			sum += h[i];
		}
		ave = sum/n;
		for (int i=1; i<=n; i++) {
			if (h[i]>ave) ans += h[i]-ave;
		}
		printf("Set #%d\nThe minimum number of moves is %d.\n\n", ++kase,ans);

	}
	return 0;
}