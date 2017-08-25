#include <cstdio>
using namespace std;
int main() {
	int N, pi;
	while(scanf("%d", &N) && N) {
		int v = 0;
		for (int i=1; i<=N; i++) {
			scanf("%d", &pi);
			v ^= pi;
		}
		printf("%s\n", v ? "Yes" : "No");
	}
	return 0;
}