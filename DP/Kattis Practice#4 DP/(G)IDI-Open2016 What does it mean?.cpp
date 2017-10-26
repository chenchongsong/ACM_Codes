#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, int> val; 
int dp[100][100];

int main() {
	int n;
	string name;
	cin >> n >> name;
	for (int i=1; i<=n; i++) {
		string s;
		int v;
		cin >> s >> v;
		val[s] = v;
	}
	
	for (int len = 1; len <=name.size(); len++) {
		for (int i=0; i<name.size(); i++) {
			int j = i + len - 1;
			if (j >= name.size()) continue;
			if (val.count(name.substr(i,len)))
				dp[i][j] = val[name.substr(i,len)];
			// printf("dp[%d][%d] ==.%d\n",i,j,dp[i][j]);
			
			for (int k = i; k < j; k++) {
				dp[i][j] += (dp[i][k] * dp[k+1][j]);
				dp[i][j] = dp[i][j] % 1000000007;
			}
		}
	}
	cout << dp[0][name.size()-1] << endl;
	return 0;
}