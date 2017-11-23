#include<cstdio>
#include<algorithm>
#include <vector>
#include <iostream>
#define maxn 500010
#define maxlog 19
#define INF 0x3f3f3f3f
using namespace std;

struct Edge{int u,v,w;};
vector<Edge> edges;
vector<int> G[maxn];
int dep[maxn]; //在dfs树上的深度
int f[maxn][maxlog], g[maxn][maxlog];
//点index: 1~N (不能为0)
//init: f, g = 0
//f[i,j]记录i结点向上走2^j步后所到达的祖先
//g[i,j]记录i结点向上走2^j步的路途中的边权最小值
void dfs(int u) {
	for (int i=1;i<maxlog;i++) {
		f[u][i] = f[f[u][i-1]][i-1];
		g[u][i] = min(g[u][i-1], g[f[u][i-1]][i-1]);
	}
	for (int i=0; i<G[u].size(); i++) {
		Edge& e = edges[G[u][i]];
		int v = e.v, w = e.w;
		if (!dep[v]) {
			f[v][0]=u;
			g[v][0]=w;
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	}
}
int LCA(int a,int b) {
	if (dep[a]>dep[b]) swap(a,b); //保证b更深
	int Ans=INF;
	for (int i=maxlog-1;i>=0;i--)
	if (dep[f[b][i]]>=dep[a]){
		Ans=min(Ans,g[b][i]);
		b=f[b][i];
	} //将b移动至与a同一深度
	if (a==b) return a; //LCA=a=b
	for (int i=maxlog-1;i>=0;i--)
		if (f[a][i]!=f[b][i]){
			Ans=min(Ans,min(g[a][i],g[b][i]));
			a=f[a][i];b=f[b][i];
		}//向上找到LCA
	Ans=min(Ans,min(g[a][0],g[b][0]));
	return f[a][0]; //LCA=f[a][0]-f[b][0]
}


int main() {
	int n, q, root;
	cin >> n >> q >> root;
	for (int i=1; i<=n-1; i++) {
		int u, v;
		cin >> u >> v;
		edges.push_back((Edge){u,v,0});
		edges.push_back((Edge){v,u,0});
		G[u].push_back(edges.size()-2);
		G[v].push_back(edges.size()-1);		
	}
	// 不连通的森林:
	// for (int i=1; i<=n; i++)
	// 	if (!dep[i]) {
	// 		dep[i] = 1;
	// 			dfs(i);

	// 单棵树
	dep[root] = 1;
	dfs(root); // 这里的1不能改为0

	for (int i=1; i<=q; i++) {
		int x, y;
		scanf("%d%d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
	return 0;
}
