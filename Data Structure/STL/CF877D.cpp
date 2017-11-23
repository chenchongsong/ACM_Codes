#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <set>
#define maxn 1010
using namespace std;

struct node{
    int x, y;
    bool operator < (const node& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};
char s[maxn][maxn];
int dis[maxn][maxn];
int sumrow[maxn][maxn], sumcol[maxn][maxn];
bool vis[maxn][maxn];
set<node> row[maxn], col[maxn]; // maintain unvisited nodes
queue<node> Q; // for BFS

int n, m, k;
int sx, sy, ex, ey;

bool check(int x1, int y1, int x2, int y2) {
    // check whether can move from (x1 y1)->(x2 y2) in 1s
    if (x1 != x2 && y1 != y2) return false;
    if (abs(x1-x2)+abs(y1-y2) > k) return false;
    if (x1 == x2 && sumrow[x1][max(y1,y2)] - sumrow[x1][min(y1,y2)-1] > 0)
        return false; // blocked by cans
    if (y1 == y2 && sumcol[max(x1,x2)][y1] - sumcol[min(x1,x2)-1][y1] > 0)
        return false; // blocked by cans
    return true;
}

bool handle(int ux, int uy, set<node>& tmpset, set<node>::iterator& it) {
    int vx = it->x, vy = it->y;
    if (!check(ux,uy,vx,vy)) return false;
    if (!vis[vx][vy]) {
        vis[vx][vy] = 1;
        dis[vx][vy] = dis[ux][uy] + 1;
        Q.push(*it);
    }
    tmpset.erase(it);
    return true;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i=1; i<=n; i++) {
        scanf("%s", s[i]+1);
        for (int j=1; j<=m; j++) {
            if (s[i][j] == '.') {
                row[i].insert((node){i,j});
                col[j].insert((node){i,j});
            }
            else {
                sumrow[i][j] = 1;
                sumcol[i][j] = 1;
            }
        }
    }
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            sumrow[i][j] += sumrow[i][j-1];
            sumcol[i][j] += sumcol[i-1][j];
        }
    }
    memset(dis, -1, sizeof(dis));

    Q.push((node){sx, sy});
    dis[sx][sy] = 0;
    vis[sx][sy] = 1;

    while (!Q.empty()) {
        node u = Q.front();
        if (u.x == ex && u.y == ey) break;
        Q.pop();

        // rightwards
        auto it = (row[u.x].lower_bound((node){u.x,u.y}));
        while (it != row[u.x].end() && handle(u.x, u.y, row[u.x], it)) {
            it = (row[u.x].lower_bound((node){u.x,u.y}));
        }

        // leftwards
        it = row[u.x].lower_bound((node){u.x,u.y});
        while (it != row[u.x].begin() && handle(u.x, u.y, row[u.x], --it)) {
            it = (row[u.x].lower_bound((node){u.x,u.y}));
        }

        // downwards
        it = (col[u.y].lower_bound((node){u.x,u.y}));
        while (it != col[u.y].end() && handle(u.x, u.y, col[u.y], it)) {
            it = (col[u.y].lower_bound((node){u.x,u.y}));
        }

        // upwards
        it = col[u.y].lower_bound((node){u.x,u.y});
        while (it != col[u.y].begin() && handle(u.x, u.y, col[u.y], --it)) {
            it = (col[u.y].lower_bound((node){u.x,u.y}));
        }
    }

    printf("%d\n", dis[ex][ey]);
    return 0;
}