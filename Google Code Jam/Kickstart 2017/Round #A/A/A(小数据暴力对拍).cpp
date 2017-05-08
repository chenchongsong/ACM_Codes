#include <cstdio>
const long long mo = 1000000007;
using namespace std;
long long r, c, ans;
int main()
{
	//freopen("Desktop/Google Kickstart/A/A-small-practice.in","r",stdin);
    //freopen("Desktop/Google Kickstart/ans.txt","w",stdout);
	int T;
	scanf("%d", &T);
	for (int kase=1; kase<=T; kase++)
	{
		scanf("%lld%lld", &r, &c);
		r--; c--;
		ans = 0;
		//ans = (r * (r-1) * c * (c-1) / 4) % mo;
		//printf("Here %lld\n", ans);
		for (long long i=0;i<=r; i++)
			for (long long j=1;j<=c;j++)
			{
				long long xk = i, yk = i+j;
				long long xl = j+i, yl = j;
				if (xk > c || xl > c) continue;
				if (yk > r || yl > r) continue;
				ans += (r-i-j+1) * (c-i-j+1);
				ans %= mo; 
				//printf("%lld %lld:: %lld\n",i,j,ans);
			}
		printf("Case #%d: %lld\n", kase, ans);
	}
	return 0;
}