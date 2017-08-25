#include <iostream>
using namespace std;

int main() {
	int T, N, ai;
	bool flag;
	cin >> T;
	
	while (T--) {
		cin >> N;
		flag = 0;

		for (int i=1; i<=N; i++) {
			cin >> ai;
			if (ai > 1)	flag = 1;
		}

		flag = flag || (N % 2);

		cout << (flag ? "poopi" : "piloop") << endl;
	}
	return 0;
}