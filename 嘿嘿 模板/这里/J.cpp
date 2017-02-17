#include<cstdio>
#include<cstring>
#include <cmath>
#define INF 0x7fffffff
#define MaxNode 15000
#define MaxEdge 80000
#define MaxQue 1000000
#define in(x) 8+i*2-1
#define out(x) 8+i*2
int M,N,m0=1,Ans,S,T;
int head[MaxNode],u[MaxEdge],v[MaxEdge],next[MaxEdge],con[MaxEdge];
int Q[MaxQue],dis[MaxNode],cur[MaxNode],vis[MaxNode];


double X[MaxNode],Y[MaxNode],R[MaxNode];


int Min(int a,int b){return a<b?a:b;}

double Dist(int i,int j)
{double Tmp = fabs(X[i]-X[j])*fabs(X[i]-X[j])+fabs(Y[i]-Y[j])*fabs(Y[i]-Y[j]);
return sqrt(Tmp);}



void Add(int a,int b,int c)
{
	v[++m0]=b;next[m0]=head[a];head[a]=m0;con[m0]=c;
	v[++m0]=a;next[m0]=head[b];head[b]=m0;
}

int bfs()
{
	int Qhead=0,Qtail=0;
	memset(vis,0,sizeof(vis));
	memset(dis,127,sizeof(dis));
	dis[S]=0;vis[S]=1;Q[++Qtail]=S;
	while(Qhead<Qtail)
	{
		++Qhead;
		for(int i=head[Q[Qhead]];i;i=next[i])
			if(!vis[v[i]] && con[i])
			{
				vis[v[i]]=1;
				dis[v[i]]=dis[Q[Qhead]]+1;
				Q[++Qtail]=v[i];
			}
	}
	return vis[T];
}

int dfs(int now,int lim)
{
	if (now==T || !lim) return lim;
	int flow=0,f;
	for (int& i=cur[now];i;i=next[i])
	{
		if (dis[v[i]]>dis[now] && con[i])
		if (f=dfs(v[i],Min(lim-flow,con[i])))
		{
			flow+=f;
			con[i]-=f;
			con[i^1]+=f;
			if (flow==lim) break;
		}
	}
	return flow;
}

int DINIC()
{
	int flow=0;
	while(bfs())
	{
		memcpy(cur,head,sizeof(head));
		flow+=dfs(1,INF);
	}
	return flow;
}

int main()
{
	scanf("%d",&N);
	S=2;T=3; //Total=0;
	
	for (int i=1;i<=N;i++)
	{
		scanf("%lf",&X[i]);
		scanf("%lf",&Y[i]);
		scanf("%lf",&R[i]);
		Add(in(i),out(i),1);
	}
	
	for (int i=1;i<=N;i++)
	{
		for (int j=i+1;j<=N;j++)
		{
			if (Dist(i,j)<R[i]+R[j])
			{
				Add(out(i),in(j),INF);
				Add(out(j),in(i),INF);
			}
		}
	}
	for (int i=1;i<=N;i++)
	{
		if (X[i]<R[i])
			Add(S,in(i),INF);
		if (X[i]+R[i]>200.0)
			Add(out(i),T,INF);
	}
		
	
	
	
	
	


	Ans=DINIC();
	printf("%d\n",Ans);
	return 0;
}
