// O(N*M)
// 点index不得为0
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
    // 左半张图为1~m 右半张图为m+1~n
    // 由左半张图向右半张图连单向边
	for (int i=1;i<=M;i++)
	{memset(vis,0,sizeof(vis)); if(dfs(i)) ans++;}
	printf("%d\n", ans);
	for (int i=M+1;i<=N;i++)
	if (link[i]) printf("%d %d\n",link[i],i);
}

