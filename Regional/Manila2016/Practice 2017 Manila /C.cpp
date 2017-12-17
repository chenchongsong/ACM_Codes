#include <cstdio>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
map<string, int> cnt;
char c[111];

int main() {
	int t;
	cin >> t;
	while (t--) {
		cnt.clear();
		int n;
		cin >> n;
		for (int i=1; i<=n; i++) {
			scanf("%s", c);
			string s = string(c);
			cnt[s] = cnt[s] + 1;
		}
		auto it = cnt.begin();
		printf("%d\n", (it->second)-1);
	}
	return 0;
}