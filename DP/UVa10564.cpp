#include <cstdio>
#include <cstring>
#define maxn 30
#define maxs 510
int const INF = (int) 1e8; 
int a[maxn][maxn];
int f[maxn][maxn][maxs];
int path[maxn][maxn][maxs];
int N, s;
//char ans2[maxn];

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

		/*for (int i=1;i<=N*2-1;i++)
		{
			for (int j=1;j<=N;j++)
				printf("*%d ", a[i][j]);
			puts("");
		}*/
//initialization (反过来做 保证字典序最小)
		for (int j=1;j<=N;j++)
			f[2*N-1][j][a[2*N-1][j]] = 1;

// 下半段
		for (int i=2*N-2; i>=N; i--)
			for (int j=1; j<=(i-N+1); j++)
				for (int sum=0; sum<=s;sum++)
				{
					if (sum-a[i][j] >= 0)
					{ //printf("IN %d\n", sum);
						//printf("======%d %d %d\n", i-1, j, sum-a[i][j]);
						if (f[i+1][j+1][sum-a[i][j]])
						{  //printf("Here %d %d %d\n", i+1, j+1, a[i][j]);

							f[i][j][sum]+=f[i+1][j+1][sum-a[i][j]];
							path[i][j][sum] = 1;
						}
						//if (i==11 && j==5 && sum==41)
							//printf("kengdie %d\n", path[i][j][sum]);
						//printf("======%d %d %d\n", i-1, j-1, f[i-1][j-1][sum-a[i][j]]);
						if (f[i+1][j][sum-a[i][j]])
						{
							f[i][j][sum]+=f[i+1][j][sum-a[i][j]];
							path[i][j][sum] = 0;
							//printf("Here %d %d %d\n", i+1, j, a[i][j]);
						}// L/R都可行的时候保留L 这样保证了字典序最小
						//if (i==11 && j==5 && sum==41)
							//printf("kengdie %d\n", path[i][j][sum]);
					} //printf("?????????????????????%d %d sum %d::----f %d.  path %d\n",i,j,sum,f[i][j][sum],path[i][j][sum]);		
				}

// 上半段
		for (int i=N-1;i>=1;i--)
		{
			for (int j=1; j<=(N-i+1); j++)
			{
				for (int sum=0; sum<=s;sum++)
				{
					if (sum-a[i][j] >= 0)
					{
						if (f[i+1][j][sum-a[i][j]])
						{
							
							f[i][j][sum]+=f[i+1][j][sum-a[i][j]];
							path[i][j][sum] = 0;
						}
						if (f[i+1][j-1][sum-a[i][j]])
						{
							
							f[i][j][sum]+=f[i+1][j-1][sum-a[i][j]];
							path[i][j][sum] = -1;
						}
					}
					//printf("?????????????????????%d %d sum %d::----f %d.  path %d\n",i,j,sum,f[i][j][sum],path[i][j][sum]);
					
				}
			}
		}

		
		int ans1 = 0, ans2, MIN = 100;
		for (int j=N;j>=1;j--)
		{
			//printf("%d---%d\n", j, f[1][j][s]);
			if (f[1][j][s])
			{
				ans1 += f[1][j][s];
				if (a[1][j]<MIN)
					MIN = a[1][j],
					ans2 = j;
			}
		}
		if (ans1==0) {puts("0\n");continue;}

		printf("%d\n%d ", ans1, a[1][ans2]);
		int sum = s, j = ans2;
		int last_j = j;
		for (int i=1; i<N; i++)
		{
			//printf("pos @ %d %d path %d\n", i,j, path[i][j][sum]);
			printf("%c", (path[i][j][sum]==0)?'R':'L');
			//printf("%c", );
			last_j = j;
			j += path[i][j][sum];
			sum -= a[i][last_j];

			//printf("%d---+++\n",j);
			
			
			
		}

		for (int i=N; i<=2*N-2; i++)
		{
			//printf("pos @ %d %d\n",i,j);
			printf("%c", (path[i][j][sum]==0)?'L':'R');
			last_j = j;
			j += path[i][j][sum];
			sum -= a[i][last_j];
			
			
		}
		puts("");


	}

}

/*

6 41
6 7 2 3 6 8
1 8 0 7 1
2 6 5 7
3 1 0
7 6
8
8 8
6 5 3
9 5 9 5
6 4 4 1 3
2 6 9 4 3 8
2 7
3 1
2
3 5
5 26
2 8 7 2 5
3 6 0 2
1 3 4
2 5
3
7 2
2 9 3
1 0 4 4
4 8 7 2 3
0 0

*/