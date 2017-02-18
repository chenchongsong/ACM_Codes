//滑动窗口优化 O(N+C)
#include <cstdio>
#include <cstring>
#include <deque> // or include <queue>
//front() back() size() empty()
//pop_front(..) push_front(..)
//pop_back() pop_front()
#define MaxN 100010
using namespace std;

int x[MaxN], y[MaxN], w[MaxN];
int dp[MaxN];
int sum_dis[MaxN], sum_weight[MaxN], dis2o[MaxN];

int func(int j){return dp[j] - sum_dis[j+1] + dis2o[j+1];}
int abs(int x){return x<0?-x:x;}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int C, N;
		scanf("%d%d", &C, &N);
		deque <int> q; //双端队列STL 对于每个testCase都要新建
		q.push_back(0);

		for (int i=1; i<=N; i++)
		{
			scanf("%d%d%d", &x[i], &y[i], &w[i]);
			sum_weight[i] = sum_weight[i-1] + w[i];
			sum_dis[i] = sum_dis[i-1] + abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
			dis2o[i] = abs(x[i]) + abs(y[i]);
		}
		for (int i=1; i<=N; i++)
		{
			while (!q.empty() && sum_weight[i]-sum_weight[q.front()] > C) //滑动窗口的左端向右移
				q.pop_front();

			dp[i] = func(q.front()) + sum_dis[i] + dis2o[i];

			while (!q.empty() && func(i) <= func(q.back()) ) q.pop_back(); //用当前的i来更新
			q.push_back(i); //把i塞入队列
		}
		printf("%d\n", dp[N]);
		if (T) puts(""); 
	}
	return 0;
}

/*

2
10
4
1 2 3
1 0 3
3 1 4
3 1 4
10
4
1 2 3
1 0 3
3 1 4
3 1 4

*/