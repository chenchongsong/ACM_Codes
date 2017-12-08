//完全积性函数 mo[i*j]=mo[i]*mo[j]
//sum(mo[d] for d|n)=(n==1)
//反演公式
//若f(n)=sum(g(d) for d|n) 则 g(n)=sum(mo[n/d]*f(d) for d|n)=sum(mo[d]*f(n/d) for d|n)
//If f(i)=sum(g(d*i) for d from 1 to floor(n/i)) then g(i)=sum(f(d*i)*mo[d] for d from 1 to floor(n/i))
typedef long long ll;
bool vis[maxn+123];
int mo[maxn+123], primes[maxn+123], a[maxn+123], pcnt, N;
void mobius(){//预处理
	mo[1]=1;
	for(int i=2; i<=maxn; i++){
		if(!vis[i]){
			mo[i]=-1;
			primes[pcnt++]=i;
		}
		for(int j=0; j<pcnt&&ll(i)*primes[j]<=maxn; j++){
			vis[i*primes[j]]=true;
			if(i%primes[j]) mo[i*primes[j]]=-mo[i];
			else{
				mo[i*primes[j]]=false;
				break;
			}
		}
	}
	for(int i=2; i<=maxn; i++) mo[i]+=mo[i-1];//mo记录前缀和
}
//O(sqrt(n)+sqrt(m))
ll cnt_gcd(ll n, ll m, ll k){//for i from 1 to n for j from 1 to m cnt gcd(i, j)=k
	if(n>m) swap(n, m);
	ll res=0;
	n/=k, m/=k;
	for(int i=1, j=1; i<=n; i=j+1){
		j=min(n/(n/i), m/(m/i));
		res+=ll(mo[j]-mo[i-1])*(n/i)*(m/i);//前缀和Mobius
	}
	return res;
}