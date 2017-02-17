#include <cstdio>
#include <queue>
#include <cstring>
#define MaxN 500010
using namespace std;
int v[MaxN];
bool done[MaxN], isK[MaxN];
int deg[MaxN]; //入度
int cnt, ans[MaxN];

void Clear()
{
	memset(v, 0, sizeof(v));
	memset(done, 0, sizeof(done));
	memset(isK, 0, sizeof(isK));
	memset(deg, 0, sizeof(deg));
	memset(ans, 0, sizeof(ans));
	cnt = 0;
}

int main()
{
	int to, N;
	while (scanf("%d", &N)!=EOF)
	{
		Clear();
		for (int i=1;i<=N*2;i++)
		{
			scanf("%d", &to);
			v[i] = to;
			deg[to]++;
		}

		queue <int> q;	

		for (int i=1;i<=N*2;i++)
			if (!deg[i])
			{
				q.push(i);
				done[i] = 1;
				isK[i] = 1;
			}

		while (!q.empty())
		{
			int Qhead = q.front();
			q.pop();
			
			
			int to = v[Qhead];	

			/*for (int i=1;i<=2*N;i++)
			{
				printf("%d-%d ", i, isK[i]);
			}
			puts("");
			for (int i=1;i<=2*N;i++)
				printf("%d-%d ",i,done[i]);	

			printf("head=%d to==%d\n", Qhead, to);*/
			deg[to]--;	
	

			if (done[to]) continue;
			if (isK[Qhead])
			{
				isK[to] = 0;
				done[to] = 1;
				q.push(to);
				continue;
			}
			if (!deg[to])
			{
				isK[to] = 1;
				done[to] = 1;
				q.push(to);
			}	

		}
		//
		cnt = 0;
		for (int i=1;i<=N*2;i++)
		{
			if (isK[i])
			{
				ans[++cnt] = i;
				continue;
			}
				
			if (done[i]==0 && i<=N)
				ans[++cnt] = i;
		}
		
		for (int i=1;i<cnt;i++)
			printf("%d ", ans[i]);
		printf("%d ", ans[cnt]);
		puts("");
	}
	return 0;
}
/*

4
5 6 7 7
1 3 2 3

*/
