#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define MOD 1000000

using namespace std;

typedef long long int LL;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        LL n,ans=0;
        scanf("%lld",&n);
        LL i=1;
        while(i<=n)
        {
            LL j=n/(n/i);
            //printf("i--%lld j--%lld\n",i,j);

            ans=(ans+((j-i+1)*(n/i))%MOD)%MOD;
            //i~j:  (int)n/i == (int)n/j 全部都是

            i=j+1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}