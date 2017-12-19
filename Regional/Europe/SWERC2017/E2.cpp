#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#define maxn 2000005
using namespace std;
int b, m;
int dish[maxn];
int cost[maxn], val[maxn];

struct Edge {int to, w, val;};
vector <Edge> edges;
vector<int> G[maxn];
int indeg[maxn];
map<string, int> id;
stack<int> s;

int f[maxn];
vector<int> T;

int tot=0;
int getid(string s) {
	if (id.count(s))
		return id[s];
	id[s] = ++tot;
	// cout << endl << s << " == " << tot;
	return tot;
}

int main() {
	//cin.tie(0);
	//ios_base::sync_with_stdio(false);
	cin >> b;cin >> m;

	//string s1, s2;
	char buff1[31], buff2[31], tmp[31];
	int tmpc, tmpv;
	while (m--) {
		//cin >> s1 >> s2 >> tmp;
		scanf("%s%s%s", buff1, buff2, tmp);
		string s1(buff1);
		string s2(buff2);
		scanf("%d%d", &tmpc, &tmpv);
		int id1 = getid(s1), id2 = getid(s2);
		edges.push_back((Edge){id1, tmpc, tmpv});
		G[id2].push_back(int(edges.size())-1);
		indeg[id1]++;
	}
	// puts("OK");
	memset(cost, 63, sizeof(cost));
	for (int i=1; i<=tot; i++) {
		if (!indeg[i]) {
			s.push(i);
			// printf(" start i %d\n", i);
			cost[i] = val[i] = 0;
		}
	}

	while (!s.empty()) {
		int u = s.top(); s.pop();
		// printf("u == %d\n", u);
		// dish[cost[u]] = max(dish[cost[u]], val[u]);
		for (int i=0; i<G[u].size(); i++) {
			Edge& e = edges[G[u][i]];
			int v = e.to;
			// printf("from %d -- to %d\n", u, v);
			if (cost[v] > cost[u] + e.w) {
				cost[v] = cost[u] + e.w;
				val[v] = val[u] + e.val;
			}
			else if (cost[v] == cost[u] + e.w)
				val[v] = max(val[v], val[u] + e.val);

			indeg[v]--;
			if (!indeg[v])
				s.push(v);
		}
	}

	for (int i=1; i<=tot; i++) { // object 
		for (int v = b; v >=0; v--) { // volume
			if (v - cost[i] >= 0) {
				f[v] = max(f[v], f[v-cost[i]]+val[i]);
			}
		}
	}
	int Ans1 = 0, Ans2 = 0;
	for (int v=0; v<=b; v++) {
		if (f[v] > Ans1) {
			Ans1 = f[v];
			Ans2 = v;
		}
	}
	printf("%d\n%d\n", Ans1, Ans2);

	return 0;

	
}

/*



15
6
pizza_tomato pizza_base tomato 1 2
pizza_cheese pizza_base cheese 5 10
pizza_classic pizza_tomato cheese 5 5
pizza_classic pizza_cheese tomato 1 2
pizza_salami pizza_classic salami 7 6
pizza_spicy pizza_tomato chili 3 1

*/