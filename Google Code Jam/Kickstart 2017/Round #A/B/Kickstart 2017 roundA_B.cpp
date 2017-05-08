#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 30010
using namespace std;
//int f[maxn][maxn];
int cnt1, cnt2;
int a1[maxn], a2[maxn];
int num1[maxn], num2[maxn];
char s1[maxn], s2[maxn];
int len1, len2;

bool check()
{
	char tmp1[maxn], tmp2[maxn];
	int t1=0, t2=0;
	for (int i=1;i<=len1; i++)
	{
		if (s1[i]!='*') {tmp1[++t1]=s1[i];continue;}
		for (int j=1;j<=num1[i]; j++)
		{
			tmp1[++t1] = '*';
		}
	}

	for (int i=1;i<=len2; i++)
	{
		if (s2[i]!='*') {tmp2[++t2]=s2[i];continue;}
		for (int j=1;j<=num2[i]; j++)
		{
			tmp2[++t2] = '*';
		}
	}

	/*for (int i=1;i<=t1;i++)
		printf("%c ",tmp1[i]);
	puts("");
	for (int i=1;i<=t2;i++)
		printf("%c ",tmp2[i]);
	puts("");*/

	if (t1!=t2) return 0;

	for (int i=1;i<=t1; i++)
	{
		if (tmp1[i]!=tmp2[i] && tmp1[i]!='*' && tmp2[i]!='*') return 0;
	}
	return 1;


}

bool solve2(int x)
{
	if (x>cnt2) return check();
	for (int i=0;i<=4;i++)
	{
		num2[a2[x]] = i; if (solve2(x+1)) return 1;
	}
	return 0;
	
}

int solve1(int x)
{
	if (x>cnt1)
	{
		return solve2(1);
	}
	for (int i=0;i<=4;i++)
	{
		num1[a1[x]] = i;
		if (solve1(x+1)) return 1;
	}
	return 0;
}

int main()
{
	freopen("Desktop/Google Kickstart/C/B-small-attemp0.in","r",stdin);
    //freopen("Desktop/Google Kickstart/C/ans.txt","w",stdout);
	int T;
	scanf("%d", &T);
	//printf("%d", );
	for (int kase=1;kase<=T;kase++)
	{
		scanf("%s\n",s1);
		scanf("%s\n", s2);
		len1 = strlen(s1); //len1--;
		len2 = strlen(s2); //len2--;

		for (int i=len1;i>=1; i--)
			s1[i] = s1[i-1];
		for (int i=len2;i>=1; i--)
			s2[i] = s2[i-1];
		//memset(f, 0, sizeof(f));
		//f[0][0] = 1;
		cnt1 = cnt2 = 0;
		for (int i=1;i<=len1;i++)
		{
			if (s1[i]=='*') a1[++cnt1] = i;
			if (s2[i]=='*') a2[++cnt2] = i;
		}
		/*for (int i=1;i<=10;i++)
			printf("%d -- %d\n", a1[i], a2[i]);*/
		printf("Case #%d: ", kase);
		if (solve1(1)) printf("TRUE\n");
		else printf("FALSE\n");

	}
	return 0;
}