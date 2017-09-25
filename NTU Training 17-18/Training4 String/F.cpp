#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 10010
#define maxm 10010
#define maxq 500010
#define INF 0x7fffffff
using namespace std;
int v[maxm], u[maxm], con[maxm], cost[maxm], prep[maxn];
int head[maxn], Dis[maxn], path[maxn];
int Que[maxq];
bool vis[maxn];
int m0 = 1, S, T, Qhead, Qtail, Ans1=0, Ans2=0, n, m;
int leftNode(int x) {return x + 2;}
int rightNode(int x) {return x + n + 2;}

void AddEdge(int a,int b,int c,int d) { printf("a %d  b %d  c %d  d %d\n",a,b,c,d);
v[++m0]=b;u[m0]=a;con[m0]=c;cost[m0]=d;prep[m0]=head[a];head[a]=m0;
v[++m0]=a;u[m0]=b;con[m0]=0;cost[m0]=-d;prep[m0]=head[b];head[b]=m0;}

bool spfa() {
memset(Dis,127,sizeof(Dis)); memset(vis,0,sizeof(vis));
Dis[S]=0; vis[S]=1; Que[Qhead=Qtail=1]=S;
while(Qhead<=Qtail){
	for(int i=head[Que[Qhead]];i;i=prep[i])
		if(con[i]&&Dis[v[i]]>Dis[Que[Qhead]]+cost[i]){
			Dis[v[i]]=Dis[Que[Qhead]]+cost[i];
			path[v[i]]=i;
			if(!vis[v[i]]) vis[Que[++Qtail]=v[i]] = 1;
		}   vis[Que[Qhead]]=0; ++Qhead;
} return Dis[T]<2100000000; }

void CostFlow() {
	int x; Ans1=Ans2=0; memset(path,0,sizeof(path));
	while(spfa()) { int f=INF;
		for(x=T;x!=S;x=u[path[x]]) f=min(f,con[path[x]]);
		for(x=T;x!=S;x=u[path[x]]) {con[path[x]]-=f; con[path[x]^1]+=f; }
		Ans1++;
		Ans2+=Dis[T]*(long long)f;}
}

int main() {
	scanf("%d%d", &n, &m);
	S=1;T=2;
	for (int i=1; i<=n; i++) {
		AddEdge(S, leftNode(i), 1, 0);
		AddEdge(rightNode(i), T, 1, 0);
	}

	int tmp1, tmp2, tmp3;
	for (int i=1; i<=m; i++) {
		scanf("%d%d%d", &tmp1, &tmp2, &tmp3);
		AddEdge(leftNode(min(tmp1,tmp2)), rightNode(max(tmp1,tmp2)), 1, tmp3);

	}
	CostFlow();
	printf("Ans1 %d   Ans2 %d\n", Ans1, Ans2);

	if (Ans1*2 == n)
		printf("%d\n",Ans2);
	else
		puts("impossible");

	return 0;
}

