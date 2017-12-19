#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=511;
const int maxc=12345;
struct SW{
	int ind, d, s, tot, rls;
	bool operator < (const SW& rhs) const{
		return rls>rhs.rls;
	}
}sw[maxn];
int dp[maxn][maxc], q[maxn], f[maxn][maxc], w[maxn][maxc], cnt, mmax, n, c;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>n>>c;
	for(int i=1; i<=n; i++){
		cin>>sw[i].d>>sw[i].s;
		sw[i].ind=i;
		sw[i].tot=max(sw[i].d, sw[i].s);
		sw[i].rls=sw[i].tot-sw[i].s;
	}
	sort(sw+1, sw+n+1);
	for(int i=0; i<=n; i++)
		for(int j=0; j<=c; j++)
			dp[i][j]=-c;
	dp[0][c]=0;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=c; j++){
			dp[i][j]=dp[i-1][j];
			f[i][j]=j;
			w[i][j]=0;
		}
		for(int j=0; j<=c; j++){
			if(dp[i][j]>=0&&j>=sw[i].tot){
				if(dp[i-1][j]+1>dp[i][j-sw[i].s]){
					dp[i][j-sw[i].s]=dp[i-1][j]+1;
					f[i][j-sw[i].s]=j;
					w[i][j-sw[i].s]=sw[i].ind;
				}
			}
		}
	}
	for(int i=0; i<=c; i++)
		if(dp[n][i]>dp[n][mmax]) mmax=i;
	cout<<dp[n][mmax]<<endl;
	for(int i=n; i>0; i--){
		if(w[i][mmax]) q[++cnt]=w[i][mmax];
		mmax=f[i][mmax];
	}
	for(int i=cnt; i>0; i--)
		cout<<q[i]<<' ';
	cout<<endl;
	return 0;
}