#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
typedef long long ll;
#define mod1 1000007 // must be greater than 300000, otherwise hashvalue would propably become 0
#define mod2 9999907
using namespace std;
string s;
int main() {

	char c;
	ll tar_hash1 = 0, tar_hash2 = 0, tar_hash3 = 0;
	cin >> s;
	for (int i=0; i<s.size(); i++) {
		c = s[i];
		tar_hash1 = (tar_hash1 * 10 + c -'0') % mod1;
		tar_hash2 = (tar_hash2 * 10 + c -'0') % mod2;
	}

	ll tmp_hash1 = 1, tmp_hash2 = 1, tmp_hash3 = 1;
	for (ll i = 1; i <= 300000; i++) {
		tmp_hash1 = (tmp_hash1 * i) % (ll)mod1;
		tmp_hash2 = (tmp_hash2 * i) % (ll)mod2;
		if (tmp_hash1 == tar_hash1 && tmp_hash2 == tar_hash2) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
