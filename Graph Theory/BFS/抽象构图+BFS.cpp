#include <cstdio>
// Problem Distinctive Character
// code time: 15 mins
// Source: Nordic Dollegiate Progamming Contest 2017
// Author: Chen Chongsong
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#define maxnode 1<<22
using namespace std;
int n, k;
int dis[maxnode], vis[maxnode];
string s;
queue<int> q;

int main() {
	cin >> n >> k;
	for (int i=1; i<=n; i++) {
		cin >> s;
		int tmp = 0;
		for (int j=0; j<s.size(); j++)
			tmp = tmp*2 + s[j]-'0';
		q.push(tmp);
		vis[tmp] = 1;
		dis[tmp] = 0;
	}
	while (!q.empty()) {
		int qhead = q.front();
		q.pop();
		for (int i=0; i<k; i++) {
			int next = qhead ^ (1<<i);
			if (!vis[next]) {
				vis[next] = 1;
				dis[next] = dis[qhead] + 1;
				q.push(next);
			}
		}
	}

	int maxdis = 0, ans = 0;
	for (int i=0; i<(1<<k); i++) {
		if (dis[i] >= maxdis) {
			maxdis = dis[i];
			ans = i;
		}
	}
	// puts("OK");
	for (int i=k-1; i>=0; i--) {
		if (ans & (1<<i))
			printf("1");
		else
			printf("0");
	}
	puts("");
	return 0;
}