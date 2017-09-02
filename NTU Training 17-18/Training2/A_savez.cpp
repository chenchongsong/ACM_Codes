#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
typedef long long llint;

#define value first
#define idx second

const int MAXN = 1000010;
const int HASH1 = 3137;
const int HASH2 = 10007;
const int MOD = 1000000007;

map<pii, pii> dp;
int n, powh1[MAXN], powh2[MAXN], ans, ans_idx;
char s[MAXN];

// previous[MAXN];
// vector<int> sol;

void solve(void) {

	// memset(previous, -1, sizeof(previous));
	powh1[0] = powh2[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
	    powh1[i] = (llint)powh1[i - 1] * HASH1 % MOD;
	    powh2[i] = (llint)powh2[i - 1] * HASH2 % MOD;
	}
  
	scanf("%d",&n);
	for (int j = 0; j < n; ++j) {
	    scanf("%s",s);
	    int m = strlen(s);
	    int h_front1 = 0, h_back1 = 0;
	    int h_front2 = 0, h_back2 = 0;
	    int best = 0;
    
	    for (int i = 0; i < m; ++i) {
	      	h_back1 = ((llint)h_back1 * HASH1 + int(s[m - 1 - i])) % MOD;
	      	h_front1 = (h_front1 + (llint)powh1[i] * int(s[i])) % MOD;

	      	h_back2 = ((llint)h_back2 * HASH2 + int(s[m - 1 - i])) % MOD;
	      	h_front2 = (h_front2 + (llint)powh2[i] * int(s[i])) % MOD;
      
	      	if (h_front1 == h_back1 && h_front2 == h_back2 && best < dp[make_pair(h_front1, h_front2)].value) {
				// 保证 s[0~i] == s[m-i-1~m-1]

				best = dp[make_pair(h_front1, h_front2)].value;
				// previous[j] = dp[make_pair(h_front1, h_front2)].idx;
	      	}
	    }
	    dp[make_pair(h_front1, h_front2)] = pii(best + 1, j);

	    if (best + 1 > ans) {
	    	ans = best + 1;
		    ans_idx = j;
	    }
	}
	printf("%d\n",ans);
}

int main(void) {
  solve();
  return 0;
}
