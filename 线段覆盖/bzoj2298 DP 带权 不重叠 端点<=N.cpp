// 求最多说真话的人数，答案即为n-ans
// 设dp[i]表示在前i名中最多有多少人说真话
// dp[i] = max{dp[j-1]+sum[j][i]} 其中sum[j][i]表示名次区间为[j, i]的人数
// O(N)

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long
#define MaxN 100010
using namespace std;
int read()
{
	int x=0, f=1; char c=getchar();
	while (c<'0' || c>'9') { if(c=='-')f=-1; c=getchar();}
	while (c>='0' && c<='9') { x=x*10+c-'0'; c=getchar();}
	return x * f;
}

int N;
int f[MaxN];
vector <int> find_front[MaxN];
map < pair<int,int> ,int> find_val;

int main()
{
	N = read();
	for (int i=1; i<=N; i++)
	{
		int tmpL = read(), tmpR = read();
		int l = tmpL + 1, r = N - tmpR; //转化为线段覆盖问题
		if (l > r) continue;
		find_val[ make_pair(l,r) ]++;
		if (find_val[make_pair(l,r)]==1)
				find_front[r].push_back(l);
	}
	for (int i=1;i<=N;i++)
	{
		f[i] = f[i-1];
		for (int j=0; j<find_front[i].size(); j++)
		// 枚举以i为右端点的线段
		{
			int l = find_front[i][j], r = i;
			int val = find_val[make_pair(l,r)];
			f[i] = max(f[i], f[l-1]	+ min(r-l+1, val) );
		}
	}
	printf("%d\n", N - f[N]);
	return 0;
}