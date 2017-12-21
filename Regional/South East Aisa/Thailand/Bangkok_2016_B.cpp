#include <cstdio>
#include <iostream>
#include <algorithm>
#define MOD 1000000007
#define ll long long
using namespace std;
int n, full;
int f[205][60][60*205];
int g[205][60*205];
// f[i-1][sum] + f[i-1][sum-1] + ... + f[i-1][sum-full]

void add(int& a, int b) {
	a = ( (a+b) % MOD + MOD ) % MOD;
}
int main() {
	for (int full = 1; full <= 200; full++) {
	// full = 3; {
		f[full][0][0] = 1;
		g[full][0] = 1;
		for (int i=1; i<=60; i++) {
			f[full][i][0] = 1;
			for (int sum = 1; sum <= i * full; sum++) {
				
				f[full][i][sum] = g[full][min(sum, (i-1)*full)];
				
				if (sum - full - 1 >= 0)
					add(f[full][i][sum], -g[full][sum-full-1]);
				
				// printf("f[%d][%d] == %d\n", i, sum, f[full][i][sum]);
				
			}
			for (int sum = 1; sum <= i * full; sum++) {
				g[full][sum] = (g[full][sum-1] + f[full][i][sum]) % MOD;
			}
		}
	}
	// puts("OK");
	while (1) {
		scanf("%d%d", &n, &full);
		if (!n && !full) break;
		ll cnt = 0;
		for (int avg = 0; avg <= full; avg++) {
			cnt += (ll)f[full][n-1][avg * (n-1)];
		}
		cnt = (cnt * n) % MOD;

		printf("%d\n", (int)cnt);
	}
	return 0;
}

