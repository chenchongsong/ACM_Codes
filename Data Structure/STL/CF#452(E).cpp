#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#define maxn 200005
using namespace std;
int a[maxn], b[maxn]; // a -- compress --> b
int init_cnt[maxn];
int n, tot;

struct State {
	int key, cnt, l, r;
	bool operator < (const State& rhs) const {
		return cnt < rhs.cnt || (cnt==rhs.cnt && l > rhs.l);
	}
};

priority_queue<State> q;
set<int> s; // remaining available positions
int trans[maxn]; // keep track of current (l <--> r) pairs;
int cnt[maxn];

int main() {
	cin >> n;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
	}
	b[tot = 1] = a[1];
	init_cnt[1] = 1;
	for (int i=2; i<=n; i++) {
		if (a[i] == a[i-1]) {
			init_cnt[tot]++;
		}
		else {
			b[++tot] = a[i];
			init_cnt[tot] = 1;
		}
	}
	n = tot;
	for (int i=1; i<=tot; i++) {
		q.push((State){b[i], init_cnt[i], i, i});
		s.insert(i);
		trans[i] = i;
		cnt[i] = init_cnt[i];
	}

	int ans = 0;

	while (!q.empty()) {
		State u = q.top();
		q.pop();
		
		if (s.find(u.l) == s.end() || s.find(u.r) == s.end())
			continue;
		ans++;
		
		auto r1 = s.find(u.l); auto l2 = s.find(u.r);

		if (r1 == s.begin() || ++l2 == s.end()) { // no more left or no more right
			s.erase(u.l);
			s.erase(u.r);
			continue;
		}
		--l2;

		--r1; ++l2;

		s.erase(u.l); s.erase(u.r);
		auto l1 = s.find(trans[*r1]);
		auto r2 = s.find(trans[*l2]);

		int pos1 = *l1, pos2 = *r2;

		if (b[pos1] != b[pos2]) continue;

		if (l1 != r1) s.erase(r1);
		if (l2 != r2) s.erase(l2);

		trans[pos1] = pos2;
		trans[pos2] = pos1;
		cnt[pos1] = cnt[pos2] = cnt[pos1] + cnt[pos2];
		q.push((State){b[pos1], cnt[pos1], pos1, pos2});
	}
	cout << ans << endl;
	return 0;
}