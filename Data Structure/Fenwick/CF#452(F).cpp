#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define maxn 200005
using namespace std;

int n, m;
int bit[maxn * 4]; // a[1~n]
int lowbit(int x) {return x&(-x);}
void edit(int u,int v) { //a[u]的值增加v
	for(int j=u;j<=n;j+=lowbit(j))
		bit[j]+=v;
}
int query(int p) { //区间和 a[1]+...+a[n]
    int ans=0,i;
    for(i=p;i>0;i-=lowbit(i))
        ans+=bit[i];
    return ans;
}

char str[maxn];
bool deleted[maxn];
set<int> s[100];

int to_int(char ch) {
	if ('0' <= ch && ch <= '9') return ch-'0';
	if ('A' <=ch && ch <= 'Z') return ch-'A' + 10;
	return ch - 'a' + 50;
}

int init_pos(int newpos) {
	int L = 0, R = n; // binary search for initial_pos
	while (L + 1 < R) {
		int mid = (L + R) / 2;
		if (newpos + query(mid) > mid)
			L = mid;
		else
			R = mid;
		// printf("l %d mid %d r %d\n", L, mid, R);
	}
	return R;
}

int main() {
	cin >> n >> m;
	scanf("%s", str+1);
	for (int i=1; i<=n; i++) {
		s[to_int(str[i])].insert(i);
	}
	while (m--) {
		int l, r;
		char ch;
		cin >> l >> r >> ch;

		l = init_pos(l);
		r = init_pos(r);
		// printf("to init : %d -- %d\n", l, r);
		int idx = to_int(ch);

		auto itlow = s[idx].lower_bound(l);
		auto itup = s[idx].upper_bound(r);

		for (auto it = itlow; it != itup; it++) {
			// mark as deleted
			deleted[*it] = true;
			edit(*it, 1);
		}
		s[idx].erase(itlow, itup);
	}
	for (int i=1; i<=n; i++) {
		if (!deleted[i])
			printf("%c" , str[i]);
	}
	puts("");
	return 0;
}