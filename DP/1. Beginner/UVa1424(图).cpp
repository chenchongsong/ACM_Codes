#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define maxn 110
#define maxlen 210
using namespace std;
int map[maxn][maxn];
int dp[maxlen][maxn];
//dp[i][node] 第i位 走到节点node
void Clear() {
	memset(map, 0,sizeof(map));
	memset(dp, 63, sizeof(dp));
}

int main() {
	int T; cin>>T;
	while (T--) {
		Clear();
		int n, m, len, node;
		scanf("%d%d", &n, &m);
		for (int i=1; i<=m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			map[u][v] = 1;
			map[v][u] = 1;
		}
		for (int i=1; i<=n; i++) {
			map[i][0] = 1;
			map[0][i] = 1;
			map[i][i] = 1;
		}
		scanf("%d", &len);
		for (int i=1; i<=n; i++) dp[0][i] = 0;
		for (int i=1; i<=len; i++) {
			cin >> node;
			for (int cur_node = 1; cur_node <= n; cur_node++) {
				for (int pre_node = 1; pre_node <= n; pre_node++) {
					//cout << "pre " <<pre_node<<" cur "<<cur_node<< "--- "<<map[pre_node][cur_node]<<endl; 
					if (!map[pre_node][cur_node]) continue;
						dp[i][cur_node] = min(dp[i][cur_node], dp[i-1][pre_node]);
				}
				if (cur_node != node) dp[i][cur_node]++;
				//printf("%d--%d : %d\n",i,cur_node, dp[i][cur_node]);
			}
		}
		int ans = 10000;
		for (int cur_node=1; cur_node<=n; cur_node++) {
			ans = min(ans, dp[len][cur_node]);
		}
		cout << ans << endl;
	}
	return 0;	
}