#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 500010
using namespace std;

int P[maxn], T[maxn], f[maxn];
int a1[maxn], a2[maxn];
int n;

void getfail(int p[],int f[]) //字符串p自我匹配 
{
    int len=n;
    f[0]=f[1]=0;
    for(int i=1;i<len;i++)
    {
        int j=f[i];
        while(j&&p[i]!=p[j])
            j=f[j];
        if(p[i]==p[j])
            f[i+1]=j+1;//多匹配到了一个字符
        else 
            f[i+1]=0;//该字符配不上 
    } 
}
int find(int* T, int*P, int*f)//p去匹配字符串T 
{  
    // int n = strlen(T), m = strlen(P);  

    getfail(P, f);  //得出部分匹配表 
    int j = 0;  //短串的下标 
    for(int i = 0; i < n*2; i++) //长串下标 
    {  
        while(j && P[j] != T[i])//突然失配了 
        {  
            j = f[j];  //j往回退，直到0或者上一个字符相等的位置 
        }  
        if(P[j] == T[i])
        {  
            j++;  //匹配了一个字符，j++ 
        }  
        if(j == n)  //短串匹配到头了 
        {  
            return i - n + 1;//返回成功匹配的起点字符位置 
        }
    }  
    return -1;  
} 

int main()
{
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", &a1[i]);
    }
    sort(a1, a1+n);
    T[0] = (a1[0] - a1[n-1]+ 360000) % 360000;
    for (int i=1; i<n; i++) {
        T[i] = a1[i]-a1[i-1];
    }
    for (int i=n; i<n*2; i++) {
        T[i] = T[i-n];
    }


    for (int i=0; i<n; i++) {
        scanf("%d", &a2[i]);
    }
    sort(a2, a2+n);
    P[0] = (a2[0] - a2[n-1] + 360000) % 360000;
    for (int i=1; i<n; i++) {
        P[i] = a2[i]-a2[i-1];
    }

    // for (int i=0; i<n; i++) {
    //     printf("i %d -- %d\n",i,P[i]);
    // }
    
    int t=find(T, P, f);

    if (t == -1) puts("impossible");
    else puts("possible");

    return 0;
}