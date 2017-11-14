

const int maxn=10000007;
bool vis[maxn];
vector<int> primes;

void init(){
	// vis[0] = vis[1] = true;
	// for (int i = 4; i < maxn; i += 2)
	// 	vis[i] = true;
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
