#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn=(1<<8)+1;
const ll MOD=1000000000;
struct parameter{int c, r;};
struct Matrix{
	ll matrix[maxn][maxn];
	parameter DIM;
	Matrix(){}
	Matrix(int c, int r){
		DIM={c, r};
		memset(matrix, 0, sizeof(matrix));
	}
	Matrix operator * (Matrix& A){
		Matrix C(DIM.c, A.DIM.r);
		memset(C.matrix, 0, sizeof(C.matrix));
		for(int i=0; i<DIM.c; i++)
			for(int j=0; j<A.DIM.r; j++)
				for(int k=0; k<DIM.r; k++)
					C.matrix[i][j]=(C.matrix[i][j]+A.matrix[i][k]*matrix[k][j])%MOD;
		return C;
	}
	void print(){
		for(int i=0; i<DIM.c; i++){
			for(int j=0; j<DIM.r; j++)
				cout<<matrix[i][j]<<'\t';
			cout<<endl;
		}
	}
};
Matrix BigMatrixExpo(Matrix& A, ll n){
	//cout<<n<<endl;
	Matrix B=A;
	Matrix C(A.DIM.c, A.DIM.r);
	for(int i=0; i<C.DIM.c; i++)
		for(int j=0; j<C.DIM.r; j++)
			C.matrix[i][j]=(i==j);
	//C.print();
	while(n){
		//cout<<n<<endl;
		if(n&1){
			C=C*B;
			//C.print();
		}
		B=B*B;
		//B.print();
		n>>=1;
	}
	//cout<<"------------------------"<<endl;
	//C.print();
	return C;
}
ll N, M, ts;
int main(){
	cin>>N>>M;
	ts=1<<N;
	Matrix dp(ts, ts);
	for(int i=0; i<ts; i++){
		for(int j=0; j<ts; j++){
			if(!j){
				dp.matrix[i][j]=1;
				continue;
			}
			if(!(j&1)){
				dp.matrix[i][j]=dp.matrix[i>>1][j>>1];
				continue;
			}
			if((j&3)==1){
				if(i&1) dp.matrix[i][j]=0;
				else dp.matrix[i][j]=dp.matrix[i>>2][j>>2];
				continue;
			}
			if(i&1) dp.matrix[i][j]=dp.matrix[i>>2][j>>2];
			else dp.matrix[i][j]=dp.matrix[i>>2][j>>2]+dp.matrix[i>>1][j>>1];
		}
	}
	//dp.print();
	//cout<<"----------------------"<<endl;
	dp=BigMatrixExpo(dp, M);
	ll res=0;
	for(int i=0; i<ts; i++)
		res=(res+dp.matrix[ts-1][i])%MOD;
	cout<<res<<endl;
	return 0;
}
/*
2 2
1	1	1	2	
1	0	1	1	
1	1	0	1	
1	0	0	1	
----------------------
1	0	0	0	
0	1	0	0	
0	0	1	0	
0	0	0	1	
2
5	2	2	6	
3	2	1	4	
3	1	2	4	
2	1	1	3	
1
5	2	2	6	
3	2	1	4	
3	1	2	4	
2	1	1	3	
49	22	22	64	
32	15	14	42	
32	14	15	42	
22	10	10	29	
------------------------
5	2	2	6	
3	2	1	4	
3	1	2	4	
2	1	1	3	
5
*/