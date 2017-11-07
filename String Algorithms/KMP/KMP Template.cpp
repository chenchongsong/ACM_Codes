#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define maxn 5000010
using namespace std;

char P[maxn]; // Pattern 短串
char T[maxn]; // Text 长串
int f[maxn];

void getFail(char* P,int* f) {
//字符串p自我匹配
    int m = strlen(P);
    f[0] = f[1] = 0;
    for(int i = 1; i < m; i++) {
        int j = f[i];
        while(j && P[i]!=P[j])
            j = f[j];
        f[i+1] = P[i]==P[j] ? j+1 : 0;
    } 
}
void Find(char* T, char* P, int* f) {
//p去匹配字符串T
    int n = strlen(T), m = strlen(P);
    getFail(P, f);  //得出部分匹配表
    int j = 0;
    //j:短串的下标  i: 长串下标
    for (int i = 0; i < n; i++) { 
        while (j && P[j] != T[i])
            j = f[j];
        if (P[j] == T[i]) j++; 
        if(j == m)
            printf("%d ", i-m+1);
    }
    puts("");
}
int main() {
    // c++ getline(cin, P)
    // c   gets(P)
    while (gets(P)) {
        gets(T);
        Find(T, P, f); 
    }
    return 0;
}