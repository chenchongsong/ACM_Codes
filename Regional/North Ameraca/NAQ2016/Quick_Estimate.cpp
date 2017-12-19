#include <cstdio>
#include <string>
#include <iostream>

using namespace std;
string s;
int main () {
	int n;
	scanf("%d", &n);
	for (int i=1; i<=n; i++) {
		cin >> s;
		cout << s.size() << endl;
	}
	return 0;
}