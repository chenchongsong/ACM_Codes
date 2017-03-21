#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define maxstick 5010
#define maxpeople 1010
using namespace std;
int f[maxstick][maxpeople], len[maxstick];
//f[i][j] 表示前i根筷子 分成j个三元组(i.e.分给j个人)
int Diff(int a, int b) {return (len[a]-len[b])*(len[a]-len[b]);}
int main() {
	int T; cin >> T;
	while (T--) {
		memset(f, 63, sizeof(f));
		int people, stick;
		cin >> people >> stick;
		people += 8;
		for (int i=stick; i>=1; i--) //倒着读入
			cin >> len[i];
		for (int i=0; i<=stick; i++)
			f[i][0] = 0;
		for (int i=1; i<=stick; i++) {
			for (int j=1; j<=people; j++) {
				if (i < (j*3)) continue;
				f[i][j] = min(f[i-1][j], f[i-2][j-1] + Diff(i, i-1));
				// min(不用第i根筷子, 讲第i根和第j根当做一个人的a与b)
				// 一个人的a与b必定相邻 否则不优
				// eg. C2 B2 c1 A2 b1 a1 不如 C2 B2 A2 c1 b1 a1
				// eg. C2 c1 b1 B2 A2 a1 不如 C2 c1 B2 A2 b1 a1
			}
		}
		cout << f[stick][people] << endl;
	}
	return 0;
}