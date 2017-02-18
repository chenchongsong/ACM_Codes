#include <cstdio>
#include <algorithm>
using namespace std;

int SumA = 0, SumB = 0, SumC = 0;
int T;

int main()
{
	scanf("%d",&T);
	while (T--)
	{
		int A,B,C;
		scanf("%d%d%d",&A,&B,&C);
		SumA+=A;
		SumB+=B;
		SumC+=C;

		int Tmp = min( min(SumA,SumB),SumC );
		if (Tmp<30) {puts("NO"); continue;}
		printf("%d\n", Tmp);
		SumA -= Tmp;
		SumB -= Tmp;
		SumC -= Tmp;


	}
	return 0;
}