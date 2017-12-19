#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 100010
using namespace std;
int N;
int a[maxn];
int Case;
int size[maxn];
int w[maxn], h[maxn];
int cnt;

void Clear()
{
	memset(a,0,sizeof(a));
	memset(size,0,sizeof(size));
	memset(w,0,sizeof(w));
	memset(h,0,sizeof(h));
	//memset(size,0,sizeof(size));
	cnt = 0;
}

int main()
{
	scanf("%d", &Case);
	while (Case--)
	{
		Clear();

		scanf("%d",&N);
		for (int i=1;i<=N;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a+1,a+N+1);

		for (int i=2;i<=N;i++)
		{
			if (a[i]!=a[i-1])
			{
				w[++cnt] = i-1;
				h[cnt] = a[i] - a[i-1];
				size[cnt] = w[cnt] * h[cnt];
			}


		}
		w[++cnt] = N;
		h[cnt] = 1e9 + 10;
		size[cnt] = 2100000000;

		int pos = 1; //1~cnt
		int delta = a[1];

		while (delta + h[pos] >= size[pos])
		{
			delta = delta + h[pos] - size[pos];
			pos++;

			printf("delta %d ---- pos %d\n",delta, pos);
		}

		if (pos != cnt)
			printf("%d\n", a[N]);
		else
		{
			int Ans = a[N];
			Ans += delta / (N-1);
			Ans += ( delta % (N-1) ) > 0;

			printf("delta. -- %d\n", delta);
			printf("%d\n", Ans);
		}
		return 0;
	}
	
}

/*

1
3
2 2 3

*/
