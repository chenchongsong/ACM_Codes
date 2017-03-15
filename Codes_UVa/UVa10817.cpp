#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
int S, M, N;
int f[110][50000];
char str[100];
int init[110], cost[110], ability[110];
vector <vector<int> > states;
map <vector<int>, int> ID;

void Clear() {
	memset(init, 0, sizeof(init));
	memset(ability, 0, sizeof(ability));
	memset(f, 63, sizeof(f));
	states.clear();
	ID.clear();
}
void build(int course, vector<int>& state) {
	if (course == S) {
		ID[state] = states.size();
		states.push_back(state);
	}
	else for (int i=init[course]; i<=2; i++) {
		state[course] = i;
		build(course+1, state);
	}
}
void DP() {
	f[0][0] = 0;
	for (int i=0; i<N; i++) {
		for (int index_cur = 0; index_cur<states.size(); index_cur++) {
			vector<int> cur = states[index_cur];
			f[i+1][ID[cur]] = min(f[i+1][ID[cur]], f[i][ID[cur]]);

			vector<int> next = cur;
			for (int pos=0; pos<S; pos++)
				if (ability[i] & (1<<pos) && next[pos]<2)
					next[pos]++;
			f[i+1][ID[next]] = min(f[i+1][ID[next]], f[i][ID[cur]]+cost[i]);	
		}
	}
}

int main()
{
	while (scanf("%d%d%d", &S, &M, &N) && (S||M||N)) {
		Clear();
		int init_cost = 0;
		for (int i=0; i<M; i++) {
			int tmp;
			scanf("%d", &tmp);
			init_cost += tmp;

			gets(str);
			int len = strlen(str);
			for (int j=0; j<len; j++)
				if (isdigit(str[j]) && init[str[j]-'0'-1]<2)
					init[str[j]-'0'-1]++;
		}
		vector<int> state(S);
		build(0, state);

		for (int i=0; i<N; i++) {
			scanf("%d", &cost[i]);

			gets(str);
			int len = strlen(str);
			for (int j=0; j<len; j++)
				if (isdigit(str[j]))
					ability[i] |= (1<<(str[j]-'0'-1)); 
		}
		DP();
		printf("%d\n", init_cost + f[N][states.size()-1]);
	}
	return 0;
}

/*
4 2 3
1 1 2
10 2 3
100000 4 2
200000 4 2 1 3
300000 4 3
*/