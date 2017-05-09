#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100;

int f[N][N][N];
char grid[N][N];

int n, m, k;

int dp(int i, int j, int k) { // 递归着向后找 正难则反
	if (i >= n) return 0;
	if (f[i][j][k] != -1) return f[i][j][k];
	f[i][j][k] = 0;
	int sum = 0;
	int l = j;
	int r = j;
	int h = i;
	while (h < n && l >= 0 && r < m) {
		
		bool ok = true;
		for (int tmp = l; tmp <= r; ++tmp)
			if (grid[h][tmp] == '.') {
				ok = false;
				break;
			}
		if (!ok) break;

		sum += r - l + 1;
		if (k > 1)
			for (int tmp = l; tmp <= r; ++tmp)
				if (dp(h + 1, tmp, k - 1) != 0)
					f[i][j][k] = max(f[i][j][k], sum + f[h + 1][tmp][k - 1]);
		// total worst time complexity
		// O( N M K * N M)

		++r;  --l;  ++h;
	}
	if (k == 1) f[i][j][k] = sum; //single triangle
	return f[i][j][k];
}

int main() {
	//freopen("C-large.in", "r", stdin);
	//freopen("C.out", "w", stdout);
	int totalTest;
	cin >> totalTest;
	for (int testNum = 1; testNum <= totalTest; ++testNum) {
		printf("Case #%d: ", testNum);
		cin >> n >> m >> k;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> grid[i][j];
			}
		}
		memset(f, -1, sizeof(f));
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				ans = max(ans, dp(i, j, k));
			}
		}
		cout << ans << endl;
	}
	return 0;
}