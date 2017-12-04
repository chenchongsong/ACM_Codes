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
const int MAXN = 400011;
complex x[MAXN * 4], x0[MAXN * 4]; // clear to {0.0,0.0}
LL num[MAXN * 4], num0[MAXN * 4];

int w;
int main() {
    int N; cin >> N;
    memset(num, 0, sizeof(num));
    int maxx = 0, minx = 0x3f3f3f3f;
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        cin >> w;
        num[w] = 1; // 相同的weight只需要考虑一个
        num0[w] = 1;
        sum += (double)w;
        maxx = max(maxx, w);
        minx = min(minx, w);
    } 
    cout << maxx * 4 << " " << minx * 4 << " ";

    int len_tmp = maxx+1, len = 1;
    while ( len < len_tmp * 4 ) len <<= 1;

    
    // conv once
    for (int i=0; i < len; i++)
        x[i] = complex((double)num[i],0.0),
        x0[i] = complex((double)num0[i],0.0);

    fft(x, len, 1);
    fft(x0, len, 1);
    for (int i = 0; i < len;i++)
        x[i] = x[i] * x0[i];
    fft(x, len, -1);

    for (int i = 0; i < len;i++)
        num[i] = round(x[i].r) >= 1 ? 1 : 0;// 相同的weight只需要考虑一个


    // conv twice
    for (int i=0; i < len; i++)
        x[i] = complex(num[i],0.0);
    fft(x, len, 1);
    for (int i = 0; i < len;i++)
        x[i] = x[i] * x0[i];
    fft(x, len, -1);

    for (int i = 0; i < len;i++)
        num[i] = round(x[i].r) >= 1 ? 1 : 0;// 相同的weight只需要考虑一个


    // conv third
    for (int i=0; i < len; i++)
        x[i] = complex(num[i],0.0);
    fft(x, len, 1);
    for (int i = 0; i < len;i++)
        x[i] = x[i] * x0[i];
    fft(x, len, -1);

    for (int i = 0; i < len;i++)
        num[i] = round(x[i].r) >= 1 ? 1 : 0;// 相同的weight只需要考虑一个

    
    int Cnt = 0;
    for (int i=0; i<len; i++) {
        Cnt += (num[i] != 0);
    }
    cout << Cnt << " ";

    printf("%.10lf\n", sum * 4.0 / N);

    return 0;
}