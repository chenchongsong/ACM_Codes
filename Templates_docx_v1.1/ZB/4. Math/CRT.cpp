typedef long long ll;
//n个方程为x=a[i] (mod m[i])
ll china(int n, int* a, int* m){
	ll M=1, d, y, x=0;//M是等价以后的模
	for(int i=0; i<n; i++) M*=m[i];
	for(int i=0; i<n; i++){
		ll w=M/m[i];
		exgcd(m[i], w, d, d, y);
		x=(x+y*w*a[i])%M;
	}
	return (x+M)%M;
}
