// https://zhuanlan.zhihu.com/p/25017840
// Codes

// http://blog.csdn.net/thy_asdf/article/details/47373113
// 首先对于一个[l，r]的询问，设col[i]表示第i种颜色在这一区间内的个数，那么随机抽到相同一对的概率就是
// ∑C(col[i],2)/C(r-l+1,2)
// 然后有：∑(col[i]^2-col[i])/((r-l+1)*(r-l))
// 然后我们发现得到了[l,r]的答案后，我们可以O(1)地得到[l,r-1]和[l,r+1]和[l-1,r]和[l+1,r]的答案。

// http://hzwer.com/2782.html
// 1、i与i+1在同一块内，移动右端点的时间复杂度: r单调递增，所以r是O(n)的。由于有n^0.5块,所以这一部分时间复杂度是n^1.5。
// 2、i与i+1跨越一块，移动右端点的时间复杂度: r最多变化n，由于有n^0.5块，所以这一部分时间复杂度是n^1.5
// 3、移动左端点的时间复杂度: 
// i与i+1在同一块内时l变化不超过n^0.5，跨越一块也不会超过n^0.5，忽略*2。由于有m次询问（和n同级），所以时间复杂度是n^1.5

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int Maxn = 50005;
typedef long long ll;
inline ll sqr(const ll &x) {
	return x * x;
}
inline ll gcd(const ll &a, const ll &b) {
	if (!b) return a;
	else return gcd(b, a % b);
}
inline void read(int &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = getchar());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = getchar());
}
int belong[Maxn]; // 每个点的分块预处理
ll ans1[Maxn], ans2[Maxn];
struct Cmd {
	int l, r, id;
	friend bool operator < (const Cmd &a, const Cmd &b) {
		if (belong[a.l] == belong[b.l]) return a.r < b.r; // 右端点大小作为第二关键字
		else return belong[a.l] < belong[b.l]; // 左端点所在分块作为第一关键字
	}
} cmd[Maxn];
int n, m, c[Maxn], sum[Maxn];
// now =  ∑(col[i]^2) (for i in l~r)
// sum[i] = 区间内colour为i的袜子的个数
inline void upd(ll &now, int p, int v) { // 更新平方和
	now -= sqr(sum[c[p]]); 
	sum[c[p]] += v;
	now += sqr(sum[c[p]]);
}
inline void solve(void) {
	int L = 1, R = 0; // [L,R]为当前维护好的区间
	ll now = 0, g; // now为当前区间的答案
	for (int i = 1; i <= m; i++) { // 莫队的主要部分
		for (; L < cmd[i].l; L++) upd(now, L, -1); //    [L+1,R]
		for (; R > cmd[i].r; R--) upd(now, R, -1); //    [L,R-1]
		for (; L > cmd[i].l; L--) upd(now, L - 1, 1); // [L-1,R]
		for (; R < cmd[i].r; R++) upd(now, R + 1, 1); // [L,R+1]
		if (cmd[i].l == cmd[i].r) {
			ans1[cmd[i].id] = 0, ans2[cmd[i].id] = 1;
			continue;
		}
		ans1[cmd[i].id] = now - (cmd[i].r - cmd[i].l + 1); // ∑(col[i]^2) - ∑(col[i])
		ans2[cmd[i].id] = (ll)(cmd[i].r - cmd[i].l) * (cmd[i].r - cmd[i].l + 1);
		g = gcd(ans1[cmd[i].id], ans2[cmd[i].id]);
		ans1[cmd[i].id] /= g;
		ans2[cmd[i].id] /= g;
	}
}
int main() {
	read(n), read(m); int s = sqrt(n);
	for (int i = 1; i <= n; i++) {
		read(c[i]); belong[i] = (i - 1) / s + 1; // 每个点的分块预处理
	}
	for (int i = 1; i <= m; i++) {
		read(cmd[i].l), read(cmd[i].r);
		cmd[i].id = i;
	}
	sort(cmd + 1, cmd + m + 1); // 对区间重新排序
	solve();
	for (int i = 1; i <= m; i++) {
		printf("%lld/%lld\n", ans1[i], ans2[i]);
	}
	return 0;
}