#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;
#define INF 0x3f3f3f3f

int dp[155][505][105][55];
bool vis[155][505][105][55];
int T, D, n1, n5, n10;
int dfs(int c, int i, int j, int k) {
	if (i < 0 || j < 0 || k < 0)
		return INF;
	if (c == 0) return 0;
	
	if (vis[c][i][j][k]) return dp[c][i][j][k];
	vis[c][i][j][k] = 1;

	int& res = dp[c][i][j][k];
	res = min(INF, dfs(c-1, i+2, j, k-1) + 1);
	res = min(res, dfs(c-1, i+2, j-2, k) + 2);
	res = min(res, dfs(c-1, i-3, j+1, k-1) + 4);
	res = min(res, dfs(c-1, i-8, j, k) + 8);
	res = min(res, dfs(c-1, i-3, j-1, k) + 4);
	// printf("%d %d %d %d : %d\n",c,i,j,k,res);
	return res;
}
int main() {
	cin >> T;
	while (T--) {
		cin >> D >> n1 >> n5 >> n10;
		dfs(D, n1, n5, n10);
		cout << dp[D][n1][n5][n10] << endl;
	}
	return 0;
}