#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int a, b;
	while (cin >> a >> b && (a||b)) {
		int ans = 0;
		for (int i=1; i<=(int)sqrt(b)+1; i++) {
			if (a <= i*i && i*i <=b)
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}