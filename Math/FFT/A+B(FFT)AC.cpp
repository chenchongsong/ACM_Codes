#include <algorithm>
#include <cstring>
#include <string.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <cstdio>
#include <cmath>

#define LL long long
#define N 200005
#define INF 0x3ffffff

using namespace std;

const double PI = acos(-1.0);


struct Complex // 复数
{
    double r,i;
    Complex(double _r = 0,double _i = 0)
    {
        r = _r; i = _i;
    }
    Complex operator +(const Complex &b)
    {
        return Complex(r+b.r,i+b.i);
    }
    Complex operator -(const Complex &b)
    {
        return Complex(r-b.r,i-b.i);
    }
    Complex operator *(const Complex &b)
    {
        return Complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};

void change(Complex y[],int len) // 二进制平摊反转置换 O(logn)  
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++)
    {
        if(i < j)swap(y[i],y[j]); 
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
void fft(Complex y[],int len,int on) //DFT和FFT
{
    change(y,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j += h)
        {
            Complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}


const int M =50000;          // a数组所有元素+M，使a[i]>=0
const int MAXN = 800040;

Complex x1[MAXN];
int a[MAXN/4];                //原数组
long long num[MAXN];     //利用FFT得到的数组
long long tt[MAXN];        //统计数组每个元素出现个数

int main()
{
    int n=0;                   // n表示除了0之外数组元素个数
    int tot;
    scanf("%d",&tot);
    memset(num,0,sizeof(num));
    memset(tt,0,sizeof(tt));

    int cnt0=0;             //cnt0 统计0的个数
    int aa;

    for(int i = 0;i < tot;i++)
        {
            scanf("%d",&aa);
            if(aa==0) {cnt0++;continue;}  //先把0全删掉，最后特殊考虑0
            else a[n]=aa;  
            num[a[n]+M]++;
            tt[a[n]+M]++;
            n++;
        }

    sort(a,a+n);
    int len1 = a[n-1]+M+1;
    int len = 1;

    while( len < 2*len1 ) len <<= 1;

    for(int i = 0;i < len1;i++){
         x1[i] = Complex(num[i],0);
    }
    for(int i = len1;i < len;i++){
         x1[i] =Complex(0,0);
    }
    fft(x1,len,1);

    for(int i = 0;i < len;i++){
        x1[i] = x1[i]*x1[i];
    }
    fft(x1,len,-1);

    for(int i = 0;i < len;i++){
         num[i] = (long long)(x1[i].r+0.5);
    }

    len = 2*(a[n-1]+M);
        
    for(int i = 0;i < n;i++) //删掉ai+ai的情况
           num[a[i]+a[i]+2*M]--;
/*
   for(int i = 0;i < len;i++){
            if(num[i]) cout<<i-2*M<<' '<<num[i]<<endl;
    }
*/
    long long ret= 0;

    int l=a[n-1]+M;

    for(int i = 0;i <=l; i++)   //ai,aj,ak都不为0的情况
        {
            if(tt[i]) ret+=(long long)(num[i+M]*tt[i]);
        }

    ret+=(long long)(num[2*M]*cnt0);        // ai+aj=0的情况

    if(cnt0!=0)
        {
            if(cnt0>=3) {                   //ai,aj,ak都为0的情况
                long long tmp=1;
                tmp*=(long long)(cnt0);
                tmp*=(long long)(cnt0-1);
                tmp*=(long long)(cnt0-2);
                ret+=tmp;
            }
             for(int i = 0;i <=l; i++)
                {
                    if(tt[i]>=2){             // x+0=x的情况      
                        long long tmp=(long long)cnt0;
                        tmp*=(long long)(tt[i]);
                        tmp*=(long long)(tt[i]-1);
                        ret+=tmp*2;
                    }
                }
        }

    printf("%lld\n",ret);

    return 0;
}