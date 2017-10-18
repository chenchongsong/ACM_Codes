#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int tc, l1, a1, l2, a2, l3, a3;

int main() {
	cin >> tc;
	while (tc--) {
		cin >> l1 >> a1 >> l2>> a2 >> l3 >> a3;
		int num_ans = 0;
		int ansx = 0, ansy = 0;
		for (int x = 1; x<=10000; x++) {
			int y = (l3 - x * l1) / l2;
			if (y < 1) continue; // x , y must be a positive integer
			if (x*l1+y*l2 == l3 && x*a1+y*a2 == a3) {
				num_ans ++ ;
				ansx = x;
				ansy = y;
			}
		}
		if (num_ans == 1) {
			cout << ansx << " " << ansy << endl;
		}
		else puts("?");
	}
}
