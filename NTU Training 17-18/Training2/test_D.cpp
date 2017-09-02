#include <cstdio>
using namespace std;

int cnt=0;							// 逆序对个数
int a[1000010], c[1000010];
int sum[1000010];
void MergeSort(int l, int r)	// r＝右边界索引＋1
{ 
	int mid, i, j, tmp;
	if (r>l+1)
	{
		mid = (l+r)/2;
		MergeSort(l, mid);
		MergeSort(mid, r);
		tmp = l;
		for (i=l,j=mid; i<mid && j<r; )
		{
			if (a[i]>=a[j])
			{
				c[tmp++] = a[j++];
				cnt += mid-i;			// 使用排序，就可以方便地数跨“分界”的逆序对个数了
			}
			else
				c[tmp++] = a[i++];
		}
		if (j<r) for (; j<r; j++) c[tmp++] = a[j];
		else for (; i<mid; i++) c[tmp++] = a[i];
		for (i=l; i<r; i++) a[i]=c[i];
	}
}

int main() {
	a[1] = 1;
	a[2] = 2;
	a[3] = 0;
	MergeSort(1, 4);
	printf("cnt == %d\n", cnt);
	return 0;
}