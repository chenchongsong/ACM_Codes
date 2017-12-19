#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
#define maxn 200011
double MIN(double a, double b) {return a<b?a:b;}
int h[maxn], v[maxn];
int t, n;

int main() {
	cin >> t;
	while (t--) {
		cin >> n;

		for (int i=1; i<=n; i++) {
			cin >> h[i] >> v[i];
		}
		if (h[3] <= h[1]) {
			puts("0");
			continue;
		}
		// now h[3] > h[1]

		bool flag = 0;
		double ans = 1e18;
		for (int i=1; i<=n; i++) { // start from i at time 0
			if (i == 3) continue;
			if (h[i] > h[1] || v[i] <= v[3]) continue;
			flag = 1;
			ans = MIN(ans, (double)(h[3]-h[i]) / (double)(v[i]-v[3]));
		}
		if (!flag) puts("BYE DENZEL");
		else printf("%.10lf\n", ans);
	}
	return 0;
}