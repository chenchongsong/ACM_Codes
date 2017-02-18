#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 16;
const int MAXW = 110;
int a[MAXN], sum[1<<MAXN];
int f[1<<MAXN][MAXW], vis[1<<MAXN][MAXW];

int bit_count (int x)
{ return x==0? 0: bit_count(x>>1) + (x&1); }

int dp(int S, int x) //x 为较小的边长
{
	if (vis[S][x]) return f[S][x];
	vis[S][x] = 1;
	int& ans = f[S][x];
	if (bit_count(S) == 1) return ans = 1;

	int y = sum[S] / x; //y为较大边长

	for (int S0 = (S-1)&S; S0; S0 = (S0-1)&S) //枚举S的子集S0
	{
		int S1 = S-S0; //S 被拆成两个集合 S0 & S1
		if ( sum[S0]%x==0 && dp(S0,min(x,sum[S0]/x)) && dp(S1,min(x,sum[S1]/x)) )
			return ans = 1;
		if ( sum[S0]%y==0 && dp(S0,min(y,sum[S0]/y)) && dp(S1,min(y,sum[S1]/y)) )
			return ans = 1;

	}
	return ans = 0;
}

int main()
{
	int Case = 0, n, x, y, ans;
	while (scanf("%d", &n)!=EOF && n)
	{
		scanf("%d%d", &x, &y);
		for (int i=0; i<n; i++)
			scanf("%d", &a[i]);

		memset(sum, 0, sizeof(sum));
		for (int S=0; S<(1<<n); S++)
			for (int i=0; i<n; i++)
				if (S & (1<<i))
					sum[S] += a[i];

		memset(vis, 0, sizeof(vis));
		int tot = (1<<n) - 1;
		if (sum[tot] != x*y || sum[tot]%x )
			ans = 0;
		else
			ans = dp(tot, min(x,y));
		
		printf("Case %d: %s\n", ++Case, ans ? "Yes" : "No");
	}
	return 0;
}
/*

4
3 4
6 3 2 1
2
2 3
1 5
0

*/