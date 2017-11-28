#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define maxn 2000005
#define maxm 2000005
typedef long long ll;
using namespace std;

struct Edge {
	int u, v, w;
	bool operator < (const Edge& lhs) const {
		return w < lhs.w;
	}
};
int fa[maxn];
vector<Edge> edges;

int getf(int x) {return fa[x]==x?x:fa[x]=getf(fa[x]);}

void Clear(int N) {
	for (int i=0; i<=N+1; i++)
		fa[i] = i;
	edges.clear();
}

int main() {
	int T, N, M, L, S;
	cin >> T;
	while (T--) {
		cin >> N >> M >> L >> S;
		Clear(N);
		for (int i=0; i<S; i++) {
			int tmps;
			cin >> tmps;
			edges.push_back((Edge){N+1,tmps,0});
		}
		for (int i=0; i<M; i++) {
			int tmpu, tmpv, tmpw;
			cin >> tmpu >> tmpv >> tmpw;
			edges.push_back((Edge){tmpu,tmpv,tmpw});
		}
		sort(edges.begin(), edges.end());
		
		ll ans = 0;
		for (int i=0; i<edges.size(); i++) {
			int fu = getf(edges[i].u);
			int fv = getf(edges[i].v);
			if (fu == fv) continue;
			fa[fu] = fv;
			ans += (ll)edges[i].w;
		}

		ans += (ll)(N-S) * (ll)L;
		cout << ans << endl;
	}
	return 0;
}