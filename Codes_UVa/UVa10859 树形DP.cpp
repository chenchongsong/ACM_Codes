#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define MaxN 1010
using namespace std;
int N;
int vis[MaxN];
int f[MaxN][2]; // [][0]该节点放灯 [][1]该节点不放灯
vector <int> ed[MaxN];
int father[MaxN];

void dfs (int u)
{
	if (vis[u]) return;
	vis[u] = 1;
	
	for (vector<int>::iterator it=ed[u].begin(); it!=ed[u].end(); it++)
	{
		int v = *it;
		//if (v==father[u]) continue;
		//father[v] = u;
		// 若用father数组 则每个testCase要清零一次
		if (vis[v]) continue;
		dfs(v);
		f[u][1] += min(f[v][0]+1, f[v][1]);//[1] 放灯
		f[u][0] += (f[v][1]+1); //[0] 不放灯
	}
	f[u][1] += 10000;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int N, M;
		scanf("%d%d",&N, &M);
		memset(vis, 0, sizeof(vis));
		memset(f, 0, sizeof(f));
		for (int i=0; i<N; i++) ed[i].clear();

		int u, v;
		for (int i=0; i<M; i++)
		{
			scanf("%d%d", &u, &v);
			ed[u].push_back(v);
			ed[v].push_back(u);//双向边
		}
		int ans = 0;
		for (int i=0; i<N; i++)
			if (!vis[i])
			{
				dfs(i);
				ans+= min(f[i][0], f[i][1]);
			}
		printf("%d %d %d\n", ans/(int)(10000), M-ans%(int)(10000), ans%(int)(10000));
	}
	return 0;
}