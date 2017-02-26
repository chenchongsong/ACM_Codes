#include <cstdio>
#include <cstring>
#define maxn 30
#define maxs 510
int const INF = (int) 1e8; 
int a[maxn][maxn];
int f[maxn][maxn][maxs];
int path[maxn][maxn][maxs];
int N, s;
char ans2[maxn];

void Clear()
{
	memset(a, 0, sizeof(a));
	memset(f, 0, sizeof(f));
	memset(path, 0, sizeof(path));
}

int main()
{
	while (scanf("%d%d", &N, &s)==2 && (N||s))
	{
		Clear();
		for (int i=1; i<=N; i++)
		{
			for (int j=1; j<=(N-i+1); j++)
				scanf("%d", &a[i][j]);
		}
		for (int i=N+1; i<=2*N-1; i++)
			for (int j=1; j<=(i-N+1); j++)
			{
				scanf("%d", &a[i][j]);
			}

		for (int i=1;i<=N*2-1;i++)
		{
			for (int j=1;j<=N;j++)
				printf("*%d ", a[i][j]);
			puts("");
		}

		for (int j=1;j<=N;j++)
			f[1][j][a[1][j]] = 1;
		for (int i=2;i<=N;i++)
		{
			for (int j=1; j<=(N-i+1); j++)
			{
				for (int sum=0; sum<=s;sum++)
				{
					if (sum-a[i][j] >= 0)
					{
						if (f[i-1][j][sum-a[i][j]])
						{
							
							f[i][j][sum]+=f[i-1][j][sum-a[i][j]];
							path[i][j][sum] = 0;
						}

					//if (sum-a[i-1][j+1] >= 0)
						if (f[i-1][j+1][sum-a[i][j]])
						{
							
							f[i][j][sum]+=f[i-1][j+1][sum-a[i][j]];
							path[i][j][sum] = 1;
						}
					}
					printf("?????????????????????%d %d sum %d::----f %d.  path %d\n",i,j,sum,f[i][j][sum],path[i][j][sum]);
					
				}
			}
		}
		for (int i=N; i<=2*N-1; i++)
			for (int j=1; j<=(i-N+1); j++)
				for (int sum=0; sum<=s;sum++)
				{
					if (sum-a[i][j] >= 0)
					{ //printf("IN %d\n", sum);
						//printf("======%d %d %d\n", i-1, j, sum-a[i][j]);
						if (f[i-1][j][sum-a[i][j]])
						{//printf("Here %d %d %d\n", i-1, j, sum-a[i][j]);

							f[i][j][sum]+=f[i-1][j][sum-a[i][j]];
							path[i][j][sum] = 0;
						}
						if (i==11 && j==5 && sum==41)
							printf("kengdie %d\n", path[i][j][sum]);
						//printf("======%d %d %d\n", i-1, j-1, f[i-1][j-1][sum-a[i][j]]);
						if (f[i-1][j-1][sum-a[i][j]])
						{
							f[i][j][sum]+=f[i-1][j-1][sum-a[i][j]];
							path[i][j][sum] = -1;
							//printf("Here %d %d %d\n", i-1, j, sum-a[i][j]);
						}
						if (i==11 && j==5 && sum==41)
							printf("kengdie %d\n", path[i][j][sum]);
					} printf("?????????????????????%d %d sum %d::----f %d.  path %d\n",i,j,sum,f[i][j][sum],path[i][j][sum]);		
				}
		int ans1 = 0, tmp;
		for (int j=1;j<=N;j++)
		{
			printf("%d---%d\n", j, f[2*N-1][j][s]);
			if (f[2*N-1][j][s])
			{
				ans1 += f[2*N-1][j][s];
				tmp = j;
			}
		}
		if (ans1==0) {puts("0\n");continue;}

		int j = 3;
		printf("%d ", ans1);
		int sum = s, last_j = j;
		int cnt = 0;
		for (int i=2*N-1; i>=N+1; i--)
		{
			printf("pos @ %d %d\n", i,j);
			ans2[++cnt] = (path[i][j][sum]==0)?'L':'R';
			//printf("%c", );
			last_j = j;
			j += path[i][j][sum];
			sum -= a[i][last_j];
			
		}
		for (int i=N; i>=2; i--)
		{
			printf("pos @ %d %d\n",i,j);
			ans2[++cnt] = (path[i][j][sum]==0)?'R':'L';
			last_j = j;
			j += path[i][j][sum];
			sum -= a[i][last_j];
		}
		for (int i=cnt; i; i--)
		{
			printf("%c", ans2[i]);
		}
		puts("");


	}

}