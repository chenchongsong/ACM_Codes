typedef long long ll;
ll fast_pow(ll x, ll k, ll p);
int Combination(int m, int n, int p){
	ll nom=1, den=1;
	for(int i=m-n+1; i<=m; i++){
		nom*=i;
		nom%=p;
	}
	for(int i=2; i<=n; i++){
		den*=i;
		den%=p;
	}
	den=fast_pow(den, p-2, p);
	return (nom*den)%p;
}
ll C[maxn][maxn];
int Combination_table(int n, ll MOD){
	memset(C, 0, sizeof(C));
	C[0][0]=1;
	for(int i=1; i<=n; i++){
		C[i][0]=1;
		for(int j=1; j<=i; j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
}