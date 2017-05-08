#include <cstdio>
using namespace std;

long long a[100000];
const long long MOD = 1000000007;
long long n, T;

long long pow(long long a,long long i){
 	if (i==0) return 1;
 	long long temp = pow(a,i>>1);
 	temp = temp * temp % MOD;
 	if (i & 1)
 		temp= (long long) temp * a % MOD;
 	return temp % MOD;
}

int main() {
	freopen("Desktop/kickstart B/code/A-large.in", "r", stdin);
	freopen("Desktop/kickstart B/code/ans1.out", "w", stdout);
	scanf("%lld", &T);
	for (long long kase=1; kase<=T; kase++ ) {
		scanf("%lld", &n);

		long long ans = 0;
		for (long long i=1;i <= n;i ++) {
			scanf ("%lld", &a[i]);
			
			ans += a[i] * pow(2, i-1);
			ans -= a[i] * pow(2, n-i);
			ans %= MOD;

			if (ans < 0) ans += MOD;
		}
		printf("Case #%lld: %lld\n", kase, ans);
	}
	return 0;
}