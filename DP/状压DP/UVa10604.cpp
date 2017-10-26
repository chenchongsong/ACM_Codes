#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

int heat[20][20], product[20][20];
int cnt[20];
int n, m;
map<vector<int>, int> dp;
queue<vector<int> > Q;

void Clear() {
	memset(cnt, 0, sizeof(cnt));
	dp.clear();
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		
		Clear();
		cin >> m;
		for (int i=0; i<m; i++)
			for (int j=0; j<m; j++) {
				cin >> product[i][j] >> heat[i][j];
				product[i][j]--;
			}

		cin >> n;
		for (int i=0; i<n ;i++) {
			int tmp;
			cin >> tmp;
			cnt[--tmp]++;
		}
		string s; cin >> s;

		vector<int> tot, Qhead;
		tot.clear();
		for (int i=0; i<m; i++) tot.push_back(cnt[i]); 
		dp[tot] = 0; // at the beginning state, heat = 0
		Q.push(tot);
		
		while (!Q.empty()) {

			Qhead = Q.front();
			Q.pop();
			for (int i=0; i<Qhead.size(); i++) {
				if (Qhead[i] == 0) continue;
				
				for (int j=0; j<Qhead.size(); j++) {
				// j cannot start from i
				// since (i mix j) can be different from (j mix i)
					if (Qhead[j] == 0) continue;
					if (i == j && Qhead[i] < 2) continue;
					vector<int> next = Qhead;
					next[i]--;
					next[j]--;
					next[product[i][j]]++;
					if (dp.count(next) == 0) { // state "next" does not exist in the map
						dp[next] = dp[Qhead] + heat[i][j];
						Q.push(next);
					}
					else {
						dp[next] = min(dp[next], dp[Qhead] + heat[i][j]);
					}
				}
			}
		}

		int ans = 0x3f3f3f3f;
		for (int i=0; i<m; i++) {
			// try each ending state "tmp"
			vector<int> tmp;
			for (int j=0; j<m; j++) tmp.push_back(0);
			tmp[i]++;

			if (dp.count(tmp) == false) continue; // notice
			if (dp[tmp] < ans) ans = dp[tmp];
		}
		cout << ans << endl;
	}
	return 0;
}

/*

2
3
1 0
3 -10
3 3000
3 -10
2 0
1 -500
3 3000
1 -500
3 0
4
1 2 2 3
/
3
1 0
3 500
3 -250
3 500
2 0
1 10
3 -250
1 100
3 0
6
1 1 1 2 2 3
.

*/