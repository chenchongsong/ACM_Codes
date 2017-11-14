#include <cstdio>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn=10000007;
bool vis[maxn];
vector<ll> primes;

void init(){
	vis[0] = vis[1] = true;
	for (int i = 4; i < maxn; i += 2)
		vis[i] = true;
    primes.push_back(2);
    for(int i=3; i<maxn; i+=2){
        if(!vis[i])
            primes.push_back(ll(i));
        for (int p : primes) {
            if (p * i > maxn-1) break;
            vis[p * i] = true;
            if (i % p == 0) break;
        }
    }
}

int main() {
	init();
	int N, M;
	cin >> N >> M;
	for (int i=1; i<=M; i++) {
		int tmp;
		cin >> tmp;
		if (!vis[tmp]) puts("Yes");
		else puts("No");
	}
	return 0;
}

