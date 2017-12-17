#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#define maxn 200005
#define ll long long
using namespace std;

ll n, a[maxn], b[maxn];
ll sumb[3];
ll cnt[3]; // , snt1, cnt2;
int main() {
	cin >> n;
	for (int i=1; i<=n; i++) {
		int tmp;
		scanf("%d", &tmp);
		a[i] = (ll)tmp;
	}
	for (int i=1; i<=n; i++) {
		int tmp;
		scanf("%d", &tmp);
		b[i] = (ll)tmp;
		sumb[i % 3] += b[i];
		// printf("sumb );
	}
	for (int i=1; i<=n; i++) {
		for (int t=0; t<3; t++) {
			cnt[(i+t)%3] += (a[i] * sumb[t]);
		}
	}
	cout << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
	return 0;


}

/*

7
6 2 4 5 1 1 4
2 5 1 4 2 3 4

*/