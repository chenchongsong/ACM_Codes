#include<cstdio>
#include<algorithm>
#include <vector>
#include <iostream>
#define maxn 500010
#define maxlog 19
#define INF 0x3f3f3f3f
using namespace std;
int tot = 0;
int head[maxn], v[maxn*2], prep[maxn*2];
int dep[maxn]; //在dfs树上的深度
int f[maxn][maxlog];
//点index: 1~N (不能为0)
//init: f, g = 0
//f[i,j]记录i结点向上走2^j步后所到达的祖先
void dfs(int u) {
	for (int i=1;i<maxlog;i++)
		f[u][i] = f[f[u][i-1]][i-1];
	for (int i=head[u]; i; i=prep[i]) {
		if (!dep[v[i]]) {
			f[v[i]][0]=u;
			dep[v[i]] = dep[u] + 1;
			dfs(v[i]);
		}
	}
}
int LCA(int a,int b) {
	if (dep[a]>dep[b]) swap(a,b); //保证b更深
	for (int i=maxlog-1;i>=0;i--)
	if (dep[f[b][i]]>=dep[a])
		b=f[b][i];
	//将b移动至与a同一深度
	if (a==b) return a; //LCA=a=b
	for (int i=maxlog-1;i>=0;i--)
		if (f[a][i]!=f[b][i])
			a=f[a][i], b=f[b][i];
	//向上找到LCA
	return f[a][0]; //LCA=f[a][0]-f[b][0]
}


int main() {
	int n, q, root;
	cin >> n >> q >> root;
	for (int i=1; i<=n-1; i++) {
		int tmpu, tmpv;
		cin >> tmpu >> tmpv;
		v[++tot] = tmpv; prep[tot] = head[tmpu]; head[tmpu] = tot;
		v[++tot] = tmpu; prep[tot] = head[tmpv]; head[tmpv] = tot;
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
