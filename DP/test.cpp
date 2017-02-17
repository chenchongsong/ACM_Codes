#include <cstdio>
using namespace std;
int main()
{
	int S;
	scanf("%d", &S);
	for (int S0 = S&(S-1); S0; S0= S &(S0-1))
	{
		printf("%d\n", S0);

	}
	return 0;
}