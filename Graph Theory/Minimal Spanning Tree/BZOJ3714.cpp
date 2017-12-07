#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define maxn 4010
typedef long long ll;
using namespace std;
int n;
int c[maxn][maxn];
int fa[maxn];

int getf(int x){return fa[x]==x?x:fa[x]=getf(fa[x]);}

struct Edge {
	int u, v, w;
	bool operator < (const Edge& rhs) const {
		return w < rhs.w;
	}
};
vector<Edge> edges;

int main() {
	scanf("%d", &n);
	for (int i=1; i<=n+1; i++)
		fa[i] = i;

	for (int i=1; i<=n; i++) {
		for (int j=i; j<=n; j++) {
			scanf("%d", &c[i][j]);
			edges.push_back((Edge){i, j+1, c[i][j]});
		}
	}
	sort(edges.begin(), edges.end());

	ll ans = 0;
	for (int i = 0; i<edges.size(); i++) {
		Edge& e = edges[i];
		int fu = getf(e.u), fv = getf(e.v);
		if (fu == fv) continue;
		fa[fu] =fv;
		ans += (ll)e.w;
	}
	cout << ans << endl;
	return 0;
}

/*

5
1 2 3 4 5
4 3 2 1
3 4 5
2 1
5

*/
