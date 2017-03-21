#include<cstdio>  
#include<string>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
const int MAXN = 222;  
const int INF = 0x7fffffff;  
char str[MAXN];  
int dp[MAXN][MAXN];  
int calNum(int n){  
    int cnt = 0;  
    while(n) cnt ++, n /= 10;  
    return cnt;  
}  
bool check(int n, int m, int k){  
    if((m - n + 1) % k) return false;  
    for(int i = 0 ;i < k;i ++){  
        for(int j = n + k ;j <= m; j += k){  
            if(str[j+i] != str[n+i]) return false;  
        }  
    }  
    return true;  
}  
int dfs(int n, int m){         //dp[n][m] = min(dp[n][k] + dp[k+1][m], calNum(k) + dp[n][n+k-1] + 2);  
    if(n == m) return 1;  
    if(dp[n][m]) return dp[n][m];  
    dp[n][m] = INF;  
    for(int i = 0; i <= m - n - 1; i ++){  
        dp[n][m] = min(dp[n][m], dfs(n, n + i) + dfs(n + i + 1, m));  
        if(check(n, m, i + 1)) dp[n][m] = min(dp[n][m], calNum((m - n + 1)/(i + 1)) + 2 + dfs(n, n + i));  
    }  
    return dp[n][m];  
}  
int main(){  
    int n;  
    //freopen("in.cpp", "r", stdin);  
    while(~scanf("%d", &n)){  
        for(int i = 0;i < n;i ++){  
            memset(dp, 0, sizeof(dp));  
            scanf("%s", str);  
            printf("%d\n", dfs(0, strlen(str)-1));  
        }  
    }  
    return 0;  
}  