#include <iostream>
#include <cstdio>
#include <algorithm>
#define INF 0x7fffffff
// #define MaxN 10010

int g[100000+100];

using namespace std;
typedef pair<int, int> pii;
int seg[100000+100], dp[100000+100], K, N, mmax;
pii v[100000+100];
int main(){
    cin>>N>>K;
    for(int i=1; i<=N; i++){
        int tmp;
        //cin>>tmp;
        scanf("%d", &tmp);
        v[i]=make_pair(tmp, i);
    }
    sort(v+1, v+N+1);
    for(int i=1; i<=N; i++)
        seg[v[i].second]=(i-1)/K;

int Ans = 0;

// for (int i=1; i<=N; i++)
//     printf("%d --- %d\n",i,seg[i]);

	
// strictly increasing
for (int i=2;i<=N+1;i++) g[i]=INF;
for (int i=1;i<=N;i++)
{
	int k=upper_bound(g+2,g+N+2,seg[i]) - g;
	dp[i] = k-1; //  以A[i]结尾的LIS长度
	Ans = max(Ans, dp[i]);
	g[k] = seg[i];
}

	printf("%d\n",N - Ans);

	return 0;

}