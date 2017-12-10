#include<cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n<=3)
		printf("1\n");
	else
		printf("%d\n",n-2);
}