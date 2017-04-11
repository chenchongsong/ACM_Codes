#include <cstdio>
#include <cmath>
using namespace std;
int main() {
	int n;
	while (scanf("%d", &n)!=EOF) {
		int cnt = 1;
		int remain = 1 % n;
		while (remain != 0) {
			cnt++;
			remain = (remain*10 + 1) % n;
		}
		printf("%d\n", cnt);
	}
	return 0;
}