#include <cstdio>
using namespace std;
int N,L;
int pos1[10010], pos2[10010], tmp[10010];

int main()
{
	scanf("%d%d", &N, &L);
	for (int i=1;i<=N;i++)
	{
		scanf("%d", &tmp[i]);
	}
	pos1[1] = (L-tmp[N])+tmp[1];
	for (int i=2;i<=N;i++)
		pos1[i] = tmp[i] - tmp[i-1];

	for (int i=1;i<=N;i++)
		scanf("%d", &tmp[i]);
	pos2[1] = (L-tmp[N])+tmp[1];
	for (int i=2;i<=N;i++)
		pos2[i] = tmp[i] - tmp[i-1];
//printf("pos1 %d %d %d\n",pos1[1], pos1[2], pos1[3]);


//printf("pos2 %d %d %d\n",pos2[1], pos2[2], pos2[3]);

	for (int off=0;off<N;off++)
	{
		for (int i=1;i<=N;i++)
		 	tmp[i] = pos1[(i+off)%N+1];
		
		int flag=1;
		for (int i=1;i<=N;i++)
			if (tmp[i]!=pos2[i])
			{flag=0;break;}
		if (flag) {puts("YES"); return 0;}
	}
	puts("NO");
	return 0;
}