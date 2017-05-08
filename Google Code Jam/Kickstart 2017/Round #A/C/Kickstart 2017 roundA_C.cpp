#include <cstdio>
#include <algorithm>
using namespace std;
struct pp{
	int x,y,z;
} a[100000];
int toty[100000];
int totx[100000];
int cntx, cnty;
int n;

bool cmpz (pp A, pp B)
{return A.z<B.z || (A.z==B.z && A.x<B.x) || (A.z==B.z&&A.x==B.x&&A.y<B.y);}
bool cmpx (pp A , pp B)
{return A.x<B.x;}
bool cmpy (pp A, pp B)
{return A.y<B.y;}

int dx[100] = {1, 1, 1, 1, -1, -1, -1, -1};
int dy[100] = {1, 1, -1, -1, 1,1, -1, -1};
int dz[100] = {1, -1, 1, -1, 1, -1, 1, -1};
//bool vis[100000];

bool check2(int x1, int y1, int z1, int len)
{
	//if (len<20) printf("x%d y%d z%d len%d\n",x1,y1,z1, len);
	int	minx=5e8, miny = 5e8, minz = 5e8;
	int maxx = -5e8, maxy = -5e8, maxz=-5e8;
	for (int i=1;i<=n*8;i++)
	{
		if (x1<= a[i].x && a[i].x<=x1+len &&
			y1<= a[i].y && a[i].y<=y1+len &&
			z1<= a[i].z && a[i].z<=z1+len)
		continue;

		minx = min(minx, a[i].x);
		miny = min(miny, a[i].y);
		minz = min(minz, a[i].z);

		maxx = max(maxx, a[i].x);
		maxy = max(maxy, a[i].y);
		maxz = max(maxz, a[i].z);
		
	}
	//if (len<20) printf("min%d %d %d\nmax%d %d %d\n", minx,miny,minz,maxx,maxy,maxz);
	
	if (maxx-minx > len) return 0;
	if (maxy-miny > len) return 0;
	if (maxz-minz > len) return 0;

	
	return 1;
}

bool check(int len)
{
	int x1, y1, z1, x2, y2, z2;
	z1 = a[1].z;
	
	x1 = totx[1];
	y1 = toty[1];
	if (check2(x1, y1, z1, len)) return 1;

	x1 = totx[1];
	y1 = toty[cnty]-len;
	if (check2(x1, y1, z1, len)) return 1;

	x1 = totx[cntx]-len;
	y1 = toty[1];
	if (check2(x1, y1, z1, len)) return 1;

	x1 = totx[cntx]-len;
	y1 = toty[cnty]-len;
	if (check2(x1, y1, z1, len)) return 1;

	return 0;

}

void Clear()
{
	cntx = cnty = 0;
	memset(totx, 0,sizeof(totx));
	memset(toty, 0, sizeof(toty));
}

int main()
{
	//freopen("Desktop/Google Kickstart/B/C-large.in","r",stdin);
    //freopen("Desktop/Google Kickstart/B/ans.txt","w",stdout);
	int T;
	scanf("%d", &T);
	for (int kase=1; kase<=T;kase++)
	{
		Clear();
		scanf("%d", &n);
		int cnt = 0;
		cntx = cnty = 0;
		for (int i=1;i<=n;i++)
		{
			int x,y,z,r;
			scanf("%d%d%d%d", &x, &y, &z, &r);
			for (int j=0;j<8;j++)
			{
				a[++cnt].x = x+dx[j]*r;
				a[cnt].y = y+dy[j] * r;
				a[cnt].z = z+dz[j] *r;
			}
		}

		sort(a+1, a+n*8+1, cmpx);
		totx[++cntx] = a[1].x;
		for (int i=2;i<=n*8;i++)
		{
			if (a[i].x!=a[i-1].x)
				totx[++cntx] = a[i].x;
		}
		/*for (int i=1;i<=n*8;i++)
		{
			printf("%d  ", totx[i]);

		}puts("");*/

		
		sort(a+1, a+n*8+1, cmpy);
/*for (int i=1;i<=n*8;i++)
		{
			printf("zuobiao %d %d %d\n", a[i].x, a[i].y, a[i].z);

		}puts("");*/


		toty[++cnty] = a[1].y;
		//printf("Here ==  %d %d %d\n", totx);
		for (int i=2;i<=n*8;i++)
		{
			if (a[i].y!=a[i-1].y)
				toty[++cnty] = a[i].y;
		}
		// for (int i=1;i<=n*8;i++)
		// {
		// 	printf("%d  ", toty[i]);

		// }puts("");

		sort(a+1, a+n*8+1, cmpz);
		

		int l=-1,r = (int) 1e9, mid;
		while (l+1<r)
		{
			if ( check(mid = (l+r)/2) ) r=mid;
			else l = mid;

		}
		printf("Case #%d: %d\n", kase, r);


	}
	return 0;
}
/*

3
3
1 1 1 2
2 3 4 1
5 6 7 1
3
1 1 1 1
2 2 2 1
4 4 4 1
3
1 1 1 2
2 3 4 1
5 6 7 1
3
1 1 1 1
1 1 1 1
9 9 9 1
*/