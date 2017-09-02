#include <cstdio>
#include <cstring>
using namespace std;
char s[2000010];
bool pd[2000010];
int cnt = 0;

int main() {
	memset(pd, 0, sizeof(pd));
	scanf("%s", s); //s[0] = 'x';
	int LEN = strlen(s);
	//printf("%d\n\n", LEN);
	
	for (int i=LEN-1; i>=0; i--) {
		//printf("%d ---- %c\n", i, s[i]);
		if (s[i] == '<') {
			cnt++;
			pd[i] = 1;
			continue;
		}
		if (cnt) {
			pd[i] = 1;
			cnt--;
		}

	}
	for (int i=0; i< LEN; i++) {
		if (pd[i] == 0)
			printf("%c", s[i]);
	}
	puts("");
	return 0;
	
}