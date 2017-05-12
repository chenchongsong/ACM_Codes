#include <cstdio>
#include <cmath>
using namespace std;
const double eps = 1e-14;
double p, q, r, s, t, u;

double F(double x) {
	return p*exp(-x) + q*sin(x)+ r*cos(x) + s*tan(x) + t*x*x + u;
}

int main() {
	while (scanf("%lf%lf%lf%lf%lf%lf", &p, &q, &r, &s, &t, &u)==6) {
		double f0 = F(0), f1 = F(1);
		if (f1 > eps || f0 < -eps) printf("No solution\n");
		else {
			double x = 0, y = 1.0, m = 0;
			for (int i=0; i<100; i++) {
				m = (x+y) / 2.0;
				if (F(m) < 0)
					y = m;
				else
					x = m;
			}
			printf("%.4lf\n", m);
		}
	}
	return 0;	
}