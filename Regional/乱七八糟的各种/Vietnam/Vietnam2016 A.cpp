#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define maxn 1000011
typedef long long ll;
using namespace std;

ll a[maxn], sum[maxn];
ll n, m;
vector<int> pos;
vector<int> npos;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &n, &m);

		pos.clear();
		pos.push_back(0);
		npos.clear();
		npos.push_back(0);

		for (int i=1; i<=n; i++) {
			scanf("%lld", &a[i]);
			if (a[i] < m) a[i] = 0, npos.push_back(i);
			
			sum[i] = sum[i-1] + a[i];
			if (a[i] == m) pos.push_back(i);
		}
		pos.push_back(n+1);
		npos.push_back(n+1);
		
		ll ans = 0;
		for (int i=1; i<pos.size()-1; i++) {
			int upidx = upper_bound(npos.begin(),npos.end(),pos[i])-npos.begin();
			int lowidx = upidx-1;

			int uppos = min(npos[upidx], pos[i+1]);
			int lowpos = max(npos[lowidx], pos[i-1]);

			ans = max(ans, sum[uppos-1]-sum[lowpos]);
		}
		printf("%lld\n", ans);	
	}
	return 0;
}