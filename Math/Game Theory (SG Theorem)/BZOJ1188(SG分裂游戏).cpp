#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int sg[25];
int t, n, p[25];
bool mex[250];

int SG(int x) {
	if (sg[x] != -1)
		return sg[x];
	memset(mex, false, sizeof(mex));
	for (int j=0; j<x; j++)
		for (int k=j; k<x; k++)
			mex[SG(j)^SG(k)] = true;
			// 后继状态：变为两堆大小更小的新石子
	for (int i=0; ; i++)
		if (!mex[i])
			return sg[x] = i;
	return -1;
}

int main() {
	cin >> t;
	memset(sg, -1, sizeof(sg));

	while (t--) {
		cin >> n;
		int sg_sum = 0;
		for (int i=0; i<n; i++) {
			cin >> p[i];
			for (int j=1; j<=p[i]; j++)
				sg_sum ^= SG((n-1)-i);
				// eg.把一颗放在第0位的豆子看成一堆大小为n-1的石子
				// 一颗豆子可以变成两颗新豆子
				// 对应的，一堆大小为x的石子可以变成两堆大小<x的石子
		}
		if (sg_sum == 0) {
			puts("-1 -1 -1");
			puts("0");
			continue;
		}

		int cnt_ans = 0;
		bool founded = 0;
		for (int i=0; i<n; i++)
			for (int j=i+1; j<n; j++)
				for (int k=j; k<n; k++) {
					if (!p[i]) continue;
					if ((sg_sum^SG(n-1-i)^SG(n-1-j)^SG(n-1-k)) == 0) {
						if (!founded)
							founded = 1,
							printf("%d %d %d\n",i,j,k);
						cnt_ans++;
					}
				}
		printf("%d\n", cnt_ans);
	}
	return 0;
}

/*

2
4
1 0 1 0
3
0 0 1

*/