#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define MaxN 310
#define MaxM 150010
#define MaxQ 5000010
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;

int Que[MaxQ], Qhead, Qtail;

int Dis[MaxN], head[MaxN], path[MaxN];
int u[MaxM], v[MaxM], prep[MaxM], con[MaxM], cost[MaxM];
bool vis[MaxN];

int n, m, S, T, m0 = 1;
int AnsFlow;
ll AnsCost;

// ========== 费用流 ==========
void AddEdge(int a,int b,int c,int d) {
	v[++m0]=b;u[m0]=a;con[m0]=c;cost[m0]=d;prep[m0]=head[a];head[a]=m0;
	v[++m0]=a;u[m0]=b;con[m0]=0;cost[m0]=-d;prep[m0]=head[b];head[b]=m0;
}
bool spfa() {
	memset(Dis, 63, sizeof(Dis));
	memset(vis, 0,sizeof(vis));
	Dis[S]=0; vis[S]=1; Que[Qhead=Qtail=1]=S;
	while(Qhead<=Qtail){
		for(int i=head[Que[Qhead]];i;i=prep[i])
			if(con[i]&&Dis[v[i]]>Dis[Que[Qhead]]+cost[i]) {
				Dis[v[i]]=Dis[Que[Qhead]]+cost[i];
				path[v[i]]=i;
				if(!vis[v[i]])
				vis[Que[++Qtail]=v[i]] = 1;
			}  
		vis[Que[Qhead]]=0;
		++Qhead;
	}
	return Dis[T]<INF; // 0x3f3f3f3f
}

void CostFlow() {
	int x;
	AnsFlow = AnsCost = 0;
	memset(path, 0, sizeof(path));
	while (spfa()) {
		int f=INF;
		for(x=T;x!=S;x=u[path[x]])
			f=min(f,con[path[x]]);
		for(x=T;x!=S;x=u[path[x]]) {
			con[path[x]]-=f;
			con[path[x]^1]+=f;
		}
		AnsCost += (ll)Dis[T]*(ll)f;
		AnsFlow += f;
	}
}

int main() {
	cin >> n >> m >> S >> T;
	while (m--) {
		int u, v, c, w;
		cin >> u >> v >> c >> w;
		AddEdge(u, v, c, w);
	}
	CostFlow();
	printf("%d %lld\n", AnsFlow, AnsCost);

}
// S=1;T=2; CostFlow(); 
