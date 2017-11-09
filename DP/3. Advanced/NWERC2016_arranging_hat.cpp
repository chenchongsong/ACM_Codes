#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#define INF ox3f3f3f3f
using namespace std;

int N, M;
int cnt[410][50][10];
// "input数列"的第j列 前i行 有cnt[j][i][num] 个数字num

int dp[410][50][50][10]; // j~M列 i1~i2行 第j列的数取值范围为[0,num] 且递增 需要的最小代价
int s[410][50][50][10]; // 决策数组
char str[50][410];

inline void solve(int j, int i1, int i2, int num) {
	if (j > M) return;
	if (i1 > i2 || i1 < 1 || i1 > N || i2 < 1 || i2 > N) return;

	while (s[j][i1][i2][num] == -1) // from dp[j][i1][i2][num-1]
		num--;
	
	if (0 <= s[j][i1][i2][num] && s[j][i1][i2][num] <= 9) { // first color all same numbers
		for (int i=i1; i<=i2; i++)
			str[i][j] = '0' + s[j][i1][i2][num];
		solve(j+1, i1, i2, 9);
		return;
	}
	
	// s > 10
	int k = s[j][i1][i2][num] - 10;
	for (int i=k+1; i<=i2; i++)
		str[i][j] = '0' + num;
	
	solve(j, i1, k, num-1);
	solve(j+1, k+1, i2, 9);
}

int main() {

	scanf("%d%d", &N, &M);
	for (int i=1; i<=N; i++) {
		scanf("%s", str[i]+1);
		for (int j=1; j<=M; j++)
			cnt[j][i][str[i][j]-'0']++;
	}

	// 求前缀和
	for (int j=1; j<=M; j++)
		for (int i=1; i<=N; i++)
			for (int num=0; num<=9; num++)
				cnt[j][i][num]+=cnt[j][i-1][num];
	
	// dp & s initiallization
	memset(dp, 63, sizeof(dp));
	memset(s, -1, sizeof(s));
	for (int i1=0; i1<=N; i1++)
		for (int i2=i1; i2<=N; i2++)
			for (int num=0; num<=9; num++)
				dp[M+1][i1][i2][num] = 0;

	for (int j=M; j; j--) {
		for (int len = 1; len <=N; len++) // interval DP: from
			for (int i1=1; i1<=N; i1++) {
				int i2 = i1+len-1;
				if (i2 > N) break;

				for (int num=0; num<=9; num++) {
					int& res = dp[j][i1][i2][num];
					
					if (num) res = dp[j][i1][i2][num-1];
					// s is -1 by default

					for (int firstnum=0; firstnum<=num; firstnum++)
						// try setting all elements [i1~i2][j] to "firstnum"
						if (res > dp[j+1][i1][i2][9]+len-(cnt[j][i2][firstnum]-cnt[j][i1-1][firstnum])) {
							res = dp[j+1][i1][i2][9]+len-(cnt[j][i2][firstnum]-cnt[j][i1-1][firstnum]);
							s[j][i1][i2][num] = firstnum;
						}

					if (num)
					for (int k=i1; k<i2; k++) // break_point k: [i1 ~ k], [k+1 ~ i2]
						// try setting all elements [k+1~i2][j] to "num"
						if (res > dp[j][i1][k][num-1]+dp[j+1][k+1][i2][9]+(i2-k)-(cnt[j][i2][num]-cnt[j][k][num])) {
							res = dp[j][i1][k][num-1]+dp[j+1][k+1][i2][9]+(i2-k)-(cnt[j][i2][num]-cnt[j][k][num]);
							s[j][i1][i2][num] = 10 + k;
						}
				}
			}
	}

	solve(1, 1, N, 9);
	for (int i=1; i<=N; i++) {
		for (int j=1; j<=M; j++)
			printf("%c", str[i][j]);
		puts("");
	}
	return 0;
}