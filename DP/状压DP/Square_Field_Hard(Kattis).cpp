#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF 1e6
using namespace std;

int T, n, k;
int x[17], y[17];
int dp[1<<17]; // minimum square needed to cover the set
int onelen[1<<17]; // length needed to cover the set with one square

void Init_Onelen() {
	memset(onelen, 0, sizeof(onelen));
	onelen[0] = 0;
	for (int S = 1; S < (1<<n); S++) {
		int minx = INF, miny = INF;
		int maxx = -1, maxy = -1;
		for (int i = 0; i < n; i++) {
			if ((S & (1<<i)) == 0) continue;
			minx = min(minx, x[i]);
			maxx = max(maxx, x[i]);
			miny = min(miny, y[i]);
			maxy = max(maxy, y[i]);
		}
		onelen[S] = max(maxx-minx, maxy-miny);
		// printf("len[%d] == %d\n",S,onelen[S]);
	}
}

bool check(int len) {
	memset(dp, 63, sizeof(dp)); // dp[S] = INF;
	
	for (int S = 1; S < (1<<n); S++) {
		if (onelen[S] <= len) {
			dp[S] = 1;
			continue;
		}
		for (int S0 = (S-1)&S; S0; S0 = (S0-1)&S) {
			int S1 = S-S0; //S 被拆成两个集合 S0 & S1
			dp[S] = min(dp[S], dp[S0]+dp[S1]);
		}
	}
	// for (int S = 1; S < (1<<n); S++) {
	// 	printf("dp[%d] == %d\n", S, dp[S]);
	// }

	if (dp[(1<<n)-1] > k) return 0;
	return 1;
}


int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		
		scanf("%d%d", &n, &k);
		
		for (int i=0; i<n; i++) scanf("%d%d",&x[i],&y[i]);
		Init_Onelen();

		int l = -1, r = 65000;
		while (l + 1 < r) {
			int mid = (l+r) >> 1;
			if (check(mid)) r = mid;
			else l = mid;
		}
		// printf("check(1) == %d\n", check(2));
		printf("Case #%d: %d\n", kase, r);
	}
	return 0;
}



/*


1
5 2
1 1
2 2
3 3
6 6
7 8

3 2
3 3
3 6
6 9

*/
