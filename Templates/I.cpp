
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MaxN 500010

int n,q,tot=0;
int fa[MaxN],Clock[MaxN],vis[MaxN];
int v[MaxN*2],head[MaxN],next[MaxN*2];
int f[MaxN][25];
//f[i,j]记录i结点向上走2^j步后所到达的祖先

int Ans;

int root, size[MaxN];


void dfs(int now,int clock_now)
{
	Clock[now]=clock_now;  //在dfs树上的深度
	for (int i=1;i<=20;i++)
	{
		f[now][i]=f[f[now][i-1]][i-1];
	}
	for (int i=head[now];i;i=next[i])
		if (!Clock[v[i]])
		{
			f[v[i]][0]=now;
			dfs(v[i],clock_now+1);
		}
}

int LCA(int a,int b)
{

	if (Clock[a]>Clock[b])
	{
		int t=a;
		a=b;b=t;
	}

	for (int i=20;i+1;i--)
		if (Clock[f[b][i]]>Clock[a])
			b=f[b][i];
	
	Ans = b;


//printf("Ans==%d\n\n",Ans);

	b = f[b][0];//将ab移动至同一深度
	

	
	if (a==b) return a;
	//Ans = 0;


	for (int i=20;i+1;i--)
		if (f[a][i]!=f[b][i])
		{
			a=f[a][i];b=f[b][i];
		}//向上找到LCA
	
	/*if (newroot == 1)
		Ans = a;
	else
		Ans = b;*/


	return f[a][0];
}



void Clear()
{
	root = 0;
	tot = 0;
	memset(vis,0,sizeof(vis));
	memset(fa,0,sizeof(fa));
	memset(v,0,sizeof(v));
	memset(next,0,sizeof(next));
	memset(Clock,0,sizeof(Clock));
	memset(head,0,sizeof(head));
	memset(f,0,sizeof(f));
	memset(size,0,sizeof(size));

}

void DFS(int x)
{
	vis[x] = 1;
	int Cnt = 1;
	//printf("v%d\n",head[x]);
	for (int i=head[x];i;i=next[i])
	{
		
		if (!vis[v[i]])
		{
			
			DFS(v[i]);
			Cnt += size[v[i]];
			fa[v[i]] = x;
		}
	}
	size[x] = Cnt;
}

int main()
{
int T;
scanf("%d",&T);
for (int Case =1; Case<=T;Case++)
{
	Clear();

	scanf("%d%d%d",&n,&q, &root);
	//printf("%d q%d. r%d\n",n,q,root);

	for (int i=1;i<n;i++)
	{
		int uu,vv;
		scanf("%d%d",&uu,&vv);


		v[++tot]=vv;next[tot]=head[uu];head[uu]=tot;
		v[++tot]=uu;next[tot]=head[vv];head[vv]=tot;
			//fa[x]=y;
		
	}
		
	DFS(root);
	/*for (int i=1;i<=n;i++)
	{
		printf("%d-- %d\n",i,size[i]);
	}*/





	
	for (int i=1;i<=n;i++)
		if (!Clock[i]) dfs(i,1);

	int newroot = root;
	
	printf("Case #%d:\n", Case);
	for (int i=1;i<=q;i++)
	{
		int ch, Tmp;
		scanf("%d%d",&ch, &Tmp);
		

//printf("ch--%d Tmp %d\n",ch,Tmp);

		if (ch==0)
		{
			newroot = Tmp;

		}
		else
		{
			if (Tmp == newroot) {printf("%d\n",n);continue;}

			int Zuxian = LCA(Tmp,newroot);
			if (Zuxian != Tmp)
				printf("%d\n", size[Tmp]);
			else
			{
				printf("%d\n", n-size[Ans]);
			}

		}
	}
	

//for (int i=1;i<=n;i++)
	//for (int j=1;j<=n;j++)
		//printf("LCA %d---%d. : %d\n",i,j,LCA(i,j));



}
	return 0;
}
/*

1
5 5 1
1 2
3 1
4 1
1 5





*/

