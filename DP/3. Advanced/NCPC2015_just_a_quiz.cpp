// DP 好难De…
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int T, N;
double dp[110];
// double pb_t[110]; // max expected score after hearing t seconds and give an answer
int sz = 0;     // trie node indexed from 0 to sz
map<string, int> trie[100010];
map<string, int> cnt[100010]; // count how many answer corresponding to this string under this subtree
int tot_answer[100010]; // count how many answer under this substree
double pb_node[100010]; // max prob of be correct, if answer directly when coming to this node

void buildTrie() {
	int u = 0;
	bool mark = 0;
	vector<int> ancestors(1);

	string s, ans_str;
	while (true) {
		cin >> s;
		
		if (!trie[u][s]) {
			++sz;
			trie[u][s] = sz;
		}
		u = trie[u][s];
		ancestors.push_back(u);

		if (s[s.size()-1] == '?') {

			cin >> ans_str;
			break;
		}
	}
	for (int index = 0; index < ancestors.size(); index++) {
		cnt[ancestors[index]][ans_str] = cnt[ancestors[index]][ans_str]+1;
		tot_answer[ancestors[index]]++;
	}
}

double dfs(int node, int prev, int time_left) { // prev == time_left - 1
	if (time_left == 0) return 0;
	double now = pb_node[node] + dp[prev]; // answer now and move to the next question
	double move = 0;
	
	for (map<string, int>::iterator it=trie[node].begin(); it!=trie[node].end(); it++)
		// listen to another word
		move += dfs(it->second, prev - 1, time_left - 1) * tot_answer[it->second];

	return max(now, move / tot_answer[node]);
}

int main() {
	cin >> T >> N;
	for (int ques = 1; ques <= N; ques++)
		buildTrie();

	queue<int> Q;
	Q.push(0);
	int cnt_uncertain = N;

	for (int i = 0; i<=sz; i++) {
        int s = 0, ma = 0; // sum, max_ans
        for (map<string, int>::iterator it=cnt[i].begin(); it!=cnt[i].end(); it++) {
            s += it->second;
            ma = max(ma, it->second);
        }
        pb_node[i] = ma / double(s);
        tot_answer[i] = s;
    }

	for (int i = 1; i <= T; i++)
        dp[i] = dfs(0, i - 1, i);

	printf("%.10lf\n", dp[T]);

	return 0;
}