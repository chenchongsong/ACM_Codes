#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#define maxlen 210
using namespace std;
char s[maxlen];
//bool CanRepeat[maxlen][maxlen][maxlen];
struct interval {
	int ans, node_len;
	std:: string node; //最短循环节
} dp[maxlen][maxlen];
void Clear() {
	memset(dp, 0, sizeof(dp));
}

int main () {
	int T;
	scanf("%d", &T);
	for (int kase = 1; kase<=T; kase++) {
		Clear();
		scanf("%s", s);
		int n = strlen(s);
		for (int i=n-1; i>=0; i--) {
			//CanRepeat[i][i][i] = 1;
			dp[i][i].ans = 1;
			dp[i][i].node_len = 1;
			dp[i][i].node = s[i];

			for (int j=i+1; j<n; j++) {
				//printf("i %d----j %d\n",i,j);
				dp[i][j].ans = j-i+1;
				dp[i][j].node_len = j-i+1;
				dp[i][j].node.assign(s+i, dp[i][j].node_len);
				//cout << dp[i][j].node_len << *(s+i) << dp[i][j].node << " end\n";
				//puts("Here\n\n");

				for (int k=i; k<j; k++)
					if (dp[i][k].ans + dp[k+1][j].ans < dp[i][j].ans)
						dp[i][j].ans = dp[i][k].ans + dp[k+1][j].ans;


				for (int k=i; k<=((i+j)>>1); k++) {
					if ((j-i+1)%(k-i+1) != 0) continue;
					//if (dp[i][k].node_len != (k-i+1)) continue;
					if (dp[i][k].node_len != dp[k+1][j].node_len) continue;
					if (dp[i][k].node != dp[k+1][j].node) continue;

					if (k==i) {
						// 循环节长度为1 果断合并 且不用加括号
						dp[i][j].ans = 1+((j-i+1)>99)+((j-i+1)>9)+1;
						dp[i][j].node_len = 1;
						dp[i][j].node = s[i];
						break;
					}
					if (k==i+1 && (j-i+1)/(k-i+1)==2) {
						// 循环节为 2
						dp[i][j].ans = 2*2;

						dp[i][j].node.assign(s+i, 2);
						dp[i][j].node_len = 2;
						break;
					}
					//puts("OOK");
					//cout<<dp[i][k].ans<<endl;
					dp[i][j].ans = dp[i][k].ans+2+((j-i+1)/(k-i+1)>99)+((j-i+1)/(k-i+1)>9)+1;

					dp[i][j].node_len = dp[i][k].node_len;
					dp[i][j].node = dp[i][k].node;

					break;



				}
				//printf("dp == %d\n", dp[i][j].ans);
			}
		}
		printf("%d\n", dp[0][n-1].ans);
		//cout << dp[0][7].ans << ' '<<dp[0][7].node<<' '<<dp[0][7].node_len<<endl;
		//cout << dp[8][15].ans << ' '<<dp[8][15].node<<' '<<dp[8][15].node_len<<endl;

	}
	return 0;
}

/*

1
ababcdcdababcdcd


*/