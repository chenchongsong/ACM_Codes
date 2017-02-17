#include <cstdio>
#include <algorithm>
#define MaxN 1010
using namespace std;

int a[MaxN], N, L;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int c =1;c<=Case;c++)
	{
		scanf("%d%d", &N, &L);
		for (int i=1;i<=N;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+N+1);
		int Sum = 0, Ans = 0;
		int i = 1;
		for (;i<=N;i++)
		{
			if( (Sum + a[i]) > L ) break;
			
			Sum+=a[i];
			//printf("Sum---%d. %d\n", Sum, L);
			Ans += Sum;
		}
		printf("Case %d: %d %d %d\n", c, --i, Sum, Ans);




	}
	return 0;
}