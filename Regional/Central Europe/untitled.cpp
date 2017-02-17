#include <cstring>
#include <cstdio>
#include <algortihm>
#define MaxL 500010
using namespace std;

char s[MaxL];
int size[MaxL];
int start[MaxL], end[MaxL];
int cnt;

void Clear()
{
	cnt = 0;

}

int main()
{
	while (gets(s)!=EOF)
	{
		int Ans = 0, A, B;
		scanf("%d%d", &A, &B);

		len = strlen(s);
		cnt = 1;
		start[cnt] = 0;

		for (int i=0;i<len;i++)
		{
			if (s[i]==' ')
			{
				
				size[cnt] = i-[cnt];
				end[cnt] = start[cnt]+size[cnt]-1;
				start[++cnt] = i+1;
			}
		}
		size[cnt] = len - start[cnt];
		end[cnt] = start[cnt] + size[cnt]-1;
		//pos[cnt+1] = len+1;



		int offset = 0;
		for (int m = A; M<=B; m++)
		{
			int next, lead, curpos;
			while ()
			{
				Ans += size[lead];
				cur_pos = start[lead];
				//next_pos = 




				next_pos = upper_bound(end+1, end+cnt+1, start[lead]+m-1);
				lead = next_pos;
			}

		}
		printf("%d\n",Ans);

	}
	return 0;
}