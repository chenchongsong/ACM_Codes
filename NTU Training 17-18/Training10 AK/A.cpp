#include <cstdio>
// #include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct pp {long long pos, need;} a[100010];


long long N, K;
long long dis = 0;
bool cmp (pp A, pp B) {return (A.pos < B.pos)?true:false;}
bool cmp2 (pp A, pp B) {return (A.pos > B.pos)?true:false;}

int main() {
	scanf("%lld%lld", &N, &K);
	for (int i=1; i<=N; i++) {
		scanf("%lld%lld", &a[i].pos, &a[i].need);

	}
	sort(a+1, a+N+1, cmp);
	int first_right = N+1;
	for (int i=1; i<=N; i++) if (a[i].pos >= 0 ) {first_right = i; break;}
	//  = lower_bound(a+1, a+N+1, 0)-a;

	// printf("first_right == %d\n", first_right);

	long long vol = 0;
	long long i=1, curdis = 0;
	while (i < first_right) {
		if (a[i].need > K) {
			dis += (-2)*a[i].pos*(a[i].need / K);
			a[i].need %= K;
		}
		if (a[i].need == 0) {
			i++;
			if (i == first_right) break;
		}
		curdis = a[i].pos;
		// printf("curdis == %d\n", curdis);
		while (vol < K && i < first_right) {
			int newvol = min(a[i].need, K-vol);
			vol += newvol;
			a[i].need -= newvol;
			if (a[i].need == 0) i++;
			if (i == first_right) break;
		}
		vol = 0;
		dis += curdis * (-2);
	}
	sort(a+first_right, a+N+1, cmp2);

	vol = 0;
	i = first_right;
	curdis = 0;
	while (i <= N) {
		if (a[i].need > K) {
			dis += (2)*a[i].pos*(a[i].need / K);
			a[i].need %= K;
		}
		if (a[i].need == 0) {
			i++;
			if (i > N) break;
		}
		curdis = a[i].pos;
		// printf("curdis == %d\n", curdis);
		while (vol < K && i <= N) {
			int newvol = min(a[i].need, K-vol);
			vol += newvol;
			a[i].need -= newvol;
			if (a[i].need == 0) i++;
			if (i > N) break;
		}
		vol = 0;
		dis += curdis * (2);
	}

	printf("%lld\n", dis);


	return 0;

}
/*

2 100
-10 50
-10 175
-25 20


5 3
1002 800
1001 800
1000 800
999 800
998 800
*/