#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#define maxs 60010
#define maxn 210
#define maxm 2010
using namespace std;

int cost[maxn], menu;
int dp[maxs];
int from[maxs];
// dp[i] how many ways to achieve a total cost of i

// bool cmp(int A, int B) {return A>B;}
int main() {
	// freopen("Desktop/orders/10.in", "r", stdin);
	int n, m;
	cin >> n;
	// cout << "hello" << endl;
	// cout << n << endl;
	for (int i=1; i<=n; i++) cin >> cost[i];

	
	dp[0] = 1;
	for (int i=n; i; i--) {
	// make sure that when outputing solution of "from"s
	// smaller value will be outputted first
		for (int j=cost[i]; j<=40000; j++) {
			if (dp[j - cost[i]] > 0) {
				dp[j] += dp[j-cost[i]];
				if (dp[j] > 2) dp[j] = 2;
				from[j] = i;
			}
		}
	}
	// for (int i=1; i<=100; i++) {
	// 	printf("%d -- %d %d\n",i,dp[i],from[i]);
	// }
	cin >> m;
	for (int i=1; i<=m; i++) {
		cin >> menu;
		if (dp[menu] == 0) {
			puts("Impossible");
			continue;
		}
		if (dp[menu] > 1) {
			puts("Ambiguous");
			continue;
		}
		while (menu > 0) {
			cout << from[menu] << " ";
			menu -= cost[from[menu]];
		}
		puts("");
	}
	return 0;
}