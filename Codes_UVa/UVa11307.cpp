#include <cstdio>
#include <cstring>
#include <vector>
#define INF 0x3f3f3f3f
using namespace std;
int n, dp[10010][10];
char str[30000];
vector<int> ed[10010];

void handle() {
    int i = 0;
    int len = strlen(str), num = -1;
    while (str[i] < '0' || str[i] > '9') i++;
    for (;str[i] != ':'; i++) {
        if (num == -1)
            num = str[i] - '0';
        else
            num = num * 10 + str[i] - '0';
    }
    int u = num;
    num = -1;
    for (;i <= len; i++) {
        if (num != -1 && (str[i] < '0' || str[i] > '9')) {
            ed[u].push_back(num);
            ed[num].push_back(u);
            num = -1;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            if (num == -1)
                num = str[i] - '0';
            else
                num = num * 10 + str[i] - '0';
        }
    }
}

void dfs(int u, int fa) {
    int i;
    for (i = 1; i <= 6; i++)
        dp[u][i] = i;
    for (i = 0; i < ed[u].size(); i++) {
        int v = ed[u][i];
        if (v == fa) continue;
        dfs(v, u);
        for (int col_u = 1; col_u <= 6; col_u++) {
            int tmp = INF;
            for (int col_v = 1; col_v <= 6; col_v++) {
                if (col_u == col_v) continue;
                tmp = min(tmp, dp[v][col_v]);
            }
            dp[u][col_u] += tmp;
        }
    }
}

int main() {
	while (~scanf("%d\n", &n) && n) {
		for (int i=0; i<=n; i++)
			ed[i].clear();
		while (gets(str) && str[0] != '\0') {
			handle();
		}
		dfs(0, -1);
		int ans = INF;
		for (int i = 1; i <= 6; i++)
			ans = min(ans, dp[0][i]);
		printf("%d\n", ans);
	}
	return 0;
}

/*
2
0:
1: 0

8
0: 1 2 3
1: 4 5
2:
3: 6 7
4:
5:
6:
7:

0
*/