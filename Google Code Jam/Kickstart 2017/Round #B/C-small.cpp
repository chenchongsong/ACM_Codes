#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000][1000];
int T, n, m, k;

int solve(int i, int j) {
	int l=j, r=j, ret = 0;
	int flag = 0;
	for (; i<=n; i++) {

		for (int tmp = l; tmp<=r; tmp++)
			if (s[i][tmp] == '.') {
				flag = 1;
				break;
			}
		if (flag) break;

		ret += r-l+1;

		l--;
		r++;
		if (l==-1 || r==m) break;
	}
	return ret;
}


int main() {
	freopen("Desktop/kickstart B/code/C-small-attempt0 (1).in", "r", stdin);
  	freopen("Desktop/kickstart B/code/ans3.out", "w", stdout);
	scanf("%d", &T);
	for (int kase=1; kase<=T; kase++) {
		int ans = 0;
		scanf("%d%d%d", &n, &m, &k);
		
		for (int i=1; i<=n; i++)
			scanf("%s", s[i]);

		for (int i=1;i<=n; i++)
			for (int j=0; j<m; j++)
				ans = max(ans, solve(i, j));

		printf("Case #%d: %d\n", kase, ans);
	}
	return 0;
}