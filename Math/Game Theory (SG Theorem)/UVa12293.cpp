// 打表找规律
// similar to LA 5059

#include <iostream>
typedef long long ll;
using namespace std;

ll SG(ll x) {
	if (x % 2 == 0)
		return x / 2;
	if (x == 1)
		return 0;
	return SG(x / 2);
}

int main() {
	int N;
	while (cin >> N && N) {
		cout << (SG(N) ? "Alice" : "Bob") << endl;
	}
	return 0;
}