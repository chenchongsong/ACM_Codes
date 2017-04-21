#include <cstdio>
#include <cmath>
using namespace std;
int main() {
	long long n;
	while (scanf("%lld", &n)==1 && n!=0) {
		long long root = (long long) sqrt(n);
		if (root * root == n) {puts("yes");continue;}
		if ((root+1) * (root+1) == n){puts("yes");continue;}
		if ((root-1) * (root-1) == n){puts("yes");continue;}
		puts("no");
	}
	return 0;
}