// directed
// time 460ms

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define MaxN 2000010
#define MaxM 2000010
#define MaxQ 3000010
#define INF 0x3f3f3f3f
using namespace std;

// 最短路
// ==========  SPFA ==========
int tot=0,v[MaxM],NEXT[MaxM],w[MaxM],head[MaxN]; //memset
int Dis[MaxN],Que[MaxQ];
bool vis[MaxN];

void AddEdge(int a,int b,int c)
{v[++tot]=b;w[tot]=c;NEXT[tot]=head[a];head[a]=tot;}

void Spfa(int Source) {
	memset(Dis,0x3f,sizeof(Dis));
	memset(vis, 0, sizeof(vis));
	int Qhead=1, Qtail=1;
	Dis[Que[1]=Source]=0;
	while(Qhead<=Qtail) {
		for(int i=head[Que[Qhead]];i;i=NEXT[i])
		if(Dis[Que[Qhead]]+w[i]<Dis[v[i]]) {
			Dis[v[i]]=Dis[Que[Qhead]]+w[i];
			if(!vis[v[i]]) {
				vis[v[i]]=1;
				Que[++Qtail]=v[i];
			}
		}
		vis[Que[Qhead]]=0;
		++Qhead;
	}
}
// S = ???;   // Spfa();

int main() {
	int N, M, S;
	cin >> N >> M >> S;
	for (int i=1; i<=M; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c); // directed
	}
	Spfa(S);
	for (int i=1; i<=N; i++) {
		printf("%d ", Dis[i] == INF ? 2147483647 : Dis[i]);
	}
	return 0;
}