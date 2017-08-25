#include <cstdio>
#include <cstring>
using namespace std;
int sg[100000];
int vis[100000];
int main() {
	sg[1] = 0;
	sg[2] = 1;

	printf("sg[1] == 0\n");
	printf("sg[2] == 1\n");


	for (int i=3; i<= 100; i++) {
		memset(vis,0 , sizeof(vis));
		for (int j = (i+1)/2; j < i; j++) {
			vis[sg[j]] = 1;
		}

		int j = 0;
		while (vis[j]) {
			j++;
		}
		sg[i] = j;

		printf("sg[%d] == %d\n", i, sg[i]);

	}
	return 0;
}