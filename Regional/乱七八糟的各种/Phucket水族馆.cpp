#include <cstdio>
#include <algorithm>
using namespace std;
#define MaxN 1000010
#define MaxM 1000010
int R,C;
char s[500][500];
int Val[500][500];
int fa[MaxN];

int GetFa(int x)
{return fa[x]==x? x: fa[x]=GetFa(fa[x]);}

int Node(int x,int y,int z) {

//printf("Node %d %d %d\n",x,y,z);
	return (x*C + y)*4 +z; 


} 

int totEdge = 0;
int Ans;


struct E{int u,v,w;} ed[MaxM];
void AddEd(int x, int y, int z)
{ed[++totEdge].u = x; ed[totEdge].v = y; ed[totEdge].w = z;

//printf("%d-----from:%d to:%d len:%d\n", totEdge, x,y,z);
}

bool cmp(E A, E B){return A.w<B.w;}

void Clear()
{
	totEdge = 0;
	Ans = 0;
}


int main()
{
	int T;
	scanf("%d", &T);
	for (int Case=1;Case<=T;Case++)
	{
		
		Clear();
		scanf("%d%d",&R, &C);

		for (int i=0;i<R;i++)
			scanf("%s",s[i]);
		for (int i=0;i<R;i++)
			for (int j=0;j<C;j++)
				scanf("%d", &Val[i][j]);

		for (int i=0;i<R;i++)
			for (int j=0;j<C;j++)
			{
				if (j+1<C) AddEd(Node(i,j,2),Node(i,j+1,4),0);
				if (i+1<R) AddEd(Node(i,j,3),Node(i+1,j,1),0);
			}

		for (int i=0;i<R;i++)
			for (int j=0;j<C;j++)
				if (s[i][j]=='/')
				{
					AddEd(Node(i,j,1), Node(i,j,2), Val[i][j]);
					AddEd(Node(i,j,2), Node(i,j,3), 0);
					AddEd(Node(i,j,3), Node(i,j,4), Val[i][j]);
					AddEd(Node(i,j,4), Node(i,j,1), 0);
				}
				else 
				{
					AddEd(Node(i,j,1), Node(i,j,2), 0);
					AddEd(Node(i,j,2), Node(i,j,3), Val[i][j]);
					AddEd(Node(i,j,3), Node(i,j,4), 0);
					AddEd(Node(i,j,4), Node(i,j,1), Val[i][j]);
				}
		
		sort(ed+1,ed+totEdge+1,cmp);
		for (int i=1;i<=R*C*10;i++)
			fa[i] = i;
		
		int uu, vv;
		for (int i=1;i<=totEdge;i++)
		{
			
			uu = GetFa(ed[i].u);
			vv = GetFa(ed[i].v);

			//printf("%d-----%d %d-----%d\n",ed[i].u,uu,ed[i].v,vv);

			if (uu==vv) continue;
			
			//printf("%d---===---%d\n",ed[i].u,ed[i].v);
			Ans += ed[i].w;
			fa[uu] = vv;
		}
		printf("Case %d: %d\n", Case, Ans);



	}
	return 0;
}

/*

2
2 2
\/
\\
7 10
12 9

1
1 3
/\\
3 4 5

*/