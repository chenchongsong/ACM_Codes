#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
const double PI = acos(-1.0);
struct complex //复数结构体
{
    double r,i;
    complex(double _r = 0.0,double _i = 0.0)
    {r = _r; i = _i;}
    complex operator +(const complex &b)
    {return complex(r+b.r,i+b.i);}
    complex operator -(const complex &b)
    {return complex(r-b.r,i-b.i);}
    complex operator *(const complex &b)
    {return complex(r*b.r-i*b.i,r*b.i+i*b.r);}
};
void change(complex y[],int len)  //进行FFT和IFFT前的反转变换 位置i和 （i二进制反转后位置）互换 len必须去2的幂
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1; i++)
    {
        if(i < j)swap(y[i],y[j]); //交换互为小标反转的元素，i<j保证交换一次
        k = len/2;                //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        while( j >= k) {j -= k;k /= 2;}
        if(j < k) j += k;
    }
}
void fft(complex y[],int len,int on) //on==-1 IDFT
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j+=h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++) y[i].r /= len;
}
typedef long long LL;
const int MAXN = 200011;
complex x[MAXN * 4];
LL num[MAXN * 4]; // twice
LL once_num[MAXN * 4];

int a[MAXN];
int main() {
    int N;
    cin >> N;

    memset(num, 0, sizeof(num));
    for (int i = 0;i < N; i++) {
        cin >> a[i];
        num[a[i]]++;
        once_num[a[i]]++;
    }

    sort(a, a+N);
    int len_tmp = a[N-1]+1, len = 1;
    while ( len < len_tmp*2 ) len <<= 1;

    for (int i=0;i<len;i++)
        x[i] = complex(num[i],0);
    
    fft(x, len, 1);//DFT
    for(int i = 0;i < len;i++)
        x[i] = x[i]*x[i]; // a[i]*b[i]
    fft(x, len, -1);//IDFT

    for (int i = 0;i < len;i++)
        num[i] = (LL)(x[i].r+0.5); // 四舍五入

    int Cnt = 0, dis, M;
    cin >> M;
    while (M--) {
        cin >> dis;
        if (num[dis] || once_num[dis]) Cnt++;
    }
   
    cout << Cnt << endl;
    return 0;
}