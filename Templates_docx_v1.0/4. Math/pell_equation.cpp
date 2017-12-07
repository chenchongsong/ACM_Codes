//用于求解标准型Pell方程的第(k+1)组非平凡解 (x^2-n*y^2=1)
//输入n, k和MOD
//递推关系为 x[i+1]=x[0]*x[i]+n*y[0]*y[i];
//y[i+1]=y[0]*x[i]+x[0]*y[i];
//上述递推关系可由sqrt(n)的连分数表示推出
typedef long long ll;
typedef pair<ll, ll> pii;
pii res;//(xk, yk)
ll MOD;//模<必须是全局变量>
void Find(ll n, ll& x, ll& y){//暴力寻找特解(x0, y0)
	y=1;
	while(true){
		x=sqrt(y*y*n+1);
		if(x*x-n*y*y==1) break;
		y++;
	}
}
struct parameter{int c, r;};
struct Matrix{
    ll matrix[maxn][maxn];
    parameter DIM;
    Matrix(){}
    Matrix(int c, int r);
    Matrix operator*(Matrix &A);//带模乘法
    Matrix operator+(Matrix &A);
    void print();
};
Matrix BigMatrixExpo(Matrix &A, ll n);//带模快速幂
bool Pell(ll n, ll k){//k为第k组解, 从0开始数
	ll t=sqrt(n)+0.5, x, y;
	if(t*t==n) return false;//仅有平凡解 (1, 0) 和 (-1, 0)
	Matrix A(2, 2);
	Find(n, x, y);
	A.matrix[0][0]=A.matrix[1][1]=x;
	A.matrix[0][1]=n*y;
	A.matrix[1][0]=y;
	A=BigMatrixExpo(A, k-1);
	res=make_pair((A.matrix[0][0]*x+A.matrix[0][1]*y)%MOD, (A.matrix[1][0]*x+A.matrix[1][1]*y)%MOD);
	return true;
}
