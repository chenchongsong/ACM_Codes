#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 10010;
int a[maxn], b[maxn], c[maxn], n;

double F(double x) {
	double ans = a[0]*x*x + b[0]*x + c[0];
	for (int i=1; i<n; i++)
		ans = max(ans, a[i]*x*x + b[i]*x + c[i]);
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i=0; i<n; i++)	scanf("%d%d%d", &a[i], &b[i], &c[i]);
		double l = 0, r = 1000.0;
		for (int i=0; i<100; i++) {
			double m1 = (2*l + r) / 3;
			double m2 = (l + 2*r) / 3;
			if (F(m1) < F(m2)) r = m2;
			else l = m1;
		}
		printf("%.4lf\n", F(l));
	}
	return 0;
}
