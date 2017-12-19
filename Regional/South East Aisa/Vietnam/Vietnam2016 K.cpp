#include <cstdio>
#include <cstring>
#include <algorithm>
#define MaxN 1010
using namespace std;
int A[MaxN], f[MaxN][MaxN];
int Case, N;
//int max(int a, int b){return a>b?a:b;}

int main()
{
	scanf("%d", &Case);
	while (Case--)
	{
		memset(A,0,sizeof(A));
		memset(f,0,sizeof(f));
		scanf("%d", &N);
		for (int i=1;i<=N*3;i++)
			scanf("%d", &A[i]);
		sort(A+1, A+N*3+1);
		for (int i=1;i<=N*3;i++)
			for (int j=1;j<=i;j++)
				for (int k=1;k<i;k++)
				{
					f[i][j] = max(f[i][j], f[k][j]);
					// if (i >= j*2 && N*3-i >= j)
					if (i >= j*2 && N*3-i >= 1+(N-j)*2)
						f[i][j] = max(f[i][j], f[k][j-1]+A[i]);
				}
		// for (int i=1;i<=N*3;i++)
		// {
		// 	for (int j=1;j<=N;j++)
		// 		printf("%d %d::  %d\n",i,j,f[i][j]);
		// }
		printf("%d\n", f[N*3][N]);
	}
	return 0;
}
/*
1
3
4 5 6
7 8 9
1 2 3

1
3
1 1 1
4 4 4
5 5 5

should be 13

*/

