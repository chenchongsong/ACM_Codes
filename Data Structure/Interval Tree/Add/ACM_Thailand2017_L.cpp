#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 100005;

int _min, _max, _sum, op, qL, qR, v; // 必须为全局变量

struct IntervalTree {
	// int sumv[maxn*4], maxv[maxn*4];
	int minv[maxn*4], addv[maxn*4];

	// 维护信息	
	void maintain(int o, int L, int R) {	
		int lc = o*2, rc = o*2+1;	
		// sumv[o] = minv[o] = maxv[o] = 0;
		minv[o] = 0;
		if(R > L) {	
			// sumv[o] = sumv[lc] + sumv[rc];	
			minv[o] = min(minv[lc], minv[rc]);	
			// maxv[o] = max(maxv[lc], maxv[rc]);	
		}	
		if(addv[o]) {
			minv[o] += addv[o];
			// maxv[o] += addv[o];
			// sumv[o] += addv[o]*(R-L+1);
		}	
	}	
	
	void update(int o, int L, int R) {
		int lc = o*2, rc = o*2+1;
		if(qL <= L && qR >= R) { // 递归边界			
			addv[o] += v; // 累加边界的add值
		} else {
			int M = L + (R-L)/2;
			if(qL <= M) update(lc, L, M);
			if(qR > M) update(rc, M+1, R);
		}
		maintain(o, L, R); // 递归结束前重新计算本结点的附加信息
	}

	void query(int o, int L, int R, int add) {	
		if(qL <= L && qR >= R) { // 递归边界：用边界区间的附加信息更新答案	
			// _sum += sumv[o] + add * (R-L+1);
			_min = min(_min, minv[o] + add);
			// _max = max(_max, maxv[o] + add);
		} else { // 递归统计，累加参数add
			int M = L + (R-L)/2;
			if(qL <= M) query(o*2, L, M, add + addv[o]);
			if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
		}
	}
};
IntervalTree tree;

int a[maxn], pre[maxn], nxt[maxn];
vector<pair<int, int> > del_interval[maxn], add_interval[maxn];
map<int, int> prev_pos; // value to pos

void Clear() {
	memset(&tree, 0, sizeof(tree));
	memset(a, 0, sizeof(a));
	memset(pre, 0, sizeof(pre));
	memset(nxt, 0, sizeof(nxt));
	for (int i=0; i<maxn; i++) {
		del_interval[i].clear();
		add_interval[i].clear();
	}
}

int main() {
	int t; cin >> t;
	while (t--) {
		Clear();
		int n; scanf("%d", &n);
		for (int i=1; i<=n; i++)
			scanf("%d", &a[i]);
		
		prev_pos.clear();
		for (int i=1; i<=n; i++) {
			if (prev_pos.count(a[i]) != 0)
				pre[i] = prev_pos[a[i]];
			else
				pre[i] = 0;
			prev_pos[a[i]] = i;
		}
		prev_pos.clear();
		for (int i=n; i>=1; i--) {
			if (prev_pos.count(a[i]) != 0)
				nxt[i] = prev_pos[a[i]];
			else
				nxt[i] = n+1;
			prev_pos[a[i]] = i;
		}

		for (int i=1; i<=n; i++) {
			int L = pre[i] + 1, R = nxt[i] - 1;
			printf("L %d i %d R %d\n",L,i,R);
			// 左端点在[L,i]内 且右端点在[i,R]内的区间 是可行的
			// 因为这些区间都有一个共同的unique number 即a[i]
			add_interval[L].push_back(make_pair(i,R));
			del_interval[i+1].push_back(make_pair(i,R));
			// 差分
		}

		bool flag = true;

		for (int i=1; i<=n; i++) {
			printf("i == %d\n",i);
			// add
			for (auto seg : add_interval[i]) {
				v = 1;
				qL = seg.first;
				qR = seg.second;
				printf("add one from %d to %d\n", qL, qR);
				tree.update(1, 1, n);
			}
			// delete
			for (auto seg : del_interval[i]) {
				v = -1;
				qL = seg.first;
				qR = seg.second;
				printf("minus one from %d to %d\n", qL, qR);
				tree.update(1, 1, n);
			}
			_min = INF;
			qL = i+1; qR = n;
			tree.query(1, 1, n, 0);
			if (_min == 0) {
				flag = false;
				break;
			}
		}

		if (flag) puts("YES");
		else puts("NO");
	}
	return 0;	
}