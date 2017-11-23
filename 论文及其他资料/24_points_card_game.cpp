#include <cstdio>
//#include <algorithm>
#include <cmath>
using namespace std;
double a[100];
double b[100];
char c[100] = {'0', '+', '-', '*', '/'};
double abs(double a) {return a>0?a:-a;}

void work()
{
	double cnt=0;
	cnt = b[1];

	for (int i=1;i<=4;i++)
	{
		if (i==1) cnt+=b[2];
		if (i==2) cnt-=b[2];
		if (i==3) cnt*=b[2];
		if (i==4) cnt/=b[2];
		for (int j=1;j<=4;j++)
		{
			if (j==1) cnt+=b[3];
			if (j==2) cnt-=b[3];
			if (j==3) cnt*=b[3];
			if (j==4) cnt/=b[3];

			for (int k=1;k<=4;k++)
			{
				if (k==1) cnt+=b[4];
				if (k==2) cnt-=b[4];
				if (k==3) cnt*=b[4];
				if (k==4) cnt/=b[4];

				if (fabs(cnt - 24.0) < 1e-6)
				{
					printf("( (%.0lf%c%.0lf)%c %.0lf) %c %.0lf\n\n", 
						b[1],c[i],b[2],c[j],b[3],c[k],b[4]);
					printf("cnt=== %.0lf\n", cnt);
				}
				if (k==1) cnt-=b[4];
				if (k==2) cnt+=b[4];
				if (k==3) cnt/=b[4];
				if (k==4) cnt*=b[4];


			}
			if (j==1) cnt-=b[3];
			if (j==2) cnt+=b[3];
			if (j==3) cnt/=b[3];
			if (j==4) cnt*=b[3];
		}
		if (i==1) cnt-=b[2];
		if (i==2) cnt+=b[2];
		if (i==3) cnt/=b[2];
		if (i==4) cnt*=b[2];
	}	
}

void work2()
{
	double cnt1 = 0, cnt2 = 0;
	cnt1 = b[1];
	cnt2 = b[3];
	for (int i=1;i<=4;i++)
	{
		if (i==1) cnt1+=b[2];
		if (i==2) cnt1-=b[2];
		if (i==3) cnt1*=b[2];
		if (i==4) cnt1/=b[2];
		for (int j=1;j<=4;j++)
		{
			if (j==1) cnt2+=b[4];
			if (j==2) cnt2-=b[4];
			if (j==3) cnt2*=b[4];
			if (j==4) cnt2/=b[4];
			for (int k=1;k<=4;k++)
			{
				if (k==1) cnt1+=cnt2;
				if (k==2) cnt1-=cnt2;
				if (k==3) cnt1*=cnt2;
				if (k==4) cnt1/=cnt2;

				if (fabs(cnt1 - 24.0) < 1e-6)
				{
					printf("(%.0lf %c %.0lf) %c (%.0lf %c %.0lf)\n\n", 
						b[1],c[i],b[2],c[k],b[3],c[j],b[4]);
					printf("cnt=== %.0lf\n", cnt1);
				}
				if (k==1) cnt1-=cnt2;
				if (k==2) cnt1+=cnt2;
				if (k==3) cnt1/=cnt2;
				if (k==4) cnt1*=cnt2;
			}
			if (j==1) cnt2-=b[4];
			if (j==2) cnt2+=b[4];
			if (j==3) cnt2/=b[4];
			if (j==4) cnt2*=b[4];
		}
		if (i==1) cnt1-=b[2];
		if (i==2) cnt1+=b[2];
		if (i==3) cnt1/=b[2];
		if (i==4) cnt1*=b[2];
	}	
}




int main()
{
	scanf("%lf%lf%lf%lf", &a[1], &a[2], &a[3], &a[4]);
	for (int i=1;i<=4;i++)
	{
		for (int j=1;j<=4;j++)
		{
			if (j==i) continue;
			for (int k=1;k<=4;k++)
			{
				if (k==i || k==j) continue;
				for (int l=1;l<=4;l++)
				{
					if (l==i || l==j||l==k) continue;
					b[1]=a[i]; b[2]=a[j];
					b[3]=a[k]; b[4]=a[l];
					work();
					work2();
				}
			}
		}
	}
	return 0;

}