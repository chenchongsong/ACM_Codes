#include <cstdio>
using namespace std;
const int MAXN = 10000;

double X[MAXN], Y[MAXN], W[MAXN];
int N;

double abs(double x) {return x>0?x:-x;}
double max(double x, double y) {return x>y?x:y;}
double Cal(double x, double y){
	double ret = 0;
	for (int i = 0; i < N; i++)
		ret += max(abs(X[i] - x), abs(Y[i] - y))*W[i];
	return ret;
}

double ternarySearchY(double x){
	// given a x-coridinate, find the minimum pos of y
	double lo = -1000, hi = 1000;
	for (int i = 0; i < 100; i++){
		double m1 = (2 * lo + hi) / 3;
		double m2 = (lo + 2 * hi) / 3;
		double L = Cal(x, m1), R = Cal(x, m2);
		if (L <= R) hi = m2; // m1 is closer to the minimum position, move the right side.
		else lo = m1;
	}
	return Cal(x, lo);
}

double ternarySearchX(){ // 平面上的单峰函数？ 故而可以用三分法求解
	// 先三分x坐标
	double lo = -1000, hi = 1000;
	for (int i = 0; i < 100; i++){
		double m1 = (2 * lo + hi) / 3;
		double m2 = (lo + 2 * hi) / 3;
		double L = ternarySearchY(m1), R = ternarySearchY(m2);
		if (L <= R) hi = m2; // m1 is closer to the minimum pos.
		else lo = m1;
	}
	return ternarySearchY(lo);
}

int main(){
	freopen("Desktop/kickstart B/code/B-large-practice.in", "r", stdin);
	freopen("Desktop/kickstart B/code/large-ans.out", "w", stdout);

	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++){
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%lf%lf%lf", X + i, Y + i, W + i);
		printf("Case #%d: %.8lf\n", tc, ternarySearchX());
	}
}