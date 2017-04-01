// from http://97littleleaf11.xyz/oi/mobius/
#include <cstdio>
#include <algorithm>
#define maxnum 50010
using namespace std;
int A, B, C, D, k, ptot;
int mu[maxnum], sum[maxnum], pri[maxnum], vis[maxnum];

void get() { // get mu[]: mobius function
	int i, j;
	mu[1] = 1;
	for (i = 2; i <= 50000; i++) {
		if (!vis[i]) {
			pri[++ptot] = i;
			mu[i] = -1;
		}
		for (j = 1; j <= ptot && i * pri[j] <= 50000; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			}
			else mu[i * pri[j]] = -mu[i];
		}
	} 
	for (i = 1; i <= 50000; i++)
		sum[i] = sum[i - 1] + mu[i];
}

int cal(int n, int m) {
	n /= k; // in the blog:: a' = a/D
	m /= k; // in the blog:: b' = b/D
	int i, j, ans = 0;
	for (i = 1; i <= min(n, m); i = j + 1) {
	// i:: the iterator k in the blog
		j = min(n / (n / i), m / (m / i));
		// i~j :: if i<=k<=j,
		// trunc(n/k)==trunc(n/i), trunc(m/k)==trunc(m/i)
		ans += (sum[j] - sum[i - 1]) * (n / i) * (m / i);
	}
	return ans;
}

int main() {
	int T;
	get();
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d", &A, &B, &C, &D, &k);
		printf("%d\n", cal(B, D)-cal(A-1, D)-cal(B, C-1)+cal(A-1, C-1));
	}
	return 0;
}