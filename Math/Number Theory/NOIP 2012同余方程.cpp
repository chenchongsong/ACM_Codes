#include<cstdio>
#define ll long long
void exgcd(ll a,ll b,ll& g,ll& x,ll& y)
{
    //printf("%lld -- %lld\n", a, b);
    if(!b){g=a;x=1,y=0;}
    else{exgcd(b,a%b,g,y,x);y-=x*(a/b);}
}

// hzwer version
void EXGCD(int a,int b,int &x,int &y)
{
    if(b==0){x=1;y=0;return;}
    EXGCD(b,a%b,x,y);
    int t=x;x=y,y=t-a/b*y;
}

int main()
{
    ll A,B;
    printf("Enter A & M\n\n");
    scanf("%lld %lld",&A,&B);
    ll G,X,Y;
    exgcd(A,B,G,X,Y);
    printf("原数 x = %lld  n = %lld ------ st:  Ax+Mn = 1\n", X, Y);
    printf("正整数 %lld\n",(X+B)%B);
    return 0;
}