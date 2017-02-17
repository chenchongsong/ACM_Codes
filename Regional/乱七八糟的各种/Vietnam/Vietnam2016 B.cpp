#include <cstdio>
#include <algorithm>
#define MaxN 300010
#define INF 0x7fffffff
using namespace std;

long long N, Q, K;
long long L[MaxN], H[MaxN], V[MaxN];
long long preH[MaxN];
//preH[i] = pos：记录小于i && 满足H[pos]>=H[i] 的最大的位置pos
int main()
{
	long long Case;
	scanf("%lld", &Case);
	while (Case--)
	{
		scanf("%lld",&N);
		for (long long i=1;i<=N;i++)
			scanf("%lld", &L[i]);
		for (long long i=1;i<=N;i++)
			scanf("%lld", &H[i]);
		L[0] = -1LL;
		H[0] = INF;
		V[0] = 0;
		for (long long i=1;i<=N;i++)
		{
			if ( H[i] <= H[i-1] )
			{
				preH[i] = i-1;
				V[i] = V[i-1] + (L[i]-L[i-1]-1) * H[i];
			}
			else
			{
				V[i] = V[i-1] + (L[i]-L[i-1]-1) * H[i-1];
				//fill up the small gap between i-1 & i
				
				long long Tmp = i-1;
				while (H[i] > H[ preH[Tmp] ])
				{
					V[i] += (L[i]-L[preH[Tmp]]-1) * (H[preH[Tmp]] - H[Tmp]);
					Tmp = preH[Tmp];
				}
				preH[i] = preH[Tmp];
				V[i] += (L[i]-L[preH[i]]-1) * (H[i] - H[Tmp]);
			}

		}
		for (long long i=1;i<=N;i++)
			printf("v[%lld]---%lld %lld\n",i,V[i], preH[i]);


		scanf("%lld", &Q);
		while (Q--)
		{
			scanf("%lld", &K);
			if ( K > V[N] ) { printf("%lld\n", N); continue; }
			printf("%lld\n", (long long) (lower_bound(V+1LL, V+N+1LL, K) - V) - 1LL );

		}

	}
	return 0;
}