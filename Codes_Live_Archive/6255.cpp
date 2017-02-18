#include <cstdio>
#include <cstring>
using namespace std;
bool dp[1<<21];
int money[21][21];
int Ans[21];

int main()

{
	int Case, N;
	scanf("%d", &Case);
	while (Case--)
	{
		scanf("%d", &N);
		for (int i=0;i<N;i++)
		{
			for (int j=0;j<N;j++)
				scanf("%d", &money[i][j]);
		}
		memset(dp, false, sizeof(dp));
		dp[(1<<N)-1] = true;
		for (int st=(1<<N)-1; st; st--)
		{
			if (!dp[st]) continue;
			for (int i=0;i<N;i++) // 枚举下一个倒闭的王国
			{
				int sum = 0; //
				if ( st & (1<<i) ) // 这个王国还没倒闭
				{
					for (int j=0;j<N;j++)
						if ( st & (1<<j) )
							sum += money[i][j];

					if (sum>0) // 这个国家i钱的钱的钱太多了 可以倒闭
						dp[st ^ (1<<i) ] = true;

				}
			}
		}

		int cnt = 0;
		for (int i=0;i<N;i++)
			if (dp[1<<i])
			{
				Ans[++cnt] = i+1;
				//printf("%d ", i+1);
			}

		if (!cnt) {puts("0"); continue;}
		//puts("");
		for (int i=1;i<cnt;i++)
			printf("%d ", Ans[i]);
		printf("%d\n", Ans[cnt]);
	}
	return 0;
}