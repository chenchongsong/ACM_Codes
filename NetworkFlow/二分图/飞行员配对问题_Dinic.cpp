#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#define MaxNode 1007
#define MaxEdge 10007
#define MaxQue 200010
using namespace std;

// ==========  DINIC() ==========
// O(n^2*m)
// all con[]==1 O(min(n^(2/3),m(1/2))*m)
// 二分图匹配 O(n^(0.5) * m)
#define INF 0x3f3f3f3f
int m0 = 1, S, T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],NEXT[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];
int Min(int a,int b){return a<b?a:b;}
void Add(int a,int b,int c) {
v[++m0]=b;u[m0]=a;NEXT[m0]=head[a];head[a]=m0;con[m0]=c;
v[++m0]=a;u[m0]=b;NEXT[m0]=head[b];head[b]=m0;con[m0]=0;
}
int bfs() {
    int Qhead=0,Qtail=0;
    memset(vis,0,sizeof(vis));
    memset(dis,127,sizeof(dis));
    dis[S]=0;vis[S]=1;Q[++Qtail]=S;
    while(Qhead<Qtail) {
        ++Qhead;
        for(int i=head[Q[Qhead]];i;i=NEXT[i])
            if(!vis[v[i]] && con[i]) {
                vis[v[i]]=1;
                dis[v[i]]=dis[Q[Qhead]]+1;
                Q[++Qtail]=v[i];
            }
    }
    return vis[T];
}
int dfs(int now,int lim) {
    if (now==T || !lim) return lim;
    int flow=0, f;
    for (int& i=cur[now];i;i=NEXT[i]) {
        if (dis[v[i]]>dis[now] && con[i])
            if ((f=dfs(v[i],Min(lim-flow,con[i]))) > 0){
            flow+=f;
            con[i]-=f;
            con[i^1]+=f;
            if (flow==lim) break;
        }
    }
    return flow;
}
int DINIC() {
    int flow=0;
    while(bfs()) {
        memcpy(cur,head,sizeof(head));
        flow+=dfs(S,INF);
    }
    return flow;
}


int main() {
	int N, M, a, b;
	cin >> M >> N;
	S = N + 100;
	T = S + 1;
	for (int i=1; i<=M; i++) Add(S, i, 1);
	for (int i=M+1; i<=N; i++) Add(i, T, 1);
	while (cin >> a >> b && a != -1 && b != -1)
		Add(a, b, 1);

	int ans = DINIC();
	printf("%d\n", ans);

	for (int u=1; u<=M; u++) {
		for (int i=head[u];i;i=NEXT[i]) {
			if (!con[i] && M < v[i] && v[i] <= N)
				printf("%d %d\n", u,v[i]);
		}
	}
	
	return 0;
}
// 左半张图为1~m 右半张图为m+1~n
