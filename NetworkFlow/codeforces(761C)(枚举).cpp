#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int map[110][110];
int pos[110][4];
int  N, M, Ans = 0;
char s[110];

int Dis(int x){return min(x-1, M-x+1);}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=1;i<=N;i++)
	{
		scanf("%s", s+1);
		for (int j=1;j<=M;j++)
		{
			if ('0'<=s[j] && s[j]<='9')
			{
				map[i][j] = 1;
				continue;
			}
			if ('a'<=s[j] && s[j]<='z')
			{
				map[i][j] = 2;
				continue;
			}
			map[i][j] = 3;
		}
		
		pos[i][1] = pos[i][2] = pos[i][3] = 1e8;
		for (int j=1;j<=M;j++)
			pos[i][map[i][j]] = min(pos[i][map[i][j]],Dis(j));
	}
	Ans = 1e8;
	for (int i=1;i<=N;i++) //digit
		for (int j=1;j<=N;j++) //letter
		{
			if (i==j) continue;
			for (int k=1;k<=N;k++) //char
			{
				if (k==i || k==j) continue;
				Ans = min(Ans, pos[i][1]+pos[j][2]+pos[k][3]);
			}
		}
	printf("%d\n", Ans);
	return 0;
}