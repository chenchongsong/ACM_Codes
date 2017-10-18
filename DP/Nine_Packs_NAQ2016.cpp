#include <cstdio>
#include <iostream>
#include <cstring>
#define maxv 100010
#define maxn 110
#define INF 1e7
int H, B;
int sumh, sumb;
int h[maxn], b[maxn];
int fh[maxv], fb[maxv];

using namespace std;
int main() {
	
	cin >> H;
	memset(fh, 63, sizeof(fh));
	fh[0] = 0;
	for (int i=1; i<=H; i++) {
		cin >> h[i];
		sumh += h[i];
		for (int j=sumh; j>=h[i]; j--) // 类似 0/1 背包 倒过来枚举
			fh[j] = min(fh[j], fh[j - h[i]] + 1);
	}

	cin >> B;
	memset(fb, 63, sizeof(fb));
	fb[0] = 0;
	for (int i=1; i<=B; i++) {
		cin >> b[i];
		sumb += b[i];
		for (int j=sumb; j>=b[i]; j--) {
			fb[j] = min(fb[j], fb[j - b[i]] + 1);
		}
	}

	int Ans = INF;
	for (int i=1; i<=min(sumh, sumb); i++)
		if (fh[i] < INF && fb[i] < INF)
			Ans = min(Ans, fh[i]+fb[i]);

	if (Ans == INF) puts("impossible");
	else cout << Ans << endl;

	return 0;
}