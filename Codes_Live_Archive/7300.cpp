#include <cstdio>
#include <cstring>
#define MaxN 1010
using namespace std;
char s[MaxN];
int l;

int main()
{
	while (scanf("%s",s)!=EOF)
	{
		l = strlen(s);
		char c;
		for (int i=0;i<l;i++)
		{
			if ('0'<= s[i] && s[i]<= '9')
				s[i] -= '0';
			if ('A' <= s[i] && s[i]<= 'F')
				s[i] = s[i]-'A'+10;

		}

		for (int i=0;i<l;i+=2)
			printf("%c", s[i]*16+s[i+1]);
		puts("");


	}
}