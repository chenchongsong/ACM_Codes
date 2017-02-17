#include <cstdio>
#include <cstring>
#include <algorithm>
#define MaxN 3000// max number of nodes
#define MaxM 150010
//max number of edges = ( (N*M*2)+const )*2
#define MaxQ 5000010
#define INF (int)1e8
using namespace std;

int Que[MaxQ], Qhead, Qtail;
int Dis[MaxN], head[MaxN], path[MaxN];
int u[MaxM], v[MaxM], prep[MaxM], con[MaxM], cost[MaxM];
bool vis[MaxN];

int N, M, S=1, T=2, old_S=3, old_T=4, m0=1, Ans;
int digit_T=5, letter_T=6, char_T=7;
char s[110];
int map[110][110];

void AddEdge (int a,int b,int c,int d) {
	//printf("%d ---> %d  con==%d  weight==%d\n",a,b,c,d);
	v[++m0]=b;u[m0]=a;con[m0]=c;cost[m0]=d;prep[m0]=head[a];head[a]=m0;
 	v[++m0]=a;u[m0]=b;con[m0]=0;cost[m0]=-d;prep[m0]=head[b];head[b]=m0;
 }

void AddEdge_Lower_Bound (int u, int v, int lower, int upper, int w) {
	//puts("below 3 lines lower_boud");
	AddEdge(S,v,lower,w);
	//AddEdge(u,v,upper-lower,w);
	AddEdge(u,T,lower,0);

	//puts("--------");
	//同一个u到S或者T 如果各边weight一样的话 需要把这些边合并
}

bool spfa() {
	memset(Dis,127,sizeof(Dis));
	memset(vis,0,sizeof(vis));
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

int Node(int i, int j) {return (i-1)*M+j+10;}
int Op(int pos) {return min( pos-1, M-pos+1);}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=1;i<=N;i++)
	{
		scanf("%s", s+1);
		AddEdge_Lower_Bound( old_S, Node(i,1), 1, 1, 0);
		for (int j=1;j<=M;j++)
		{
			if ('0'<=s[j] && s[j]<='9')
			{
				AddEdge(Node(i,j), digit_T, 1, 0);
				if (j==1) continue;
				AddEdge(Node(i,1), Node(i,j), 1, Op(j));
				continue;
			}
			if ('a'<=s[j] && s[j]<='z')
			{
				AddEdge(Node(i,j), letter_T, 1, 0);
				if (j==1) continue;
				AddEdge(Node(i,1), Node(i,j), 1, Op(j));
				continue;
			}
			//if (s[j]=='#' || s[j]=='*' || s[j]=='&')
			{
				AddEdge(Node(i,j), char_T, 1, 0);
				if (j==1) continue;
				AddEdge(Node(i,1), Node(i,j), 1, Op(j));
				//continue;
			}
		}
	}
	AddEdge_Lower_Bound(digit_T, old_T, 1, N, 0);
	AddEdge_Lower_Bound(letter_T, old_T, 1, N, 0);
	AddEdge_Lower_Bound(char_T, old_T, 1, N, 0);
	AddEdge(old_T, old_S, INF, 0);
	CostFlow();
	printf("%d\n",Ans);
	return 0;
}