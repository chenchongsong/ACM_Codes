#include <cstdio>
#include <vector>
#define maxn 500010
typedef long long ll;
using namespace std;
ll n, root, r[maxn], t[maxn], fa[maxn], ans[maxn];
vector<ll> ed[maxn];

ll treeNum[maxn];

ll lowbit(ll x) {return x&(-x);}

ll getSum(ll x) {
    ll sum = 0;
    while(x) {
    	sum += treeNum[x];
    	x -= lowbit(x);
	}
    return sum; // V[1]~V[x]
}

void add(ll x , ll val) {
	//单点修改(V[x]+=val)
    while(x < maxn/2) {
    	treeNum[x] += val;
    	x += lowbit(x);
    }
}

void dfs(ll now) {
	ll prev_sum = getSum(r[now]-1);

	for (ll i=0; i<ed[now].size(); i++)
		dfs(ed[now][i]);

	ans[now] = getSum(r[now]-1) - prev_sum;
	add(r[now], t[now]);
	
}

int main() {
	scanf("%lld", &n);
	for (ll i=1; i<=n; i++) {
		scanf("%lld%lld%lld", &fa[i], &r[i], &t[i]);
		if (fa[i] == -1)
			root = i;
		else
			ed[fa[i]].push_back(i);
	}
	dfs(root);
	for (ll i=1; i<=n; i++) {
		printf("%lld\n", ans[i]);
	}

}