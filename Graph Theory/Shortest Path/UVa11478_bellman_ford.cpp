#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#define maxn 5000
#define maxm 27000
using namespace std;

struct Edge{
	int u, v, w, w0;
};
vector<Edge> edges;
int dis[maxn];
int n, m;
int S = 0;

bool check(int x) {
	for (int i=n; i<edges.size(); i++)
		edges[i].w = edges[i].w0 - x;

	memset(dis, 63, sizeof(dis));
	dis[S] = 0;
	for (int i=1; i<=n-1; i++)
		for (int j=0; j<edges.size(); j++){
			Edge e = edges[j];
			dis[e.v] = min(dis[e.v], dis[e.u]+e.w);
		}

	for (int i=1; i<edges.size(); i++) {
		Edge e = edges[i];
		if (dis[e.v] > dis[e.u] + e.w)
			return false;
	}
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m)==2) {
		edges.clear();
		for (int i=1; i<=n; i++)
			edges.push_back((Edge){0,i,0,0});
		for (int i=1; i<=m; i++) {
			int a, b, c;
			scanf("%d%d%d",&a,&b,&c);
			edges.push_back((Edge){a,b,c,c});
		}

		if (!check(1)) {
			puts("No Solution");
			continue;
		}
		
		int l = -1, r = 100010, mid = 0;
		while (l + 1 < r) {
			mid = (l+r) >> 1;
			if (check(mid)) l = mid;
			else r = mid;
		}
		if (l > 100000) puts("Infinite");
		else printf("%d\n", l);
	}
	return 0;
}