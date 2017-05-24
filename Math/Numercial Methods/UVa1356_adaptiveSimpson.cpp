#include <cstdio>
#include <cmath>
using namespace std;
double a;

double Cal(double x) {
	double a2 = a*a, x2 = x*x;
	return sqrt(1 + 4 * a2 * x2);
}

double simpson(double a, double b) {
	double c = (a + b) / 2.0;
	return (Cal(a)+4*Cal(c)+Cal(b)) * (b-a) / 6.0;
}

//recursive process of adaptive simpson's rule
//given A as the simpson Value for the whole interval [a,b]
double asr(double a, double b, double eps, double A) {
	double c = (a + b) / 2.0;
	double L = simpson(a, c), R = simpson(c, b);
	if  (fabs(L+R-A) <= 15*eps)
		return L + R + (L+R-A)/15.0;
	return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

//main process of adaptive simpson's rule
double asr(double a, double b, double eps) {
	return asr(a, b, eps, simpson(a, b));
}

double arcLen(double w, double h) {
	a = 4.0 * h / (w * w);
	return asr(0, w/2, 1e-5) * 2.0;
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