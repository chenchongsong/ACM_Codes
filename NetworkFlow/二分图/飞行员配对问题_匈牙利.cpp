#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#define maxn 100010
using namespace std;

vector<int> G[maxn];
int link[maxn];
bool vis[maxn];
int ans = 0;
int dfs(int u)  {
for (auto v : G[u])
if (!vis[v]) {
    vis[v]=1;
    if (!link[v] || dfs(link[v]))
    { link[v] = u; return 1; }
}  return 0; }

int main() {
	int N, M, a, b;
	cin >> M >> N;
	while (cin >> a >> b && a != -1 && b != -1) {
		G[a].push_back(b);
	}

	for (int i=1;i<=M;i++)
	{memset(vis,0,sizeof(vis)); if(dfs(i)) ans++;}
	printf("%d\n", ans);
	for (int i=M+1;i<=N;i++)
	if (link[i]) printf("%d %d\n",link[i],i);
	return 0;
}
// 左半张图为1~m 右半张图为m+1~n
