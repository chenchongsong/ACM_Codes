#include <iostream>
using namespace std;
typedef long long ll;
int n;
ll a, b, c, d;
inline ll f(ll a, ll b, ll c){
	return a*a+b*b+c*c+7*c;
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>n;
	while(n--){
		cin>>a>>b>>c>>d;
		if(a<b) swap(a, b);
		if(a<c) swap(a, c);
		if(b<c) swap(b, c);
		ll f1=f(a+d, b, c), f2=0, f3=0, f4=0;
		if(b-c>=d) f2=f(a, b, c+d);
		else{
			d-=(b-c);
			if((d&1)&&d<=2*(a-b)) f3=f(a, b+d/2+1, b+d/2);
			else if(d<=2*(a-b)) f3=f(a, b+d/2, b+d/2);
			else{
				ll tmp=a+2*b+d;
				if(d%3==0){
					f3=f(tmp/3, tmp/3, tmp/3);
				}else if(d%3==1){
					f3=f(tmp/3+1, tmp/3, tmp/3);
				}else f3=f(tmp/3+1, tmp/3+1, tmp/3);
			}
			f4=f(a+d, b, b);
		}
		cout<<max(max(f1, f2), max(f3, f4))<<endl;
	}
	return 0;
}