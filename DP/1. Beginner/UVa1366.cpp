#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 510
#define maxm 510
using namespace std;
int n, m;
int a[maxn][maxm];
int b[maxn][maxm];
int suma[maxn][maxm];
int sumb[maxn][maxm];
int f[maxn][maxm];

void Clear() {
	memset(suma, 0, sizeof(suma));
	memset(sumb, 0, sizeof(sumb));
}

void DP() {
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
		{
			f[i][j] = max(f[i-1][j]+suma[i][j], f[i][j-1]+sumb[i][j]);
		}
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && n && m) {
		Clear();
		for (int i=1; i<=n; i++)
			for (int j=1; j<=m; j++) {
				scanf("%d", &a[i][j]);
				suma[i][j] = suma[i][j-1] + a[i][j];
			}
		for (int i=1; i<=n; i++)
			for (int j=1; j<=m ;j++) {
				scanf("%d", &b[i][j]);
				sumb[i][j] = sumb[i-1][j] + b[i][j];
			}
		DP();
		printf("%d\n", f[n][m]);
	}
	return 0;
}