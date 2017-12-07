#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
#define MAXN 100011
#define ms(x) memset(x, 0, sizeof(x))

struct Edge{
	int u,v;
	bool operator < (const Edge& lhs) const
	{return u < lhs.u || (u == lhs.u && v < lhs.v);}
};
vector<int>G[MAXN],bcc[MAXN];
vector<Edge>bridge;
int low[MAXN],pre[MAXN],dfs_clock=0,
iscut[MAXN],bccno[MAXN],bcc_cnt=0;
//bccno是每个点在哪块 bcc是第i块有哪些点
//点编号0~n-1
stack<Edge>s;//保存在当前bcc中的边,割顶的bccno无意义,因为存在于多个bcc中
void dfs(int u, int fa) {
	low[u] = pre[u] = ++dfs_clock;
	int child=0;
	for (auto v : G[u]) {
		Edge e = {u,v};
		if (!pre[v]) {
		//not visited yet
			s.push(e); //store cut edge
			dfs(v,u); //注意v,u的顺序
			child++;
			low[u] = min(low[u], low[v]);
			if (low[v] >= pre[u]) {
			//if cut, bcc find
				if (low[v] > pre[u])
					bridge.push_back((Edge){min(u,v),max(u,v)});
				iscut[u] = 1;
				bcc[++bcc_cnt].clear();
				while(1) {
					Edge x = s.top(); s.pop();
					if(bccno[x.u] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if(bccno[x.v] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x.v);
						bccno[x.v] = bcc_cnt;
					}
					if (x.u==u && x.v==v) break;
				}
			}
		}
		else if( pre[u] > pre[v] && v!=fa ) {
		//early than father
			s.push(e);
			low[u] = min(low[u],pre[v]);
		}
	}
	if(child <= 1 && fa < 0)
		iscut[u] = 0;
}

void Clear() {
	while (!s.empty()) s.pop();
	for (int i=0; i<MAXN; i++) {
		G[i].clear();
		bcc[i].clear();
	}
	bridge.clear();
	ms(low);
	ms(pre);
	ms(iscut);
	ms(bccno);
	dfs_clock = bcc_cnt = 0;
}
int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		Clear();
		int a, b, num;
		for (int i=0; i<n; i++) {
			scanf("%d (%d)", &a, &num);
			while (num--) {
				cin >> b;
				if (b <= a) continue;
				G[a].push_back(b);
				G[b].push_back(a);
			}

		}
		for(int i = 0; i < n; i++)
			if(!pre[i])
				dfs(i, -1);
		cout << bridge.size() << " critical links" << endl;
		sort(bridge.begin(), bridge.end());
		for (auto e: bridge)
			printf("%d - %d\n",e.u, e.v);
		puts("");

	}
	return 0;
}

/*

8
0 (1) 1
1 (3) 2 0 3
2 (2) 1 3
3 (3) 1 2 4
4 (1) 3
7 (1) 6
6 (1) 7
5 (0)
0

*/
