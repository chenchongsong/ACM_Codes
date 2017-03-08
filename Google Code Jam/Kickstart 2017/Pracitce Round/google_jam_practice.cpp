#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
char name[110][30];
bool vis[110][30];
int cnt[110];
int num[110];

void Clear()
{
	memset(name, 0, sizeof(name));
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	memset(num, 0, sizeof(num));
}
int main()
{
	freopen("Desktop/Google Kickstart/A-small-practice.in","r",stdin);
    freopen("Desktop/Google Kickstart/ans.txt","w",stdout);
	int T;
	scanf("%d", &T);
	//printf("TTT == %d\n", T);
	for (int Case = 1; Case<=T; Case++)
	{
		Clear();
		int n;

		scanf("%d\n", &n);
		//printf("N== %d\n", n);
		for (int i=1;i<=n;i++)
		{
			gets(name[i]);
			int len = strlen(name[i]);

			for (int j=0; j<len; j++)
			{
				if (name[i][j]==' ') continue;
				vis[i][name[i][j]-'A'] = 1;
				num[i] |= (1<<(25-(name[i][j]-'A')));
				//printf("%d---%c\n", i,name[i][j]);

			}
			//first[i] = -100;
			for (int c=0; c<26; c++)
			{
				cnt[i] += vis[i][c];


			}
			


		}

		int Ans=1; //, Ans_cnt = cnt[1], Ans_num = num[1];
		for (int i=2; i<=n; i++)
		{
			//printf("%d %d ---- %d\n", 1, cnt[1], num[1]);
			//printf("%d %d ---- %d\n", i, cnt[i], num[i]);
			if (cnt[i]>cnt[Ans]) {Ans = i; continue;}
			if (cnt[i]<cnt[Ans]) {continue;}
			//puts("Here");
			if(num[i]>num[Ans]) 
			{
				Ans = i;
				//Ans_cnt
			}
		}
		/*int len = strlen( name[Ans] );
		for (int j=0;j< len; len++)
		{
			printf("%c");

		}*/
		printf("Case #%d: ", Case);puts(name[Ans]);
//puts("OK");
	}
	return 0;
}
/*

2
3
ADAM
BOB
JOHNSON
2
A AB C
XYZ

*/