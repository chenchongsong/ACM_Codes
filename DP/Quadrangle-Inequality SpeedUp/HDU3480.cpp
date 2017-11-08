#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXINT = 999999999;

int n, m;
int a[10010];
int dp[10010][5000];
int s[10010][5000];

int cost (int _a, int _b) {
    return (a[_b] - a[_a]) * (a[_b] - a[_a]);
}
// dp[i][j] 前i个数 分成j组 最小代价
// dp[i][j] = min { dp[k-1][j-1] + cost(k,i) }
// cost函数 满足四边形不等式
int main () {
    int T;
    scanf ("%d", &T);
    for (int i_case = 1; i_case<=T; i_case++) {
        scanf ("%d%d", &n, &m);
        for (int i=1; i<=n; i++) {
            scanf ("%d", &a[i]);
        }

        sort (a+1, a+n+1);

        for (int i=0; i<n; i++) {
            s[i][0] = 1;
        }
        for (int i=1; i<=n; i++){
            s[n+1][i] = n;
        }

        memset(dp, 0, sizeof(dp));
        for (int i=1; i<=n; i++) {
            dp[i][1] = cost(1, i);
        }
        for (int j=2; j<=m; j++) {
            for (int i=n; i>=1; i--) {
                // printf("%d -- %d\n",i,j);
                // printf("k from %d to %d\n", s[i][j-1], s[i+1][j]);
                dp[i][j] = MAXINT;
                for (int k=s[i][j-1]; k<=s[i+1][j]; k++) {
                    if (dp[i][j] > dp[k-1][j-1] + cost(k, i)) {
                        dp[i][j] = dp[k-1][j-1] + cost(k, i);
                        s[i][j] = k;
                    }
                }
            }
        }
        printf ("Case %d: %d\n", i_case, dp[n][m]);
    }

    return 0;
}