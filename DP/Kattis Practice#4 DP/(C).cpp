#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
using namespace std;

map<string, int> vis;
int ans;
void DFS(const string& s) {
	if (vis[s]) return;
	vis[s] = 1;

	int cnt = 0;
	for (int i=0; i<s.size(); i++) cnt += (s[i]=='o');
	// cout << s << " is " << cnt << endl;
	ans = min(ans, cnt);

	for (int i=0; i<=20; i++) {
		if (s[i+1] != 'o') continue;
		if (s[i]=='o' && s[i+2]=='-') {
			string tmp = s;
			tmp[i] = '-';
			tmp[i+1] = '-';
			tmp[i+2] = 'o';
			DFS(tmp);
			continue;
		}
		if (s[i]=='-' && s[i+2]=='o') {
			string tmp = s;
			tmp[i] = 'o';
			tmp[i+1] = '-';
			tmp[i+2] = '-';
			DFS(tmp);
			continue;
		}
	}
}

void Clear() {
	vis.clear();
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		Clear();
		string s;
		cin >> s;
		int cnt = 0;
		for (int i=0; i<s.size(); i++) cnt += (s[i]=='o');
		ans = cnt;
		DFS(s);
		cout << ans << endl;
	}
	return 0;
}

/*

5
---oo----------oo------
-o--o-oo-----o--o-oo---
-o----ooo----o----ooo--
ooooooooooooooooooooooo
oooooooooo-ooooooooooo-

*/