// method one:
// dp[i][j] 表示左端点为i 右端点为j 的子问题
// .val为length .ans为决策序列(即要输出的答案)
// dp[i][j] = max(dp[i+1][j], dp[i][j-1], (s[i]==s[j])*(dp[i+1][j-1]+2) )

#include <cstdio>
#include <iostream>
#include <cstring>
#define maxn 1010
using namespace std;

struct state {
	int val;
	string ans;
	inline bool operator > (const state& b) const{
		if (this->val != b.val) return this->val > b.val;
		return this->ans < b.ans;
	}
} dp[maxn][maxn];
char s[maxn];
state MAX(state a, state b){return a>b?a:b;}
int main() {
	while (scanf("%s", s+1)!=EOF) {
		//Clear();
		int n = strlen(s+1);
		for (int i=n; i>=1; i--) {
			dp[i][i].val = 1;
			dp[i][i].ans = s[i];
			for (int j=i+1; j<=n; j++) {
				if (s[i]==s[j]) {
					dp[i][j].val = dp[i+1][j-1].val+2;
					dp[i][j].ans = s[i]+dp[i+1][j-1].ans+s[j];
				}
				else dp[i][j] = MAX(dp[i+1][j], dp[i][j-1]);
			}
		}
		cout << dp[1][n].ans << endl;
	}
	return 0;
}