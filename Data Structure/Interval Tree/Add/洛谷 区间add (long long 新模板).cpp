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

struct IntervalTree{
    ll addv[maxnode*4],setv[maxnode*4];
    ll sumv[maxnode*4],minv[maxnode*4],maxv[maxnode*4];

    void maintain(ll o, ll L, ll R){
        ll lc = o*2, rc = o*2+1;
        if(L < R){
            sumv[o] = sumv[lc] + sumv[rc];
            maxv[o] = max(maxv[lc], maxv[rc]);
            minv[o] = min(minv[lc], minv[rc]);
        }
        if(setv[o] >= 0){
            minv[o] = maxv[o] = setv[o];
            sumv[o] = setv[o] * (R-L+1);
        }
        if(addv[o]){
            minv[o] += addv[o];
            maxv[o] += addv[o];
            sumv[o] += addv[o] * (R-L+1);
        }
    }
    void pushdown(ll o){
        ll lc = o*2, rc = o*2+1;
        if(setv[o] >= 0){
            setv[lc] = setv[rc] = setv[o];
            addv[lc] = addv[rc] = 0;
            setv[o] = -1;
        }
        if(addv[o]){
            addv[lc] += addv[o]; /// wrong answer
            addv[rc] += addv[o]; /// wrong answer
            addv[o] = 0;
        }
    }
    void update(ll o, ll L, ll R){
        ll lc = o*2, rc = o*2+1;
        if(qL <= L && qR >= R){
            if(op == 2) { // set
                setv[o] = v;
                addv[o] = 0;
            } // op == 1 : Add
            else{
                addv[o] += v;
            }
        }
        else{
            pushdown(o);
            ll M = L + (R-L)/2;
            if(qL <= M) update(lc, L, M);
            else maintain(lc, L, M);
            if(qR > M) update(rc, M+1, R);
            else maintain(rc, M+1, R);
        }
        maintain(o, L, R); /// wrong answer;
    }
    void query(ll o, ll L, ll R, ll add){
        if(setv[o] >= 0){
            ll v = setv[o] + addv[o] + add;
            _sum += v * (min(R, qR)-max(L, qL)+1); /// wrong answer
            _max = max(_max, v);
            _min = min(_min, v);
        }
        else if(qL <= L && qR >= R){
            _sum += sumv[o] + add*(R-L+1); /// wrong answer
            _max = max(_max, maxv[o]+add); /// wrong answer
            _min = min(_min, minv[o]+add); /// wrong answer
        }
        else{
            ll lc = o*2, rc = o*2+1;
            ll M = L + (R-L)/2;
            if(qL <= M) query(lc, L, M, add+addv[o]);
            if(qR > M) query(rc, M+1, R, add+addv[o]);
        }
    } 
};
IntervalTree tree;

int main() {
	ll n, m;
	while(scanf("%lld%lld", &n, &m) == 2) {
		memset(&tree, 0, sizeof(tree));
		for (ll i=1; i<=n; i++) {
			cin >> v;
			qL = qR = i;
			tree.update(1, 1, n);
		}
		while(m--) {
			scanf("%lld%lld%lld", &op, &qL, &qR);
			if(op == 1) {
				scanf("%lld", &v);
				tree.update(1, 1, n);
			} else {
				// set op to 1;	
				_sum = 0; _min = INF; _max = -INF;
				tree.query(1, 1, n, 0);
				printf("%lld\n", _sum);
			}	
		}	
	}	
	return 0;	
}