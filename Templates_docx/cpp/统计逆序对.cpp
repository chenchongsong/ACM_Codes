#include <cstdio>
#define MaxN 1000010
using namespace std;

int cnt=0; // 逆序对个数
int a[MaxN], c[MaxN];
void MergeSort(int l, int r) {
// if a[1]~a[N] then r = N+1
	int mid, i, j, tmp;
	if (r>l+1) {
		mid = (l+r)/2;
		MergeSort(l, mid);
		MergeSort(mid, r);
		tmp = l;
		for (i=l,j=mid; i<mid && j<r; )
			if (a[i]>a[j])
			// 如果算上(x,x)则改成a[i]>=a[j]
			{
				c[tmp++] = a[j++];
				cnt += mid-i;
			}
			else
				c[tmp++] = a[i++];
		if (j<r) for (; j<r; j++) c[tmp++] = a[j];
		else for (; i<mid; i++) c[tmp++] = a[i];
		for (i=l; i<r; i++) a[i]=c[i];
	}
}

int main() {
	a[1] = 4;
	a[2] = 2;
	a[3] = 1;
	MergeSort(1, 4);
	printf("cnt == %d\n", cnt);
	return 0;
}