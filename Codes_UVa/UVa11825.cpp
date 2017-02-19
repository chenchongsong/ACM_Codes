#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int f[1<<17];
bool vis[1<<17];
int N, M;
int node_cover[17];
int set_cover[1<<17];
int tot;

void Clear()
{
	memset(node_cover, 0, sizeof(node_cover));
	memset(set_cover, 0, sizeof(set_cover));
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
}

int dp(int s)
{
	if (vis[s]) return f[s];
	vis[s] = 1;
	for (int s0 = s; s0; s0 = (s0-1) & s)
	{
		int s1 = s-s0;
		if (set_cover[s0]!=tot)
			continue;
		f[s] = max(f[s], dp(s1) + 1);
	}
	return f[s];
}

int main()
{
	int tmp;
	int kase = 0;
	while (scanf("%d", &N)==1 && N)
	{
		Clear();
		tot = (1<<N)-1;
		for (int i=0;i<N;i++)
		{
			scanf("%d", &M);
			for (int j=0;j<M;j++)
			{
				scanf("%d", &tmp);
				node_cover[i] |= 1<<tmp;
			}
			node_cover[i] |= (1<<i);
		}
		for (int s=0; s<(1<<N); s++)
			for (int i=0;i<N;i++)
				if (s&(1<<i))
					set_cover[s] |= node_cover[i];
		printf("Case %d: %d\n", ++kase, dp(tot));
	}
	return 0;
}
