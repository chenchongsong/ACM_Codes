#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 1010
using namespace std;
struct node {
	double x,y;
	bool operator < (const node& b) const {
		//两个“const”一定要写
		return x<b.x;
	}
} a[maxn];
double f[maxn][maxn];
//f[i][j] 表示1~max(i,j)全部走过 一条落在i点 另一条路径落在j点
//由于两条路径等价 不妨令 i>=j
//f[i][j] --> f[i+1][j]
//f[i][j] --> f[i+1][i]
//(f[i][j]--> f[i][i])
double Dist(int i, int j) {
	return sqrt( (a[i].x-a[j].x)*(a[i].x-a[j].x)
				+(a[i].y-a[j].y)*(a[i].y-a[j].y) );
}
int main() {
	int n;
	while (scanf("%d", &n)!=EOF) {
		for (int i=1; i<=n; i++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		sort(a+1, a+n+1);
		
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				f[i][j] = 1e9;
		f[1][1] = 0;

		for (int i=1; i<=n; i++)
			for (int j=1; j<=i; j++) {
				f[i+1][j] = min(f[i+1][j], f[i][j] + Dist(i, i+1));
				f[i+1][i] = min(f[i+1][i], f[i][j] + Dist(j, i+1));
				f[i][i] = min(f[i][i], f[i][j] + Dist(j, i));
			}
		printf("%.2lf\n", f[n][n]);	
	}
	return 0;	
}