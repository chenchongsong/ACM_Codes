#include <iostream>
#include <stack>
using namespace std;
const int maxn=2123;
typedef long long ll;
typedef pair<ll, ll> pii;
bool table[maxn][maxn];
ll h[maxn], X, Y, N, D, cnt[maxn][maxn];
stack<pii> s;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>X>>Y>>N>>D;
	while(N--){
		int xl, xr, yl, yr;
		cin>>xl>>xr>>yl>>yr;
		for(int i=xl; i<xr; i++)
			for(int j=yl; j<yr; j++)
				table[i][j]=true;
	}
	for(int i=0; i<X; i++)
		table[i][Y]=true;
	for(int i=0; i<X; i++){
		stack<pii> tmp;
		swap(s, tmp);
		for(int j=0; j<=Y; j++){
			h[j]=table[i][j]?0:h[j]+1;
			int y=j;
			while(!s.empty()&&s.top().first>=h[j]){
				cnt[s.top().first][j-y]--;
				y=s.top().second;
				cnt[s.top().first][j-y]++;
				s.pop();
			}
			cnt[h[j]][j-y]--;
			s.push(make_pair(h[j], y));
		}
	}
	for(int i=X; i>=0; i--){
		for(int j=Y-1; j>=0; j--)
			cnt[i][j]+=cnt[i][j+1];
		for(int j=Y-1; j>=0; j--)
			cnt[i][j]+=cnt[i][j+1];
	}
	for(int i=X-1; i>=0; i--)
		for(int j=Y; j>=0; j--)
			cnt[i][j]+=cnt[i+1][j];
	while(D--){
		int x, y;
		cin>>x>>y;
		cout<<cnt[x][y]<<endl;
	}
	return 0;
}