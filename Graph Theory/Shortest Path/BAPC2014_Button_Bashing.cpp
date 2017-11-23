#include <cstdio>
#include <cstring>
#include <iostream>
#define MaxN 40000
#define MaxM 900000
#define INF 0x3f3f3f3f
#define MaxQ 3000000
using namespace std;

// ==========  SPFA ==========
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
       vis[Que[Qhead]]=0;   ++Qhead;
       }
}

void Clear() {
      int tot = 0;
      memset(v, 0, sizeof(v));
      memset(NEXT, 0, sizeof(NEXT));
      memset(w, 0, sizeof(w));
      memset(head, 0, sizeof(head));
}

int button[MaxN];

int main() {
      int TC, N, tar;
      cin >> TC;
      while (TC--) {
            Clear();
            cin >> N >> tar;
            for (int i=1; i<=N; i++) {
                  cin >> button[i];
                  for (int t = 0; t <= 3600; t++) {
                        int to = t + button[i];
                        if (to < 0) to = 0;
                        if (to > 3600) to = 3600;
                        AddEdge(t, to, 1);
                  }
            }
            Spfa(0);
            for (int t=tar; t<=3600; t++) {
                  if (Dis[t] < INF) {
                        printf("%d %d\n", Dis[t], t-tar);
                        break;
                  } 
            }
      }
      return 0;
}