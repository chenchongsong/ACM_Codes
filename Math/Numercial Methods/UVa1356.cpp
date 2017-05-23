#include <cstdio>
#include <cmath>
using namespace std;

double Cal(double a, double x) {
	double a2 = a*a, x2 = x*x;
	return (x*sqrt(a2+x2)+a2*log(fabs(x+sqrt(a2+x2))))/2;
}

double arcLen(double w, double h) {
	double a = 4.0 * h / (w * w);
	double b = 1.0 / (2 * a);
	return (Cal(b, w/2) - Cal(b, 0)) * 4 * a;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		int D, H, B, L;
		scanf("%d%d%d%d", &D, &H, &B, &L);
		int n = (B+D-1) / D;
		double D1 = (double) B/n;
		double L1 = (double) L/n;
		double left = 0, right = H;
		while (right-left > 1e-5) {
			double m = (left+right) / 2.0;
			if (arcLen(D1, m) < L1)
				left = m;
			else
				right = m;
		}
		if (kase > 1) puts("");
		printf("Case %d:\n%.2lf\n", kase, H-left);
	}
	return 0;
}

/*

2
20 101 400 4042 
1 2 3 4 

*/