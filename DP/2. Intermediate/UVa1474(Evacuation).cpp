#include <cstdio>
#include <cstring>
#include <algorithm>
//#define INF 1e8
#define MaxN 4010
#define MaxM 4010
using namespace std;
int N, M;
long long dp[MaxM][MaxN]; // 前i个站点 前j个施工队 每站至少一人
bool from[MaxM][MaxN];
int ans[MaxN];

struct node {int pos, id;} a[MaxN], b[MaxM];
bool cmp(node A, node B){return A.pos<B.pos;}
long long ABS(long long x){return x>0?x:-x;}

int main()
{
	while (scanf("%d", &N)!=EOF)
	{
		for (int i=1;i<=N;i++)
		{
			scanf("%d", &a[i].pos);
			a[i].id = i;
		}
		scanf("%d", &M);
		for (int i=1;i<=M;i++)
		{
			scanf("%d", &b[i].pos);
			b[i].id = i;
		}
		sort(a+1, a+N+1, cmp);
		sort(b+1, b+M+1, cmp);

		memset(dp, 127, sizeof(dp));
		memset(from, 0, sizeof(from));
		dp[0][0] = 0;
		for (int i=1; i<=M; i++)
			for (int j=i; j<=N-M+i; j++) //j>=i && N-j>=M-i
			{
				long long dist = ABS((long long)b[i].pos - (long long)a[j].pos);

				if (dp[i-1][j-1]<dp[i][j-1])
				{
					dp[i][j] = dp[i-1][j-1] + dist;// 第i站此时只有j一个队伍
					from[i][j] = 1; //
				}
				else
				{
					dp[i][j] = dp[i][j-1] + dist;//除j外 i站还有其他队伍
					from[i][j] = 0;
				}
			}
		printf("%lld\n", dp[M][N]);

		int i=M, j=N;
		while(j)
		{
			ans[a[j].id] = b[i].id;
			if (from[i][j]) i--;
			j--;
		}
		for (int j=1; j<N; j++)
			printf("%d ", ans[j]);
		printf("%d\n", ans[N]);
	}
	return 0;
}