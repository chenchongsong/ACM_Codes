// LA 7714
#include <cstdio>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;

ll fast_pow(ll Base, ll Pow) {
	ll ret = 1;
	while (Pow != 0) {
		if (Pow % 2 == 1)
			ret = (ret*Base) % mod;
		Base = (Base*Base) % mod;
		Pow /= 2;
	}
	return ret;
}

int main() {
	int TC, C, tmp;
	ll N, M;
	scanf("%d", &TC);
	for (int k = 1; k <=TC; k++) {
		scanf("%lld%lld", &N, &M);
		for (int i=1; i<=N; i++) {
			scanf("%d", &C);
			for (int j = 1; j<= C; j++) {
				scanf("%d", &tmp);
			}
		}
		if (N > M) {
			printf("Case #%d: 0\n", k);
			continue;
		}

		// ans = c(N-1 from M-1) = P(N-1 from M-1) / (N-1)!

		ll ans = 1;

		for (ll i = M-N+1; i <= M-1; i++) {
			ans *= i;
			ans %= mod;
		}

		

		// now i = P(N-1 from M-1)

		for (ll i=1; i <= N-1; i++) {
			ans = ans * fast_pow(i, mod-2);
			ans %= mod;
		}  // i.e. ans /= i;

		printf("Case #%d: %lld\n", k, ans);
	}
	return 0;
}

/*

4
6 12
3 2 3 4
0
0
2 5 6
0
0
1 100
0
2 100
1 2
0
3 5
1 2
1 3
0


*/