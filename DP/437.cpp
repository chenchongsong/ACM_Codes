#include <cstdio>
#include <algorithm>
#define maxn 100
using namespace std;
struct block {
	int x, y, h;
	bool operator < (const block& b) const{
		return x<b.x || (x==b.x && y==b.y);
	}
} a[maxn];
int n, dp[maxn];

void Add(int pos, int x, int y, int h) {
	a[pos].x = x;
	a[pos].y = y;
	a[pos].h = h;
}

int main() {
	int kase = 0;
	while (scanf("%d", &n)!=EOF && n){
		//Clear();
		int x, y, h;
		for (int i=1; i<=n; i++) {
			scanf("%d%d%d", &x, &y, &h);
			Add(i*6-5, x, y, h);
			Add(i*6-4, y, x, h);
			Add(i*6-3, h, y, x);
			Add(i*6-2, y, h, x);
			Add(i*6-1, x, h, y);
			Add(i*6, h, x, y);
		}
		sort(a+1, a+6*n+1);
		int ans = 0;
		for (int i=1; i<=n*6; i++) {
			dp[i] = a[i].h;
			for (int j=1; j<i; j++) {
				if (a[j].x == a[i].x) continue;
				if (a[j].y >= a[i].y) continue;
				dp[i] = max(dp[i], dp[j]+a[i].h);
			}
			ans = max(ans, dp[i]);
		}
		printf("Case %d: maximum height = %d\n", ++kase, ans);
	}
	return 0;
}