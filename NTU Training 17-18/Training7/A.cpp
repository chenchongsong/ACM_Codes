#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
int a[100], b[100];

int main() {
	int T; cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		
		int ans = 0;
		int tmp; cin >> tmp;
		for (int i=1; i<=12; i++) cin >> a[i];
	
		for (int i=2; i<=11; i++) {
			for (int j=i; j<=11; j++) {
				int flag = 1;
				for (int k=i; k<=j; k++) {
					if (a[k] <= max(a[i-1], a[j+1])) {
						flag = 0;
						break;
					}
				}
			ans += flag;
			}
		}
		printf("%d %d\n", tc, ans);
	}
	return 0;
}

/*


1
1 0 1 2 4 3 1 3 4 5 2 1 0

*/