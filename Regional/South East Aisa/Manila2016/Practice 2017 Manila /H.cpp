#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <cstring>
#include <set>
#define maxn 200005
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
ll t, n, q, l;
ll len, a[maxn], sum[maxn], dp[maxn];
multiset<ll> s;
deque<ll> que, m;
void Init() {
	while (!que.empty())
		que.pop_back();
	while (!m.empty())
		m.pop_back();
}
void In(int x) {
	que.push_back(x);
	while (!m.empty() && m.back() > x)
		m.pop_back();
	m.push_back(x);
}
void Out() {
	if (m.front() == que.front())
		m.pop_front();
	que.pop_front();
}
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> q;

		sum[0] = 0;
		for (int i=1; i<=n; i++) {
			scanf("%lld", &a[i]);
			sum[i] = sum[i-1] + a[i];
		}

		while (q--) {
			cin >> l;
			memset(dp, 63, sizeof(dp));
			dp[0] = 0;
			// dp[l] = sum[l];

			// Init();
			s.clear();

			for (int i=0; i<l; i++)
				// In(dp[i]);
				s.insert(dp[i]);

			for (int i=l; i<=n; i++) {
				// for (auto it : s) {
				// 	printf("%lld--", it);
				// 	puts("");
				// }
				dp[i] = (*s.begin()) + sum[i] - sum[i-l];
				// In(dp[i]);
				// Out();
				s.insert(dp[i]);
				s.erase(dp[i-l]);
			}
			printf("%lld\n", dp[n]);
		}
	}
	return 0;
}

/*


1
5 5
7 5 3 6 3
5
4
2
6

*/


