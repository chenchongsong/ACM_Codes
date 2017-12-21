#include <cstdio>
#include <algorithm>
#include <iostream>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
ll t, m, n;
ll num[3], pos[3], cost[3];
ll tot= 0;
ll a[100];

ll cal(ll l, ll r, ll num, ll pos, ll cost) {
	if (l > r) return 0;
	while (a[l]==0 && l <= r) l++;
	while (a[r]==0 && r >= l) r--;
	if (l > r) return 0;
	if (l == r && a[l] == 0) return 0;
	ll cmove = 0, ceat = 0;
	for (int i=l; i<=r; i++) {
		ceat += (a[i]/num) + ((a[i]%num) > 0);
	}
	if (pos <= l) cmove = (r-pos) * cost;
	else if (pos >= r) cmove = (pos - l) * cost;
	else cmove = min(2*(r-pos)+pos-l, 2*(pos-l)+r-pos) * cost;
	return cmove + ceat;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> m >> n;
		if (m==1) {
			cin >> num[1] >> pos[1] >> cost[1];
			for (int i=0; i<n; i++)
				cin >> a[i];
			tot = 0;
			tot = cal(0, n-1, num[1], pos[1], cost[1]);
		}
		else {
			for (int i=1; i<=2; i++)
				cin >> num[i] >> pos[i] >> cost[i];
			for (int i=0; i<n; i++)
				cin >> a[i];
			tot = INF;
			for (int i=-1; i<n; i++) {
				ll tmp1 = cal(0, i, num[1], pos[1], cost[1]);
				ll tmp2 = cal(i+1, n-1, num[2], pos[2], cost[2]);
				tot = min(tot, tmp1+tmp2);


				tmp1 = cal(0, i, num[2], pos[2], cost[2]);
				tmp2 = cal(i+1, n-1, num[1], pos[1], cost[1]);
				tot = min(tot, tmp1+tmp2);
			}
		}
		cout << tot << endl;
	}
	return 0;
}

/*

1
2 4
2 1 1
5 2 2
0 2 0 8

1
2 6
2 2 1
5 3 2
0 0 10 0 0 0

*/