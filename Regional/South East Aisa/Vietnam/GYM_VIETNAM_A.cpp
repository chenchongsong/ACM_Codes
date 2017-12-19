#include<cstdio>
using namespace std;

int N,W,T,p[1010];

int Tmp=0,MAX=0;

int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&N, &W);		
		Tmp=0;
		MAX = 0;
		for (int i=1;i<=N;i++)
		{
			scanf("%d",&p[i]);
			for (int j=1;j<i;j++)
			{

				Tmp = (int)(W/p[j])*(int)(p[i]-p[j]);

				if (Tmp>MAX)
					MAX = Tmp;
			}
		}
		printf("%d\n",MAX);
	}
	return 0;
}