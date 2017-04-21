#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#define maxn 300
using namespace std;
int f[maxn];
struct edge {
	int u, v, w;
	bool operator < (const edge& b) const{
		return w > b.w;
	}
} ed[maxn * maxn];

map <string, int> ind;
int getf(int x){return f[x]==x?x:f[x]=getf(f[x]);}

int main() {
	int n, m, weight, kase = 0;
	string s1, s2;  // string 读到空格或回车会停止 不必担心行末回车问题

	while ((cin >> n >> m) && (n||m)) {
		int cnt = 0, tot = 0;

		for (int i=1; i<=m; i++) {
			cin >> s1 >> s2 >> weight;
			if (!ind[s1]) ind[s1] = ++cnt;
			if (!ind[s2]) ind[s2] = ++cnt;
			ed[++tot].u = ind[s1];
			ed[tot].v = ind[s2];
			ed[tot].w = weight;
		}
		cin >> s1 >> s2;
		int target1 = ind[s1], target2 = ind[s2];

		sort(ed+1, ed+m+1);
		for (int i=1; i<=n; i++) f[i] = i;
		
		for (int i=1; i<=m; i++) {
			
			int fu = getf(ed[i].u), fv = getf(ed[i].v);
			f[fu] = fv;

			fu = getf(target1), fv = getf(target2);
			if (fu==fv) {
				printf("Scenario #%d\n", ++kase);
				printf("%d tons\n\n", ed[i].w);
				break;
			}
		}
	}
	return 0;
}