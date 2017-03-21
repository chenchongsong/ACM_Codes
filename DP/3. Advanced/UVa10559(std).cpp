// 直接记dp[i][j]的话 决策会对之后造成影响 不满足无后效性
// 所以加一维k用作预期判断
// dp[i][j][k] 记第i~j块 + 后面并上k个与j颜色相同的block
#include <iostream>
#include <cstdio> 
#include <cstring>
#define maxn 210
using namespace std;
int N, a[maxn], dp[maxn][maxn][maxn];
int DFS(int l,int r,int k) {
    if(l > r) return 0;
    if(l == r) return (k+1)*(k+1);
    if(dp[l][r][k] > 0) return dp[l][r][k];
    dp[l][r][k] = DFS(l,r-1,0)+ (k+1)*(k+1);
    for(int i = l;i < r;i++)
        if(a[i] == a[r])
            dp[l][r][k] = max(dp[l][r][k], DFS(l,i,k+1) + DFS(i+1,r-1,0));
    return dp[l][r][k];
}
int main() {
    int T; cin >> T;
    for(int kase = 1;kase <= T;kase++) {
        memset(dp,-1,sizeof(dp));
        cin >> N;
        for(int i = 1;i <= N;i++) cin>>a[i];
        cout<<"Case "<< kase <<": "<<DFS(1,N,0)<<endl;
    }
}