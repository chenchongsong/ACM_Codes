#include <cstdio>
#include <cstdio>
using namespace std;
int a,b;
int main()
{
	//int a , b;
	scanf("%d%d", &a, &b);
	if (a==b && b==0)
		{puts("NO"); return 0;}
	if (a-b>1 || b-a>1)
		puts("NO");
	else
		puts("YES");
	return 0;
}