//题意：原图每条边都要至少跑过一次
//最小费用 可行流（不是最大流 因为原图每条边容量没有上限制）

// 建立超级源点S和超级汇点T 
// 对于原图的每条边(i,j) 
// 连边：
// S−>j 费用为v，流量为1
// i−>j 费用为v，流量为无穷（无穷-1）
// i−>T 费用为0,流量为1
// 对所有的点都连一条到1的流量为无穷费用为0的边 
// 跑最小费用最大流就是答案！



#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MaxN 310
#define MaxM 150010
#define MaxQ 5000010
#define INF (int)1e10
using namespace std;

int Que[MaxQ], Qhead, Qtail;

int Dis[MaxN], head[MaxN], path[MaxN];
int u[MaxM], v[MaxM], prep[MaxM], con[MaxM], cost[MaxM];
bool vis[MaxN];

int N, S, T, old_s, old_t, m0=1, Ans;

int sc()
{
    int i=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')i=i*10+c-'0',c=getchar();
    return i*f;
}

void AddEdge (int a,int b,int c,int d) {
	v[++m0]=b;u[m0]=a;con[m0]=c;cost[m0]=d;prep[m0]=head[a];head[a]=m0;
 	v[++m0]=a;u[m0]=b;con[m0]=0;cost[m0]=-d;prep[m0]=head[b];head[b]=m0;
 }

bool spfa() {
	memset(Dis,127,sizeof(Dis)); memset(vis,0,sizeof(vis));
	Dis[S]=0; vis[S]=1; Que[Qhead=Qtail=1]=S;
	while(Qhead<=Qtail)
	{
		for(int i=head[Que[Qhead]];i;i=prep[i])
			if(con[i]&&Dis[v[i]]>Dis[Que[Qhead]]+cost[i])
			{
				Dis[v[i]]=Dis[Que[Qhead]]+cost[i];
				path[v[i]]=i;
				if(!vis[v[i]]) vis[Que[++Qtail]=v[i]]=1;
			}
		vis[Que[Qhead]]=0;
		++Qhead;
	}
	return Dis[T]<2100000000;
}

void CostFlow() {
	int x;
	Ans=0;
	memset(path,0,sizeof(path));
	while(spfa())
	{
		int f=INF;
		for(x=T;x!=S;x=u[path[x]])
			f=min(f,con[path[x]]);
		for(x=T;x!=S;x=u[path[x]])
		{
			con[path[x]]-=f;
			con[path[x]^1]+=f;
		}
		Ans+=Dis[T]*f;
	}
}

int main()
{
	N = sc();
	S = N + 1;
	T = N + 2;
	//old_S = 1;
	for (int i=1;i<=N;i++)
	{
		int M = sc();

		AddEdge(i,T,M,0);
		AddEdge(i,1,INF,0);
		for (int j=1;j<=M;j++)
		{
			int to = sc(), time = sc();
			AddEdge(i,to,INF,time);
			AddEdge(S,to,1,time);
		}
	}
	CostFlow();
	printf("%d\n",Ans);
	return 0;
}


/*

6
2 2 1 3 2
2 4 3 5 4
2 5 5 6 6
0
0
0

*/