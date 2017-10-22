// Hong Kong Regional Online Preliminary 2016
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 50010;
const int maxm = 50010;
const int maxk = 1000010;
inline void read(int &x) {
	x = 0; static char c;
	for (; !(c >= '0' && c <= '9'); c = getchar());
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = getchar());
}

int belong[maxn]; // 每个点的分块预处理
int ans[maxm];
struct Cmd {
	int l, r, id;
	friend bool operator < (const Cmd &a, const Cmd &b) {
		if (belong[a.l] == belong[b.l]) return a.r < b.r; // 右端点大小作为第二关键字
		else return belong[a.l] < belong[b.l]; // 左端点所在分块作为第一关键字
	}
} cmd[maxm];
int N, M, K;
int lang1[maxn], lang2[maxn]; // language
int cnt1[maxk], cnt2[maxk]; // cnt1[i] = j 表示当前区间内第一行有j个人会说第i种语言

inline void upd(int &now, int pos, int v) { // 更新now
	int l1 = lang1[pos];
	int l2 = lang2[pos];
	if (l1 == l2) {
		now += v;
		cnt1[l1] += v;
		cnt2[l2] += v;
		return;
	}
	now -= min(cnt1[l1], cnt2[l1]);
	now -= min(cnt1[l2], cnt2[l2]);
	cnt1[l1] += v;
	cnt2[l2] += v;
	now += min(cnt1[l1], cnt2[l1]);
	now += min(cnt1[l2], cnt2[l2]);
}
inline void solve(void) {
	int L = 1, R = 0; // [L,R]为当前维护好的区间
	int now = 0;    // now为当前区间的答案
	for (int i = 1; i <= M; i++) { // 莫队的主要部分		
		for (; L < cmd[i].l; L++) upd(now, L, -1);
		for (; R > cmd[i].r; R--) upd(now, R, -1);
		for (; L > cmd[i].l; L--) upd(now, L - 1, 1);
		for (; R < cmd[i].r; R++) upd(now, R + 1, 1);
		if (cmd[i].l == cmd[i].r) {
			ans[cmd[i].id] = (lang1[cmd[i].l]==lang2[cmd[i].l]?1:0);
			continue;
		}
		ans[cmd[i].id] = now;
	}
}

int main() {
	read(N), read(M), read(K);
	int blocksize = sqrt(N);
	for (int i = 1; i <= N; i++) {
		read(lang1[i]);
		belong[i] = (i - 1) / blocksize + 1; // 每个点的分块预处理
	}
	for (int i = 1; i <= N; i++) read(lang2[i]);

	for (int i = 1; i <= M; i++) {
		read(cmd[i].l), read(cmd[i].r);
		cmd[i].l++; cmd[i].r++;
		cmd[i].id = i;
	}
	sort(cmd + 1, cmd + M + 1); // 对区间重新排序

	solve();
	for (int i = 1; i <= M; i++)
		printf("%d\n", ans[i]);
	return 0;
}