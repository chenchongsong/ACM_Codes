#include <cstdio>
using namespace std;
long long n, k, i, j;

long long cal(long x, long long y)
{
	return (k/x) * ((x+y)*(y-x+1)/2);
}

int main() {
	scanf("%lld%lld", &n, &k);
	long long ans1 = n*k;
	long long ans2 = 0;

	for (i = 1; i<=n; i = j+1)
	{
		if (k/i == 0) break;
		ans2 += cal(i, j = k/(k/i));

		//printf("i--%lld j--%lld, ans2== %lld\n", i,j,ans2);
	}
	printf("%lld\n", ans1-ans2);
	return 0;
}