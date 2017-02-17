#include <cstdio>
#include <algorithm>
#define INF 0x7fffffff
#define MaxN 10010
using namespace std;
int A[MaxN], g[MaxN], dp[MaxN];
int N;


int main()
{
	scanf("%d",&N);
	for (int i=1;i<=N;i++)
	{
		scanf("%d", &A[i]);
	}
	int Ans = 0;
	
// strictly increasing
for (int i=2;i<=N+1;i++) g[i]=INF;
for (int i=1;i<=N;i++)
{
	int k=upper_bound(g+2,g+N+2,A[i]) - g;
	dp[i] = k-1; //  以A[i]结尾的LIS长度
	Ans = max(Ans, dp[i]);
	g[k] = A[i];
}

	printf("%d\n",Ans);

	return 0;

}