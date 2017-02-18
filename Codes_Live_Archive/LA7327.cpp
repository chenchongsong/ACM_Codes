#include <cstdio>
#define MaxN 300010
#define MaxM 100010
const long long Mod = 1e9 + 7;

using namespace std;

int N, M;
char s[MaxN];
int Power[MaxN];

int main()
{
	Power[0] = 1;
	for (int i=1;i<=MaxN;i++)
		Power[i] = ( Power[i-1] * 2 ) % Mod;

	while (scanf("%d%d\n", &N, &M) != EOF)
	{
		scanf("%s", s+1);
		int Remain = 0, Cut = 0;
		for (int i=1;i<=N;i++)
		{
			Remain = (Remain * 10 + s[i] - '0') % M;
			if (Remain == 0) Cut++;

			//printf("%d----%d %d %c\n", i, Remain, Cut, s[i]); 
		}
		if (Remain) { puts("0"); continue;}
		printf("%d\n", Power[Cut-1]);
	}
	return 0;
}