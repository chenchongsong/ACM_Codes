#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#define maxrc 1001
using namespace std;

int r, c;
int q;
int sx, sy, ex, ey;
string s[maxrc];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int fa[maxrc * maxrc];

int tonode(int i, int j) {
	return i * c + j;
}
bool issafe(int i, int j) {
	if (i < 0 || i >= r) return false;
	if (j < 0 || j >= c) return false;
	if (s[i][j] == '#') return false;
	return true;
}
void Clear() {
	for (int i=0; i<maxrc*maxrc; i++)
		fa[i] = i;
}

int getf(int x){return fa[x]==x?x:fa[x]=getf(fa[x]);}
void  Union(int x, int y) {
	int fx = getf(x);
	int fy = getf(y);
	if (fx != fy) fa[fx] = fy;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		Clear();
		cin >> r >> c;
		for (int i=0; i<r; i++) {
			cin >> s[i];

		}
		for (int i=0; i<r; i++) {
			for (int j=0; j<c; j++) {
				if (s[i][j] == '#') continue;
				for (int d=0; d<4; d++) {
					int tx = i + dx[d];
					int ty = j + dy[d];
					if (issafe(tx,ty) == false) continue;
					Union(tonode(i,j), tonode(tx,ty));
					// printf("%d -- %d\n", tonode(i,j), tonode(tx,ty));
				}
			}
		}
		cin >> q;
		while (q--) {
			cin >> sx >> sy >> ex >> ey;
			sx--; sy--; ex--; ey--;
			int fs = getf(tonode(sx, sy));
			int fe = getf(tonode(ex, ey));
			if (fs == fe) puts("IN");
			else puts("OUT");
		}
	}
	return 0;
}

/*

1
4 8
........
..###.#.
.#..#.#.
#...#...
5
1 1 1 8
4 2 3 4
2 2 3 3
1 1 4 4
3 1 4 6

4 3
.#.
.##
##.
.#.
4
1 1 4 3
4 1 1 3
1 3 4 1
3 3 2 1

*/



