#include <cstdio>
#include <cstring>
#define maxn 20
using namespace std;
int n, init_ability, ability[maxn];
long long f[1<<maxn];
// ans_max = P(16, 16) = 16! > 2*10^13
char s[maxn];

void init() {
	memset(f, 0, sizeof(f));
	memset(ability, 0, sizeof(ability));
	init_ability = 0;
	scanf("%s", s);
	for (int j=0; j<strlen(s); j++)
		init_ability += (s[j]-'0')*(1<<j);
	f[0] = 1;
}

void DP() {
	for (int s=0; s<(1<<n); s++) {
		int cur_ability = init_ability;
		for (int i=0; i<n; i++)
			if (s & (1<<i))
				cur_ability |= ability[i];
		for (int i=0; i<n; i++)
			if (cur_ability & (1<<i) && (s & (1<<i))==0)
				f[s+(1<<i)] += f[s]; // 向后转移
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int kase = 1; kase<=T; kase++) {
		scanf("%d", &n);
		init();
		for (int i=0; i<n; i++) {
			scanf("%s", s);
			for (int j=0; j<strlen(s); j++)
				ability[i] += (s[j]-'0')*(1<<j);
		}
		DP();
		printf("Case %d: %lld\n", kase, f[(1<<n)-1]);
	}
}
