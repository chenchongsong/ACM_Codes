#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define maxn 500010
using namespace std;

int N, M;
int tot = 0;
int cnt[maxn];
long long sum[maxn];
int fa[maxn], idx[maxn];

int getf(int x){return fa[x]==x ? x : fa[x]=getf(fa[x]);}
void UNION(int u, int v) {
	int fu = getf(u);
	int fv = getf(v);
	if (fu == fv) return;
	fa[fu] = fv;
	cnt[fv] += cnt[fu];
	sum[fv] += sum[fu];
}
void separate(int x) {
	int fx = getf(idx[x]);
	sum[fx] -= x;
	cnt[fx] -= 1;
	++tot;
	idx[x] = tot;
	fa[tot] = tot;
	cnt[tot] = 1;
	sum[tot] = x;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i=0; i<=N; i++) {
		fa[i] = i;
		idx[i] = i;
		cnt[i] = 1;
		sum[i] = i;
	}
	tot = N;
	for (int i=1; i<=M; i++) {
		int opt, p, q;
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &p, &q);
			UNION(idx[p], idx[q]);
		}
		else if (opt == 2) {
			scanf("%d%d", &p, &q);
			int fp = getf(idx[p]);
			int fq = getf(idx[q]);
			if (fp == fq) continue;
			separate(p);
			UNION(idx[p], idx[q]);
		}
		else { // 3
			scanf("%d", &p);
			int fp = getf(idx[p]);
			printf("%d %lld\n", cnt[fp], sum[fp]);
		}
		// for (int i=1; i<=N; i++) {
		// 	int fi = getf(idx[i]);
		// 	// printf("%d === %d.  idx %d. cnt%d sum%lld\n",i,fi,idx[i],cnt[fi],sum[fi]);
		
		// }
		// puts("");
	}
}

/*

5 3
1 1 2
2 3 4
1 3 5


3 4
2 4 1
3 4
3 3

*/