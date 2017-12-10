#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
#define maxn 1005
double PI=4.0*atan(1.0);
int x[maxn],y[maxn],n;
double pox[10],poy[10],vertxmax,vertymax,vertxmin,vertymin,para[2];
bool PNPoly(int u, int deg)
{
	if (!  (vertxmin <= x[u] <= vertxmax)  ||  ! ( vertymin <= y[u] <= vertymax ) )
        return 0;

    bool is_in = 0;
    int i,j;
    for(i=0;i<deg;i++)
    {
    	if(!i) j= deg-1;
    	else   j= i-1;

        if ( ((poy[i] > y[u]) != (poy[j] > y[u])) && (
                    x[u] < (pox[j] - pox[i]) * (y[u] - poy[i]) / (poy[j] - poy[i]) + pox[i]) )
            is_in = !is_in;
    }
      
    return is_in;
}

void judge(int deg)
{
	bool flag=0;
	int i,j;
	double xmax,xmin,mid,theta=2*PI/deg,xcos,xsin;
	double ans[3];
	xmax = 10000000;
	xmin = 0;
	xcos = cos(theta);
	xsin = sin(theta);
	int cnt=100;
	while(cnt--)// 下界
	{
		flag=1;
		mid = xmin+(xmax-xmin)/2;
		pox[0]= mid;
		poy[0]= 0;
		//printf("xmax %lf xmin %lf\n",xmax,xmin);
		vertxmax = vertxmin = mid;
		vertymax = vertymin = 0;

		for(i=1;i<deg;i++)
		{
			pox[i] = pox[i-1]*xcos - poy[i-1]*xsin;
			poy[i] = pox[i-1]*xsin + poy[i-1]*xcos;

			//printf("%lf, %lf\n",pox[i],poy[i]);

			vertymax = max(vertymax, poy[i]);
			vertymin = min(vertymin, poy[i]);
			vertxmin = max(vertxmin, poy[i]);

		}
		//printf("------------------\n");
		for(i=1;i<=n;i++)
		{
			if ( PNPoly(i,deg) )
			{
				xmax=mid;flag=0;
				break;
				
			}
		}
		if(flag)
			xmin=mid;
	}
	//printf("ans inside %lf\n",(xmin*xsin*xmin));
	para[0]=xmin*xmin*xsin;
	xmax = 10000000;
	xmin = 0;
	cnt=100;
	while(cnt--)//upper bound
	{
		flag=1;
		mid = xmin+(xmax-xmin)/2;
		pox[0]= mid;
		poy[0]= 0;

		vertxmax = vertxmin = mid;
		vertymax = vertymin = 0;


		for(i=1;i<deg;i++)
		{
			pox[i] = pox[i-1]*xcos - poy[i-1]*xsin;
			poy[i] = pox[i-1]*xsin + poy[i-1]*xcos;



			vertymax = max(vertymax, poy[i]);
			vertymin = min(vertymin, poy[i]);
			vertxmin = max(vertxmin, poy[i]);

		}
		for(i=1;i<=n;i++)
		{
			if ( !PNPoly(i,deg) )
			{
				xmin=mid;
				flag=0;
				break;
				
			}
		}
		if(flag)
			xmax=mid;

	}
	//printf("ans outside %lf\n",(xmin*xsin*xmin));
	para[1]=xmin*xmin*xsin;
	return;

}


int main()
{
	int i,j,deg=3;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	double ans[2],tmp;
	judge(3);
	ans[0]=para[0];
	ans[1]=para[1];
	for(i=4;i<=8;i++)
	{
		judge(i);
		//printf("%lf\n",tmp);
		if(para[0]*ans[1] > para[1]*ans[0])
		{	
			ans[0]=para[0];
			ans[1]=para[1];
			deg = i;
		}
	}
	printf("%d %.10lf\n",deg,ans[0]/ans[1]);

}