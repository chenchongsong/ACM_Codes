#include <iostream>
using namespace std;
typedef long long ll;
ll W, N, w, l, cur;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>W>>N;
	while(N--){
		cin>>w>>l;
		cur+=w*l;
	}
	cout<<cur/W<<endl;
	return 0;
}