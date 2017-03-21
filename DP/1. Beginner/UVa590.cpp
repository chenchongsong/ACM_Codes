#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 20
#define maxk 1010
#define maxd 40
const int INF = (int)1e8;
using namespace std;
int cost[maxn][maxn][maxk];
int dp[maxk][maxn];
int tmp[100];

void Clear() {memset(dp, 63, sizeof(dp));}
int main() {
	int kase = 0, n, day, d;
	while (scanf("%d%d", &n, &day)!=EOF && (n||day)) {
		Clear();
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++) {
				if (i==j) continue;
				scanf("%d", &d);
				for (int k=1; k<=d; k++)
					scanf("%d", &tmp[k]);

				for (int k=1; k<=day; k++) {
					cost[i][j][k] = tmp[(k-1)%d+1];
					//printf("i--%d j--%d k--%d : %d\n",i,j,k,cost[i][j][k]);
				}
			}
		dp[0][1] = 0;
		for (int k=1; k<=day; k++)
			for (int i=1; i<=n; i++) {
				for (int j=1; j<=n; j++) {
					if (i==j) continue;
					if (cost[j][i][k]==0) continue;
					dp[k][i] = min(dp[k][i], dp[k-1][j]+cost[j][i][k]);
				}
				//printf("day--%d pos--%d : %d\n",k,i,dp[k][i]);
			}
		printf("Scenario #%d\n", ++kase);
		if (dp[day][n] > INF) puts("No flight possible.");
		else printf("The best flight costs %d.\n", dp[day][n]);
		puts("");
	}
}