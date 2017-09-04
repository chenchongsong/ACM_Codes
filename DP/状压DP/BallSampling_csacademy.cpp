// https://csacademy.com/contest/archive/task/ball-sampling

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
double a[22], p[22], f[1<<22];
bool vis[1<<22];
int N, M;
int tot;
double sum = 0;

void Init() {	
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));

	tot = (1<<N)-1;
	vis[tot] = 1;
	f[tot] = 0;
}

double dp(int s) {
	if (vis[s]) return f[s];
	vis[s] = 1;

	// assume equation A * f[s] = B;
	double A = 1.0, B = 0.0;

	for (int i=0; i<N; i++) {
		if ( s & (1<<i) ) { // bad pick

			A -= p[i];
			B += p[i];
		}
		else { // good pick
			B += p[i] * dp(s | (1<<i));
			B += p[i];
		}		
	}
	return f[s] = B/A;
}

int main() {
	scanf("%d", &N);
	for (int i=0; i<N; i++) {
		scanf("%lf", &a[i]);
		sum += a[i];
	}
	for (int i=0; i<N; i++)
		p[i] = a[i] / sum;

	Init();
	printf("%.10lf\n", dp(0));
	return 0;
}