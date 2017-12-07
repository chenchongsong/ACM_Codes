ll a[maxn];
/*
连分数逼近由欧几里德算法求解
n/d=a[0]+1/(a[1]+1/(a[2]+1/(a[3]+1/(...+1/a[len-1]))))
*/
int cont_frac(ll n, ll d){
	ll r;
	int len=0;
	while(d){
		a[len++]=n/d;
		r=n%d; n=d; d=r;
	}
	return len;
}
