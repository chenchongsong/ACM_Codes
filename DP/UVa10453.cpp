// f[i][j] = min{ f[i+1][j]+1, f[i][j-1]+1, (s[i]==s[j]) f[i+1][j-1]
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#define maxn 2010
using namespace std;
int f[maxn][maxn], opt[maxn][maxn];
char s[maxn], ans[maxn];

void Clear() {
	memset(f, 0, sizeof(f));
	memset(opt, 0, sizeof(opt));
}

int main() {
	while (scanf("%s", s+1)!=EOF) {
		Clear();
		int n = strlen(s+1);
		for (int i=n; i>=1; i--) {
			f[i][i] = 0;
			opt[i][i] = 2;
			//f[i][i].str = s[i];
			for (int j=i+1; j<=n; j++) {
				if (f[i+1][j] < f[i+1][j]) {
					f[i][j] = f[i+1][j] + 1;
					opt[i][j] = 0;
					//f[i][j].str = s[i]+f[i+1][j].str+s[i];
				} else {
					f[i][j] = f[i][j-1] + 1;
					opt[i][j] = 1;
					//f[i][j].str = s[j]+f[i][j-1].str+s[j];
				}
				if (s[i]==s[j]) {
					if (j-i == 1) {
						f[i][j] = 0;
						opt[i][j] = 2;
						//f[i][j].str = s[i];
						//f[i][j].str +=s[j];
					} else
						if (f[i+1][j-1] < f[i][j]) {
							f[i][j] = f[i+1][j-1];
							opt[i][j] = 2;
							//f[i][j].str = s[i]+f[i+1][j-1].str+s[j];
						}
				}
				//cout << i<< "--"<< j<< ": "<<f[i][j] <<' '<<f[i][j].str<<endl;
			}
		}
		cout << f[1][n] << ' ';
		int i=1, j=n, cnt=0;
		for (; i<j; ) {
			//printf("%d--%d\n",i,j);
			if (opt[i][j] == 0) {
				ans[++cnt] = s[i];
				i++; continue;
			}
			if (opt[i][j] == 1) {
				ans[++cnt] = s[j];
				j--; continue;
			}
			if (opt[i][j] == 2) {
				ans[++cnt] = s[i];
				i++; j--;
			}
		}
		for (int pos=1; pos<=cnt; pos++) printf("%c", ans[pos]);
		if (i==j) printf("%c", s[i]);
		for (int pos=cnt; pos>=1; pos--) printf("%c", ans[pos]);
		puts("");
	}
	return 0;
}