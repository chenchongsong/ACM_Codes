typedef int Matrix[maxn][maxn];
void exgcd(int a, int b, int& d, int& x, int& y){
	!b?(d=a, x=1, y=0):(exgcd(b, a%b, d, y, x), y-=x*(a/b));
}
int inv(int a){
	int d, x, y;
	exgcd(a, MOD, d, x, y);
	return d==1?(x+MOD)%MOD:-1;
}
int gauss_jordan(Matrix A, int n, int m){//A是增广矩阵, n个未知数, m个方程, MOD是模, 如果MOD不是质数的话每次inv完先检测是否是-1
	int i=0, j=0;
	while(i<m&&j<n){
		int row=i;
		for(int k=i; k<m; k++){
			if(A[k][j]){
				row=k;
				break;
			}
		}
		if(row!=i) for(int k=0; k<=n; k++) swap(A[i][k], A[row][k]);
		if(!A[i][j]){
			j++;
			continue;
		}
		for(int k=0; k<m; k++){
			if(!A[k][j]||i==k) continue;
			int cur=A[k][j]*inv(A[i][j])%MOD;
			for(int t=j; t<=n; t++)
				A[k][t]=((A[k][t]-cur*A[i][t])%MOD+MOD)%MOD;
		}
		i++;
	}
	for(int k=i; k<m; k++) if(A[k][n]) return -1;//无解
	if(i<n) return 0;//无限解
	for(int k=0; k<n; k++)
		A[k][n]=A[k][n]*inv(A[k][k])%MOD;//解存在A[k][n]里面
	return 1;
}