#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 10010
#define INF 100000000
using namespace std;
int dp[maxn], g[maxn], A[maxn];
int dp1[maxn], dp2[maxn];
int Ans, N;

void DP_LIS()
{
	// LIS  strictly increasing A[1]~A[N]
	for (int i=2;i<=N+1;i++) g[i]=INF;
	for (int i=1;i<=N;i++)
	{
		int k=lower_bound(g+2,g+N+2,A[i]) - g;
		//想改成non-decreasing的话
		//只要换成upper_bound就好了
		dp[i] = k-1; //以A[i]结尾的LIS长度
		g[k] = A[i];
	}
}

int main()
{
	while (scanf("%d", &N)!=EOF)
	{
		for (int i=1;i<=N;i++)
			scanf("%d", &A[i]);
		DP_LIS();
		for (int i=1;i<=N;i++)
			dp1[i] = dp[i];
		
		for (int i=1;i<=(N/2);i++)
			swap(A[i], A[N-i+1]);
		DP_LIS();
		for (int i=1;i<=N;i++)
			dp2[i] = dp[i];

		Ans = 0;
		for (int i=1;i<=N;i++)
		{
			int len = min(dp1[i], dp2[N-i+1]);
			Ans = max(Ans, len * 2 - 1);	
		}
		printf("%d\n", Ans);
	}
}

