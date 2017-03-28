#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define maxn 100
using namespace std;
int dp[maxn][maxn], cnt[maxn][maxn];
struct position{
	int pos1, pos2;
} prePos[maxn][maxn];
int len1, len2;
char s1[maxn], s2[maxn];
int main() {
	int T; cin >> T; getchar();
	for (int kase=1; kase<=T; kase++) {
		memset(dp, 0, sizeof(dp));
		memset(cnt, 0, sizeof(cnt));
		gets(s1);
		gets(s2); //有可能出现空字符串 所以不用scanf %s
		len1 = strlen(s1);
		len2 = strlen(s2);
		for (int i=0; i<=max(len1, len2); i++)
			cnt[i][0] = cnt[0][i] = 1;

		for (int i=1; i<=len1; i++) {
			for (int j=1; j<=len2; j++) {
				if (s1[i-1] == s2[j-1]) {
					dp[i][j] = dp[i-1][j-1]+1;
					cnt[i][j] = cnt[i-1][j-1];
					continue;
				}
				if (dp[i-1][j] > dp[i][j-1])
					dp[i][j] = dp[i-1][j],
					cnt[i][j] = cnt[i-1][j];
				else if (dp[i-1][j] < dp[i][j-1])
					dp[i][j] = dp[i][j-1],
					cnt[i][j] = cnt[i][j-1];
				else
					dp[i][j] = dp[i-1][j],
					cnt[i][j] = cnt[i-1][j]+cnt[i][j-1];
			}
		}
		printf("Case #%d: %d %d\n",kase, len1+len2-dp[len1][len2], cnt[len1][len2]);
	}
	return 0;
}