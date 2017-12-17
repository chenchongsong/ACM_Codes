#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
int main()
{
	bool hascour=0;
	int n,m,i,j,k;
	int b[2005][3],c[2005][3],r[3];
	int dis[2005],tmp,vis[2005];
	memset(vis,0,sizeof(vis));
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&b[i][1],&b[i][2]);
		q.push(i);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&c[i][1],&c[i][2]);
	}
	scanf("%d%d",&r[1],&r[2]);
	while(!q.empty())
	{
		i = q.top();
		q.pop();
		dis[i]=abs(r[1]-b[i][1])+abs(r[2]-b[i][2]);
		//ini distance

		for(j=1;j<=m;j++)//贪心
		{
			tmp=abs(c[j][1]-b[i][1])+abs(c[j][2]-b[i][2]);
			if(!vis[j])//没人
			{
				if(tmp < dis[i])//更近
				{
					vis[j] = i;//courier j 运送 i 瓶子
					dis[i] = tmp;
				}
			}
			else if( tmp < dis[ vis[j] ]  )//送这个瓶子更好
			{
				q.push(vis[j]);
				dis[ vis[j] ] = abs(b[vis[j]][1]-r[1])+abs(b[vis[j]][2]-r[2]);

				vis[j] = i;
				dis[i] = tmp;
			}
		}
	}


}