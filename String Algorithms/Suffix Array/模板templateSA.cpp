#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define maxn 400010
using namespace std;  
char s[maxn];  
int rk1[maxn], rk2[maxn], cnt[maxn];
int sa[maxn], rk[maxn], ht[maxn];
int N;

bool cmpSA(int *y,int a,int b,int k, int n) {  
    int a1=y[a];
    int b1=y[b];
    int a2=a+k >= n ? -1: y[a+k];
    int b2=b+k >= n ? -1: y[b+k];
    return a1==b1 && a2==b2;
}
void buildSA(const char* str, int n, int m) {

    for(int i = 0; i < m; i++) cnt[i] = 0;
    for(int i = 0; i < n; i++) ++cnt[rk1[i]=(int)s[i]];
    for(int i = 1; i < m; i++) cnt[i] += cnt[i-1];
    for(int i = n-1; i >= 0; i--) sa[--cnt[rk1[i]]]=i;

    for(int len=1; len<=n; len<<=1) {
        int p=0;
        for(int i = n-len; i < n; i++) rk2[p++]=i;
        for(int i=0; i<n; i++)
            if( sa[i]>=len )
                rk2[p++]=sa[i]-len;

        for(int i = 0; i < n; i++) cnt[i]=0;
        for(int i = 0; i < n; i++) ++cnt[rk1[rk2[i]]];
        for(int i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--) sa[--cnt[rk1[rk2[i]]]]=rk2[i];

        for(int i = 0; i < n; i++) swap(rk1[i], rk2[i]);
        int tot_rk = 1;
        rk1[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            rk1[sa[i]] = cmpSA(rk2,sa[i],sa[i-1],len,n) ? tot_rk-1 : tot_rk++;
        if (tot_rk >= n) break;
    }
}
void getHeight(const char* str, int n) {
    for (int i = 0; i<n; i++) rk[sa[i]] = i;
    ht[0] = 0;
    for (int i = 0, k = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (str[i + k] == str[j + k]) k++;
        ht[rk[i]] = k;
    }
}

int main()  
{  
	// freopen("Desktop/dvaput/dvaput.in.7", "r", stdin);
	int t;
	scanf("%d\n", &t);
    scanf("%s",s);
    N=strlen(s);
    buildSA(s, N, 257);
    getHeight(s, N);  
    // for(int i=0; i<N; i++) cout << i; cout << endl;  
    // for(int i=0; i<N; i++) cout << sa[i] << " "; cout << endl;  
    int ans = 0;
    for(int i=0; i<N; i++) ans = max(ans, ht[i]);
    printf("%d\n", ans);  
    return 0;  
}  