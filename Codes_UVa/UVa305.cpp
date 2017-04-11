#include <cstdio>
using namespace std;
bool check(int k, int m) {
	int kill = 0;
	for (int i=0; i<k; i++) { //kill k times
		kill = (kill + m - 1) % (k * 2 - i);
		if (kill < k) return 0; // good people being killed
	}
	return 1;
}

int main() {
	int ans[15];
	for (int k=1; k<15; k++)
		for (int m = k; ; m++)
			if (check(k, m)) {
				ans[k] = m;
				break;
			}

	int k;	
	while (scanf("%d", &k)!=EOF && k)
		printf("%d\n", ans[k]);
	return 0;
}