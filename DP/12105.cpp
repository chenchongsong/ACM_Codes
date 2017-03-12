// f[i][j] 表示 不超过i根火柴 能摆出的最大的 %m==j 的数
// 枚举最后一位数字为k
// f[i][j] = max{ f[i-num[k]][x] | (10*x)%M + k%M == j}
// ans = f[n][0]
// O(N*M * N*M)

// 待进一步优化：(10*x)%M + k%M == j 可以不必枚举 可直接解线性同余方程求得

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M;
int num[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int f[110][3010];

int main() {
	int kase = 0;
	while (scanf("%d%d", &N, &M) && N) {
		printf("Case %d: ", ++kase);
		//Clear();
		memset(f, -1, sizeof(f));
		for (int i=0; i<10; i++)
			f[num[i]][i%M] = i;

		for (int i=1; i<=N; i++) {
			for (int j=0; j<M; j++) {
				for (int k=0; k<10; k++) // 枚举最后一位数字
				{
					if (i < num[k]) continue;
					int x = 0;
					for (; x<M; x++)
						if ((10*x+k)%M==j) {

							if (f[i-num[k]][x] < 0) continue;
							f[i][j] = max(f[i][j], f[i-num[k]][x]*10 + k);
						//(10x) % m == (j-k + m) % m
						//int a=10, b=(j-k+M)%M, p = N;
						//if (gcd(a, p)%b != 0) continue;
						}
				}
				f[i][j] = max(f[i][j], f[i-1][j]);	
			}
		}
		printf("%d\n", f[N][0]);
	}
	return 0;
}