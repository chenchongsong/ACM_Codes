// https://open.kattis.com/problems/mailbox
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;
int dp[20][200][200];
// dp[ijk] denotes: with i mailbox, we need at least dp[ijk] crackers
// to fully test an interval [j ~ k]
// (get inspiration from UVa10934)
int N, M, K;
int main() {

	memset(dp, 0, sizeof(dp));
	for (int j=0; j<=100; j++)
		for (int k=j; k<=100; k++)
			dp[0][j][k] = INF;
	for (int i=1; i<=10; i++)
		for (int j=0; j<=100; j++)
			dp[i][j][j] = j;
	
	for (int i=1; i<=10; i++) {
		for (int len = 2; len<=100; len++) { // interval DP: len is at outer loop
			for (int j=1; j<=100; j++) {
				int k = j+len-1;
				if (k > 100) continue;
				dp[i][j][k] = INF;
				for (int l = j; l<=k; l++) {
					dp[i][j][k] = min(dp[i][j][k], max(dp[i-1][j][l-1],dp[i][l+1][k]) + l);
				}
			}
		}
	}

	cin >> N;
	for (int i=1; i<=N; i++) {
		cin >> K >> M;
		cout << dp[K][1][M] << endl;
	}
	return 0;
}