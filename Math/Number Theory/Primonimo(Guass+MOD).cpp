#include <cstdio>
#include <algorithm>
#include <cmath>
#define MaxN 500
using namespace std;
int N, Big, r, c;
int A[MaxN][MaxN], inittable[MaxN][MaxN];
int P;

int power(int a, int b, int mod) {
    int ret = 1;
    for (; b; b /= 2) {
      if (b % 2) ret = ret*a % mod;
      a = a*a % mod;
    }
    return ret;
}
// hzwer version
void EXGCD(int a,int b,int &x,int &y)
{
    if(b==0){x=1;y=0;return;}
    EXGCD(b,a%b,x,y);
    int t=x;x=y,y=t-a/b*y;
}
// int inv(int x, int mod) { return power(x, mod-2, mod); }
int inv(int A, int B) { // return a^(-1) (mod B)
	int X, Y;
	EXGCD(A, B, X, Y);
	return (X%B+B)%B;
}

int Node(int x, int y) {return x*c+y;}
void Init() {
	scanf("%d%d%d",&r, &c, &P);
	for (int i=0; i<r; i++)
		for (int j=0; j<c;j++) {
			scanf("%d", &inittable[i][j]);
			inittable[i][j]--;
		}
	N = r * c;
	for (int i=0; i<N; i++) { // each line of the equations
		int x = i/c;
		int y = i%c;
		for (int pos = 0; pos < r; pos++)
			A[i][Node(pos,y)] = 1;
		for (int pos = 0; pos < c; pos++)
			A[i][Node(x,pos)] = 1;
		A[i][r*c] = P-1-inittable[x][y];
	}
} 

int Ans[100000], tot = 0;
void Print() {
	// check
	for (int i=0; i<N; i++) {
		if (!A[i][N]) continue;
		for (int cnt=1; cnt<=A[i][N]; cnt++) Ans[++tot] = i+1;
		int x = i/c;
		int y = i%c;
		for (int pos=0; pos<r; pos++) inittable[pos][y] += A[i][N];
		for (int pos=0; pos<c; pos++) inittable[x][pos] += A[i][N];
		inittable[x][y] -= A[i][N];
	}
	bool flag = true;
	for (int i=0; i<r; i++)
		for (int j=0; j<c; j++)
			if (inittable[i][j]%P != P-1) {
				flag = false;
				break;
			}
	if (flag) {
		printf("%d\n", tot);
		for (int i=1; i<=tot; i++) printf("%d ", Ans[i]);
		// printf("%d\n", Ans[tot]);
	}
	else puts("-1");
}

void Gauss() {
	for (int i=0; i<N; i++) {
		int Big=i;
		for (int j=i+1;j<N;j++)
    		if (A[j][i]>A[Big][i])
				Big=j;
  		if (Big!=i)
  			for (int j=0;j<=N;j++)
    			swap(A[Big][j],A[i][j]);
 		for (int k = i+1; k<N; k++) {
 			int tmp = A[k][i] * inv(A[i][i], P);
    		for (int j=i; j<=N; j++) {
    			tmp %= P;
      			A[k][j] = ((A[k][j]-(tmp*A[i][j]))%P+P)%P;
      			A[k][j] += P*2;
      			A[k][j] %= P;
    		}
    	}
	}
	for (int i=N-1;i>=0;i--) {
    	for (int j=i+1;j<N;j++) {
    		int tmp = (A[j][N] * A[i][j]) % P;
			A[i][N] -= tmp;
			A[i][N] += P*2; A[i][N] %=P;
		}
    	A[i][N] = (A[i][N] * inv(A[i][i], P)) % P;
	}
}
int main()
{
	Init();
	Gauss();
	Print();
	return 0;
}


/*

2 11
3 4 3
4 3 2

*/

