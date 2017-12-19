#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

char s[260];
int map[260][260];
int vis[260][260];
int w[260][260];
// int two[30];
int dis[260][260];

int n, m, p, q, maxl;
int Node(int x, int y) {return (x-1) * m + (y-1) + 1;}


int cur = 0, curx, cury;
bool check(int x, int y) {
	if (map[x][y] == 0)
		return 0;
	if (x == 0 || x > n || y == 0 || y>m )
		return 0;
	if (vis[x][y])
		return 0;
	
	vis[x][y] = 1;

	return 1;
}

int bfs(int x, int y) {
	int cnt = 0;
	queue<int> que;
	que.push(Node(x, y));
	vis[x][y] = 1;
	dis[x][y] = 0;
	
	//cnt += (map[x][y]-10) * q;
	w[x][y] = 1;

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		curx = (cur -1) / m + 1;
		cury = (cur -1) % m + 1;

		cnt += (map[curx][cury]-10) * q / w[curx][cury];
		// printf("x %d. y%d. cnt %d  %d. %d \n", curx, cury, cnt, map[curx][cury]-10, w[curx][cury]);

		if (cnt > p) break;
		if (dis[curx][cury] > maxl) break;

		if (check(curx-1, cury)) {
			que.push(Node(curx-1, cury));
			w[curx-1][cury] = w[curx][cury] * 2;
			dis[curx-1][cury] = dis[curx][cury] + 1;
		}
		if (check(curx+1, cury)) {
			que.push(Node(curx+1, cury));
			w[curx+1][cury] = w[curx][cury] * 2;
			dis[curx+1][cury] = dis[curx][cury] + 1;
		}
		if (check(curx, cury-1)) {
			que.push(Node(curx, cury-1));
			w[curx][cury-1] = w[curx][cury] * 2;
			dis[curx][cury-1] = dis[curx][cury] + 1;
		}
		if (check(curx, cury+1)) {
			que.push(Node(curx, cury+1));
			w[curx][cury+1] = w[curx][cury] * 2;
			dis[curx][cury+1] = dis[curx][cury] + 1;
		}

	}

	return cnt;
	
} 


int main() {

	scanf("%d%d%d%d", &n, &m, &q, &p);
	for (int i=1; i<=n; i++) {
		scanf("%s", s+1);
		for (int j=1; j<=m; j++) {
			if (s[j] == '.') {
				map[i][j] = 10;
				continue;
			}
			if (s[j] == '*') {
				map[i][j] = 0;
				continue;
			}
			map[i][j] = s[j]-'A' + 11;
		}
	}

	/*for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			printf("%d ", map[i][j]);
		}
		puts("");
	}*/

	maxl = 26; // 25

	int tmp = 0, ans = 0;

	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			memset(vis, 0, sizeof(vis));
			if (map[i][j] == 0)
				continue;
			
			tmp = bfs(i,j);
			if (tmp > p)
				ans++;
			// printf("%d -- %d: %d\n",i,j,tmp);
		}
	}
	// tmp = bfs(3, 3);
	// printf("tmp == %d\n", tmp);
	printf("%d\n", ans);
	return 0;
}
