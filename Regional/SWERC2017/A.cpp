#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
struct item
{
	long long t;
	bool in;
};
map<long long,long long>s;
item q[5000];
bool cmp(item i1,item i2)
{
	if(i1.t<i2.t) return true;
	return false;
}
int main()
{
	int n,m,i,j,k,t,idx=0,diff,curmax,ans;
	item tmp;
	long long in[2005],out[2005];
	tmp.in=1;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		{
			cin>>tmp.t;
			q[idx++]=tmp;
		}
	tmp.in=0;
	for(i=1;i<=m;i++)
		{
			cin>>tmp.t;
			q[idx++]=tmp;
		}
	sort(q,q+idx,cmp);

	for(i=0;i<idx;i++)
	{
		if(!q[i].in)
			for(j=i-1;j>=0;j--)
			{
				if(q[j].in)
					{
						diff=q[i].t-q[j].t;
						s[diff]++;
					}
			}
	}
	curmax=0;ans=0;

	
	for(auto i:s)
	{
		if(i.second > curmax)
		{
			curmax = i.second;
			ans = i.first;
		}
	}
	cout<<ans<<endl;
}


/*
5
5
0 10 12 20 30
1 5 17 27 50
*/