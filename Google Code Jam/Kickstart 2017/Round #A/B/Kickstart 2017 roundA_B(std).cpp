#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <bitset>

using namespace std;
typedef pair<int, int> Pi;
typedef long long ll;
#define pii Pi
#define pll PL
#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0;i<n;i++)
#define all(x) (x).begin(), (x).end()
typedef tuple<int, int, int> t3;
typedef pair<ll, ll> PL;

int d[8020][8020];

void solve(){
	string a, b; cin >> a >> b;
	string A = "?a", B = "?a";
	for(char c : a){
		if(c == '*')rep(i, 4)A.pb('*');
		else A.pb(c);
	}
	for(char c : b){
		if(c == '*')rep(i, 4)B.pb('*');
		else B.pb(c);
	}
	int n = sz(A) - 1, m = sz(B) - 1;
	d[0][0] = 1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			d[i][j] = 0;
			if(A[i] != '*' && B[j] != '*')d[i][j] = (A[i] == B[j] && d[i-1][j-1]);
			else if(A[i] == '*' && B[j] != '*'){
				d[i][j] = d[i-1][j] | d[i-1][j-1];
				// 该‘*’不代表0个字符 | 该‘*’代表1个字符
			}
			else if(A[i] != '*' && B[j] == '*'){
				d[i][j] = d[i][j-1] | d[i-1][j-1];
			}
			else{
				d[i][j] = d[i][j-1] | d[i-1][j] | d[i-1][j-1];
			}
		}
	}
	printf("%s\n", d[n][m] ? "TRUE" : "FALSE");
}

int main(){
	int Tc = 1; scanf("%d", &Tc);
	for(int tc=1;tc<=Tc;tc++){
		printf("Case #%d: ", tc);
		solve();
	}
	return 0;
}
