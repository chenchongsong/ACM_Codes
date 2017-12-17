#include <iostream>
using namespace std;
const int maxn=100000;
int n, t, a, b, c;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n;
		if(n<maxn-32){
			int cnt=0, i=0;
			while(1){
				puts("section 1");
				a=b=n^(1<<i);
				if(a==0 || a > maxn){
					i++;
					continue;
				}
				cout<<a<<endl;
				c=((a^n)+(b^n))^n;
				cout<<((a^n)+(b^n))<<endl;
				if(c==0 || c > maxn){
					i++;
					continue;
				}
				puts("OK");
				cout<<a<<' '<<b<<' '<<c<<endl;
				cnt++;
				if(cnt==5) break;
				i++;
			}
		}else{
			int cnt=0, i=0;
			while(1){
				puts("section 2");
				a=b=n-i;
				c=((a^n)+(b^n))^n;
				if(c>0&&c<=maxn){
					cout<<a<<' '<<b<<' '<<c<<endl;
					cnt++;
				}
				i++;
				if(cnt==5) break;
			}
		}
	}
	return 0;
}