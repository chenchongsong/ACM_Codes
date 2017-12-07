#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int opt, w, c;
struct flower {
	int w, c;
	flower(int ww, int cc){w=ww;c=cc;}
	bool operator < (const flower& rhs) const {
		return c < rhs.c;
	}
};
flower tmp = flower(0, 0);
vector<flower> tree;
int main() {
	tree.reserve(150000);
	
	// for (int i=1; i<=200000; i++) {
	// 	tree.insert(tree.begin(),{100, 200});
	// }
	// for (int i=1; i<=200000; i++)
	// 	tree.erase(tree.begin());
	
	while (scanf("%d", &opt)!=EOF && opt != -1) {
		switch(opt) {
			case 1:
				scanf("%d%d", &w, &c);
				tmp.w = w; tmp.c = c;
				if (upper_bound(tree.begin(),tree.end(),tmp)-lower_bound(tree.begin(),tree.end(),tmp))
					continue;
				tree.insert(upper_bound(tree.begin(),tree.end(),tmp), tmp);
				break;
			case 2:
				if (!tree.size()) continue;
				tree.erase(--tree.end());
				break;
			case 3:
				if (!tree.size()) continue;
				tree.erase(tree.begin());
				break;
		}
	}
	long long totw = 0, totc = 0;
	for (auto& i : tree) {
		totw += (long long) i.w;
		totc += (long long) i.c;
	}
	cout << totw << " " << totc << endl;
	return 0;
}