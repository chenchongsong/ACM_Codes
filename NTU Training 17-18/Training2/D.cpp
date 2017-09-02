#include <cstdio>
typedef long long ll;
using namespace std;


ll N, P;
ll cnt=0;							// 逆序对个数
ll a[1000010], c[1000010];
ll sum[1000010];
void MergeSort(ll l, ll r)	// r＝右边界索引＋1
{ 
	ll mid, i, j, tmp;
	if (r>l+1)
	{
		mid = (l+r)/2;
		MergeSort(l, mid);
		MergeSort(mid, r);
		tmp = l;
		for (i=l,j=mid; i<mid && j<r; )
		{
			if (sum[i]>=sum[j])
			{
				c[tmp++] = sum[j++];
				cnt += mid-i;			// 使用排序，就可以方便地数跨“分界”的逆序对个数了
			}
			else
				c[tmp++] = sum[i++];
		}
		if (j<r) for (; j<r; j++) c[tmp++] = sum[j];
		else for (; i<mid; i++) c[tmp++] = sum[i];
		for (i=l; i<r; i++) sum[i]=c[i];
	}
}

int main() {

	scanf("%lld", &N);
	for (ll i=1; i<= N; i++) {
		scanf("%lld", &a[i]);
		//if (a[i] >= )
	}
	scanf("%lld", &P);

	for (ll i=1; i<=N; i++) {
		//if (a[i] >= P) cnt++;
		a[i] -= P;
	}
	sum[0] = 0;
	for (ll i=1; i<=N; i++) {
		sum[i] = sum[i-1] + a[i];

	}
	for (ll i=1; i<=N; i++) {
		sum[i] = 0-sum[i];
		//printf("%lld -- %lld\n", i, sum[i]);

	}

	

	MergeSort(0, N+1);
	printf("%lld\n", cnt);
	return 0;


}