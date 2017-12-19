#include <cstdio>
#include <cstring>
using namespace std;

char s[1010];
int map[1010][1010],vis[1010][1010];
int N, M, Ans, Case;

int f[1010][1010][5][3];

// Enter Directions:
//    1
// 2     3
//    4

int Cal(int i, int j)
{
	return f[i][j-1][3][1] + f[i-1][j][4][1]
		 + f[i][j+1][2][1] + f[i+1][j][1][1];
}

void Clear()
{
	Ans=0;
	memset(map,0,sizeof(map));
	memset(vis,0,sizeof(vis));
	memset(f,0,sizeof(f));
}

int main()
{
	scanf("%d",&Case);
	while (Case--)
	{
		Ans=0;
		Clear();
		scanf("%d%d",&N,&M);
		for (int i=1;i<=N;i++)
		{
			scanf("%s", s+1);

			for (int j=1;j<=M;j++)
				map[i][j] = s[j]-'0';
		}

		//
		for (int i=1;i<=N;i++)
		{
			for (int j=1;j<=M;j++)
				if (map[i][j])
				{
					f[i][j][3][1] = f[i-1][j][4][2] + 1;
					f[i][j][4][2] = f[i][j-1][3][1] + 1;
				}

			for (int j=M;j>=1;j--)
				if (map[i][j])
				{
					f[i][j][4][1] = f[i][j+1][2][2] + 1;
					f[i][j][2][2] = f[i-1][j][4][1] + 1;
				}
		}

		for (int i=N;i>=1;i--)
		{
			for (int j=1;j<=M;j++)
				if (map[i][j])
				{
					f[i][j][1][1] = f[i][j-1][3][2] + 1;
					f[i][j][3][2] = f[i+1][j][1][1] + 1;
				}

			for (int j=M;j>=1;j--)
				if (map[i][j])
				{
					f[i][j][1][2] = f[i][j+1][2][1] + 1;
					f[i][j][2][1] = f[i+1][j][1][2] + 1;
				}
		}
		int Tmp;
		for (int i=1;i<=N;i++)
			for (int j=1;j<=M;j++)
				if (map[i][j])
				{
					Tmp = Cal(i,j);
					if ( Tmp > Ans )
						Ans = Tmp;
						//printf("flskjflsj-----%d %d\n",i,j);
				}
				

		
		for (int i=1;i<=N;i++)
		{
			for (int j=1;j<=M;j++)
			{
				//printf("\n\ni--%d j--%d----------\n",i,j);
				//for (int k=1;k<=4;k++)
					//for (int l=1;l<=2;l++)
						//printf("k--%d l--%d. %d\n",k,l,f[i][j][k][l]);
			}
		}



		printf("%d\n", Ans+1);
	}
	return 0;
}