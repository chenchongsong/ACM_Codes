#include<cstdio>
#include<algorithm>
#include <vector>
#define ll long long
#define MaxN 50010
#define MaxM 50010
#define MaxQ 100000
#define INF 0x3f3f3f3f
using namespace std;
int n, m, q, x, y;
int fa[MaxN];
int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}

struct Edge{int u,v,w;};
vector<Edge> edges;
vector<int> G[MaxN];
int dep[MaxN];
int f[MaxN][14], g[MaxN][14];
//f[i,j]记录i结点向上走2^j步后所到达的祖先
//g[i,j]记录i结点向上走2^j步的路途中的边权最小值
void dfs(int u,int cur_dep) {
	dep[u] = cur_dep;  //在dfs树上的深度
	for (int i=1;i<=13;i++) {
		f[u][i] = f[f[u][i-1]][i-1];
		g[u][i] = min(g[u][i-1], g[f[u][i-1]][i-1]);
	}
	for (int i=0; i<G[u].size(); i++) {
		Edge& e = edges[G[u][i]];
		int v = e.v, w = e.w;
		if (!dep[v]) {
			f[v][0]=u;
			g[v][0]=w;
			dfs(v, cur_dep+1);
		}
	}
}
int LCA(int a,int b) {
	if (dep[a]>dep[b]) swap(a,b); //保证b更深
	int Ans=INF;
	for (int i=13;i>=0;i--)
	if (dep[f[b][i]]>=dep[a]){
		Ans=min(Ans,g[b][i]);
		b=f[b][i];
	} //将b移动至与a同一深度
	if (a==b) return Ans; //LCA=a=b
	for (int i=13;i>=0;i--)
		if (f[a][i]!=f[b][i]){
			Ans=min(Ans,min(g[a][i],g[b][i]));
			a=f[a][i];b=f[b][i];
		}//向上找到LCA
	Ans=min(Ans,min(g[a][0],g[b][0]));
	return Ans; //LCA=f[a][0]-f[b][0]
}

bool cmp(Edge a,Edge b){return a.w>b.w;}//边权从大到小
Edge ed[MaxM];
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
		scanf("%d%d%d",&ed[i].u,&ed[i].v,&ed[i].w);
	sort(ed+1,ed+m+1,cmp);
	edges.clear();
	for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=m;i++) {
		int x=find(ed[i].u),y=find(ed[i].v);//最小生成树
		if (x != y) {
			int u = ed[i].u, v = ed[i].v, w = ed[i].w;
			edges.push_back((Edge){u,v,w});
			edges.push_back((Edge){v,u,w});
			G[u].push_back(edges.size()-2);
			G[v].push_back(edges.size()-1);
			fa[x]=y; // Union
		}
	}


	for (int i=1; i<=n; i++)
		if (!dep[i])
			dfs(i,1);
	// for (int i=1; i<=n; i++) {
	// 	for (int j=0; j<G[i].size(); j++)
	// 		printf("%d -> %d\n",i,edges[G[i][j]].v);
	// }
	// for (int i=1; i<=n; i++) {
	// 	printf("fa[%d] = %d : %d\n",i,f[i][0],g[i][0]);
	// }
	
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		scanf("%d%d",&x,&y);
		if (find(x)!=find(y)) puts("-1");
		else printf("%d\n",LCA(x,y));
	}
	return 0;
}
