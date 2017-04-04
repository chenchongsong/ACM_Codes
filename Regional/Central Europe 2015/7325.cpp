#include <cstring>
#include <cstdio>
#include <algorithm>
#define MaxL 500010
using namespace std;

char s[MaxL];
int size[MaxL];
int start[MaxL], ending[MaxL];
int cnt;

void Clear()
{
	cnt = 0;
	memset(size, 0, sizeof(size));
	memset(start,0, sizeof(start));
	memset(ending, 0, sizeof(ending));
}

int main()
{
	while ( (gets(s)) !=NULL) //gets遇到文件结尾标志时返回NULL
	{
		Clear();
		int A, B;
		scanf("%d%d", &A, &B);

		int len = strlen(s);
		cnt = 1;
		start[cnt] = 0;

		for (int i=0;i<len;i++)
		{
			if (s[i]==' ')
			{
				
				size[cnt] = i-start[cnt];
				ending[cnt] = start[cnt]+size[cnt]-1;
				start[++cnt] = i+1;
			}
		}
		size[cnt] = len - start[cnt];
		ending[cnt] = start[cnt] + size[cnt]-1;

		for (int m = A; m<=B; m++)
		{
			int Ans = size[1]+1, lead=1, next_pos;
			while (true)
			{
				next_pos = upper_bound(ending+1, ending+cnt+1, start[lead]+m-1)-ending;
				//printf("lead %d---key %d, ending %d next_pos %d\n", lead, start[lead]+m-1, ending[next_pos], next_pos);
				lead = next_pos;
				if (next_pos>cnt) break;
				Ans += (size[lead]+1);
			}
			printf("%d\n",Ans-1);
		}
		char c=getchar();
	}
	return 0;
}