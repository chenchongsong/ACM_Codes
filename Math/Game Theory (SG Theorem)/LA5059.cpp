// Liu Rujia Traning Guide P137-138
// 打表找规律

#include <iostream>
typedef long long ll;
using namespace std;

ll SG(ll ai) {
	if (ai % 2 == 0)
		return ai / 2;
	if (ai == 1)
		return 0;
	return SG(ai / 2);
}

int main() {
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		ll ai, v = 0;
		
		for (int i=1; i<=N; i++) {
			cin >> ai;
			v ^= SG(ai);
		}

		cout << (v ? "YES" : "NO") << endl;
	}
	return 0;
}