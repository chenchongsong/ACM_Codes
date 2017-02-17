#include <cstdio>
using namespace std;
int main()
{
	int N;
	int a[100];
	scanf("%d",&N);
	for (int i=1;i<=N;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("%d\n",a[0]);
	return 0;
}