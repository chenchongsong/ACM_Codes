#include <cstdio>
#include <cstring>
#include <iostream>
#define MaxN 110
#define MaxM 10010
#define MaxQ 2000010
using namespace std;
#include <vector>
#include <queue>

vector<int> G[MaxN];
int tot=0,v[MaxM],NEXT[MaxM],w[MaxM],head[MaxN]; //memset
int Dis[MaxN],Que[MaxQ];
bool vis[MaxN];
void AddEdge(int a,int b,int c)
{v[++tot]=b;w[tot]=c;NEXT[tot]=head[a];head[a]=tot;}
void Spfa(int Source) {
	memset(Dis,63,sizeof(Dis));
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
// S = ???;
// Spfa();

void Clear() {
	tot = 0;
	memset(v, 0, sizeof(v));
	memset(NEXT, 0, sizeof(NEXT));
	memset(w, 0, sizeof(w));
	memset(head, 0, sizeof(head));
}
int main() {
	int N, M;
	while (cin >> N >> M && N && M) {
		Clear();
		for (int i=1; i<=M; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			AddEdge(a, b, c);
			AddEdge(b, a, c);
		}
		Spfa(1);
		printf("%d\n", Dis[N]);
	}
	return 0;
}
