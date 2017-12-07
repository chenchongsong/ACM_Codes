#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define maxval 10005
#define maxl 105
#define maxk 105
using namespace std;

int k, s[maxk];
int m, l, h[maxl];
int sg[maxval];
int mex[maxval];

int SG(int x) {
	if (sg[x] != -1)
		return sg[x];

	memset(mex, 0, sizeof(mex));
	for (int i=1; i<=k; i++) {
		if (x - s[i] < 0)
			break;
		mex[SG(x - s[i])] = 1;
	}
	for (int i=0; ; i++)
		if (!mex[i])
			return i;
	return -1;
}

int main () {
	cin >> k;
	for (int i=1; i<=k; i++)
		cin >> s[i];
	sort(s+1, s+1+k);

	memset(sg, -1, sizeof(sg));
	for (int i=0; i<maxval; i++)
		sg[i] = SG(i); //, printf("sg[%d] == %d\n", i,sg[i]);

	cin >> m;
	while (m--) {
		cin >> l;
		int sg_sum = 0;
		for (int i=1; i<=l; i++)
			cin >> h[i], sg_sum ^= SG(h[i]);

		if (sg_sum) printf("W");
		else printf("L");
	}
	puts("");
	return 0;
}

