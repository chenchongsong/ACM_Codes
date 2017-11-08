#include<cstdio>  
#include<algorithm>  
using namespace std;  
const int inf = 1 << 30;  
const int maxn = 1000 + 5;  
int dp[maxn][maxn], s[maxn][maxn], a[maxn], sum[maxn];  
  
//四边形不等式优化   
int solve(int n){  
    for(int i = 1; i <= n; ++i) {  
        dp[i][i] = 0;  
        s[i][i] = i;  
    }  
    for(int l = 2; l <= n; ++l) {  
        for(int i = 1; i <= n - l + 1; ++i) {  
            int j = i + l - 1;  
            dp[i][j] = inf;  
            int x = s[i][j-1], y = s[i+1][j];  
            for(int k = x; k <= y; ++k) {  
                int h = dp[i][k] + dp[k+1][j] + sum[j] - sum[i-1];  
                if(h < dp[i][j]) {  
                    dp[i][j] = h;  
                    s[i][j] = k;  
                }  
            }  
        }  
    }  
    return dp[1][n];  
}  
  
int main(){  
    int n;  
    while(scanf("%d", &n) == 1){  
        sum[0] = 0;  
        for(int i = 1; i <= n; ++i) {  
            scanf("%d", &a[i]);  
            sum[i] = sum[i - 1] + a[i];  
        }  
        printf("%d\n", solve(n));  
    }  
    return 0;  
}  