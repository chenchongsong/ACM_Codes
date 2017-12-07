#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int t, n;
int p[1000];

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		int sgsum = 0;
		bool suf = false; // whether sufficient pile exists
		for (int i=1; i<=n; i++) {
			cin >> p[i];
			sgsum ^= p[i];
			suf |= (p[i] > 1);
		}
		if (suf) {
			if (sgsum) puts("John");
			else puts("Brother");
		}
		else {
			if (n % 2 == 0) puts("John");
			else puts("Brother");
		}
	}
	return 0;
}