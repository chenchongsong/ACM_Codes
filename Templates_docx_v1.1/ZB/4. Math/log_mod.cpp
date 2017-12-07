//解方程a^x=b (mod n) n为素数
int shank(int a, int b, int n){
	int m, v, e=1, i;
	m=int(sqrt(n+0.5));//复杂度为O((m+n/m)logm) 所以m==n/m时最快
	v=inv(fast_pow(a, m, n), n);//fast_pow(a, m, n)=(a^m)%n
	map<int, int> x;//x[j]=min(i|e[i]==j)
	x[1]=0;
	for(int i=1; i<m; i++){
		e=a*e%n;//e=(a^i)%n
		if(!x.count(e)) x[e]=i;
	}
	for(int i=0; i<m; i++){//a^(im)到a^(im+m-1)
		if(x.count(b)) return i*m+x[b];
		b=b*v%n;//递推更新b
	}
	return -1;//无解
}
