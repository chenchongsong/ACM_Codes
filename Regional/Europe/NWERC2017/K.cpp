#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define maxn 40696
using namespace std;
int n;
double dale;
double a[maxn];

bool cmp (double A, double B) {
	return A > B;
}

double pro[maxn][15];
int pos[maxn]; // take in an id
int s[maxn], e[maxn]; // take in pos
int main() {
	scanf("%d", &n);
	scanf("%lf", &dale);
	for (int i=1; i<n; i++) {
		scanf("%lf", &a[i]);
	}
	sort(a+1, a+n, cmp);
	a[n] = dale;

	// for (int i=1; i<=n; i++) printf("a[%d] == %.3lf\n", i, a[i]);
	int len = 0;
	while ((1<<(len+1)) <= n) len++;
	int r2 = 1 << len;
	
	for (int i=1; i<=(n-r2); i++) {
		pos[2*i-1] = i;
		pos[2*i] = i;
		s[i] = i*2-1;
		e[i] = i*2;
		pro[i*2-1][2] = a[i*2-1] / (a[i*2-1]+a[2*i]);
		pro[i*2][2] = a[i*2] / (a[i*2-1]+a[2*i]);
	}
	for (int i=2*(n-r2) + 1; i<=n; i++) {
		pos[i] = i - (n-r2);
		s[pos[i]] = e[pos[i]] = i;
		pro[i][2] = 1.0;
	}
	// for (int i=1; i<=n; i++) {
	// 	printf("pos[%d] = %d\n",i,pos[i]);
	// }
	// for (int i=1; i<=n; i++) {
	// 	printf("pro[%d][2] = %.3lf\n",i,pro[i][2]);
	// }
	// for (int i=1; i<=r2; i++) printf("s[%d] == %d && e[%d] == %d\n",i,s[i],i,e[i]);
	
	for (int step = 3; step <= 2 + len; step++) {
		int curlen = (1<<(step-3));
		// printf("curlen = %d\n", curlen);
		for (int i=1; i<=n; i++) {
			// printf("i %d\n", i);
			int left_pos = ( (((pos[i]-1)/curlen)^1) * curlen + 1);
			int right_pos = left_pos + curlen - 1;
			int left_id = s[left_pos];
			int right_id = e[right_pos];
			// printf("from pos %d -- %d\n", left_pos, right_pos);
			// printf("from id %d -- %d\n", left_id, right_id);
			pro[i][step] = 0.0;
			for (int j=left_id; j<=right_id; j++) {
				
				pro[i][step] += pro[i][step-1] * pro[j][step-1] * a[i] / (a[i]+a[j]);

			}
		}
	}
	// for (int step=3; step<=2 + len; step++) {
	// 	for (int i=1; i<=n; i++)

	// 	printf("%.3lf ", pro[i][step]);
	// 	puts("");
	// }

	printf("%.10lf\n", pro[n][2+len]);
	return 0;
}