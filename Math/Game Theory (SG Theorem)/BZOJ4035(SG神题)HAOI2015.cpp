// https://cydiater.space/2017/04/05/BZOJ4035-%E6%95%B0%E7%BB%84%E6%B8%B8%E6%88%8F/
// http://blog.csdn.net/lych_cys/article/details/50896005

#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
#define up(i,j,n)   for(int i=j;i<=n;i++)
#define down(i,j,n) for(int i=j;i>=n;i--)
#define cmax(a,b)   a=max(a,b)
#define cmin(a,b)   a=min(a,b)
#define MAXN (int)1e5+5
using namespace std;

int T, N, sgin[MAXN], sgout[MAXN];
int B, mark[MAXN], M;

int nxt(int x,int y){return (x==y)?x+1:y/(y/(x+1));}

namespace solution{
    void Prepare(){ // initialize sgin & sgout O(N)
        scanf("%d%d", &N, &T);
        B = sqrt(N);
        for (int i=1; i<=N; i=nxt(i, N)){ // O(N^0.5)
            // i belongs to the distinct set of ceil(N/x), x<=N
            // N/N, N/(N/2), ...
            int now=0;
            for (int j=2; j<=i; j=nxt(j, i)){ // O(i^0.5)
                // i == tmp * j
                int tmp = i/j;
                int sg = (tmp<=B ? sgin[tmp] : sgout[N/tmp]);
                mark[now^sg] = i;
                if( (i/tmp-i/(tmp+1))&1 )
                    now ^= sg;
            }
            now = 1;
            while (mark[now] == i)
                now++;
            if (i <= B) sgin[i] = now;
            else sgout[N/i] = now;
        }
    }
    void Solve(){
        while(T--){
            scanf("%d",&M);
            int sgsum=0,t;
            while(M--){
                scanf("%d",&t);
                t=N/t;
                sgsum^=(t<=B?sgin[t]:sgout[N/t]);
            }
            puts(sgsum?"Yes":"No");
        }
    }
}

int main(){
    using namespace solution;
    Prepare();
    Solve();
    return 0;
}