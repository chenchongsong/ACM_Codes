#include <cstdio>
#include <cstring>
#define maxn 1010
#define maxm 100010
#define maxq 2000010

int v[maxm], u[maxm], cost[maxm], con[maxm], prep[maxm];
int head[maxn], Dis[maxn], path[maxn];
bool vis[maxn];
int Que[maxq];
int m0 = 1, Ans = 0, S, T, Qhead, Qtail;

void Clear() {
	int m0 = 1;
	memset(u, 0, sizeof(u));
	memset(v, 0, sizeof(v));
	memset(cost, 0, sizeof(cost));
	memset(con, 0, sizeof(con));
	memset(prep, 0, sizeof(prep));
	memset(head, 0, sizeof(head));
}

int Min(int a, int b) {return a<b?a:b;}

void AddEdge(int a,int b,int c,int d) {
	v[++m0]=b;u[m0]=a;con[m0]=c;cost[m0]=d;prep[m0]=head[a];head[a]=m0;
	v[++m0]=a;u[m0]=b;con[m0]=0;cost[m0]=-d;prep[m0]=head[b];head[b]=m0;
}

bool spfa() {
	memset(Dis,127,sizeof(Dis));
	memset(vis,0,sizeof(vis));
	Dis[S]=0; vis[S]=1; Que[Qhead=Qtail=1]=S;
	
	while(Qhead<=Qtail){
	for(int i=head[Que[Qhead]];i;i=prep[i])
		if(con[i]&&Dis[v[i]]>Dis[Que[Qhead]]+cost[i]) {
			Dis[v[i]]=Dis[Que[Qhead]]+cost[i];
			path[v[i]]=i;
			if(!vis[v[i]]) vis[Que[++Qtail]=v[i]] = 1;
		}
		vis[Que[Qhead]]=0;
		++Qhead;
	}
	return Dis[T]<2100000000;
}

void CostFlow(int UpperBound) {
	int x;
	Ans=0;
	memset(path,0,sizeof(path));
	while(spfa() && UpperBound--) {
		int f=0x7fffffff;
		for(x=T;x!=S;x=u[path[x]])
			f=Min(f,con[path[x]]);
		for(x=T;x!=S;x=u[path[x]]) {
			con[path[x]]-=f;
			con[path[x]^1]+=f;
		}
		Ans+=Dis[T]*(long long)f;
	}
	if (UpperBound > 0)
		Ans = -1;
}

int main() {
	int N, M;
	while (scanf("%d", &N) != EOF && N) {
		Clear();
		int tmpu = 0, tmpv = 0, tmpw = 0;
		scanf("%d", &M);
		for (int i=1; i<=M; i++) {
			scanf("%d%d%d", &tmpu, &tmpv, &tmpw);
			AddEdge(tmpu, tmpv, 1, tmpw);
			AddEdge(tmpv, tmpu, 1, tmpw);
		}
		S = 1;
		T = N;
		CostFlow(2);
		if (Ans < 0)
			puts("Back to jail");
		else
			printf("%d\n",Ans);
	} 
	return 0;
}