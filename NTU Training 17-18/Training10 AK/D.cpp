#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;
int n, m, ans;
int dp[210][65][65][65]; // t 时刻 i j len

string s[65];
int sx, sy, ex, ey;
string tmp;
int opt[65];
int opt_size = 0;

int dx[10] = {-1, 1, 0, 0};
int dy[10] = {0, 0, -1, 1};

bool check(int x, int y) {
	if (x<1 || y<1 || x>n || y>m) return false;
	if (s[x][y] == '#') return false;
	return true;
}

void find_dir(int& tx, int& ty, int i, int j, int d) {
	tx = i + dx[d];
	ty = j + dy[d];
	if (!check(tx, ty)) tx = i, ty = j;
}


int main() {
	cin >> n >> m;

	for (int i=1; i<=n; i++) {
		cin >> s[i];
		s[i] = " "+s[i];
		for (int j=1; j<=m; j++) {
			if (s[i][j]=='S')
				sx = i, sy = j;
			else if (s[i][j] == 'G')
				ex = i, ey = j;
		}
	}
	cin >> tmp;
	tmp = " " + tmp;
	opt_size = tmp.size()-1;
	for (int i=1; i<tmp.size(); i++) {
		if (tmp[i] == 'U') opt[i] = 0;
		if (tmp[i] == 'D') opt[i] = 1;
		if (tmp[i] == 'L') opt[i] = 2;
		if (tmp[i] == 'R') opt[i] = 3;
	}

	// for (int i=1; i<=opt_size; i++) {
	// 	printf("opt[%d] == %d\n", i, opt[i]);
	// }

	memset(dp, 63, sizeof(dp));
	dp[0][sx][sy][0] = 0;

	for (int t=0; t<=2*(n+m); t++) {
		for (int i = 1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				if (s[i][j] == '#') continue;
				for (int l = 0; l <opt_size; l++) {
					// printf("dp[%d][%d][%d][%d] == %d\n",t,i,j,l,dp[t][i][j][l]);

					int tx = i + dx[opt[l+1]];
					int ty = j + dy[opt[l+1]];
					if (!check(tx, ty)) tx = i, ty = j;
					dp[t+1][tx][ty][l+1] = min(dp[t+1][tx][ty][l+1], dp[t][i][j][l]);

					// insert
					for (int d=0; d<4; d++) {
						find_dir(tx, ty, i, j, d);
						dp[t+1][tx][ty][l] = min(dp[t+1][tx][ty][l], dp[t][i][j][l]+1);
					}
					
					// delete
					dp[t+1][i][j][l+1] = min(dp[t+1][i][j][l+1], dp[t][i][j][l]+1);
				}
			}
		}
	}

	ans = INF;
	for (int t=0; t<=2*(n+m); t++) {
		for (int l = 0; l<=opt_size; l++) {
			ans = min(ans, dp[t][ex][ey][l]);
		}
	}
	cout << ans << endl;

	return 0;

}