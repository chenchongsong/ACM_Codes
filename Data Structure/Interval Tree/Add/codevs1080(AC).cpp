// n m 数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 L R v 表示设a[L]+=v, a[L+1]+v, ..., a[R]+=v
// 2 L R   查询a[L]~a[R]的sum, min和max	
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define ll long long
using namespace std;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll maxnode = 100005;

ll _min, _max, _sum, op, qL, qR, v; // 必须为全局变量

struct InervalTree {
	ll sumv[maxnode*4], minv[maxnode*4];
	ll maxv[maxnode*4], addv[maxnode*4];

	// 维护信息	
	void maintain(ll o, ll L, ll R) {	
		ll lc = o*2, rc = o*2+1;	
		sumv[o] = minv[o] = maxv[o] = 0;	
		if(R > L) {	
			sumv[o] = sumv[lc] + sumv[rc];	
			minv[o] = min(minv[lc], minv[rc]);	
			maxv[o] = max(maxv[lc], maxv[rc]);	
		}	
		if(addv[o]) {
			minv[o] += addv[o];
			maxv[o] += addv[o];
			sumv[o] += addv[o]*(R-L+1);
		}	
	}	
	
	void update(ll o, ll L, ll R) {
		ll lc = o*2, rc = o*2+1;
		if(qL <= L && qR >= R) { // 递归边界			
			addv[o] += v; // 累加边界的add值
		} else {
			ll M = L + (R-L)/2;
			if(qL <= M) update(lc, L, M);
			if(qR > M) update(rc, M+1, R);
		}
		maintain(o, L, R); // 递归结束前重新计算本结点的附加信息
	}

	void query(ll o, ll L, ll R, ll add) {	
		if(qL <= L && qR >= R) { // 递归边界：用边界区间的附加信息更新答案	
			_sum += sumv[o] + add * (R-L+1);
			_min = min(_min, minv[o] + add);
			_max = max(_max, maxv[o] + add);
		} else { // 递归统计，累加参数add
			ll M = L + (R-L)/2;
			if(qL <= M) query(o*2, L, M, add + addv[o]);
			if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
		}
	}
};
InervalTree tree;

int main() {
	ll n, m;
	scanf("%lld", &n);
	{
		memset(&tree, 0, sizeof(tree));
		for (ll i=1; i<=n; i++) {
			cin >> v;
			qL = qR = i;
			tree.update(1, 1, n);
		}
		scanf("%lld", &m);
		while(m--) {
			scanf("%lld%lld", &op, &qL);
			if(op == 1) {
				qR = qL;
				scanf("%lld", &v);
				tree.update(1, 1, n);
			} else {
				scanf("%lld", &qR);
				_sum = 0; _min = INF; _max = -INF;
				tree.query(1, 1, n, 0);
				printf("%lld\n", _sum);
			}	
		}	
	}	
	return 0;	
}
/*

6
4 
5 
6 
2 
1 
3
4
1 3 5
2 1 4
1 1 9
2 2 6

*/