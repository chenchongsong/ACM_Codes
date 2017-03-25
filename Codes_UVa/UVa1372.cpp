#include <cstdio>
#include <algorithm>
#include <iostream>
#define maxn 5010
using namespace std;
int pos[maxn];
int T, n, k;
bool check(int a, int b) {return pos[b]-pos[a] <= k;}
int main() {
	cin >> T;
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i=1; i<=n; i++)
			scanf("%d", &pos[i]);
		sort(pos+1, pos+n+1);

		int i=1, ans = 0;
		while (i<=n) {
			int old_i = i;
			int sum = 1;
			while (i<n && (sum==1||check(i-1,i+1)) && (check(i,i+1)))
				sum++, i++;
			if (i == old_i) i++;
			ans = max(ans, sum);
		}
		cout << ans << endl;
	}
	return 0;
}