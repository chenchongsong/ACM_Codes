#include <cstdio>
#include <cmath>
using namespace std;


int count_factor(int x) {
	int ret = 0;
	for (int i = 2; i*i <= x; i++) {
		while (x % i == 0) {
			ret++;
			x /= i;
		}
	}

	if (x > 1) // the original x is a big prime number
		ret++;
	return ret;
}

int main() {
	int T, N, M;
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		
		int v = 0;
		scanf("%d%d", &N, &M);
		
		for (int i=1; i<=N; i++) {
			int sum = 0, tmp;
			
			for (int j=1; j<=M; j++) {
				scanf("%d", &tmp);
				sum += count_factor(tmp);
			}
			v ^= sum;
		}

		printf("Case #%d: %s\n", kase, v ? "YES" : "NO");
	}
	return 0;
}

/*

5
2 2
2 3
2 3
2 2
4 9
8 5
3 3
2 3 5
3 9 2
8 8 3
3 3
3 4 5
4 5 6
5 6 7
2 3
4 5 6
7 8 9

*/