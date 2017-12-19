#include <cstdio>
#include <iostream>
typedef long long ll;
using namespace std;
const long long maxn = 1000005;
const long long mod = (ll)1e9+7LL;
ll f[maxn];
int t, n;

int main() {
	// cout << mod << endl;
	f[1] = 1;
	f[2] = 2;
	for (ll i=3; i<maxn; i++)
		f[i] = f[i-1] + (i-1) * f[i-2],
		f[i] %= mod;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << f[n] << endl;
	}
	return 0;
}