#include <cstdio>
#include <algorithm>
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


const int MAXN = 400040;
int a[MAXN/4];
complex x[MAXN];
typedef long long LL;
LL num[MAXN], sum[MAXN];
int main()
{
    int Case, N;
    scanf("%d", &Case);
    while(Case--)
    {
        scanf("%d", &N);
        memset(num, 0, sizeof(num));
        for (int i = 0;i < N; i++)
        {
            scanf("%d", &a[i]);
            num[a[i]]++;
        }

        sort(a, a+N);
        int len_tmp = a[N-1]+1, len = 1;
        while ( len < len_tmp*2 ) len <<= 1;

        for (int i=0;i<len_tmp;i++)
            x[i] = complex(num[i],0);
        for (int i=len_tmp;i<len;i++)
            x[i] = complex(0,0);        
        
        fft(x, len, 1);//DFT
        for(int i = 0;i < len;i++)
            x[i] = x[i]*x[i];
        fft(x, len, -1);//IDFT

        for (int i = 0;i < len;i++)
            num[i] = (LL)(x[i].r+0.5);
        len = 2 * a[N-1];

        for (int i=0;i<N;i++)
            num[a[i]+a[i]]--;
        //减掉两个相同的组合

        for (int i=0;i<=len;i++)
            num[i] /= 2;
        //选择的无序，除以2

        sum[0] = 0;
        for (int i=0;i<=len;i++)
            sum[i] = sum[i-1]+num[i];

        LL Cnt = 0;
        for (int i=0; i<N;i++)
        {
            Cnt += sum[len]-sum[a[i]];
            //此时已加上所有 aj+ak > ai 的情况
            //然而有重复 为了保证不重复 我们每次只应加上aj<ai && ak<ai 的情况
            
            Cnt -= (N-1); //扣除一个取本身，另外一个取其他 (because:a[i]+other>a[i] 故而属于多加的部分 应扣除)
            Cnt -= (LL) (N-1-i) * i; //扣除一个取大，一个取小的 (because:一大一小加起来肯定比ai大)
            Cnt -= (LL)(N-i-1)*(N-i-2)/2; //扣除大于它的取两个的组合 (because:两大段加起来肯定比ai大)
        }
        long long tot = (LL)N*(N-1)*(N-2)/6;
        printf("%.7lf\n", (double)Cnt/tot);
    }
    return 0;
}