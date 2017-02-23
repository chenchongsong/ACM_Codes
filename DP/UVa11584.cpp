#include <cstdio>
#include <cstring>
#define MaxL 1010
using namespace std;
bool isPal[MaxL][MaxL];
int f[MaxL];
char s[MaxL];

int min(int a, int b){return a<b?a:b;}
void Clear()
{
	memset(isPal, 0, sizeof(isPal));
	memset(f, 0, sizeof(f));
}

int main()
{
	int T, l, r;
	scanf("%d", &T);
	while (T--)
	{
		Clear();
		scanf("%s", s+1);
		s[0] = 'x';
		int len = strlen(s) - 1;
		for (int i=1; i<=len; i++)
		{
			l = i; r = i; // odd_palindrome
			while (s[l] == s[r] && 1<=l && r<=len)
			{
				isPal[l][r] = 1;
				l--; r++;
			}

			l = i; r = i+1; // even_palindrome
			while (s[l] == s[r] && 1<=l && r<=len)
			{
				isPal[l][r] = 1;
				l--; r++;	
			}

		}
		for (int i=1;i<=len;i++)
		{
			f[i] = (int)1e8;
			for (int j=1;j<=i;j++)
				if (isPal[j][i])
					f[i] = min(f[i], f[j-1]+1);
		}
		printf("%d\n", f[len]);
	}
	return 0;
}