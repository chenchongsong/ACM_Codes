#include <cstdio>
#include <map>
#include <iostream>
using namespace std;

int t, n;
int a[200011];
map<int, int> cnt;

int main() {
	cin >> t;
	while (t--) {
		cnt.clear();
		cin >> n;
		for (int i=1; i<=n; i++) {
			cin >> a[i];
			if (cnt[a[i]] < 2) {
				printf("%d ", a[i]);
				cnt[a[i]] = cnt[a[i]] + 1;
			}
		}
		puts("");
	}
	return 0;
}