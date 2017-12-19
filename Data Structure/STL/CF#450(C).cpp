#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
#define maxn 100005
#define INF 0x3f3f3f3f
using namespace std;
multiset<int> s;
int a[maxn];
int pos[maxn]; // val to pos
int n;
int w[maxn];
int main() {
	cin >> n;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
		pos[a[i]] = i;
	}

	s.clear();
	for (int i=1; i<=n; i++) {
		auto it = s.lower_bound(a[i]);
		if (it == s.end()) // a[i] larger than any previous element
			w[i] = -1;
		s.insert(a[i]);
	}

	s.clear();
	for (int i=1; i<=n; i++) {
		auto it = s.upper_bound(a[i]);
		if (it != s.end()) {
			auto nxt = it; nxt++;
			if (nxt == s.end())
				w[pos[*it]]++;
			// if *it deleted, a[i] would become a new record
		}
		s.insert(a[i]);
	}

	int ans = 0, maxx = -INF;
	for (int i=1; i<=n; i++) { // pos
		if (w[i] > maxx) {
			maxx = w[i];
			ans = a[i];
		}
		else if (w[i] == maxx) {
			ans = min(ans, a[i]);
		}
	}
	cout << ans << endl;
	return 0;

}