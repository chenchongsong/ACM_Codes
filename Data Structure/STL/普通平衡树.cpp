#include <vector>
#include <cstdio>
#include <algorithm>
#define maxn 200005
using namespace std;

int n;
vector<int> tree;
int FIND(int x) {
    return lower_bound(tree.begin(),tree.end(),x)-tree.begin()+1;
}
int main() {
	scanf("%d", &n);
	tree.reserve(maxn);
	int opt, x;
	for (int i=1; i<=n; i++) {
		scanf("%d%d", &opt, &x);
		switch(opt) {
			case 1:tree.insert(upper_bound(tree.begin(),tree.end(),x),x);break;
            case 2:tree.erase(lower_bound(tree.begin(),tree.end(),x));break;
            case 3:printf("%d\n",FIND(x));break;
            case 4:printf("%d\n",tree[x-1]);break;
            case 5:printf("%d\n",*--lower_bound(tree.begin(),tree.end(),x));break;
            case 6:printf("%d\n",*upper_bound(tree.begin(),tree.end(),x));break;
		}
	}
}
