#include <cstdio>
#include <vector>
#include <map>
using namespace std;
map<int, vector<int> > a;

int main() {
	int k, val, n, m;
	while (scanf("%d%d", &n, &m)==2) {
		
		for (int i=1; i<=n; i++) {
			scanf("%d", &val);
			if (a.count(val)==0) a[val] = vector<int>();
			a[val].push_back(i);
		}

		while (m--) {
			scanf("%d%d", &k, &val);
			if (a.count(val)==0 || a[val].size() < k)
				puts("0");
			else
				printf("%d\n", a[val][k-1]);
		}
	}
	return 0;
}

/*
8 4
1 3 2 2 4 3 2 1
1 3
2 4
3 2
4 2
*/