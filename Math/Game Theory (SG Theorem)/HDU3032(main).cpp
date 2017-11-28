#include <cstdio>
#include <iostream>
#include <algorithm>
#define maxn 1000005
using namespace std;

int s[maxn];
int T, n;

// 规律由打表得来
int SG(int x) {
	if (x == 0) return 0;
	if (x % 4 == 1) return x;
	if (x % 4 == 2) return x;
	if (x % 4 == 3) return x+1;
	if (x % 4 == 0) return x-1;
	return -1; // warning prevention
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int sg_sum = 0;
		for (int i=1; i<=n; i++) {
			scanf("%d", &s[i]);
			sg_sum ^= SG(s[i]);
		}
		if (sg_sum) puts("Alice");
		else puts("Bob");
	}
	return 0;
}