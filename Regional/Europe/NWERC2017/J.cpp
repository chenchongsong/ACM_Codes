#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int maxn=1123456;
int n;
char res[maxn];
set<int> s;
int main(){
	scanf("%s", res+1);
	n=strlen(res+1);
	s.insert(0);
	s.insert(n+1);
	for(int i=1; i<=n; i++)
		if(res[i]=='0') s.insert(i);
	for(int i=1; i<=n; i++){
		if(res[i]=='2'){
			auto l=s.lower_bound(i);
			auto r=l--;
			int ins=(*l)+(*r)-i;
			if((*l)>0) s.erase(*l);
			if((*r)<n+1) s.erase(*r);
			s.insert(ins);
		}
	}
	for(int i=1; i<=n; i++)
		res[i]='1';
	for(int ind:s)
		res[ind]='0';
	res[n+1]='\0';
	puts(res+1);
	return 0;
}